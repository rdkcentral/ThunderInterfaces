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

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IDeviceInfo : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_INFO };

        virtual ~IDeviceInfo() override = default;

        virtual uint32_t Configure(const PluginHost::IShell* service) = 0;

        virtual uint32_t SerialNumber(string& value /* @out */) const = 0;
        virtual uint32_t Sku(string& value /* @out */) const = 0;
        virtual uint32_t Make(string& value /* @out */) const = 0;
        virtual uint32_t ModelName(string& value/*@out*/) const = 0;
        virtual uint32_t ModelYear(uint16_t& value/*@out*/) const = 0;
        virtual uint32_t FriendlyName(string& value/*@out*/) const = 0;
        virtual uint32_t DeviceType(string& value /* @out */) const = 0;
        virtual uint32_t PlatformName(string& value/*@out*/) const = 0;
        virtual uint32_t DistributorId(string& value /* @out */) const = 0;
    };

    struct EXTERNAL IDeviceAudioCapabilities : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_CAPABILITIES_AUDIO };

        virtual ~IDeviceAudioCapabilities() override = default;

        enum AudioOutput : uint8_t {
            AUDIO_OTHER,
            AUDIO_RF_MODULATOR,
            AUDIO_ANALOG,
            AUDIO_SPDIF, //over RCA or TOSLINK
            AUDIO_HDMI0,
            AUDIO_HDMI1,
            AUDIO_DISPLAYPORT
        };

        enum AudioCapability : uint8_t {
            AUDIOCAPABILITY_NONE,
            ATMOS,
            DD,
            DDPLUS,
            DAD,
            DAPV2,
            MS12
        };

        enum MS12Capability : uint8_t {
            MS12CAPABILITY_NONE,
            DOLBYVOLUME,
            INTELIGENTEQUALIZER,
            DIALOGUEENHANCER
        };

        enum MS12Profile : uint8_t {
            MS12PROFILE_NONE,
            MUSIC,
            MOVIE,
            VOICE
        };

        typedef RPC::IIteratorType<AudioOutput, ID_DEVICE_CAPABILITIES_AUDIO_OUTPUT> IAudioOutputIterator;
        typedef RPC::IIteratorType<AudioCapability, ID_DEVICE_CAPABILITIES_AUDIO_CAPABILITY> IAudioCapabilityIterator;
        typedef RPC::IIteratorType<MS12Capability, ID_DEVICE_CAPABILITIES_AUDIO_MS12_CAPABILITY> IMS12CapabilityIterator;
        typedef RPC::IIteratorType<MS12Profile, ID_DEVICE_CAPABILITIES_AUDIO_MS12_PROFILE> IMS12ProfileIterator;

        virtual uint32_t AudioOutputs(IAudioOutputIterator*& audioOutputs /* @out */) const = 0;
        virtual uint32_t AudioCapabilities(const AudioOutput audioOutput /* @in */, IAudioCapabilityIterator*& audioCapabilities /* @out */) const = 0;
        virtual uint32_t MS12Capabilities(const AudioOutput audioOutput /* @in */, IMS12CapabilityIterator*& ms12Capabilities /* @out */) const = 0;
        virtual uint32_t MS12AudioProfiles(const AudioOutput audioOutput /* @in */, IMS12ProfileIterator*& ms12Profiles /* @out */) const = 0;
    };

    struct EXTERNAL IDeviceVideoCapabilities : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_CAPABILITIES_VIDEO };

        virtual ~IDeviceVideoCapabilities() override = default;

        enum VideoOutput : uint8_t {
            VIDEO_OTHER,
            VIDEO_RF_MODULATOR,
            VIDEO_COMPOSITE, // also composite over SCART
            VIDEO_SVIDEO,
            VIDEO_COMPONENT,
            VIDEO_SCART_RGB,
            VIDEO_HDMI0,
            VIDEO_HDMI1,
            VIDEO_DISPLAYPORT // also DisplayPort over USB-C
        };

        enum ScreenResolution : uint8_t {
            ScreenResolution_Unknown = 0,
            ScreenResolution_480i = 1,
            ScreenResolution_480p = 2,
            ScreenResolution_576i = 3,
            ScreenResolution_576p = 4,
            ScreenResolution_576p50Hz = 5,
            ScreenResolution_720p = 6,
            ScreenResolution_720p50Hz = 7,
            ScreenResolution_1080i = 8,
            ScreenResolution_1080i25Hz = 9,
            ScreenResolution_1080i50Hz = 10,
            ScreenResolution_1080p = 11,
            ScreenResolution_1080p24Hz = 12,
            ScreenResolution_1080p25Hz = 13,
            ScreenResolution_1080p30Hz = 14,
            ScreenResolution_1080p50Hz = 15,
            ScreenResolution_1080p60Hz = 16,
            ScreenResolution_2160p30Hz = 17,
            ScreenResolution_2160p50Hz = 18,
            ScreenResolution_2160p60Hz = 19,
            ScreenResolution_4320p30Hz = 20,
            ScreenResolution_4320p60Hz = 21
        };

        enum CopyProtection : uint8_t {
            HDCP_UNAVAILABLE,
            HDCP_14,
            HDCP_20,
            HDCP_21,
            HDCP_22
        };

        typedef RPC::IIteratorType<VideoOutput, ID_DEVICE_CAPABILITIES_VIDEO_OUTPUT> IVideoOutputIterator;
        typedef RPC::IIteratorType<ScreenResolution, ID_DEVICE_CAPABILITIES_RESOLUTION> IScreenResolutionIterator;

        virtual uint32_t VideoOutputs(IVideoOutputIterator*& videoOutputs /* @out */) const = 0;
        virtual uint32_t DefaultResolution(const VideoOutput videoOutput /* @in */, ScreenResolution& defaultResolution /* @out */) const = 0;
        virtual uint32_t Resolutions(const VideoOutput videoOutput /* @in */, IScreenResolutionIterator*& resolutions /* @out */) const = 0;
        virtual uint32_t Hdcp(const VideoOutput videoOutput /* @in */, CopyProtection& hdcpVersion /* @out */) const = 0;
        virtual uint32_t HostEDID(string& edid /* @out */) const = 0;
        virtual uint32_t HDR(bool& supportsHDR /*@out*/) const = 0;
        virtual uint32_t Atmos(bool& supportsAtmos /*@out*/) const = 0;
        virtual uint32_t CEC(bool& supportsCEC /*@out*/) const = 0;
    };
}
}
