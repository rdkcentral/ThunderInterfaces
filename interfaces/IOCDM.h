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

enum OCDM_RESULT : uint32_t {
    OCDM_SUCCESS = 0,
    OCDM_S_FALSE = 1,
    OCDM_MORE_DATA_AVAILABLE = 2,
    OCDM_INTERFACE_NOT_IMPLEMENTED = 3,
    OCDM_BUFFER_TOO_SMALL = 4,
    OCDM_INVALID_ACCESSOR = 0x80000001,
    OCDM_KEYSYSTEM_NOT_SUPPORTED = 0x80000002,
    OCDM_INVALID_SESSION = 0x80000003,
    OCDM_INVALID_DECRYPT_BUFFER = 0x80000004,
    OCDM_OUT_OF_MEMORY = 0x80000005,
    OCDM_METHOD_NOT_IMPLEMENTED = 0x80000006,
    OCDM_FAIL = 0x80004005,
    OCDM_INVALID_ARG = 0x80070057,
    OCDM_SERVER_INTERNAL_ERROR = 0x8004C600,
    OCDM_SERVER_INVALID_MESSAGE = 0x8004C601,
    OCDM_SERVER_SERVICE_SPECIFIC = 0x8004C604,
    OCDM_BUSY_CANNOT_INITIALIZE = 0x8004DD00
};

// ISession defines the interface towards a DRM context that can decrypt data
// using a given key.
struct ISession : virtual public Core::IUnknown {
    enum KeyStatus : uint32_t {
        Usable = 0,
        Expired,
        Released,
        OutputRestricted,
        OutputRestrictedHDCP22,
        OutputDownscaled,
        StatusPending,
        InternalError,
        HWError
    };

    // ICallback defines the callback interface to receive
    // events originated from the session.
    struct ICallback : virtual public Core::IUnknown {
        enum { ID = ID_SESSION_CALLBACK };

        ~ICallback() override = default;

        // Event fired when a key message is successfully created.
        virtual void OnKeyMessage(const uint8_t* keyMessage /* @in @length:keyLength */, //__in_bcount(f_cbKeyMessage)
            const uint16_t keyLength, //__in
            const std::string& URL) = 0; //__in_z_opt

        // Event fired when MediaKeySession encounters an error.
        virtual void OnError(const int16_t error, const OCDM_RESULT sysError, const std::string& errorMessage) = 0;

        // Event fired on key status update
        virtual void OnKeyStatusUpdate(const uint8_t keyID[] /* @in @length:keyIDLength */,
                                       const uint8_t keyIDLength,
                                       const ISession::KeyStatus status) = 0;

        virtual void OnKeyStatusesUpdated() const = 0;
    };

    enum { ID = ID_SESSION };

    ~ISession(void) override = default;

    // Loads the data stored for the specified session into the cdm object
    virtual OCDM_RESULT Load() = 0;

    // Process a key message response.
    virtual void
    Update(const uint8_t* keyMessage /* @in @length:keyLength */, //__in_bcount(f_cbKeyMessageResponse)
        const uint16_t keyLength)
        = 0; //__in

    // Removes all license(s) and key(s) associated with the session
    virtual OCDM_RESULT Remove() = 0;

    // Provides keysystem-specific metadata of the session
    virtual std::string Metadata() const = 0;

    // Provides keysystem-specific metricdata of the session
    virtual OCDM_RESULT Metricdata(
        uint32_t& bufferSize /* @inout */,
        uint8_t buffer[] /* @out @length:bufferSize */) const
        = 0;

    // Report the current status of the Session with respect to the KeyExchange.
    virtual KeyStatus Status() const = 0;
    virtual KeyStatus Status(const uint8_t keyID[] /* @in @length:keyIDLength */, const uint8_t keyIDLength) const = 0;

    // Lazy Create the decryption buffer
    virtual OCDM_RESULT CreateSessionBuffer(string& bufferID /* @out */ ) = 0;

    // Report the name to be used for the Shared Memory for exchanging the
    // Encrypted fragements.
    virtual std::string BufferId() const = 0;

    // Report the name to be used for the Shared Memory for exchanging the
    // Encrypted fragements.
    virtual std::string SessionId() const = 0;

    // We are completely done with the session, it can be closed.
    virtual void Close() = 0;

    // Let the CDM know playback has stopped in order to disable output protection
    virtual void ResetOutputProtection() = 0;

    // During instantiation a callback is set, here we can decouple.
    virtual void Revoke(ISession::ICallback* callback) = 0;
};

struct ISessionExt : virtual public Core::IUnknown {
    enum { ID = ID_SESSION_EXTENSION };

    enum LicenseTypeExt { Invalid = 0,
        LimitedDuration,
        Standard };

    enum SessionStateExt {
        LicenseAcquisitionState = 0,
        InactiveDecryptionState,
        ActiveDecryptionState,
        InvalidState
    };

    virtual uint32_t SessionIdExt() const = 0;

    // Report the name to be used for the Shared Memory for exchanging the
    // Encrypted fragements.
    virtual std::string BufferIdExt() const = 0;

    virtual OCDM_RESULT SetDrmHeader(const uint8_t drmHeader[] /* @in @length:drmHeaderLength */,
        uint16_t drmHeaderLength)
        = 0;

    virtual OCDM_RESULT GetChallengeDataExt(uint8_t* challenge /* @inout @length:challengeSize @maxlength:challengeSize */,
        uint16_t& challengeSize /* @inout */,
        uint32_t isLDL)
        = 0;

    virtual OCDM_RESULT CancelChallengeDataExt() = 0;

    virtual OCDM_RESULT StoreLicenseData(const uint8_t licenseData[] /* @in @length:licenseDataSize */,
        uint16_t licenseDataSize,
        uint8_t* secureStopId /* @out @length:16 */)
        = 0;

    virtual OCDM_RESULT SelectKeyId(const uint8_t keyLength,
        const uint8_t keyId[] /* @in @length:keyLength */)
        = 0;


    virtual OCDM_RESULT CleanDecryptContext() = 0;
};

struct IAccessorOCDM : virtual public Core::IUnknown {

    enum { ID = ID_ACCESSOROCDM };

    ~IAccessorOCDM() override = default;

    virtual bool IsTypeSupported(const std::string& keySystem,
        const std::string& mimeType) const = 0;

    // Provides keysystem-specific metadata
    virtual OCDM_RESULT Metadata(const std::string& keySystem, std::string& metadata /* @out */) const = 0;

    // Provides keysystem-specific metricdata
    virtual OCDM_RESULT Metricdata(
        const std::string& keySystem,
        uint32_t& bufferSize /* @inout */,
        uint8_t buffer[] /* @out @length:bufferSize */) const
        = 0;

    // Create a MediaKeySession using the supplied init data and CDM data.
    virtual OCDM_RESULT
    CreateSession(const string& keySystem, const int32_t licenseType,
        const std::string& initDataType, const uint8_t* initData /* @in @length:initDataLength */,
        const uint16_t initDataLength, const uint8_t* CDMData /* @in @length:CDMDataLength */,
        const uint16_t CDMDataLength, ISession::ICallback* callback,
        std::string& sessionId /* @out */, ISession*& session /* @out */)
        = 0;

    // Set Server Certificate
    virtual OCDM_RESULT
    SetServerCertificate(const string& keySystem, const uint8_t* serverCertificate /* @in @length:serverCertificateLength */,
        const uint16_t serverCertificateLength)
        = 0;

    virtual uint64_t GetDrmSystemTime(const std::string& keySystem) const = 0;

    virtual std::string GetVersionExt(const std::string& keySystem) const = 0;

    virtual uint32_t GetLdlSessionLimit(const std::string& keySystem) const = 0;

    virtual bool IsSecureStopEnabled(const std::string& keySystem) = 0;

    virtual OCDM_RESULT EnableSecureStop(const std::string& keySystem,
        bool enable)
        = 0;

    virtual uint32_t ResetSecureStops(const std::string& keySystem) = 0;

    virtual OCDM_RESULT GetSecureStopIds(const std::string& keySystem,
        uint8_t ids[] /* @out @length:idsLength */, uint16_t idsLength,
        uint32_t& count /* @inout */)
        = 0;

    virtual OCDM_RESULT GetSecureStop(const std::string& keySystem,
        const uint8_t sessionID[] /* @in @length:sessionIDLength */,
        uint16_t sessionIDLength, uint8_t* rawData /* @out @length:rawSize */,
        uint16_t& rawSize /* @inout */)
        = 0;

    virtual OCDM_RESULT CommitSecureStop(const std::string& keySystem,
        const uint8_t sessionID[] /* @in @length:sessionIDLength */,
        uint16_t sessionIDLength,
        const uint8_t serverResponse[] /* @in @length:serverResponseLength */,
        uint16_t serverResponseLength)
        = 0;

    virtual OCDM_RESULT DeleteKeyStore(const std::string& keySystem) = 0;

    virtual OCDM_RESULT DeleteSecureStore(const std::string& keySystem) = 0;

    virtual OCDM_RESULT GetKeyStoreHash(const std::string& keySystem,
        uint8_t keyStoreHash[] /* @out @length:keyStoreHashLength */,
        uint16_t keyStoreHashLength)
        = 0;

    virtual OCDM_RESULT GetSecureStoreHash(const std::string& keySystem,
        uint8_t secureStoreHash[] /* @out @length:secureStoreHashLength */,
        uint16_t secureStoreHashLength)
        = 0;
};

class EXTERNAL KeyId {
public:
    static constexpr uint8_t KEY_LENGTH = 16;

    inline KeyId()
        : _status(ISession::StatusPending)
    {
        ::memset(_kid, ~0, sizeof(_kid));
    }
    inline KeyId(const uint8_t kid[], const uint8_t length)
        : _status(ISession::StatusPending)
    {
        uint8_t copyLength(length > sizeof(_kid) ? sizeof(_kid) : length);

        ::memcpy(_kid, kid, copyLength);

        if (copyLength < sizeof(_kid)) {
            ::memset(&(_kid[copyLength]), 0, sizeof(_kid) - copyLength);
        }
    }
    // Microsoft playready XML flavor retrieval of KID
    inline KeyId(const uint32_t a, const uint16_t b, const uint16_t c, const uint8_t d[])
        : _status(ISession::StatusPending)
    {
        // A bit confused on how the mapping of the Microsoft KeyId's should go, looking at the spec:
        // https://msdn.microsoft.com/nl-nl/library/windows/desktop/aa379358(v=vs.85).aspx
        // Some test cases have a little endian byte ordering for the GUID, other a MSB ordering.
        _kid[0] = a & 0xFF;
        _kid[1] = (a >> 8) & 0xFF;
        _kid[2] = (a >> 16) & 0xFF;
        _kid[3] = (a >> 24) & 0xFF;
        _kid[4] = b & 0xFF;
        _kid[5] = (b >> 8) & 0xFF;
        _kid[6] = c & 0xFF;
        _kid[7] = (c >> 8) & 0xFF;

        ::memcpy(&(_kid[8]), d, 8);
    }
    inline KeyId(const KeyId& copy)
        : _status(copy._status)
    {
        ::memcpy(_kid, copy._kid, sizeof(_kid));
    }
    ~KeyId() = default;

    inline KeyId& operator=(const KeyId& rhs)
    {
        _status = rhs._status;
        ::memcpy(_kid, rhs._kid, sizeof(_kid));
        return (*this);
    }

public:
    inline bool IsValid() const
    {
        const KeyId InvalidKey;
        return (operator!=(InvalidKey));
    }
    inline bool operator==(const uint8_t rhs[]) const
    {
        // Hack, in case of PlayReady, the key offered on the interface might be
        // ordered incorrectly, cater for this situation, by silenty comparing with this incorrect value.
        bool equal = false;

        // Regardless of the order, the last 8 bytes should be equal
        if (memcmp(&_kid[8], &(rhs[8]), 8) == 0) {

            // Lets first try the non swapped byte order.
            if (memcmp(_kid, rhs, 8) == 0) {
                // this is a match :-)
                equal = true;
            } else {
                // Let do the byte order alignment as suggested in the spec and see if it matches than :-)
                // https://msdn.microsoft.com/nl-nl/library/windows/desktop/aa379358(v=vs.85).aspx
                uint8_t alignedBuffer[8];
                alignedBuffer[0] = rhs[3];
                alignedBuffer[1] = rhs[2];
                alignedBuffer[2] = rhs[1];
                alignedBuffer[3] = rhs[0];
                alignedBuffer[4] = rhs[5];
                alignedBuffer[5] = rhs[4];
                alignedBuffer[6] = rhs[7];
                alignedBuffer[7] = rhs[6];
                equal = (memcmp(_kid, alignedBuffer, 8) == 0);
            }
        }
        return (equal);
    }    
    inline bool operator!=(const uint8_t rhs[]) const
    {
        return !(operator==(rhs));
    }
    inline bool operator==(const KeyId& rhs) const
    {
        return (operator==(rhs._kid));
    }
    inline bool operator!=(const KeyId& rhs) const
    {
        return !(operator==(rhs));
    }
    inline const uint8_t* Id() const
    {
        return (_kid);
    }
    inline static uint8_t Length()
    {
        return (KEY_LENGTH);
    }
    inline string ToString() const
    {
        const uint8_t HexArray[] = "0123456789ABCDEF";

        string result;
        for (uint8_t teller = 0; teller < sizeof(_kid); teller++) {
            result += HexArray[(_kid[teller] >> 4) & 0x0f];
            result += HexArray[_kid[teller] & 0x0f];
        }
        return (result);
    }
    void Status(ISession::KeyStatus status)
    {
        _status = status;
    }
    ISession::KeyStatus Status() const
    {
        return (_status);
    }

private:
    uint8_t _kid[KEY_LENGTH];
    ISession::KeyStatus _status;
};


} //namespace Exchange
} //namespace Thunder

