/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 Metrological
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