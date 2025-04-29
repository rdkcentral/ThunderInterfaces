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
 
 
 namespace Thunder {
 
 namespace Exchange {
 
     /* @json 1.0.0 */
     struct ITopicExchange2 : virtual public Core::IUnknown {
         enum { ID = ID_TOPICEXCHANGE };
 
         enum payloadtype : uint8_t {
             ONE,
             TWO
         };

         // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
             enum { ID = ID_TOPICEXCHANGE_NOTIFICATION };
 
             virtual void Connected() = 0;
             virtual void Disconnected(const string& reason) = 0;
         };
 
         virtual Core::hresult Register(INotification* const sink) = 0;
         virtual Core::hresult Unregister(const INotification* const sink) = 0;
 
 
         /* are these really needed for the client, should the client even be aware of the connections, isn't it more internal?? */
         /* note in R4_4 there is no good way to call the Disconnect when the client channel is closed without a Disconnect first. */
         virtual Core::hresult Connect(const uint32_t operationTimeout,	const uint32_t retryInterval, const uint32_t maximumRetryTimeout) = 0;
         virtual Core::hresult Disconnect() = 0;
         virtual Core::hresult getConnectionStatus(/* add some usefull out params here */) const;
 
         // @event
         struct EXTERNAL IMsgNotification : virtual public Core::IUnknown {
         enum { ID = ID_TOPICEXCHANGE_TOPIC_MSGNOTIFICATION };
 
                 virtual void Message(const string& topicID /* @index */,  const string& payload, const payloadtype payloadtype) = 0;
         };
 
         /* @json:omit */
         virtual Core::hresult Register(const string& topicID, INotification* const sink) = 0;
         /* @json:omit */
         virtual Core::hresult Unregister(const string& topicID, const INotification* const sink) = 0;
 
         /* note is this really needed? This can be done but you need to keep your own list (using the status listeners which in 4.4 must use the client ID 
                                        as they do not yet provide the channel info). Please do not use any way to get to the internal list but you need to 
                                        build your own list, and why do this to provide info to the client who just could if needed keep this list local to 
                                        the client reducing unnecessary memoroy in the plugin and overhead to get this info
         */
         virtual Core::hresult getListOfSubscribedTopics(/* use a string iterator here I guess*/) const = 0;
 
         virtual Core::hresult Publich(const string& topicID, const string& payload, const payloadtype payloadtype) = 0;
         virtual Core::hresult Fetch(const string& topicID, string& payload /* @out */, payloadtype& payloadtype /* @out */) = 0;
     };
 
 } // namespace Exchange
 
 } // namespace WPEFramework
 