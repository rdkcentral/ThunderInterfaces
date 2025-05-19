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

// @insert <com/IIteratorType.h>

namespace Thunder {

namespace Exchange {

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IDHCPServer : virtual public Core::IUnknown {

        enum { ID = ID_DHCP_SERVER };

        struct Lease {
            string name /* @brief Client identifier (or client hardware address if identifier is absent) (e.g. 00e04c326c56) */;
            string ip /* @brief Client IP address (e.g. 192.168.0.10) */;
            Core::OptionalType<Core::Time> expires /* @brief Client IP expiration time (in ISO8601 format, empty: never expires) (e.g. 2019-05-07T07:20:26Z) */;
        };

        struct Server {
            string interface /* @brief Network interface name (e.g. eth0) */;
            bool active /* @brief Denotes if server is currently active (e.g. true) */;
            Core::OptionalType<string> begin /* @brief IP address pool start (e.g. 192.168.0.10) */;
            Core::OptionalType<string> end /* @brief IP address pool end (e.g. 192.168.0.100) */;
            Core::OptionalType<string> router /* @brief Router IP address (e.g. 192.168.0.1) */;
            Core::OptionalType<std::vector<Lease>> leases /* @brief List of IP address leases @restrict:100 */;
        };

        typedef RPC::IIteratorType<Server, ID_DHCP_SERVER_SERVERS> IServerIterator;

        // @brief Activates a DHCP server
        // @param interface: Network interface name (e.g. eth0)
        // @retval ERROR_GENERAL: Failed to activate server
        // @retval ERROR_UNKNOWN_KEY: Invalid interface name given
        // @retval ERROR_ILLEGAL_STATE: Server is already activated
        virtual Core::hresult Activate(const string& interface) = 0;

        // @brief Deactivates a DHCP server
        // @param interface: Network interface name (e.g. eth0)
        // @retval ERROR_GENERAL: Failed to deactivate server
        // @retval ERROR_UNKNOWN_KEY: Invalid interface name given
        // @retval ERROR_ILLEGAL_STATE: Server is not activated
        virtual Core::hresult Deactivate(const string& interface) = 0;

        // @property
        // @brief Server status
        // @param interface: Server name, if omitted, status of all configured servers is returned (e.g. eth0)
        // @param servers: List of configured servers
        // @retval ERROR_UNKNOWN_KEY: Invalid server name given
        virtual Core::hresult Status(const Core::OptionalType<string>& interface /* @index */, IServerIterator*& servers /* @out @extract */) const = 0;
    };

} // namespace Exchange

}
