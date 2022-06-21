#pragma once

#include "Module.h"

// @stubgen:include <com/IRPCIterator.h>

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IDeviceCapabilities : virtual public Core::IUnknown {
        enum { ID = ID_DEVICE_CAPABILITIES };

        virtual ~IDeviceCapabilities() override = default;

        enum CopyProtection : uint8_t {
            HDCP_UNAVAILABLE,
            HDCP_14,
            HDCP_20,
            HDCP_21,
            HDCP_22
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

        typedef RPC::IIteratorType<AudioCapability, ID_DEVICE_CAPABILITIES_AUDIO_CAPABILITY> IAudioCapabilityIterator;
        typedef RPC::IIteratorType<MS12Capability, ID_DEVICE_CAPABILITIES_MS12_CAPABILITY> IMS12CapabilityIterator;

        virtual uint32_t SerialNumber(string& serialNumber /* @out */) const = 0;
        virtual uint32_t Sku(string& sku /* @out */) const = 0;
        virtual uint32_t Make(string& make /* @out */) const = 0;
        virtual uint32_t Model(string& model /* @out */) const = 0;
        virtual uint32_t DeviceType(string& deviceType /* @out */) const = 0;
        virtual uint32_t DistributorId(string& distributorId /* @out */) const = 0;
        virtual uint32_t SupportedAudioPorts(RPC::IStringIterator*& supportedAudioPorts /* @out */) const = 0;
        virtual uint32_t SupportedVideoDisplays(RPC::IStringIterator*& supportedVideoDisplays /* @out */) const = 0;
        virtual uint32_t HostEDID(string& edid /* @out */) const = 0;
        virtual uint32_t DefaultResolution(const string& videoDisplay /* @in */, string& defaultResolution /* @out */) const = 0;
        virtual uint32_t SupportedResolutions(const string& videoDisplay /* @in */, RPC::IStringIterator*& supportedResolutions /* @out */) const = 0;
        virtual uint32_t SupportedHdcp(const string& videoDisplay /* @in */, CopyProtection& supportedHDCPVersion /* @out */) const = 0;
        virtual uint32_t AudioCapabilities(const string& audioPort /* @in */, IAudioCapabilityIterator*& audioCapabilities /* @out */) const = 0;
        virtual uint32_t MS12Capabilities(const string& audioPort /* @in */, IMS12CapabilityIterator*& ms12Capabilities /* @out */) const = 0;
        virtual uint32_t SupportedMS12AudioProfiles(const string& audioPort /* @in */, RPC::IStringIterator*& supportedMS12AudioProfiles /* @out */) const = 0;
    };
}
}