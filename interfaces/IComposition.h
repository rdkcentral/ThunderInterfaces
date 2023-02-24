/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "Module.h"

#include "IDeviceInfo.h"

// @insert "IDeviceInfo.h"

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IComposition : virtual public Core::IUnknown {
        enum { ID = ID_COMPOSITION };

        ~IComposition() override = default;

        static constexpr uint32_t maxOpacity = 255;
        static constexpr uint32_t minOpacity = 0;

        static constexpr uint32_t maxZOrder = 255;
        static constexpr uint32_t minZOrder = 0;

        using ScreenResolution = IDeviceVideoCapabilities::ScreenResolution;

        /**
         * @brief factor to be used to remove the need of using float values on the interface.
         *
         */
        static constexpr uint16_t RefreshRateFactor = 1000;

        /**
         * @brief Gets the refresh rate from a IComposition::ScreenResolution.
         *
         * @param resolution The resolution to parse
         * @return uint16_t the refresh rate multiplied with @RefreshRateFactor (59940 / @RefreshRateFactor -> 59.940Hz)
         */
        static uint32_t RefreshRateFromResolution(const ScreenResolution resolution);
        static uint32_t WidthFromResolution(const ScreenResolution resolution);
        static uint32_t HeightFromResolution(const ScreenResolution resolution);

        static ScreenResolution ResolutionFromHeightWidth(const uint32_t height, const uint32_t width);

        struct Rectangle {
            uint32_t x;
            uint32_t y;
            uint32_t width;
            uint32_t height;
        };

        struct EXTERNAL IClient : virtual public Core::IUnknown {
            enum { ID = ID_COMPOSITION_CLIENT };

            ~IClient() override = default;

            struct EXTERNAL IProperties : virtual public Core::IUnknown {
                enum { ID = ID_COMPOSITION_CLIENTPROPERTIES };

                ~IProperties() override = default;

                virtual uint32_t Stride() = 0; // bytes per row [(bit-per-pixel/8) * width]
                virtual uint32_t Format() = 0; // pixel arrangement according the fourcc format
                virtual uint32_t Offset() = 0;
                virtual uint64_t Modifier() = 0;
            };

            virtual WPEFramework::Core::instance_id Native() const { return 0; };
            virtual string Name() const = 0;
            virtual void Opacity(const uint32_t value) = 0;
            virtual uint32_t Opacity() const { return 0; };
            virtual uint32_t Geometry(const Rectangle& rectangle) = 0;
            virtual Rectangle Geometry() const = 0;
            virtual uint32_t ZOrder(const uint16_t index) = 0;
            virtual uint32_t ZOrder() const = 0;
        };

        struct EXTERNAL IRender : virtual public Core::IUnknown {
            enum { ID = ID_COMPOSITION_RENDER };

            ~IRender() override = default;

            virtual void ScanOut() = 0;
            virtual void PreScanOut() {};
            virtual void PostScanOut() {};
        };

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_COMPOSITION_NOTIFICATION };

            ~INotification() override = default;

            virtual void Attached(const string& name, IClient* client) = 0;
            virtual void Detached(const string& name) = 0;
        };

        struct EXTERNAL IDisplay : virtual public Core::IUnknown {
            enum { ID = ID_COMPOSITION_DISPLAY };

            ~IDisplay() override = default;

            virtual WPEFramework::Core::instance_id Native() const = 0;
            virtual string Port() const = 0;

            virtual IClient* CreateClient(const string& name, const uint32_t width, const uint32_t height) = 0;

            // Set and get output resolution
            virtual uint32_t Resolution(const ScreenResolution) = 0;
            virtual ScreenResolution Resolution() const = 0;
        };

        virtual void Register(IComposition::INotification* notification) = 0;
        virtual void Unregister(IComposition::INotification* notification) = 0;

        virtual uint32_t Configure(PluginHost::IShell* service) = 0;

        // Set and get output resolution
        virtual uint32_t Resolution(const ScreenResolution) = 0;
        virtual ScreenResolution Resolution() const = 0;
    };

    struct EXTERNAL IBrightness : virtual public Core::IUnknown {
        enum { ID = ID_BRIGHTNESS };

        // Brightness of SDR graphics in HDR display
        enum Brightness : uint8_t {
            SdrToHdrGraphicsBrightness_Default = 0, /* peak luminance of SDR graphics in HDR display might be less bright than SDR video in HDR display */
            SdrToHdrGraphicsBrightness_MatchVideo = 1, /* peak luminance of SDR graphics in HDR display will be as bright as SDR video in HDR display */
            SdrToHdrGraphicsBrightness_Max = 2 /* peak luminance of SDR graphics in HDR display might be more bright than SDR video in HDR display */
        };

        virtual uint32_t SdrToHdrGraphicsBrightness(Brightness& brightness /* @out */) const = 0;
        virtual uint32_t SdrToHdrGraphicsBrightness(const Brightness& brightness) = 0;
    };
}
}
