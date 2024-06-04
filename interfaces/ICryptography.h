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

    enum CryptographyVault : uint8_t {
        CRYPTOGRAPHY_VAULT_DEFAULT = 0,
        CRYPTOGRAPHY_VAULT_PLATFORM = 1,
        CRYPTOGRAPHY_VAULT_PROVISIONING = 0x10,
        CRYPTOGRAPHY_VAULT_NETFLIX = 0x11
    };

    enum aesmode : uint8_t {
        ECB,
        CBC,
        OFB,
        CFB1,
        CFB8,
        CFB128,
        CTR
    };

    enum hashtype : uint8_t {
        SHA1 = 20,
        SHA224 = 28,
        SHA256 = 32,
        SHA384 = 48,
        SHA512 = 64
    };

    struct EXTERNAL IRandom : virtual public Core::IUnknown {

        enum { ID = ID_CRYPTOGRAPHY_RANDOM };

        // Generates an array of cryptographically strong random bytes
        virtual uint16_t Generate(const uint16_t length, uint8_t data[] /* @out @length:return @maxlength:length */) const = 0;
    };

    struct EXTERNAL IHash : virtual public Core::IUnknown {

        enum { ID = ID_CRYPTOGRAPHY_HASH };

        // Ingest data into the hash calculator (multiple calls possible)
        virtual uint32_t Ingest(const uint32_t length /* @restrict:4M-1 */, const uint8_t data[] /* @in @length:length */) = 0;

        // Calculate the hash from all ingested data
        virtual uint8_t Calculate(const uint8_t maxLength, uint8_t data[] /* @out @length:return @maxlength:maxLength */) = 0;
    };

    struct EXTERNAL ICipher : virtual public Core::IUnknown {

        enum { ID = ID_CRYPTOGRAPHY_CIPHER };

        // If the encryption or decryption failed due to a lack of storage space, a negative length is returned.
        // The abs(length) indicates the number of bytes required in the output buffer to succefully complete.
        // Note that encryption might require extra output buffer space to succeed (may need to include padding and/or the IV).

        // Encrypt data
        virtual int32_t Encrypt(const uint8_t ivLength, const uint8_t iv[] /* @in @length:ivLength */,
                                const uint32_t inputLength /* @restrict:4M-1 */, const uint8_t input[] /* @in @length:inputLength */,
                                const uint32_t maxOutputLength, uint8_t output[] /* @out @length:return @maxlength:maxOutputLength */) const = 0;

        // Decrypt data
        virtual int32_t Decrypt(const uint8_t ivLength, const uint8_t iv[] /* @in @length:ivLength */,
                                const uint32_t inputLength /* @restrict:4M-1 */, const uint8_t input[] /* @in @length:inputLength */,
                                const uint32_t maxOutputLength, uint8_t output[] /* @out @length:return @maxlength:maxOutputLength */) const = 0;
    };

    struct EXTERNAL IDiffieHellman : virtual public Core::IUnknown {

        enum { ID = ID_CRYPTOGRAPHY_DIFFIEHELLMAN };

        // Generate DH private/public keys
        virtual uint32_t Generate(const uint8_t generator, const uint16_t modulusSize, const uint8_t modulus[]/* @in @length:modulusSize */ ,
                                  uint32_t& privKeyId /* @out */, uint32_t& pubKeyId /* @out */) = 0;

        // Calculate a DH shared secret
        virtual uint32_t Derive(const uint32_t privateKey, const uint32_t peerPublicKeyId, uint32_t& secretId /* @out */) = 0;
    };

    struct EXTERNAL IPersistent : virtual public Core::IUnknown {

        enum { ID = ID_CRYPTOGRAPHY_PERSISTENT };

        enum keytype : uint8_t {
            AES128,
            AES256,
            HMAC128,
            HMAC160,
            HMAC256
        };

        // Check if a named key exists in peristent storage
        virtual uint32_t Exists(const string& locator, bool& result /* @out */) const = 0;

        // Load persistent key details to vault
        virtual uint32_t Load(const string& locator, uint32_t& id /* @out */) = 0;

        // Create a new key on persistent storage
        virtual uint32_t Create(const string& locator, const keytype keyType, uint32_t& id /* @out */) = 0;

        // To explicitly flush resources at the backend
        virtual uint32_t Flush() = 0;
    };

    struct EXTERNAL IVault : virtual public Core::IUnknown {

        enum { ID = ID_CRYPTOGRAPHY_VAULT };

        // Operations manipulating items in the vault
        // ---------------------------------------------------

        // Return size of a vault data blob
        // (-1 if the blob exists in the vault but is not extractable and 0 if the ID does not exist)
        virtual uint16_t Size(const uint32_t id) const = 0;

        // Import unencrypted data blob into the vault (returns blob ID)
        // Note: User IDs are always greater than 0x80000000, values below 0x80000000 are reserved for implementation-specific internal data blobs.
        virtual uint32_t Import(const uint16_t length, const uint8_t blob[] /* @in @length:length */) = 0;

        // Export unencrypted data blob out of the vault (returns blob ID), only public blobs are exportable
        virtual uint16_t Export(const uint32_t id, const uint16_t maxLength, uint8_t blob[] /* @out @length:return @maxlength:maxLength */) const = 0;

        // Set encrypted data blob in the vault (returns blob ID)
        virtual uint32_t Set(const uint16_t length, const uint8_t blob[] /* @in @length:length */) = 0;

        // Get encrypted data blob out of the vault (data identified by ID, returns size of the retrieved data)
        virtual uint16_t Get(const uint32_t id, const uint16_t maxLength, uint8_t blob[] /* @out @length:return @maxlength:maxLength */) const = 0;

        // Generates a random data blob of specified length in the vault (returns blob ID)
        virtual uint32_t Generate(const uint16_t length) = 0;

        // Delete a data blob from the vault
        virtual bool Delete(const uint32_t id) = 0;


        // Crypto operations using the vault for key storage
        // -----------------------------------------------------

        // Retrieve a HMAC calculator
        virtual IHash* HMAC(const hashtype hashType, const uint32_t keyId) = 0;

        // Retrieve an AES encryptor/decryptor
        virtual ICipher* AES(const aesmode aesMode, const uint32_t keyId) = 0;

        // Retrieve a Diffie-Hellman key creator
        virtual IDiffieHellman* DiffieHellman() = 0;
    };

    struct EXTERNAL IDeviceObjects : virtual public Core::IUnknown {

        enum { ID = ID_CRYPTOGRAPHY_DEVICEOBJECTS };

        static IDeviceObjects* Instance();

        // Locates the vault and the ID of a device-bound named blob
        virtual uint32_t Id(const string& label, IVault*& vault /* @out */) = 0;
    };

    struct EXTERNAL ICryptography : virtual public Core::IUnknown {

        enum { ID = ID_CRYPTOGRAPHY };

        static ICryptography* Instance(const std::string& connectionPoint);

        // Retrieve a random number generator
        virtual IRandom* Random() = 0;

        // Retrieve a hash calculator
        virtual IHash* Hash(const hashtype hashType) = 0;

        // Retrieve a vault (TEE identified by ID)
        virtual IVault* Vault(const CryptographyVault id) = 0;
    };

}
}
