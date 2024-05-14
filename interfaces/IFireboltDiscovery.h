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

    struct EXTERNAL IFDiscovery : virtual public Core::IUnknown {

        enum { ID = ID_FIREBOLT_DISCOVERY };

        virtual Core::hresult watched(const string& appId) = 0;
    };

    namespace JSONRPC {

        /* @json 1.0.0 */
        struct EXTERNAL IFireboltDiscovery {

            virtual ~IFireboltDiscovery() = default;


            // @text SignIn
            // @brief Signin the user in the app
            // @details AppID shall be passed through the security token.
            // @param param: SignInParam
            // @retval ERROR_PRIVILIGED_REQUEST: App security errors
            virtual Core::hresult SignIn(const Core::JSONRPC::Context& context, const bool param ) = 0;

        };

    } // namespace JSONRPC

} // namespace Exchange

}
