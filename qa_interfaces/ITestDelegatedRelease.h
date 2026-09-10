#pragma once

#include "Module.h"
#include "ITestDelegatedReleasePeer.h"

// @stubgen:include "ITestDelegatedReleasePeer.h"

namespace Thunder {
namespace QualityAssurance {

    struct EXTERNAL ITestDelegatedRelease : virtual public Core::IUnknown {
        enum { ID = ID_TESTDELEGATEDRELEASE };

        ~ITestDelegatedRelease() override = default;

        virtual Core::hresult Ping(uint32_t& value /* @out */) = 0;
        virtual Core::hresult HoldPeer(ITestDelegatedReleasePeer* peer) = 0;
    };

} // namespace QualityAssurance
} // namespace Thunder