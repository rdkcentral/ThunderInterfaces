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
#include "../Module.h"

namespace WPEFramework {
    namespace Exchange {
        namespace External {
            // This interface allows for retrieval of memory usage specific to the implementor
            // of the interface
			class Metadata : public Core::JSON::Container {
			public:
				Metadata(const Metadata&) = delete;
				Metadata& operator=(const Metadata&) = delete;

				enum protocol : uint8_t {
					I2C,
					ONEWIRE,
					NRF24L01,
					GPIO,
					ZWAVE,
					ZIGBEE,
					JSONRPC,
					VIRTUAL
				};

				Metadata()
					: Manufacturer()
					, Protocol()
				{
					Add(_T("manufacturer"), &Manufacturer);
					Add(_T("source"), &Protocol);
				}
				~Metadata() override = default;

			public:
				Core::JSON::String Manufacturer;
				Core::JSON::EnumType<protocol> Protocol;
			};
        }
    }

	ENUM_CONVERSION_HANDLER(Exchange::External::Metadata::protocol);
}
