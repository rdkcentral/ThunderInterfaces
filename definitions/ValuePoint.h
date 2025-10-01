/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "Module.h"
#include <interfaces/IValuePoint.h>

namespace Thunder {
namespace Implementation {

    class ValuePoint : public Exchange::IValuePoint {
    private:
        enum notify : uint8_t {
            NONE     = 0x00,
            UPDATE   = 0x01,
            METADATA = 0x02
        };
        class Job { 
        public: 
            Job() = delete;
            Job(Job&&) = delete;
            Job(const Job&) = delete;
            Job& operator=(const Job&) = delete;

            Job(ValuePoint& parent)
                : _parent(parent) 
            {
            }
            ~Job() = default;

        public:
            void Dispatch()
            {
                _parent.Notify();
            }

        private:
            ValuePoint& _parent;
        };
        class Timed {
        public:
            Timed() = delete;
            Timed(Timed&&) = delete;
            Timed(const Timed&) = delete;
            Timed& operator=(const Timed&) = delete;

            Timed(ValuePoint& parent)
                : _parent(parent)
                , _nextTime(0)
                , _periodicity(0) {
            }
            ~Timed() = default;

        public:
            inline bool IsActive() const {
                return (_periodicity != 0);
            }
            // Return the periodicity in Seconds...
            inline uint32_t Period() const
            {
                return (_periodicity / 1000);
            }
            inline void Period(const uint32_t periodicity)
            {
                _parent._adminLock.Lock();
                _periodicity = 0;
                _parent._adminLock.Unlock();

                // If we are going to change the periodicity, we need to remove 
                // the current action, if ongoing, anyway..
                // First attempt to remove the Job. The job might currently be
                // executing....
                _parent._timed.Revoke();

                if (periodicity != 0) {
                    _periodicity = periodicity * 1000;
                    _nextTime = Core::Time::Now().Ticks();
                    _parent._timed.Submit();
                }
            }
            void Dispatch()
            {
                if (_parent.Evaluate() == true) {
                    _parent.Updated();
                }

                _parent._adminLock.Lock();
                if (_periodicity != 0) {
                    _nextTime.Add(_periodicity);
                    _parent._timed.Reschedule(_nextTime);
                }
                _parent._adminLock.Unlock();
            }

        private:
            ValuePoint& _parent;
            Core::Time _nextTime;
            uint32_t _periodicity;
        };
        using Notifiers = std::vector<IValuePoint::INotification*>;

    public:
        ValuePoint() = delete;
        ValuePoint(ValuePoint&&) = delete;
        ValuePoint(const ValuePoint&) = delete;
        ValuePoint& operator=(const ValuePoint&) = delete;

        PUSH_WARNING(DISABLE_WARNING_THIS_IN_MEMBER_INITIALIZER_LIST);
        ValuePoint(const uint32_t parentId, const uint32_t id, const string& manufacturer, const string& model, const protocol prot, const uint32_t type, const int32_t min = 0, const int32_t max = 0)
            : _adminLock()
            , _parent(parentId)
            , _manufacturer(manufacturer)
            , _model(model)
            , _id(id & 0x00FFFFFF)
            , _protocol(prot)
            , _type(type)
            , _condition(IValuePoint::constructing)
            , _min(min > max ? max : min)
            , _max(min > max ? min : max)
            , _metadata()
            , _inverse(min > max)
            , _cached(Core::NumberType<int32_t>::Min())
            , _notify(notify::NONE)
            , _clients()
            , _job(*this)
            , _timed(*this)
        {
        }
        POP_WARNING();
        inline ValuePoint(const uint32_t parentId, const uint32_t id, const string& manufacturer, const string& model, const protocol prot, const basic base, const specific spec, const dimension dim, const uint8_t decimals, const int32_t min = 0, const int32_t max = 0)
            : ValuePoint(parentId, id, manufacturer, model, prot, IValuePoint::Type(base, spec, dim, decimals), min, max)
        {
        }
        ~ValuePoint() override {
            ASSERT(_clients.size() == 0);
            ASSERT(_condition == IValuePoint::deactivated);
            _job.Revoke();
    	}

    public:

        // ------------------------------------------------------------------------
        // Convenience methods to extract interesting information from the type
        // ------------------------------------------------------------------------
        inline uint32_t Id() const {
            return (_id & 0x00FFFFFF);
        }
        inline uint32_t Identifier() const {
            return (_id);
        }
        inline int32_t Cache() const {
            return (_cached);
        }
        inline bool Inverse() const {
            return (_inverse);
        }
        inline condition Condition() const {
            return(_condition);
        }
        inline basic Basic() const {
            return (IValuePoint::Basic(_type));
        }
        inline dimension Dimension() const {
            return (IValuePoint::Dimension(_type));
        }
        inline specific Specific() const {
            return (IValuePoint::Specific(_type));
        }
        inline uint8_t Decimals() const {
            return (IValuePoint::Decimals(_type));
        }
        inline bool IsReadOnly() const {
            return (Basic() == IValuePoint::measurement);
        }
        inline int32_t Minimum() const {
            int32_t result;

            if ((_min != 0) || (_max != 0)) {
                result = _min;
            }
            else {
                Exchange::IValuePoint::dimension dimension = Dimension();

                switch (dimension) {
                case logic:
                case percentage:
                case kwh:
                case kvah:
                case pulses: {
                    result = 0;
                    break;
                }
                case degrees: {
                    result = -127;
                    break;
                }
                case units: {
                    result = Core::NumberType<int32_t>::Min();
                    break;
                }
                default:
                    ASSERT(false);
                    break;
                }
            }

            return (result);
        }
        inline int32_t Maximum() const {
            int32_t result;

            if ((_min != 0) || (_max != 0)) {
                result = _max;
            }
            else {
                switch (Dimension()) {
                case logic: {
                    result = 1;
                    break;
                }
                case percentage: {
                    result = 100;
                    break;
                }
                case kwh:
                case kvah:
                case pulses:
                case units: {
                    result = Core::NumberType<int32_t>::Max();
                    break;
                }
                case degrees: {
                    result = +512;
                    break;
                }
                }
            }
            return (result);
        }
        void Metadata(const string& metadata) {
            _metadata = metadata;
        }

        // ------------------------------------------------------------------------
        // Polling interface methods
        // ------------------------------------------------------------------------
        // Define the polling time in Seconds. This value has a maximum of a 48 days.
        inline uint32_t Period() const
        {
            return (static_cast<const Timed&>(_timed).Period());
        }
        inline void Period(const uint32_t value)
        {
            _adminLock.Lock();
            static_cast<Timed&>(_timed).Period(value);
            _adminLock.Unlock();
        }

        // ------------------------------------------------------------------------
        // IValuePoint default interface implementation
        // ------------------------------------------------------------------------
        // Pushing notifications to interested sinks
        Core::hresult Register(IValuePoint::INotification* const sink) override
        {
            _adminLock.Lock();

            Notifiers::iterator index = std::find(_clients.begin(), _clients.end(), sink);

            if (index == _clients.end()) {
                sink->AddRef();
                _clients.push_back(sink);
                sink->Update(_id);
            }

            _adminLock.Unlock();

            return (Core::ERROR_NONE);
        }
        Core::hresult Unregister(const IValuePoint::INotification* sink) override
        {
            _adminLock.Lock();

            Notifiers::iterator index = std::find(_clients.begin(), _clients.end(), sink);

            if (index != _clients.end()) {
                sink->Release();
                _clients.erase(index);
            }

            _adminLock.Unlock();

            return (Core::ERROR_NONE);
        }

        Core::hresult Identifier(uint32_t& ID /* @out */) const override {
            ID = Identifier();
            return (Core::ERROR_NONE);
        }

        Core::hresult Bundle(uint32_t& ID /* @out */) const override {
            uint32_t result = Core::ERROR_UNAVAILABLE;
            if (_parent != static_cast<uint32_t>(~0)) {
                ID = _parent;
                result = Core::ERROR_NONE;
			}
            return (result);
        }

        Core::hresult Condition(condition& value /* @out */) const  override {
            value = Condition();;
            return (Core::ERROR_NONE);
        }

        Core::hresult Type(uint32_t& value /* @out */) const  override {
            value = _type;
            return (Core::ERROR_NONE);
        }

        Core::hresult Minimum(int32_t& value /* @out */) const  override {
            value = Minimum();
            return (Core::ERROR_NONE);
        }

        Core::hresult Metadata(IValuePoint::Info& value /* @out */) const override
        {
            value.base = IValuePoint::Basic(_type);
            value.extended = IValuePoint::Specific(_type);
            value.type = IValuePoint::Dimension(_type);
            value.fraction = IValuePoint::Decimals(_type);
            value.manufacturer = _manufacturer;
            value.model = _model;
            if (_metadata.empty() == false) {
                value.metadata = _metadata;
            }
            return (Core::ERROR_NONE);
        }

        Core::hresult Value(int32_t& value) const override {
            uint32_t result = Core::ERROR_UNAVAILABLE;

            _adminLock.Lock();

            if (Condition() == condition::activated) {
                result = Read(value);

                if ((result == Core::ERROR_NONE) && (_cached != value) && (static_cast<const Timed&>(_timed).IsActive() == false) ) {
                    _cached = value;
                    Updated();
                }
            }

            _adminLock.Unlock();

            return (result);
        }

        Core::hresult Value(const int32_t value) override {

            uint32_t result = Core::ERROR_UNAVAILABLE;

            if (IsReadOnly() == false)
            {
                int32_t current;

                _adminLock.Lock();

                if (Condition() == condition::activated) {
                    result = Read(current);

                    if (result == Core::ERROR_NONE)
                    {
                        if (current != value) {
                            result = Write(value);
                        }

                        if ((result == Core::ERROR_NONE) && (_cached != value)) {
                            _cached = value;

                            Updated();
                        }
                    }
                }

                _adminLock.Unlock();
            }

            return (result);
        }

        Core::hresult Maximum(int32_t& value /* @out */) const  override {
            value = Maximum();
            return (Core::ERROR_NONE);
        }

        bool Evaluate() override {
            bool modified = false;

            _adminLock.Lock();

            if (Condition() == condition::activated) {
                int32_t newValue;
                if ((Read(newValue) == Core::ERROR_NONE) && (newValue != _cached)) {
                    _cached = newValue;
                    modified = true;
                }

            }
            _adminLock.Unlock();

            return (modified);
        }

        virtual void Activate() {
            _adminLock.Lock();

            if ((_condition == IValuePoint::deactivated) || (_condition == IValuePoint::constructing)) {
                _condition = IValuePoint::activated;

                Metadata();
            }

            _adminLock.Unlock();
        }
        virtual void Deactivate() {
            _adminLock.Lock();

            if ( (_condition == IValuePoint::activated) || (_condition == IValuePoint::constructing) ) {

                static_cast<Timed&>(_timed).Period(0);
                _condition = IValuePoint::deactivated;

                Metadata();
            }

            _adminLock.Unlock();
        }

        inline void Updated() const
        {
            if (_clients.size() > 0) {

                _adminLock.Lock();

                if ((_notify & notify::UPDATE) != 0) {
                    _adminLock.Unlock();
                }
                else if (_notify != notify::NONE) {
                    _notify = static_cast<notify>(_notify|notify::UPDATE);
                    _adminLock.Unlock();
                }
                else {
                    _notify = notify::UPDATE;
                    _adminLock.Unlock();

                    _job.Submit();
                }
            }
        }
 
        BEGIN_INTERFACE_MAP(ValuePoint)
            INTERFACE_ENTRY(Exchange::IValuePoint)
        END_INTERFACE_MAP

    protected:
        virtual uint32_t Read(int32_t& value) const = 0;
        virtual uint32_t Write(const int32_t value) = 0;

        inline bool Cache(const int32_t value) {
            _adminLock.Lock();
            bool result = (value != _cached);
            _cached = value;
            _adminLock.Unlock();
            return (result);
        }
        inline int32_t FromRange(const int32_t value, const int32_t range) const
        {
            int32_t result = value;

            // Adapt it to from the given range, if needed..
            if ((_max - _min) != range) {
                result = (((value * (_max - _min) * 2) + range) / (2 * range));
            }
            return (result);
        }
        inline int32_t ToRange(const int32_t value, const int32_t range) const
        {
            int32_t result = value;

            // Adapt it to the requetsed value, if needed..
            if ((_max - _min) != range) {
                result = ((((value * range * 2) + (_max - _min)) / (2 * (_max - _min))) + _min);
            }

            return (result);
        }
        inline void Metadata() const
        {
            if (_clients.size() > 0) {
                _adminLock.Lock();

                if ((_notify & notify::METADATA) != 0) {
                    _adminLock.Unlock();
                }
                else if (_notify != notify::NONE) {
                    _notify = static_cast<notify>(_notify | notify::METADATA);
                    _adminLock.Unlock();
                }
                else {
                    _notify = notify::METADATA;
                    _adminLock.Unlock();

                    _job.Submit();
                }
            }
        }
        inline bool Schedule(const Core::Time& evaluationPoint)
        {
            return (_timed.Reschedule(evaluationPoint));
        }
        inline void ChangeDirection(const basic type)
        {
			_type = IValuePoint::Type(type, IValuePoint::Specific(_type), IValuePoint::Dimension(_type), IValuePoint::Decimals(_type));
        }
        inline void Lock() const {
            _adminLock.Lock();
        }
        inline void Unlock() const {
            _adminLock.Unlock();
        }

    private:
        void Notify()
        {
            _adminLock.Lock();

            uint8_t mode = _notify;
            _notify = notify::NONE;

            if (mode == notify::NONE) {
                _adminLock.Unlock();
            }
            else {
                Notifiers::iterator index(_clients.begin());
                RecursiveCall(index, mode);
            }
        }
        void RecursiveCall(Notifiers::iterator& position, uint8_t mode)
        {
            if (position == _clients.end()) {
                _adminLock.Unlock();
            } else {
                IValuePoint::INotification* client(*position);
                client->AddRef();
                position++;
                RecursiveCall(position, mode);

                if ((mode & notify::UPDATE) != 0) {
                    client->Update(_id);
                }
                if ((mode & notify::METADATA) != 0) {
                    client->Metadata(_id);
                }

                client->Release();
            }
        }

    private:
        mutable Core::CriticalSection _adminLock;
        const uint32_t _parent;
        const string _manufacturer;
        const string _model;
        const uint32_t _id;
		const protocol _protocol;
        uint32_t _type;
        condition _condition;
        const int32_t _min;
        const int32_t _max;
        string _metadata;
        const bool _inverse;
        mutable int32_t _cached;
        mutable notify _notify;
        Notifiers _clients;
        mutable Core::WorkerPool::JobType<Job> _job;
        Core::WorkerPool::JobType<Timed> _timed;
    };

    class EXTERNAL Catalog 
        : public Exchange::IValuePoint
        , public Exchange::IValuePoint::ICatalog {
    private:
        using Notifiers = std::vector<IValuePoint::INotification*>;
		using CatalogObservers = std::vector<IValuePoint::ICatalog::INotification*>;
        using Members = std::unordered_map<uint32_t, IValuePoint*>;

        class Sink : public Exchange::IValuePoint::INotification {
        public:
            Sink() = delete;
            Sink(Sink&&) = delete;
            Sink(const Sink&) = delete;
            Sink& operator=(Sink&&) = delete;
            Sink& operator=(const Sink&) = delete;

            Sink(Catalog& parent)
                : _parent(parent) {
			}
			~Sink() override = default;

        public:
            // IValuePoint::INotification methods
            // -------------------------------------------------------------------------------------------------------
            void Update(const uint32_t id) override {
                _parent.Update(id);
            }
            void Metadata(const uint32_t id) override {
                _parent.Metadata(id);
            }
            BEGIN_INTERFACE_MAP(Sink)
                INTERFACE_ENTRY(Exchange::IValuePoint::INotification)
            END_INTERFACE_MAP

        private:
			Catalog& _parent;
        };

    public:
        Catalog() = delete;
        Catalog(Catalog&&) = delete;
        Catalog(const Catalog&) = delete;
        Catalog& operator=(Catalog&&) = delete;
        Catalog& operator=(const Catalog&) = delete;

        PUSH_WARNING(DISABLE_WARNING_THIS_IN_MEMBER_INITIALIZER_LIST);
        Catalog(const uint32_t parent, const uint32_t id, const string& manufacturer, const string& model, const IValuePoint::protocol prot)
            : _adminLock()
            , _parent(parent)
            , _id(id)
            , _manufacturer(manufacturer)
            , _model(model)
			, _protocol(prot)
            , _type(IValuePoint::Type(basic::group, specific::system, dimension::units, 0))
            , _members()
            , _clients()
            , _sink(*this) {
        }
        POP_WARNING();
        ~Catalog() override {
            ASSERT(_clients.size() == 0);
            ASSERT(_observers.size() == 0);

			_adminLock.Lock();

            // Unregister all members from the sink.
            for (auto& entry : _members) {
                entry.second->Unregister(&_sink);
                entry.second->Release();
            }
            for (auto& entry : _clients) {
				entry->Release();
            }
            for (auto& entry : _observers) {
                entry->Release();
            }
            _members.clear();
            _clients.clear();
			_observers.clear();

            _adminLock.Unlock();
        }

    public:
        //   IValuePoint methods
        // -------------------------------------------------------------------------------------------------------
        Core::hresult Register(IValuePoint::INotification* sink) override {
            _adminLock.Lock();

            Notifiers::iterator index = std::find(_clients.begin(), _clients.end(), sink);

            if (index == _clients.end()) {
                sink->AddRef();
                _clients.push_back(sink);
                sink->Update(_id);
            }

            _adminLock.Unlock();
            return (Core::ERROR_NONE);
        }
        Core::hresult Unregister(const IValuePoint::INotification* sink) override {
            _adminLock.Lock();

            Notifiers::iterator index = std::find(_clients.begin(), _clients.end(), sink);

            if (index != _clients.end()) {
                sink->Release();
                _clients.erase(index);
            }

            _adminLock.Unlock();
            return (Core::ERROR_NONE);
        }
        Core::hresult Identifier(uint32_t& ID /* @out */) const override {
            ID = _id;
            return (Core::ERROR_NONE);
        }
        Core::hresult Bundle(uint32_t & ID /* @out */) const override {
            uint32_t result = Core::ERROR_UNAVAILABLE;
            if (_parent != static_cast<uint32_t>(~0)) {
                ID = _parent;
                result = Core::ERROR_NONE;
            }
            return (result);
        }
        Core::hresult Condition(condition& value /* @out */) const {
            value = condition::activated;
            return(Core::ERROR_NONE);
        }
        Core::hresult Type(uint32_t& value /* @out */) const override {
            value = _type;
            return (Core::ERROR_NONE);
        }
        Core::hresult Metadata(IValuePoint::Info& value /* @out */) const override {
            value.base = IValuePoint::Basic(_type);
            value.extended = IValuePoint::Specific(_type);
            value.type = IValuePoint::Dimension(_type);
            value.fraction = IValuePoint::Decimals(_type);
            value.manufacturer = _manufacturer;
            value.model = _model;
			value.communication = _protocol;
            value.metadata.Clear();
            return (Core::ERROR_NONE);
        }
        Core::hresult Value(int32_t& value) const override {
            value = static_cast<int32_t>(_members.size());
            return (Core::ERROR_NONE);
        }
        Core::hresult Value(const int32_t) override {
            return (Core::ERROR_BAD_REQUEST);
        }
        Core::hresult Minimum(int32_t& value) const override {
            value = 0;
            return (Core::ERROR_NONE);
        }
        Core::hresult Maximum(int32_t& value) const override {
            value = static_cast<int32_t>(_members.size());
            return (Core::ERROR_NONE);
        }
        bool Evaluate() override {
            return(false);
        }
        uint32_t Count() const {
			return (static_cast<uint32_t>(_members.size()));
        }

        //   IValuePoint::ICatalog methods
        // -------------------------------------------------------------------------------------------------------
        Core::hresult Register(IValuePoint::ICatalog::INotification* const sink) override {
			uint32_t result = Core::ERROR_DUPLICATE_KEY;

            Core::SafeSyncType<Core::CriticalSection> lock(_adminLock);

            CatalogObservers::iterator index = std::find(_observers.begin(), _observers.end(), sink);

            if (index == _observers.end()) {
                result = Core::ERROR_NONE;
                sink->AddRef();
                _observers.push_back(sink);
                for(const auto& entry : _members) {

                    Exchange::IValuePoint::condition status;

                    ASSERT(entry.second != nullptr);

                    if ((entry.second->Condition(status) == Core::ERROR_NONE) && (status == Exchange::IValuePoint::condition::activated)) {
                        sink->Activated(entry.second);
                    }
				}
            }
			return (result);
        }
        Core::hresult Unregister(const IValuePoint::ICatalog::INotification* sink) override {
            uint32_t result = Core::ERROR_NOT_EXIST;
            Core::SafeSyncType<Core::CriticalSection> lock(_adminLock);
            CatalogObservers::iterator index = std::find(_observers.begin(), _observers.end(), sink);
            if (index != _observers.end()) {
                sink->Release();
                _observers.erase(index);
				result = Core::ERROR_NONE;
			}
            return (result);
		}
        // Get a specific ValuePoint by its Id, owned by this Catalog.
        Core::hresult Resource(const uint32_t id, IValuePoint*& interface /* @out */) override {
			uint32_t result = Core::ERROR_NOT_EXIST;
            Core::SafeSyncType<Core::CriticalSection> lock(_adminLock);
            Members::const_iterator index(_members.find(id));
            if (index != _members.cend()) {
                interface = index->second;
                interface->AddRef();
                result = Core::ERROR_NONE;
            }
            return (result);
		}

        // Get all ValuePoint Ids, owned by this Catalog.
        Core::hresult Resources(RPC::IValueIterator*& iterator /* @out */) override {
			std::vector<uint32_t> ids;

            _adminLock.Lock();
            for(const auto& entry : _members) {
                ids.push_back(entry.first);
			}
            _adminLock.Unlock();

            // Create a new iterator, that will iterate over the Ids of the members.
           iterator = Core::ServiceType<RPC::ValueIterator>::Create<RPC::IValueIterator>(std::move(ids));

            return (Core::ERROR_NONE);
		}

        // -------------------------------------------------------------------------------------------------------
        // Administration methods
        // -------------------------------------------------------------------------------------------------------
        bool HasEntry(const uint32_t id) const {
            Core::SafeSyncType<Core::CriticalSection> lock(_adminLock);

            Members::const_iterator index(_members.find(id));

            return (index != _members.cend());
        }
        inline uint32_t Add(Exchange::IValuePoint* point) {
			uint32_t result = Core::ERROR_UNAVAILABLE;

            assert(point != nullptr);

            uint32_t id;

            if (point->Identifier(id) == Core::ERROR_NONE) {

				result = Core::ERROR_DUPLICATE_KEY;

                _adminLock.Lock();

                Members::iterator index(_members.find(id));

                ASSERT(index == _members.end());

                if (index == _members.end()) {
					point->AddRef();
                    _members.emplace(id, point);
                    point->Register(&_sink);
					result = Core::ERROR_NONE;
                }

                _adminLock.Unlock();
            }
            return (result);
        }
        inline uint32_t Remove(const Exchange::IValuePoint* point) {

            uint32_t result = Core::ERROR_UNAVAILABLE;

            assert(point != nullptr);

            uint32_t id;

            if (point->Identifier(id) == Core::ERROR_NONE) {

				result = Core::ERROR_NOT_EXIST;

                _adminLock.Lock();

                Members::iterator index(_members.find(id));

                ASSERT(index != _members.end());

                if (index != _members.end()) {
					index->second->Unregister(&_sink);
					index->second->Release();
                    _members.erase(index);
					result = Core::ERROR_NONE;
                }

                _adminLock.Unlock();
            }

            return (result);
        }
        inline bool IsEmpty() const {
            return (_members.empty());
        }
        template<typename ACTION>
        void Visit(ACTION&& action) const {
            _adminLock.Lock();
            for (const std::pair<uint32_t, IValuePoint*>& entry : _members) {
                action(entry.first, entry.second);
            }
            _adminLock.Unlock();
        }

        BEGIN_INTERFACE_MAP(Catalog)
            INTERFACE_ENTRY(Exchange::IValuePoint)
            INTERFACE_ENTRY(Exchange::IValuePoint::ICatalog)
        END_INTERFACE_MAP

    private:
        void Update(const uint32_t id) {

			_adminLock.Lock();

            // id is the id of the "contained" Value point, which in turn suggests
            // that we (catalog/bundle) have a changed value, so here we should report 
            // "our" id..
            for (auto& client :_clients) {
                client->Update(_id);
            }

            _adminLock.Unlock();
        }
        void Metadata(const uint32_t id) {
            _adminLock.Lock();

            for (auto& client : _clients) {
                client->Metadata(id);
            }

            _adminLock.Unlock();
        }

    private:
        mutable Core::CriticalSection _adminLock;
        const uint32_t _parent;
        const uint32_t _id;
        const string _manufacturer;
        const string _model;
		const IValuePoint::protocol _protocol;
        const uint32_t _type;
        Members _members;
        Notifiers _clients;
		CatalogObservers _observers;
        Core::SinkType<Sink> _sink;
    };
}

} // Namespace Exchange
