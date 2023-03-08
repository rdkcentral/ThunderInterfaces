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

    /* json */
    struct EXTERNAL IValuePoint : virtual public Core::IUnknown {
        enum { ID = ID_VALUE_POINT };

        /* json omit */
        struct EXTERNAL ICatalog : virtual public Core::IUnknown {
            enum { ID = ID_VALUE_POINT_CATALOG };

            /* json omit */
            struct EXTERNAL INotification : virtual public Core::IUnknown {
                enum { ID = ID_VALUE_POINT_CATALOG_NOTIFICATION };

                virtual void Activated(IValuePoint* source) = 0;
                virtual void Deactivated(IValuePoint* source) = 0;
            };

            // Pushing notifications to interested sinks
            virtual void Register(ICatalog::INotification* sink) = 0;
            virtual void Unregister(const ICatalog::INotification* sink) = 0;
            virtual IValuePoint* Resource(const uint32_t id) = 0;
        };

        /* event */
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_VALUE_POINT_NOTIFICATION };

            // Push changes. If the Current value changes, the next method is called.
            virtual void Update(const uint32_t id) = 0;
            virtual void Metadata(const uint32_t id) = 0;
        };

        //  Basic/specific and dimension together define the Type.
        // 32     13    | 3 |  4  |     12     |
        //  +---------------+------------------+
        //  | dimension |FLT|basic|  specific  |
        //  +---------------+------------------+
        //  FLT = Floating point. The number of decimals thats
        //        should be considerd to be the remainder.
        //        3 bits (0..7)
        //
        enum basic : uint8_t { /* 4 bits (16)*/
            regulator = 0x0,
            measurement = 0x1,
            group = 0xE,
            identification = 0xF
        };

        enum specific : uint16_t { /* 12 bits (4096) */
            general = 0x000,
            electricity = 0x001,
            water = 0x002,
            gas = 0x003,
            air = 0x004,
            smoke = 0x005,
            carbonMonoxide = 0x006,
            carbonDioxide = 0x007,
            temperature = 0x008,
            accessControl = 0x009,
            burglar = 0x00A,
            powerManagement = 0x00B,
            system = 0x00C,
            emergency = 0x00D,
            clock = 0x00E,
            light = 0x00F
        };

        enum dimension : uint16_t { /* 13 bits (8192) */
            logic = 0x0000, /* values 0 or 1  */
            percentage = 0x0001, /* values 0 - 100 */
            kwh = 0x0002, /* kilo Watt hours  */
            kvah = 0x0003, /* kilo Volt Ampere hours */
            pulses = 0x0004, /* counter */
            degrees = 0x0005, /* temperture in degrees celsius */
            units = 0x0006, /* unqualified value, just units */
            lux = 0x0007,
            volt = 0x0008,
            ampere = 0x0009
        };

        enum condition : uint8_t {
            constructing = 0x00,
            activated    = 0x01,
            deactivated  = 0x02
        };

        // Pushing notifications to interested sinks
        virtual void Register(INotification* sink) = 0;
        virtual void Unregister(INotification* sink) = 0;

        // @property
        // @brief Each IValuePoint instance has a unique identifier that identifies the instance. The 
        //        value returned here return the unique ID of this IValuePoint.
        // @param ID is the unique identification of this element.
        virtual uint32_t Identifier(uint32_t& ID /* @out */) const = 0;

        // @property
        // @brief If this IValuePoint belongs to a bundle that has multiple IValuePoints the id
        //        that identifies the bundle and the result will be Core::ERROR_NONE. If it does 
        //        not belong to a bundle, this call returns Core::ERROR_UNAVAILABLE,
        // @param ID is the unique identification of the parent element.
        virtual uint32_t Bundle(uint32_t& ID /* @out */) const = 0;

        // @property
        // @brief Current state/condition of this IValuePoint
        // @param value is the current condition of this IValuePoint 
        virtual uint32_t Condition(condition& value /* @out */) const = 0;

        // @property
        // @brief Characteristics of this IElement
        // @param value represent the characteristics of this IValuePoint 
        virtual uint32_t Type(uint32_t& value /* @out */) const = 0;

        // @property
        // @brief The minimum value this IElement can reach.
        // @param value represent the minimum value this IValuePoint can reach.
        virtual uint32_t Minimum(int32_t& value /* @out */) const = 0;

        // @property
        // @brief The maximum value this IElement can reach.
        // @param value represent the maxium value this IValuePoint can reach.
        virtual uint32_t Maximum(int32_t& value /* @out */) const = 0;

        // @property
        // @brief The current value of this IValuePoint.
        // @param value represent the current value of this IValuePoint.
        virtual uint32_t Value(int32_t& value /* @out */) const = 0;
        virtual uint32_t Value(const int32_t value) = 0;

        // @property
        // @brief There most be more than meets the eye, report it as a JSON string.
        // @param value represent the metadata associated with this IValuePoint.
        // 
        virtual uint32_t Metadata(string& value /* @out */) const = 0;

        // Periodically we might like to be evaluated, call this method at a set time.
        /* @json:omit */
        virtual bool Evaluate() = 0;

        // ------------------------------------------------------------------------
        // Convenience methods to extract interesting information from the Type()
        // ------------------------------------------------------------------------
        /* json:omit */
        static basic Basic(const uint32_t instanceType);
        /* json:omit */
        static dimension Dimension(const uint32_t instanceType);
        /* json:omit */
        static specific Specific(const uint32_t instanceType);
        /* json:omit */
        static uint8_t Decimals(const uint32_t instanceType);
        /* json:omit */
        static uint32_t Type(const basic base, const specific spec, const dimension dim, const uint8_t decimals);
    };

} } // Namespace Exchange
