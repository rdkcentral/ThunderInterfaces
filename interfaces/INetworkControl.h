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

namespace Thunder {
namespace Exchange {

    /* @json 1.0.0 */
    struct EXTERNAL INetworkControl : virtual public Core::IUnknown {
        enum { ID = ID_NETWORKCONTROL };

        enum ModeType : uint8_t {
            STATIC,
            DYNAMIC
        };

        enum StatusType : uint8_t {
            UNAVAILABLE,
            AVAILABLE
        };

        struct NetworkInfo {
            string address        /* @brief IP Address */;
            string defaultGateway /* @brief Default Gateway */;
            uint8_t mask          /* @brief Network mask */;
            ModeType mode         /* @brief Mode of interface activation Dynamic or Static */;
        };

        using INetworkInfoIterator = RPC::IIteratorType<NetworkInfo, ID_NETWORKCONTROL_NETWORK_INFO_ITERATOR>;
        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_NETWORKCONTROL_NOTIFICATION };
            ~INotification() override = default;

            // @brief Signal interface update
            // @param interfaceName: Name of the interface where an update occured
            virtual void Update(const string& interfaceName) = 0;
        };

        ~INetworkControl() override = default;

        // Pushing notifications to interested sinks
        virtual uint32_t Register(INetworkControl::INotification* sink) = 0;
        virtual uint32_t Unregister(INetworkControl::INotification* sink) = 0;

        // @property
        // @brief Currently available interfaces
        virtual uint32_t Interfaces(IStringIterator*& interfaces /* @out */) const = 0;

        // @property
        // @brief Status of requested interface
        virtual uint32_t Status(const string& interface /* @index */, StatusType& status /* @out */) const = 0;

        // @property
        // @brief Network info of requested interface
        // @param networkInfo: Info about requested interface
        // @retval ERROR_UNAVAILABLE Failed to set/retrieve network
        virtual uint32_t Network(const string& interface /* @index */, INetworkInfoIterator*& networkInfo /* @out */) const = 0;
        virtual uint32_t Network(const string& interface /* @index */, INetworkInfoIterator* const& networkInfo /* @in */) = 0;

        // @property
        // @brief DNS list
        // @param dns: List of DNS
        // @retval ERROR_UNAVAILABLE Failed to set/retrieve DNS
        virtual uint32_t DNS(IStringIterator*& dns /* @out */) const = 0;
        virtual uint32_t DNS(IStringIterator* const& dns /* @in */) = 0;

        // @property
        // @brief Provides given requested interface is up or not
        // @param up: Up/Down requested interface
        // @retval ERROR_UNAVAILABLE Failed to set/retrieve UP
        virtual uint32_t Up(const string& interface /* @index */, bool& up /* @out */) const = 0;
        virtual uint32_t Up(const string& interface /* @index */, const bool up /* @in */) = 0;

        // @brief Flush and reload requested interface
        // @param interface: Name of the interface to be flushed
        virtual uint32_t Flush(const string& interface) = 0;
    };
}
}
