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

namespace Thunder {
namespace Exchange {

    // The ICompositionBuffer is an interface definition to communicate across 
    // process boundaries between two actors, the Client and the Compositor. 
    // Client:     Producing content in the buffer
    // Compositor: Consuming the content (move to another Buffer)
    // 
    // From a Client perspective:
    // 1) ICompositionBuffer::Acquire(50)
    //    Locks the planes so the Compositor can not and will not use this
    //    buffer in the process of creating a new composition.
    // 2) IIterator::Plane::Accessor()
    //    Write anything the client likes onto the buffer
    // 3) ICompositionBuffer::Relinquish()
    //    Unlock the planes, the Compositor can use/consume what is on the 
    //    buffer and move it to wherever the compositor likes.
    //
    // From a Compositor perspective:
    // 1) a screen update is requested, iterate over all Buffers available 
    //    in the Compositor and call ICompositionBuffer::Acquire(0), no need 
    //    to wait cause if the producer (Client) is working on the buffer we
    //    do not want to consume it.
    // 2) IIterator::Plane::Accessor()
    //    Read anything from the buffer the client has written on it and move it
    //    to a new buffer.
    // 3) ICompositionBuffer::Relinquish()
    //    Unlock the planes, the Client can use/produce new contents on the  
    //    buffer. The content how it was is now copied to a new location.

    // NOTE:
    // --------------------------------------------------------------------------
    // This is delibratly *NOT* a COMRPC interface as the communication and the 
    // exchange over the process boundaries must be done with OS native features
    // to enforce the best performance!

    // @stubgen:omit
    struct EXTERNAL ICompositionBuffer {
        virtual ~ICompositionBuffer() = default;
        
        /**
         * @brief   frame buffer interface with hardware optimisation in mind
         */
        enum DataType : uint8_t {
            TYPE_INVALID = 0x00, // Invalid buffer
            TYPE_DMA = 0x01, // DMA buffer  
            TYPE_RAW = 0x02 // Raw buffer
        };

        struct IIterator {
            virtual ~IIterator() = default;

            virtual bool IsValid() const = 0;
            virtual void Reset() = 0;
            virtual bool Next() = 0;

            virtual int Descriptor() const = 0; // Access to the actual data.

            virtual uint32_t Stride() const = 0; // Bytes per row for a plane [(bit-per-pixel/8) * width]
            virtual uint32_t Offset() const = 0; // Offset of the plane from where the pixel data starts in the buffer.
        };

        // Acquire (lock) the planes (Compositor or Client), the 
        // other user (Client or Compositor) of this object (process 
        // agnostic) can now not access the planes, they have to 
        // wait till they become availabe again.....
        virtual IIterator* Acquire(const uint32_t timeoutMs) = 0;
        // Relinquish (unlock) the Planes. End lifetime of the IIterator
        // received from Planes()
        virtual void Relinquish() = 0;

        virtual uint32_t Width() const = 0; // Width of the allocated buffer in pixels
        virtual uint32_t Height() const = 0; // Height of the allocated buffer in pixels
        virtual uint32_t Format() const = 0; // Layout of a pixel according the fourcc format
        virtual uint64_t Modifier() const = 0; // Pixel arrangement in the buffer, used to optimize for hardware

        virtual DataType Type() const = 0;
    }; // struct IPlainBuffer

} // namespace Exchange

} // namespace Thunder
