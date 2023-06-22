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

namespace WPEFramework {
namespace Exchange {

    // @stubgen:omit
    struct EXTERNAL ICompositionBuffer {
        /**
         * @brief   frame buffer interface with hardware optimisation in mind
         */

        using buffer_id = uintptr_t;

        enum DataType : uint8_t {
            TYPE_INVALID = 0x00, // Invalid buffer
            TYPE_DMA = 0x01, // DMA buffer  
            TYPE_RAW = 0x02 // Raw buffer
        };

        virtual ~ICompositionBuffer() = default;

        struct IPlane {
            virtual ~IPlane() = default;

            virtual buffer_id Accessor() const = 0; // Access to the actual data.

            virtual uint32_t Stride() const = 0; // Bytes per row for a plane [(bit-per-pixel/8) * width]
            virtual uint32_t Offset() const = 0; // Offset of the plane from where the pixel data starts in the buffer.
        };

        struct IIterator {
            virtual ~IIterator() = default;

            virtual bool IsValid() const = 0;
            virtual void Reset() = 0;
            virtual bool Next() = 0;

            virtual IPlane* Plane() = 0;
        };

        virtual void AddRef() const = 0;
        virtual uint32_t Release() const = 0;

        virtual uint32_t Identifier() const = 0;

        virtual IIterator* Planes(const uint32_t timeoutMs) = 0; // Access the planes.
        virtual uint32_t Completed(const bool dirty) = 0; // Called by callee when is done with the planes.

        virtual void Render() = 0; // Mark for scanout.

        virtual uint32_t Width() const = 0; // Width of the allocated buffer in pixels
        virtual uint32_t Height() const = 0; // Height of the allocated buffer in pixels
        virtual uint32_t Format() const = 0; // Layout of a pixel according the fourcc format
        virtual uint64_t Modifier() const = 0; // Pixel arrangement in the buffer, used to optimize for hardware

        virtual DataType Type() const = 0;
    }; // struct ICompositionBuffer

} // namespace Exchange

} // namespace WPEFramework
