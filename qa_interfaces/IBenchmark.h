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

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IBenchmark : virtual public Core::IUnknown {
        enum { ID = ID_BENCHMARK };

        ~IBenchmark() override = default;

        struct RoundTripStats {
            uint64_t minMs;
            uint64_t avgMs;
            uint64_t maxMs;
            uint64_t stddevMs;
        };

        
        struct BenchmarkResult {
            string apiName;
            uint32_t iterations;

            //uint32_t resultCount;
            //uint64_t results[4096];   

            RoundTripStats roundTrip;
        };

        typedef RPC::IIteratorType<BenchmarkResult, ID_BENCHMARK_RESULT_ITERATOR> IBenchmarkResultIterator;

        // @param iterations: Denotes the number of iterations the benchmark should run.
        virtual Core::hresult Trigger(const uint32_t iterations) = 0;

        virtual Core::hresult CollectData(IBenchmarkResultIterator*& report /* @out */) const = 0;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_BENCHMARK_NOTIFICATION };

            ~INotification() override = default;

            virtual void PerformanceCheckCompleted() = 0;
        };

        virtual Core::hresult Register(const IBenchmark::INotification* sink) = 0;
        virtual Core::hresult Unregister(const IBenchmark::INotification* sink) = 0;
    };

}
}