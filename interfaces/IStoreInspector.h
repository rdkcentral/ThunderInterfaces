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

#include "IStore2.h"

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IStoreInspector : virtual public Core::IUnknown {
        enum { ID = ID_STORE_INSPECTOR };

        virtual ~IStoreInspector() override = default;

        using ScopeType = IStore2::ScopeType;

        struct NamespaceSize {
            string ns;
            uint32_t size;
        };

        using INamespaceSizeIterator = RPC::IIteratorType<NamespaceSize, ID_STORE_INSPECTOR_NAMESPACE_SIZE_ITERATOR>;

        virtual uint32_t SetNamespaceStorageLimit(const ScopeType scope, const string& ns, const uint32_t size) = 0;
        virtual uint32_t GetNamespaceStorageLimit(const ScopeType scope, const string& ns, uint32_t& size /* @out */) = 0;
        virtual uint32_t GetKeys(const ScopeType scope, const string& ns, RPC::IStringIterator*& keys /* @out */) = 0;
        virtual uint32_t GetNamespaces(const ScopeType scope, RPC::IStringIterator*& namespaces /* @out */) = 0;
        virtual uint32_t GetStorageSizes(const ScopeType scope, INamespaceSizeIterator*& storageList /* @out */) = 0;
    };

} // namespace Exchange
} // namespace WPEFramework
