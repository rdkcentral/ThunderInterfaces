/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Liberty Global Service B.V.
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

    struct EXTERNAL ILISA : virtual public Core::IUnknown {

        enum { ID = ID_LISA };

        /* @brief Download the application bundle. */
        virtual uint32_t Install(const std::string& type,
                const std::string& id,
                const std::string& version,
                const std::string& url,
                const std::string& appName,
                const std::string& category,
                std::string& handle /* @out */) = 0;

        /* @brief Uninstall the application. */
        virtual uint32_t Uninstall(const std::string& type,
                const std::string& id,
                const std::string& version,
                const std::string& uninstallType,
                std::string& handle /* @out */) = 0;

        /* @brief Download arbitrary application's resource file. */
        virtual uint32_t Download(const std::string& type,
                const std::string& id,
                const std::string& version,
                const std::string& resKey,
                const std::string& url,
                std::string& handle /* @out */) = 0;

        /* @brief Delete persistent data stored locally. */
        virtual uint32_t Reset(const std::string& type,
                const std::string& id,
                const std::string& version,
                const std::string& resetType) = 0;

        struct EXTERNAL IStorage : virtual public Core::IUnknown
        {
            enum { ID = ID_LISA_STORAGE };

            virtual uint32_t Path(string& path /* @out */) const = 0;
            virtual uint32_t QuotaKB(string& quotaKB /* @out */) const = 0;
            virtual uint32_t UsedKB(string& usedKB /* @out */) const = 0;
        };

        struct EXTERNAL IStoragePayload : virtual public Core::IUnknown {
            enum { ID = ID_LISA_STORAGE_PAYLOAD };

            virtual uint32_t Apps(ILISA::IStorage*& storage /* @out */) const = 0;
            virtual uint32_t Persistent(ILISA::IStorage*& storage /* @out */) const = 0;
        };

        /* @brief Information on the storage usage. */
        virtual uint32_t GetStorageDetails(const std::string& type,
                const std::string& id,
                const std::string& version,
                ILISA::IStoragePayload*& result /* @out */) = 0;

        struct EXTERNAL IKeyValue : virtual public Core::IUnknown {
            enum { ID = ID_LISA_KEY_VALUE };

            virtual uint32_t Key(string& key /* @out */) const = 0;
            virtual uint32_t Value(string& value /* @out */) const = 0;
        };

        struct EXTERNAL IKeyValueIterator : virtual public Core::IUnknown {
            enum { ID = ID_LISA_KEY_VALUE_ITERATOR };

            virtual uint32_t Reset() = 0;
            virtual uint32_t IsValid(bool& isValid /* @out */) const = 0;
            virtual uint32_t Next(bool& hasNext /* @out */) = 0;
            virtual uint32_t Current(ILISA::IKeyValue*& keyValue /* @out */) const = 0;
        };

        struct EXTERNAL IMetadataPayload : virtual public Core::IUnknown {
            enum { ID = ID_LISA_METADATA_PAYLOAD };

            virtual uint32_t AppName(std::string& appName /* @out */) const = 0;
            virtual uint32_t Category(std::string& category /* @out */) const = 0;
            virtual uint32_t Url(std::string& url /* @out */) const = 0;
            virtual uint32_t Resources(ILISA::IKeyValueIterator*& resources /* @out */) const = 0;
            virtual uint32_t AuxMetadata(ILISA::IKeyValueIterator*& auxMetadata /* @out */) const = 0;
        };

        /* @brief Set an arbitrary metadata. */
        virtual uint32_t SetAuxMetadata(const std::string& type,
                const std::string& id,
                const std::string& version,
                const std::string& key,
                const std::string& value) = 0;

        /* @brief Clears an arbitrary metadata. */
        virtual uint32_t ClearAuxMetadata(const std::string& type,
                const std::string& id,
                const std::string& version,
                const std::string& key) = 0;

        /* @brief Get application metadata. */
        virtual uint32_t GetMetadata(const std::string& type,
                const std::string& id,
                const std::string& version,
                ILISA::IMetadataPayload*& result /* @out */) = 0;

        /* @brief Cancel asynchronous request. */
        virtual uint32_t Cancel(const std::string& handle) = 0;

        /* @brief Estimated progress of a request. */
        virtual uint32_t GetProgress(const std::string& handle, uint32_t& progress /* @out */) = 0;

        /* @event */
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum {ID = ID_LISA_NOTIFICATION};

            /* @brief Completion of asynchronous operation. */
            virtual void operationStatus(const string& handle, const string& operation, const string& type, const string& id,
                                         const string& version, const string& status, const string& details) = 0;
        };

        virtual uint32_t Register(ILISA::INotification* notification) = 0;
        virtual uint32_t Unregister(ILISA::INotification* notification) = 0;
        virtual uint32_t Configure(const std::string& config) = 0;

        struct EXTERNAL IAppVersion : virtual public Core::IUnknown {
            enum { ID = ID_LISA_APP_VERSION };

            struct EXTERNAL IIterator : virtual public Core::IUnknown {
                enum { ID = ID_LISA_APP_VERSION_ITERATOR };

                virtual uint32_t Reset() = 0;
                virtual uint32_t IsValid(bool& isValid /* @out */) const = 0;
                virtual uint32_t Next(bool& hasNext /* @out */) = 0;
                virtual uint32_t Current(ILISA::IAppVersion*& app /* @out */) const = 0;
            };

            virtual uint32_t Version(string& version /* @out */) const = 0;
            virtual uint32_t AppName(string& appName /* @out */) const = 0;
            virtual uint32_t Category(string& category /* @out */) const = 0;
            virtual uint32_t Url(string& url /* @out */) const = 0;
        };

        struct EXTERNAL IApp : virtual public Core::IUnknown {
            enum { ID = ID_LISA_APP };

            struct EXTERNAL IIterator : virtual public Core::IUnknown {
                enum { ID = ID_LISA_APP_ITERATOR };

                virtual uint32_t Reset() = 0;
                virtual uint32_t IsValid(bool& isValid /* @out */) const = 0;
                virtual uint32_t Next(bool& hasNext /* @out */) = 0;
                virtual uint32_t Current(ILISA::IApp*& app /* @out */) const = 0;
            };

            virtual uint32_t Type(string& type /* @out */) const = 0;
            virtual uint32_t Id(string& id /* @out */) const = 0;
            virtual uint32_t Installed(ILISA::IAppVersion::IIterator*& versions /* @out */) const = 0;
        };

        struct EXTERNAL IAppsPayload : virtual public Core::IUnknown {
            enum { ID = ID_LISA_APPS_PAYLOAD };

            virtual uint32_t Apps(ILISA::IApp::IIterator*& apps /* @out */) const = 0;
        };

        /* @brief List installed applications. */
        virtual uint32_t GetList(
                const std::string& type,
                const std::string& id,
                const std::string& version,
                const std::string& appName,
                const std::string& category,
                IAppsPayload*& result /* @out */) const = 0;

        struct EXTERNAL IHandleResult : virtual public Core::IUnknown {
            enum { ID = ID_LISA_HANDLE_RESULT };

            virtual uint32_t Handle(std::string& handle /* @out */) const = 0;
        };

        /* @brief Lock the application. Preventing uninstallation. */
        virtual uint32_t Lock(const std::string& type,
                const std::string& id,
                const std::string& version,
                const std::string& reason,
                const std::string& owner,
                ILISA::IHandleResult*& result /* @out */) = 0;


        /* @brief Unlock application. */
        virtual uint32_t Unlock(const std::string& handle) = 0;

        struct EXTERNAL ILockInfo : virtual public Core::IUnknown {
            enum { ID = ID_LISA_LOCK_INFO };

            virtual uint32_t Reason(std::string& reason /* @out */) const = 0;
            virtual uint32_t Owner(std::string& owner /* @out */) const = 0;
        };

        /* @brief Get lock info. */
        virtual uint32_t GetLockInfo(const std::string& type,
                const std::string& id,
                const std::string& version,
                ILISA::ILockInfo*& result /* @out */) = 0;
    };

}
}
