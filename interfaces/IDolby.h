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

    namespace Dolby {

        // @json 1.0.0 @uncompliant:extended
        struct EXTERNAL IOutput : virtual public Core::IUnknown {

            enum { ID = ID_DOLBY_OUTPUT };

            ~IOutput() override = default;

            enum Type : uint8_t {
                DIGITAL_PCM = 0,
                DIGITAL_PLUS = 3,
                DIGITAL_AC3 = 4,
                AUTO = 5,
                DIGITAL_PASSTHROUGH = 6,
                MS12 = 7
            };

            enum SoundModes : uint8_t {
                UNKNOWN,
                MONO,
                STEREO,
                SURROUND,
                PASSTHRU,
                DOLBYDIGITAL,
                DOLBYDIGITALPLUS,
                SOUNDMODE_AUTO /* @text:Auto */
            };

            // @event @uncompliant:extended
            struct EXTERNAL INotification : virtual public Core::IUnknown {
                enum { ID = ID_DOLBY_OUTPUT_NOTIFICATION };

                ~INotification() override = default;
                // @brief Signal audio mode change
                // @text soundmodechanged @alt:deprecated dolby_audiomodechanged
                // @param mode: Changed Mode
                // @param enabled: Enabled/Disabled
                virtual void AudioModeChanged(const Dolby::IOutput::SoundModes mode, const bool enabled) = 0;
            };

            virtual uint32_t Register(INotification*) = 0;
            virtual uint32_t Unregister(INotification*) = 0;

            // @property
            // @text dolbyatmossupported @alt:deprecated dolby_atmosmetadata
            // @brief Atmos capabilities of Sink
            virtual uint32_t AtmosMetadata(bool& supported /* @out */) const = 0;

            // @property
            // @text: dolbysoundmode @alt:deprecated dolby_soundmode
            // @brief Sound Mode - Mono/Stereo/Surround
            virtual uint32_t SoundMode(Dolby::IOutput::SoundModes& mode /* @out */) const = 0;

            // @property
            // @text dolbyatmosoutput @alt:deprecated dolby_enableatmosoutput
            // @brief Enable Atmos Audio Output
            // @param enable: Enable/Disable
            virtual uint32_t EnableAtmosOutput(const bool enable /* @in */) = 0;

            // @property
            // @text:dolbymode @alt:deprecated dolby_mode
            // @brief Dolby Mode
            // @param mode: Dolby mode type
            virtual uint32_t Mode(const Dolby::IOutput::Type& mode) = 0;
            virtual uint32_t Mode(Dolby::IOutput::Type& mode /* @out */) const = 0;

        };
    }
}
}
