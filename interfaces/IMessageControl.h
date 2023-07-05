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

// @insert <com/IIteratorType.h>

namespace WPEFramework {

namespace Exchange {

// @json
struct EXTERNAL IMessageControl : virtual public Core::IUnknown {

    enum { ID = ID_MESSAGE_CONTROL };

    enum messagetype : uint8_t {
        TRACING        = 1,
        LOGGING        = 2,
        REPORTING      = 3,
        STANDARD_OUT   = 4,
        STANDARD_ERROR = 5
    };

    struct Control {
        messagetype type /* @brief Type of message */;
        string category /* @brief Name of the message category (e.g. Information) */;
        string module /* @brief Name of the module the message is originating from (e.g. Plugin_BluetoothControl) */;
        bool enabled /* @brief Denotes if the control is enabled (true) or disabled (false) */;
    };

    using IControlIterator = RPC::IIteratorType<Control, ID_MESSAGE_CONTROL_ITERATOR>;

    // @brief Enables/disables a message control
    // @param type Message type
    // @param module Name of the module the message is originating from (e.g. Plugin_BluetoothControl)
    // @param category Name of the message category (e.g. Information)
    // @param enabled Denotes if control should be enabled (true) or disabled (false)
    virtual uint32_t Enable(const messagetype type, const string& category, const string& module, const bool enabled) = 0;

    // @property
    // @brief Retrieves a list of current message controls
    virtual uint32_t Controls(IControlIterator*& control /* @out */) const = 0;
  };

} // namespace Exchange
} // namespace WPEFramework
