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
namespace QualityAssurance {

    // @json 1.0.0
    struct EXTERNAL ITestPlugin : virtual public Core::IUnknown {
        enum { ID = ID_TESTPLUGIN };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_TESTPLUGIN_NOTIFICATION };
            ~INotification() override = default;

            virtual void OnGreeting(const string& message) = 0;
        };

        ~ITestPlugin() override = default;

        virtual Core::hresult Register(ITestPlugin::INotification* notification) = 0;
        virtual Core::hresult Unregister(ITestPlugin::INotification* notification) = 0;
        virtual Core::hresult Echo(const string& input, string& output /* @out */) = 0;
        virtual Core::hresult Greet(const string& name, string& message /* @out */) = 0;
    };

} // namespace QualityAssurance
} // namespace Thunder