/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Metrological
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

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IStore2 : virtual public Core::IUnknown {
        enum { ID = ID_STORE2 };

        ~IStore2() override = default;

        enum ScopeType : uint8_t {
            DEVICE,
            ACCOUNT
        };

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_STORE2_NOTIFICATION };

            ~INotification() override = default;

            virtual void ValueChanged(const ScopeType scope, const string& ns, const string& key, const string& value) = 0;
        };

        virtual uint32_t Register(Exchange::IStore2::INotification* notification) = 0;
        virtual uint32_t Unregister(Exchange::IStore2::INotification* notification) = 0;

        virtual uint32_t SetValue(const ScopeType scope, const string& ns, const string& key, const string& value, const uint32_t ttl) = 0;
        virtual uint32_t GetValue(const ScopeType scope, const string& ns, const string& key, string& value /* @out */, uint32_t& ttl /* @out */) = 0;
        virtual uint32_t DeleteKey(const ScopeType scope, const string& ns, const string& key) = 0;
        virtual uint32_t DeleteNamespace(const ScopeType scope, const string& ns) = 0;
    };

    struct EXTERNAL IStoreInspector : virtual public Core::IUnknown {
        enum { ID = ID_STORE_INSPECTOR };

        ~IStoreInspector() override = default;

        struct NamespaceSize {
            string ns;
            uint32_t size;
        };

        using ScopeType = IStore2::ScopeType;
        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;
        using INamespaceSizeIterator = RPC::IIteratorType<NamespaceSize, ID_STORE_INSPECTOR_NAMESPACE_SIZE_ITERATOR>;

        virtual uint32_t GetKeys(const ScopeType scope, const string& ns, IStringIterator*& keys /* @out */) = 0;
        virtual uint32_t GetNamespaces(const ScopeType scope, IStringIterator*& namespaces /* @out */) = 0;
        virtual uint32_t GetStorageSizes(const ScopeType scope, INamespaceSizeIterator*& storageList /* @out */) = 0;
    };

    struct EXTERNAL IStoreLimit : virtual public Core::IUnknown {
        enum { ID = ID_STORE_LIMIT };

        ~IStoreLimit() override = default;

        using ScopeType = IStore2::ScopeType;

        virtual uint32_t SetNamespaceStorageLimit(const ScopeType scope, const string& ns, const uint32_t size) = 0;
        virtual uint32_t GetNamespaceStorageLimit(const ScopeType scope, const string& ns, uint32_t& size /* @out */) = 0;
    };

} // namespace Exchange
} // namespace WPEFramework
