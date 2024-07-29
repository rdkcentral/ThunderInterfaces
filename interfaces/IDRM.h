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
/*
 * Metrological has done changes to the original interface definition
 * from Fraunhofer FOKUS
 */
/*
 * Copyright 2014 Fraunhofer FOKUS
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

// For the support of portable data types such as uint8_t.
#include <stdint.h>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

#include <interfaces/Portability.h>
#include <interfaces/DRMHelper.h>

namespace Thunder
{
   namespace PluginHost
   {
      struct IShell;
   }
}

namespace CDMi {

// EME error code to which CDMi errors are mapped. Please
// refer to the EME spec for details of the errors
// https://dvcs.w3.org/hg/html-media/raw-file/tip/encrypted-media/encrypted-media.html
#define MEDIA_KEYERR_UNKNOWN 1
#define MEDIA_KEYERR_CLIENT 2
#define MEDIA_KEYERR_SERVICE 3
#define MEDIA_KEYERR_OUTPUT 4
#define MEDIA_KEYERR_HARDWARECHANGE 5
#define MEDIA_KEYERR_DOMAIN 6

// More CDMi status codes can be defined. In general
// CDMi status codes should use the same PK error codes.

#define CDMi_FAILED(Status) ((CDMi_RESULT)(Status) < 0)
#define CDMi_SUCCEEDED(Status) ((CDMi_RESULT)(Status) >= 0)

/* Media Key status required by EME */
#define MEDIA_KEY_STATUS_USABLE 0
#define MEDIA_KEY_STATUS_INTERNAL_ERROR 1
#define MEDIA_KEY_STATUS_EXPIRED 2
#define MEDIA_KEY_STATUS_OUTPUT_NOT_ALLOWED 3
#define MEDIA_KEY_STATUS_OUTPUT_DOWNSCALED 4
#define MEDIA_KEY_STATUS_KEY_STATUS_PENDING 5
#define MEDIA_KEY_STATUS_KEY_STATUS_MAX KEY_STATUS_PENDING

enum CDMi_RESULT {
    CDMi_SUCCESS = 0,
    CDMi_S_FALSE = 1,
    CDMi_MORE_DATA_AVAILABLE = 2,
    CDMi_INTERFACE_NOT_IMPLEMENTED = 3,
    CDMi_BUFFER_TOO_SMALL = 4,
    CDMi_INVALID_ACCESSOR = 0x80000001,
    CDMi_KEYSYSTEM_NOT_SUPPORTED = 0x80000002,
    CDMi_INVALID_SESSION = 0x80000003,
    CDMi_INVALID_DECRYPT_BUFFER = 0x80000004,
    CDMi_OUT_OF_MEMORY = 0x80000005,
    CDMi_METHOD_NOT_IMPLEMENTED = 0x80000006,
    CDMi_FAIL = 0x80004005,
    CDMi_INVALID_ARG = 0x80070057,
    CDMi_SERVER_INTERNAL_ERROR = 0x8004C600,
    CDMi_SERVER_INVALID_MESSAGE = 0x8004C601,
    CDMi_SERVER_SERVICE_SPECIFIC = 0x8004C604,
    CDMi_BUSY_CANNOT_INITIALIZE = 0x8004DD00,
};

enum LicenseType {
    Temporary,
    PersistentUsageRecord,
    PersistentLicense
};

enum LicenseTypeExt {
    Invalid = 0,
    LimitedDuration,
    Standard
};

enum SessionStateExt {
    LicenseAcquisitionState = 0,
    InactiveDecryptionState,
    ActiveDecryptionState,
    InvalidState
};

enum MediaType {
    Unknown = 0,
    Video,
    Audio,
    Data
};

// ISO/IEC 23001-7 defines two Common Encryption Schemes with Full Sample and Subsample modes
enum EncryptionScheme : uint8_t {
    Clear = 0,
    AesCtr_Cenc,    // AES-CTR mode and Sub-Sample encryption
    AesCbc_Cbc1,    // AES-CBC mode and Sub-Sample encryption
    AesCtr_Cens,    // AES-CTR mode and Sub-Sample + patterned encryption
    AesCbc_Cbcs     // AES-CBC mode and Sub-Sample + patterned encryption + Constant IV
};

// CBCS & CENC3.0 pattern is a number of encrypted blocks followed a number of clear
// blocks after which the pattern repeats.
struct EncryptionPattern {
    uint32_t clear_blocks;
    uint32_t encrypted_blocks;
};

struct SubSampleInfo {
    uint16_t clear_bytes;
    uint32_t encrypted_bytes;
};

struct SampleInfo {
    EncryptionScheme   scheme;          // Encryption scheme used in this sample
    EncryptionPattern pattern;          // Encryption Pattern used in this sample
    uint8_t*           iv;              // Initialization vector(IV) to decrypt this sample
    uint8_t            ivLength;        // Length of IV
    uint8_t*           keyId;           // ID of Key required to decrypt this sample
    uint8_t            keyIdLength;     // Length of KeyId
    uint8_t            subSampleCount;  // Number or Sub-Samples in this sample
    SubSampleInfo*     subSample;       // SubSample mapping - Repeating pair of Clear bytes and Encrypted Bytes representing each subsample.
};

// IStreamProperties to provide information about the current stream
class IStreamProperties {
public:
    virtual ~IStreamProperties (void) = default;

    // Get stream video size
    virtual uint16_t GetHeight() const = 0;
    virtual uint16_t GetWidth() const = 0;

    // Get stream type
    virtual MediaType GetMediaType() const = 0;

    // Deprecated method for backwards compatibility. 
    virtual uint8_t InitLength() const = 0;
};

// IMediaKeySessionCallback defines the callback interface to receive
// events originated from MediaKeySession.
class IMediaKeySessionCallback {
public:
    virtual ~IMediaKeySessionCallback(void) = default;

    // Event fired when a key message is successfully created.
    virtual void OnKeyMessage(
        const uint8_t* f_pbKeyMessage, //__in_bcount(f_cbKeyMessage)
        uint32_t f_cbKeyMessage, //__in
        const char* f_pszUrl)
        = 0; //__in_z_opt

    // Event fired when MediaKeySession encounters an error.
    virtual void OnError(
        int16_t f_nError,
        CDMi_RESULT f_crSysError,
        const char* errorMessage)
        = 0;

    //Event fired on key status update
    virtual void OnKeyStatusUpdate(const char* keyMessage, const uint8_t* buffer, const uint8_t length) = 0;
    virtual void OnKeyStatusesUpdated() const = 0;
};

// IMediaKeySession defines the MediaKeySession interface.
class IMediaKeySession {
public:
    IMediaKeySession(void) = default;
    virtual ~IMediaKeySession(void) = default;

    // Retrieves keysystem-specific metadata of the session
    virtual std::string GetMetadata() const { return std::string(); }

    // Kicks off the process of acquiring a key. A MediaKeySession callback is supplied
    // to receive notifications during the process.
    virtual void Run(
        const IMediaKeySessionCallback* f_piMediaKeySessionCallback)
        = 0; //__in

    // Loads the data stored for the specified session into the cdm object
    virtual CDMi_RESULT Load() = 0;

    // Process a key message response.
    virtual void Update(
        const uint8_t* f_pbKeyMessageResponse, //__in_bcount(f_cbKeyMessageResponse)
        uint32_t f_cbKeyMessageResponse)
        = 0; //__in

    //Removes all license(s) and key(s) associated with the session
    virtual CDMi_RESULT Remove() = 0;

    // Explicitly release all resources associated with the MediaKeySession.
    virtual CDMi_RESULT Close(void) = 0;

    // Return the session ID of the MediaKeySession. The returned pointer
    // is valid as long as the associated MediaKeySession still exists.
    virtual const char* GetSessionId(void) const = 0;

    // Return the key system of the MediaKeySession.
    virtual const char* GetKeySystem(void) const = 0;

    DEPRECATED virtual CDMi_RESULT Decrypt(
        const uint8_t* f_pbSessionKey VARIABLE_IS_NOT_USED,
        uint32_t f_cbSessionKey VARIABLE_IS_NOT_USED,
        const EncryptionScheme encryptionScheme VARIABLE_IS_NOT_USED,
        const EncryptionPattern& pattern VARIABLE_IS_NOT_USED,
        const uint8_t* f_pbIV VARIABLE_IS_NOT_USED,
        uint32_t f_cbIV VARIABLE_IS_NOT_USED,
        uint8_t* f_pbData VARIABLE_IS_NOT_USED,
        uint32_t f_cbData VARIABLE_IS_NOT_USED,
        uint32_t* f_pcbOpaqueClearContent VARIABLE_IS_NOT_USED,
        uint8_t** f_ppbOpaqueClearContent VARIABLE_IS_NOT_USED,
        const uint8_t keyIdLength VARIABLE_IS_NOT_USED,
        const uint8_t* keyId VARIABLE_IS_NOT_USED,
        bool initWithLast15 /*=0*/ VARIABLE_IS_NOT_USED) {

        return (CDMi_METHOD_NOT_IMPLEMENTED);
    }

    virtual CDMi_RESULT Decrypt(
        uint8_t*                 inData,          // Incoming encrypted data
        const uint32_t           inDataLength,    // Incoming encrypted data length
        uint8_t**                outData,         // Outgoing decrypted data
        uint32_t*                outDataLength,   // Outgoing decrypted data length
        const SampleInfo*        sampleInfo,      // Information required to decrypt Sample
        const IStreamProperties* properties) {    // Stream Properties

PUSH_WARNING(DISABLE_WARNING_DEPRECATED_USE)
        return (Decrypt(sampleInfo->keyId, sampleInfo->keyIdLength,
                sampleInfo->scheme, sampleInfo->pattern,
                sampleInfo->iv, sampleInfo->ivLength,
                inData, inDataLength,
                outDataLength, outData,
                sampleInfo->keyIdLength, sampleInfo->keyId,
                properties->InitLength()));
POP_WARNING()
    }

    virtual CDMi_RESULT ReleaseClearContent(
        const uint8_t* f_pbSessionKey,
        uint32_t f_cbSessionKey,
        const uint32_t f_cbClearContentOpaque,
        uint8_t* f_pbClearContentOpaque)
        = 0;

    virtual CDMi_RESULT ResetOutputProtection() { return (CDMi_METHOD_NOT_IMPLEMENTED); }
    virtual CDMi_RESULT SetParameter(const std::string& name VARIABLE_IS_NOT_USED, const std::string& value VARIABLE_IS_NOT_USED) { return (CDMi_METHOD_NOT_IMPLEMENTED); }
};

// IMediaKeySession defines the MediaKeySession interface.
class IMediaKeySessionExt {
public:
    IMediaKeySessionExt(void) = default;
    virtual ~IMediaKeySessionExt(void) = default;

    virtual uint32_t GetSessionIdExt(void) const = 0;

    virtual CDMi_RESULT SetDrmHeader(const uint8_t drmHeader[], uint32_t drmHeaderLength) = 0;

    virtual CDMi_RESULT GetChallengeDataExt(uint8_t* challenge, uint32_t& challengeSize, uint32_t isLDL) = 0;

    virtual CDMi_RESULT CancelChallengeDataExt() = 0;

    virtual CDMi_RESULT StoreLicenseData(const uint8_t licenseData[], uint32_t licenseDataSize, uint8_t* secureStopId) = 0;

    virtual CDMi_RESULT SelectKeyId(const uint8_t keyLength, const uint8_t keyId[]) = 0;

    virtual CDMi_RESULT CleanDecryptContext() = 0;
};

// IMediaKeys defines the MediaKeys interface.
class IMediaKeys {
public:
    IMediaKeys(void) = default;
    virtual ~IMediaKeys(void) = default;

    // Retrieves keysystem-specific metadata
    virtual std::string GetMetadata() const { return std::string(); }

    // Create a MediaKeySession using the supplied init data and CDM data.
    virtual CDMi_RESULT CreateMediaKeySession(
        const std::string& keySystem,
        int32_t licenseType,
        const char* f_pwszInitDataType,
        const uint8_t* f_pbInitData,
        uint32_t f_cbInitData,
        const uint8_t* f_pbCDMData,
        uint32_t f_cbCDMData,
        IMediaKeySession** f_ppiMediaKeySession)
        = 0;

    // Set Server Certificate
    virtual CDMi_RESULT SetServerCertificate(
        const uint8_t* f_pbServerCertificate,
        uint32_t f_cbServerCertificate)
        = 0;

    // Destroy a MediaKeySession instance.
    virtual CDMi_RESULT DestroyMediaKeySession(
        IMediaKeySession* f_piMediaKeySession)
        = 0;
};

// IMediaKeySession defines the MediaKeySessionExt interface.
class IMediaKeysExt {
public:
    IMediaKeysExt(void) = default;
    virtual ~IMediaKeysExt(void) = default;

    virtual uint64_t GetDrmSystemTime() const = 0;

    virtual std::string GetVersionExt() const = 0;

    virtual uint32_t GetLdlSessionLimit() const = 0;

    virtual bool IsSecureStopEnabled() = 0;

    virtual CDMi_RESULT EnableSecureStop(bool enable) = 0;

    virtual uint32_t ResetSecureStops() = 0;

    virtual CDMi_RESULT GetSecureStopIds(
        uint8_t ids[],
        uint16_t idsLength,
        uint32_t& count)
        = 0;

    virtual CDMi_RESULT GetSecureStop(
        const uint8_t sessionID[],
        uint32_t sessionIDLength,
        uint8_t* rawData,
        uint16_t& rawSize)
        = 0;

    virtual CDMi_RESULT CommitSecureStop(
        const uint8_t sessionID[],
        uint32_t sessionIDLength,
        const uint8_t serverResponse[],
        uint32_t serverResponseLength)
        = 0;

    virtual CDMi_RESULT DeleteKeyStore() = 0;

    virtual CDMi_RESULT DeleteSecureStore() = 0;

    virtual CDMi_RESULT GetKeyStoreHash(
        uint8_t secureStoreHash[],
        uint32_t secureStoreHashLength)
        = 0;

    virtual CDMi_RESULT GetSecureStoreHash(
        uint8_t secureStoreHash[],
        uint32_t secureStoreHashLength)
        = 0;
};

struct IMediaSystemMetrics {
    virtual ~IMediaSystemMetrics() = default;

    virtual CDMi_RESULT Metrics (uint32_t& bufferLength, uint8_t buffer[]) const = 0;
};

struct IMediaSessionMetrics {
    virtual ~IMediaSessionMetrics() = default;

    virtual CDMi_RESULT Metrics (uint32_t& bufferLength, uint8_t buffer[]) const = 0;
};

// @stop
struct ISystemFactory {
    virtual ~ISystemFactory() = default;
    virtual IMediaKeys* Instance() = 0;
    virtual const char* KeySystem() const = 0;
    virtual const std::vector<std::string>& MimeTypes() const = 0;
    virtual void Initialize(const Thunder::PluginHost::IShell * shell, const std::string& configline) = 0;
    virtual void Deinitialize(const Thunder::PluginHost::IShell * shell) = 0;
    virtual CDMi_RESULT Enable() = 0;
    virtual CDMi_RESULT Disable() = 0;
};

template <typename IMPLEMENTATION>
class SystemFactoryType : public ISystemFactory {
private:
    SystemFactoryType() = delete;
    SystemFactoryType(const SystemFactoryType<IMPLEMENTATION>&) = delete;
    SystemFactoryType<IMPLEMENTATION>& operator=(const SystemFactoryType<IMPLEMENTATION>&) = delete;

public:
    SystemFactoryType(const std::vector<std::string>& list)
        : _mimes(list)
        , _instance()
    {
    }
    ~SystemFactoryType() override = default;

public:
    IMediaKeys* Instance() override
    {
        return (&_instance);
    }
    const std::vector<std::string>& MimeTypes() const override
    {
        return (_mimes);
    }
    const char* KeySystem() const override
    {
        return (typeid(IMPLEMENTATION).name());
    }

    void Initialize(const Thunder::PluginHost::IShell * shell, const std::string& configline) override
    {
        Initialize(shell, configline, std::integral_constant<bool, HasOnShellAndSystemInitialize<IMPLEMENTATION>::Has>());
    }
    void Deinitialize(const Thunder::PluginHost::IShell * shell) override
    {
        Deinitialize(shell, std::integral_constant<bool, HasOnShellAndSystemDeinitialize<IMPLEMENTATION>::Has>());
    }

    CDMi_RESULT Enable() override
    {
        return (Enable(std::integral_constant<bool, HasEnable<IMPLEMENTATION>::Has>()));
    }
    CDMi_RESULT Disable() override
    {
        return (Disable (std::integral_constant<bool, HasDisable<IMPLEMENTATION>::Has>()));
    }

private:
    template <typename T>
    struct HasOnShellAndSystemInitialize {
        template <typename U, void (U::*)(const Thunder::PluginHost::IShell *, const std::string&)>
        struct SFINAE {
        };
        template <typename U>
        static uint8_t Test(SFINAE<U, &U::Initialize>*);
        template <typename U>
        static uint32_t Test(...);
        static const bool Has = sizeof(Test<T>(0)) == sizeof(uint8_t);
    };

    template <typename T>
    struct HasOnShellAndSystemDeinitialize {
        template <typename U, void (U::*)(const Thunder::PluginHost::IShell *)>
        struct SFINAE {
        };
        template <typename U>
        static uint8_t Test(SFINAE<U, &U::Deinitialize>*);
        template <typename U>
        static uint32_t Test(...);
        static const bool Has = sizeof(Test<T>(0)) == sizeof(uint8_t);
    };


    void Initialize(const Thunder::PluginHost::IShell * service, const std::string& configline, std::true_type) {
        _instance.Initialize(service, configline);
    }

    void Initialize(const Thunder::PluginHost::IShell *, const std::string&, std::false_type) {
    }

    void Deinitialize(const Thunder::PluginHost::IShell * service, std::true_type) {
        _instance.Deinitialize(service);
    }

    void Deinitialize(const Thunder::PluginHost::IShell *, std::false_type) {
    }

    template <typename T>
    struct HasEnable{
        template <typename U, CDMi_RESULT (U::*)()>
        struct SFINAE {
        };
        template <typename U>
        static uint8_t Test(SFINAE<U, &U::Enable>*);
        template <typename U>
        static uint32_t Test(...);
        static const bool Has = sizeof(Test<T>(0)) == sizeof(uint8_t);
    };

    CDMi_RESULT Enable(std::true_type) {
        return(_instance.Enable());
    }

    CDMi_RESULT Enable(std::false_type) {
        return(CDMi_KEYSYSTEM_NOT_SUPPORTED);
    }

    template <typename T>
    struct HasDisable{
        template <typename U, CDMi_RESULT (U::*)()>
        struct SFINAE {
        };
        template <typename U>
        static uint8_t Test(SFINAE<U, &U::Disable>*);
        template <typename U>
        static uint32_t Test(...);
        static const bool Has = sizeof(Test<T>(0)) == sizeof(uint8_t);
    };

    CDMi_RESULT Disable(std::true_type) {
        return(_instance.Enable());
    }

    CDMi_RESULT Disable(std::false_type) {
        return(CDMi_KEYSYSTEM_NOT_SUPPORTED);
    }

    const std::vector<std::string> _mimes;
    IMPLEMENTATION _instance;
};

} // namespace CDMi

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXTERNAL
#ifdef _MSVC_LANG
__declspec(dllexport) CDMi::ISystemFactory* GetSystemFactory();
#else
__attribute__ ((visibility ("default"))) CDMi::ISystemFactory* GetSystemFactory();
#endif
#else
EXTERNAL CDMi::ISystemFactory* GetSystemFactory();
#endif


#ifdef __cplusplus
}
#endif
