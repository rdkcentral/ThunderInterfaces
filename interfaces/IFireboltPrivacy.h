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

    /* @json 1.0.0*/
    struct EXTERNAL IFireboltPrivacy : virtual public Core::IUnknown {
        enum { ID = ID_FIREBOLT_PRIVACY };
        enum StorageLocation : uint8_t {
            Disk,
            InMemory,
        };


        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_FIREBOLT_PRIVACY_NOTIFICATION };
            ~INotification() override = default;

            // @brief Notifies that Allow Resume points value change
            /* @text:OnAllowResumePointsChanged */
            virtual void OnAllowResumePointsChanged(const bool value) = 0;

        };
        struct entitlements {
                string entitlements;
                string startTime;
                string endTime;
        };

        ~IFireboltPrivacy() override = default;

        // Pushing notifications to interested sinks
        virtual Core::hresult Register(IFireboltPrivacy::INotification* sink) = 0;
        virtual Core::hresult Unregister(IFireboltPrivacy::INotification* sink) = 0;

        // @brief Provides Current resume watch status
        // @text:AllowResumePoints
        virtual Core::hresult GetAllowResumePoints(const string& appId, bool& allow /* @out */) const = 0;
        // @brief sets the current resume watch status
        // @text:SetAllowResumePoints
        virtual Core::hresult SetAllowResumePoints(const string& appId, const bool& value ) = 0;

        // @brief sets the current resume watch status
        // @text:SignIn
        virtual Core::hresult SignIn(const string& appId, const entitlements& entitilements) = 0;
        // @property
        // @brief Get the storage location
        // @text: GetStorageLocation1
        virtual Core::hresult GetStorageLocation(StorageLocation& value /* @out */) const = 0;
    };
}
}
