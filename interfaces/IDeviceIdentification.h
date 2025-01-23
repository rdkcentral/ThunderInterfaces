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

namespace Thunder {

namespace Exchange {

    // @json 1.0.0 @uncompliant:collapsed @text:legacy_lowercase
    struct EXTERNAL IDeviceIdentification : virtual public Core::IUnknown {

        enum { ID = ID_DEVICEIDENTIFICATION };

        struct DeviceInfo {
            string firmwareVersion /* @brief Version of the device firmware (e.g. 1.0.0) */;
            string chipset /* @brief Chipset used for this device (e.g. BCM2711) */;
            string deviceID /* @brief Device ID (e.g. WPEuCfrLF45) */;
        };

        // @property
        // @text deviceidentification
        // @brief Get device paltform specific information
        virtual Core::hresult Identification(DeviceInfo& info /* @out */) const = 0;

    };

} // namespace Exchange

}