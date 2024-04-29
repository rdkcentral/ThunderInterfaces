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

    struct EXTERNAL IFireboltContentProgress : virtual public Core::IUnknown {

        enum { ID = ID_FIREBOLT_CONTENTPROGRESS };

        struct EXTERNAL IAppResumePoints : virtual public Core::IUnknown {

            enum { ID = ID_FIREBOLT_CONTENTPROGRESS_APPRESUMEPOINTS };

            struct ResumePointInfo {
                string AssetId /* @brief ID of the asset (e.g. partner.com/entity/123) */;
                uint16_t Current /* @brief Position in seconds where the asset was paused (e.g. 125) */;
                uint16_t Duration /* @brief Duration of the asset in seconds (e.g. 5400), zero for live content */;
                uint64_t WatchedOn /* @brief Date/time when the assed was paused (in epoch) (e.g. 1714395197) */;
            };

            using IResumePointInfoIterator = RPC::IIteratorType<ResumePointInfo, ID_FIREBOLT_CONTENTPROGRESS_APPRESUMEPOINTS_RESUMEPOINTINFO_ITERATOR>;

            struct EXTERNAL INotification : virtual public Core::IUnknown {

                enum { ID = ID_FIREBOLT_CONTENTPROGRESS_APPRESUMEPOINTS_NOTIFICATION };

                virtual void PermitChanged() = 0;
                virtual void ResumePointChanged() = 0;
            };

            virtual Core::hresult Register(INotification* sink) = 0;
            virtual Core::hresult Unregister(const INotification* sink) = 0;

            virtual Core::hresult Permit(const bool allow) = 0;
            virtual Core::hresult IsPermitted(bool& allowed /* @out */) const = 0;

            virtual Core::hresult Update(const ResumePointInfo& resumePoint) = 0;

            virtual Core::hresult Catalogue(IResumePointInfoIterator*& resumePoints /* @out */) const = 0;
        };

        virtual Core::hresult AppResumePoints(const string& appId, IAppResumePoints*& appResumePoints /* @out */) = 0;
    };

    namespace JSONRPC {

        /* @json 1.0.0 */
        struct EXTERNAL IFireboltContentProgress {

            virtual ~IFireboltContentProgress() = default;

            using ResumePointInfo = Exchange::IFireboltContentProgress::IAppResumePoints::ResumePointInfo;
            using IResumePointInfoIterator = RPC::IIteratorType<ResumePointInfo, 0>;

            // @event
            struct EXTERNAL INotification {

                virtual ~INotification() = default;

                // @text OnPermitChanged
                // @brief Notifies that permision for resume points value has been changed
                // @param appId: ID of the applocation for which this notification relates to
                // @param allow: Allow or deny use of resume points
                virtual void OnPermitChanged(const string& appId /* @index */, const bool allow) = 0;

                // @text OnResumePointChanged
                // @brief Notifies that a resume point has been added, updated or removed
                // @param appId: ID of the application for which this notification relates to
                virtual void OnResumePointChanged(const string& appId /* @index */) = 0;
            };

            // @text PermitResumePoints
            // @brief Sets resume point permission
            // @details AppID shall be passed through the security token.
            // @param allow: Allow or deny use of resume points
            // @retval ERROR_PRIVILIGED_REQUEST: App security errors
            virtual Core::hresult PermitResumePoints(const Core::JSONRPC::Context& context, const bool allow) const = 0;

            // @text UpdateResumePoint
            // @brief Adds, updates or removes a resume point for/from an asset
            // @details AppID shall be passed through the security token.
            //          Note that setting WatchedOn field to 0 removes the resume point.
            // @param resumePoint: Details of the resume point to add, update or remove
            // @retval ERROR_BAD_REQUEST: Resume point details were invalid
            // @retval ERROR_ILLEGAL_STATE: Resume points are not permitted
            // @retval ERROR_PRIVILIGED_REQUEST: App security errors
            virtual Core::hresult UpdateResumePoint(const Core::JSONRPC::Context& context, const ResumePointInfo& resumePoint) = 0;

            // @text ResumePoints
            // @brief Retrieves a list of resume points
            // @details AppID shall be passed through the security token.
            // @param resumePoints: List of resume points
            // @retval ERROR_ILLEGAL_STATE: Resume points are not permitted
            // @retval ERROR_PRIVILIGED_REQUEST: App security errors
            virtual Core::hresult ResumePoints(const Core::JSONRPC::Context& context, IResumePointInfoIterator*& resumePoints /* @out */) const = 0;
        };

    } // namespace JSONRPC

} // namespace Exchange

}
