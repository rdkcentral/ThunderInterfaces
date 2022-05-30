/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 RDK Management
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

    // This interface gives direct access to a Virtual Keyboard
    // It allows controlling Virtual Keyboard as well as getting input from it

    struct EXTERNAL IVirtualKeyboard : virtual public Core::IUnknown {
        enum { ID = ID_VIRTUAL_KEYBOARD };

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_VIRTUAL_KEYBOARD_NOTIFICATION };

            // Signal changes on the subscribed namespace
            virtual void AppendText(const string& text) = 0;
            virtual void EraseTextFromEnd(const unsigned characters) = 0;
            virtual void Closed(const string& callsign) = 0;
        };

        virtual void Register(IVirtualKeyboard::INotification* sink) = 0;
        virtual void Unregister(IVirtualKeyboard::INotification* sink) = 0;

        virtual bool Open(const string& callsign) = 0;
        virtual void Close(const string& callsign) = 0;
    };
}
}
