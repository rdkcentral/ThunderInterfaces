/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Metrological
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

    /* @json 1.0.0 @text:legacy_lowercase */
    struct EXTERNAL IWANControl : virtual public Core::IUnknown {
        enum { ID = ID_WANCONTROL };

        enum StatusType : uint8_t {
            DOWN,
            UP
        };

        struct Dhcpv4Info {
            uint8_t       addressAssigned;              /** Have we been assigned an IP address ? */
            uint8_t       isExpired;                    /** Is the lease time expired ? */
            string        ip;                           /** New IP address, if addressAssigned==TRUE */
            string        netmask;                      /** New netmask, if addressAssigned==TRUE */
            string        gateway;                      /** New gateway, if addressAssigned==TRUE */
            string        dnsServer1;                   /** New dns Server, if addressAssigned==TRUE */
            string        dnsServer2;                   /** New dns Server, if addressAssigned==TRUE */
            string        dhcpcInterface;               /** Dhcp interface name */
            uint32_t      leaseTime;                    /** Lease time, , if addressAssigned==TRUE */
            uint32_t      rebindingTime;                /** Rebinding time, if addressAssigned==TRUE */
            uint32_t      renewalTime;                  /** Renewal Time, if addressAssigned==TRUE */
            int32_t       timeOffset;                   /** New time offset, if addressAssigned==TRUE */
            uint8_t       isTimeOffsetAssigned;         /** Is the time offset assigned ? */
            string        timeZone;                     /** New time zone, if addressAssigned==TRUE */
            uint8_t       mtuAssigned;                  /** Have we been assigned MTU size ? */
            uint16_t      mtuSize;                      /** MTU Size, if mtuAssigned==TRUE */
        };

        struct Dhcpv6Info
        {
            uint8_t       prefixAssigned;               /**< Have we been assigned a site prefix ? */
            uint8_t       addrAssigned;                 /**< Have we been assigned an IPv6 address ? */
            uint8_t       dnsAssigned;                  /**< Have we been assigned dns server addresses ? */
            uint8_t       domainNameAssigned;           /**< Have we been assigned dns server addresses ? */
            uint8_t       aftrAssigned;                 /**< Have we been assigned aftr name ? */
            uint8_t       mapeAssigned;                 /**< Have we been assigned mape config ? */
            uint8_t       maptAssigned;                 /**< Have we been assigned mapt config ? */
            uint8_t       isExpired;                    /**< Is the lease time expired ? */
            string        sitePrefix;                   /**< New site prefix, if prefixAssigned==TRUE */
            uint32_t      prefixPltime;
            uint32_t      prefixVltime;
            string        sitePrefixOld;                /**< add support for RFC7084 requirement L-13 */
            uint32_t      prefixVltimeOld;
            uint32_t      prefixCmd;
            string        ifname;
            string        address;                      /**< New IPv6 address, if addrAssigned==TRUE */
            uint32_t      addressPltime;
            uint32_t      addressVltime;
            string        pdIfAddress;                  /**< New IPv6 address of PD interface */
            uint32_t      addrCmd;
            string        nameserver1;                  /**< New nameserver, if addressAssigned==TRUE */
            string        nameserver2;                  /**< New nameserver, if addressAssigned==TRUE */
            string        domainName;                   /**< New domain Name, if addressAssigned==TRUE */
            string        ntpserver;                    /**< New ntp server(s), dhcp server may provide this */
        };

        struct InterfaceInfo {
            string      alias                                /* @brief Alias Name of Interface Name */;
            string      baseIfaceName                        /* @brief L2 Interface Name */;
            string      virtualIfaceName                     /* @brief L3 Interface Name */;
        };

        struct NetworkStatusInfo {
            String     current_wan_interface_name            /* @brief current wan interface name */;
            String     available_wan_interfaces_status       /* @brief available wan interface status */;
            StatusType wan_status                            /* @brief WAN status */;
        };

        struct NetworkInfo {
            struct NetworkStatusInfo    statusInfo           /* @brief Network Status Information */;
            struct Dhcpv4Info           dhcpv4Info           /* @brief Network IPv4 Information */;
            struct Dhcpv6Info           dhcpv6Info           /* @brief Network IPv6 Information */;
        };

        using INetworkInfoIterator = RPC::IIteratorType<NetworkInfo, ID_WANCONTROL_NETWORK_INFO_ITERATOR>;
        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

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
        // @brief Get Current active WAN network information
        // @param networkInfo: Output of Active WAN Information
        // @retval ERROR_UNAVAILABLE Failed to retrieve current WAN network information
        virtual uint32_t GetNetworkInfo(NetworkInfo& networkInfo /* @out */) const = 0;

        // @property
        // @brief Create WAN Interface
        // @param ifaceInfo: Information about Interface
        // @retval ERROR_UNAVAILABLE Failed to create WAN Interface
        virtual uint32_t CreateInterface(const struct InterfaceInfo ifaceInfo /* @in */) = 0;

        // @property
        // @brief Delete WAN Interface
        // @param interface: interface to be deleted
        // @retval ERROR_UNAVAILABLE Failed to delete WAN Interface
        virtual uint32_t DeleteInterface(const string& interface /* @in */) = 0;

        // @property
        // @brief Get WAN Interfaces Information
        // @param interfaces: interfaces information
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
