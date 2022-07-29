#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct PalettedImageData
    {
        uint32_t imageKey;
        uint32_t imageWidth;
        uint32_t imageHeight;
        uint32_t clutKey;
        uint32_t clutSize;
        string clutType;
    };

    struct EXTERNAL IWatermark : virtual public Core::IUnknown {
        enum { ID = ID_WATERMARK };

        struct INotification : virtual public Core::IUnknown {

            enum { ID = ID_WATERMARK_NOTIFICATION };

            ~INotification() override = default;

            virtual void WatermarkEvent(const string& eventName, const string& parametersJson) = 0;
        };


        virtual ~IWatermark() {}
        virtual uint32_t Initialize(string waylandDisplay, bool synchronized) = 0;
        virtual uint32_t Deinitialize() = 0;
        virtual uint32_t Register(INotification* notification) = 0;
        virtual uint32_t Unregister(INotification* notification) = 0;
        virtual bool ShowWatermark(const bool show) = 0;
        virtual bool CreateWatermark(uint32_t id, uint32_t zorder) = 0;
        virtual bool UpdateWatermark(uint32_t id, uint32_t key, uint32_t size) = 0;
        virtual bool AdjustWatermark(uint32_t id, uint32_t zorder) = 0;
        virtual bool DeleteWatermark(uint32_t id) = 0;
        virtual PalettedImageData GetPalettedWatermark(uint32_t id) = 0;
        virtual bool ModifyPalettedWatermark(uint32_t id, PalettedImageData data) = 0;
    };

} // Exchange
} // WPEFramework
