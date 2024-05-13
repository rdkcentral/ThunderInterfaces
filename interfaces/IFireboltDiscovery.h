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

        virtual Core::hresult watched(const string& appId) = 0;
    };

    namespace JSONRPC {

        /* @json 1.0.0 */
        struct EXTERNAL IFireboltDiscovery {

            virtual ~IFireboltDiscovery() = default;


            // @event
            struct EXTERNAL INotification {

                virtual ~INotification() = default;

                // @text onNavigateTo
                // @brief Notifies that permision for resume points value has been changed
                // @param appId: ID of the applocation for which this notification relates to
                // @param allow: Allow or deny use of resume points
                virtual void OnNavigateTo(const string& appId /* @index */, const bool allow) = 0;

                // @text onPolicyChanged
                // @brief Notifies that a resume point has been added, updated or removed
                // @param appId: ID of the application for which this notification relates to
                virtual void OnPolicyChanged(const string& appId /* @index */) = 0;
            };
            virtual Core::hresult Register(IFireboltDiscovery::INotification* sink) = 0;
            virtual Core::hresult UnRegister(IFireboltDiscovery::INotification* sink) = 0;

            // @text PermitResumePoints
            // @brief Sets resume point permission
            // @details AppID shall be passed through the security token.
            // @param allow: Allow or deny use of resume points
            // @retval ERROR_PRIVILIGED_REQUEST: App security errors
            virtual Core::hresult PermitResumePoints(const Core::JSONRPC::Context& context, const Core::OptionalType<bool> param ) = 0;

        };

    } // namespace JSONRPC

} // namespace Exchange

}
