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

    struct EXTERNAL IRDKAdapter : virtual public Core::IUnknown {

        enum { ID = ID_RDKADAPTER };

        ~IRDKAdapter() override = default;

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_RDKADAPTER_NOTIFICATION };
            ~INotification() override = default;

            virtual void ConnectionUpdate(const bool connected) = 0;
        };

        virtual Core::hresult Register(IRDKAdapter::INotification* sink) = 0;
        virtual Core::hresult Unregister(IRDKAdapter::INotification* sink) = 0;

        virtual Core::hresult Connected(bool& connected /* @out */) const = 0;
        virtual Core::hresult PublicIP(string& ipaddress /* @out */) const = 0;
    };
}
}
