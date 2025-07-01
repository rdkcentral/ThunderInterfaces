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

// @insert <com/IIteratorType.h>

namespace Thunder {

namespace Exchange {

    // This interface gives direct access to a switchboard
    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL ISwitchBoard : virtual public Core::IUnknown {

        enum { ID = ID_SWITCHBOARD };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum { ID = ID_SWITCHBOARD_NOTIFICATION };

            // @brief Signal which callsign has been switched on
            // @param callsign: The callsign of the plugin that has been activated (e.g. WebKitBrowser)
            virtual void Activated(const string& callsign) = 0;
        };

        virtual Core::hresult Register(INotification* const notification) = 0;
        virtual Core::hresult Unregister(const INotification* const notification) = 0;

        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        // @property
        // @brief Get the list of switches available in the switchboard
        // @param switches: An iterator to the list of switches
        virtual Core::hresult Switches(IStringIterator*& switches /* @out */) const = 0;

        // @property
        // @brief Get a callsign of the default switch
        // @param callsign: The callsign of the default switch (e.g. WebKitBrowser)
        // @retval ERROR_UNAVAILABLE: No default switch available
        virtual Core::hresult Default(string& callsign /* @out */) const = 0;

        // @property
        // @brief Check if a plugin is active
        // @param callsign: The callsign of the plugin to check (e.g. DeviceInfo)
        // @param active: The state of the plugin, true if it is active, false if not (e.g. true)
        // @retval ERROR_UNKNOWN_KEY: Callsign not found
        virtual Core::hresult IsActive(const string& callsign /* @index */, bool& active /* @out */) const = 0;

        // @brief Activate a plugin by its callsign
        // @param callsign: The callsign of the plugin to activate (e.g. WebServer)
        // @retval ERROR_ILLEGAL_STATE: Not in a state to allow activation
        // @retval ERROR_INPROGRESS: Currently processing another request
        // @retval ERROR_UNAVAILABLE: The plugin is not available for activation
        virtual Core::hresult Activate(const string& callsign) = 0;

        // @brief Deactivate a plugin by its callsign
        // @param callsign: The callsign of the plugin to deactivate (e.g. MessageControl)
        // @retval ERROR_ILLEGAL_STATE: Not in a state to allow deactivation
        // @retval ERROR_INPROGRESS: Currently processing another request
        // @retval ERROR_UNAVAILABLE: The plugin is not available for deactivation
        virtual Core::hresult Deactivate(const string& callsign) = 0;
    };
}
}
