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

    /* @json @uncompliant:collapsed */
    struct EXTERNAL ITimeZone : virtual public Core::IUnknown {
        enum { ID = ID_TIMEZONE };

        /* @event @uncompliant:collapsed */
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_TIMEZONE_NOTIFICATION };

            // Signal that the TimeZone has been changed for the system
            // @brief TimeZone was set for the system
            // @param timeZone the new TimeZone
            virtual void TimeZoneChanged(const string& timeZone) = 0;
      };

      virtual uint32_t Register(ITimeZone::INotification* sink) = 0;
      virtual uint32_t Unregister(ITimeZone::INotification* sink) = 0;

      // @property
      // @brief TimeZone for system
      // @param value: timezone
      virtual uint32_t TimeZone(string& timeZone /* @out */) const = 0;
      virtual uint32_t TimeZone(const string& timeZone) = 0;
    };

} // namespace Exchange
} // namespace WPEFramework
