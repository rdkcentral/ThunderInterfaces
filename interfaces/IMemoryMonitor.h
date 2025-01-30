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

// @insert <com/IIteratorType.h>

namespace Thunder {

namespace Exchange {

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IMemoryMonitor : virtual public Core::IUnknown {

        enum { ID = ID_MEMORY_MONITOR };

        struct Restart {
            uint8_t limit /* @brief Maximum number or restarts to be attempted (e.g. 3) */;
            uint16_t window /* @brief Time period (in seconds) within which failures must happen for the limit to be considered crossed (e.g. 60) */;
        };

        struct Measurement {
            uint64_t min /* @brief Minimal value measured (e.g. 0) */;
            uint64_t max /* @brief Maximal value measured (e.g. 100) */;
            uint64_t average /* @brief Average of all measurements (e.g. 50) */;
            uint64_t last /* @brief Last measured value (e.g. 100) */;
        };

        struct Statistics {
            Measurement resident /* @brief Resident memory measurement */;
            Measurement allocated /* @brief Allocated memory measurement */;
            Measurement shared /* @brief Shared memory measurement */;
            Measurement process /* @brief Processes measurement */;
            bool operational /* @brief Whether the service is up and running (e.g. true) */;
            uint32_t count /* @brief Number of measurements (e.g. 100) */;
        };
        
        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum { ID = ID_MEMORY_MONITOR_NOTIFICATION };

            enum action : uint8_t {
                DEACTIVATED,
                ACTIVATED,
                RESTARTING_STOPPED
            };

            enum reason : uint8_t {
                EXCEEDED_MEMORY,
                NOT_OPERATIONAL
            };

            // @brief Signals an action taken by the Monitor
            // @param Callsign of the service the Monitor acted upon (e.g. WebServer)
            // @param Ation executed by the Monitor on a service (e.g. Deactivate)
            // @param Mssage describing the reason the action was taken (e.g. EXCEEDED_MEMORY)
            virtual void StatusChanged(const string& callsign, const action action, const Core::OptionalType<reason>& reason) = 0;
        };

        virtual Core::hresult Register(INotification* const notification) = 0;
        virtual Core::hresult Unregister(const INotification* const notification) = 0;

        // @property
        // @brief Limits of restarting of a service
        // @param Callsign of the service (e.g. WebServer)
        // @param Limits of restarts applying to a given service
        virtual Core::hresult RestartingLimits(const string& callsign /* @index */, const Restart& restart) = 0;
        virtual Core::hresult RestartingLimits(const string& callsign /* @index */, Restart& restart /* @out */) const = 0;

        // @property
        // @brief List of services watched by the Monitor
        // @param List of monitored services
        virtual Core::hresult Observables(IStringIterator*& observables /* @out */) const = 0;

        // @property
        // @brief Memory statistics for a given service
        // @param Callsign of the service (e.g. WebServer)
        // @param Statistics for the requested callsign
        virtual Core::hresult MeasurementData(const string& callsign /* @index */, Statistics& statistics /* @out */) const = 0;

        // @brief Resets memory statistics for a given service
        // @param Callsign of the service (e.g. WebServer)
        virtual Core::hresult ResetStatistics(const string& callsign) = 0;
    };

} // namespace Exchange

}