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
// @insert <com/IIteratorType.h>

namespace Thunder {

namespace Exchange {

    /* @json 1.0.0 */
    struct ITopicExchange : virtual public Core::IUnknown {
        enum { ID = ID_TOPICEXCHANGE };

        enum payloadtype : uint8_t {
            ONE,
            TWO
        };

        struct EXTERNAL ITopic : virtual public Core::IUnknown {
            enum { ID = ID_TOPICEXCHANGE_TOPIC };

            struct EXTERNAL IMsgNotification : virtual public Core::IUnknown {
                enum { ID = ID_TOPICEXCHANGE_TOPIC_MSGNOTIFICATION };

                virtual void Message(const string& payload, const payloadtype payloadtype) = 0;
            };

            virtual Core::hresult Register(IMsgNotification* const sink) = 0;
            virtual Core::hresult Unregister(const IMsgNotification* const sink) = 0;
    
            virtual Core::hresult Publich(const string& payload, const payloadtype payloadtype) = 0;
            virtual Core::hresult Fetch(string& payload /* @out */, payloadtype& payloadtype /* @out */) = 0;

            virtual Core::hresult TopicID(string& id /* @out */) const = 0;
        };

        virtual Core::hresult Join(const string& topicId, ITopic*& topic /* @out */) = 0;
        virtual Core::hresult Leave(ITopic* const topic) = 0;

        virtual Core::hresult Connect(const uint32_t operationTimeout,	const uint32_t retryInterval, const uint32_t maximumRetryTimeout) = 0;
        virtual Core::hresult Disconnect() = 0;

        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_TOPICEXCHANGE_NOTIFICATION };

            virtual void Connected() = 0;
            virtual void Disconnected(const string& reason) = 0;
        };

        virtual Core::hresult Register(INotification* const sink) = 0;
        virtual Core::hresult Unregister(const INotification* const sink) = 0;

    };

    namespace JSONRPC {

        // @json 1.0.0 @text:legacy_lowercase
        struct EXTERNAL IMessenger {

            virtual ~IMessenger() = default;

            enum security : uint8_t {
                INSECURE /* @text insecure */,
                SECURE /* @text secure */
            };

            using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

            /* @event */
            struct EXTERNAL INotification {

                virtual ~INotification() = default;

                enum roomupdate : uint8_t {
                    CREATED /* @text created */,
                    DESTROYED /* @text destroyed */
                };

                enum userupdate : uint8_t {
                    JOINED /* @text joined */,
                    LEFT /* @text left */
                };

                // @statuslistener
                // @brief Notifies of room status changes
                // @details Immediately after registering to this notification the listener will sequentially receive updates
                //          of all rooms that have been created so far.
                // @param room: Name of the room that has changed its status (e.g. Lounge)
                // @param action: New room status
                // @param secure: Denotes if the room is secure
                virtual void RoomUpdate(const string& room, const roomupdate action, const security secure) = 0;

                // @statuslistener
                // @brief Notifies of user status changes
                // @details Immediately after registering to this notification the listener will sequentially receive updates of
                //          all users that have joined the room so far.
                // @param roomId: Token of ther room this notification relates to (e.g. 1e217990dd1cd4f66124)
                // @param: user: Name of the user that has changed its status (e.g. Bob)
                // @param action: New user status
                virtual void UserUpdate(const string& roomId /* @index */, const string& user, const userupdate action) = 0;

                // @brief Notifies of messages sent the the room
                // @param roomId: Token of the room this notification relates to (e.g. 1e217990dd1cd4f66124)
                // @param user: Name of the user that has sent the message (e.g. Bob)
                // @param message: Contents of the sent message (e.g. "Hello!")
                virtual void Message(const string& roomId /* @index */, const string& user, const string& message) = 0;
            };

            // @brief Joins a messaging room
            // @details If the specified room does not exist, then it will be created.
            // @param room: Name of the room to join (e.g. Lounge)
            // @param user: Name of ther user to join as (e.g. Bob)
            // @param roomId: Token for accessing the room (unique for a user) (e.g. 1e217990dd1cd4f66124)
            // @param secure: Denotes if the room is secure (by default not secure)
            // @param acl: List of URL origins with possible wildcards
            // @retval ERROR_ILLEGAL_STATE: User name is already taken (i.e. the user has already joined the room)
            // @retval ERROR_BAD_REQUEST: User name or room name is invalid
            // @retval ERROR_PRIVILEGED_REQUEST Room security errors
            virtual Core::hresult Join(const Core::JSONRPC::Context& context, const string& room, const string& user,
                                       const security secure /* @optional */, IStringIterator* const acl /* @optional */,
                                       string& roomId /* @out */) = 0;

            // @brief Leaves a messaging room
            // @details The room ID becomes invalid after this call.
            //          If there are no more users, the room will be destroyed and related resources freed.
            // @param roomId: Token of the room to leave (e.g. 1e217990dd1cd4f66124)
            // @retval ERROR_UNKNOWN_KEY: The room token is invalid
            virtual Core::hresult Leave(const string& roomId) = 0;

            // @brief Sends a message to a messaging room
            // @param roomId: Token of the room to send the message to (e.g. 1e217990dd1cd4f66124)
            // @param message: Contents of the message to send (e.g. "Hello!")
            // @retval ERROR_UNKNOWN_KEY: The room token is invalid
            virtual Core::hresult Send(const string& roomId, const string& message) = 0;
        };

    } // namespace JSONRPC

} // namespace Exchange

}
