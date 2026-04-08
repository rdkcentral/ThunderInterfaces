#pragma once
#include "Module.h"

// @stubgen:include <com/IIteratorType.h>

namespace Thunder {
    namespace QualityAssurance {


    struct SampleData
    {
        uint32_t id;
        uint32_t value;
        string name;
    };

    struct EXTERNAL IBenchmarkPayload : virtual public Core::IUnknown
    {
        enum { ID = ID_BENCHMARK_PAYLOAD };

        enum PayloadType : uint8_t
        {
            PAYLOAD_UNKNOWN,
            PAYLOAD_SMALL,
            PAYLOAD_MEDIUM,
            PAYLOAD_LARGE
        };

        typedef RPC::IIteratorType<PayloadType, ID_PAYLOADTYPE_ITERATOR> IPayloadTypeIterator;

        virtual uint32_t GetPayloadTypes(IPayloadTypeIterator*& types /* @out */) const = 0;

        virtual uint32_t SendUint16(const uint16_t value) = 0;

        virtual uint32_t SendUint32(const uint32_t value) = 0;

        virtual uint32_t SendUint64(const uint64_t value) = 0;

        virtual uint32_t SendBool(const bool value) = 0;

        virtual uint32_t SendFloat(const float value) = 0;

        virtual uint32_t SendDouble(const double value) = 0;

        virtual uint32_t SendString(const string& value) = 0;

        virtual uint32_t SendSampleData(const SampleData& data) = 0;

        virtual uint32_t SendWithNoParameters() = 0;

        virtual uint32_t SendBuffer(const uint16_t bufferSize, const uint8_t buffer[] /* @length:bufferSize @in */) = 0;

        virtual uint32_t SendReceiveUint16(const uint16_t input, uint16_t &output /* @out */) const = 0;

        virtual uint32_t SendReceiveUint32(const uint32_t input, uint32_t &output /* @out */) const = 0;

        virtual uint32_t SendReceiveUint64(const uint64_t input, uint64_t &output /* @out */) const = 0;

        virtual uint32_t SendReceiveBool(const bool input, bool &output /* @out */) const = 0;

        virtual uint32_t SendReceiveFloat(const float input, float &output /* @out */) const = 0;

        virtual uint32_t SendReceiveDouble(const double input, double &output /* @out */) const = 0;

        virtual uint32_t SendReceiveString(const string &input, string &output /* @out */) const = 0;

        virtual uint32_t SendReceiveSampleData(const SampleData &input, SampleData &output /* @out */) const = 0;

        virtual uint32_t SendReceiveBuffer(uint16_t &bufferSize /* @inout */, uint8_t buffer[] /* @length:bufferSize @inout */) const = 0;

        virtual uint32_t Add(const uint32_t a, const uint32_t b, uint32_t &result /* @out */) const = 0;

        ~IBenchmarkPayload() override = default;
    };
}
}