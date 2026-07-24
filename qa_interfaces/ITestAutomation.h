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

        // =================================================================
        // Per-field @text on struct members (partial overrides)
        // =================================================================

        struct EXTERNAL MixedFieldNames {
            string DeviceName      /* @text:device_id */;
            uint32_t FirmwareVer   /* @text:fw_version */;
            bool IsOnline;  // No override - follows standard camelCase convention (isOnline in JSON)
        };

        // @brief Echo a struct with partial field name overrides.
        // @param input Input struct.
        // @param output Receives echoed struct.
        virtual Core::hresult EchoMixedFields(const MixedFieldNames& input /* @in */, MixedFieldNames& output /* @out */) const = 0;

        // =================================================================
        // Per-enumerator @text on enum values
        // =================================================================

        enum ConnectionStatus : uint8_t {
            STATUS_IDLE = 0,
            STATUS_CONNECTING = 1  /* @text:connecting */,
            STATUS_ACTIVE = 2,
            STATUS_AUTH_FAILED = 3 /* @text:auth-error */
        };

        // @brief Set connection status.
        // @param status Status value.
        virtual Core::hresult SetStatus(const ConnectionStatus status /* @in */) = 0;

        // @brief Get connection status.
        // @param status Receives current status.
        virtual Core::hresult GetStatus(ConnectionStatus& status /* @out */) const = 0;

        // =================================================================
        // Per-method @text override
        // C++ name: InternalMethodName → JSON-RPC name: "renamedMethod"
        // =================================================================

        // @brief Method with overridden JSON-RPC dispatch name.
        // @text renamedMethod
        // @param value Input value.
        // @param result Receives echoed value.
        virtual Core::hresult InternalMethodName(const uint32_t value /* @in */, uint32_t& result /* @out */) const = 0;

        // =================================================================
        // @text combined with @alt
        // Primary: "primaryApi", Alternative: "legacyApi"
        // C++ name "TextAndAltMethod" is NOT callable via JSON-RPC.
        // =================================================================

        // @brief Method with both text rename and alt alternative.
        // @text primaryApi
        // @alt legacyApi
        // @param value Input value.
        // @param result Receives echoed value.
        virtual Core::hresult TextAndAltMethod(const uint32_t value /* @in */, uint32_t& result /* @out */) const = 0;

        // =================================================================
        // Event trigger (for verifying event naming under convention)
        // =================================================================

        // @brief Register for notifications.
        virtual Core::hresult Register(INotification* notification) = 0;

        // @brief Unregister from notifications.
        virtual Core::hresult Unregister(INotification* notification) = 0;

        // @brief Trigger the test event for event name verification.
        // @param firstTestParam First param.
        // @param secondTestParam Second param.
        // @param thirdTestParam Struct param.
        // @param fourthTestParam Enum param.
        virtual Core::hresult TriggerEvent(const uint32_t firstTestParam /* @in */, const uint32_t secondTestParam /* @in */,
            const TestDetails& thirdTestParam /* @in */, const EnumTextOptions fourthTestParam /* @in */) = 0;


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
