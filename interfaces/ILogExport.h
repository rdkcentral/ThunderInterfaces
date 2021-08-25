/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
*
* Copyright 2021 Metrological Management
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
**/

#pragma once
#include "Module.h"

// @stubgen:include <com/IRPCIterator.h>

namespace WPEFramework{
namespace Exchange{
    //@json
    struct EXTERNAL ILogExport: virtual public Core::IUnknown {
        enum {ID = ID_LOG_EXPORT};
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum {ID = ID_LOG_NOTIFICATION};
            using ILogIterator = RPC::IIteratorType<string, ID_LOGITERATOR>;
            //@json:omit
            virtual uint32_t OutputMessage(const std::string& filename /*@out*/, Exchange::ILogExport::INotification::ILogIterator* logLines /*@out*/) = 0;
        };
        virtual ~ILogExport() {}
        // @brief filename that should be watched for changes and upload them.
        virtual uint32_t watch(const std::string& filename, const bool& fromBeginning ) = 0;
        // @brief filename that should be stop watching
        virtual uint32_t unwatch(const std::string& filename ) = 0;
        // @brief filename that should not be watched but contents to be uploaded
        virtual uint32_t dump(const std::string& filename ) = 0;
        //@brief register notification sink
        //@json:omit
        virtual void Register(ILogExport::INotification* sink) = 0;
        //@brief unregister notification sink
        //@json:omit
        virtual void Unregister(ILogExport::INotification* sink) = 0;
    };

}
}
