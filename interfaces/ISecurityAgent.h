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

namespace Exchange {

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL ISecurityAgent : virtual public Core::IUnknown {

        enum { ID = ID_SECURITYAGENT };

        // @brief Validates a token
        // @description Checks whether the token is valid and properly signed
        // @param token Token that will be validated (e.g. eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9)
        // @param valid Tells whether token's signature is correct
        virtual Core::hresult Validate(const string& token, bool& valid /* @out */) const = 0;

    };

} // namespace Exchange
}
