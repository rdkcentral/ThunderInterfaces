#pragma once

#include "Module.h"

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IAnalytics : virtual public Core::IUnknown {
        enum { ID = ID_ANALYTICS };

        virtual ~IAnalytics() override = default;

        virtual uint32_t SendEvent(const string& eventName /* @in */,
                                   const string& eventVersion /* @in */,
                                   const string& eventSource /* @in */,
                                   const string& eventSourceVersion /* @in */,
                                   RPC::IStringIterator* const& cetList /* @in */,
                                   const uint64_t& epochTimestamp /* @in */,
                                   const uint64_t& uptimeTimestamp /* @in */,
                                   const string& eventPayload /* @in */ ) = 0;
        virtual uint32_t SetSessionId(const string& id /* @in */) = 0;
        virtual uint32_t SetTimeReady() = 0;
    };
}
}
