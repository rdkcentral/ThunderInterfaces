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

namespace Thunder {

namespace Exchange {

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IPower : virtual public Core::IUnknown {

        enum { ID = ID_POWER };

        // @text:keep
        enum PCState : uint8_t {
            On = 1, // S0.
            ActiveStandby = 2, // S1.
            PassiveStandby = 3, // S2.
            SuspendToRAM = 4, // S3.
            Hibernate = 5, // S4.
            PowerOff = 6, // S5.
        };

        enum PCPhase : uint8_t {
            Before = 1,
            After  = 2
        };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum { ID = ID_POWER_NOTIFICATION };

            // @brief Signals a change in the power state
            // @param origin: The state the device is transitioning from (e.g. ActiveStandby)
            // @param destination: The state the device is transitioning to (e.g. SuspendToRAM)
            // @param phase: The phase of the transition (e.g. After)
            virtual Core::hresult StateChange(const PCState origin, const PCState destination, const PCPhase phase) = 0;
        };

        virtual Core::hresult Register(INotification* const sink) = 0;
        virtual Core::hresult Unregister(const INotification* const sink) = 0;

        // @property
        // @brief Get the current power state
        // @param state: The current power state (e.g. PassiveStandby)
        virtual Core::hresult GetState(PCState& state /* @out */) const = 0;

        // @brief Set the power state
        // @param state: The power state to set (e.g. Hibernate)
        // @param waitTime: The time to wait for the power state to be set in seconds (e.g. 10)
        // @retval ERROR_GENERAL: General failure
        // @retval ERROR_DUPLICATE_KEY: Trying to set the same power mode
        // @retval ERROR_ILLEGAL_STATE: Power state is not supported
        // @retval ERROR_BAD_REQUEST: Invalid Power state or Bad JSON param data format
        virtual Core::hresult SetState(const PCState& state, const uint32_t waitTime) = 0;

        // @json:omit
        virtual void PowerKey() = 0;
    };

} // namespace Exchange

}

