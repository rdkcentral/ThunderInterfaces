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

namespace WPEFramework {
namespace Exchange {

struct EXTERNAL IMessageControl : virtual public Core::IUnknown {

    ~IMessageControl() override = default;
  
    enum { ID = ID_MESSAGE_CONTROL };

    enum MessageType : uint8_t {
        Tracing = 0,
        Logging = 1,
    };

    struct EXTERNAL ICallback : virtual public Core::IUnknown {

        ~ICallback() override = default;

        enum { ID = ID_MESSAGE_CONTROL_CALLBACK };

        virtual void Message(const MessageType type, const string& category,
                             const string& module, const string& fileName,
                             const uint16_t lineNumber, const string& className,
                             const uint64_t timeStamp, const string& message) = 0;
    };

    virtual uint32_t Configure(ICallback* callback) = 0;

    virtual uint32_t Attach(const uint32_t id) = 0;
    virtual uint32_t Detach(const uint32_t id) = 0;

    virtual uint32_t Enable(
        const MessageType type, 
        const string& moduleName,
        const string& categoryName,
        const bool enable) = 0;

    virtual uint32_t Setting (
        const bool initialize, 
        MessageType& type /* @out */, 
        string& category /* @out */,
        string& module /* @out */,
        bool& enabled /* @out */) = 0;
};

} // namespace Exchange
} // namespace WPEFramework
