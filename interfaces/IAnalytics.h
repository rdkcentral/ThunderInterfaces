#pragma once

#include "Module.h"

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {
    // @json 1.0.0 @text:keep 
    struct EXTERNAL IAnalytics : virtual public Core::IUnknown {
        enum { ID = ID_ANALYTICS };

        virtual ~IAnalytics() override = default;

        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        
        // @alt sendEvent
        // @brief Send an event to the analytics server
        // @param eventName: Name of the event
        // @param eventVersion: Version of the event
        // @param eventSource: Source of the event
        // @param eventSourceVersion: Version of the event source
        // @param cetList: List of CETs
        // @param epochTimestamp: Epoch timestamp of the event
        // @param uptimeTimestamp: Uptime timestamp of the event
        // @param eventPayload: Payload of the event

        virtual Core::hresult SendEvent(const string& eventName /* @in */,
                                   const string& eventVersion /* @in */,
                                   const string& eventSource /* @in */,
                                   const string& eventSourceVersion /* @in */,
                                   IStringIterator* const& cetList /* @in */,
                                   const uint64_t epochTimestamp /* @in */,
                                   const uint64_t uptimeTimestamp /* @in */,
                                   const string& eventPayload /* @in */ ) = 0;
    };
}
}
