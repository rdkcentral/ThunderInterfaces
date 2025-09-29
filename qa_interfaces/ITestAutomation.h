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
namespace QualityAssurance {

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IMemory : virtual public Core::IUnknown {
        enum { ID = ID_TESTAUTOMATIONMEMORY };

        ~IMemory() override = default;
       
        // @brief Allocates Memory as given size of MB
        // @retval ERROR_GENERAL Failed to allocate memory
        virtual Core::hresult AllocateMemory(const uint32_t size) = 0;


        // @brief Frees the allocated memory
        // @retval ERROR_GENERAL Failed to free allocated memory
        virtual Core::hresult FreeAllocatedMemory() = 0;

    };


    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL IComRpc : virtual public Core::IUnknown {
        enum { ID = ID_TESTAUTOMATIONCOMRPC };

        ~IComRpc() override = default;

        // @brief Validates big string over proxy-stub with given length of KB
        // @retval ERROR_GENERAL Failed to verify
        virtual Core::hresult TestBigString(const uint32_t length) = 0;

        struct EXTERNAL IComRpcInternal : virtual public Core::IUnknown {
            enum { ID = ID_TESTAUTOMATIONCOMRPCINTERNAL };

            ~IComRpcInternal() override = default;

            virtual Core::hresult BigStringTest(const string& testString /* @restrict: (4M-1) */) = 0;
        };
    };

    // @json 1.0.0
    // @brief Validates jsonrpc document generation based on given parameters
    struct EXTERNAL ITestTextOptions : virtual public Core::IUnknown {
        enum { ID = ID_TESTTEXTOPTIONS };

        enum EnumTextOptions : uint8_t {
            FIRST_OPTION = 0,
            SECOND_OPTION = 1,
            ThirdOption = 2
        };

        struct EXTERNAL TestDetails
            {
                string testDetailsFirst;
                string testDetailsSecond;
            };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_TESTTEXTOPTIONS_NOTIFICATION };
            ~INotification() override = default;

            virtual void TestEvent(const uint32_t firstTestParam, const uint32_t secondTestParam, const TestDetails& thirdTestParam, const EnumTextOptions fourthTestParam) = 0;
        };


        ~ITestTextOptions() override = default;

        // @brief Validates standard which is camelCase
        // @retval ERROR_GENERAL Failed to verify
        virtual Core::hresult TestStandard(const uint32_t firstTestParam, const uint32_t secondTestParam, const TestDetails& thirdTestParam, const EnumTextOptions fourthTestParam) = 0;


        // @json 1.0.0 @text:legacy_lowercase
        struct EXTERNAL ITestLegacy : virtual public Core::IUnknown {
            enum { ID = ID_TESTLEGACY };

            enum EnumTextOptions : uint8_t {
                FIRST_OPTION = 0,
                SECOND_OPTION = 1,
                ThirdOption = 2
            };

            struct EXTERNAL TestDetails
            {
                string testDetailsFirst;
                string testDetailsSecond;
            };

            // @event
            struct EXTERNAL INotification : virtual public Core::IUnknown {
                enum { ID = ID_TESTLEGACY_NOTIFICATION };
                ~INotification() override = default;

                virtual void TestEvent(const uint32_t firstTestParam, const uint32_t secondTestParam, const TestDetails& thirdTestParam, const EnumTextOptions fourthTestParam) = 0;
            };

            ~ITestLegacy() override = default;
            // @brief Validates legacy which is lowercase
            // @retval ERROR_GENERAL Failed to verify
            virtual Core::hresult TestLegacy(const uint32_t firstTestParam, const uint32_t secondTestParam, const TestDetails& thirdTestParam, const EnumTextOptions fourthTestParam) = 0;
        };

        // @json 1.0.0 @text:keep
        struct EXTERNAL ITestKeep : virtual public Core::IUnknown {
            enum { ID = ID_TESTKEEP };

            enum EnumTextOptions : uint8_t {
                FIRST_OPTION = 0,
                SECOND_OPTION = 1,
                ThirdOption = 2
            };

            struct EXTERNAL TestDetails
            {
                string testDetailsFirst;
                string testDetailsSecond;
            };

            // @event
            struct EXTERNAL INotification : virtual public Core::IUnknown {
                enum { ID = ID_TESTKEEP_NOTIFICATION };
                ~INotification() override = default;

                virtual void TestEvent(const uint32_t firstTestParam, const uint32_t secondTestParam, const TestDetails& thirdTestParam, const EnumTextOptions fourthTestParam) = 0;
            };

            ~ITestKeep() override = default;
            // @brief Validates keep which is as same as it's coded
            // @retval ERROR_GENERAL Failed to verify
            virtual Core::hresult TestKeeP(const uint32_t firstTestParaM, const uint32_t secondTestParaM, const TestDetails& thirdTestParaM, const EnumTextOptions fourthTestParaM) = 0;
        };

        // @json 1.0.0 @text:custom=lower,upper,lowersnake,uppersnake,pascal,lower
        struct EXTERNAL ITestCustom : virtual public Core::IUnknown {
            enum { ID = ID_TESTCUSTOM };

            enum EnumTextOptions : uint8_t {
                FIRST_OPTION = 0,
                SECOND_OPTION = 1,
                ThirdOption = 2
            };

            struct EXTERNAL TestDetails
            {
                string testDetailsFirst;
                string testDetailsSecond;
            };

            // @event
            struct EXTERNAL INotification : virtual public Core::IUnknown {
                enum { ID = ID_TESTCUSTOM_NOTIFICATION };
                ~INotification() override = default;

                virtual void TestEvent(const uint32_t firstTestParam, const uint32_t secondTestParam, const TestDetails& thirdTestParam, const EnumTextOptions fourthTestParam) = 0;
            };

            ~ITestCustom() override = default;
            // @brief Validates custom generation
            // @retval ERROR_GENERAL Failed to verify
            virtual Core::hresult TestCustom(const uint32_t firstTestParam, const uint32_t secondTestParam, const TestDetails& thirdTestParam, const EnumTextOptions fourthTestParam) = 0;
        };
    };

    // @json 1.0.0 @text:legacy_lowercase
    struct EXTERNAL ITestUtils : virtual public Core::IUnknown {
        enum { ID = ID_TESTAUTOMATIONUTILS };

        ~ITestUtils() override = default;

        // @brief Causes a crash
        virtual Core::hresult Crash() const = 0;
    };

}
}
