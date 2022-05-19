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

namespace WPEFramework {

	namespace Exchange {

		struct EXTERNAL IRustBridge : virtual public Core::IUnknown {
			
			enum { ID = ID_RUST_BRIDGE };

			struct EXTERNAL ICallback : virtual public Core::IUnknown {
				
				enum { ID = ID_RUST_BRIDGE_NOTIFICATION };
				
				~ICallback() override = default;

				// ALLOW RUST -> THUNDER (Invoke and Event)
				// The synchronous Invoke from a JSONRPC is coming from the RUST world,
				// synchronously handle this in the Thunder world.
				virtual void Invoke(const string& context, const string& method, const string& parmeters, string& response /* @out */, uint32_t& result /* @out */) = 0;
				
				// Allow RUST to send an event to the interested subscribers in the Thunder
				// world.
				virtual void Event(const string& event, const string& parmeters) = 0;

				// This is the response form the RUST side of things for the Request that was send..
				virtual void Response(const uint32_t id, const string& response, const uint32_t error) = 0;
			};

			~IRustBridge() override = default;		
			
			virtual uint32_t Configure(PluginHost::IShell* framework, ICallback* callback) = 0;
			
			// ALLOW THUNDER -> RUST (Invoke and Event)
			// The synchronous Invoke from a JSONRPC perspective has been splitup into an 
			// a-synchronous communication to RUST. First we send a Request with an id,
			// Than it is up to RUST (ICallback) to send a response (with the same id) to 
			// complete.
			virtual void Request(const uint32_t id, const string& context, const string& method, const string& parmeters) = 0;
			
			// Allow THUNDER to send an event to the interested subscribers in the RUST
			// world.
			virtual void Event(const string& event, const string& parmeters) = 0;
		};
	}
} // Namespace Exchange
