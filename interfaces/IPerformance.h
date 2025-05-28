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

    struct EXTERNAL IPerformance : virtual public Core::IUnknown {

        enum { ID = ID_PERFORMANCE };

        struct Statistics {
            uint32_t minimum /* @brief Minimum value of measurements (e.g. 1) */;
            uint32_t maximum /* @brief Maximum value of measurements (e.g. 4) */;
            uint32_t average /* @brief Average value of measurements (e.g. 2) */;
            uint32_t count /* How many times measurement has been collected (e.g. 5) */;
        };

        struct Measurement {
            Statistics serialization /* @brief Time taken to complete serialization */;
            Statistics deserialization /* @brief Time taken to complete deserialization */;
            Statistics execution /* @brief Time taken to complete execution */;
            Statistics threadPool /* Time taken to complete threadpool wait */;
            Statistics communication /* @brief Time taken to complete communication */;
            Statistics total /* @brief Time taken to complete whole jsonrpc process */;
        };

        // @property
        // @brief Retrieve the performance measurement against given package size. Measurements will be provided in milliseconds
        // @param index: Size of package whose statistics info has to be retrieved (e.g. 1000)
        // @param measurement: Various performance measurements against given package size
        virtual Core::hresult Measurement(const uint32_t index /* @index */, Measurement& measurement /* @out */) const = 0;

        // @brief Clear all performance data collected
        virtual Core::hresult Clear() = 0;

        // @brief Test the process of sending data
        // @param data: Any string data to be sent (e.g. HelloWorld)
        virtual Core::hresult Send(const uint16_t length, const uint8_t data[] /* @length:length */) = 0;

        // @brief Test the process of receiving data
        // @param datasize: Size of data to be provided by the jsonrpc interface (e.g. 10)
        // @param data: String data with a specified length to be received (e.g. fhrjtus4p1)
        virtual Core::hresult Receive(uint16_t& length /* @inout */, uint8_t data[] /* @maxlength:length @out */) const = 0;

        // @brief Test the process of both sending and receiving data
        // @param data: String data to be sent and then also received (e.g. kjrpq018rt)
        virtual Core::hresult Exchange(uint16_t& length /* @inout */, uint8_t data[] /* @length:length @maxlength:length @inout*/) = 0;
    };
}
}
