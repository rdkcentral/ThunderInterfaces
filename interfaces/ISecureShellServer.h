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

#include "Module.h"

// @stubgen:include <com/IIteratorType.h>

namespace Thunder {

namespace Exchange {

    // @stubgen:omit
    struct EXTERNAL ISecureShellServer : virtual public Core::IUnknown {

        enum { ID = ID_SECURESHELLSERVER };

	    ~ISecureShellServer() override = default;

        struct IClient : virtual public Core::IUnknown {

            enum { ID = ID_SECURESHELLSERVER_CLIENT};

            ~IClient() override = default;

            struct EXTERNAL IIterator : virtual public Core::IUnknown {

                enum { ID = ID_SECURESHELLSERVER_CLIENT_ITERATOR };

                ~IIterator() override = default;

                virtual uint32_t Count() const = 0;
                virtual void Reset() = 0;
                virtual bool IsValid() const = 0;
                virtual bool Next() = 0;
                virtual IClient* Current() = 0;
            };

            virtual string RemoteId() const = 0;
            virtual string TimeStamp() const = 0;
            virtual string IpAddress() const = 0;
            virtual void Close() = 0;
        };

        virtual IClient::IIterator* Clients() = 0;
    };

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL ISSHSessions : virtual public Core::IUnknown {

        enum { ID = ID_SECURESHELLSERVER_SESSIONS };

        struct Client {
            uint32_t pid /* @brief SSH client process ID (e.g. 268) */;
            string ipAddress /* @brief SSH client connected from this IP address (e.g. 192.168.33.57) */;
            string timeStamp /* @brief SSH client connected at this timestamp (e.g. Sun Jun 30 21:49:08 2019) */;
        };

        typedef RPC::IIteratorType<Client, ID_SECURESHELLSERVER_SESSIONS_ITERATOR> IClientIterator;

        // @property
        // @brief Get count of currently active SSH client sessions maintained by SecureShell SSH Service
        // @description With this method SecureShell SSH service shall provide the count of active SSH client sessions
        // @alt:deprecated getactivesessionscount
        // @param count: Number of client sessions count
        virtual Core::hresult ActiveSessionsCount(uint32_t& count /* @out */) const = 0;

        // @property
        // @brief Get details of currently active SSH client sessions maintained by SecureShell SSH Service
        // @description With this method SecureShell SSH service shall provide the full details of active SSH client sessions
        // @alt:deprecated getactivesessionsinfo
        // @param count: Number of client sessions count
        // @retval ERROR_GENERAL: No active SSH client sessions
        virtual Core::hresult ActiveSessionsInfo(IClientIterator*& clients /* @out */) const = 0;

        // @property
        // @brief Close an active SSH client session
        // @description With this method an active SSH client session shall be closed
        // @alt:deprecated closeclientsession
        // @param pid: SSH client process id
        virtual Core::hresult CloseSession(uint32_t& pid /* @out */) const = 0;

    };

} // namespace Exchange

}
