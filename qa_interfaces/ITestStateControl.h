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
namespace QualityAssurance {

    // @json 1.0.0
    struct EXTERNAL ITestStateControl : virtual public Core::IUnknown {

        enum { ID = ID_TESTSTATECONTROL };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_TESTSTATECONTROL_NOTIFICATION };

            ~INotification() override = default;

            // @brief Fires whenever the IStateControl state changes
            // @param state New state value ("resumed", "suspended", "uninitialized", "exited")
            virtual void StateChanged(const string& state) = 0;
        };

        ~ITestStateControl() override = default;

        virtual Core::hresult Register(INotification* notification) = 0;
        virtual Core::hresult Unregister(INotification* notification) = 0;

        // @property
        // @brief Current IStateControl state of the plugin
        virtual Core::hresult State(string& state /* @out */) const = 0;

        // @brief Request a state change
        // @param command State command: "resume" or "suspend"
        // @retval ERROR_INCORRECT_URL Unknown command string
        virtual Core::hresult Request(const string& command) = 0;
    };

} // namespace QualityAssurance
} // namespace Thunder
