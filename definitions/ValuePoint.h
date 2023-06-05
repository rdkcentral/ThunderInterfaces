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

namespace WPEFramework {
namespace Exchange {

    class ValuePoint : public IValuePoint {
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
        ValuePoint(const uint32_t id, const uint32_t type, const int32_t min = 0, const int32_t max = 0)
            : _adminLock()
            , _id(id & 0x00FFFFFF)
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
        inline ValuePoint(const uint32_t id, const basic base, const specific spec, const dimension dim, const uint8_t decimals, const int32_t min = 0, const int32_t max = 0)
            : ValuePoint(id, IValuePoint::Type(base, spec, dim, decimals), min, max)
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
        void Register(IValuePoint::INotification* sink) override
        {
            _adminLock.Lock();

            Notifiers::iterator index = std::find(_clients.begin(), _clients.end(), sink);

            if (index == _clients.end()) {
                sink->AddRef();
                _clients.push_back(sink);
                sink->Update(_id);
            }

            _adminLock.Unlock();
        }
        void Unregister(IValuePoint::INotification* sink) override
        {
            _adminLock.Lock();

            Notifiers::iterator index = std::find(_clients.begin(), _clients.end(), sink);

            if (index != _clients.end()) {
                sink->Release();
                _clients.erase(index);
            }

            _adminLock.Unlock();
        }

        uint32_t Identifier(uint32_t& ID /* @out */) const override {
            ID = Identifier();
            return (Core::ERROR_NONE);
        }

        uint32_t Bundle(uint32_t& ID /* @out */) const override {
            return (Core::ERROR_UNAVAILABLE);
        }

        uint32_t Condition(condition& value /* @out */) const  override {
            value = Condition();;
            return (Core::ERROR_NONE);
        }

        uint32_t Type(uint32_t& value /* @out */) const  override {
            value = _type;
            return (Core::ERROR_NONE);
        }

        uint32_t Minimum(int32_t& value /* @out */) const  override {
            value = Minimum();
            return (Core::ERROR_NONE);
        }

        uint32_t Metadata(string& value /* @out */) const override
        {
            value = _metadata;
            return (Core::ERROR_NONE);
        }

        uint32_t Value(int32_t& value) const override {
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

        uint32_t Value(const int32_t value) override {

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

        uint32_t Maximum(int32_t& value /* @out */) const  override {
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
        inline void ChangeTypeId(const uint32_t id, const uint32_t type)
        {
            _id = (id & 0x00FFFFFF);
            _type = type;
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
        uint32_t _id;
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
}

} // Namespace Exchange
