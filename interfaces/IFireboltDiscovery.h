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

// @insert <com/IIteratorType.h>

namespace WPEFramework {

namespace Exchange {


    struct EXTERNAL IFireboltDiscovery : virtual public Core::IUnknown {

        enum { ID = ID_FIREBOLT_DISCOVERY };
#if 1
        struct EXTERNAL DiscoveryPolicy{
            uint8_t enableRecommendation;
            uint8_t shareWatchHistory;
            uint8_t rememberWatchedProgram;
        };
#endif 
#if 1
        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_FIREBOLT_DISCOVERY_NOTIFICATION };
            ~INotification() override = default;

            // @brief Notifies that PolicyValue Changed
            /* @text:onPolicyChanged */
            virtual void OnPolicyChanged(const struct DiscoveryPolicy policy) = 0;
        };

            // Pushing notifications to interested sinks
            virtual Core::hresult Register(IFireboltDiscovery::INotification* sink) = 0;
            virtual Core::hresult Unregister(IFireboltDiscovery::INotification* sink) = 0;
#endif
        // @brief Provides Current Policy in action
        virtual Core::hresult GetDiscoveryPolicy(DiscoveryPolicy& policy /* @out */) = 0;

        virtual Core::hresult watched(const string& appId) = 0;
    };

    namespace JSONRPC {

        /* @json 1.0.0 */
        struct EXTERNAL IFireboltDiscoveryJSONRPC {

            virtual ~IFireboltDiscoveryJSONRPC() = default;


            /* @event */
            struct EXTERNAL INotification {

                virtual ~INotification() = default;

                // @brief Notifies change in the discovery policy
                virtual void PolicyChanged(const IFireboltDiscovery::DiscoveryPolicy policy) = 0;
            };
            // @text SignIn
            // @brief Signin the user in the app
            // @details AppID shall be passed through the security token.
            // @param signin: True - SignIn 
            // @retval ERROR_PRIVILIGED_REQUEST: App security errors
            virtual Core::hresult SignIn(const Core::JSONRPC::Context& context, const bool signin /*@optional*/) = 0;

            // @text Policy
            // @brief Signin the user in the app
            // @details Get the current Discovery Policy
            // @retval ERROR_PRIVILIGED_REQUEST: App security errors
            virtual Core::hresult Policy(const Core::JSONRPC::Context& context, IFireboltDiscovery::DiscoveryPolicy& policy /*@out*/) = 0; 

        };

    } // namespace JSONRPC

} // namespace Exchange

}
