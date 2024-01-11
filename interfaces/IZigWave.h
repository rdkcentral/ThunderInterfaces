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

            struct Device {
                enum type : uint8_t {
                    END_DEVICE,
                    ROUTER,
                    CONTROLLER
                };

                uint32_t Parent /* @brief address of the Parent */;
                uint32_t Address /* @brief address of the device */;
                type Type /* @brief type of the device */;
                uint16_t Manufacturer  /* @brief manufactured of this device */;
                string Metadata /* metadata associated with this device */;
            };

            struct Controller {
                bool Permutable;
                string Port;
                uint32_t Id;
                uint8_t Major;
                uint8_t Minor;
                uint16_t Nodes;
            };

            using IDeviceIterator = RPC::IIteratorType<Device, ID_ZIGWAVE_DEVICE_ITERATOR>;

            // @property
            // @brief To allow new devices to the network, the controller should be placed
            //        into an accepting mode. By enabling this mode, the controller can 
            //        accept new devices.
            // @param enabled (true) or disable (false) the accepting mode.
            // 
            /* @alt accept */
            virtual Core::hresult Permutable(const uint32_t address /* @index */, bool& enabled /* @out */) const = 0;
            virtual Core::hresult Permutable(const uint32_t address /* @index */, const bool enabled) = 0;

            // @property
            // @brief Get the information of available devices. An id of 0xFFFFFFFF means 
            // all devices available by this plugin.
            // 
            virtual Core::hresult Devices(const uint32_t id /* @index */, IDeviceIterator*& devices /* @out */) const = 0;

            // @brief Bind the *out* from the soure to the *in* of the destination
            // @return: The success of the binding action.
            virtual Core::hresult Bind(const uint32_t source, const uint32_t destination) = 0;

            // @brief Unbind the *out* from the soure to the *in* of the destination
            // @return: The success of the unbinding action.
            virtual Core::hresult Unbind(const uint32_t source, const uint32_t destination) = 0;

            // @brief return the Metadata associated with the controller for this instance.
            // @return: The success of the Metdata action.
            virtual Core::hresult Metadata(Controller& metadata /* @out */) const = 0;
        };
    }
}
