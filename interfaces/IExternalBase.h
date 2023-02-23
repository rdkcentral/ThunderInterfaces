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
#include "IExternal.h"

namespace WPEFramework {
namespace Exchange {

    // @stubgen:omit
    class ExternalBase : public IExternal {
    private:
        class Job { 
        public: 
            Job() = delete;
            Job(const Job&) = delete;
            Job& operator=(const Job&) = delete;

            Job(ExternalBase& parent)
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
            ExternalBase& _parent;
        };
        class Timed {
        public:
            Timed() = delete;
            Timed(const Timed&) = delete;
            Timed& operator=(const Timed&) = delete;

            Timed(ExternalBase& parent)
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
            ExternalBase& _parent;
            Core::Time _nextTime;
            uint32_t _periodicity;
        };

    public:
        ExternalBase() = delete;
        ExternalBase(const ExternalBase&) = delete;
        ExternalBase& operator=(const ExternalBase&) = delete;

PUSH_WARNING(DISABLE_WARNING_THIS_IN_MEMBER_INITIALIZER_LIST)
        ExternalBase(const uint32_t id, const uint32_t type)
            : _adminLock()
            , _id(id & 0x00FFFFFF)
            , _type(type)
            , _condition(IExternal::condition::constructing)
            , _clients()
            , _job(*this)
            , _timed(*this)
        {
        }
POP_WARNING()
        inline ExternalBase(const uint32_t id, const basic base, const specific spec, const dimension dim, const uint8_t decimals)
            : ExternalBase(id, IExternal::Type(base, spec, dim, decimals))
        {
        }
        ~ExternalBase() override {
            ASSERT(_clients.size() == 0);
            ASSERT(_condition == IExternal::condition::deactivated);
            _job.Revoke();
    	}

    public:
        // ------------------------------------------------------------------------
        // Convenience methods to extract interesting information from the type
        // ------------------------------------------------------------------------
        inline basic Basic() const
        {
            return (IExternal::Basic(_type));
        }
        inline dimension Dimension() const
        {
            return (IExternal::Dimension(_type));
        }
        inline specific Specific() const
        {
            return (IExternal::Specific(_type));
        }
        inline uint8_t Decimals() const
        {
            return (IExternal::Decimals(_type));
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
        // IExternal default interface implementation
        // ------------------------------------------------------------------------
        // Pushing notifications to interested sinks
        void Register(IExternal::INotification* sink) override
        {
            _adminLock.Lock();

            std::list<IExternal::INotification*>::iterator index = std::find(_clients.begin(), _clients.end(), sink);

            if (index == _clients.end()) {
                sink->AddRef();
                _clients.push_back(sink);
                sink->Update(_id);
            }

            _adminLock.Unlock();
        }
        void Unregister(IExternal::INotification* sink) override
        {

            _adminLock.Lock();

            std::list<IExternal::INotification*>::iterator index = std::find(_clients.begin(), _clients.end(), sink);

            if (index != _clients.end()) {
                sink->Release();
                _clients.erase(index);
            }

            _adminLock.Unlock();
        }

        condition Condition() const override
        {
            return (_condition);
        }

        // Identification of this element.
        uint32_t Identifier() const override
        {
            return (_id);
        }

        // Characteristics of this element
        uint32_t Type() const override
        {
            return (_type);
        }

        int32_t Minimum() const override
        {
            int32_t result = 0;

            switch (Dimension()) {
            case dimension::logic:
            case dimension::percentage:
            case dimension::kwh:
            case dimension::kvah:
            case dimension::pulses: {
                break;
            }
            case dimension::degrees: {
                result = -127;
                break;
            }
            case dimension::units: {
                result = Core::NumberType<int32_t>::Min();
                break;
            }
            }
            return (result);
        }
        int32_t Maximum() const override
        {
            int32_t result = 1;
            switch (Dimension()) {
            case dimension::logic: {
                break;
            }
            case dimension::percentage: {
                result = 100;
                break;
            }
            case dimension::kwh:
            case dimension::kvah:
            case dimension::pulses:
            case dimension::units: {
                result = Core::NumberType<int32_t>::Max();
                break;
            }
            case dimension::degrees: {
                result = +512;
                break;
            }
            }
            return (result);
        }
        virtual void Activate()
        {
            _adminLock.Lock();

            if ((_condition == IExternal::condition::deactivated) || (_condition == IExternal::condition::constructing)) {
                _condition = IExternal::condition::activated;

                if (_clients.size() > 0) {
                    _job.Submit();
                }
            }

            _adminLock.Unlock();
        }
        virtual void Deactivate() {
            _adminLock.Lock();

            if ( (_condition == IExternal::condition::activated) || (_condition == IExternal::condition::constructing) ) {

                static_cast<Timed&>(_timed).Period(0);
                _condition = IExternal::condition::deactivated;

                if (_clients.size() > 0) {
                    _job.Submit();
                }
            }

            _adminLock.Unlock();
        }

        virtual void Evaluate() = 0;
        virtual uint32_t Get(int32_t& value) const = 0;
        virtual uint32_t Set(const int32_t value) = 0;

        BEGIN_INTERFACE_MAP(ExternalBase)
            INTERFACE_ENTRY(Exchange::IExternal)
        END_INTERFACE_MAP

    protected:
        inline void Updated() const
        {
            _job.Submit();
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
            std::list<IExternal::INotification*>::iterator index(_clients.begin());
            RecursiveCall(index);
        }
        void RecursiveCall(std::list<IExternal::INotification*>::iterator& position)
        {
            if (position == _clients.end()) {
                _adminLock.Unlock();
            } else {
                IExternal::INotification* client(*position);
                client->AddRef();
                position++;
                RecursiveCall(position);
                client->Update(_id);
                client->Release();
            }
        }

    private:
        mutable Core::CriticalSection _adminLock;
        uint32_t _id;
        uint32_t _type;
        condition _condition;
        std::list<IExternal::INotification*> _clients;
        mutable Core::WorkerPool::JobType<Job> _job;
        Core::WorkerPool::JobType<Timed> _timed;
    };
}

} // Namespace Exchange
