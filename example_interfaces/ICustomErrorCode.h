/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the License);
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

namespace Example {

    // @json 1.0.0
    struct ICustomErrorCode : virtual public Core::IUnknown {

        enum { ID = ID_CUSTOMERRORCODE};

        virtual Core::hresult TriggerCustomError(const int32_t errorcode) const = 0; // note: uin24_t would have been a better match, but as we also want to test overflow errors int32_t is used (otherwise generated code will already block the call)
        virtual Core::hresult TriggerNonCustomError(const uint32_t errorcode) const = 0;
    };

} // namespace Example

}
