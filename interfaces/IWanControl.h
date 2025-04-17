/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Sky
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
    struct EXTERNAL IWANControl : virtual public Core::IUnknown {
        enum { ID = ID_WANCONTROL };

        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        enum StatusType : uint8_t {
            DOWN,
            UP
        };

        struct IPv4Info {
            string                 ipAddress;                    /** IPv4 address */
            string                 netmask;                      /** IPv4 netmask */
            string                 gateway;                      /** IPv4 Default gateway */
            IStringIterator        dnsServers;                   /** IPv4 dns Servers */
            string                 interfaceName;                /** IPv4 interface name */
            uint32_t               leaseTime;                    /** Lease time */
            uint32_t               rebindingTime;                /** Rebinding time */
            uint32_t               renewalTime;                  /** Renewal Time */
            int32_t                timeOffset;                   /** Time offset */
            string                 timeZone;                     /** Time zone */
            uint8_t                mtuSize;                      /** MTU Size */
        };

        struct IPv6Info
        {
            string                 sitePrefix;                   /** Site prefix */
            uint32_t               prefixPltime;                 /** IPv6 Prefix Preferred Life Time */
            uint32_t               prefixVltime;                 /** IPv6 Prefix Valid Life Time */
            string                 sitePrefixOld;                /** add support for RFC7084 requirement L-13, Site Prefix Old */
            uint32_t               prefixVltimeOld;              /** add support for RFC7084 requirement L-13, Prefix Valid Life Time Old */
            string                 interfaceName;                /** Interface where we received leases */
            string                 ipv6Address;                  /** IPv6 address */
            uint32_t               addressPltime;                /** IPv6 address, Preferred Life Time */
            uint32_t               addressVltime;                /** IPv6 address, Valid Life Time */
            string                 pdIfAddress;                  /** IPv6 address of Prefix Deligation interface */
            IStringIterator        dnsServers;                   /** Nameserver(s) */
            IStringIterator        ntpServers;                   /** Ntp server(s), dhcp server may provide this */
        };

        struct VirtualInterfaceConfig {
            string      alias                                /* @brief Alias Name of Interface Name */;
            string      virtualIfaceName                     /* @brief L3(Virtual) Interface Name */;
        };

        struct NetworkInterfaceStatus {
            String       alias                                 /* @brief current wan interface name */;
            bool         isActive                              /* @brief WAN interface active status */;
        };

        using INetworkInterfaceStatusIterator = RPC::IIteratorType<NetworkInterfaceStatus, ID_WANCONTROL_NETWORK_INTERFACE_STATUS_ITERATOR>;

        struct NetworkStatusInfo {
            String                              currentWanInterfaceName              /* @brief current wan interface name */;
            StatusType                          wanStatus                            /* @brief WAN status */;
            INetworkInterfaceStatusIterator     availableWanInterfacesStatus;        /* @brief available wan interface status */;
        };

        struct NetworkInfo {
            struct NetworkStatusInfo    statusInfo           /* @brief Network Status Information */;
            struct IPv4Info             ipv4Info             /* @brief Network IPv4 Information */;
            struct IPv6Info             ipv6Info             /* @brief Network IPv6 Information */;
        };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_WANCONTROL_NOTIFICATION };

            ~INotification() override = default;

            // @brief Signal WAN network status update
            // @param networkInfo: Active WAN network information where an update occured
            // @retval ERROR_UNAVAILABLE Failed to update WAN network information
            virtual uint32_t UpdateOnWANInfoChange(const NetworkStatusInfo& networkInfo) = 0;
        };

        ~IWANControl() override = default;

        // Pushing notifications to interested sinks
        virtual uint32_t Register(IWANControl::INotification* sink) = 0;
        virtual uint32_t Unregister(IWANControl::INotification* sink) = 0;

        // @property
        // @brief Get WAN network information
        // @param networkInfo: Output of WAN Information including Active, Available WAN status
        // @retval ERROR_UNAVAILABLE Failed to retrieve WAN network information
        virtual uint32_t GetNetworkInfo(NetworkInfo& networkInfo /* @out */) const = 0;

        // @property
        // @brief Create WAN Interface
        // @param interface: Input parameter for passing Base Interface Name to 
        //                       use a lookup to create virtual interface on top of this interface
        // @param config: Input of Virtual Interface Information
        // @retval ERROR_UNAVAILABLE Failed to create WAN Virtual Interface
        virtual uint32_t CreateInterface(const string& interface /* @in */, const struct VirtualInterfaceConfig config /* @in */) = 0;

        // @property
        // @brief Delete WAN Interface
        // @param interface: Input parameter for pasing alias to lookup corresponding virtual 
        //               interface to be delete and detach from base interface
        // @retval ERROR_UNAVAILABLE Failed to delete WAN Interface
        virtual uint32_t DeleteInterface(const string& interface /* @in */) = 0;

        // @property
        // @brief Get WAN Interfaces Information
        // @param interfaces: returns list of alias
        // @retval ERROR_UNAVAILABLE Failed to retrieve WAN Interfaces
        virtual uint32_t GetInterfaces(IStringIterator*& interfaces /* @out */) const = 0;
        
        // @property
        // @brief Activate WAN Interface
        // @param interface: interface to be Activate
        // @retval ERROR_UNAVAILABLE Failed to retrieve WAN Interface
        virtual uint32_t ActivateInterface(const string& interface /* @in */) = 0;
    };
}
}