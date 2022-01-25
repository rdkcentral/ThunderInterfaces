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

struct EXTERNAL IMessageControl : virtual public Core::IUnknown {
  virtual ~IMessageControl() = default;
  enum { ID = ID_MESSAGE_CONTROL };

  enum MessageType : uint8_t {
    Tracing = 0,
    Logging = 1,
    WarningReporting = 2,
  };

  /* @event */
  struct EXTERNAL INotification : virtual public Core::IUnknown {
    enum { ID = ID_MESSAGE_CONTROL_NOTIFICATION };
    virtual ~INotification() = default;
    virtual void ReceiveRawMessage(MessageType type, const string &category,
                                   const string &module, const string &fileName,
                                   uint16_t lineNumber, uint64_t timestamp,
                                   const string &message) = 0;
  };

  virtual void RegisterOutputNotification(IMessageControl::INotification *notification) = 0;
  virtual void UnregisterOutputNotification(const IMessageControl::INotification *notification) = 0;

  virtual uint32_t Configure(PluginHost::IShell *service) = 0;
  virtual void RegisterConnection(const uint32_t id) = 0;
  virtual void UnregisterConnection(const uint32_t id) = 0;

  virtual uint32_t EnableMessage(MessageType type, const string &moduleName,
                                 const string &categoryName,
                                 const bool enable) = 0;

  virtual uint32_t ActiveMessages(const bool first, MessageType &type /*@out*/,
                                  string &moduleName /*@out*/,
                                  string &categoryName /*@out*/,
                                  bool &enable /*@out*/) = 0; // rename
};

} // namespace Exchange
} // namespace WPEFramework
