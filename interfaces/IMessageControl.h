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
  enum { ID = ID_MESSAGE_CONTROL };

  enum MessageType : uint8_t {
    Tracing = 0,
    Logging = 1,
    WarningReporting = 2,
  };

  virtual ~IMessageControl() = default;

  virtual void Start() = 0;
  virtual void Activated(const uint32_t id) = 0;
  virtual void Deactivated(const uint32_t id) = 0;
  virtual void Configure(const bool isBackground, const string &configuration,
                         const string &volatilePath) = 0;

  virtual uint32_t EnableMessage(MessageType type,
                                 const string &moduleName,
                                 const string &categoryName,
                                 const bool enable) = 0;
};

} // namespace Exchange
} // namespace WPEFramework
