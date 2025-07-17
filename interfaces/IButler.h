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
#include <plugins/IShell.h>
#include <interfaces/IValuePoint.h>

// @stubgen:include <com/ICOM.h>
// @stubgen:include "IValuePoint.h"

namespace Thunder {
	namespace Exchange {

		// @json 1.0.0 
		struct EXTERNAL IButler : virtual public Core::IUnknown {
			~IButler() override = default;

			enum { ID = ID_BUTLER };

			// @event
			struct EXTERNAL INotification : virtual public Core::IUnknown {
				~INotification() override = default;

				enum { ID = ID_BUTLER_NOTIFICATION };

				// Push changes. If we a new IValuePoint is offered or revoked
				virtual void Added(IValuePoint* const element) = 0;
				virtual void Removed(IValuePoint* const element) = 0;

				// Push changes. If the Current value changes.
				virtual void Updated(IValuePoint* const element) = 0;

				// Push changes. If the Current metadata of the value point changes
				virtual void Metadata(IValuePoint* const element)= 0;
			};

			// Register for any changes on the elements the butler knows.
			virtual Core::hresult Register(INotification* const sink) = 0;
			virtual Core::hresult Unregister(const INotification* sink) = 0;

			// Get Access to a specific IValuePoint, by specifying a proper identifaction. 
			virtual Core::hresult Name(const string& name, IValuePoint*& valuePoint /* @out */) = 0;
			virtual Core::hresult Identifier(const uint32_t id, IValuePoint*& valuePoint /* @out */) = 0;

			virtual Core::hresult Branch(const string& path) = 0;
			virtual Core::hresult Move(const string& path, const string& newName) = 0;
			virtual Core::hresult Delete(const string& path) = 0;

			// Returns the callsign of the plugin that is the origin of this IValuePoint Id.
			virtual Core::hresult Source(const uint32_t id, string& callsign/* @out */) const = 0;

			// Associate (link) the given IValuePoint id to given path with leaf name.
			virtual Core::hresult Link(const string& name, const uint32_t id) = 0;

			// Returns all the ValuePointis that have no name but are announced through the
			// ICatalog of the IValuePoint.
      virtual Core::hresult Orphans(const uint8_t module, RPC::IValueIterator*& iterator /* @out */) const = 0;
		};
	}
} // Namespace Exchange
