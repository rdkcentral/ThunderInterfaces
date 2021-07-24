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

// @stubgen:include <com/IRPCIterator.h>

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IDeviceCapabilities : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_CAPABILITIES };

        ~IDeviceCapabilities() override = default;

        enum AudioOutput : uint8_t {
            AUDIO_OTHER,
            AUDIO_RF_MODULATOR,
            AUDIO_ANALOG,
            AUDIO_SPDIF, //over RCA or TOSLINK
            AUDIO_HDMI,
            AUDIO_DISPLAYPORT
        };

        enum VideoOutput : uint8_t {
            VIDEO_OTHER,
            VIDEO_RF_MODULATOR,
            VIDEO_COMPOSITE, // also composite over SCART
            VIDEO_SVIDEO,
            VIDEO_COMPONENT,
            VIDEO_SCART_RGB,
            VIDEO_HDMI,
            VIDEO_DISPLAYPORT // also DisplayPort over USB-C
        };

        enum OutputResolution : uint8_t {
            RESOLUTION_UNKNOWN,
            RESOLUTION_480I,
            RESOLUTION_480P,
            RESOLUTION_576I,
            RESOLUTION_576P,
            RESOLUTION_720P,
            RESOLUTION_1080I,
            RESOLUTION_1080P,
            RESOLUTION_2160P30,
            RESOLUTION_2160P60,
            RESOLUTION_4320P30,
            RESOLUTION_4320P60,
        };

        enum CopyProtection : uint8_t {
            HDCP_UNAVAILABLE,
            HDCP_14,
            HDCP_20,
            HDCP_21,
            HDCP_22
        };

        typedef RPC::IIteratorType<AudioOutput, ID_DEVICE_CAPABILITIES_AUDIO> IAudioOutputIterator;
        typedef RPC::IIteratorType<VideoOutput, ID_DEVICE_CAPABILITIES_VIDEO> IVideoOutputIterator;
        typedef RPC::IIteratorType<OutputResolution, ID_DEVICE_CAPABILITIES_RESOLUTION> IOutputResolutionIterator;

        virtual uint32_t Configure(const PluginHost::IShell* service) = 0;

        virtual uint32_t AudioOutputs(IAudioOutputIterator*& res /* @out */) const = 0;
        virtual uint32_t VideoOutputs(IVideoOutputIterator*& res /* @out */) const = 0;
        virtual uint32_t Resolutions(IOutputResolutionIterator*& res /* @out */) const = 0;

        virtual uint32_t HDR(bool& supportsHDR /*@out*/) const = 0;
        virtual uint32_t Atmos(bool& supportsAtmos /*@out*/) const = 0;
        virtual uint32_t CEC(bool& supportsCEC /*@out*/) const = 0;
        virtual uint32_t HDCP(CopyProtection& supportedHDCP /*@out*/) const = 0;



    };

    struct EXTERNAL IDeviceMetadata : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_METADATA };

        ~IDeviceMetadata() override = default;


        virtual uint32_t ModelName(string& value/*@out*/) const = 0; 
        virtual uint32_t ModelYear(uint16_t& value/*@out*/) const = 0; 
        virtual uint32_t FriendlyName(string& value/*@out*/) const = 0; 
        virtual uint32_t SystemIntegratorName(string& value/*@out*/) const = 0; 
        virtual uint32_t PlatformName(string& value/*@out*/) const = 0; 
    };
}
}
