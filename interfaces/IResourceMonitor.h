/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 Metrological
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

#ifndef __IRESOURCEMONITOR_H
#define __IRESOURCEMONITOR_H

#include "Module.h"

namespace Thunder {
namespace Exchange {

    struct EXTERNAL IResourceMonitor : virtual public Core::IUnknown {

        enum { ID = ID_RESOURCEMONITOR };

        ~IResourceMonitor() override = default;
        
        virtual uint32_t Configure(PluginHost::IShell* framework) = 0;

        virtual string CompileMemoryCsv() = 0;
    };
}
}

#endif // __IRESOURCEMONITOR_H
