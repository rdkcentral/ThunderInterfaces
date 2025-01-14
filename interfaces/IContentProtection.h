/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Metrological
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

    // @json 1.0.0
    struct EXTERNAL IContentProtection : virtual public Core::IUnknown {
        enum { ID = ID_CONTENTPROTECTION };

        ~IContentProtection() override = default;

        enum KeySystem : uint8_t {
            WIDEVINE /* @text:widevine */,
            PLAYREADY /* @text:playready */,
            CLEARKEY /* @text:clearkey */
        };

        enum State : uint8_t {
            ACTIVE /* @text:active */,
            INACTIVE /* @text:inactive */
        };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_CONTENTPROTECTION_NOTIFICATION };

            ~INotification() override = default;

            struct Status {
                enum State : uint8_t {
                    GRANTED = 1 /* @text:GRANTED */,
                    NOT_REQUIRED = 2 /* @text:NOT_REQUIRED */,
                    DENIED = 3 /* @text:DENIED */,
                    FAILED = 4 /* @text:FAILED */,
                };

                State state;
                int32_t failureReason;
            };

            // @alt onWatermarkStatusChanged
            virtual void WatermarkStatusChanged(uint32_t sessionId,
                const Status& status)
                = 0;
        };

        virtual uint32_t Register(INotification* notification) = 0;
        virtual uint32_t Unregister(INotification* notification) = 0;

        // @alt openDrmSession
        virtual uint32_t OpenDrmSession(const string& clientId,
            KeySystem keySystem, const string& licenseRequest,
            const string& initData /* @opaque */,
            uint32_t& sessionId /* @out */,
            string& response /* @text:openSessionResponse @opaque @out */)
            = 0;

        // @alt setDrmSessionState
        virtual uint32_t SetDrmSessionState(uint32_t sessionId,
            State sessionState)
            = 0;

        // @alt updateDrmSession
        virtual uint32_t UpdateDrmSession(uint32_t sessionId,
            const string& licenseRequest,
            const string& initData /* @opaque */,
            string& response /* @text:updateSessionResponse @opaque @out */)
            = 0;

        // @alt closeDrmSession
        virtual uint32_t CloseDrmSession(uint32_t sessionId) = 0;

        // @alt showWatermark
        virtual uint32_t ShowWatermark(uint32_t sessionId,
            bool show, bool localOverlay)
            = 0;

        // @alt setPlaybackPosition
        virtual uint32_t SetPlaybackPosition(uint32_t sessionId,
            int32_t speed, long position)
            = 0;
    };

} // namespace Exchange
} // namespace Thunder
