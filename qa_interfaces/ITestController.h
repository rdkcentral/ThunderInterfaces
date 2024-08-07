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
        struct EXTERNAL ITestController : virtual public Core::IUnknown {
            enum { ID = ID_TESTCONTROLLER };

            struct EXTERNAL ITest : virtual public Core::IUnknown {
                enum { ID = ID_TESTCONTROLLER_TEST };

                struct EXTERNAL IIterator : virtual public Core::IUnknown {
                    enum { ID = ID_TESTCONTROLLER_TEST_ITERATOR };

                    virtual void Reset() = 0;
                    virtual bool IsValid() const = 0;
                    virtual bool Next() = 0;

                    virtual ITest* Test() const = 0;
                };

                virtual string Execute(const string& params) = 0;

                virtual string Description() const = 0;
                virtual string Name() const = 0;
            };

            struct EXTERNAL ICategory : virtual public Core::IUnknown {
                enum { ID = ID_TESTCONTROLLER_CATEGORY };

                struct EXTERNAL IIterator : virtual public Core::IUnknown {
                    enum { ID = ID_TESTCONTROLLER_CATEGORY_ITERATOR };

                    virtual void Reset() = 0;
                    virtual bool IsValid() const = 0;
                    virtual bool Next() = 0;

                    virtual ICategory* Category() const = 0;
                };

                virtual string Name() const = 0;

                virtual void Setup() = 0;
                virtual void TearDown() = 0;

                virtual void Register(ITest* test) = 0;
                virtual void Unregister(ITest* test) = 0;
                virtual ITest::IIterator* Tests() const = 0;
                virtual ITest* Test(const string& name) const = 0;
            };

            struct TestInfo {
                string category; /* @brief Category: name of the Test, if omitted: all tests are executed */
                string test; /* @brief Test: Test name, if omitted: all tests of category are executed */
                string args; /* @brief Args: The test arguments in JSON format */
            };
            struct TestResult {
                string test; /* @brief Test Name of the test executed */
                string status; /* @brief Status after test */
            };

            using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;
            using ITestResultIterator = RPC::IIteratorType<TestResult, ID_TESTCONTROLLER_TEST_RESULT_ITERATOR>;

            // @property
            // @brief Description of the given test
            // @param test: Name of the test
            // @param description: Description of the test
            // @retval ERROR_UNAVAILABLE: Unknown test
            // @retval ERROR_BAD_REQUEST: Bad test name
            virtual uint32_t Description(const string& test /* @index */, string& description /* @out */) const = 0;
            // @property
            // @brief Categories of the test
            // @param categories - List of test categories
            virtual uint32_t Categories(IStringIterator*& categories /* @out */) const = 0;
            // @property
            // @brief List of test for selected category
            // @param category: Name of the Category
            // @retval ERROR_UNAVAILABLE: Unknown category
            // @retval ERROR_BAD_REQUEST: Bad category name
            virtual uint32_t Tests(const string& category /* @index */, IStringIterator*& tests /* @out */) const = 0;
            // @brief Run Test based on testInfo given and collect Test results
            // @param testInfo: Info about the test to be executed
            // @param testResults: Status of the tests executed
            // @retval ERROR_UNAVAILABLE: Unknown category/test
            // @retval ERROR_BAD_REQUEST: Bad testInfo
            virtual uint32_t Run(const TestInfo& testInfo /* @in */, ITestResultIterator*& testResults /* @out */) = 0;
 

            /* @json:omit */
            virtual void Setup() = 0;
            /* @json:omit */
            virtual void TearDown() = 0;
        };

    } // namespace QualityAssurance
} // namespace Thunder
