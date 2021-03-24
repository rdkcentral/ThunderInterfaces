#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IEssosSample : virtual public Core::IUnknown {
        enum { ID = ID_ESSOS_SAMPLE };

        virtual ~IEssosSample() {}
        virtual uint32_t Initialize(PluginHost::IShell* service) = 0;
        virtual void Deinitialize(PluginHost::IShell* service) = 0;
        virtual uint32_t Configure(PluginHost::IShell* service) = 0;
        virtual uint32_t setWaylandDisplay(const string &input) = 0;
        virtual uint32_t start() = 0;
        virtual uint32_t stop() = 0;
    };

} // Exchange
} // WPEFramework
