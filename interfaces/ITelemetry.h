#pragma once
#include "Module.h"


namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL ITelemetry : virtual public Core::IUnknown {
        enum { ID = ID_TELEMETRY };

        virtual ~ITelemetry() {}

        virtual uint32_t LogApplicationEvent(const string marker, const string event) = 0;

    };
} // namespace Exchange
} // namespace WPEFramework
