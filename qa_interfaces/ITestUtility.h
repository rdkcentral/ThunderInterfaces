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

// @stubgen:include <com/IIteratorType.h>

namespace Thunder {
namespace QualityAssurance {

    /* @json 1.0.0 */
    struct EXTERNAL ITestUtility : virtual public Core::IUnknown {
        enum { ID = ID_TESTUTILITY };

        ~ITestUtility() override = default;

        struct EXTERNAL ICommand : virtual public Core::IUnknown {

            enum { ID = ID_TESTUTILITY_COMMAND };

            ~ICommand() override = default;

            struct EXTERNAL IIterator : virtual public Core::IUnknown {

                enum { ID = ID_TESTUTILITY_ITERATOR };

                ~IIterator() override = default;

                virtual void Reset() = 0;
                virtual bool IsValid() const = 0;
                virtual bool Next() = 0;

                virtual ICommand* Command() const = 0;
            };

            virtual string Execute(const string& params) = 0;

            virtual string Description() const = 0;
            virtual string Signature() const = 0;
            virtual string Name() const = 0;
        };

        struct ParameterInfo {
            enum Type : uint8_t {
                NUMBER,
                STRING,
                BOOLEAN,
                OBJECT,
                SYMBOL
            };
            string name;    /* @brief Name of command */
            Type type;      /* @brief Type of command */
            string comment; /* @brief Comment about command */
        };

        using IParameterInfoIterator = RPC::IIteratorType<ParameterInfo, ID_TESTUTILITY_COMMAND_PARAMETER_INFO_ITERATOR>;
        struct CrashInfo {
            string command; /* @brief Command name */
            uint8_t delay;  /* @brief Delay (in seconds) before the crash attempt (applicable for *Crash* command) */
            uint8_t count;  /* @brief How many times a Crash command will be executed consecutively (applicable for *CrashNTimes* command)*/
        };

        struct MemoryInfo {
            string command; /* @brief Command name */
            uint32_t size;  /* @brief Size: The amount of memory in KB for allocation (applicable for *Malloc* commands) */
        };

        struct MemoryResult {
            uint32_t allocated;/* @brief Allocated: already allocated memory in KB */
            uint32_t size;     /* @brief Size: Current allocation in KB */
            uint32_t resident; /* @brief Resident: memory in KB */
        };

        using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

        // @property
        // @brief Description - Retrieves the description of selected test command
        // @param command: Name of the command
        // @param description: Description of the command
        // @retval ERROR_UNAVAILABLE: Unknown command
        // @retval ERROR_BAD_REQUEST: Bad command name
        virtual uint32_t Description(const string& command /* @index */, string& description /* @out */) const = 0;

        // @property
        // @brief Commands - Retrieves the list of test commands
        // @param commands: Names of the commands
        virtual uint32_t Commands(IStringIterator*& commands /* @out */) const = 0;
 
        // @property
        // @brief ShutdownTimeout: Timeout to be waited before deactivating the plugin
        // @param timeout: Timeout to be waited
        virtual uint32_t ShutdownTimeout(const uint32_t timeout /* @in */) = 0;

        // @brief Parameters - Retrieves parameters of the selected test command
        // @param command: Name of the command
        // @param response: Parameter Data
        // @retval ERROR_UNAVAILABLE: Unknown command
        // @retval ERROR_BAD_REQUEST: Bad param data format
        virtual uint32_t Parameters(const string& command /* @input */, IParameterInfoIterator*& input /* @out */, ParameterInfo& output /* @out */) const = 0;

        // @brief RunCrash - Runs a crash test command
        // @param info: Info about crash test to be run
        // @retval ERROR_UNAVAILABLE: Unknown command
        // @retval ERROR_BAD_REQUEST: Bad param data format
        virtual uint32_t RunCrash(const CrashInfo& info /* @in */) = 0;

        // @brief RunMemory - Runs a memory test command
        // @param info: Memory info for the test
        // @param result: Memory result after test
        // @retval ERROR_UNAVAILABLE: Unknown category
        // @retval ERROR_BAD_REQUEST: Bad param data format
        virtual uint32_t RunMemory(const MemoryInfo& info /* @in */, MemoryResult& result /* @out */) = 0;


        // @brief Execute - Execute test command
        // @param command: Name of the command
        // @param params: Parameters details
        // @param status: Test status
        // @retval ERROR_UNAVAILABLE: Unknown command
        // @retval ERROR_BAD_REQUEST: Bad param data format
        virtual uint32_t Execute(const string& command /* @in */, const string& params /* @in */, string& status /* @out */) = 0;
    };

} // namespace QualityAssurance
} // namespace Thunder
