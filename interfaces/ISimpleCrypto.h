/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 Metrological
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

    struct EXTERNAL ISimpleCrypto : virtual public Core::IUnknown {

        enum { ID = ID_SIMPLECRYPTO };

        struct EXTERNAL ICipher : virtual public Core::IUnknown {

            enum { ID = ID_SIMPLECRYPTO_CIPHER };

            virtual uint32_t Encrypt(const uint32_t length, const uint8_t input[] /* @in @length:length */,
                                     const uint32_t maxOutputLength, uint8_t output[] /* @out @maxlength:maxOutputLength */) const = 0;

            virtual uint32_t Decrypt(const uint32_t length, const uint8_t input[] /* @in @length:length */,
                                     const uint32_t maxOutputLength, uint8_t output[] /* @out @maxlength:maxOutputLength */) const = 0;

        };

        virtual ICipher* Cipher(const string& keyName) = 0;
    };

}

}
