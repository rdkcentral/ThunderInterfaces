#pragma once

#include "Module.h"

// @stubgen:include <com/IRPCIterator.h>

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IDeviceCapabilities : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_CAPABILITIES };

        virtual ~IDeviceCapabilities() {}

        enum AudioOutput : uint8_t {
            ANALOG,
            DIGITAL_COAX,
            TOSLINK,
            HDMI_PCM,
            HDMI_DOLBY
        };

        enum VideoOutput : uint8_t {
            COMPOSITE,
            SCART_RGB,
            HDMI_14,
            HDMI_20,
            HDMI_21
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

        typedef RPC::IIteratorType<AudioOutput, ID_DEVICE_CAPABILITIES_AUDIO> IAudioOutputIterator;
        typedef RPC::IIteratorType<VideoOutput, ID_DEVICE_CAPABILITIES_VIDEO> IVideoOutputIterator;
        typedef RPC::IIteratorType<OutputResolution, ID_DEVICE_CAPABILITIES_RESOLUTION> IOutputResolutionIterator;

        virtual uint32_t Configure(const PluginHost::IShell* service) = 0;

        virtual uint32_t SupportedAudioOutputs(IAudioOutputIterator*& res /* @out */) const = 0;
        virtual uint32_t SupportedVideoOutputs(IVideoOutputIterator*& res /* @out */) const = 0;
        virtual uint32_t SupportedResolutions(IOutputResolutionIterator*& res /* @out */) const = 0;

        virtual uint32_t SupportsHDR(bool& supportsHDR /*@out*/) const = 0;
        virtual uint32_t SupportsAtmos(bool& supportsAtmos /*@out*/) const = 0;
    };
}
}