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

    // @stubgen:omit
    struct EXTERNAL IBluetooth : virtual public Core::IUnknown {
        enum { ID = ID_BLUETOOTH };

        struct EXTERNAL IDevice : virtual public Core::IUnknown {
            enum { ID = ID_BLUETOOTH_DEVICE };

            struct EXTERNAL IClassic : virtual public Core::IUnknown {
                enum { ID = ID_BLUETOOTH_DEVICE_CLASSIC };

                struct EXTERNAL ISecurityCallback : virtual public Core::IUnknown {
                    enum { ID = ID_BLUETOOTH_DEVICE_CLASSIC_SECURITYCALLBACK };

                    virtual void PINCodeRequest() = 0; 
                };

                virtual void PINCode(const string& pinCode) = 0;

                virtual uint32_t Callback(ISecurityCallback* callback) = 0;
            };

            struct EXTERNAL ILowEnergy : virtual public Core::IUnknown {
                enum { ID = ID_BLUETOOTH_DEVICE_LOWENERGY };

                virtual uint16_t Appearance() const = 0;
            };

            struct EXTERNAL IIterator : virtual public Core::IUnknown {
                enum { ID = ID_BLUETOOTH_DEVICE_ITERATOR };

                virtual void Reset() = 0;
                virtual bool IsValid() const = 0;
                virtual bool Next() = 0;
                virtual IDevice* Current() = 0;
            };

            struct EXTERNAL ICallback : virtual public Core::IUnknown {
                enum { ID = ID_BLUETOOTH_DEVICE_CALLBACK };

                virtual void Updated() = 0;
            };

            struct EXTERNAL ISecurityCallback : virtual public Core::IUnknown {
                enum { ID = ID_BLUETOOTH_DEVICE_SECURITYCALLBACK };

                virtual void PasskeyRequest() = 0;
                virtual void PasskeyConfirmRequest(const uint32_t passkey) = 0;
            };

            enum type : uint8_t {
                ADDRESS_BREDR /*@text:Classic */,
                ADDRESS_LE_PUBLIC /*@text:LowEnergy */,
                ADDRESS_LE_RANDOM  /*@text:LowEnergyRandom */
            };

            enum pairingcapabilities : uint8_t {
                DISPLAY_ONLY,
                DISPLAY_YES_NO,
                KEYBOARD_ONLY,
                NO_INPUT_NO_OUTPUT,
                KEYBOARD_DISPLAY
            };

            virtual type Type() const = 0;

            virtual bool IsValid() const = 0;
            DEPRECATED bool IsBonded() const { return (IsPaired()); }
            virtual bool IsPaired() const = 0;
            virtual bool IsConnected() const = 0;

            virtual string LocalId() const = 0;
            virtual string RemoteId() const = 0;
            virtual string Name() const = 0;
            virtual uint32_t Class() const = 0;
            virtual bool IsServiceSupported(const string& uuid) const = 0;

            virtual uint32_t Pair(const pairingcapabilities capabilities, const uint16_t timeout /* sec */) = 0;
            virtual uint32_t AbortPairing() = 0;
            virtual uint32_t Unpair() = 0;

            virtual void Passkey(const uint32_t passkey) = 0;
            virtual void ConfirmPasskey(const bool confirm) = 0;

            virtual uint32_t Connect() = 0;
            virtual uint32_t Disconnect() = 0;

            virtual uint32_t Callback(ICallback* callback) = 0;
            virtual uint32_t Callback(ISecurityCallback* callback) = 0;
        };

        struct EXTERNAL IClassic : virtual public Core::IUnknown {
            enum { ID = ID_BLUETOOTH_CLASSIC };

            struct EXTERNAL INotification : virtual public Core::IUnknown {
                enum { ID = ID_BLUETOOTH_CLASSIC_NOTIFICATION };

                virtual void ScanningStateChanged() = 0;
                virtual void InquiryScanningStateChanged() = 0;
            };

            virtual uint16_t Interface() const = 0;

            virtual bool IsScanning(bool& limited) const = 0;
            virtual uint32_t Scan(const bool limited, const uint16_t duration /* sec */) = 0;
            virtual uint32_t StopScanning() = 0;

            virtual bool IsInquiryScanning(bool& limited) const = 0;
            virtual uint32_t InquiryScan(const bool limited, const uint16_t duration /* sec */) = 0;
            virtual uint32_t StopInquiryScanning() = 0;

            virtual uint32_t Register(INotification* notification) = 0;
            virtual uint32_t Unregister(INotification* notification) = 0;
        };

        struct EXTERNAL ILowEnergy : virtual public Core::IUnknown {
            enum { ID = ID_BLUETOOTH_LOWENERGY };

            struct EXTERNAL INotification : virtual public Core::IUnknown {
                enum { ID = ID_BLUETOOTH_LOWENERGY_NOTIFICATION };

                virtual void ScanningStateChanged() = 0;
                virtual void AdvertisingStateChanged() = 0;
            };

            virtual uint16_t Interface() const = 0;

            virtual bool IsScanning(bool& limited) const = 0;
            virtual uint32_t Scan(const bool limited, const uint16_t duration /* sec */) = 0;
            virtual uint32_t StopScanning() = 0;

            virtual bool IsAdvertising(bool& limited, bool& connectable) const = 0;
            virtual uint32_t Advertise(const bool limited, const bool connectable, const uint16_t duration /* sec */) = 0;
            virtual uint32_t StopAdvertising() = 0;

            virtual uint32_t Register(INotification* notification) = 0;
            virtual uint32_t Unregister(INotification* notification) = 0;
        };

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_BLUETOOTH_NOTIFICATION };

            virtual void Update(IDevice* device) = 0;

            DEPRECATED virtual void Update() = 0;
        };

        virtual uint32_t Register(INotification* notification) = 0;
        virtual uint32_t Unregister(INotification* notification) = 0;

        DEPRECATED virtual bool IsScanning() const = 0;
        DEPRECATED virtual uint32_t Scan(const bool lowEnergy, const uint16_t duration /* sec */) = 0;
        DEPRECATED virtual uint32_t StopScanning() = 0;

        DEPRECATED IDevice* Device(const string& address) { return (Device(address, IDevice::ADDRESS_LE_PUBLIC)); }
        virtual IDevice* Device(const string& address, const IDevice::type type) = 0;

        virtual IDevice::IIterator* Devices() = 0;

        virtual uint32_t ForgetDevice(const string& address, const IDevice::type type) = 0;
    };

} // namespace Exchange

}
