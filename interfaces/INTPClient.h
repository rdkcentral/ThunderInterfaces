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
    struct EXTERNAL INTPClient : virtual public Core::IUnknown {
        enum { ID = ID_NTPCLIENT };
        
        enum NTPClientStatus: uint8_t {
            NTPCLIENT_DISABLED = 0,
            NTPCLIENT_UNSYNCHRONIZED,
            NTPCLIENT_SYNCHRONIZED,
            NTPCLIENT_ERROR
        };

        enum NTPClientTransmissionMode: uint8_t {
            NTPCLIENT_MODE_UNICAST = 0,
            NTPCLIENT_MODE_BROADCAST,
            NTPCLIENT_MODE_MULTICAST,
            NTPCLIENT_MODE_MANYCAST
        };

        enum NTPClientSyncMode: uint8_t {
            NTPCLIENT_MODE_QUICK_SYNC = 0,
            NTPCLIENT_MODE_NORMAL = 1,
        };
        
        struct NTPClientConfiguration {
            NTPClientTransmissionMode mode; // Unicast / Broadcast / Multicast / Manycast
            uint32_t port; // the port used to send NTP packets
            uint32_t version; 
            //Comma-separated list of strings. Points to a CSV list of NTP servers or pools. 
            //A NTP server can either be specified as an IP address or a host name. 
            //It is expected that the NTP client resolves multiple addresses which can change over time when ResolveAddresses is enabled.
            string servers;
            // When this option is enabled the NTP client must resolve the multiple addresses 
            //associated with the host name(s) that are specified in the Servers field.
            bool resolveAddresses;
            // When ResolveAddresses is enabled, This parameter specifies the maximum number of IP addresses 
            // that the NTP client can resolve. 0 means that all addresses must be resolved.
            uint32_t resolveMaxAddresses;
            // Use symmetric active association mode. This device may provide synchronization to the configured NTP server.
            bool peer;
            //	This is the minimum polling interval, in seconds to the power of two, 
            //  allowed by any peer of the Internet system, currently set to 6 (64 seconds).
            uint32_t minPoll;
            // This is the maximum polling interval, in seconds to the power of two, 
            // allowed by any peer of the Internet system, currently set to 10 (1024 seconds)
            uint32_t maxPoll;
            // If the IBurst parameter is enabled, and this is the first packet sent when 
            // the server has been unreachable, the client sends a burst. This is useful to 
            // quickly reduce the synchronization distance below the distance threshold and synchronize the clock. 
            bool iBurst;
            // If the Burst parameter is enabled and the server is reachable and 
            // a valid source of synchronization is available, the client sends a 
            // burst of BCOUNT (8) packets at each poll interval. The interval between packets 
            // in the burst is two seconds. This is useful to accurately measure jitter with long poll intervals. [RFC5905].
            uint32_t burst;
            // The IP Interface associated with the Client entry.
            string interface;
            // Specifies how the client sockets are bound.
            // Address (The client sockets are bound to a local IP address)
            // Device (The client sockets are bound to a network device. This can be useful when the local address is dynamic)
            string bindType;
        };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_NTPCLIENT_NOTIFICATION };

            // Some change happened with respect to the Network..
            virtual void Completed() = 0;
        };

        ~INTPClient() override = default;
        virtual uint32_t Register(INTPClient::INotification* sink) = 0;
        virtual uint32_t Unregister(INTPClient::INotification* sink) = 0;

        // @property
        // @brief sysnchronize the time
        // @description sysnchronize the time by calling client utility(eg:chrony)
        // @param mode: synchronisation mode 
        virtual uint32_t SynchroniseTime(const NTPClientSyncMode& mode /* @in */) = 0;

        // @property
        // @brief status of synchronization
        // @description Get status whether time is synchronized or not
        // @param status: Enum value  
        virtual uint32_t GetStatus(NTPClientStatus &status /*@out*/ ) const = 0;

        // @property
        // @brief Current synchronized system time 
        // @description Get Current synchronized system time in ISO8601 format (e.g. 2019-05-07T07:20:26Z)
        // @param time: System time in ISO8601 format 
        virtual uint32_t GetSyncTime(string& time /* @out */) const = 0;

        // @property
        // @brief Set configuration
        // @description Set configuration in config file for the client utility(eg: chrony.conf)
        // @param config: configuration structure 
        virtual uint32_t SetConfiguration(const NTPClientConfiguration& config /* @in */) = 0;
    };

} // namespace Exchange
} // namespace WPEFramework
