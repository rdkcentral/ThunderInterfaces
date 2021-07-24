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

    // @json
    struct EXTERNAL ILanguageTag : virtual public Core::IUnknown {
        enum { ID = ID_LANGUAGETAG };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_LANGUAGETAG_NOTIFICATION };

            virtual ~INotification() {}

            // @brief Notify that the Language tag has been changed
            // @param language new LangauageTag value.
            virtual void LanguageChanged(const string& language) = 0;

        };

        virtual ~ILanguageTag() {}

        virtual void Register(ILanguageTag::INotification* sink) = 0;
        virtual void Unregister(const ILanguageTag::INotification* sink) = 0;
        // @property
        // @brief Current application user interface language tag
        // @param language Language string as per RFC5646 (e.g. en)
        virtual uint32_t Language(string& language /* @out */) const = 0;
        virtual uint32_t Language(const string& language) = 0;

    };
}
}
