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

namespace Thunder {
namespace Exchange {

struct EXTERNAL IStore : virtual public Core::IUnknown {
    enum { ID = ID_STORE };

    struct EXTERNAL INotification : virtual public Core::IUnknown {
        enum { ID = ID_STORE_NOTIFICATION };

        virtual void ValueChanged(const string &ns, const string &key, const string &value) = 0;
        virtual void StorageExceeded() = 0;
    };

    virtual uint32_t Register(Exchange::IStore::INotification *notification) = 0;
    virtual uint32_t Unregister(Exchange::IStore::INotification *notification) = 0;
    virtual uint32_t SetValue(const string &ns, const string &key, const string &value) = 0;
    virtual uint32_t GetValue(const string &ns, const string &key, string &value /* @out */) = 0;
    virtual uint32_t DeleteKey(const string &ns, const string &key) = 0;
    virtual uint32_t DeleteNamespace(const string &ns) = 0;
};

} // namespace Exchange
} // namespace Thunder
