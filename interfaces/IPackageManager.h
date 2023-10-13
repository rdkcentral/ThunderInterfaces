/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
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

// This interface is based on the LGI ILISA interface with smal changes to enable JSON RPC code generation from the interface and extensions for improved Firebolt support

#pragma once
#include "Module.h"

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    /* @json */
    struct EXTERNAL IPackageManager : virtual public Core::IUnknown {

        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        enum { ID = ID_PACKAGEMANAGER };

        /* @brief Download the application bundle. */
        virtual uint32_t Install(const string& type,
                const string& id,
                const string& version,
                const string& url,
                const string& appName,
                const string& category,
                string& handle /* @out */) = 0;

        /* @brief Uninstall the application. */
        virtual uint32_t Uninstall(const string& type,
                const string& id,
                const string& version,
                const string& uninstallType,
                string& handle /* @out */) = 0;
        /* @brief Download arbitrary application's resource file. */
        virtual uint32_t Download(const string& type,
                const string& id,
                const string& version,
                const string& resKey,
                const string& url,
                string& handle /* @out */) = 0;

        /* @brief Delete persistent data stored locally. */
        virtual uint32_t Reset(const string& type,
                const string& id,
                const string& version,
                const string& resetType) = 0;

        struct EXTERNAL StorageInfo 
        {
                struct EXTERNAL StorageDetails 
                {
                        string path;
                        string quotaKB;
                        string usedKB;
                };
                
                StorageDetails apps;
                StorageDetails persistent;
        };

        /* @brief Information on the storage usage. */
        virtual uint32_t GetStorageDetails(const string& type,
                const string& id,
                const string& version,
                StorageInfo& storageinfo /* @out */) const = 0;

        struct EXTERNAL KeyValue  {
            string key;
            string value;
        };
        using IKeyValueIterator = RPC::IIteratorType<KeyValue, ID_PACKAGEMANAGER_KEY_VALUE_ITERATOR>;

        struct MetadataPayload {
            string appName;
            string type;
            string category;
            string url;
        };

        /* @brief Set an arbitrary metadata. */
        virtual uint32_t SetAuxMetadata(const string& type,
                const string& id,
                const string& version,
                const string& key,
                const string& value) = 0;

        /* @brief Clears an arbitrary metadata. */
        virtual uint32_t ClearAuxMetadata(const string& type,
                const string& id,
                const string& version,
                const string& key) = 0;

        /* @brief Get application metadata. */
        virtual uint32_t GetMetadata(const string& type,
                const string& id,
                const string& version,
                MetadataPayload& metadata /* @out */,
                IPackageManager::IKeyValueIterator*& resources /* @out */,
                IPackageManager::IKeyValueIterator*& auxMetadata /* @out */) const = 0;

        /* @brief Cancel asynchronous request. */
        virtual uint32_t Cancel(const string& handle) = 0;

        /* @brief Estimated progress of a request. */
        virtual uint32_t GetProgress(const string& handle, uint32_t& progress /* @out */) const = 0;

        /* @event */
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum {ID = ID_PACKAGEMANAGER_NOTIFICATION};

            /* @brief Completion of asynchronous operation. */
            virtual void OperationStatus(const string& handle, const string& operation, const string& type, const string& id,
                                         const string& version, const string& status, const string& details) = 0;
        };

        virtual uint32_t Register(IPackageManager::INotification* notification) = 0;
        virtual uint32_t Unregister(IPackageManager::INotification* notification) = 0;

        struct EXTERNAL PackageKey {            
            string id;
            string version;
        };

        using IPackageKeyIterator = RPC::IIteratorType<PackageKey, ID_PACKAGEMANAGER_PACKAGE_KEY_ITERATOR>;

        /* @brief List installed applications. */
        virtual uint32_t GetList(
                const string& type,
                const string& id,
                const string& version,
                const string& appName,
                const string& category,
                IPackageKeyIterator*& installedIds /* @out */) const = 0; 

        /* @brief Lock the application. Preventing uninstallation. */
        virtual uint32_t Lock(const string& type,
                const string& id,
                const string& version,
                const string& reason,
                const string& owner,
                string& handle /* @out */) = 0;


        /* @brief Unlock application. */
        virtual uint32_t Unlock(const string& handle) = 0;

        struct LockInfo {
            string reason;
            string owner;
        };

        /* @brief Get lock info. */
        virtual uint32_t GetLockInfo(const string& type,
                const string& id,
                const string& version,
                LockInfo& result /* @out */) const = 0;

    };

    struct EXTERNAL IPackageManagerBroker : virtual public Core::IUnknown {

                enum { ID = ID_PACKAGEMANAGER_BROKER };

                virtual uint32_t Offer(IPackageManager* packagemanager) = 0;
                virtual uint32_t Revoke(const IPackageManager* packagemanager) = 0;

    };

    struct EXTERNAL IPackageManagerCallback : virtual public Core::IUnknown {

                enum { ID = ID_PACKAGEMANAGER_CALLBACK };

                virtual void OperationStatusUpdate(const string& handle, const string& operation, const string& type, const string& id,
                                         const string& version, const string& status, const string& details) = 0;

    };

}
}
