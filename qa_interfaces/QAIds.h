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

// This file holds all the identifiers (uint32_t) used to identify a QA interface. From this
// identifier, the comrpc framework can find the proper proxy/stub in case of communicating
// over a process boundary.
// Some users do not "fully" rebuild the system in case of changes. If this means that the
// Proxy/Stub code is not always rebuild in case of new releases, the identifier associated
// with an interface becomes as important as the interface syntax and as interfaces are not
// allowed to be changed, the ID associated with the interface should also not be changed
// and thus should be "fixed".

// So if you extend this file by defining a new QA interface ID make sure it is defined (has
// an actual value) and once the enum label has a value, never change it again.

// As some interfaces might be grouped, the first ID of the group is assigned a value, the
// other interfaces belonging to this group use the enum value of label that has an assigned
// value and just increment that label by the proper amount.

// Using this system, all interfaces will have an assigned number. If numbers overlap, the
// compiler, your best friend, will start complaining. Time to reassign the value, before we
// deploy.

// NOTE: Default the gap between each group of interface is 16. If you need more and the new
//       addition is add the end, write a comment with your interface that you might need more
//       than 16 interface in that group so that the next ID is indeed elevated (and rounded
//       up to a multiple of 16) if the next entry is made in the future.

// @insert <com/Ids.h>

namespace WPEFramework {

namespace QualityAssurance {

    enum IDS : uint32_t {

        ID_TESTAUTOMATIONMEMORY                      = RPC::IDS::ID_EXTERNAL_QA_INTERFACE_OFFSET,
        ID_TESTAUTOMATIONCOMRPC                      = ID_TESTAUTOMATIONMEMORY + 1,
        ID_TESTAUTOMATIONCOMRPCINTERNAL              = ID_TESTAUTOMATIONMEMORY + 2,

        ID_TESTCONTROLLER                            = RPC::IDS::ID_EXTERNAL_QA_INTERFACE_OFFSET + 0x010,
        ID_TESTCONTROLLER_TEST                       = ID_TESTCONTROLLER + 1,
        ID_TESTCONTROLLER_TEST_ITERATOR              = ID_TESTCONTROLLER + 2,
        ID_TESTCONTROLLER_CATEGORY                   = ID_TESTCONTROLLER + 3,
        ID_TESTCONTROLLER_CATEGORY_ITERATOR          = ID_TESTCONTROLLER + 4,

        ID_TESTUTILITY                               = RPC::IDS::ID_EXTERNAL_QA_INTERFACE_OFFSET + 0x020,
        ID_TESTUTILITY_COMMAND                       = ID_TESTUTILITY + 1,
        ID_TESTUTILITY_ITERATOR                      = ID_TESTUTILITY + 2,

    };
}
}
