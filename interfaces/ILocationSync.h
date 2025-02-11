/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 Metrological
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
    struct EXTERNAL ILocationSync : virtual public Core::IUnknown {

        enum { ID = ID_LOCATIONSYNC };

        struct LocationInfo {
            Core::OptionalType<string> city /* @brief City name (e.g. Wroclaw) */;
            Core::OptionalType<string> country /* @brief Country name (e.g. Poland) */;
            Core::OptionalType<string> region /* @brief Region name (e.g. Silesia) */;
            Core::OptionalType<string> timeZone /* @deprecated @brief Time zone information (e.g. CET-1CEST,M3.5.0,M10.5.0/3) */;
            Core::OptionalType<string> publicIP /* @deprecated @brief Public IP (e.g. 78.11.117.118) */;
        };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum { ID = ID_LOCATIONSYNC_NOTIFICATION };

            // @brief Signals a location change
            // @alt:deprecated locationchange
            virtual void Updated() = 0;
        };

        virtual Core::hresult Register(INotification* const notification) = 0;
        virtual Core::hresult Unregister(const INotification* const notification) = 0;

        // @brief Synchronize the location
        // @retval ERROR_GENERAL Failed to synchdonize the location
        // @retval ERROR_UNAVAILABLE Locator is not available 
        // @retval ERROR_INCORRECT_URL The URL is incorrect
        // @retval ERROR_INPROGRESS Probing is still in progress
        virtual Core::hresult Sync() = 0;

        // @property
        // @brief Get information about the location
        // @retval ERROR_UNAVAILABLE Either the internet or the location information is not available
        virtual Core::hresult Location(LocationInfo& info /* @out */) const = 0;

    };

} // namespace Exchange

}
