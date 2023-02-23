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

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
	namespace Exchange {

		struct IValuePoint;

		struct EXTERNAL IButler : virtual public Core::IUnknown {

			~IButler() override = default;

			enum { ID = ID_BUTLER };

			struct EXTERNAL INotification : virtual public Core::IUnknown {

				~INotification() override = default;

				enum { ID = ID_BUTLER_NOTIFICATION };

				// Push changes. If we a new IValuePoint is offered or revoked
				virtual void Added(IValuePoint* element) = 0;
				virtual void Removed(IValuePoint* element) = 0;

				// Push changes. If the Current value changes.
				virtual void Updated(IValuePoint* element) = 0;

				// Push changes. If the Current metadata of the value point changes
				virtual void Metadata(IValuePoint* element) = 0;
			};

			// Register for any changes on the elements the butler knows.
			virtual void Register(INotification* sink) = 0;
			virtual void Unregister(INotification* sink) = 0;

			// Get Access to a specific IValuePoint, by specifying a proper identifaction. 
			virtual IValuePoint* Element(const string& name) = 0;
			virtual IValuePoint* Element(const uint32_t id) = 0;
			virtual string Source(const uint32_t module) const = 0;

			virtual uint32_t Branch(const string& path) = 0;
			virtual uint32_t Link(const string& path, const uint32_t id) = 0;
			virtual uint32_t Move(const string& path, const string& newName) = 0;
			virtual uint32_t Delete(const string& path) = 0;

			virtual RPC::IValueIterator* Orphans(const uint8_t module) const = 0;
		};
	}
} // Namespace Exchange
