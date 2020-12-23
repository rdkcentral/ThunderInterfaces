/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
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

    // This interface gives direct access to a Browser to change
    // Browser specific properties like displayed URL.

    struct EXTERNAL IBrowser : virtual public Core::IUnknown {
        enum { ID = ID_BROWSER };

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_BROWSER_NOTIFICATION };

            // Signal changes on the subscribed namespace..
            virtual void LoadFinished(const string& URL) = 0;
            virtual void URLChanged(const string& URL) = 0;
            virtual void Hidden(const bool hidden) = 0;
            virtual void Closure() = 0;
        };

        virtual void Register(IBrowser::INotification* sink) = 0;
        virtual void Unregister(IBrowser::INotification* sink) = 0;

        // Change the currently displayed URL by the browser.
        virtual void SetURL(const string& URL) = 0;
        virtual string GetURL() const = 0;

        virtual uint32_t GetFPS() const = 0;

        virtual void Hide(const bool hidden) = 0;
    };

    /* @json */
    struct EXTERNAL IWebBrowser : virtual public Core::IUnknown {
        enum { ID = ID_WEB_BROWSER };

        enum Visibility : uint8_t {
            HIDDEN = 0,
            VISIBLE = 1,
        };

        enum HTTPCookieAcceptPolicyType : uint8_t {
            ALWAYS = 0,
            NEVER  = 1,
            ONLY_FROM_MAIN_DOCUMENT_DOMAIN = 2,
            EXCLUSIVELY_FROM_MAIN_DOCUMENT_DOMAIN = 3
        };

        /* @event */
        struct INotification : virtual public Core::IUnknown {
            enum { ID = ID_WEBKITBROWSER_NOTIFICATION };

            // Signal changes on the subscribed namespace..
            // @brief Initial HTML document has been completely loaded and parsed
            // @param URL The URL that has been loaded
            // @param code The response code of main resource request
            virtual void LoadFinished(const string& URL, const int32_t code) = 0;
            // @brief Browser failed to load page
            // @param URL The URL that has been failed to load
            virtual void LoadFailed(const string& URL) = 0;
            // @brief Signals a URL change in the browser
            // @param URL The URL that has been loaded or requested
            // @param loaded loaded (true) or not (false)
            virtual void URLChange(const string& URL, const bool loaded) = 0;
            // @brief Signals a visibility change of the browser
            // @param hidden hidden (true) or visible (false)
            virtual void VisibilityChange(const bool hidden) = 0;
            // @brief Notifies that the web page requests to close its window
            virtual void PageClosure() = 0;
            // @brief Base64 encoded JSON message from legacy $badger bridge
            virtual void BridgeQuery(const string& message) = 0;
        };

        virtual void Register(INotification* sink) = 0;
        virtual void Unregister(INotification* sink) = 0;

        // @property
        // @brief Page loaded in the browser
        // @param url Loaded URL
        virtual uint32_t URL(string& url /* @out */) const = 0;
        virtual uint32_t URL(const string& url) = 0;

        // @property
        // @brief Browser window visibility state
        // @param visible Visiblity state
        virtual uint32_t Visible(bool& visible /* @out */) const = 0;
        virtual uint32_t Visible(const bool visible) = 0;

        // @property
        // @brief Current framerate the browser is rendering at
        // @param fps Current FPS
        virtual uint32_t FPS(uint8_t& fps /* @out */) const = 0;

        // @property
        // @brief Headers to send on all requests that the browser makes
        // @param header Header Name
        virtual uint32_t Headers(string& header /* @out */) const = 0;
        virtual uint32_t Headers(const string& header) = 0;

        // @property
        // @brief UserAgent string used by the browser
        // @param useragent UserAgent value
        virtual uint32_t UserAgent(string& ua /* @out */) const = 0;
        virtual uint32_t UserAgent(const string& ua) = 0;

        // @property
        // @brief User preferred languages used by the browser
        // @param language Preferred language
        virtual uint32_t Languages(string& langs /* @out */) const = 0;
        virtual uint32_t Languages(const string& langs) = 0;

        // @property
        // @brief Controls the local storage availability
        // @param state enabled or disabled
        virtual uint32_t LocalStorageEnabled(bool& enabled /* @out */) const = 0;
        virtual uint32_t LocalStorageEnabled(const bool enabled) = 0;

        // @property
        // @brief HTTP cookies accept policy
        // @param policy HTTP Cookie Accept Policy Type
        virtual uint32_t HTTPCookieAcceptPolicy(HTTPCookieAcceptPolicyType& policy /* @out */) const = 0;
        virtual uint32_t HTTPCookieAcceptPolicy(const HTTPCookieAcceptPolicyType policy) = 0;

        // @brief Response for legacy $badger.
        // @param payload base64 encoded JSON string response to be delivered to $badger.callback(pid, success, json)
        virtual uint32_t BridgeReply(const string& payload) = 0;
        // @brief Send legacy $badger event.
        // @param payload base64 encoded JSON string response to be delivered to window.$badger.event(handlerId, json)
        virtual uint32_t BridgeEvent(const string& payload) = 0;

    };

}
}
