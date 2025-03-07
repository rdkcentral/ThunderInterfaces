/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2021 Metrological
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

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IIOConnector : virtual public Core::IUnknown {

    enum { ID = ID_IOCONNECTOR };

    // @event
    struct EXTERNAL INotification : virtual public Core::IUnknown {

        enum { ID = ID_IOCONNECTOR_NOTIFICATION };

        // @brief Notifies about GPIO pin activity
        // @description Register to this event to be notified about pin value changes
        // @param id: pin ID (e.g. 189)
        virtual void Activity(const string& id /* @index */, const int32_t& value) = 0;
    };

    virtual Core::hresult Register(const string& id, INotification* const notification) = 0;
    virtual Core::hresult Unregister(const string& id, const INotification* const notification) = 0;

    // @property
    // @brief GPIO pin value
    // @param index: pin ID (e.g. 189)
    // @param pinvalue: Value of the pin (e.g. 1)
    // @retval ERROR_UNKNOWNKEY Unknown pin ID given
    virtual Core::hresult Pin(const string& index /* @index */, const int32_t& pinvalue) = 0;
    virtual Core::hresult Pin(const string& index /* @index */, int32_t& pinvalue /* @out */) const = 0;

    };

} // namespace Exchange

}
