/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
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
#include <interfaces/IAVNClient.h>
#include <interfaces/IAVSClient.h>
#include <interfaces/IBluetooth.h>
#include <interfaces/IButler.h>
#include <interfaces/IBrowser.h>
#include <interfaces/ICapture.h>
#include <interfaces/ICommand.h>
#include <interfaces/IComposition.h>
#include <interfaces/IConfiguration.h>
#include <interfaces/IContentDecryption.h>
#include <interfaces/ICustomerCareOperations.h>
#include <interfaces/IDeviceIdentification.h>
#include <interfaces/IDictionary.h>
#include <interfaces/IDisplayInfo.h>
#include <interfaces/IDialServer.h>
#include <interfaces/IDolby.h>
#include <interfaces/IDRM.h>
#include <interfaces/IDsgccClient.h>
#include <interfaces/IExternal.h>
#include <interfaces/IExternalBase.h>
#include <interfaces/IGuide.h>
#include <interfaces/IInputPin.h>
#include <interfaces/IInputSwitch.h>
#include <interfaces/IIPNetwork.h>
#include <interfaces/IKeyHandler.h>
#include <interfaces/IMath.h>
#include <interfaces/IMemory.h>
#include <interfaces/IMessenger.h>
#include <interfaces/INetflix.h>
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
#include <interfaces/ISecureShellServer.h>
#include <interfaces/IStream.h>
#include <interfaces/ISwitchBoard.h>
#include <interfaces/ISystemCommands.h>
#include <interfaces/ITestController.h>
#include <interfaces/ITestUtility.h>
#include <interfaces/ITimeSync.h>
#include <interfaces/IVoiceHandler.h>
#include <interfaces/IVolumeControl.h>
#include <interfaces/IWebDriver.h>
#include <interfaces/IWebPA.h>
#include <interfaces/IWebServer.h>
#include <interfaces/IDeviceInfo.h>
#endif

MODULE_NAME_DECLARATION(BUILD_REFERENCE);

namespace WPEFramework {

struct ScreenResolutionWidthHeight {
    Exchange::IComposition::ScreenResolution resolution;
    uint32_t width;
    uint32_t height;
};

ScreenResolutionWidthHeight resolutionWidthHeightTable[] = {

    { Exchange::IComposition::ScreenResolution_Unknown, 0, 0 },
    { Exchange::IComposition::ScreenResolution_480i, 640, 480 },
    { Exchange::IComposition::ScreenResolution_480p, 640, 480 },
    { Exchange::IComposition::ScreenResolution_720p, 1280, 720 },
    { Exchange::IComposition::ScreenResolution_720p50Hz, 1280, 720 },
    { Exchange::IComposition::ScreenResolution_1080p24Hz, 1920, 1080 },
    { Exchange::IComposition::ScreenResolution_1080i50Hz, 1920, 1080 },
    { Exchange::IComposition::ScreenResolution_1080p50Hz, 1920, 1080 },
    { Exchange::IComposition::ScreenResolution_1080p60Hz, 1920, 1080 },
    { Exchange::IComposition::ScreenResolution_2160p50Hz, 3840, 2160 },
    { Exchange::IComposition::ScreenResolution_2160p60Hz, 3840, 2160 },
};

ENUM_CONVERSION_BEGIN(Exchange::IComposition::ScreenResolution)
    { Exchange::IComposition::ScreenResolution_Unknown, _TXT("Unknown") },
    { Exchange::IComposition::ScreenResolution_480i, _TXT("480i") },
    { Exchange::IComposition::ScreenResolution_480p, _TXT("480p") },
    { Exchange::IComposition::ScreenResolution_720p, _TXT("720p") },
    { Exchange::IComposition::ScreenResolution_720p50Hz, _TXT("720p50Hz") },
    { Exchange::IComposition::ScreenResolution_1080p24Hz, _TXT("1080p24Hz") },
    { Exchange::IComposition::ScreenResolution_1080i50Hz, _TXT("1080i50Hz") },
    { Exchange::IComposition::ScreenResolution_1080p50Hz, _TXT("1080p50Hz") },
    { Exchange::IComposition::ScreenResolution_1080p60Hz, _TXT("1080p60Hz") },
    { Exchange::IComposition::ScreenResolution_2160p50Hz, _TXT("2160p50Hz") },
    { Exchange::IComposition::ScreenResolution_2160p60Hz, _TXT("2160p60Hz") },
ENUM_CONVERSION_END(Exchange::IComposition::ScreenResolution)

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

ENUM_CONVERSION_BEGIN(Exchange::IDeviceCapabilities::AudioOutput)
    { Exchange::IDeviceCapabilities::AudioOutput::AUDIO_OTHER, _TXT("other") },
    { Exchange::IDeviceCapabilities::AudioOutput::AUDIO_ANALOG, _TXT("analog") },
    { Exchange::IDeviceCapabilities::AudioOutput::AUDIO_DISPLAYPORT, _TXT("displayport") },
    { Exchange::IDeviceCapabilities::AudioOutput::AUDIO_HDMI, _TXT("hdmi") },
    { Exchange::IDeviceCapabilities::AudioOutput::AUDIO_RF_MODULATOR, _TXT("rf_modulator") },
    { Exchange::IDeviceCapabilities::AudioOutput::AUDIO_SPDIF, _TXT("spdif") },
ENUM_CONVERSION_END(Exchange::IDeviceCapabilities::AudioOutput)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceCapabilities::VideoOutput)
    { Exchange::IDeviceCapabilities::VideoOutput::VIDEO_COMPONENT, _TXT("component") },
    { Exchange::IDeviceCapabilities::VideoOutput::VIDEO_COMPOSITE, _TXT("composite") },
    { Exchange::IDeviceCapabilities::VideoOutput::VIDEO_DISPLAYPORT, _TXT("displayport") },
    { Exchange::IDeviceCapabilities::VideoOutput::VIDEO_HDMI, _TXT("hdmi") },
    { Exchange::IDeviceCapabilities::VideoOutput::VIDEO_OTHER, _TXT("other") },
    { Exchange::IDeviceCapabilities::VideoOutput::VIDEO_RF_MODULATOR, _TXT("rf_modulator") },
    { Exchange::IDeviceCapabilities::VideoOutput::VIDEO_SCART_RGB, _TXT("scart_rgb") },
    { Exchange::IDeviceCapabilities::VideoOutput::VIDEO_SVIDEO, _TXT("svideo") },
ENUM_CONVERSION_END(Exchange::IDeviceCapabilities::VideoOutput)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceCapabilities::OutputResolution)
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_1080I, _TXT("1080i") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_1080P, _TXT("1080p") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_2160P30, _TXT("2160p30") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_2160P60, _TXT("2160p60") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_4320P30, _TXT("4320p30") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_4320P60, _TXT("4320p60") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_480I, _TXT("480i") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_480P, _TXT("480p") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_576I, _TXT("576i") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_576P, _TXT("576p") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_720P, _TXT("720p") },
    { Exchange::IDeviceCapabilities::OutputResolution::RESOLUTION_UNKNOWN, _TXT("unknown") },
ENUM_CONVERSION_END(Exchange::IDeviceCapabilities::OutputResolution)

ENUM_CONVERSION_BEGIN(Exchange::IDeviceCapabilities::CopyProtection)
    { Exchange::IDeviceCapabilities::CopyProtection::HDCP_UNAVAILABLE, _TXT("unavailable") },
    { Exchange::IDeviceCapabilities::CopyProtection::HDCP_14, _TXT("hdcp_14") },
    { Exchange::IDeviceCapabilities::CopyProtection::HDCP_20, _TXT("hdcp_20") },
    { Exchange::IDeviceCapabilities::CopyProtection::HDCP_21, _TXT("hdcp_21") },
    { Exchange::IDeviceCapabilities::CopyProtection::HDCP_22, _TXT("hdcp_22") },
ENUM_CONVERSION_END(Exchange::IDeviceCapabilities::CopyProtection)

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
}
}
