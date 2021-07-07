/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
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
**/

#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

struct IMediaPlayer : virtual public Core::IUnknown {

    enum { ID = ID_MEDIAPLAYER };

    struct IMediaStream : virtual public Core::IUnknown {

        enum { ID = ID_MEDIASTREAM };

        struct INotification : virtual public Core::IUnknown {

            enum { ID = ID_MEDIASTREAM_NOTIFICATION };

            ~INotification() override = default;

            virtual void Event(const string& eventName, const string& parametersJson) = 0;
        };

        ~IMediaStream() override = default;

        virtual uint32_t Load(const string& url, bool autoPlay) = 0;
        virtual uint32_t SetRate(int32_t rate) = 0;
        virtual uint32_t SeekTo(int32_t positionSec) = 0;
        virtual uint32_t Stop() = 0;
        virtual uint32_t InitConfig(const string& configurationJson) = 0;
        virtual uint32_t InitDRMConfig(const string& configurationJson) = 0;
        virtual uint32_t Register(INotification* notification) = 0;
        virtual uint32_t Unregister(INotification* notification) = 0;
    };

    ~IMediaPlayer() override = default;

    virtual IMediaStream* CreateStream(const string& id) = 0;
};

}
}
