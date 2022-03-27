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
    struct EXTERNAL INetworkTools : virtual public Core::IUnknown {
        enum { ID = ID_NETWORKTOOLS };

        /* @event */ 
        struct EXTERNAL ICallback : virtual public Core::IUnknown {
            enum { ID = ID_NETWORKTOOLS_CALLBACK };

            ~ICallback() override = default;

            // @brief Signals an message from a given host
            // @param source is the NodeId of the system that send the metadta presented in the next field.
            // @param metadata depending on the tool started, this JSON string will contain additiona information on this notification.
            virtual void Report (const string& source, const string& metadata) = 0;
        };

        ~INetworkTools() override = default;

        // @brief Ping the given destination with ICMP packages.
	// @param reportOn interface for receiving information back.
        // @param The node id of the host we would like to ping (ipv4/ipv6)
        // @param Time out, continue to ping for the given duration.
        // @param Count maximum number of pings to send.
        // @retval ERROR_NONE, ERROR_INPROGRES means an icmp check is already in progress .
        virtual uint32_t Ping(const string& destination, const uint16_t timeOutInSeconds, const uint16_t count) = 0;

        // @brief TraceRoute to the given destination with ICMP packages.
	// @param reportOn interface for receiving information back.
        // @param The node id of the host we would like to ping traceroute (ipv4/ipv6).
        // @param Time out, continue to trace for the given duration.
        // @retval ERROR_NONE, ERROR_INPROGRES means an icmp check is already in progress 
        virtual uint32_t TraceRoute(const string& destination, const uint16_t timeOutInSeconds) = 0;

        // @brief Callback allow you to set a listener for ICMP packages received. Setting a callback, if a callback
	// is already set, will fail. Setting a nullptr as the callback will abort any action in progress and thus allows
	// for setting a new callback or abort a ICMP check in progress.
        // @retval ERROR_NONE, ERROR_INPROGRES 
        virtual uint32_t Callback(ICallback* reportOn) = 0;
    };
}
}
