/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 Metrological
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
    /* @json 1.0.0 */
    struct EXTERNAL ILocationSync : virtual public Core::IUnknown {
        enum { ID = ID_LOCATIONSYNC };

        struct Info {
	    string city /* @brief City name */;
            string country /* @brief Country name */;
            string region /* @brief Region name */;
            string timezone /* @brief Time zone information */;
            string publicip /* @brief Public IP */;
        };

	// @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_LOCATIONSYNC_NOTIFICATION };
            // @brief Signals a location change
            virtual void LocationChange() = 0;
        };
        // Pushing notifications to interested sinks
        virtual Core::hresult Register(INotification* notification) = 0;
        virtual Core::hresult Unregister(INotification* notification) = 0;

        // @property
        // @brief Get location information
        virtual Core::hresult Location(Info& value /* @out */) const = 0;

	// @brief Runs sync command
        virtual Core::hresult Sync() = 0;
    };
}
}
