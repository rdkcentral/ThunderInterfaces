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

namespace Thunder {
namespace Exchange {

    /* @json 1.0.0 */
    struct EXTERNAL IPackageManager : virtual public Core::IUnknown {

        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        enum { ID = ID_PACKAGEMANAGER };

        // @brief Download the application bundle.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param url: URL used to install package
        // @param appName: Application Name
        // @param category: Category of the package
        // @param handle: Handle to the active installtion
        //        that can be used to refer to it later.
        //        e.g. for canceling or progress information
        virtual uint32_t Install(const string& type,
                const string& id,
                const string& version,
                const string& url,
                const string& appName,
                const string& category,
                string& handle /* @out */) = 0;

        // @brief Uninstall the application.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param uninstallType: Type of uninstall
        // @param handle: Handle to the active uninstallation
        //        that can be used to refer to it later.
        //        e.g. for canceling or progress information
        virtual uint32_t Uninstall(const string& type,
                const string& id,
                const string& version,
                const string& uninstallType,
                string& handle /* @out */) = 0;

        // @brief Download arbitrary application's resource file.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param url: URL used to download package
        // @param resKey: Resorce Key
        // @param handle: Handle to the active download
        //        that can be used to refer to it later.
        //        e.g. for canceling or progress information
        virtual uint32_t Download(const string& type,
                const string& id,
                const string& version,
                const string& resKey,
                const string& url,
                string& handle /* @out */) = 0;

        // @brief Delete persistent data stored locally.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param resetType: Type of Reset
        virtual uint32_t Reset(const string& type,
                const string& id,
                const string& version,
                const string& resetType) = 0;

        struct EXTERNAL StorageInfo 
        {
            struct EXTERNAL StorageDetails
            {
                string path    /* @brief Path of Storage */;
                string quotaKB /* @brief Total Space allowed in KB */;
                string usedKB  /* @brief Used Space in KB */;
            };
            StorageDetails apps       /* @brief Storage details of application */;
            StorageDetails persistent /* @brief Storage details of persistent */;
        };

        // @brief Information on the storage usage.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param storageinfo: Info about Storage
        virtual uint32_t GetStorageDetails(const string& type,
                const string& id,
                const string& version,
                StorageInfo& storageinfo /* @out */) const = 0;

        struct EXTERNAL KeyValue  {
            string key   /* @brief Key */;
            string value /* @brief Value */;
        };
        using IKeyValueIterator = RPC::IIteratorType<KeyValue, ID_PACKAGEMANAGER_KEY_VALUE_ITERATOR>;

        struct MetadataPayload {
            string appName  /* @brief Name of the application */;
            string type     /* @brief Type of the package */;
            string category /* @brief Category of the package */;
            string url      /* @brief URL used for operation */;
        };

        // @brief Set an arbitrary metadata.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param key: Key used to set arbitrary meta data
        // @param value: Value of given key
        virtual uint32_t SetAuxMetadata(const string& type,
                const string& id,
                const string& version,
                const string& key,
                const string& value) = 0;

        // @brief Clears an arbitrary metadata.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param key: Key used to clear arbitrary meta data
        virtual uint32_t ClearAuxMetadata(const string& type,
                const string& id,
                const string& version,
                const string& key) = 0;

        // @brief Get application metadata.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param metadata: Payload of meta data
        // @param resources: Resources
        // @param auxMetadata: Arbitrary metadata
        virtual uint32_t GetMetadata(const string& type,
                const string& id,
                const string& version,
                MetadataPayload& metadata /* @out */,
                IPackageManager::IKeyValueIterator*& resources /* @out */,
                IPackageManager::IKeyValueIterator*& auxMetadata /* @out */) const = 0;

        // @brief Cancel asynchronous request.
        // @param handle: Handle of the currently progressing operation (i.e, install/uninstal/download)
        virtual uint32_t Cancel(const string& handle) = 0;

        // @brief Estimated progress of a request.
        // @param handle: Handle of the currently progressing operation (i.e, install/uninstal/download)
        // @param progress: Indication of installation progress
        virtual uint32_t GetProgress(const string& handle, uint32_t& progress /* @out */) const = 0;

        /* @event */
        struct EXTERNAL INotification : virtual public Core::IUnknown {

            enum {ID = ID_PACKAGEMANAGER_NOTIFICATION};

            // @brief Completion of asynchronous operation.
            // @param handle: Handle of the currently progressing operation (i.e, install/uninstal/download)
            // @param operation: Type of the operation
            // @param type: Type of the package
            // @param id: Id of the package
            // @param version: Version of the package
            // @param status: Current status of the operation
            // @param details: Details about the operation
            virtual void OperationStatus(const string& handle, const string& operation, const string& type, const string& id,
                                         const string& version, const string& status, const string& details) = 0;
        };

        virtual uint32_t Register(IPackageManager::INotification* notification) = 0;
        virtual uint32_t Unregister(IPackageManager::INotification* notification) = 0;

        struct EXTERNAL PackageKey {            
            string id      /* @brief Unique identifier of the package */;
            string version /* @brief Version of the package */;
        };

        using IPackageKeyIterator = RPC::IIteratorType<PackageKey, ID_PACKAGEMANAGER_PACKAGE_KEY_ITERATOR>;

        // @brief List installed applications.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param appName: Application Name
        // @param category: Category of the package
        // @param installedIds: Ids of Installed Package
        virtual uint32_t GetList(
                const string& type,
                const string& id,
                const string& version,
                const string& appName,
                const string& category,
                IPackageKeyIterator*& installedIds /* @out */) const = 0; 

        // @brief Lock the application. Preventing uninstallation
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param reason: Reason to lock the application
        // @param owner: Owner used to lock
        // @param handle: Handle to the lock
        //        that can be used to refer to it later.
        //        e.g. for unlock later

        virtual uint32_t Lock(const string& type,
                const string& id,
                const string& version,
                const string& reason,
                const string& owner,
                string& handle /* @out */) = 0;


        // @brief Unlock application.
        // @param handle: Handle got during the Lock, it is to be used to Unlock operation
        virtual uint32_t Unlock(const string& handle) = 0;

        struct LockInfo {
            string reason /* @brief Reason of Locking */;
            string owner  /* @brief Owner of Locking */;
        };

        // @brief Get lock info.
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param result: Info about Lock
        virtual uint32_t GetLockInfo(const string& type,
                const string& id,
                const string& version,
                LockInfo& result /* @out */) const = 0;

    };

    struct EXTERNAL IPackageManagerBroker : virtual public Core::IUnknown {

        enum { ID = ID_PACKAGEMANAGER_BROKER };
        // @brief Offer Package Manager
        // @param packagemanager: Package manager instance
        virtual uint32_t Offer(IPackageManager* packagemanager) = 0;
        // @brief Revoke Package Manager
        // @param packagemanager: Package manager instance
        virtual uint32_t Revoke(const IPackageManager* packagemanager) = 0;
    };

    struct EXTERNAL IPackageManagerCallback : virtual public Core::IUnknown {

        enum { ID = ID_PACKAGEMANAGER_CALLBACK };

        // @brief Notify Update in requested operation (install/uninstall/download)
        // @param handle: Handle of the operation
        // @param operation: Type of the operation
        // @param type: Type of the package
        // @param id: Id of the package
        // @param version: Version of the package
        // @param status: Current status of the operation
        // @param details: Details about the operation
        virtual void OperationStatusUpdate(const string& handle, const string& operation,
                                           const string& type, const string& id,
                                           const string& version, const string& status,
                                           const string& details) = 0;
    };

}
}
