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

namespace Thunder {
namespace Exchange {
    /* @json 1.0.0 */
    struct EXTERNAL IMonitor : virtual public Core::IUnknown {
        enum { ID = ID_MONITOR };
        struct Measurement {
            uint64_t min /* @brief Minimal value measured */;
            uint64_t max /* @brief Maximal value measured */;
            uint64_t average /* @brief Average of all measurements */;
            uint64_t last /* @brief Last measured value */;
        };
        struct Statistics {
            Measurement resident /* @brief Resident memory measurement */;
            Measurement allocated /* @brief Allocated memory measurement */;
            Measurement shared /* @brief Shared memory measurement */;
            Measurement process /* @brief Processes measurement */;
            bool operational /* @brief Whether the service is up and running */;
            uint32_t count /* @brief Number of measurements */;
        };
        struct RestartInfo {
            uint8_t limit /* @brief Maximum number or restarts to be attempted */;
            uint16_t window /* @brief Time period (in seconds) within which failures must happen for the limit to be considered crossed */;
        };

        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_MONITOR_NOTIFICATION };
            enum action : uint8_t {
                DEACTIVATE,
                ACTIVATE,
                RESTARTING_IS_STOPPED,
            };
            // @brief Signals an action taken by the Monitor
            // @param Callsign of the service the Monitor acted upon
            // @param The action executed by the Monitor on a service. One of: Activate, Deactivate, StoppedRestarting
            // @param A message describing the reason the action was taken
            virtual void Action(const string& callsign, const action value, const string& reason) = 0;
        };

        // Pushing notifications to interested sinks
        virtual Core::hresult Register(INotification* notification) = 0;
        virtual Core::hresult Unregister(INotification* notification) = 0;

        // @property
        // @brief Set/Get new restart limits for a plugin
        // @param Callsign of the plugin
        // @param Restart Information
        virtual Core::hresult RestartLimits(const string& callsign /* @index */, const RestartInfo& params) = 0;
        virtual Core::hresult RestartLimits(const string& callsign /* @index */, RestartInfo& params /* @out */) const = 0;

        // @brief Resets memory for a single plugin watched by the Monitor
        virtual Core::hresult Reset(const string& callsign) = 0;

        // @property
        // @brief List of plugins watched by the Monitor
        // @param List of plugins name monitoring by this plugin
        virtual Core::hresult Observables(IStringIterator*& observables /* @out */) const = 0;
        // @property
        // @brief The memory and process statistics either for a given plugin
        // @param Callsign of the plugin
        // @param Statistics for the requested plugin
        virtual Core::hresult StatisticsInfo(const string& callsign /* @index */, Statistics& statistics /* @out */) const = 0;
    };
}
}
