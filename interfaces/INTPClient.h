/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Sky UK Limited
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
    struct EXTERNAL INTPClient : virtual public Core::IUnknown {
        enum { ID = ID_NTPCLIENT };

        enum NTPClientStatus: uint8_t {
            NTPCLIENT_DISABLED = 0,
            NTPCLIENT_UNSYNCHRONIZED,
            NTPCLIENT_SYNCHRONIZED,
            NTPCLIENT_ERROR
        };

        enum IPMode : uint8_t {
            Auto, // tries either ipv4 or ipv6 depending on router stack and endpoint availability
            IPv4Only, // only attempts ntp over IPv4
            IPv6Only // only attempts ntp over IPv6
        };
        
        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_NTPCLIENT_NOTIFICATION };

            // Time has been synchronised
            virtual void TimeSynchronised() = 0;
        };

        ~INTPClient() override = default;
        virtual uint32_t Register(INTPClient::INotification* sink) = 0;
        virtual uint32_t Unregister(INTPClient::INotification* sink) = 0;

        // @brief sysnchronise the time
        // @description sysnchronise the time by calling client utility(eg:chrony)
        // @param mode: synchronisation mode 
        virtual uint32_t SynchroniseTime(const string& server /* @in */, const IPMode& mode /* @in */) = 0;

        // @property
        // @brief status of synchronization
        // @description Get status whether time is synchronized or not
        // @param status: Enum value  
        virtual uint32_t GetStatus(NTPClientStatus &status /*@out*/ ) const = 0;

    };

} // namespace Exchange
} // namespace WPEFramework
