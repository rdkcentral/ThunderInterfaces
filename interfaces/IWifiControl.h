/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Metrological
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

    /* @json */
    struct EXTERNAL IWifiControl : virtual public Core::IUnknown {
        enum { ID = ID_WIFICONTROL };

        enum Security : uint8_t {
            OPEN       = 0x01,
            WEP        = 0x02  /* @text: WEP */,
            WPA        = 0x04  /* @text: WPA */,
            WPA2       = 0x08  /* @text: WPA2 */,
            WPS        = 0x10  /* @text: WPS */,
            ENTERPRISE = 0x20  /* @text: Enterprise */,
            WPA_WPA2   = 0x40  /* @text: WPA_WPA2 */,
            UNKNOWN    = 0x00
        };
        
        struct SecurityInfo {
            enum Key : uint8_t {
                PSK        = 0x01  /* @text: PSK */,
                EAP        = 0x02  /* @text: EAP */,
                CCMP       = 0x04  /* @text: CCMP */,
                TKIP       = 0x08  /* @text: TKIP */,
                PREAUTH    = 0x10,
                PBC        = 0x20  /* @text: PBC */,
                PIN        = 0x40  /* @text: PIN */,
                PSK_HASHED = 0x80  /* @text: PSK_HASHED */,
                NONE       = 0x00
            };
            
            Security method;
            Key keys /* @bitmask */;
        };    
        using ISecurityIterator = RPC::IIteratorType<SecurityInfo, ID_WIFICONTROL_SECURITY_INFO_ITERATOR>;

        struct NetworkInfo {
            string ssid;
            uint64_t bssid;
            uint32_t frequency;
            int32_t signal;
            Security security /* @bitmask */;
        };
        using INetworkInfoIterator = RPC::IIteratorType<NetworkInfo, ID_WIFICONTROL_NETWORK_INFO_ITERATOR>;
        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        struct ConfigInfo {
            bool hidden;
            bool accesspoint;
            string ssid;
            string secret;
            string identity;
            Security method;
            SecurityInfo::Key key;
        };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_WIFICONTROL_NOTIFICATION };
            ~INotification() override = default;

            // @brief Notifies that Network were added, removed or modified.
            virtual void NetworkChange() = 0;

            // @brief Notifies that wifi connection changes
            virtual void ConnectionChange(const string& ssid) = 0;
        };

        ~IWifiControl() override = default;

        // Pushing notifications to interested sinks
        virtual uint32_t Register(IWifiControl::INotification* sink) = 0;
        virtual uint32_t Unregister(IWifiControl::INotification* sink) = 0;

        // @property
        // @brief Provides available networks information
        virtual uint32_t Networks(INetworkInfoIterator*& networkInfoList /* @out */) const = 0;

        // @property
        // @brief Provides security method of requested SSID
        virtual uint32_t Securities(const string& ssid /* @index */, ISecurityIterator*& securityMethods /* @out */) const = 0;

        // @property
        // @brief Provides configs list
        virtual uint32_t Configs(IStringIterator*& configs /* @out */) const = 0;

        // @property
        // NOTE: Setting the config by indicating the ssid, but in the POD the SSID member is empty, will
        //       remove the config and disconnect to this SSID (if applicable).
        // @brief Provide config details for requested SSID
        virtual uint32_t Config(const string& ssid /* @index */, ConfigInfo& configInfo /* @out */) const = 0;
        virtual uint32_t Config(const string& ssid /* @index */, const ConfigInfo& configInfo) = 0;

        // @brief Trigger Scanning
        virtual uint32_t Scan() = 0;
        // @brief Abort Currentlt running scan
        virtual uint32_t AbortScan() = 0;

        // @brief Connect device to requested SSID
        virtual uint32_t Connect(const string& configSSID) = 0;
        // @brief Disconnect device from requested SSID
        virtual uint32_t Disconnect(const string& configSSID) = 0;

        // @brief Status of current device, like which SSID is connected and it is in scanning state or not
        virtual uint32_t Status(string& connectedSsid /* @out */, bool& isScanning /* @out */) const = 0;
    };
}
}
