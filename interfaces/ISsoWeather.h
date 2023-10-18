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

namespace WPEFramework {
namespace Exchange {

    // @json
    struct EXTERNAL ISsoWeather : virtual public Core::IUnknown {
        enum { ID = ID_SSOWEATHER };
        
        // @event 
            struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_SSOWEATHER_NOTIFICATION };

            ~INotification() override = default;

            // @brief Signals temperature change
            // @param temperature New temperature in degrees Celsius.
            virtual void Temperature(const uint8_t temperature) = 0;

            // @brief Signals raining state change
            // @param raining New raining state (true: raining, false: sunny)
            virtual void IsRaining(const bool raining) = 0;
        };

        ~ISsoWeather() override = default;

        virtual void Register(ISsoWeather::INotification* sink) = 0;
        virtual void Unregister(const ISsoWeather::INotification* sink) = 0;

        // @property
        // @brief Check current temperature
        // @param temperature value in Celsius degrees
        // @retval ERROR_GENERAL Failed to retrieve current temperature
        virtual uint32_t Temperature(const uint8_t temperature) = 0;
        virtual uint32_t Temperature(uint8_t& temperature /* @out */) const = 0;

        // @property
        // @brief Check wether is already raining
        // @param raining state (true: raining, false: sunny)
        // @retval ERROR_GENERAL Failed to retrieve current temperature
        virtual uint32_t IsRaining(const bool raining) = 0;
        virtual uint32_t IsRaining(bool& raining /* @out */) const = 0;
    };
}
}
