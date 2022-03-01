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
  virtual ~IMessageControl() = default;
  enum { ID = ID_MESSAGE_CONTROL };

  enum MessageType : uint8_t {
    Tracing = 0,
    Logging = 1,
  };

  /* @event */
  struct EXTERNAL INotification : virtual public Core::IUnknown {
    enum { ID = ID_MESSAGE_CONTROL_NOTIFICATION };
    virtual ~INotification() = default;
    virtual void ReceiveRawMessage(const MessageType type, const string &category,
                                   const string &module, const string &fileName,
                                   const uint16_t lineNumber, const uint64_t timestamp,
                                   const string &message) = 0;
  };

  virtual void
  RegisterOutputNotification(IMessageControl::INotification *notification) = 0;
  virtual void UnregisterOutputNotification(
      const IMessageControl::INotification *notification) = 0;

  virtual uint32_t Configure(const bool isBackground, const bool abbreviate,
                             const bool outputToConsole, const bool outputToSysLog,
                             const string &outputFileName,
                             const string &binding, const uint32_t port) = 0;

  virtual void RegisterConnection(const uint32_t id) = 0;
  virtual void UnregisterConnection(const uint32_t id) = 0;

  virtual uint32_t EnableMessage(const MessageType type, const string &moduleName,
                                 const string &categoryName,
                                 const bool enable) = 0;

  virtual uint32_t ActiveMessages(const bool first, MessageType &type /*@out*/,
                                  string &moduleName /*@out*/,
                                  string &categoryName /*@out*/,
                                  bool &enable /*@out*/) = 0;
};

} // namespace Exchange
} // namespace WPEFramework
