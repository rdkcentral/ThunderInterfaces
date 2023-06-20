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

 // @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
	namespace Exchange {

        /* @json */
        struct EXTERNAL IZigWave : virtual public Core::IUnknown {
            enum { ID = ID_ZIGWAVE };

            // @property
            // @brief To allow new devices to the network, the controller should be placed
            //        into an accepting mode. By enabling this mode, the controller can 
            //        accept new devices.
            // @param enabled (true) or disable (false) the accepting mode.
            // 
            /* @alt accept */
            virtual uint32_t Permutable(const uint32_t address /* @index */, bool& enabled /* @out */) const = 0;
            virtual uint32_t Permutable(const uint32_t address /* @index */, const bool enabled) = 0;

            // @property
            // @brief To allow new devices to the network, the controller should be placed
            //        into an accepting mode. By enabling this mode, the controller can 
            //        accept new devices.
            // @param enabled (true) or disable (false) the accepting mode.
            // 
            virtual uint32_t Device(const uint32_t id /* @index */, string& metadata /* @out */) const = 0;

            // @brief All devices currently available
            // @return devices: array of ids from the available devices.
            /* @json:omit */
            virtual uint32_t Devices(RPC::IValueIterator*& devices /* @out */) const = 0;

            // @brief Bind the *out* from the soure to the *in* of the destination
            // @return: The success of the binding action.
            virtual uint32_t Bind(const uint32_t source, const uint32_t destination) = 0;

            // @brief Unbind the *out* from the soure to the *in* of the destination
            // @return: The success of the unbinding action.
            virtual uint32_t Unbind(const uint32_t source, const uint32_t destination) = 0;
        };
    }
}
