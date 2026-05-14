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

// @stubgen:include <com/IIteratorType.h>

namespace Thunder {
    namespace QualityAssurance {

    struct EXTERNAL IBenchmarkPayload : virtual public Core::IUnknown
    {
        enum { ID = ID_BENCHMARK_PAYLOAD };

        ~IBenchmarkPayload() override = default;

        struct SampleData
        {
            uint32_t id;
            uint32_t value;
            string name;
        };

        enum PayloadType : uint8_t
        {
            PAYLOAD_UNKNOWN,
            PAYLOAD_SMALL,
            PAYLOAD_MEDIUM,
            PAYLOAD_LARGE
        };

        typedef RPC::IIteratorType<PayloadType, ID_BENCHMARK_PAYLOADTYPE_ITERATOR> IPayloadTypeIterator;

        // @brief Retrieve supported payload types via an iterator (exercises COM-RPC iterator serialization)
        virtual Core::hresult GetPayloadTypes(IPayloadTypeIterator*& types /* @out */) const = 0;

        virtual Core::hresult SendUint16(const uint16_t value) = 0;

        virtual Core::hresult SendUint32(const uint32_t value) = 0;

        virtual Core::hresult SendUint64(const uint64_t value) = 0;

        virtual Core::hresult SendBool(const bool value) = 0;

        virtual Core::hresult SendFloat(const float value) = 0;

        virtual Core::hresult SendDouble(const double value) = 0;

        virtual Core::hresult SendString(const string& value) = 0;

        virtual Core::hresult SendSampleData(const SampleData& data) = 0;

        virtual Core::hresult SendNoPayload() = 0;

        virtual Core::hresult SendBuffer(const uint16_t bufferSize, const uint8_t buffer[] /* @length:bufferSize @in */) = 0;

        virtual Core::hresult SendReceiveUint16(const uint16_t input, uint16_t &output /* @out */) const = 0;

        virtual Core::hresult SendReceiveUint32(const uint32_t input, uint32_t &output /* @out */) const = 0;

        virtual Core::hresult SendReceiveUint64(const uint64_t input, uint64_t &output /* @out */) const = 0;

        virtual Core::hresult SendReceiveBool(const bool input, bool &output /* @out */) const = 0;

        virtual Core::hresult SendReceiveFloat(const float input, float &output /* @out */) const = 0;

        virtual Core::hresult SendReceiveDouble(const double input, double &output /* @out */) const = 0;

        virtual Core::hresult SendReceiveString(const string &input, string &output /* @out */) const = 0;

        virtual Core::hresult SendReceiveSampleData(const SampleData &input, SampleData &output /* @out */) const = 0;

        virtual Core::hresult SendReceiveBuffer(uint16_t &bufferSize /* @inout */, uint8_t buffer[] /* @length:bufferSize @inout */) const = 0;

        virtual Core::hresult Add(const uint32_t a, const uint32_t b, uint32_t &result /* @out */) const = 0;
    };
}
}
