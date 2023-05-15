/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021,2023 Metrological
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

namespace WPEFramework {

namespace Exchange {

    // @json
    struct EXTERNAL IBluetoothAudioSink : virtual public Core::IUnknown {

        enum { ID = ID_BLUETOOTHAUDIOSINK };

        struct EXTERNAL IControl : virtual public Core::IUnknown {

            // This interface is not exposed via JSON-RPC

            enum { ID = ID_BLUETOOTHAUDIOSINK_CONTROL };

            struct Format {
                uint32_t SampleRate;
                uint16_t FrameRate;
                uint8_t Resolution;
                uint8_t Channels;
            };

            virtual uint32_t Acquire(const string& connector, const Format& format) = 0;
            virtual uint32_t Relinquish() = 0;

            virtual uint32_t Speed(const int8_t speed) = 0;

            virtual uint32_t Time(uint32_t& positionMs /* @out */) const = 0;
            virtual uint32_t Delay(uint32_t& delayMs /* @out */) const = 0;
        };

        enum state : uint8_t {
            UNASSIGNED,             // No Bluetooth device assigned for audio playback
            DISCONNECTED,           // Sink device assigned but not connected
            CONNECTED_BAD_DEVICE,   // The assigned Bluetooth device connected, but is not an audio sink or has insufficient audio capabilities
            CONNECTED_RESTRICTED,   // Audio sink connected, but content protection criteria are not met
            CONNECTED,              // Audio sink connected, but not yet configured
            READY,                  // Sink ready for streaming
            STREAMING               // Audio is streaming
        };

        enum devicetype : uint8_t {
            UNKNOWN,
            HEADPHONE,
            SPEAKER,
            RECORDER,
            AMPLIFIER
        };

        enum audiocodec : uint8_t {
            LC_SBC /* @text LC-SBC */
        };

        enum drmscheme : uint8_t {
            NONE,
            DTCP   /* @text DTCP */,
            SCMS_T /* @text SCMS-T */
        };

        struct CodecProperties {
            audiocodec Codec        /* @brief Audio codec used */ ;
            string Settings         /* @brief Codec-specific audio quality preset, compression profile, etc */ ;
        };

        struct DRMProperties {
            drmscheme DRM           /* @brief Content protection scheme used */ ;
            string Settings         /* @brief DRM-specific content protection level, encoding rules, etc */ ;
        };

        struct StreamProperties {
            uint32_t SampleRate     /* @brief Sample rate in Hz (e.g. 44100) */ ;
            uint32_t BitRate        /* @brief Target bitrate in bits per second (eg. 320000) */ ;
            uint8_t Channels        /* @brief Number of audio channels (e.g. 2) */ ;
            uint8_t Resolution      /* @brief Sampling resolution in bits per sample (e.g. 16) */ ;
            bool IsResampling       /* @brief Indicates if the sink is resampling the input stream */ ;
        };

        using IAudioCodecIterator = RPC::IIteratorType<audiocodec, ID_BLUETOOTHAUDIOSINK_AUDIOCODECITERATOR>;
        using IDRMSchemeIterator = RPC::IIteratorType<drmscheme, ID_BLUETOOTHAUDIOSINK_DRMSCHEMEITERATOR>;

        // @event
        struct ICallback : virtual public Core::IUnknown {

            enum { ID = ID_BLUETOOTHAUDIOSINK_CALLBACK };

            // @brief Signals audio sink state change or stream properties update
            virtual void Updated() = 0;
        };

        virtual uint32_t Callback(ICallback* callback) = 0;

        // @brief Assigns a Bluetooth device for audio playback
        // @param address Address of the bluetooth device to assign
        // @retval ERROR_BAD_REQUEST Device address value is invalid
        // @retval ERROR_ALREADY_CONNECTED A device is already assigned
        virtual uint32_t Assign(const string& address) = 0;

        // @brief Revokes a Bluetooth device from audio playback
        // @retval ERROR_ALREADY_RELEASED No device is currently assigned
        virtual uint32_t Revoke() = 0;

        // @property
        // @brief Sink audio latency
        // @param latency Audio latency of the sink in milliseconds (e.g. 20)
        // @retval ERROR_BAD_REQUEST Latency value is invalid
        // @retval ERROR_ILLEGAL_STATE No device is currently assigned
        virtual uint32_t Latency(const int16_t latency) = 0;
        virtual uint32_t Latency(int16_t& latency /* @out */) const = 0;

        // @property
        // @brief Current audio sink state
        virtual uint32_t State(state& sinkState /* @out */) const = 0;

        // @property
        // @brief Audio sink type
        // @retval ERROR_ILLEGAL_STATE The sink device is not connected
        virtual uint32_t Type(devicetype& type /* @out */) const = 0;

        // @property
        // @brief Audio codecs supported by the sink
        // @retval ERROR_ILLEGAL_STATE The sink device is not connected
        virtual uint32_t SupportedCodecs(IAudioCodecIterator*& codecs /* @out */) const = 0;

        // @property
        // @brief DRM schemes supported by the sink
        // @retval ERROR_ILLEGAL_STATE The sink device is not connected
        virtual uint32_t SupportedDRMs(IDRMSchemeIterator*& drms /* @out */) const = 0;

        // @property
        // @brief Properites of the currently used codec
        // @retval ERROR_ILLEGAL_STATE Currently not configured or streaming
        virtual uint32_t Codec(CodecProperties& properties /* @out */) const = 0;

        // @property
        // @brief Properties of the currently used DRM scheme
        // @retval ERROR_ILLEGAL_STATE Currently not configured or streaming
        virtual uint32_t DRM(DRMProperties& properties /* @out */) const = 0;

        // @property
        // @brief Properties of the current output stream
        // @retval ERROR_ILLEGAL_STATE Currently not configured or streaming
        virtual uint32_t Stream(StreamProperties& properties /* @out */) const = 0;
    };

    // @json
    struct EXTERNAL IBluetoothAudioSource: virtual public Core::IUnknown {

        enum { ID = ID_BLUETOOTHAUDIOSOURCE };

        struct EXTERNAL IControl : virtual public Core::IUnknown {

            // This interface is not exposed via JSON-RPC

            enum { ID = ID_BLUETOOTHAUDIOSOURCE_CONTROL };

            using Format = IBluetoothAudioSink::IControl::Format;

            struct EXTERNAL ICallback : virtual public Core::IUnknown {

                enum { ID = ID_BLUETOOTHAUDIOSOURCE_CONTROL_CALLBACK };

                virtual uint32_t Acquired(const string& connector, const Format& format) = 0;
                virtual void Relinquished() = 0;

                virtual void SpeedChanged(const int8_t speed) = 0;
            };

            virtual uint32_t Callback(ICallback* callback) = 0;

            virtual uint32_t Relinquish() = 0;

            virtual uint32_t Time(uint32_t& positionMs /* @out */) const = 0;
        };

        enum state : uint8_t {
            DISCONNECTED,           // No audio source device connected
            CONNECTED,              // Audio source connected, but not yet configured
            READY,                  // Source ready and configured for streaming
            STREAMING               // Audio is currently being streamed
        };

        enum devicetype : uint8_t {
            UNKNOWN,
            PLAYER,
            MICROPHONE,
            TUNER,
            MIXER
        };

        using CodecProperties = IBluetoothAudioSink::CodecProperties;
        using DRMProperties = IBluetoothAudioSink::DRMProperties;
        using StreamProperties = IBluetoothAudioSink::StreamProperties;

        // @event
        struct INotification : virtual public Core::IUnknown {

            enum { ID = ID_BLUETOOTHAUDIOSOURCE_NOTIFICATION };

            // @brief Signals audio source state change or stream properties update
            virtual void Updated() = 0;
        };

        virtual uint32_t Register(INotification* notification) = 0;
        virtual uint32_t Unregister(const INotification* notification) = 0;

        // @property
        // @brief Bluetooth address of the source device
        // @retval ERROR_ILLEGAL_STATE Source device not connected
        virtual uint32_t Device(string& address /* @out */) const = 0;

        // @property
        // @brief Properites of the currently used codec
        // @retval ERROR_ILLEGAL_STATE Currently not ready
        virtual uint32_t Codec(CodecProperties& properties /* @out */) const = 0;

        // @property
        // @brief Properties of the currently used DRM scheme
        // @retval ERROR_ILLEGAL_STATE Currently not ready
        virtual uint32_t DRM(DRMProperties& properties /* @out */) const = 0;

        // @property
        // @brief Properties of the current output stream
        // @retval ERROR_ILLEGAL_STATE Currently not ready
        virtual uint32_t Stream(StreamProperties& properties /* @out */) const = 0;
    };

}

}
