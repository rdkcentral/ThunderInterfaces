/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
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

    struct EXTERNAL ISystemAudioPlayer : virtual public Core::IUnknown {
        enum { ID = ID_SYSTEMAUDIOPLAYER };

        struct INotification : virtual public Core::IUnknown {
            enum { ID = ID_SYSTEMAUDIOPLAYER_NOTIFICATION };

            virtual ~INotification() {}
            virtual void OnSAPEvents(const string &data) = 0;        
        };

        virtual ~ISystemAudioPlayer() {}

        virtual uint32_t Configure(PluginHost::IShell* service) = 0;
        virtual void Register(INotification* sink) = 0;
        virtual void Unregister(INotification* sink) = 0;

        virtual uint32_t Open(const string &input, string &output /* @out */) = 0;
        virtual uint32_t Play(const string &input, string &output /* @out */) = 0;
        virtual uint32_t PlayBuffer(const string &input, string &output /* @out */) = 0;
        virtual uint32_t Pause(const string &input, string &output /* @out */) = 0;
        virtual uint32_t Resume(const string &input, string &output /* @out */) = 0;
        virtual uint32_t Stop(const string &input, string &output /* @out */) = 0;
        virtual uint32_t Close(const string &input, string &output /* @out */) = 0;
        virtual uint32_t SetMixerLevels(const string &input, string &output /* @out */) = 0;
        virtual uint32_t SetSmartVolControl(const string &input, string &output /* @out */) = 0;
        virtual uint32_t IsPlaying(const string &input, string &output /* @out */) = 0;
	virtual uint32_t Config(const string &input, string &output /* @out */) = 0;
        virtual uint32_t GetPlayerSessionId(const string &input, string &output /* @out */) = 0;

    };

} // Exchange
} // Thunder
