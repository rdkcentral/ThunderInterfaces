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

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    /* @json */
    struct EXTERNAL IGraphicsProperties : virtual public Core::IUnknown {
        enum { ID = ID_GRAPHICS_PROPERTIES };

        // @property
        // @brief Total GPU DRAM memory (in bytes)
        // @return total: Total GPU RAM
        virtual uint32_t TotalGpuRam(uint64_t& total /* @out */) const = 0;

        // @property
        // @brief Free GPU DRAM memory (in bytes)
        // @return free: Free GPU RAM
        virtual uint32_t FreeGpuRam(uint64_t& free /* @out */) const = 0;
    };

    /* @json @uncompliant:extended */  // NOTE: extended format is deprecated!! Do not just copy this line!
    struct EXTERNAL IConnectionProperties : virtual public Core::IUnknown {
        enum { ID = ID_CONNECTION_PROPERTIES };

        enum HDCPProtectionType : uint8_t {
            HDCP_Unencrypted,
            HDCP_1X,
            HDCP_2X,
            HDCP_AUTO
        };

        /* @event @uncompliant:extended */  // NOTE: extended format is deprecated!! Do not just copy this line!
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_CONNECTION_PROPERTIES_NOTIFICATION };

            enum Source : uint8_t {
                PRE_RESOLUTION_CHANGE,
                POST_RESOLUTION_CHANGE,
                HDMI_CHANGE,
                HDCP_CHANGE,
            };

            virtual void Updated(const Source event) = 0;
        };

        virtual uint32_t Register(INotification*) = 0;
        virtual uint32_t Unregister(INotification*) = 0;

        // @property
        // @brief Current audio passthrough status on HDMI
        // @param passthru: enabled/disabled
        virtual uint32_t IsAudioPassthrough (bool& passthru /* @out */) const = 0;

        // @property
        // @brief Current HDMI connection status
        // @param isconnected: connected/disconnected
        virtual uint32_t Connected(bool& isconnected /* @out */) const = 0;

        // @property
        // @brief Horizontal resolution of TV
        // @param width:  width of TV in pixels
        virtual uint32_t Width(uint32_t& width /* @out */) const = 0;

        // @property
        // @brief Vertical resolution of TV
        // @param height:  height of TV in pixels
        virtual uint32_t Height(uint32_t& height /* @out */) const = 0;

        // @property
        // @brief Vertical Frequency
        // @param vf: vertical freq
        virtual uint32_t VerticalFreq(uint32_t& vf /* @out */) const = 0;

        // @brief TV's Extended Display Identification Data
        // @param edid: edid byte string
        virtual uint32_t EDID (uint16_t& length /* @inout */, uint8_t data[] /* @out @length:length */) const = 0;

        // @brief Horizontal size in centimeters
        // @param width: width in cm
        virtual uint32_t WidthInCentimeters(uint8_t& width /* @out */) const = 0;

        // @brief Vertical size in centimeters
        // @param width: height in cm
        virtual uint32_t HeightInCentimeters(uint8_t& height /* @out */) const = 0;

        // @property
        // @brief HDCP protocol used for transmission
        // @param value: protocol
        virtual uint32_t HDCPProtection (HDCPProtectionType& value /* @out */) const = 0;
        virtual uint32_t HDCPProtection (const HDCPProtectionType value) = 0;

        // @property
        // @brief Video output port on the STB used for connection to TV
        // @param name: video output port name
        virtual uint32_t PortName (string& name /* @out */) const = 0;

    };

    /* @json */
    struct EXTERNAL IHDRProperties : virtual public Core::IUnknown {
        enum { ID = ID_HDR_PROPERTIES };

        enum HDRType : uint8_t {
            HDR_OFF,
            HDR_10,
            HDR_10PLUS,
            HDR_HLG,
            HDR_DOLBYVISION,
            HDR_TECHNICOLOR
        };

        typedef RPC::IIteratorType<HDRType, ID_HDR_ITERATOR> IHDRIterator;

        // @property
        // @brief HDR formats supported by TV
        // @return HDRType: array of HDR formats
        virtual uint32_t TVCapabilities(IHDRIterator*& type /* @out */) const = 0;

        // @property
        // @brief HDR formats supported by STB
        // @return HDRType: array of HDR formats
        virtual uint32_t STBCapabilities(IHDRIterator*& type /* @out */) const = 0;

        // @property
        // @brief HDR format in use
        // @param type: HDR format
        virtual uint32_t HDRSetting(HDRType& type /* @out */) const = 0;
    };

    /* @json */
    struct EXTERNAL IDisplayProperties : virtual public Core::IUnknown {
        enum { ID = ID_DISPLAY_PROPERTIES };

        enum ColourSpaceType : uint8_t {
            FORMAT_UNKNOWN,
            FORMAT_OTHER,
            FORMAT_RGB_444,
            FORMAT_YCBCR_444,
            FORMAT_YCBCR_422,
            FORMAT_YCBCR_420
        };

        enum FrameRateType : uint8_t {
            FRAMERATE_UNKNOWN,
            FRAMERATE_23_976,
            FRAMERATE_24,
            FRAMERATE_25,
            FRAMERATE_29_97,
            FRAMERATE_30,
            FRAMERATE_47_952,
            FRAMERATE_48,
            FRAMERATE_50,
            FRAMERATE_59_94,
            FRAMERATE_60,
            FRAMERATE_119_88,
            FRAMERATE_120,
            FRAMERATE_144
        };

        enum ColourDepthType : uint8_t {
            COLORDEPTH_UNKNOWN,
            COLORDEPTH_8_BIT,
            COLORDEPTH_10_BIT,
            COLORDEPTH_12_BIT
        };

        enum QuantizationRangeType : uint8_t {
            QUANTIZATIONRANGE_UNKNOWN,
            QUANTIZATIONRANGE_LIMITED,
            QUANTIZATIONRANGE_FULL
        };

        enum ColorimetryType : uint8_t {
            COLORIMETRY_UNKNOWN,
            COLORIMETRY_OTHER,
            COLORIMETRY_SMPTE170M,
            COLORIMETRY_BT709,
            COLORIMETRY_XVYCC601,
            COLORIMETRY_XVYCC709,
            COLORIMETRY_SYCC601,
            COLORIMETRY_OPYCC601,
            COLORIMETRY_OPRGB,
            COLORIMETRY_BT2020YCCBCBRC,
            COLORIMETRY_BT2020RGB_YCBCR
        };

        enum EotfType : uint8_t {
            EOTF_UNKNOWN,
            EOTF_OTHER,
            EOTF_BT1886,
            EOTF_BT2100,
            EOTF_SMPTE_ST_2084
        };
        typedef RPC::IIteratorType<ColorimetryType, ID_COLORIMETRY_ITERATOR> IColorimetryIterator;

        // @property
        // @brief Provides access to the display's Colour space (chroma subsampling format)
        // @param cs: colour space
        virtual uint32_t ColorSpace(ColourSpaceType& cs /* @out */) const = 0;

        // @property
        // @brief Provides access to Frame Rate
        // @param rate: frame rate
        virtual uint32_t FrameRate(FrameRateType& rate /* @out */) const = 0;

        // @property
        // @brief Provides access to display's colour Depth
        // @param colour: colour depth
        virtual uint32_t ColourDepth(ColourDepthType& colour /* @out */) const = 0;

        // @property
        // @brief Provides access to display's colorimetry
        // @param colorimetry: display colorimetry
        virtual uint32_t Colorimetry(IColorimetryIterator*& colorimetry /* @out */) const = 0;

        // @property
        // @brief Provides access to display's Qauntization Range
        // @param qr: quantization range
        virtual uint32_t QuantizationRange(QuantizationRangeType& qr /* @out */) const = 0;

        // @property
        // @brief Provides access to display's Electro optical transfer function
        // @param eotf: display's EOTF
        virtual uint32_t EOTF(EotfType& eotf /* @out */) const = 0;
    };
}
}
