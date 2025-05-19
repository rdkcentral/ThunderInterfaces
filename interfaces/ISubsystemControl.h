/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2021 Metrological
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

// @stubgen:include <plugins/ISubSystem.h>

namespace Thunder {

namespace Exchange {

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL ISubsystemControl : virtual public Core::IUnknown {

        enum { ID = ID_SUBSYSTEM_CONTROL };

        // @brief Activates a subsystem
        // @description This method allows a subsystem to be activated from the outside. This is usefull in case Thunder can not determine the availability of a subsystem but it needs to be triggered from the outside.
        // @param subsystem: Subsystem to activate (e.g. network)
        // @param configuration: A JSON string that holds the information applicable to the subsystem to be activated
        // @retval ERROR_BAD_REQUEST: Setting a subsystem to disabled is not supported
        virtual Core::hresult Activate(const PluginHost::ISubSystem::subsystem subsystem, const Core::OptionalType<string>& configuration /* @opaque */) = 0;

        // @brief Deactivates a subsystem
        // @description This method allows a subsystem to be deactivated from the outside. This is usefull in case Thunder can not determine the availability of a subsystem but it needs to be triggered from the outside.
        // @param subsystem: Subsystem to deactivate (e.g. network)
        virtual Core::hresult Deactivate(const PluginHost::ISubSystem::subsystem subsystem) = 0;

    };

} // namespace Exchange

}