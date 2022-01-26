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
#include "IValuePoint.h"

namespace WPEFramework {
namespace Exchange {
    struct EXTERNAL IExternal : virtual public Core::IUnknown {
        enum { ID = ID_EXTERNAL };

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_EXTERNAL_NOTIFICATION };

            // Push changes. If the Current value changes, the next method is called.
            virtual void Update(const uint32_t id) = 0;
        };

        struct EXTERNAL ICatalog : virtual public Core::IUnknown {
            enum { ID = ID_EXTERNAL_CATALOG };

            struct EXTERNAL INotification : virtual public Core::IUnknown {
                enum { ID = ID_EXTERNAL_CATALOG_NOTIFICATION };

                virtual void Activated(IExternal* source) = 0;
                virtual void Deactivated(IExternal* source) = 0;
            };

            // Pushing notifications to interested sinks
            virtual void Register(ICatalog::INotification* sink) = 0;
            virtual void Unregister(ICatalog::INotification* sink) = 0;
            virtual IExternal* Resource(const uint32_t id) = 0;
        };

        using basic = IValuePoint::basic;
        using specific = IValuePoint::specific;
        using dimension = IValuePoint::dimension;

        enum condition : uint8_t {
            constructing = 0x00,
            activated    = 0x01,
            deactivated  = 0x02
        };

        // Pushing notifications to interested sinks
        virtual void Register(INotification* sink) = 0;
        virtual void Unregister(INotification* sink) = 0;

        // Element require communication, so might fail, report our condition
        virtual condition Condition() const = 0;

        // Identification of this element.
        virtual uint32_t Identifier() const = 0;

        // Characteristics of this element
        virtual uint32_t Type() const = 0;

        // Value determination of this element
        virtual int32_t Minimum() const = 0;
        virtual int32_t Maximum() const = 0;

        virtual uint32_t Get(int32_t& value /* @out */) const = 0;
        virtual uint32_t Set(const int32_t value) = 0;

        // Periodically we might like to be evaluated, call this method at a set time.
        virtual void Evaluate() = 0;

        // There most be more than meets the eye, report it as a JSON string..
        virtual string Metadata() const = 0;

        // ------------------------------------------------------------------------
        // Convenience methods to extract interesting information from the Type()
        // ------------------------------------------------------------------------
        static basic Basic(const uint32_t instanceType);
        static dimension Dimension(const uint32_t instanceType);
        static specific Specific(const uint32_t instanceType);
        static uint8_t Decimals(const uint32_t instanceType);
        static uint32_t Type(const basic base, const specific spec, const dimension dim, const uint8_t decimals);
    };

} } // Namespace Exchange
