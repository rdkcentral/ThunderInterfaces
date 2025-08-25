#pragma once

#include "Module.h"

namespace Thunder {
namespace Exchange {

// Generate JSON_RPC in addition to COM_RPC by adding this tag
// @json 1.0.0
struct EXTERNAL ISimplePlugin : virtual public Core::IUnknown {
    enum { ID = ID_SIMPLEPLUGIN };

    // @event
    struct EXTERNAL INotification : virtual public Core::IUnknown {
        enum { ID = ID_SIMPLEPLUGIN_NOTIFICATION };

        virtual void LifeChangingEvent(const string& description) = 0;
    };

    // Register for COM_RPC notifications 
    virtual uint32_t Register(ISimplePlugin::INotification* sink /* @in */) = 0;

    // Unregister for COM_RPC notifications 
    virtual uint32_t Unregister(ISimplePlugin::INotification* sink /* @in */) = 0;

    // Arbitrary method
    virtual uint32_t DoSomething() = 0;

    // Start the implemented service
    virtual uint32_t ServiceStart(VARIABLE_IS_NOT_USED uint32_t waitTime /* @in */) = 0;

    // Stop the implemented service
    virtual uint32_t ServiceStop(VARIABLE_IS_NOT_USED uint32_t waitTime /* @in */) = 0;
};

} } // namespace Thunder::Exchange


// Abstract
// Naming
// const
