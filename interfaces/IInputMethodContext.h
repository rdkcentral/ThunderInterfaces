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

    // This interface gives direct access to the context of application input fields
    // It allows injecting text etc.

    struct EXTERNAL IInputMethodContext : virtual public Core::IUnknown {
        enum { ID = ID_INPUT_METHOD_CONTEXT };

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_INPUT_METHOD_CONTEXT_NOTIFICATION };

            virtual void FocusedIn() = 0;
            virtual void FocusedOut() = 0;
        };

        virtual void Register(IInputMethodContext::INotification* sink) = 0;
        virtual void Unregister(IInputMethodContext::INotification* sink) = 0;

        virtual void AppendText(const string& text) = 0;
        virtual void EraseTextFromEnd(const unsigned characters) = 0;
        virtual void FilterKeyEvents(bool enable) = 0; // filters out all key events if enabled
    };

}
}
