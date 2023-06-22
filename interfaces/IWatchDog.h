#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    // @json
    struct EXTERNAL IWatchDog : virtual public Core::IUnknown {

        enum { ID = ID_WATCHDOG };

        ~IWatchDog() override = default;

        // @brief Touch the watchdog as a sign of life.
        // @param callsign In case a specific watchdog needs to be padded pass
	    //                 the name of the callsign for which we want to touch.
        virtual uint32_t Touch(const string& callsign) = 0;
    };
}
}
