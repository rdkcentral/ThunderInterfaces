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

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IBluetoothRemoteControl : virtual public Core::IUnknown {

        enum { ID = ID_BLUETOOTHREMOTECONTROL };

        struct unitmetadata {
            string name /* @brief Name of the unit */;
            Core::OptionalType<string> model /* @brief Model name */;
            Core::OptionalType<string> serial /* @brief Serial number */;
            Core::OptionalType<string> firmware /* @brief Firmware version */;
            Core::OptionalType<string> software /* @brief Software version */;
            Core::OptionalType<string> manufacturer /* @brief Vendor/manufacturer name */;
        };

        // @event
        struct INotification : virtual public Core::IUnknown {

            enum { ID = ID_BLUETOOTHREMOTECONTROL_NOTIFICATION };

            // @statuslistener
            // @brief Signals battery level change
            // @param level Battery level in percent (e.g. 75)
            virtual void BatteryLevelChange(const uint8_t level) = 0;
        };

        virtual Core::hresult Register(INotification* const notification) = 0;
        virtual Core::hresult Unregister(const INotification* const notification) = 0;

        // @brief Assigns a Bluetooth device as a RCU
        // @param address: Address of the Bluetooth device to assign
        // @retval ERROR_UNKNOWN_KEY Device address value is invalid
        // @retval ERROR_ALREADY_CONNECTED A RCU device is already assigned
        virtual Core::hresult Assign(const string& address) = 0;

        // @brief Revokes a Bluetooth device from RCU operation
        // @retval ERROR_ALREADY_RELEASED No device is currently assigned as RCU
        virtual Core::hresult Revoke() = 0;

        // @property
        // @alt-deprecated:address
        // @brief Bluetooth address
        // @retval ERROR_ILLEGAL_STATE The RCU device currently is not assigned
        virtual Core::hresult Device(string& address /* @out */) const = 0;

        // @property
        // @brief Device metadata
        // @alt-deprecated:info
        // @retval ERROR_ILLEGAL_STATE The RCU device currently is not assigned
        virtual Core::hresult Metadata(unitmetadata& info /* @out */) const = 0;

        // @property
        // @brief Battery level
        // @param level Battery level (e.g. 75)
        // @retval ERROR_UNAVAILABLE The device is not connected or does not support battery information
        // @retval ERROR_ILLEGAL_STATE The RCU device currently is not assigned
        virtual Core::hresult BatteryLevel(uint8_t& level /* @out */) const = 0;

        // @property
        // @brief Toggle voice control
        // @retval ERROR_NOT_SUPPORTED The device does not support voice input
        // @retval ERROR_ILLEGAL_STATE The RCU device currently is not assigned
        virtual Core::hresult VoiceControl(bool& value /* @out */) const = 0;
        virtual Core::hresult VoiceControl(const bool value) = 0;
    };

} // namespace Exchange

}
