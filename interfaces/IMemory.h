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

//already added the below so it is not forgotten when to start generating proxy/stubs for this
// @stubgen:include <com/IIteratorType.h>
 
namespace WPEFramework {
namespace Exchange {

    // This interface allows for retrieval of memory usage specific to the implementor
    // of the interface
    // @stubgen:omit
    struct EXTERNAL IMemory : virtual public Core::IUnknown {
        enum { ID = ID_MEMORY };

        virtual uint64_t Resident() const = 0;
        virtual uint64_t Allocated() const = 0;
        virtual uint64_t Shared() const = 0;
        virtual uint8_t Processes() const = 0;
        virtual bool IsOperational() const = 0;
    };

    // @stubgen:omit
    struct EXTERNAL IProcessMemory : public IMemory {
        enum { ID = ID_PROCESSMEMORY };

        virtual uint32_t Identifier() const = 0;
        virtual string Name() const = 0;
    };

    // @stubgen:omit
    struct EXTERNAL IMemoryExtended : virtual public Core::IUnknown {
        enum { ID = ID_MEMORYEXTENDED };

        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        virtual uint32_t Processes(IStringIterator*& processnames /* @out */) const = 0;

        virtual uint32_t Process(const string& processname, IProcessMemory*& process /* @out */ ) const = 0;
    };
}
}

