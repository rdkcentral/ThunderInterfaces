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
#include "IDRM.h"

namespace WPEFramework {

namespace Exchange {

    // This interface gives direct access to a OpenCDMi server instance, running as a plugin in the framework.
    struct EXTERNAL IContentDecryption : virtual public Core::IUnknown {
        enum { ID = ID_CONTENTDECRYPTION };

        virtual uint32_t Initialize(PluginHost::IShell* service) = 0;
        virtual void Deinitialize(PluginHost::IShell* service) = 0;
        virtual uint32_t Reset() = 0;
        virtual RPC::IStringIterator* Systems() const = 0;
        virtual RPC::IStringIterator* Designators(const string& keySystem) const = 0;
        virtual RPC::IStringIterator* Sessions(const string& keySystem) const = 0;

        enum Status : uint8_t {
            BUSY,
            SUCCESS,
            FAILED
        };

        /* @event */
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum {ID = ID_CONTENTDECRYPTION_NOTIFICATION};

            /* @brief initialization status. */
            virtual void initializationStatus(const std::string& drm,
                                              const Status status) = 0;
        };

        virtual uint32_t Register(IContentDecryption::INotification* notification VARIABLE_IS_NOT_USED) { return Core::ERROR_NOT_SUPPORTED; };
        virtual uint32_t Unregister(IContentDecryption::INotification* notification VARIABLE_IS_NOT_USED) { return Core::ERROR_NOT_SUPPORTED; };
    };

    class DataExchange : public Core::SharedBuffer {
    private:
        struct Administration {
            uint32_t Status;
            uint8_t  EncScheme;
            uint8_t  IVLength;
            uint8_t  KeyIdLength;
            uint16_t SubSampleLength;
            uint32_t PatternEncBlocks;
            uint32_t PatternClearBlocks;
            uint8_t  IV[24];
            uint8_t  KeyId[17];
            CDMi::SubSampleInfo SubSamples[100];
            uint16_t StreamHeight;
            uint16_t StreamWidth;
            uint8_t  StreamType;
        };

    public:
        DataExchange() = delete;
        DataExchange(const DataExchange&) = delete;
        DataExchange& operator=(const DataExchange&) = delete;

        DataExchange(const string& name)
            : Core::SharedBuffer(name.c_str())
        {
        }
        DataExchange(const string& name, const uint32_t bufferSize)
            : Core::SharedBuffer(name.c_str(), 
                Core::File::USER_READ    |
                Core::File::USER_WRITE   |
                Core::File::USER_EXECUTE |
                Core::File::GROUP_READ   |
                Core::File::GROUP_WRITE  |
                Core::File::OTHERS_READ  |
                Core::File::OTHERS_WRITE,
                bufferSize,
                sizeof(Administration))
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            // Clear the administration space before using it.
            ::memset(admin, 0, sizeof(Administration));
        }
        ~DataExchange() = default;

    public:
        void Clear() 
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            admin->SubSampleLength = 0;
            admin->IVLength = 0;
            admin->KeyIdLength = 0;
            admin->StreamHeight = 0;
            admin->StreamWidth = 0;
            admin->StreamType = 0;
        }
        void Status(uint32_t status)
        {
            reinterpret_cast<Administration*>(AdministrationBuffer())->Status = status;
        }
        uint32_t Status() const
        {
            return (reinterpret_cast<const Administration*>(AdministrationBuffer())->Status);
        }
        void InitWithLast15(bool initWithLast15)
        {
            if (initWithLast15 == true) {
                reinterpret_cast<Administration*>(AdministrationBuffer())->IVLength |= 0x80;
            }
            else {
                reinterpret_cast<Administration*>(AdministrationBuffer())->IVLength &= (~0x80);
            }
        }
        bool InitWithLast15() const
        {
            return ((reinterpret_cast<const Administration*>(AdministrationBuffer())->IVLength & 0x80) != 0);
        }
        void SetIV(const uint8_t ivDataLength, const uint8_t ivData[])
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            VERIFY(ivDataLength <= sizeof(Administration::IV));
            admin->IVLength = (ivDataLength > sizeof(Administration::IV) ? sizeof(Administration::IV)
                                                                        : ivDataLength);
            ::memcpy(admin->IV, ivData, admin->IVLength);
            if (admin->IVLength < sizeof(Administration::IV)) {
                ::memset(&(admin->IV[admin->IVLength]), 0,
                    (sizeof(Administration::IV) - admin->IVLength));
            }
        }
        void SetEncScheme(const uint8_t encScheme)
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            admin->EncScheme = encScheme;
        }
        uint8_t EncScheme()
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            return admin->EncScheme;
        }
        void SetEncPattern(const uint32_t encBlocks, const uint32_t clearBlocks)
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            admin->PatternEncBlocks = encBlocks;
            admin->PatternClearBlocks = clearBlocks;
        }
        void EncPattern(uint32_t& encBlocks, uint32_t& clearBlocks)
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            encBlocks = admin->PatternEncBlocks;
            clearBlocks = admin->PatternClearBlocks;
        }
        uint16_t SubSampleLength() const 
        {
            const Administration* admin = reinterpret_cast<const Administration*>(AdministrationBuffer());
            return (admin->SubSampleLength);
        }
        const CDMi::SubSampleInfo* SubSamples() const
        {
            const Administration* admin = reinterpret_cast<const Administration*>(AdministrationBuffer());
            return (&(admin->SubSamples[0]));
        }
        void SubSample(const uint16_t length, const CDMi::SubSampleInfo subSampleInfo[])
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            VERIFY(sizeof(Administration::SubSamples)/sizeof(CDMi::SubSampleInfo) >= length);
            admin->SubSampleLength = std::min(static_cast<uint16_t>(sizeof(Administration::SubSamples)/sizeof(CDMi::SubSampleInfo)), length);
            for(uint8_t index = 0; index < admin->SubSampleLength; index++) {
                admin->SubSamples[index].encrypted_bytes = subSampleInfo[index].encrypted_bytes;
                admin->SubSamples[index].clear_bytes = subSampleInfo[index].clear_bytes;
            }
        }
        void SetMediaProperties(const uint16_t height, const uint16_t width, const uint8_t type)
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            admin->StreamHeight = height;
            admin->StreamWidth = width;
            admin->StreamType = type;
        }
        void MediaProperties(uint16_t& height, uint16_t& width, uint8_t& type)
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            height = admin->StreamHeight;
            width = admin->StreamWidth;
            type = admin->StreamType;
        }
        void Write(const uint32_t length, const uint8_t* data)
        {
            if (Core::SharedBuffer::Size(length) == true) {
                SetBuffer(0, length, data);
            }
        }
        void Read(const uint32_t length, uint8_t* data) const
        {
            GetBuffer(0, length, data);
        }
        const uint8_t* IVKey() const
        {
            const Administration* admin = reinterpret_cast<const Administration*>(AdministrationBuffer());
            return (admin->IV);
        }
        uint8_t IVKeyLength() const
        {
            const Administration* admin = reinterpret_cast<const Administration*>(AdministrationBuffer());
            return (admin->IVLength);
        }
        void KeyId(const uint8_t length, const uint8_t buffer[])
        {
            Administration* admin = reinterpret_cast<Administration*>(AdministrationBuffer());
            VERIFY(length <= sizeof(Administration::KeyId));
            admin->KeyId[0] = (length <= sizeof(Administration::KeyId) ? length : sizeof(Administration::KeyId));
            if (length != 0) {
                ::memcpy(&(admin->KeyId[1]), buffer, admin->KeyId[0]);
            }
        }
        const uint8_t* KeyId(uint8_t& length) const
        {
            const Administration* admin = reinterpret_cast<const Administration*>(AdministrationBuffer());
            length = admin->KeyId[0];
            VERIFY(length <= 16);
            return (length > 0 ? &admin->KeyId[1] : nullptr);
        }
    };
}
}

