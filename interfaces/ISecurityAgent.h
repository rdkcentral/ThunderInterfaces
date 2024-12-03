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

// @stubgen:include <com/IIteratorType.h>

namespace Thunder {
namespace Exchange {
    /* @json 1.0.0 */
    struct EXTERNAL ISecurityAgent : virtual public Core::IUnknown {
        enum { ID = ID_SECURITYAGENT };
        // @brief Validate Token
        // @param Token to be validated
        // @param Given token status, i.e, it is valid or not
        virtual Core::hresult Validate(const string& token, bool& valid /* @out */) const = 0;
    };

namespace JSONRPC {
    /* @json 1.0.0 */
    struct EXTERNAL ISecurityToken {
        virtual ~ISecurityToken() = default;

        // @brief Creates Token
        // @param Size of buffer
        // @param Input buffer with data to create Token
        // @param Created token string
        virtual Core::hresult CreateToken(const uint16_t bufferLength, const uint8_t buffer[] /* @in */, string& token /* @out */) const = 0;
    };
}
}
}
