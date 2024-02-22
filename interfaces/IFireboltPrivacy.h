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

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_FIREBOLT_PRIVACY_NOTIFICATION };
            ~INotification() override = default;

            // @brief Notifies that Allow Resume points value change
            /* @alt:OnAllowResumePointsChanged */
            virtual void OnAllowResumePointsChanged(const bool value) = 0;

        };

        ~IFireboltPrivacy() override = default;

        // Pushing notifications to interested sinks
        virtual uint32_t Register(IFireboltPrivacy::INotification* sink) = 0;
        virtual uint32_t Unregister(IFireboltPrivacy::INotification* sink) = 0;

        // @property
        // @brief Provides Current resume watch status
        // @alt:AllowResumePoints
        virtual uint32_t AllowResumePoints(bool& allow /* @out */) const = 0;

        // @brief Set resume watch status
        // @alt:SetAllowResumePoints
        virtual uint32_t SetAllowResumePoints(const bool& value ) = 0;
    };
}
}
