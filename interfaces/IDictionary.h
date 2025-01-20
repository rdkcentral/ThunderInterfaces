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

 // @stubgen:include <com/IIteratorType.h>

namespace Thunder {
namespace Exchange {

    /* @json 1.0.0 */
    // @description This interface is designed to be used to access a service that keeps key value pairs inside namespaces, which can be nested if needed. 
    //              Nested namespaces can be seperated by a delimiter when used in a path to a key.
    //              The interface is designed with a usage pattern in mind where a namespace does not contain a huge amount of keys, but instead these would be spread over multiple (nested if desired) namespaces.
    struct EXTERNAL IDictionary : virtual public Core::IUnknown {
        enum { ID = ID_DICTIONARY };

        ~IDictionary() override = default;

        // Delimiter that can be used to seperate multiple namespaces in a path to a key
        static constexpr TCHAR namespaceDelimiter = { _T('/') };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_DICTIONARY_NOTIFICATION };

            ~INotification() override = default;

            // @brief Changes on the subscribed namespace..
            // @param path: Path to the key which value changed
            // @param key: Key which value changed
            // @param value: Value that changed
            virtual void Modified(const string& path, const string& key, const string& value) = 0;
        };

        // Allow to observe values in the dictionary. If they are changed, the sink gets notified.
        virtual Core::hresult Register(const string& path, struct IDictionary::INotification* sink) = 0;
        virtual Core::hresult Unregister(const string& path, const struct IDictionary::INotification* sink) = 0;

        enum class Type : uint8_t {
            NAMESPACE,
            PERSISTENT_KEY,
            VOLATILE_KEY
        };

        struct EXTERNAL PathEntry {
            string name   /* @brief Name of Key or Namespace */;
            Type type /* @brief Type */;
        };
        using IPathIterator = RPC::IIteratorType<PathEntry, ID_DICTIONARY_ITERATOR>;


        // @brief Getters for the dictionary.
        // @param path: NameSpace path to be used
        // @param key: Key to be used
        // @param value: Value that was retrieved
        virtual Core::hresult Get(const string& path, const string& key, string& value /* @out */) const = 0;
        // @brief Setters for the dictionary.
        // @param path: NameSpace path to be used
        // @param key: Key to be used
        // @param value: Value to be set
        virtual Core::hresult Set(const string& path, const string& key, const string& value) = 0;

        // @brief Get a list of all entries for this namespace (could be keys or nested namespaces)
        // @param path: Namespace path where to get the keys and/or nested namespaces for
        // @param entries: Available nested namespaces and keys for this namespace path
        virtual Core::hresult PathEntries(const string& path, IDictionary::IPathIterator*& entries /* @out */) const = 0;
    };
}
}

