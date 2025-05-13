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

// @insert <com/IIteratorType.h>

namespace Thunder {

namespace Exchange {

    // This interface gives direct access to a time synchronize / update
    struct EXTERNAL IInputSwitch : virtual public Core::IUnknown {
        enum { ID = ID_INPUT_SWITCH };

        enum mode : uint8_t {
            ENABLED,
            DISABLED,
            SLAVE
        };

        virtual RPC::IStringIterator* Consumers() const = 0;
        virtual bool Consumer(const string& name) const = 0;
        virtual uint32_t Consumer(const string& name, const mode value) = 0;

        virtual uint32_t Select(const string& name) = 0;
    };

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IInputSwitchChannel : virtual public Core::IUnknown {

        enum { ID = ID_INPUT_SWITCH_CHANNEL };

        struct Channel {
            string name /* @brief Callsign associated with this channel (e.g. WebKitBrowser) */;
            bool enabled /* @brief Is the channel enabled to receive info (e.g. true) */;
        };

        typedef RPC::IIteratorType<Channel, ID_INPUT_SWITCH_CHANNEL_CHANNELS> IChannelIterator;

        // @brief Enable or Disable the throughput through the given channel
        // @param name: Callsign that is the owner of this channel (e.g. WebKitBrowser)
        // @param enabled: Enable or disable the throughput of data through this channel (e.g. true)
        // @retval ERROR_UNKNOWN_KEY: Failed to scan
        virtual Core::hresult Channel(const string& name, const bool enabled) = 0;

        // @brief Enable the given channel, disabling all other not immune channels
        // @param name: Callsign that is the owner of this channel (e.g. WebKitBrowser)
        // @retval ERROR_UNKNOWN_KEY: Failed to scan
        virtual Core::hresult Select(const string& name) = 0;

        // @property
        // @brief Check the status of the requested channel
        // @param name: Server name, if omitted, status of all configured channels is returned (e.g. WebKitBrowser)
        // @param servers: List of configured servers
        // @retval ERROR_UNKNOWN_KEY: Could not find the designated channel
        virtual Core::hresult Status(const Core::OptionalType<string>& name /* @index */, IChannelIterator*& channels /* @out @extract */) const = 0;
    };

} // namespace Exchange

}
