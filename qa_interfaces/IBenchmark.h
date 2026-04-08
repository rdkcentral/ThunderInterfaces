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


        struct BenchmarkResult {
            string apiName;
            uint32_t iterations;

            RoundTripStats roundTrip;
            MemoryStats memory;

            bool passed;            // true if within configured thresholds
            string failureReason;   // empty if passed, describes which threshold was exceeded
        };

        typedef RPC::IIteratorType<BenchmarkResult, ID_BENCHMARK_RESULT_ITERATOR> IBenchmarkResultIterator;

        // @brief Run the benchmark
        // @param iterations: Denotes the number of iterations the benchmark should run
        // @param success: True if the benchmark completed successfully
        virtual Core::hresult Trigger(const uint32_t iterations, bool& success /* @out */) = 0;

        virtual Core::hresult CollectData(IBenchmarkResultIterator*& report /* @out */) const = 0;

        // @brief Set pass/fail thresholds for benchmark results
        // @param maxLatencyDeviationPct: Maximum allowed % deviation in avg latency compared to first-run baseline (0 = no latency check)
        // @param maxMemoryGrowthBytes: Maximum allowed RSS growth in bytes per method (0 = no memory check)
        // @param success: True if thresholds were set
        virtual Core::hresult SetThreshold(const float maxLatencyDeviationPct, const uint64_t maxMemoryGrowthBytes, bool& success /* @out */) = 0;

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