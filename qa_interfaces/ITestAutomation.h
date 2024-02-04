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
namespace QualityAssurance {

    // @json
    struct EXTERNAL IMemory : virtual public Core::IUnknown {
        // Ask Pierre if using namespace+interface as ID! Is there a coding guide line
        enum { ID = ID_TESTAUTOMATIONMEMORY };

        ~IMemory() override = default;
       
        // @method
        // @brief Allocates Memory as given size of MB
        // @retval ERROR_GENERAL Failed to allocate memory
        virtual Core::hresult AllocateMemory(const uint32_t size) = 0;


        // @method
        // @brief Frees the allocated memory
        // @retval ERROR_GENERAL Failed to free allocated memory
        virtual Core::hresult FreeAllocatedMemory() = 0;

    };


    // @json
    struct EXTERNAL IComRpc : virtual public Core::IUnknown {
        // Ask Pierre if using namespace+interface as ID! Is there a coding guide line
        enum { ID = ID_TESTAUTOMATIONCOMRPC };

        ~IComRpc() override = default;

        // @method
        // @brief Validates big string over proxy-stub with given length of KB
        // @retval ERROR_GENERAL Failed to verify
        virtual Core::hresult TestBigString(const uint32_t length) = 0;

        struct EXTERNAL IComRpcInternal : virtual public Core::IUnknown {
            enum { ID = ID_TESTAUTOMATIONCOMRPCINTERNAL };

            ~IComRpcInternal() override = default;

            virtual Core::hresult BigStringTest(const string& testString /* @restrict: (4M-1) */) = 0;
        };
    };

}
}