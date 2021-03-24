#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IEssosSample : virtual public Core::IUnknown {
        enum { ID = ID_ESSOS_SAMPLE };

        virtual ~IEssosSample() {}
        virtual uint32_t SetWaylandDisplay(const string &input) = 0;
        virtual uint32_t Start() = 0;
        virtual uint32_t Stop() = 0;
    };

} // Exchange
} // WPEFramework
