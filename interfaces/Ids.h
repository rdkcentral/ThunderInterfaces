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

#pragma once

// This file holds all the identifiers (uint32_t) used to identify an interface. From this
// identifier, the comrpc framework can find the proper proxy/stub in case of communicating
// over a process boundary. 
// Some users do not "fully" rebuild the system in case of changes. If this means that the 
// Proxy/Stub code is not always rebuild in case of new releases, the identifier associated
// with an interface becomes as important as the interface syntax and as interfaces are not
// allowed to be changed, the ID associated with the interface should also not be changed
// and thus should be "fixed". 

// So if you extend this file by defining a new interface ID make sure it is defined (has
// an actual value) and once the enum label has a value, never change it again.

// As some interfaces might be grouped, the first ID of the group is assigned a value, the 
// other interfaces belonging to this group use the enum value of label that has an assigned 
// value and just increment that label by the proper amount. 

// Using this system, all interfaces will have an assigned number. If numbers overlap, the
// compiler, your best friend, will start complaining. Time to reassign the value, before we 
// deploy.

// NOTE: Default the gap between each group of interface is 16. If you need more and the new 
//       addition is add the end, write a comment with your interface that you might need more
//       than 16 interface in that group so that the next ID is indeed elevated (and rounded 
//       up to a multiple of 16) if the next entry is made in the future.

namespace WPEFramework {

namespace Exchange {

    enum IDS : uint32_t {
        ID_BROWSER                                   = 0x00000040,
        ID_WEB_BROWSER                               = ID_BROWSER + 1,
        ID_BROWSER_NOTIFICATION                      = ID_BROWSER + 2,
        ID_BROWSER_METADATA                          = ID_BROWSER + 3,
        ID_BROWSER_RESOURCES                         = ID_BROWSER + 4,
        ID_BROWSER_SECURITY                          = ID_BROWSER + 5,
        ID_WEBKITBROWSER_NOTIFICATION                = ID_BROWSER + 6,
        ID_BROWSER_SCRIPTING                         = ID_BROWSER + 7,
        ID_BROWSER_COOKIEJAR                         = ID_BROWSER + 8,
        ID_BROWSER_COOKIEJAR_NOTIFICATION            = ID_BROWSER + 9,

        ID_POWER                                     = 0x00000050,
        ID_POWER_NOTIFICATION                        = ID_POWER + 1,

        ID_PLAYGIGA                                  = 0x00000060,

        ID_COMMAND                                   = 0x00000070,
        ID_COMMAND_REGISTRATION                      = ID_COMMAND + 1,

        ID_DICTIONARY                                = 0x00000080,
        ID_DICTIONARY_NOTIFICATION                   = ID_DICTIONARY + 1,
        ID_DICTIONARY_ITERATOR                       = ID_DICTIONARY + 2,

        ID_EXTERNAL                                  = 0x00000090,
        ID_EXTERNAL_NOTIFICATION                     = ID_EXTERNAL + 1,
        ID_EXTERNAL_CATALOG                          = ID_EXTERNAL + 2,
        ID_EXTERNAL_CATALOG_NOTIFICATION             = ID_EXTERNAL + 3,
        ID_EXTERNAL_DERIVED                          = ID_EXTERNAL + 4,

        ID_KEYHANDLER                                = 0x000000A0,

        ID_KEYPRODUCER                               = 0x000000B0,

        ID_MEMORY                                    = 0x000000C0,
        ID_PROCESSMEMORY                             = ID_MEMORY + 1,
        ID_MEMORYEXTENDED                            = ID_MEMORY + 2,
  
        ID_NETFLIX                                   = 0x000000D0,
        ID_NETFLIX_NOTIFICATION                      = ID_NETFLIX + 1,
  
        ID_CONTENTDECRYPTION                         = 0x000000E0,
        ID_CONTENTDECRYPTION_NOTIFICATION            = ID_CONTENTDECRYPTION + 1,

        ID_PROVISIONING                              = 0x000000F0,
        ID_PROVISIONING_NOTIFICATION                 = ID_PROVISIONING + 1,

        ID_SWITCHBOARD                               = 0x00000100,
        ID_SWITCHBOARD_NOTIFICATION                  = ID_SWITCHBOARD + 1,

        ID_TIMESYNC                                  = 0x00000110,
        ID_TIMESYNC_NOTIFICATION                     = ID_TIMESYNC + 1,

        ID_IPNETWORK                                 = 0x00000120,
        ID_IPNETWORK_DNSSERVER                       = ID_IPNETWORK + 1,

        ID_GUIDE                                     = 0x00000130,
        ID_GUIDE_NOTIFICATION                        = ID_GUIDE + 1,

        ID_VOICEHANDLER                              = 0x00000140,
        ID_VOICEPRODUCER                             = ID_VOICEHANDLER + 1,

        ID_WEBDRIVER                                 = 0x00000150,

        ID_WEBSERVER                                 = 0x00000160,

        ID_STREAMING                                 = 0x00000170,
        ID_STREAMING_NOTIFICATION                    = ID_STREAMING + 1,

        ID_CAPTURE                                   = 0x00000180,

        ID_RPCLINK                                   = 0x00000190,
        ID_RPCLINK_NOTIFICATION                      = ID_RPCLINK + 1,

        ID_AVNCLIENT                                 = 0x000001A0,

        ID_BLUETOOTH                                 = 0x000001B0,
        ID_BLUETOOTH_DEVICE                          = ID_BLUETOOTH + 1,
        ID_BLUETOOTH_DEVICE_ITERATOR                 = ID_BLUETOOTH + 2,
        ID_BLUETOOTH_NOTIFICATION                    = ID_BLUETOOTH + 3,
        ID_BLUETOOTH_DEVICE_CALLBACK                 = ID_BLUETOOTH + 4,
        ID_BLUETOOTH_DEVICE_SECURITYCALLBACK         = ID_BLUETOOTH + 5,
        ID_BLUETOOTH_DEVICE_CLASSIC                  = ID_BLUETOOTH + 6,
        ID_BLUETOOTH_DEVICE_CLASSIC_SECURITYCALLBACK = ID_BLUETOOTH + 7,
        ID_BLUETOOTH_DEVICE_LOWENERGY                = ID_BLUETOOTH + 8,
        ID_BLUETOOTH_CLASSIC                         = ID_BLUETOOTH + 9,
        ID_BLUETOOTH_CLASSIC_NOTIFICATION            = ID_BLUETOOTH + 10,
        ID_BLUETOOTH_LOWENERGY                       = ID_BLUETOOTH + 11,
        ID_BLUETOOTH_LOWENERGY_NOTIFICATION          = ID_BLUETOOTH + 12,

        ID_RTSPCLIENT                                = 0x000001C0,

        ID_SYSTEMCOMMAND                             = 0x000001D0,

        ID_PACKAGER                                  = 0x000001E0,
        ID_PACKAGER_INSTALLATIONINFO                 = ID_PACKAGER + 1,
        ID_PACKAGER_PACKAGEINFO                      = ID_PACKAGER + 2,
        ID_PACKAGER_NOTIFICATION                     = ID_PACKAGER + 3,

        ID_SECURESHELLSERVER                         = 0x000001F0,
        ID_SECURESHELLSERVER_CLIENT                  = ID_SECURESHELLSERVER + 1,
        ID_SECURESHELLSERVER_CLIENT_ITERATOR         = ID_SECURESHELLSERVER + 2,

        ID_PACKAGER_PACKAGEINFOEX                    = 0x00000200,
        ID_PACKAGER_PACKAGEINFOEX_ITERATOR           = ID_PACKAGER_PACKAGEINFOEX + 1,

        ID_TESTCONTROLLER                            = 0x00000210,
        ID_TESTCONTROLLER_TEST                       = ID_TESTCONTROLLER + 1,
        ID_TESTCONTROLLER_TEST_ITERATOR              = ID_TESTCONTROLLER + 2,
        ID_TESTCONTROLLER_CATEGORY                   = ID_TESTCONTROLLER + 3,
        ID_TESTCONTROLLER_CATEGORY_ITERATOR          = ID_TESTCONTROLLER + 4,

        ID_TESTUTILITY                               = 0x00000220,
        ID_TESTUTILITY_COMMAND                       = ID_TESTUTILITY + 1,
        ID_TESTUTILITY_ITERATOR                      = ID_TESTUTILITY + 2,

        ID_COMPOSITION                               = 0x00000230,
        ID_COMPOSITION_CLIENT                        = ID_COMPOSITION + 1,
        ID_COMPOSITION_RENDER                        = ID_COMPOSITION + 2,
        ID_COMPOSITION_NOTIFICATION                  = ID_COMPOSITION + 3,
        ID_COMPOSITION_DISPLAY                       = ID_COMPOSITION + 4,
        ID_COMPOSITION_CLIENTPROPERTIES              = ID_COMPOSITION + 5,

        ID_ROOMADMINISTRATOR                         = 0x00000240,
        ID_ROOMADMINISTRATOR_NOTIFICATION            = ID_ROOMADMINISTRATOR + 1,
        ID_ROOMADMINISTRATOR_ROOM                    = ID_ROOMADMINISTRATOR + 2,
        ID_ROOMADMINISTRATOR_ROOM_CALLBACK           = ID_ROOMADMINISTRATOR + 3,
        ID_ROOMADMINISTRATOR_ROOM_MSGNOTIFICATION    = ID_ROOMADMINISTRATOR + 4,

        ID_STREAM                                    = 0x00000250,
        ID_STREAM_CONTROL                            = ID_STREAM + 1,
        ID_STREAM_CONTROL_GEOMETRY                   = ID_STREAM + 2,
        ID_STREAM_CONTROL_CALLBACK                   = ID_STREAM + 3,
        ID_STREAM_CALLBACK                           = ID_STREAM + 4,
        ID_STREAM_ELEMENT                            = ID_STREAM + 5,
        ID_STREAM_ELEMENT_ITERATOR                   = ID_STREAM + 6,
        ID_PLAYER                                    = ID_STREAM + 7,

        ID_DSGCC_CLIENT                              = 0x00000260,
        ID_DSGCC_CLIENT_NOTIFICATION                 = ID_DSGCC_CLIENT + 1,

        ID_PERFORMANCE                               = 0x00000270,

        ID_WEBPA                                     = 0x00000280,
        ID_WEBPA_CLIENT                              = ID_WEBPA + 1,

        ID_WHEELHANDLER                              = 0x00000290,
        ID_WHEELPRODUCER                             = ID_WHEELHANDLER + 1,
        ID_POINTERHANDLER                            = ID_WHEELHANDLER + 2,
        ID_POINTERPRODUCER                           = ID_WHEELHANDLER + 3,
        ID_TOUCHHANDLER                              = ID_WHEELHANDLER + 4,
        ID_TOUCHPRODUCER                             = ID_WHEELHANDLER + 5,

        ID_REMOTECONTROL                             = 0x000002A0,
        ID_REMOTECONTROL_NOTIFICATION                = ID_REMOTECONTROL + 1,

        ID_RESOURCEMONITOR                           = 0x000002B0,

        ID_INPUT_PIN                                 = 0x000002C0,
        ID_INPUT_PIN_NOTIFICATION                    = ID_INPUT_PIN + 1,
        ID_INPUT_PIN_CATALOG                         = ID_INPUT_PIN + 2,

        ID_MATH                                      = 0x000002D0,

        ID_VOICEPRODUCER_PROFILE                     = 0x000002E0,

        ID_VOLUMECONTROL                             = 0x000002F0,
        ID_VOLUMECONTROL_NOTIFICATION                = ID_VOLUMECONTROL + 1,

        ID_DEVICE_PROPERTIES                         = 0x00000300,
        ID_GRAPHICS_PROPERTIES                       = ID_DEVICE_PROPERTIES + 1,
        ID_CONNECTION_PROPERTIES                     = ID_DEVICE_PROPERTIES + 2,
        ID_DISPLAY_PROPERTIES                        = ID_DEVICE_PROPERTIES + 3,
        ID_COLORIMETRY_ITERATOR                      = ID_DEVICE_PROPERTIES + 4,
        ID_CONNECTION_PROPERTIES_NOTIFICATION        = ID_DEVICE_PROPERTIES + 5,

        ID_HDR_PROPERTIES                            = 0x00000310,
        ID_HDR_ITERATOR                              = ID_HDR_PROPERTIES + 1,

        ID_PLAYER_PROPERTIES                         = 0x00000320,
        ID_PLAYER_PROPERTIES_AUDIO                   = ID_PLAYER_PROPERTIES + 1,
        ID_PLAYER_PROPERTIES_VIDEO                   = ID_PLAYER_PROPERTIES + 2,

        ID_REMOTEINVOCATION                          = 0x00000330,

        ID_AVSCLIENT                                 = 0x00000340,
        ID_AVSCONTROLLER                             = ID_AVSCLIENT + 1,
        ID_AVSCONTROLLER_NOTIFICATION                = ID_AVSCLIENT + 2,

        ID_INPUT_SWITCH                              = 0x00000350,

        ID_DOLBY_OUTPUT                              = 0x00000360,
        ID_DOLBY_OUTPUT_NOTIFICATION                 = ID_DOLBY_OUTPUT + 1,

        ID_AMAZONPRIME                               = 0x00000370,
        ID_AMAZONPRIME_NOTIFICATION                  = ID_AMAZONPRIME + 1,

        ID_CUSTOMER_CARE_OPERATIONS                  = 0x00000380,

        ID_MEDIAPLAYER                               = 0x00000390,
        ID_MEDIASTREAM                               = ID_MEDIAPLAYER + 1,
        ID_MEDIASTREAM_NOTIFICATION                  = ID_MEDIAPLAYER + 2,

        ID_APPLICATION                               = 0x000003A0,
        ID_APPLICATION_NOTIFICATION                  = ID_APPLICATION + 1,
        ID_CONFIGURATION                             = ID_APPLICATION + 2,

        ID_DEVICE_INFO                               = 0x000003B0,
        ID_DEVICE_CAPABILITIES_AUDIO                 = ID_DEVICE_INFO + 1,
        ID_DEVICE_CAPABILITIES_AUDIO_OUTPUT          = ID_DEVICE_INFO + 2,
        ID_DEVICE_CAPABILITIES_AUDIO_CAPABILITY      = ID_DEVICE_INFO + 3,
        ID_DEVICE_CAPABILITIES_AUDIO_MS12_CAPABILITY = ID_DEVICE_INFO + 4,
        ID_DEVICE_CAPABILITIES_AUDIO_MS12_PROFILE    = ID_DEVICE_INFO + 5,
        ID_DEVICE_CAPABILITIES_VIDEO                 = ID_DEVICE_INFO + 6,
        ID_DEVICE_CAPABILITIES_VIDEO_OUTPUT          = ID_DEVICE_INFO + 7,
        ID_DEVICE_CAPABILITIES_RESOLUTION            = ID_DEVICE_INFO + 8,

        ID_DIALSERVER                                = 0x000003C0,
        ID_DIALSERVER_APPLICATION                    = ID_DIALSERVER + 1,

        ID_LANGUAGETAG                               = 0x000003D0,
        ID_LANGUAGETAG_NOTIFICATION                  = ID_LANGUAGETAG + 1,
          
        ID_BRIGHTNESS                                = 0x000003E0,

        ID_FOCUS                                     = 0x000003F0,

        //OCDM
        ID_ACCESSOROCDM                              = 0x00000400,
        ID_ACCESSOROCDM_NOTIFICATION                 = ID_ACCESSOROCDM + 1,
        ID_SESSION                                   = ID_ACCESSOROCDM + 2,
        ID_SESSION_CALLBACK                          = ID_ACCESSOROCDM + 3,
        ID_SESSION_EXTENSION                         = ID_ACCESSOROCDM + 4,

        //Butler
        ID_BUTLER                                    = 0x00000410,
        ID_BUTLER_NOTIFICATION                       = ID_BUTLER + 1,

        // Network Tools
        ID_NETWORKTOOLS                              = 0x00000420,
        ID_NETWORKTOOLS_CALLBACK                     = ID_NETWORKTOOLS + 1,

        ID_BLUETOOTHAUDIOSINK                        = 0x00000430,
        ID_BLUETOOTHAUDIOSINK_CALLBACK               = ID_BLUETOOTHAUDIOSINK + 1,
        ID_BLUETOOTHAUDIOSINK_AUDIOCODECITERATOR     = ID_BLUETOOTHAUDIOSINK + 2,
        ID_BLUETOOTHAUDIOSINK_DRMSCHEMEITERATOR      = ID_BLUETOOTHAUDIOSINK + 3,
        ID_BLUETOOTHAUDIOSINK_CONTROL                = ID_BLUETOOTHAUDIOSINK + 4,

        ID_VALUE_POINT                               = 0x00000440,
        ID_VALUE_POINT_NOTIFICATION                  = ID_VALUE_POINT + 1,
        ID_VALUE_POINT_CATALOG                       = ID_VALUE_POINT + 2,
        ID_VALUE_POINT_CATALOG_NOTIFICATION          = ID_VALUE_POINT + 3,

        ID_ZIGWAVE                                   = 0x00000450,

        ID_TIMEZONE                                  = 0x00000460,
        ID_TIMEZONE_NOTIFICATION                     = ID_TIMEZONE + 1,

        ID_MESSAGE_CONTROL                           = 0x00000470,
        ID_MESSAGE_CONTROL_COLLECT                   = ID_MESSAGE_CONTROL + 1,
        ID_MESSAGE_CONTROL_COLLECT_CALLBACK          = ID_MESSAGE_CONTROL + 2,
        ID_MESSAGE_CONTROL_ITERATOR                  = ID_MESSAGE_CONTROL + 3,

        ID_STORE                                     = 0x00000480,
        ID_STORE_NOTIFICATION                        = ID_STORE + 1,
        ID_STORE_CACHE                               = ID_STORE + 2,

        ID_LISA                                      = 0x00000490,
        ID_LISA_NOTIFICATION                         = ID_LISA + 1,
        ID_LISA_APP_VERSION                          = ID_LISA + 2,
        ID_LISA_APP_VERSION_ITERATOR                 = ID_LISA + 3,
        ID_LISA_APP                                  = ID_LISA + 4,
        ID_LISA_APP_ITERATOR                         = ID_LISA + 5,
        ID_LISA_APPS_PAYLOAD                         = ID_LISA + 6,
        ID_LISA_STORAGE                              = ID_LISA + 7,
        ID_LISA_STORAGE_PAYLOAD                      = ID_LISA + 8,
        ID_LISA_PROGRESS                             = ID_LISA + 9,
        ID_LISA_KEY_VALUE                            = ID_LISA + 10,
        ID_LISA_KEY_VALUE_ITERATOR                   = ID_LISA + 11,
        ID_LISA_METADATA_PAYLOAD                     = ID_LISA + 12,
        ID_LISA_LOCK_INFO                            = ID_LISA + 13,
        ID_LISA_HANDLE_RESULT                        = ID_LISA + 14,

        ID_PACKAGEMANAGER                            = 0x000004A0,
        ID_PACKAGEMANAGER_KEY_VALUE_ITERATOR         = ID_PACKAGEMANAGER + 1,
        ID_PACKAGEMANAGER_NOTIFICATION               = ID_PACKAGEMANAGER + 2,
        ID_PACKAGEMANAGER_APP_VERSION_ITERATOR       = ID_PACKAGEMANAGER + 3,
        ID_PACKAGEMANAGER_BROKER                     = ID_PACKAGEMANAGER + 4,
        ID_PACKAGEMANAGER_CALLBACK                   = ID_PACKAGEMANAGER + 5,

        ID_RUST_BRIDGE                               = 0x000004B0,
        ID_RUST_BRIDGE_NOTIFICATION                  = ID_RUST_BRIDGE + 1,

        ID_WIFICONTROL                               = 0x000004C0,
        ID_WIFICONTROL_NOTIFICATION                  = ID_WIFICONTROL + 1,
        ID_WIFICONTROL_NETWORK_INFO_ITERATOR         = ID_WIFICONTROL + 2,
        ID_WIFICONTROL_SECURITY_INFO_ITERATOR        = ID_WIFICONTROL + 3,

        ID_NETWORKCONTROL                            = 0x000004D0,
        ID_NETWORKCONTROL_NOTIFICATION               = ID_NETWORKCONTROL + 1,
        ID_NETWORKCONTROL_NETWORK_INFO_ITERATOR      = ID_NETWORKCONTROL + 2,

        ID_WATCHDOG                                  = 0x000004E0,

        ID_SCRIPT_ENGINE                             = 0x000004F0,
        ID_SCRIPT_ENGINE_NOTIFICATION                = ID_SCRIPT_ENGINE + 1
    };
}
}
