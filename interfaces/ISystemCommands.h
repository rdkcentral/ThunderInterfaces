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
    struct EXTERNAL ISystemCommands : virtual public Core::IUnknown {

        enum { ID = ID_SYSTEMCOMMAND };

        // @brief Resets a USB device
        // @description With this method a USB device can be reset using USBFS_RESET ioctl command
        // @param device: USB device to reset (e.g. /dev/usb/001)
        // @retval ERROR_GENERAL Failed to reset USB device
        // @retval ERROR_UNAVAILABLE Unknown USB device
        virtual Core::hresult USBReset(const string& device) = 0;
    };
}
}
