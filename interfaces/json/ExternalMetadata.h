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
