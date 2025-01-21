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

    struct EXTERNAL IVoiceHandler;

    /*
     * Interface responsible for producing audio data
     * The data that is produced must be signed big endian
     */
    struct EXTERNAL IVoiceProducer : virtual public Core::IUnknown {
        enum { ID = ID_VOICEPRODUCER };

        struct EXTERNAL IProfile : virtual public Core::IUnknown {
            enum { ID = ID_VOICEPRODUCER_PROFILE };

            enum codec : uint8_t {
                UNDEFINED = 0,
                PCM /* @text:pcm */,
                ADPCM /* @text:adpcm */
            };

            virtual codec Codec() const = 0;
            virtual uint8_t Channels() const = 0;
            virtual uint32_t SampleRate() const = 0;
            virtual uint8_t Resolution() const = 0;
        };

        virtual string Name() const = 0;
        virtual uint32_t Callback(IVoiceHandler* callback) = 0;
        virtual uint32_t Error() const = 0;
        virtual string MetaData() const = 0;
        virtual void Configure(const string& settings) = 0;
    };

    struct EXTERNAL IVoiceHandler : virtual public Core::IUnknown {
        enum { ID = ID_VOICEHANDLER };

        virtual void Start(const IVoiceProducer::IProfile* profile) = 0;
        virtual void Stop() = 0;
        virtual void Data(const uint32_t sequenceNo, const uint8_t data[] /* @length:length */, const uint16_t length) = 0;
    };

    /* @json 1.0.0 @text:legacy_lowercase */
    struct EXTERNAL IAudioTransmitter : virtual public Core::IUnknown {

        enum { ID = ID_AUDIOTRANSMITTER };

        struct audioprofile {
            // Samples are always little endian signed integers
            IVoiceProducer::IProfile::codec codec /* @brief Compression method (pcm: uncompressed) */;
            uint8_t channels /* @brief Number of audio channels (e.g. 1) */;
            uint8_t resolution /* @brief Sample resultion in bits (e.g. 16) */;
            uint32_t sampleRate /* @brief Sample rate in hertz (e.g. 16000) */;
        };

        // @event
        struct ICallback: virtual public Core::IUnknown {

            enum { ID = ID_AUDIOTRANSMITTER_CALLBACK };

            enum transmissionstate : uint8_t {
                STOPPED,
                STARTED
            };

            // @statuslistener
            // @text audiotransmission
            // @brief Signals the beginning or the end of audio transmission
            // @param state New state of the audio transmission
            // @param profile Details of the format used in the audio transmission
            virtual void StateChanged(const transmissionstate state, const Core::OptionalType<audioprofile>& profile) = 0;

            // @text audioframe
            // @brief Provides audio frame data
            // @param seq Frame number in current transmission (e.g. 1)
            // @param length Size of the raw data frame in bytes (e.g. 400)
            // @param data Raw audio data
            virtual void Data(const uint16_t seq, const uint16_t length, const uint8_t data[] /* @length:length @encode:base64 */) = 0;
        };

        // Note: Installing a callback and registering for a JSON-RPC notification is mutually exclusive.
        virtual Core::hresult Callback(ICallback* const callback) = 0;

    };

} // Exchange
}
