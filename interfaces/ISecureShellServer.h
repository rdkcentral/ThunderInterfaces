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



namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL ISecureShellServer : virtual public Core::IUnknown {
        enum { ID = ID_SECURESHELLSERVER };

	    ~ISecureShellServer() override = default;

        struct IClientSession : virtual public Core::IUnknown {

            enum { ID = ID_SECURESHELLSERVER_CLIENT};

            struct EXTERNAL IIterator : virtual public Core::IUnknown {

                enum { ID = ID_SECURESHELLSERVER_CLIENT_ITERATOR };

                virtual ~IIterator() {}

                virtual uint32_t Count() const = 0;
                virtual void Reset() = 0;
                virtual bool IsValid() const = 0;
                virtual bool Next() = 0;
                virtual IClientSession* Current() = 0;
            };

            ~IClientSession() override = default;

            virtual uint64_t RemoteId() const = 0;
            virtual string TimeStamp() const = 0;
            virtual string IpAddress() const = 0;
        };


        virtual uint32_t Activate_dropbear(const string& inputConfigs) = 0;
        virtual uint32_t Deactivate_dropbear() = 0;
        virtual size_t GetActiveSessionsCount() = 0 ;
        virtual uint32_t CloseClientSession(const uint64_t pid) = 0;
        virtual IClientSession::IIterator* ActiveClientsIter() = 0;

    };

}
}
