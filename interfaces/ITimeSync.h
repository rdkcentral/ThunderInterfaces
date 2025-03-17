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

namespace Thunder {

namespace Exchange {

    // @json 1.0.0 @text:legacy_lowercase
    // This interface gives direct access to a time synchronize / update
    struct EXTERNAL ITimeSync : virtual public Core::IUnknown {

        enum { ID = ID_TIMESYNC };

        struct TimeInfo {
            string time /* @brief Synchronized time (in ISO8601 format); empty string if the time has never been synchronized (e.g. 2019-05-07T07:20:26Z) */;
            Core::OptionalType<string> source /* @brief The synchronization source like an NTP server (e.g. ntp://example.com) */;
        };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum { ID = ID_TIMESYNC_NOTIFICATION };

            // @brief Signals a time change
            // @description Some change happened with respect to the Network
            // @alt:deprecated timechange
            virtual void Completed() = 0;
        };

        virtual Core::hresult Register(INotification* const notification) = 0;
        virtual Core::hresult Unregister(const INotification* const notification) = 0;

        // @brief Synchronizes time
        // @description Use this method to synchronize the system time with the currently configured time source. If automatic time synchronization is initially disabled or canceled, it will be restarted
        // @retval ERROR_INPROGRESS: Returned when the method is called while previously triggered synchronization is in progress
        // @retval ERROR_INCOMPLETE_CONFIG: Returned when the source configuration is missing or invalid
        virtual Core::hresult Synchronize() = 0;

        // @brief Cancel the time synchronization process
        virtual Core::hresult Cancel() = 0;

        // @property
        // @brief Get the synchronization source
        // @param source: The synchronization source like an NTP server (e.g. ntp://example.com)
        virtual Core::hresult Source(string& source /* @out */) const = 0;

        // @property
        virtual Core::hresult Time(Core::Time& time /* @out */) const = 0;

        // @property
        // @deprecated
        // @brief Most recent synchronized time
        virtual Core::hresult SyncTime(TimeInfo& info /* @out */) const = 0;
    };

} // namespace Exchange

}
