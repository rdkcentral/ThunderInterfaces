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

    // @json 2.0.0
    struct EXTERNAL IBenchmark : virtual public Core::IUnknown {
        enum { ID = ID_BENCHMARK };

        ~IBenchmark() override = default;

        struct RoundTripStats {
            uint64_t minNs;
            uint64_t avgNs;
            uint64_t maxNs;
            uint64_t stddevNs;
        };

        struct MemoryStats {
            uint64_t residentBefore;  // RSS in bytes before benchmark
            uint64_t residentAfter;   // RSS in bytes after benchmark
            uint64_t allocatedBefore; // Allocated in bytes before benchmark
            uint64_t allocatedAfter;  // Allocated in bytes after benchmark
        };


        enum FailureReason : uint8_t {
            LATENCY_THRESHOLD_EXCEEDED,
            MEMORY_THRESHOLD_EXCEEDED,
            LATENCY_AND_MEMORY_THRESHOLD_EXCEEDED
        };

        struct BenchmarkResult {
            string apiName;
            uint32_t iterations;

            RoundTripStats roundTrip;
            MemoryStats memory;

            bool passed;
            Core::OptionalType<FailureReason> failureReason;
        };

        typedef RPC::IIteratorType<BenchmarkResult, ID_BENCHMARK_RESULT_ITERATOR> IBenchmarkResultIterator;

        // @brief Run the benchmark
        // @param iterations: Denotes the number of iterations the benchmark should run
        // @retval ERROR_NONE Benchmark completed and all thresholds passed
        // @retval ERROR_GENERAL Benchmark completed but one or more thresholds exceeded
        virtual Core::hresult Trigger(const uint32_t iterations) = 0;

        // @brief Collect the results of the most recent benchmark run
        // @param report: Iterator over the per-method benchmark results
        virtual Core::hresult CollectData(IBenchmarkResultIterator*& report /* @out */) const = 0;

        // @property
        // @brief Maximum allowed deviation in avg latency compared to first-run baseline, in millipercent (1000 = 1%, 0 = no latency check)
        virtual Core::hresult LatencyThreshold(const uint32_t maxLatencyDeviationPct) = 0;
        virtual Core::hresult LatencyThreshold(uint32_t& maxLatencyDeviationPct /* @out */) const = 0;

        // @property
        // @brief Maximum allowed RSS growth in bytes per method (0 = no memory check)
        virtual Core::hresult MemoryThreshold(const uint64_t maxMemoryGrowthBytes) = 0;
        virtual Core::hresult MemoryThreshold(uint64_t& maxMemoryGrowthBytes /* @out */) const = 0;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_BENCHMARK_NOTIFICATION };

            ~INotification() override = default;

            virtual void PerformanceCheckCompleted() = 0;
        };

        // @brief Set an explicit baseline from externally-supplied results, e.g. from a
        //        previous release run, so that the next trigger compares against it
        //        without requiring a warm-up run first.
        //        Setting LatencyThreshold() or MemoryThreshold() still clears this baseline.
        // @param baseline: Iterator over BenchmarkResult entries; apiName and
        //                  roundTrip.avgNs are used for latency comparison,
        //                  memory stats for memory threshold comparison.
        virtual Core::hresult SetBaseline(IBenchmarkResultIterator* baseline /* @in */) = 0;

        virtual Core::hresult Register(IBenchmark::INotification* sink) = 0;
        virtual Core::hresult Unregister(IBenchmark::INotification* sink) = 0;
    };

}
}
