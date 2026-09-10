#pragma once

#include "Module.h"

namespace Thunder {
namespace QualityAssurance {

    struct EXTERNAL ITestDelegatedReleasePeer : virtual public Core::IUnknown {
        enum { ID = ID_TESTDELEGATEDRELEASEPEER };

        ~ITestDelegatedReleasePeer() override = default;

        virtual Core::hresult Ping(uint32_t& value /* @out */) = 0;
    };

} // namespace QualityAssurance
} // namespace Thunder