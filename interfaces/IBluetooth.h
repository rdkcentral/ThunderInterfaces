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

// @insert <com/IIteratorType.h>

namespace Thunder {

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
                ADDRESS_BREDR,
                ADDRESS_LE_PUBLIC,
                ADDRESS_LE_RANDOM
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

            DEPRECATED virtual void Update() { }
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


    namespace JSONRPC {

        // @json 1.0.0 @text:legacy_lowercase
        struct EXTERNAL IBluetoothControl {

            virtual ~IBluetoothControl() = default;

            enum class adaptertype : uint8_t {
                CLASSIC,
                LOW_ENERGY,
                DUAL
            };

            enum class devicetype : uint8_t {
                CLASSIC = IBluetooth::IDevice::type::ADDRESS_BREDR,
                LOW_ENERGY = IBluetooth::IDevice::type::ADDRESS_LE_PUBLIC,
                LOW_ENERGY_RANDOM = IBluetooth::IDevice::type::ADDRESS_LE_RANDOM
            };

            enum class scantype : uint8_t {
                CLASSIC,
                LOW_ENERGY
            };

            enum class scanmode : uint8_t {
                GENERAL,
                LIMITED
            };

            enum class devicestate : uint8_t {
                PAIRING,
                PAIRED,
                UNPAIRED,
                CONNECTED,
                DISCONNECTED
            };

            enum class disconnectreason : uint8_t {
                CONNECTION_TIMEOUT,
                AUTHENTICATION_FAILURE,
                REMOTE_LOW_ON_RESOURCES,
                REMOTE_POWERED_OFF,
                TERMINATED_BY_REMOTE,
                TERMINATED_BY_HOST
            };


            using pairingcapabilities = IBluetooth::IDevice::pairingcapabilities;

            struct device {
                string address /* @brief Bluetooth address */;
                devicetype type /* @brief Bluetooth device type */;
            };

            /* DEPRECATED */ struct deviceinfo {
                string address /* @brief Bluetooth address */;
                IBluetoothControl::devicetype type /* @brief Device type */;
                Core::OptionalType<string> name /* @brief Name */;
                Core::OptionalType<uint32_t> cod /* @text:class @brief Class of The device (CoD) value */;
                Core::OptionalType<uint16_t> appearance /* @brief Appearance value (LE only) */;
                Core::OptionalType<string> services /* @opaque */ /* @brief Array of supported service UUIDs */;
                bool paired /* @brief Denotes if currently paired */;
                bool connected /* @brief Denotes if currently connected */;
            };

            struct adapterinfo {
                uint8_t id /* @brief Adapter ID number */;
                string interface /* @brief Interface name */;
                string address /* @brief Bluetooth address */;
                adaptertype type /* @brief Adapter type */;
                uint8_t version /* @brief Version */;
                Core::OptionalType<uint32_t> manufacturer /* Manufacturer ID */;
                Core::OptionalType<uint32_t> cod /* @text:class */ /* @brief Class of Device (CoD) value */;
                Core::OptionalType<string> name /* @brief Name */;
                Core::OptionalType<string> shortName /* @brief Short name */;
            };

            using IUUIDIterator = RPC::IIteratorType<string, 0>;
            using IDeviceIterator = RPC::IIteratorType<device, 0>;
            using IAdapterIterator = RPC::IIteratorType<uint8_t, 0>;
            using IAddressIterator = RPC::IIteratorType<string, 0>;

            // @event
            struct EXTERNAL INotification {

                virtual ~INotification() = default;

                // @statuslistener
                // @brief Reports entering the discoverable state
                virtual void DiscoverableStarted(const scantype type, const scanmode mode,
                    const Core::OptionalType<bool>& connectable) = 0;

                // @brief Reports leaving the discoverable state
                virtual void DiscoverableComplete(const scantype type) = 0;

                // @statuslistener
                // @brief Reports start of scanning
                virtual void ScanStarted(const scantype type, const scanmode mode) = 0;

                // @brief Reports end of scanning
                virtual void ScanComplete(const scantype type) = 0;

                // @statuslistener
                // @brief Reports device state changes
                virtual void DeviceStateChanged(const string& address, const devicetype type,
                    const devicestate state, const Core::OptionalType<disconnectreason>& disconnectReason) = 0;
            };

            // @event
            struct EXTERNAL ISecurityNotification {

                virtual ~ISecurityNotification() = default;

                // @brief Notifies of a PIN code request during authenticated BR/EDR legacy pairing process
                // @description Upon receiving this event the client is required to respond with "providePinCode" call
                //      in order to complete the pairing procedure. The PIN code value is typically collected by
                //      prompting the end-user on the local device. If the client fails to respond before the pairing
                //      timeout elapses the pairing procedure will be aborted.
                virtual void PINCodeRequest(const string& address, const devicetype type) = 0;

                // @brief Notifies of a user confirmation request during authenticated BR/EDR SSP pairing process
                // @description Upon receiving this event the client is required to respond with "confirmPasskey" call
                //      in order to complete the pairing procedure. The passkey confirmation is typically collected
                //      by prompting the end-user on the local device. If the client fails to respond before the pairing
                //      timeout elapses the pairing procedure will be aborted.
                // @param secret A six-digit decimal number sent by the remote device to be presented to the end-user
                //      for confirmation on the local device. The passkey may be omitted for simple yes/no paring.
                virtual void PasskeyConfirmRequest(const string& address, const devicetype type,
                    const Core::OptionalType<uint32_t>& secret) = 0;

                // @brief Notifies of a passkey supply request during authenticated LE pairing process
                // @description Upon receiving this event the client is required to respond with "providePasskey" call
                //      in order to complete the pairing procedure. The passkey value is typically collected by
                //      prompting the end-user on the local device. If the client fails to respond before the pairing
                //      timeout elapses the pairing procedure will be aborted.
                virtual void PasskeyRequest(const string& address, const devicetype type) = 0;

                // @brief Notifies of a passkey presentation request during authenticated LE pairing process
                // @description Upon receiving this event the client is required to display the passkey on the local
                //      device. The end-user on the remote device will need to enter this passkey to complete the
                //      pairing procedure. If end-user fails to respond before the pairing timeout elapses the pairing
                //      procedure will be aborted.
                // @param secret A six-digit decimal number to be displayed on the local device
                virtual void PasskeyDisplayRequest(const string& address, const devicetype type, const uint32_t secret) = 0;
            };


            // @brief Starts LE advertising or BR/EDR inquiry scanning, making the local interface visible for
            //      nearby Bluetooth devices
            // @retval ERROR_UNAVAILABLE The adapter does not support selected discovery type
            // @retval ERROR_INPROGRESS Discoverable state of selected type is already in progress
            virtual Core::hresult SetDiscoverable(const scantype type,
                const Core::OptionalType<scanmode>& mode /* @default:GENERAL */,
                const Core::OptionalType<bool>& connectable /* @default:true */,
                const Core::OptionalType<uint16_t>& duration /* @default:30 */) = 0;

            // @brief Stops LE advertising or BR/EDR inquiry scanning operation
            // @retval ERROR_UNAVAILABLE The adapter does not support selected discovery type
            // @retval ERROR_ILLEGAL_STATE The adapter is in not discoverable state of selected type
            virtual Core::hresult StopDiscoverable(const scantype type) = 0;

            // @brief Starts LE active discovery or BR/EDR inquiry of nearby Bluetooth devices
            // @retval ERROR_UNAVAILABLE The adapter does not support selected scan type
            // @retval ERROR_INPROGRESS Scan of selected type is already in progress
            virtual Core::hresult Scan(const scantype type,
                const Core::OptionalType<scanmode>& mode /* @default:GENERAL */,
                const Core::OptionalType<uint16_t>& duration /* @default:12 */) = 0;

            // @brief Stops LE discovery or BR/EDR inquiry operation
            // @retval ERROR_UNAVAILABLE The adapter does not support selected scan type
            // @retval ERROR_ILLEGAL_STATE Scan of selected type is not in progress
            virtual Core::hresult StopScanning(const scantype type) = 0;

            // @brief Connects to a Bluetooth device, additionally the device will start becoming automatically reconnected
            // @retval ERROR_UNKNOWN_KEY The device is not known
            // @retval ERROR_ILLEGAL_STATE The device is not paired
            // @retval ERROR_ALREADY_CONNECTED The device is already connected
            // @retval ERROR_REQUEST_SUBMITTED The device has not been connected but will be automatically
            //         connected when it becomes available
            virtual Core::hresult Connect(const string& address, const devicetype type) = 0;

            // @brief Disconnects from a connected Bluetooth device, additionally the device will not be automatically
            //        reconnected anymore
            // @retval ERROR_UNKNOWN_KEY The device is not known
            // @retval ERROR_ALREADY_RELEASED The device is not connected
            // @retval ERROR_REQUEST_SUBMITTED The device is currently not connected but it's automatic reconnection
            //         mode has been disabled
            virtual Core::hresult Disconnect(const string& address, const devicetype type) = 0;

            // @brief Pairs a Bluetooth device
            // @retval ERROR_UNKNOWN_KEY The device is not known
            // @retval ERROR_ALREADY_CONNECTED The device is already paired
            virtual Core::hresult Pair(const string& address, const devicetype type,
                const Core::OptionalType<pairingcapabilities>& capabilities /* @default:NO_INPUT_NO_OUTPUT */,
                const Core::OptionalType<uint16_t>& timeout /* @default:10 */) = 0;

            // @brief Unpairs a paired Bluetooth device
            // @retval ERROR_UNKNOWN_KEY The device is not known
            // @retval ERROR_ALREADY_RELEASED The device is not paired
            virtual Core::hresult Unpair(const string& address, const devicetype type) = 0;

            // @brief Aborts pairins operation
            // @retval ERROR_UNKNOWN_KEY The device is not knowne
            // @retval ERROR_ILLEGAL_STATE The device not currently pairing
            virtual Core::hresult AbortPairing(const string& address, const devicetype type) = 0;

            // @brief Provides a PIN-code for authentication during a legacy pairing process
            // @description This method should be called upon receiving a "pinCodeRequest" event during a legacy pairing
            //      process. If the specified PIN-code is incorrect the pairing process will be aborted.
            // @retval ERROR_UNKNOWN_KEY The device is not known
            // @retval ERROR_ILLEGAL_STATE The device not currently pairing or a PIN code has not been requested
            virtual Core::hresult ProvidePINCode(const string& address, const devicetype type, const string& secret /* @restrict:16 */) = 0;

            // @brief Confirms a passkey for authentication during a BR/EDR SSP pairing processs
            // @description This method should be called upon receiving a passkeyConfirmationRequest event during a pairing
            //      process. If the confirmation is negative the pairing process will be aborted.
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ILLEGAL_STATE The device is currently not pairing or passkey confirmation has not been requested
            virtual Core::hresult ConfirmPasskey(const string& address, const devicetype type, const bool accept) = 0;

            // @brief Provides a passkey for authentication during a pairing process
            // @description This method should be called upon receiving a "passkeyRequest" event during pairing process.
            //      If the specified passkey is incorrect or empty the pairing process will be aborted.
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ILLEGAL_STATE The device not currently pairing or a passkey has not been requested
            virtual Core::hresult ProvidePasskey(const string& address, const devicetype type, const uint32_t secret) = 0;

            // @brief Forgets a previously seen Bluetooth device
            // @description The device will no longer be listed and its status tracked. If needed the device will be
            //      disconnected and unpaired beforehand.
            // @retval ERROR_UNKNOWN_KEY The device is not known
            virtual Core::hresult Forget(const string& address, const devicetype type) = 0;

            // @brief Retrieves a list of known remote Bluetooth devices
            virtual Core::hresult GetDeviceList(IDeviceIterator*& devices /* @out */) const = 0;

            // @brief Retrieves detailed information about a known Bluetooth device
            // @retval ERROR_UNKNOWN_KEY The device is not known
            virtual Core::hresult GetDeviceInfo(string& address /* @inout */, devicetype& type /* @inout */,
                Core::OptionalType<string>& name /* @out */,
                Core::OptionalType<uint32_t>& cod /* @out @text:class */ /* @brief Class of The device (CoD) value */,
                Core::OptionalType<uint16_t>& appearance /* @out */,
                Core::OptionalType<IUUIDIterator*>& services /* @out */,
                bool& paired /* @out */,
                bool& connected /* @out */) const = 0;

            // @property
            // @brief List of local Bluetooth adapters
            virtual Core::hresult Adapters(IAdapterIterator*& adapters /* @out */) const = 0;

            // @property
            // @brief Local Bluetooth adapter information
            // @retval ERROR_UNKNOWN_KEY The adapter ID is invalid
            virtual Core::hresult Adapter(const uint8_t adapter /* @index */, adapterinfo& info /* @out */) const = 0;


            // The legacy API below works with LowEnergy devices only and thus is deprecated

            // @property @deprecated
            // @brief List of known remote Bluetooth LE devices
            DEPRECATED virtual Core::hresult Devices(IAddressIterator*& devices /* @out */) const = 0;

            // @property @deprecated
            // @brief Remote Bluetooth LE device information
            // @retval ERROR_UNKNOWN_KEY The device is not known
            DEPRECATED virtual Core::hresult Device(const string& deviceAddress /* @index */, deviceinfo& info /* @out */) const = 0;
        };

    } // namespace JSONRPC

} // namespace Exchange

}
