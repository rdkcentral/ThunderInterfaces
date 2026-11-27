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
#include "ITestDelegatedReleasePeer.h"

// @stubgen:include "ITestDelegatedReleasePeer.h"

namespace Thunder {
namespace QualityAssurance {

    struct EXTERNAL ITestDelegatedRelease : virtual public Core::IUnknown {
        enum { ID = ID_TESTDELEGATEDRELEASE };

        ~ITestDelegatedRelease() override = default;

        virtual Core::hresult Ping(uint32_t& value /* @out */) = 0;
        // @brief Retain a peer for the lifetime of the COM-RPC channel.
        //        Each call retains one reference; the references are released when the channel closes.
        // @param peer: Interface pointer the callee keeps beyond the call. The callee MUST AddRef()
        //              it to retain it; otherwise it may be destroyed when the call returns.
        //              The caller keeps and releases its own reference.
        virtual Core::hresult HoldPeer(ITestDelegatedReleasePeer* peer /* @in */) = 0;
    };

} // namespace QualityAssurance
} // namespace Thunder