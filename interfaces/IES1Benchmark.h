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

#include <vector>

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    // @json
    struct EXTERNAL IES1Benchmark : virtual public Core::IUnknown {
        enum { ID = ID_ES1BENCHMARK };

        // using IUInt8Iterator = RPC::IIteratorType<uint8_t, ID_ES1BENCHMARK_UINT8ITERATOR>;

        ~IES1Benchmark() override = default;

        struct MixedElement {
            uint32_t id    /* @brief Element identifier */;
            string   name  /* @brief Element name */;
            double   value /* @brief Element floating-point value */;
            bool     flag  /* @brief Element boolean flag */;
        };

        // Nested structs for deep container traversal benchmark (4 levels)
        struct Level4Data {
            uint32_t value /* @brief Leaf integer value */;
            string   name  /* @brief Leaf string value */;
        };

        struct Level3Data {
            Level4Data inner /* @brief Level-4 nested object */;
            uint32_t   count /* @brief Level-3 integer */;
        };

        struct Level2Data {
            Level3Data nested /* @brief Level-3 nested object */;
            string     label  /* @brief Level-2 string */;
        };

        struct NestedObject {
            uint32_t   id    /* @brief Object identifier */;
            bool       flag  /* @brief Object boolean */;
            double     score /* @brief Object score */;
            Level2Data data  /* @brief Level-2 nested object */;
        };

        // @text echostring
        virtual uint32_t EchoString(const string& value /* @in */, string& echo /* @out */, uint64_t& ts2 /* @out */, uint64_t& ts3 /* @out */) = 0;

        // @text echoarray
        virtual uint32_t EchoArray(const std::vector<uint8_t>& values /* @in @restrict:0..256K */, std::vector<uint8_t>& echo /* @out @restrict:0..256K */, uint64_t& ts2 /* @out */, uint64_t& ts3 /* @out */) = 0;

        // @text echomixedarray
        virtual uint32_t EchoMixedArray(const std::vector<MixedElement>& elements /* @in @restrict:0..4228 */, std::vector<MixedElement>& echo /* @out @restrict:0..4228 */, uint64_t& ts2 /* @out */, uint64_t& ts3 /* @out */) = 0;

        // @text echonestedobjects
        virtual uint32_t EchoNestedObjects(const std::vector<NestedObject>& objects /* @in @restrict:0..1736 */, std::vector<NestedObject>& echo /* @out @restrict:0..1736 */, uint64_t& ts2 /* @out */, uint64_t& ts3 /* @out */) = 0;

        // @text echoint32
        virtual uint32_t EchoUint32(const uint32_t value /* @in */, uint32_t& echo /* @out */, uint64_t& ts2 /* @out */, uint64_t& ts3 /* @out */) = 0;

        // @text echoint64
        virtual uint32_t EchoUint64(const uint64_t value /* @in */, uint64_t& echo /* @out */, uint64_t& ts2 /* @out */, uint64_t& ts3 /* @out */) = 0;

        // @text echobool
        virtual uint32_t EchoBool(const bool value /* @in */, bool& echo /* @out */, uint64_t& ts2 /* @out */, uint64_t& ts3 /* @out */) = 0;

        // @text echofloat
        virtual uint32_t EchoFloat(const float value /* @in */, float& echo /* @out */, uint64_t& ts2 /* @out */, uint64_t& ts3 /* @out */) = 0;

        // @text echodouble
        virtual uint32_t EchoDouble(const double value /* @in */, double& echo /* @out */, uint64_t& ts2 /* @out */, uint64_t& ts3 /* @out */) = 0;
    };

} // namespace Exchange
} // namespace WPEFramework
