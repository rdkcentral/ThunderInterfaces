/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 Metrological
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


// Example interface!

#pragma once

#include "Module.h"

// @insert <core/Errors.h>

namespace WPEFramework {
namespace Exchange {

    // @json 1.0.0
    struct EXTERNAL ISimpleRichError : virtual public Core::IUnknown {

        enum { ID = ID_SIMPLERICHERROR };

        struct Diagnostic {
            enum failreason : uint8_t {
                HARDWARE_FAILURE,
                NO_WATER,
                NO_MILK,
                NO_BEANS,
                DRIP_TRAY_FULL,
                GROUNDS_CONTAINER_FULL
            };

            failreason reason;

            uint8_t water_temperature;
            uint8_t water_level;
            uint8_t brew_pressure;

            Core::OptionalType<string> info;
        };

        using Error = Core::ErrorDetails<Diagnostic>;

        enum coffeetype : uint8_t {
            ESPRESSO,
            CAPPUCCINO,
            LATTE,
            RISTRETTO
        };

        // @brief Restarts the coffee machine
        virtual Core::hresult Restart(Core::OptionalType<Core::ErrorDetails<void>>& errorDetails /* @out */) = 0;

        // @brief Makes a drink
        // @param type kind of drink to make
        // @param duration time it took to make the drink
        virtual Core::hresult MakeCoffee(const coffeetype& type, uint16_t& duration /* @out */, Core::OptionalType<Error>& errorDetails /* @out */) = 0;

    };

} // namespace Example
}
