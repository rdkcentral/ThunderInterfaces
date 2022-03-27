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
#include "IValuePoint.h"


namespace WPEFramework {
namespace Exchange {

    // @stubgen:omit
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
            Timed(const Timed&) = delete;
            Timed& operator=(const Timed&) = delete;

            Timed(ValuePoint& parent)
                : _parent(parent)
                , _nextTime(0)
                , _periodicity(0)
            {
            }
            ~Timed() = default;

        public:
            // Return the periodicity in Seconds...
            inline uint32_t Period() const
            {
                return (_periodicity / 1000);
            }
            inline void Period(const uint32_t periodicity)
            {
                _parent.Lock();
                _periodicity = 0;
                _parent.Unlock();

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
                _parent.Evaluate();

                _parent.Lock();
                if (_periodicity != 0) {
                    _nextTime.Add(_periodicity);
                    _parent._timed.Reschedule(_nextTime);
                }
                _parent.Unlock();
            }

        private:
            ValuePoint& _parent;
            Core::Time _nextTime;
            uint32_t _periodicity;
        };

    public:
        ValuePoint() = delete;
        ValuePoint(const ValuePoint&) = delete;
        ValuePoint& operator=(const ValuePoint&) = delete;

PUSH_WARNING(DISABLE_WARNING_THIS_IN_MEMBER_INITIALIZER_LIST)
        ValuePoint(const uint32_t id, const uint32_t type)
            : _adminLock()
            , _id(id & 0x00FFFFFF)
            , _type(type)
            , _condition(IValuePoint::constructing)
            , _notify(notify::NONE)
            , _clients()
            , _job(*this)
            , _timed(*this)
        {
        }
POP_WARNING()
        inline ValuePoint(const uint32_t id, const basic base, const specific spec, const dimension dim, const uint8_t decimals)
            : ValuePoint(id, IValuePoint::Type(base, spec, dim, decimals))
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
            return (_id);
        }
        inline basic Basic() const
        {
            return (IValuePoint::Basic(_type));
        }
        inline dimension Dimension() const
        {
            return (IValuePoint::Dimension(_type));
        }
        inline specific Specific() const
        {
            return (IValuePoint::Specific(_type));
        }
        inline uint8_t Decimals() const
        {
            return (IValuePoint::Decimals(_type));
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

            std::list<IValuePoint::INotification*>::iterator index = std::find(_clients.begin(), _clients.end(), sink);

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

            std::list<IValuePoint::INotification*>::iterator index = std::find(_clients.begin(), _clients.end(), sink);

            if (index != _clients.end()) {
                sink->Release();
                _clients.erase(index);
            }

            _adminLock.Unlock();
        }

        uint32_t Identifier(uint32_t& ID /* @out */) const override {
            ID = _id;
            return (Core::ERROR_NONE);
        }

        uint32_t Bundle(uint32_t& ID /* @out */) const override {
            return (Core::ERROR_UNAVAILABLE);
        }

        uint32_t Condition(condition& value /* @out */) const  override {
            value = _condition;
            return (Core::ERROR_NONE);
        }

        uint32_t Type(uint32_t& value /* @out */) const  override {
            value = _type;
            return (Core::ERROR_NONE);
        }

        uint32_t Minimum(int32_t& value /* @out */) const  override {
            switch (Dimension()) {
            case logic:
            case percentage:
            case kwh:
            case kvah:
            case pulses: {
                value = 0;
                break;
            }
            case degrees: {
                value = -127;
                break;
            }
            case units: {
                value = Core::NumberType<int32_t>::Min();
                break;
            }
            }
 
            return (Core::ERROR_NONE);
        }

        uint32_t Maximum(int32_t& value /* @out */) const  override {
            switch (Dimension()) {
            case logic: {
                value = 1;
                break;
            }
            case percentage: {
                value = 100;
                break;
            }
            case kwh:
            case kvah:
            case pulses:
            case units: {
                value = Core::NumberType<int32_t>::Max();
                break;
            }
            case degrees: {
                value = +512;
                break;
            }
            }
 
            return (Core::ERROR_NONE);
        }
        virtual void Activate()
        {
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

        virtual void Evaluate() = 0;
        virtual uint32_t Value(int32_t& value) const = 0;
        virtual uint32_t Value(const int32_t value) = 0;

        BEGIN_INTERFACE_MAP(ValuePoint)
            INTERFACE_ENTRY(Exchange::IValuePoint)
        END_INTERFACE_MAP

    protected:
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
                std::list<IValuePoint::INotification*>::iterator index(_clients.begin());
                RecursiveCall(index, mode);
            }
        }
        void RecursiveCall(std::list<IValuePoint::INotification*>::iterator& position, uint8_t mode)
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
        mutable notify _notify;
        std::list<IValuePoint::INotification*> _clients;
        mutable Core::WorkerPool::JobType<Job> _job;
        Core::WorkerPool::JobType<Timed> _timed;
    };
}

} // Namespace Exchange
