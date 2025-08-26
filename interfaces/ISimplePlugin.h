#pragma once

#include "Module.h"

namespace Thunder {
namespace Exchange {

// Generate JSON_RPC in addition to COMRPC by adding this tag
// @json 1.0.0
struct EXTERNAL ISimplePlugin : virtual public Core::IUnknown {
    enum { ID = ID_SIMPLEPLUGIN };

    // @event
    struct EXTERNAL INotification : virtual public Core::IUnknown {
        enum { ID = ID_SIMPLEPLUGIN_NOTIFICATION };

        virtual void ProcessEvent(const string& description) = 0;
    };

    // Register for COMRPC notifications 
    virtual uint32_t Register(ISimplePlugin::INotification* sink /* @in */) = 0;

    // Unregister for COMRPC notifications 
    virtual uint32_t Unregister(ISimplePlugin::INotification* sink /* @in */) = 0;

    // Arbitrary method
    virtual uint32_t ExecuteTask() = 0;

    virtual uint32_t InitializeTask(const uint32_t waitTime /* @in */) = 0;

    virtual uint32_t DeinitializeTask(const uint32_t waitTime /* @in */) = 0;
};

} } // namespace Thunder::Exchange
