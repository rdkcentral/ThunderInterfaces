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
		// @stubgen:omit
        struct IExternal;

		// @stubgen:omit
		struct EXTERNAL IGroup : virtual public Core::IUnknown {

			enum { ID = ID_BUTLER_GROUP };

			virtual uint32_t Parent() const = 0;
			virtual string Base() const = 0;
			virtual RPC::IStringIterator* Names() const = 0;
		};

		// @stubgen:omit
		struct EXTERNAL IButler : virtual public Core::IUnknown {

			enum { ID = ID_BUTLER };

			struct EXTERNAL IObserver : virtual public Core::IUnknown {

				~IObserver() override = default;

				enum { ID = 0x10000043 };

				// Push changes. If the Current value changes or the condition of IExternal, the next method is called.
				virtual void Added(/* @out */ IExternal* element) = 0;
				virtual void Removed(/* @out */ IExternal* element) = 0;
			};

			struct EXTERNAL INotification : virtual public Core::IUnknown {

				enum { ID = ID_BUTLER_NOTIFICATION };

				// Push changes. If the Current value changes or the condition of IExternal, the next method is called.
				virtual void Updated(/* @out */ IExternal* element) = 0;
			};

			// Register for new/modified or deleted extenals.
			virtual void Register(IObserver* sink) = 0;
			virtual void Unregister(IObserver* sink) = 0;

			// Register for any changes on the elements the butler knows.
			virtual void Register(INotification* sink) = 0;
			virtual void Unregister(INotification* sink) = 0;

			// Get Access to a specific IExternal, by specifying a proper identifaction. 
			virtual IExternal* Element(const string& name) = 0;
			virtual IExternal* Element(const uint32_t id) = 0;
			virtual string Source(const uint32_t module) const = 0;

			virtual uint32_t Branch(const string& path) = 0;
			virtual uint32_t Link(const string& path, const uint32_t id) = 0;
			virtual uint32_t Move(const string& path, const string& newName) = 0;
			virtual uint32_t Delete(const string& path) = 0;

			virtual RPC::IValueIterator* Orphans(const uint8_t module) const = 0;
		};
	}
} // Namespace Exchange
