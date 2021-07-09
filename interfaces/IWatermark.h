#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IWatermark : virtual public Core::IUnknown {
        enum { ID = ID_WATERMARK };

        virtual ~IWatermark() {}
        virtual uint32_t Initialize(string waylandDisplay) = 0;
        virtual uint32_t Deinitialize() = 0;
        virtual bool ShowWatermark(const bool show) = 0;
        virtual bool CreateWatermark(uint32_t id, uint32_t zorder) = 0;
        virtual bool UpdateWatermark(uint32_t id, uint32_t key, uint32_t size) = 0;
        virtual bool AdjustWatermark(uint32_t id, uint32_t zorder) = 0;
        virtual bool DeleteWatermark(uint32_t id) = 0;
    };

} // Exchange
} // WPEFramework
