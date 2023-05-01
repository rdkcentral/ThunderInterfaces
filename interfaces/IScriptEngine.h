#pragma once
#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    // @json 
    struct EXTERNAL IScriptEngine : virtual public Core::IUnknown {
        enum { ID = ID_SCRIPT_ENGINE };

	// @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_SCRIPT_ENGINE_NOTIFICATION };

            ~INotification() override = default;

            // Signal changes on the subscribed namespace..
            virtual void URLChanged(const string& URL) = 0;
        };

        ~IScriptEngine() override = default;

        virtual Core::hresult Register(INotification* sink /* @in */) = 0;
        virtual Core::hresult Unregister(const INotification* sink /* @in */) = 0;

        // @property
        // @brief Script to be loaded into the engine and to be executed.
        // @param url Loaded URL (e.g. https://example.com)
        virtual Core::hresult URL(string& url /* @out */) const = 0;
        virtual Core::hresult URL(const string& url) = 0;
    };
}
}

