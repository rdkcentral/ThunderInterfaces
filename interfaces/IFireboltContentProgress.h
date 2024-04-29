/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 Metrological
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

    /* @json 1.0.0 */
    struct EXTERNAL IFireboltContentProgress : virtual public Core::IUnknown {

        enum { ID = ID_FIREBOLT_CONTENTPROGRESS };

		struct ResumePointInfo {
			string AssetId /* @brief ID of the asset (e.g. partner.com/entity/123) */;
			uint16_t Current /* @brief Position in seconds where the asset was paused (e.g. 125) */;
            uint16_t Duration /* @brief Duration of the asset in seconds (e.g. 5400), zero for live content */;
            string WatchedOn /* @optional @brief Date/time when the assed was paused (ISO 8601 Date/Time) (e.g. 2021-04-23T18:25:43.511Z) */;
            bool IsCompleted /* @optional @brief Whether or not this viewing is considered complete as per the app's definition thereof */;
        };

		using IResumePointInfoIterator = RPC::IIteratorType<ResumePointInfo, ID_FIREBOLT_CONTENTPROGRESS_RESUMEPOINTINFO_ITERATOR>;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum { ID = ID_FIREBOLT_CONTENTPROGRESS_NOTIFICATION };

            // @text OnPermitChanged
            // @brief Notifies that permision for resume points value has been changed
            // @param appId: ID of the applocation for which this notification relates to
            // @param allow: Allow or deny use of resume points
            virtual void OnPermitChanged(const string& appId /* @index */, const bool allow) = 0;

            // @text OnResumePointChanged
            // @brief Notifies that a resume point has been added, changed or removed
            // @param appId: ID of the application for which this notification relates to
            // @param assetId: ID of the asset of the resume point that was modified (e.g. partner.com/entity/123)
            virtual void OnResumePointChanged(const string& appId /* @index */, const string& assetId) = 0;
        };

        // Pushing notifications to interested sinks
        virtual Core::hresult Register(INotification* sink) = 0;
        virtual Core::hresult Unregister(const INotification* sink) = 0;

        // @property
        // @text Permit
        // @brief Current status of resuming permissions
        // @details Allows to opt-out from storing progress
        // @param appId: ID of the application
        // @param value: Allow or deny use of resume points
        // @retval ERROR_PRIVILIGED_REQUEST: App security errors
        virtual Core::hresult Permit(const string& appId /* @index */, bool& allow /* @out */) const = 0;
        virtual Core::hresult Permit(const string& appId /* @index */, const bool allow) = 0;

        // @property
        // @text ResumePoint
        // @brief Resume point details
        // @details Adds, updates or removes a resume point from/to an asset.
        //          Set Current and Duration fileds to 0 to remove the resume point.
        // @param appId: ID of the application
        // @param resumePoint: Details of the resume point to add, update or remove
        // @retval ERROR_BAD_REQUEST: App ID or the resume point details were invalid
        // @retval ERROR_ILLEGAL_STATE: Resume points are not permitted
        // @retval ERROR_PRIVILIGED_REQUEST: App security errors
        virtual Core::hresult ResumePoint(const string& appId /* @index */, const ResumePointInfo& resumePoint) = 0;

        // @property
        // @text ResumePoints
        // @brief List of resume points
        // @param appId: ID of the application
        // @param resumePoints: List of resume points
        // @retval ERROR_BAD_REQUEST: App ID was invalid
        // @retval ERROR_ILLEGAL_STATE: Resume points are not permitted
        // @retval ERROR_PRIVILIGED_REQUEST: App security errors
        virtual Core::hresult ResumePoints(const string& appId /* @index */, IResumePointInfoIterator*& resumePoints /* @out */) const = 0;
    };

} // namespace Exchange

}
