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

namespace Thunder {

namespace Exchange {

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IPerformance : virtual public Core::IUnknown {

        enum { ID = ID_PERFORMANCE };

        // @brief Test the process of sending the data
        // @param sendSize: Length of the sent data (e.g. 15)
        // @param buffer: Any data to be sent (e.g. HelloWorld)
        virtual Core::hresult Send(const uint16_t sendSize, const uint8_t buffer[] /* @encode:base64 @length:sendSize */) = 0;

        // @brief Test the process of receiving the data
        // @param bufferSize: Size of data to be provided (e.g. 10)
        // @param buffer: Data with a specified length (e.g. fhrjtus4p1)
        virtual Core::hresult Receive(uint16_t& bufferSize /* @inout */, uint8_t buffer[] /* @encode:base64 @length:bufferSize @maxlength:bufferSize @out */) const = 0;

        // @brief Test the process of both sending and receiving the data
        // @param bufferSize: Length of the data to be both sent as well as received (e.g. 20)
        // @param buffer: Data to be sent and then also received (e.g. kjrpq018rt)
        // @param maxBufferSize: Maximum size of the buffer that can be received (e.g. 100)
        virtual Core::hresult Exchange(uint16_t& bufferSize /* @inout */, uint8_t buffer[] /* @encode:base64 @length:bufferSize @maxlength:maxBufferSize @inout */, const uint16_t maxBufferSize) = 0;
    };

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IPerformanceStatistics : virtual public Core::IUnknown {

        enum { ID = ID_PERFORMANCE_STATISTICS };

        struct Statistics {
            uint32_t minimum /* @brief Minimum value of measurements (e.g. 1) */;
            uint32_t maximum /* @brief Maximum value of measurements (e.g. 4) */;
            uint32_t average /* @brief Average value of measurements (e.g. 2) */;
            uint32_t count /* @brief How many times measurement has been collected (e.g. 5) */;
        };

        struct Measurements {
            Statistics serialization /* @brief Time taken to complete serialization */;
            Statistics deserialization /* @brief Time taken to complete deserialization */;
            Statistics execution /* @brief Time taken to complete execution */;
            Statistics threadPool /* @brief Time taken to complete threadpool wait */;
            Statistics communication /* @brief Time taken to complete communication */;
            Statistics total /* @brief Time taken to complete whole JSON-RPC process */;
        };

        // @property
        // @brief Retrieve the performance measurement against a given package size. Measurements will be provided in milliseconds
        // @param index: Size of package which statistics info is about to be retrieved (e.g. 1000)
        // @param measurement: Various performance measurements against a given package size
        virtual Core::hresult Measurement(const uint32_t index /* @index */, Measurements& measurement /* @out */) const = 0;

        // @brief Clear all performance data collected so far
        // @alt:deprecated clear
        virtual Core::hresult Reset() = 0;
    };
}
}
