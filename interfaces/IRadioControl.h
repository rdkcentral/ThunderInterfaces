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
#include "IDRM.h"

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    // @json
    struct EXTERNAL IRadioControl : virtual public Core::IUnknown {
        enum { ID = ID_RADIOCONTROL };

        struct RadioConfig {
            uint8_t radioIndex;       //Index for each radio mapped with physical radio Index of the device
            string hwmode;            //Operating mode for the radio (eg: a,b,bgn,ac)
            uint32_t channel;         //Operating channel for the radio
            bool acsEnable;           //Enable/diable auto channel selection
            bool dfsEnable;           //Enable/Disable dynamic frequency selection
            uint16_t guardInterval;   //Configure gaurdInterval value per radio
            bool status;              //Enable/Disable each radio
        };

        struct RadioCapabilities {
            uint8_t phyIndex;         //Physical index of each radio
            uint8_t noofBands;        //No of bands supported by each radio
            string suppFreqBands;     //List of frequency bands supported by each radio
            uint8_t maxnoofVaps;      //Maximum number of vaps supported by each radio

        };

        using IRadioCapIterator = RPC::IIteratorType<RadioCap, ID_RADIOCONTROL_RADIOCAP_ITERATOR>;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_RADIOCONTROL_NOTIFICATION };
            ~INotification() override = default;

            // events

        };
        ~IRadioControl() override = default;

        virtual uint32_t Register(IRadioControl::INotification* sink) = 0;
        virtual uint32_t Unregister(IRadioControl::INotification* sink) = 0;

        // @brief Provides available networks information
        virtual uint32_t DeviceCapabilities(string& country /* @out */, uint8_t& noofradios /* @out */, IRadioCapIterator*& radioCap /* @out */) const = 0;

        // @property
        // NOTE: Setting the config by indicating the radioindex.
        // @brief Provide config details for requested radioindex.
        virtual uint32_t Config(const uint8_t radioIndex /* @index */, RadioConfig& radioConfig /* @out */) const = 0;
        virtual uint32_t Config(const uint8_t radioIndex /* @index */,const RadioConfig& radioConfig) = 0;

        // @brief Change channel for provided radioIndex
        virtual uint32_t Channel(const uint8_t radioIndex /* @index */,const uint32_t radioChannel) = 0;

        // @brief Change status for provided radioIndex
        virtual uint32_t Status(const uint8_t radioIndex /* @index */, const bool status) = 0;

    };

} // namespace Exchange
} // namespace WPEFramework
