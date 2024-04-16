/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 Metrological
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

    namespace IBluetoothAudio {

        enum audiocodec : uint8_t {
            LC_SBC = 1  /* @text LC-SBC */
        };

        enum drmscheme : uint8_t {
            DTCP   = 1  /* @text DTCP */,
            SCMS_T = 2  /* @text SCMS-T */
        };

        enum state : uint8_t {
            UNASSIGNED,             // No audio device identified or assigned
            DISCONNECTED,           // No audio device connected
            CONNECTING,             // Audio device is now connecting
            CONNECTED,              // Audio device connected
            CONNECTED_BAD,          // Audio device connected but of invalid or unsupported capabilities
            CONNECTED_RESTRICTED,   // Audio device connected but copy protection criteria have not been met
            READY,                  // Streaming session is now open, source is paused, but can resume at any time
            STREAMING               // Audio data is currently being streamed
        };

        struct CodecProperties {
            audiocodec Codec                /* @brief Audio codec used */;
            string /* @opaque */ Settings   /* @brief Codec-specific audio quality preset, compression profile, etc */;
        };

        struct DRMProperties {
            drmscheme DRM                   /* @brief Content protection scheme used */;
            string /* @opaque */ Settings   /* @brief DRM-specific content protection level, encoding rules, etc */;
        };

        struct StreamProperties {
            uint32_t SampleRate     /* @brief Sample rate in Hz (e.g. 44100) */;
            uint32_t BitRate        /* @brief Target bitrate in bits per second (eg. 320000) */;
            uint8_t Channels        /* @brief Number of audio channels (e.g. 2) */;
            uint8_t Resolution      /* @brief Sampling resolution in bits per sample (e.g. 16) */;
            bool IsResampled        /* @brief Indicates if the source stream is being resampled by the stack to match sink capabilities */;
        };

        struct EXTERNAL IStream : virtual public Core::IUnknown {

            // This interface is never exposed over JSON-RPC.

            enum { ID = ID_BLUETOOTHAUDIO_STREAM };

            struct Format {
                uint32_t SampleRate;    // e.g. 44100 Hz for CD audio
                uint16_t FrameRate;     // e.g. 75 Hz for CD audio
                uint8_t Resolution;     // e.g. 16 bits for CD audio
                uint8_t Channels;       // e.g. 2 channels for CD audio
            };

            virtual Core::hresult Configure(const Format& pcmStreamFormat) = 0;
            virtual Core::hresult Acquire(const string& connector) = 0;
            virtual Core::hresult Relinquish() = 0;
            virtual Core::hresult Speed(const int8_t speedPercent) = 0;
            virtual Core::hresult Time(uint32_t& timeMs /* @out */) const = 0;
            virtual Core::hresult Delay(uint32_t& delayMs /* @out */) const = 0;
        };

        // @json 1.0.0
        // @prefix sink
        struct EXTERNAL ISink : virtual public Core::IUnknown {

            enum { ID = ID_BLUETOOTHAUDIO_SINK };

            struct EXTERNAL IControl : virtual public Core::IUnknown {

                // This interface is not exposed via JSON-RPC.

                enum { ID = ID_BLUETOOTHAUDIO_SINK_CONTROL };

                // Used to register a source object that will recieve IStream
                // callbacks when the sink device issues control commands.
                virtual Core::hresult Source(IBluetoothAudio::IStream* source) = 0;
            };

            enum devicetype : uint8_t {
                UNKNOWN,
                HEADPHONE,
                SPEAKER,
                RECORDER,
                AMPLIFIER
            };

            // @event
            struct ICallback : virtual public Core::IUnknown {

                enum { ID = ID_BLUETOOTHAUDIO_SINK_CALLBACK };

                // @brief Signals audio sink state change
                // @param state: Changed BluetoothAudio State
                virtual void StateChanged(const IBluetoothAudio::state state) = 0;
            };

            virtual Core::hresult Callback(ICallback* callback) = 0;

            // @brief Assigns a Bluetooth sink device for audio playback
            // @param address: Address of the bluetooth device to assign
            // @retval ERROR_BAD_REQUEST Device address value is invalid
            // @retval ERROR_ALREADY_CONNECTED A sink device is already assigned
            virtual Core::hresult Assign(const string& address) = 0;

            // @brief Revokes a Bluetooth sink device from audio playback
            // @retval ERROR_ALREADY_RELEASED No device is currently assigned as sink
            virtual Core::hresult Revoke() = 0;

            // @property
            // @brief Current state o the audio sink device
            virtual Core::hresult State(state& sinkState /* @out */) const = 0;

            // @property
            // @brief Bluetooth address of the audio sink device
            // @retval ERROR_ILLEGAL_STATE The sink device currently is not assigned
            virtual Core::hresult Device(string& address /* @out */) const = 0;

            // @property
            // @brief Type of the audio sink device
            // @retval ERROR_ILLEGAL_STATE The sink device currently is not connected
            virtual Core::hresult Type(devicetype& sinkType /* @out */) const = 0;

            // @property
            // @brief Latency of the audio sink device
            // @param latency: Audio latency in milliseconds (e.g. 20)
            // @retval ERROR_BAD_REQUEST Latency value is invalid
            virtual Core::hresult Latency(const int16_t latency) = 0;
            virtual Core::hresult Latency(int16_t& latency /* @out */) const = 0;

            // @property
            // @brief Audio codecs supported by the audio sink device
            // @retval ERROR_ILLEGAL_STATE The sink device currently is not connected
            virtual Core::hresult SupportedCodecs(audiocodec& codecs /* @out @bitmask */) const = 0;

            // @property
            // @brief DRM schemes supported by the audio sink device
            // @retval ERROR_ILLEGAL_STATE The sink device currently is not connected
            virtual Core::hresult SupportedDRMs(drmscheme& drms /* @out @bitmask */) const = 0;

            // @property
            // @brief Properites of the currently used audio codec
            // @retval ERROR_ILLEGAL_STATE The sink device currently is not configured
            virtual Core::hresult Codec(CodecProperties& properties /* @out */) const = 0;

            // @property
            // @brief Properites of the currently used DRM scheme
            // @retval ERROR_ILLEGAL_STATE The sink device currently is not connected or not yet configured
            virtual Core::hresult DRM(DRMProperties& properties /* @out */) const = 0;

            // @property
            // @brief Properties of the currently transmitted audio stream
            // @retval ERROR_ILLEGAL_STATE The sink device currently is not connected or not yet configured
            virtual Core::hresult Stream(StreamProperties& properties /* @out */) const = 0;
       };

        // @json 1.0.0
        // @prefix source
        struct EXTERNAL ISource: virtual public Core::IUnknown {

            enum { ID = ID_BLUETOOTHAUDIO_SOURCE };

            struct EXTERNAL IControl : virtual public Core::IUnknown {

                // This interface is not exposed via JSON-RPC.

                enum { ID = ID_BLUETOOTHAUDIO_SOURCE_CONTROL };

                // Used to register a sink object that will recieve IStream
                // callbacks when the source device issues control commands.
                virtual Core::hresult Sink(IBluetoothAudio::IStream* sink) = 0;
            };

            enum devicetype : uint8_t {
                UNKNOWN,
                PLAYER,
                MICROPHONE,
                TUNER,
                MIXER
            };

            // @event
            struct ICallback : virtual public Core::IUnknown {

                enum { ID = ID_BLUETOOTHAUDIO_SOURCE_CALLBACK };

                // @brief Signals audio source state change
                // @param state: Changed BluetoothAudio State
                virtual void StateChanged(const IBluetoothAudio::state state) = 0;
            };

            virtual Core::hresult Callback(ICallback* callback) = 0;

            // @property
            // @brief Current state of the source device
            virtual Core::hresult State(state& sourceState /* @out */) const = 0;

            // @property
            // @brief Bluetooth address of the source device
            // @retval ERROR_ILLEGAL_STATE No source device is currently connected
            virtual Core::hresult Device(string& address /* @out */) const = 0;

            // @property
            // @brief Type of the audio source device
            // @retval ERROR_ILLEGAL_STATE No source device is currently connected
            virtual Core::hresult Type(devicetype& sourceType /* @out */) const = 0;

            // @property
            // @brief Properites of the currently used codec
            // @retval ERROR_ILLEGAL_STATE No source device is not connected or sink is not yet configured
            virtual Core::hresult Codec(CodecProperties& properties /* @out */) const = 0;

            // @property
            // @brief Properties of the currently used DRM scheme
            // @retval ERROR_ILLEGAL_STATE No source device is connected or sink is not yet configured
            virtual Core::hresult DRM(DRMProperties& properties /* @out */) const = 0;

            // @property
            // @brief Properites of the currently transmitted audio stream
            // @retval ERROR_ILLEGAL_STATE No source device is connected or sink is not yet configured
            virtual Core::hresult Stream(StreamProperties& properties /* @out */) const = 0;
        };

    } // namespace IBluetoothAudio

}

}
