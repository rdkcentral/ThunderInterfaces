#pragma once

#include "Module.h"

namespace Thunder {
namespace QualityAssurance {

/* @json 1.0.0 */
struct EXTERNAL ISmartConsumer : virtual public Core::IUnknown {
    enum { ID = ID_SMART_CONSUMER };

    ~ISmartConsumer() override = default;

    virtual uint32_t Calculate(
        const uint16_t a,
        const uint16_t b,
        uint16_t& addResult /* @out */,
        uint16_t& subResult /* @out */) = 0;
};

} // namespace QualityAssurance
} // namespace Thunder