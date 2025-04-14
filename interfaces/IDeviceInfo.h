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

namespace Thunder {

namespace Exchange {

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IDeviceInfo : virtual public Core::IUnknown {

        enum { ID = ID_DEVICE_INFO };

        enum Type : uint8_t {
            TV,
            IP_STB,
            QAM_IP_STB,
            HYBRID,
            MEDIA_CLIENT
        };

        struct FirmwareInfo {
            string imageName /* @brief Name of firmware image (e.g. PX051AEI_VBN_2203_sprint_20220331225312sdy_NG) */;
            Core::OptionalType<string> sdk /* @brief SDK version string (e.g. 17.3) */;
            Core::OptionalType<string> mediarite /* @brief Mediarite value (e.g. 8.3.53) */;
            Core::OptionalType<string> build /* @brief Yocto version (e.g. dunfell) */;
        };

        // @property
        // @brief Device serial number
        // @param value: Serial number set by manufacturer (e.g. PAW400003744)
        // @retval ERROR_UNAVAILABLE: Information about the serial number of the device is not available
        virtual Core::hresult SerialNumber(string& value /* @out */) const = 0;

        // @property
        // @brief Device model number or stock keeping unit (SKU)
        // @param value: Model number or SKU of the device (e.g. PX051AEI)
        // @retval ERROR_UNAVAILABLE: Information about the model number or SKU of the device is not available
        virtual Core::hresult ModelID(string& value /* @out */) const = 0;

        // @property
        // @brief Device manufacturer
        // @param value: Manufacturer of the device (e.g. pace)
        // @retval ERROR_UNAVAILABLE: Information about the manufacturer of the device is not available
        virtual Core::hresult Make(string& value /* @out */) const = 0;

        // @property
        // @brief Device model name
        // @param value: Model name of the device (e.g. Pace Xi5)
        // @reval ERROR_UNAVAILABLE: Information about the model name of the device is not available
        virtual Core::hresult ModelName(string& value /* @out */) const = 0;

        // @property
        // @brief Device model year
        // @param value: Year of the model (e.g. 2020)
        // @retval ERROR_UNAVAILABLE: Information about the model year of the device is not available
        virtual Core::hresult ModelYear(uint16_t& value /* @out */) const = 0;

        // @property
        // @brief Device friendly name
        // @param value: Friendly name of the device (e.g. My Device)
        // @retval ERROR_UNAVAILABLE: Information about the friendly name of the device is not available
        virtual Core::hresult FriendlyName(string& value /* @out */) const = 0;

        // @property
        // @brief Device type
        // @param value: Type of the device (e.g. IP_STB)
        // @retval ERROR_UNAVAILABLE: Information about a type of the device is not available
        // @retval ERROR_UNKNOWN_KEY: The device type is not recognized
        virtual Core::hresult DeviceType(Type& value /* @out */) const = 0;

        // @property
        // @brief Device platform name
        // @param value: Platform name of the device (e.g. Linux)
        // @retval ERROR_UNAVAILABLE: Information about the platform name of the device is not available
        virtual Core::hresult PlatformName(string& value /* @out */) const = 0;

        // @property
        // @brief Partner ID or distributor ID for device
        // @param value: Partner ID or distributor ID for device (e.g. Comcast)
        // @retval ERROR_UNAVAILABLE: Information about the distributor ID of the device is not available
        virtual Core::hresult DistributorID(string& value /* @out */) const = 0;

        // @property
        // @alt:deprecated firmwareversion
        // @brief Versions maintained in version.txt
        // @param value: Name of the firmware image and its specific versions
        // @retval ERROR_UNAVAILABLE: Information about the firmware version is not available
        virtual Core::hresult Firmware(FirmwareInfo& value /* @out */) const = 0;
    };

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IDeviceAudioCapabilities : virtual public Core::IUnknown {

        enum { ID = ID_DEVICE_CAPABILITIES_AUDIO };

        enum AudioOutput : uint8_t {
            OTHER,
            RF_MODULATOR,
            ANALOG,
            SPDIF, //over RCA or TOSLINK
            HDMI_0,
            HDMI_1,
            DISPLAY_PORT
        };

        enum AudioCapability : uint8_t {
            ATMOS,
            DD,
            DD_PLUS,
            DAD,
            DAP_V2,
            MS_12
        };

        enum MS12Capability : uint8_t {
            DOLBY_VOLUME,
            INTELIGENT_EQUALIZER,
            DIALOGUE_ENHANCER
        };

        enum MS12Profile : uint8_t {
            MUSIC,
            MOVIE,
            VOICE
        };

        typedef RPC::IIteratorType<AudioOutput, ID_DEVICE_CAPABILITIES_AUDIO_OUTPUT> IAudioOutputIterator;
        typedef RPC::IIteratorType<AudioCapability, ID_DEVICE_CAPABILITIES_AUDIO_CAPABILITY> IAudioCapabilityIterator;
        typedef RPC::IIteratorType<MS12Capability, ID_DEVICE_CAPABILITIES_AUDIO_MS12_CAPABILITY> IMS12CapabilityIterator;
        typedef RPC::IIteratorType<MS12Profile, ID_DEVICE_CAPABILITIES_AUDIO_MS12_PROFILE> IMS12ProfileIterator;

        // @property
        // @alt:deprecated supportedaudioports
        // @brief Audio ports supported on the device (all ports that are physically present
        // @param audioOutputs: An array of audio outputs supported by the device
        // @retval ERROR_GENERAL: General error
        virtual Core::hresult AudioOutputs(IAudioOutputIterator*& audioOutputs /* @out */) const = 0;

        // @property
        // @brief Audio capabilities for the specified audio port
        // @param audioOutput: Audio output supported by the device
        // @param audioCapabilities: An array of audio capabilities supported by specified port
        // @retval ERROR_GENERAL: General error
        virtual Core::hresult AudioCapabilities(const AudioOutput audioOutput /* @index */, IAudioCapabilityIterator*& audioCapabilities /* @out */) const = 0;

        // @property
        // @brief Audio ms12 capabilities for the specified audio port
        // @param audioOutput: Audio output supported by the device
        // @param ms12Capabilities: An array of MS12 audio capabilities supported by specified port
        // @retval ERROR_GENERAL: General error
        virtual Core::hresult MS12Capabilities(const AudioOutput audioOutput /* @index */, IMS12CapabilityIterator*& ms12Capabilities /* @out */) const = 0;

        // @property
        // @alt:deprecated supportedms12audioprofiles
        // @brief Audio ms12 profiles for the specified audio port
        // @param audioOutput: Audio output supported by the device
        // @param ms12Profiles: An array of MS12 audio profiles supported by specified port
        // @retval ERROR_GENERAL: General error
        virtual Core::hresult MS12AudioProfiles(const AudioOutput audioOutput /* @index */, IMS12ProfileIterator*& ms12Profiles /* @out */) const = 0;
    };

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IDeviceVideoCapabilities : virtual public Core::IUnknown {

        enum { ID = ID_DEVICE_CAPABILITIES_VIDEO };

        enum VideoOutput : uint8_t {
            OTHER,
            RF_MODULATOR,
            COMPOSITE, // also composite over SCART
            S_VIDEO,
            COMPONENT,
            SCART_RGB,
            HDMI_0,
            HDMI_1,
            DISPLAY_PORT // also DisplayPort over USB-C
        };

        enum ScreenResolution : uint8_t {
            ScreenResolution_Unknown,
            ScreenResolution_480i,
            ScreenResolution_480p,
            ScreenResolution_576i,
            ScreenResolution_576p,
            ScreenResolution_576p50Hz,
            ScreenResolution_720p,
            ScreenResolution_720p50Hz,
            ScreenResolution_1080i,
            ScreenResolution_1080i25Hz,
            ScreenResolution_1080i50Hz,
            ScreenResolution_1080p,
            ScreenResolution_1080p24Hz,
            ScreenResolution_1080p25Hz,
            ScreenResolution_1080p30Hz,
            ScreenResolution_1080p50Hz,
            ScreenResolution_1080p60Hz,
            ScreenResolution_2160p30Hz,
            ScreenResolution_2160p50Hz,
            ScreenResolution_2160p60Hz,
            ScreenResolution_4320p30Hz,
            ScreenResolution_4320p60Hz
        };

        enum CopyProtection : uint8_t {
            HDCP_14,
            HDCP_20,
            HDCP_21,
            HDCP_22
        };

        typedef RPC::IIteratorType<VideoOutput, ID_DEVICE_CAPABILITIES_VIDEO_OUTPUT> IVideoOutputIterator;
        typedef RPC::IIteratorType<ScreenResolution, ID_DEVICE_CAPABILITIES_RESOLUTION> IScreenResolutionIterator;

        // @property
        // @alt:deprecated supportedvideoports
        // @brief Video ports supported on the device (all ports that are physically present)
        // @param videoOutputs: An array of video outputs supported by the device
        // @retval ERROR_GENERAL: General error
        virtual Core::hresult VideoOutputs(IVideoOutputIterator*& videoOutputs /* @out */) const = 0;

        // @property
        // @brief Default resolution for the specified video output
        // @param videoOutput: Video output supported by the device
        // @param defaultResolution: Default resolution supported by specified port
        // @retval ERROR_UNKNOWN_KEY: Provided video output is not recognized
        virtual Core::hresult DefaultResolution(const VideoOutput videoOutput /* @index */, ScreenResolution& defaultResolution /* @out */) const = 0;

        // @property
        // @alt:deprecated supportedresolutions
        // @brief Resolutions supported by the specified video output
        // @param videoOutput: Video output supported by the device
        // @param resolutions: An array of resolutions supported by specified port
        // @retval ERROR_UNKNOWN_KEY: Provided video output is not recognized
        // @retval ERROR_GENERAL: General error
        virtual Core::hresult Resolutions(const VideoOutput videoOutput /* @index */, IScreenResolutionIterator*& resolutions /* @out */) const = 0;

        // @property
        // @alt:deprecated supportedhdcp
        // @brief High-bandwidth Digital Content Protection (HDCP) supported by the specified video output
        // @param videoOutput: Video output supported by the device
        // @param hdcpVersion: HDCP version supported by specified port
        // @retval ERROR_UNKNOWN_KEY: Provided video output is not recognized
        virtual Core::hresult Hdcp(const VideoOutput videoOutput /* @index */, CopyProtection& hdcpVersion /* @out */) const = 0;

        // @property
        // @brief Extended Display Identification Data (EDID) of the host
        // @param edid: A base64 encoded byte array string representing the EDID of the host (e.g. AP///////wAQrMLQVEJTMQUdAQOANR546q11qVRNnSYPUFSlSwCBALMA0QBxT6lAgYDRwAEBVl4AoKCgKVAwIDUADighAAAaAAAA/wBNWTNORDkxVjFTQlQKAAAA/ABERUxMIFAyNDE4RAogAAAA/QAxVh1xHAAKICAgICAgARsCAxuxUJAFBAMCBxYBBhESFRMUHyBlAwwAEAACOoAYcTgtQFgsRQAOKCEAAB4BHYAYcRwWIFgsJQAOKCEAAJ6/FgCggDgTQDAgOgAOKCEAABp+OQCggDgfQDAgOgAOKCEAABoAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA2A)
        virtual Core::hresult HostEDID(string& edid /* @out */) const = 0;

        // @propety
        // @brief HDR support by this device
        // @param supportsHDR: True if device supports HDR, false otherwise
        virtual Core::hresult HDR(bool& supportsHDR /* @out */) const = 0;

        // @property
        // @brief Atmos support by this device
        // @param supportsAtmos: True if device supports Atmos, false otherwise
        virtual Core::hresult Atmos(bool& supportsAtmos /* @out */) const = 0;

        // @property
        // @brief CEC support by this device
        // @param supportsCEC: True if device supports CEC, false otherwise
        virtual Core::hresult CEC(bool& supportsCEC /* @out */) const = 0;
    };

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL ISystemInfo : virtual public Core::IUnknown {

        enum { ID = ID_SYSTEM_INFO };

        struct CPULoads {
            uint8_t avg1min /* @brief avarage CPU load over the last minute (e.g. 10) */;
            uint8_t avg5min /* @brief avarage CPU load over the last 5 minutes (e.g. 15) */;
            uint8_t avg15min /* @brief avarage CPU load over the last 15 minutes (e.g. 20) */;
        };

        struct NetworkInterface {
            string name /* @brief Name of the network interface (e.g. lo) */;
            string mac /* @brief MAC address of the network interface (e.g. 00:00:00:00:00:00) */;
            Core::OptionalType<std::vector<string>> ipAddresses /* @brief List of IP addresses assigned to the network interface @restrict:100 */;
        };

        struct Sockets {
            Core::OptionalType<uint32_t> total /* @brief Total number of sockets (e.g. 1024) */;
            Core::OptionalType<uint32_t> open /* @brief Number of open sockets (e.g. 512) */;
            Core::OptionalType<uint32_t> link /* @brief Number of linked sockets (e.g. 256) */;
            Core::OptionalType<uint32_t> exception /* @brief Number of exceptions (e.g. 128) */;
            Core::OptionalType<uint32_t> shutdown /* @brief Number of sockets that were shut down (e.g. 64) */;
            uint32_t runs /* @brief Number of resource monitor runs (e.g. 32) */;
        };

        typedef RPC::IIteratorType<NetworkInterface, ID_SYSTEM_INFO_NETWORK_INTERFACE> INetworkInterfaceIterator;

        // @property
        // @brief Software version (in form *version#hashtag*)
        // param value: Software version of the device (e.g. 1.0#14452f612c3747645d54974255d11b8f3b4faa54)
        virtual Core::hresult Version(string& value /* @out */) const = 0;

        // @property
        // @brief System uptime (in seconds)
        // param value: System uptime in seconds (e.g. 120)
        virtual Core::hresult Uptime(uint32_t& value /* @out */) const = 0;

        // @property
        // @brief Total installed system RAM (in bytes)
        // param value: Total installed system RAM in bytes (e.g. 655757312)
        virtual Core::hresult TotalRAM(uint64_t& value /* @out */) const = 0;

        // @property
        // @brief Free system RAM (in bytes)
        // param value: System RAM still available in bytes (e.g. 563015680)
        virtual Core::hresult FreeRAM(uint64_t& value /* @out */) const = 0;

        // @property
        // @brief Total swap space (in bytes)
        // param value: Total swap space in bytes (e.g. 789132680)
        virtual Core::hresult TotalSwap(uint64_t& value /* @out */) const = 0;

        // @property
        // @brief Free swap space (in bytes)
        // param value: Swap space still available in bytes (e.g. 789132680)
        virtual Core::hresult FreeSwap(uint64_t& value /* @out */) const = 0;

        // @property
        // @brief Host name
        // param value: Host name of the device (e.g. buildroot)
        virtual Core::hresult DeviceName(string& value /* @out */) const = 0;

        // @property
        // @brief Current CPU load (percentage)
        // param value: Current CPU load in percentage (e.g. 2)
        virtual Core::hresult CPULoad(uint8_t& value /* @out */) const = 0;

        // @property
        // @brief CPU load averages from 1, 5 and 15 minutes (percentage)
        // param value: An array of three CPU load averages in percentage (e.g. [2, 3, 4])
        virtual Core::hresult CPULoadAvgs(CPULoads& value /* @out */) const = 0;

        // @property
        // @brief Network interface addresses
        // @param networkInterfaces: An array of network interfaces with their addresses
        virtual Core::hresult Addresses(INetworkInterfaceIterator*& networkInterfaces /* @out */) const = 0;

        // @property
        // @brief Socket information
        // @param socketInfo: Information about the sockets
        virtual Core::hresult SocketInfo(Sockets& socketInfo /* @out */) const = 0;
    };
}
}
