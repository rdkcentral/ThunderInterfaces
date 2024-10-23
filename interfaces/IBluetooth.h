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

            enum devicetype : uint8_t {
                CLASSIC,
                LOW_ENERGY,
                LOW_ENERGY_RANDOM
            };

            enum scanmode : uint8_t {
                GENERAL,
                LIMITED
            };

            using btaddress = string;
            using uuid = string;
            using pairingcapabilities = IBluetooth::IDevice::pairingcapabilities;

            struct device {
                btaddress address /* @brief Bluetooth address */;
                devicetype type /* @brief Bluetooth device type */;
            };

            struct adapterinfo {
                uint8_t id /* @brief Adapter ID */;
                string interface /* @brief Interface */;
                btaddress address /* @brief Bluetooth address */;
                devicetype type /* @brief Bluetooth device type */;
                uint8_t version /* @brief Version */;
                Core::OptionalType<uint32_t> manufacturer /* Manufacturer ID */;
                Core::OptionalType<uint32_t> cod /* @text:class @brief Class of Device (CoD) value */;
                Core::OptionalType<string> name /* @brief Name */;
                Core::OptionalType<string> shortName /* @brief Short name */;
            };

            using IUUIDIterator = RPC::IIteratorType<uuid, 0>;
            using IDeviceIterator = RPC::IIteratorType<device, 0>;
            using IAdapterIterator = RPC::IIteratorType<uint8_t, 0>;

            // @event
            struct EXTERNAL INotification {

                enum devicestate : uint8_t {
                    PAIRING,
                    PAIRED,
                    UNPAIRED,
                    CONNECTED,
                    DISCONNECTED
                };

                enum disconnectreason : uint8_t {
                    CONNECTION_TIMEOUT,
                    AUTHENTICATION_FAILURE,
                    REMOTE_LOW_ON_RESOURCES,
                    REMOTE_POWERED_OFF,
                    TERMINATED_BY_REMOTE,
                    TERMINATED_BY_HOST
                };

                virtual ~INotification() = default;

                // @brief Notifies of entering the discoverable state.
                virtual void DiscoverableStarted(const devicetype type, const scanmode mode, Core::OptionalType<bool>& connectable) = 0;

                // @brief Notifies of leaving the discoverable state
                virtual void DiscoverableComplete(const devicetype type) = 0;

                // @brief Notifies of scan start
                virtual void ScanStarted(const devicetype type, const scanmode mode) = 0;

                // @brief Notifies of scan completion
                virtual void ScanComplete(const devicetype type) = 0;

                // @brief Notifies of device state changes
                virtual void DeviceStateChange(const btaddress& address, const devicetype type,
                    const devicestate state, const Core::OptionalType<disconnectreason>& disconnectReason) = 0;

                // @brief Notifies of a PIN code request
                // @description Upon receiving this event the client is required to respond with "providepincode" call
                //      in order to complete the pairing procedure. The PIN code value would typically be collected by
                //      prompting the end-user. If the client fails to respond before the pairing timeout elapses the
                //      pairing procedure will be aborted.
                virtual void PINCodeRequest(const btaddress& address, const devicetype type) = 0;

                // @brief Notifies of a passkey request
                // @description Upon receiving this event the client is required to respond with "providepasskey" call
                //      in order to complete the pairing procedure. The passkey value would typically be collected by
                //      prompting the end-user. If the client fails to respond before the pairing timeout elapses the
                //      pairing procedure will be aborted.
                virtual void PassKeyRequest(const btaddress& address, const devicetype type) = 0;

                // @brief Notifies of a passkey confirmation request.
                // @description Upon receiving this event the client is required to respond with "passkeyconfirm" call
                //      in order to complete the pairing procedure. The passkey confirmation would typically be collected
                //      by prompting the end-user. If the client fails to respond before the pairing timeout elapses the
                //      pairing procedure will be aborted.
                // @param secret A six-digit decimal number passkey sent by the remote device for confirmation;
                //      may be 0 for a simple accept/forbid paring request
                virtual void PassKeyConfirmRequest(const btaddress& address, const devicetype type, const string& secret) = 0;
            };

            virtual ~IBluetoothControl() = default;

            // @brief Starts advertising (or inquiry scanning), making the local interface visible by nearby Bluetooth devices
            // @retval ERROR_INPROGRESS Discoverable state of selected type is already in progress
            virtual Core::hresult SetDiscoverable(const devicetype type,
                const Core::OptionalType<scanmode>& mode /* @default:GENERAL */,
                const Core::OptionalType<bool>& connectable,
                const Core::OptionalType<uint16_t>& duration /* @default:30 */) = 0;

            // @brief Stops advertising (or inquiry scanning) operation
            // @retval ERROR_ILLEGAL_STATE Adapter is in not discoverable state of selected type
            virtual Core::hresult StopDiscoverable(const devicetype type) = 0;

            // @brief Starts active discovery (or inquiry) of nearby Bluetooth devices
            // @retval ERROR_INPROGRESS Scan of selected type is already in progress
            virtual Core::hresult Scan(const devicetype type,
                const Core::OptionalType<scanmode>& mode /* @default:GENERAL */,
                const Core::OptionalType<bool>& connectable,
                const Core::OptionalType<uint16_t>& duration /* @default:10 */) = 0;

            // @brief Stops discovery (or inquiry) operation
            // @reval ERROR_ILLEGAL_STATE Scan of selected type is not in progress
            virtual Core::hresult StopScanning(const devicetype type) = 0;

            // @brief Connects to a Bluetooth device
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ILLEGAL_STATE Device not paired
            // @retval ERROR_ALREADY_CONNECTED Device already connected
            // @retval ERROR_REQUEST_SUBMITTED Device has not been connected but will be automatically connected when available
            virtual Core::hresult Connect(const btaddress& address, const devicetype type) = 0;

            // @brief Disconnects from a connected Bluetooth device
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ALREADY_RELEASED Device not connected
            // @retval ERROR_REQUEST_SUBMITTED Device is currently not connected but it's autoconnection mode has been disabled
            virtual Core::hresult Disconnect(const btaddress& address, const devicetype type) = 0;

            // @brief Pairs a Bluetooth device
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ALREADY_CONNECTED Device already paired
            virtual Core::hresult Pair(const btaddress& address, const devicetype type,
                const Core::OptionalType<pairingcapabilities>& capabilities /* @default:NO_INPUT_NO_OUTPUT */,
                const Core::OptionalType<uint16_t>& timeout) = 0;

            // @brief Unpairs a paired Bluetooth device
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ALREADY_RELEASED Device not paired
            virtual Core::hresult Unpair(const btaddress& address, const devicetype type) = 0;

            // @brief Aborts pairins operation
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ILLEGAL_STATE Device not currently pairing
            virtual Core::hresult AbortPairing(const btaddress& address, const devicetype type) = 0;

            // @brief Provides a PIN-code for authentication during a legacy pairing process
            // @description This method should be called upon receiving a "pincoderequest" event during a legacy pairing
            //      process. If the specified PIN-code is incorrect the pairing process will be aborted.
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ILLEGAL_STATE Device not currently pairing or PIN code has not been requested
            virtual Core::hresult ProvidePINCode(const btaddress& address, const devicetype type, const string& secret) = 0;

            // @brief Provides a passkey for authentication during a pairing process
            // @description This method should be called upon receiving a "passkeyrequest" event during pairing process.
            //      If the specified passkey is incorrect or empty the pairing process will be aborted.
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ILLEGAL_STATE Device not currently pairing or a passkey has not been requested
            virtual Core::hresult ProvidePassKey(const btaddress& address, const devicetype type, const string& secret) = 0;

            // @brief Confirms a passkey for authentication during a pairing processs
            // @description This method should be called upon receiving a passkeyconfirmationrequest event during a pairing
            //      process. If the confirmation is negative the pairing process will be aborted.
            // @retval ERROR_UNKNOWN_KEY Unknown device
            // @retval ERROR_ILLEGAL_STATE Device is currently not pairing or passkey confirmation has not been requested
            virtual Core::hresult ConfirmPassKey(const btaddress& address, const devicetype type, const bool isCorrect) = 0;

            // @brief Forgets previously seen Bluetooth device
            // @description The device will no longer be listed and its status tracked. If the device is connected
            //      and/or paired it will be disconnected and unpaired.
            // @retval ERROR_UNKNOWN_KEY Unknown device
            virtual Core::hresult Forget(const btaddress& address, const devicetype type) = 0;

            // @brief Retrieves a list of known remote Bluetooth devices
            virtual Core::hresult GetDeviceList(IDeviceIterator*& devices /* @out */) const = 0;

            // @brief Retrieves detailed information about a known Bluetooth device
            // @retval ERROR_UNKNOWN_KEY Unknown device
            virtual Core::hresult GetDeviceInfo(const btaddress& address, const devicetype type,
                Core::OptionalType<string>& name /* @out */,
                Core::OptionalType<uint32_t>& cod /* @out @text:class @brief Class of Device (CoD) value */,
                Core::OptionalType<uint16_t>& appearance /* @out */,
                Core::OptionalType<IUUIDIterator*>& services /* @out */,
                bool& paired /* @out */,
                bool& connected /* @out */) const = 0;

            // @property
            // @brief List of local Bluetooth adapters
            virtual Core::hresult Adapters(IAdapterIterator*& adapters /* @out */) const = 0;

            // @property
            // @brief Local Bluetooth adapter information
            // @retval ERROR_UNKNOWN_KEY Unknown adapter device
            virtual Core::hresult Adapter(const uint8_t adapter /* @index */, adapterinfo& result /* @out */) const = 0;
        };


        // Old interface, defined for backward compatibility

        // @json 1.0.0 @text:legacy_lowercase
        struct EXTERNAL IBluetoothControlLegacy {

            using btaddress = IBluetoothControl::btaddress;
            using devicetype = IBluetoothControl::devicetype;
            using IAddressIterator = RPC::IIteratorType<IBluetoothControl::btaddress, RPC::ID_EXTERNAL_INTERFACE_OFFSET>;

            struct deviceinfo {
                btaddress address /* @brief Bluetooth address */;
                devicetype type /* @brief Bluetooth device type */;
                Core::OptionalType<string> name /* @brief Name */;
                Core::OptionalType<uint32_t> cod /* @text:class @brief Class of Device (CoD) value */;
                Core::OptionalType<uint16_t> appearance /* @brief Appearance value (LE only) */;
                Core::OptionalType<string> services /* @opaque */ /* @brief Array of supported service UUIDs */;
                bool paired /* @brief Denotes if currently paired */;
                bool connected /* @brief Denotes if currently connected */;
            };

            virtual ~IBluetoothControlLegacy() = default;

            // @property @deprecated
            // @brief List of known remote Bluetooth devices
            virtual Core::hresult Devices(IAddressIterator*& devices /* @out */) const = 0;

            // @property @deprecated
            // @brief Remote Bluetooth device information
            // @retval ERROR_UNKNOWN_KEY Unknown device
            virtual Core::hresult Device(const btaddress& deviceAddress /* @index */, deviceinfo& result /* @out */) const = 0;
        };
    }

} // namespace Exchange

}
