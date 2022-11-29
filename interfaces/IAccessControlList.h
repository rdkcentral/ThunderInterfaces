/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
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

    struct EXTERNAL IAccessControlList : virtual public Core::IUnknown {
        enum { ID = ID_ACCESS_CONTROL_LIST };

        enum mode : uint8_t {
            BLOCKED,
            ALLOWED
        };

        virtual uint32_t Assign(const string& origin, const string& role) = 0;
        virtual uint32_t Revoke(const string& origin, const string& role) = 0;

        struct EXTERNAL IIterator : virtual public Core::IUnknown {
            enum { ID = ID_ACCESS_CONTROL_LIST_ITERATOR };

            virtual void Reset() = 0;
            virtual bool IsValid() const = 0;
            virtual bool Next() = 0;

            virtual string Callsign() const = 0;
            virtual IAccessControlList::mode Mode() const = 0;
            virtual RPC::IStringIterator* Methods() const = 0;
        };

        virtual uint32_t Set(const string& role, const IAccessControlList::mode& mode, const IIterator* plugins) = 0;
        virtual uint32_t Unset(const string& role) = 0;
    };
}
}
