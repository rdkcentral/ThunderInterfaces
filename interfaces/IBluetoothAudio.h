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

// @insert <com/IIteratorType.h>

namespace WPEFramework {

namespace Exchange {

    // @json
    struct EXTERNAL IBluetoothAudioSink : virtual public Core::IUnknown {

        enum { ID = ID_BLUETOOTHAUDIOSINK };

        struct EXTERNAL IControl : virtual public Core::IUnknown {

            // This interface is not exposed via JSON-RPC

            enum { ID = ID_BLUETOOTHAUDIOSINK_CONTROL };

            struct Properties {
                uint32_t SampleRate     /* @brief Source sample rate in Hz (e.g. 44100)*/ ;
                uint16_t FrameRate      /* @brief Source frame rate in Hz (e.g. 24) */ ;
                uint8_t Channels        /* @brief Number of audio channels in the source stream (e.g. 2) */ ;
                uint8_t Resolution      /* @brief Sampling resolution in bits per sample (e.g. 16) */ ;
            };

            // @brief Opens a streaming session and configures the sink device
            // @brief properties Audio properties of the input stream
            // @param connector Name of the shared memory buffer the sample data will be written to
            // @retval ERROR_UNAVAILABLE The audio sink is currently being used by another client
            // @retval ERROR_ILLEGAL_STATE The audio sink is not connected or already open
            // @retval ERROR_NOT_SUPPORTED Stream properties are not supported by the sink or codec or otherwise invalid
            // @retval ERROR_OPENING_FAILED Failed to open the shared buffer
            // @retval ERROR_ASYNC_FAILED Device error, failed to open and/or configure
            virtual uint32_t Open(const Properties& properties, const string& connector) = 0;

            // @brief Starts audio stream playback
            // @retval ERROR_ILLEGAL_STATE The audio sink is not open or already streaming
            // @retval ERROR_ASYNC_FAILED Device error, failed to start/pause playback
            virtual uint32_t Start() = 0;

            // @brief Stops audio stream playback
            // @description Data still in the buffer will be played back to the end.
            // @retval ERROR_ILLEGAL_STATE The audio sink is not currently streaming
            // @retval ERROR_ASYNC_FAILED Device error, failed to start/pause playback
            virtual uint32_t Stop() = 0;

            // @brief Closes the streaming session
            // @retval ERROR_ILLEGAL_STATE The audio sink is not currently open
            // @retval ERROR_ASYNC_FAILED Device error, failed to close the sink
            virtual uint32_t Close() = 0;
        };

        enum status : uint8_t {
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

        // @brief Registers the status update callback
        // @param Callback to register or nullptr to deregister
        // @retval ERROR_ILLEGAL_STATE A calback is already registered with the audio sink
        virtual uint32_t Callback(ICallback* callback) = 0;

        // @brief Assigns a Bluetooth device for audio playback
        // @param address Address of the bluetooth device to assign
        // @retval ERROR_ALREADY_CONNECTED A device is already assigned
        virtual uint32_t Assign(const string& address) = 0;

        // @brief Revokes a Bluetooth device from audio playback
        // @param address Address of the bluetooth device to revoke
        // @retval ERROR_ALREADY_RELEASED No device is currently assigned
        virtual uint32_t Revoke() = 0;

        // @property
        // @brief Current audio sink status
        virtual uint32_t Status(status& sinkStatus /* @out */) const = 0;

        // @property
        // @brief Audio sink type
        // @retval ERROR_ILLEGAL_STATE The sink device is not connected
        virtual uint32_t Type(devicetype& type /* @out */) const = 0;

        // @property
        // @brief Audio codecs supported by the sink
        // @retval ERROR_ILLEGAL_STATE The sink device is not connected
        virtual uint32_t Codecs(IAudioCodecIterator*& codecs /* @out */) const = 0;

        // @property
        // @brief DRM schemes supported by the sink
        // @retval ERROR_ILLEGAL_STATE The sink device is not connected
        virtual uint32_t DRMs(IDRMSchemeIterator*& drms /* @out */) const = 0;

        // @property
        // @brief Current playback time
        // @param Playback mileage since sink opening (in miliseconds)
        // @retval ERROR_ILLEGAL_STATE The sink device is not connected
        virtual uint32_t Timestamp(uint32_t& position /* @out */) const = 0;

        // @property
        // @brief Currently used codec properties
        // @retval ERROR_ILLEGAL_STATE Currently not streaming
        virtual uint32_t CodecInfo(CodecProperties& info /* @out */) const = 0;

        // @property
        // @brief Currently used DRM scheme properties
        // @retval ERROR_ILLEGAL_STATE Currently not streaming
        virtual uint32_t DRMInfo(DRMProperties& info /* @out */) const = 0;

        // @property
        // @brief Current output stream properties
        // @retval ERROR_ILLEGAL_STATE Currently not streaming
        virtual uint32_t StreamInfo(StreamProperties& info /* @out */) const = 0;
    };

}

}
