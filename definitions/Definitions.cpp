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

#include "definitions.h"

#ifdef __WINDOWS__
#include <interfaces/IAmazonPrime.h>
#include <interfaces/IApplication.h>
#include <interfaces/IAVNClient.h>
#include <interfaces/IAVSClient.h>
#include <interfaces/IBluetooth.h>
#include <interfaces/IBluetoothAudio.h>
#include <interfaces/IButler.h>
#include <interfaces/IBrowser.h>
#include <interfaces/ICapture.h>
#include <interfaces/ICommand.h>
#include <interfaces/IComposition.h>
#include <interfaces/IConfiguration.h>
#include <interfaces/IContentDecryption.h>
#include <interfaces/ICryptography.h>
#include <interfaces/ICustomerCareOperations.h>
#include <interfaces/IDeviceInfo.h>
#include <interfaces/IDictionary.h>
#include <interfaces/IDisplayInfo.h>
#include <interfaces/IDialServer.h>
#include <interfaces/IDNSServer.h>
#include <interfaces/IDolby.h>
#include <interfaces/IDRM.h>
#include <interfaces/IDsgccClient.h>
#include <interfaces/IExternalBase.h>
#include <interfaces/IGuide.h>
#include <interfaces/IFocus.h>
#include <interfaces/IInputPin.h>
#include <interfaces/IInputSwitch.h>
#include <interfaces/IIPNetwork.h>
#include <interfaces/IKeyHandler.h>
#include <interfaces/ILisa.h>
#include <interfaces/ILanguageTag.h>
#include <interfaces/IMath.h>
#include <interfaces/IMemory.h>
#include <interfaces/IMessenger.h>
#include <interfaces/IMessageControl.h>
#include <interfaces/INetworkControl.h>
#include <interfaces/INetworkTools.h>
#include <interfaces/INetflix.h>
#include <interfaces/INetflixSecurity.h>
#include <interfaces/IPackageManager.h>
#include <interfaces/IPackager.h>
#include <interfaces/IPerformance.h>
#include <interfaces/IPlayerInfo.h>
#include <interfaces/IPlayGiga.h>
#include <interfaces/IPower.h>
#include <interfaces/IProvisioning.h>
#include <interfaces/IRemoteControl.h>
#include <interfaces/IResourceMonitor.h>
#include <interfaces/IRPCLink.h>
#include <interfaces/IRtspClient.h>
#include <interfaces/IRustBridge.h>
#include <interfaces/IScriptEngine.h>
#include <interfaces/ISecureShellServer.h>
#include <interfaces/IStream.h>
#include <interfaces/IStore.h>
#include <interfaces/IStoreCache.h>
#include <interfaces/ISwitchBoard.h>
#include <interfaces/ISystemCommands.h>
#include <interfaces/ITestController.h>
#include <interfaces/ITextToSpeech.h>
#include <interfaces/ITestUtility.h>
#include <interfaces/ITimeSync.h>
#include <interfaces/ITimeZone.h>
#include <interfaces/IVoiceHandler.h>
#include <interfaces/IVolumeControl.h>
#include <interfaces/IWebDriver.h>
#include <interfaces/IWebPA.h>
#include <interfaces/IWebServer.h>
#include <interfaces/IWifiControl.h>
#include <interfaces/IDeviceInfo.h>
#include <interfaces/IWatchDog.h>
#include <interfaces/IZigWave.h>
#include "ValuePoint.h"
#endif

MODULE_NAME_DECLARATION(BUILD_REFERENCE)

namespace WPEFramework {

struct ScreenResolutionWidthHeight {
    Exchange::IDeviceVideoCapabilities::ScreenResolution resolution;
    uint32_t width;
    uint32_t height;
    uint32_t refresh;
};

ScreenResolutionWidthHeight resolutionWidthHeightTable[] = {

    { Exchange::IDeviceVideoCapabilities::ScreenResolution_Unknown,   0,    0,    0 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_480i,      640,  480,  60000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_480p,      640,  480,  60000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_576i,      1024, 576,  60000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_576p,      1024, 576,  60000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_576p50Hz,  1024, 576,  50000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_720p,      1280, 720,  60000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_720p50Hz,  1280, 720,  50000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080i,     1920, 1080, 60000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080i25Hz, 1920, 1080, 25000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080i50Hz, 1920, 1080, 50000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p,     1920, 1080, 60000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p24Hz, 1920, 1080, 24000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p25Hz, 1920, 1080, 25000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p30Hz, 1920, 1080, 30000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p50Hz, 1920, 1080, 50000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p60Hz, 1920, 1080, 60000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_2160p30Hz, 3840, 2160, 30000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_2160p50Hz, 3840, 2160, 50000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_2160p60Hz, 3840, 2160, 60000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_4320p30Hz, 7680, 4320, 30000 },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_4320p60Hz, 7680, 4320, 60000 },
};

ENUM_CONVERSION_BEGIN(Exchange::IStream::streamtype)
    { Exchange::IStream::streamtype::Undefined, _TXT(_T("Undefined")) },
    { Exchange::IStream::streamtype::Cable, _TXT(_T("Cable")) },
    { Exchange::IStream::streamtype::Handheld, _TXT(_T("Handheld")) },
    { Exchange::IStream::streamtype::Satellite, _TXT(_T("Satellite")) },
    { Exchange::IStream::streamtype::Terrestrial, _TXT(_T("Terrestrial")) },
    { Exchange::IStream::streamtype::DAB, _TXT(_T("DAB")) },
    { Exchange::IStream::streamtype::RF, _TXT(_T("RF")) },
    { Exchange::IStream::streamtype::Unicast, _TXT(_T("Unicast")) },
    { Exchange::IStream::streamtype::Multicast, _TXT(_T("Multicast")) },
    { Exchange::IStream::streamtype::IP, _TXT(_T("IP")) },
ENUM_CONVERSION_END(Exchange::IStream::streamtype)

ENUM_CONVERSION_BEGIN(Exchange::IStream::state)
    { Exchange::IStream::state::Idle, _TXT(_T("Idle")) },
    { Exchange::IStream::state::Loading, _TXT(_T("Loading")) },
    { Exchange::IStream::state::Prepared, _TXT(_T("Prepared")) },
    { Exchange::IStream::state::Controlled, _TXT(_T("Controlled")) },
    { Exchange::IStream::state::Error, _TXT(_T("Error")) },
ENUM_CONVERSION_END(Exchange::IStream::state)

ENUM_CONVERSION_BEGIN(Exchange::IVoiceProducer::IProfile::codec)
    { Exchange::IVoiceProducer::IProfile::codec::UNDEFINED, _TXT(_T("undefined")) },
    { Exchange::IVoiceProducer::IProfile::codec::PCM, _TXT(_T("pcm")) },
    { Exchange::IVoiceProducer::IProfile::codec::ADPCM, _TXT(_T("adpcm")) },
ENUM_CONVERSION_END(Exchange::IVoiceProducer::IProfile::codec)

ENUM_CONVERSION_BEGIN(Exchange::IPower::PCState)
    { Exchange::IPower::On, _TXT(_T("on")) },
    { Exchange::IPower::ActiveStandby, _TXT(_T("active")) },
    { Exchange::IPower::PassiveStandby, _TXT(_T("passive")) },
    { Exchange::IPower::SuspendToRAM, _TXT(_T("suspended")) },
    { Exchange::IPower::Hibernate, _TXT(_T("hibernate")) },
    { Exchange::IPower::PowerOff, _TXT(_T("off")) }, 
ENUM_CONVERSION_END(Exchange::IPower::PCState)

ENUM_CONVERSION_BEGIN(Exchange::External::Metadata::protocol)
    { Exchange::External::Metadata::protocol::I2C,      _TXT(_T("I2C"))      },
    { Exchange::External::Metadata::protocol::ONEWIRE,  _TXT(_T("1W"))       },
    { Exchange::External::Metadata::protocol::NRF24L01, _TXT(_T("NRF24L01")) },
    { Exchange::External::Metadata::protocol::GPIO,     _TXT(_T("GPIO"))     },
    { Exchange::External::Metadata::protocol::ZWAVE,    _TXT(_T("ZWave"))    },
    { Exchange::External::Metadata::protocol::ZIGBEE,   _TXT(_T("ZigBee"))   },
    { Exchange::External::Metadata::protocol::JSONRPC,  _TXT(_T("JSONRPC"))  },
    { Exchange::External::Metadata::protocol::VIRTUAL,  _TXT(_T("Virtual"))  },
ENUM_CONVERSION_END(Exchange::External::Metadata::protocol)

ENUM_CONVERSION_BEGIN(Exchange::IBrightness::Brightness)
    { Exchange::IBrightness::SdrToHdrGraphicsBrightness_Default, _TXT("default") },
    { Exchange::IBrightness::SdrToHdrGraphicsBrightness_MatchVideo, _TXT("match_video") },
    { Exchange::IBrightness::SdrToHdrGraphicsBrightness_Max, _TXT("max") },
ENUM_CONVERSION_END(Exchange::IBrightness::Brightness)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceAudioCapabilities::AudioOutput)
    { Exchange::IDeviceAudioCapabilities::AudioOutput::AUDIO_OTHER, _TXT("OTHER") },
    { Exchange::IDeviceAudioCapabilities::AudioOutput::AUDIO_ANALOG, _TXT("ANALOG") },
    { Exchange::IDeviceAudioCapabilities::AudioOutput::AUDIO_DISPLAYPORT, _TXT("DISPLAYPORT") },
    { Exchange::IDeviceAudioCapabilities::AudioOutput::AUDIO_HDMI0, _TXT("HDMI0") },
    { Exchange::IDeviceAudioCapabilities::AudioOutput::AUDIO_HDMI1, _TXT("HDMI1") },
    { Exchange::IDeviceAudioCapabilities::AudioOutput::AUDIO_RF_MODULATOR, _TXT("RF_MODULATOR") },
    { Exchange::IDeviceAudioCapabilities::AudioOutput::AUDIO_SPDIF, _TXT("SPDIF0") },
ENUM_CONVERSION_END(Exchange::IDeviceAudioCapabilities::AudioOutput)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceAudioCapabilities::AudioCapability)
    { Exchange::IDeviceAudioCapabilities::AudioCapability::AUDIOCAPABILITY_NONE, _TXT("audiocapability_none") },
    { Exchange::IDeviceAudioCapabilities::AudioCapability::ATMOS, _TXT("atmos") },
    { Exchange::IDeviceAudioCapabilities::AudioCapability::DD, _TXT("dd") },
    { Exchange::IDeviceAudioCapabilities::AudioCapability::DDPLUS, _TXT("ddplus") },
    { Exchange::IDeviceAudioCapabilities::AudioCapability::DAD, _TXT("dad") },
    { Exchange::IDeviceAudioCapabilities::AudioCapability::DAPV2, _TXT("dapv2") },
    { Exchange::IDeviceAudioCapabilities::AudioCapability::MS12, _TXT("ms12") },
ENUM_CONVERSION_END(Exchange::IDeviceAudioCapabilities::AudioCapability)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceAudioCapabilities::MS12Capability)
    { Exchange::IDeviceAudioCapabilities::MS12Capability::MS12CAPABILITY_NONE, _TXT("ms12capability_none") },
    { Exchange::IDeviceAudioCapabilities::MS12Capability::DOLBYVOLUME, _TXT("dolbyvolume") },
    { Exchange::IDeviceAudioCapabilities::MS12Capability::INTELIGENTEQUALIZER, _TXT("inteligentequalizer") },
    { Exchange::IDeviceAudioCapabilities::MS12Capability::DIALOGUEENHANCER, _TXT("dialogueenhancer") },
ENUM_CONVERSION_END(Exchange::IDeviceAudioCapabilities::MS12Capability)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceAudioCapabilities::MS12Profile)
    { Exchange::IDeviceAudioCapabilities::MS12Profile::MS12PROFILE_NONE, _TXT("ms12profile_none") },
    { Exchange::IDeviceAudioCapabilities::MS12Profile::MUSIC, _TXT("music") },
    { Exchange::IDeviceAudioCapabilities::MS12Profile::MOVIE, _TXT("movie") },
    { Exchange::IDeviceAudioCapabilities::MS12Profile::VOICE, _TXT("voice") },
ENUM_CONVERSION_END(Exchange::IDeviceAudioCapabilities::MS12Profile)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceVideoCapabilities::VideoOutput)
    { Exchange::IDeviceVideoCapabilities::VideoOutput::VIDEO_COMPONENT, _TXT("COMPONENT") },
    { Exchange::IDeviceVideoCapabilities::VideoOutput::VIDEO_COMPOSITE, _TXT("COMPOSITE") },
    { Exchange::IDeviceVideoCapabilities::VideoOutput::VIDEO_DISPLAYPORT, _TXT("DISPLAYPORT") },
    { Exchange::IDeviceVideoCapabilities::VideoOutput::VIDEO_HDMI0, _TXT("HDMI0") },
    { Exchange::IDeviceVideoCapabilities::VideoOutput::VIDEO_HDMI1, _TXT("HDMI1") },
    { Exchange::IDeviceVideoCapabilities::VideoOutput::VIDEO_OTHER, _TXT("OTHER") },
    { Exchange::IDeviceVideoCapabilities::VideoOutput::VIDEO_RF_MODULATOR, _TXT("RF_MODULATOR") },
    { Exchange::IDeviceVideoCapabilities::VideoOutput::VIDEO_SCART_RGB, _TXT("SCART_RGB") },
    { Exchange::IDeviceVideoCapabilities::VideoOutput::VIDEO_SVIDEO, _TXT("SVIDEO") },
ENUM_CONVERSION_END(Exchange::IDeviceVideoCapabilities::VideoOutput)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceVideoCapabilities::ScreenResolution)
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_Unknown, _TXT("Unknown") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_480i, _TXT("480i") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_480p, _TXT("480p") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_576i, _TXT("576i") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_576p, _TXT("576p") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_576p50Hz, _TXT("576p50") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_720p, _TXT("720p") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_720p50Hz, _TXT("720p50") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080i ,_TXT("1080i") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080i25Hz ,_TXT("1080i25") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080i50Hz ,_TXT("1080i50") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p ,_TXT("1080p") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p24Hz, _TXT("1080p24") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p25Hz, _TXT("1080p25") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p30Hz, _TXT("1080p30") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p50Hz, _TXT("1080p50") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_1080p60Hz, _TXT("1080p60") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_2160p30Hz, _TXT("2160p30") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_2160p50Hz, _TXT("2160p50") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_2160p60Hz, _TXT("2160p60") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_4320p30Hz, _TXT("4320p30") },
    { Exchange::IDeviceVideoCapabilities::ScreenResolution_4320p60Hz, _TXT("4320p60") },
ENUM_CONVERSION_END(Exchange::IDeviceVideoCapabilities::ScreenResolution)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceVideoCapabilities::CopyProtection)
    { Exchange::IDeviceVideoCapabilities::CopyProtection::HDCP_UNAVAILABLE, _TXT("unavailable") },
    { Exchange::IDeviceVideoCapabilities::CopyProtection::HDCP_14, _TXT("1.4") },
    { Exchange::IDeviceVideoCapabilities::CopyProtection::HDCP_20, _TXT("2.0") },
    { Exchange::IDeviceVideoCapabilities::CopyProtection::HDCP_21, _TXT("2.1") },
    { Exchange::IDeviceVideoCapabilities::CopyProtection::HDCP_22, _TXT("2.2") },
ENUM_CONVERSION_END(Exchange::IDeviceVideoCapabilities::CopyProtection)

ENUM_CONVERSION_BEGIN(Exchange::IValuePoint::basic)
    { Exchange::IValuePoint::basic::regulator,      _TXT("regulator")      },
    { Exchange::IValuePoint::basic::measurement,    _TXT("measurment")     },
    { Exchange::IValuePoint::basic::group,          _TXT("group")          },
    { Exchange::IValuePoint::basic::identification, _TXT("identification") },
ENUM_CONVERSION_END(Exchange::IValuePoint::basic)

ENUM_CONVERSION_BEGIN(Exchange::IValuePoint::specific)
    { Exchange::IValuePoint::specific::general,         _TXT("general")         },
    { Exchange::IValuePoint::specific::electricity,     _TXT("electricity")     },
    { Exchange::IValuePoint::specific::water,           _TXT("water")           },
    { Exchange::IValuePoint::specific::gas,             _TXT("gas")             },
    { Exchange::IValuePoint::specific::air,             _TXT("air")             },
    { Exchange::IValuePoint::specific::smoke,           _TXT("smoke")           },
    { Exchange::IValuePoint::specific::carbonMonoxide,  _TXT("carbonmonoxide")  },
    { Exchange::IValuePoint::specific::carbonDioxide,   _TXT("carbondioxide")   },
    { Exchange::IValuePoint::specific::temperature,     _TXT("temperature")     },
    { Exchange::IValuePoint::specific::accessControl,   _TXT("accesscontrol")   },
    { Exchange::IValuePoint::specific::burglar,         _TXT("burglar")         },
    { Exchange::IValuePoint::specific::powerManagement, _TXT("powermanagement") },
    { Exchange::IValuePoint::specific::system,          _TXT("system")          },
    { Exchange::IValuePoint::specific::emergency,       _TXT("emergency")       },
    { Exchange::IValuePoint::specific::clock,           _TXT("clock")           },
    { Exchange::IValuePoint::specific::light,           _TXT("light")           },
ENUM_CONVERSION_END(Exchange::IValuePoint::specific)

ENUM_CONVERSION_BEGIN(Exchange::IValuePoint::dimension)
    { Exchange::IValuePoint::dimension::logic,      _TXT("logic")      },
    { Exchange::IValuePoint::dimension::percentage, _TXT("percentage") },
    { Exchange::IValuePoint::dimension::kwh,        _TXT("kwh")        },
    { Exchange::IValuePoint::dimension::kvah,       _TXT("kvah")       },
    { Exchange::IValuePoint::dimension::pulses,     _TXT("pulses")     },
    { Exchange::IValuePoint::dimension::degrees,    _TXT("degrees")    },
    { Exchange::IValuePoint::dimension::units,      _TXT("units")      },
    { Exchange::IValuePoint::dimension::lux,        _TXT("lux")        },
    { Exchange::IValuePoint::dimension::volt,       _TXT("volt")       },
    { Exchange::IValuePoint::dimension::ampere,     _TXT("ampere")     },

ENUM_CONVERSION_END(Exchange::IValuePoint::dimension)

namespace Exchange
{

    uint32_t IComposition::WidthFromResolution(const IComposition::ScreenResolution resolution)
    {
        return ((static_cast<uint32_t>(resolution) < sizeof(resolutionWidthHeightTable) / sizeof(ScreenResolutionWidthHeight)) ? resolutionWidthHeightTable[static_cast<uint32_t>(resolution)].width : 0);
    }

    uint32_t IComposition::HeightFromResolution(const IComposition::ScreenResolution resolution)
    {
        return ((static_cast<uint32_t>(resolution) < sizeof(resolutionWidthHeightTable) / sizeof(ScreenResolutionWidthHeight)) ? resolutionWidthHeightTable[static_cast<uint32_t>(resolution)].height : 0);
    }

    uint32_t IComposition::RefreshRateFromResolution(const IComposition::ScreenResolution resolution)
    {
        return ((static_cast<uint32_t>(resolution) < sizeof(resolutionWidthHeightTable) / sizeof(ScreenResolutionWidthHeight)) ? resolutionWidthHeightTable[static_cast<uint32_t>(resolution)].refresh: 0);
    }


    // ------------------------------------------------------------------------
    // Convenience methods to extract interesting information from the Type()
    // ------------------------------------------------------------------------
    /* static */ IExternal::basic IExternal::Basic(const uint32_t instanceType)
    {
        return (static_cast<basic>((instanceType >> 12) & 0xF));
    }

    /* static */ IExternal::dimension IExternal::Dimension(const uint32_t instanceType)
    {
        return (static_cast<dimension>((instanceType >> 19) & 0x1FFF));
    }

    /* static */ IExternal::specific IExternal::Specific(const uint32_t instanceType)
    {
        return (static_cast<specific>(instanceType & 0xFFF));
    }

    /* static */ uint8_t IExternal::Decimals(const uint32_t instanceType)
    {
        return ((instanceType >> 16) & 0x07);
    }

    /* static */ uint32_t IExternal::Type(const IExternal::basic base, const IExternal::specific spec, const IExternal::dimension dim, const uint8_t decimals) {
        return ((dim << 19) | ((decimals & 0x07) << 16) | (base << 12) | spec);
    }

    // ------------------------------------------------------------------------
    // Convenience methods to extract interesting information from the Type()
    // ------------------------------------------------------------------------
    /* static */ IValuePoint::basic IValuePoint::Basic(const uint32_t instanceType)
    {
        return (static_cast<basic>((instanceType >> 12) & 0xF));
    }

    /* static */ IValuePoint::dimension IValuePoint::Dimension(const uint32_t instanceType)
    {
        return (static_cast<dimension>((instanceType >> 19) & 0x1FFF));
    }

    /* static */ IValuePoint::specific IValuePoint::Specific(const uint32_t instanceType)
    {
        return (static_cast<specific>(instanceType & 0xFFF));
    }

    /* static */ uint8_t IValuePoint::Decimals(const uint32_t instanceType)
    {
        return ((instanceType >> 16) & 0x07);
    }

    /* static */ uint32_t IValuePoint::Type(const IValuePoint::basic base, const IValuePoint::specific spec, const IValuePoint::dimension dim, const uint8_t decimals) {
        return ((dim << 19) | ((decimals & 0x07) << 16) | (base << 12) | spec);
    }
}
}
