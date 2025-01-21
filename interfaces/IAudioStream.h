/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Metrological
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

    /* @json 1.0.0 @text:legacy_lowercase */
    struct EXTERNAL IAudioStream : virtual public Core::IUnknown {

        enum { ID = ID_AUDIOSTREAM };

        enum codectype : uint16_t {
            PCM = 1 /* @text:PCM */,
            IMA_ADPCM = 2 /* @text:IMA-ADPCM */,

            _  /* @end */,
            ADPCM = IMA_ADPCM
        };

        struct audioprofile {
            // Samples are always little endian signed integers

            codectype codec /* @brief Compression method (PCM: uncompressed) */;
            Core::OptionalType<string> codecParams /* @opaque @brief Additional parameters for codec */;
            uint8_t channels /* @brief Number of audio channels (e.g. 1) */;
            uint8_t resolution /* @brief Sample resultion in bits (e.g. 16) */;
            uint32_t sampleRate /* @brief Sample rate in hertz (e.g. 16000) */;
            Core::OptionalType<uint32_t> bitRate /* @brief Bit rate of the compressed stream (e.g. 8000) */;
        };

        enum streamstate : uint8_t {
            UNAVAILABLE,
            IDLE,
            STARTED
        };

        // @event
        struct INotification : virtual public Core::IUnknown {

            enum { ID = ID_AUDIOSTREAM_NOTIFICATION };

            // @statuslistener
            // @text audiotransmission
            // @brief Signals state of the audio stream
            // @param state New state of the audio stream
            // @param profile Details on the format used in the audio stream
            virtual void StateChanged(const streamstate state, const Core::OptionalType<audioprofile>& profile) = 0;
        };

        // @event
        struct ICallback : virtual public Core::IUnknown {

            enum { ID = ID_AUDIOSTREAM_CALLBACK };

            // @text audioframe
            // @brief Provides audio data
            // @param seq Frame number in current transmission (e.g. 1)
            // @param timestamp Timestamp of the frame
            // @param length Size of the raw data frame in bytes (e.g. 400)
            // @param data Raw audio data, the format of the data is specified in the most recent *audiotransmission* notification
            virtual void Data(const Core::OptionalType<uint16_t>& seq, const Core::OptionalType<uint32_t>& timestamp,
                const uint16_t length, const uint8_t data[] /* @length:length @encode:base64 */) = 0;
        };

        virtual Core::hresult Register(INotification* const notification) = 0;
        virtual Core::hresult Unregister(const INotification* const notification) = 0;

        // Note: Installing a callback and registering for a JSON-RPC "audioframe" notification is mutually exclusive.
        virtual Core::hresult Callback(ICallback* const callback) = 0;

        // @property
        // @brief Name of the audio stream
        // @retval ERROR_ILLEGAL_STATE The stream is not ready for this operation
        virtual Core::hresult Name(string& name /* @out */) const = 0;

        // @property
        // @brief Current state of the stream
        virtual Core::hresult State(streamstate& state /* @out */) const = 0;

        // @property
        // @brief List of codecs supported by the stream
        // @retval ERROR_ILLEGAL_STATE The stream is not ready for this operation
        virtual Core::hresult Capabilities(codectype& caps /* @out @encode:bitmask */) const = 0;

        // @property
        // @text audioprofile
        // @brief Preferred profile of the audio stream
        // @retval ERROR_NOT_SUPPORTED Profile change is not supported by this stream
        // @retval ERROR_ILLEGAL_STATE The stream is not ready for this operation
        // @retval ERROR_BAD_REQUEST The profile specified is invalid
        // @retval ERROR_INPROGRESS Transmission is ongoing, profile will be changed with next streaming
        virtual Core::hresult Profile(const audioprofile& profile) = 0;
        virtual Core::hresult Profile(audioprofile& profile /* @out */) const = 0;

        // @property
        // @brief Stream position
        // @description Current time in stream in milliseconds
        // @retval ERROR_NOT_SUPPORTED Time reporting is not supported by this stream
        // @retval ERROR_ILLEGAL_STATE The stream is not ready for this operation
        virtual Core::hresult Time(uint32_t& time /* @out */) const = 0;

        // @property
        // @brief Stream speed
        // @description Current stream speed in percent (0 - pause, 100 - play forward)
        // @retval ERROR_NOT_SUPPORTED Speed setting is not supported by this stream
        // @retval ERROR_ILLEGAL_STATE The stream is not ready for this operation
        virtual Core::hresult Speed(const uint8_t speed) = 0;
        virtual Core::hresult Speed(uint8_t& speed /* @out */) const = 0;
    };


} // namespace Thunder
}