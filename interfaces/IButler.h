#pragma once

#include "Module.h"

// @stubgen:skip

namespace WPEFramework {
	namespace Exchange {

        struct IExternal;

		struct EXTERNAL IGroup : virtual public Core::IUnknown {

			enum { ID = 0x10000045 };

			virtual uint32_t Parent() const = 0;
			virtual string Base() const = 0;
			virtual RPC::IStringIterator* Names() const = 0;
		};

		struct EXTERNAL IButler : virtual public Core::IUnknown {

			enum { ID = 0x10000042 };

			struct EXTERNAL IObserver : virtual public Core::IUnknown {

				~IObserver() override = default;

				enum { ID = 0x10000043 };

				// Push changes. If the Current value changes or the condition of IExternal, the next method is called.
				virtual void Added(/* @out */ IExternal* element) = 0;
				virtual void Removed(/* @out */ IExternal* element) = 0;
			};

			struct EXTERNAL INotification : virtual public Core::IUnknown {

				enum { ID = 0x10000044 };

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
