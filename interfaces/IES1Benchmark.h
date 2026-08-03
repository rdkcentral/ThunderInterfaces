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

namespace WPEFramework {
namespace Exchange {

    // @json
    struct EXTERNAL IES1Benchmark : virtual public Core::IUnknown {
        enum { ID = ID_ES1BENCHMARK };

        using IUInt32Iterator = RPC::IIteratorType<uint32_t, ID_ES1BENCHMARK_UINT32ITERATOR>;

        ~IES1Benchmark() override = default;

        // @text echostring
        virtual uint32_t EchoString(const string& value /* @in */, string& echo /* @out */) = 0;

        // @text echoarray
        virtual uint32_t EchoArray(IUInt32Iterator* const values /* @in */, IUInt32Iterator*& echo /* @out */) = 0;

        // @text echoint32
        virtual uint32_t EchoUint32(const uint32_t value /* @in */, uint32_t& echo /* @out */) = 0;

        // @text echoint64
        virtual uint32_t EchoUint64(const uint64_t value /* @in */, uint64_t& echo /* @out */) = 0;

        // @text echobool
        virtual uint32_t EchoBool(const bool value /* @in */, bool& echo /* @out */) = 0;

        // @text echofloat
        virtual uint32_t EchoFloat(const float value /* @in */, float& echo /* @out */) = 0;

        // @text echodouble
        virtual uint32_t EchoDouble(const double value /* @in */, double& echo /* @out */) = 0;
    };

} // namespace Exchange
} // namespace WPEFramework
