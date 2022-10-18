/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2022 Metrological
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

#ifdef __GNUC__
#ifndef DEPRECATED
#define DEPRECATED __attribute__((deprecated))
#endif
#ifndef VARIABLE_IS_NOT_USED
#define VARIABLE_IS_NOT_USED __attribute__((unused))
#endif
#ifndef WARNING_RESULT_NOT_USED
#define WARNING_RESULT_NOT_USED __attribute__((warn_unused_result))
#endif
#else
#ifndef DEPRECATED
#define DEPRECATED
#endif
#ifndef VARIABLE_IS_NOT_USED
#define VARIABLE_IS_NOT_USED
#endif
#ifndef WARNING_RESULT_NOT_USED
#define WARNING_RESULT_NOT_USED
#endif
#endif

#if !defined(PUSH_WARNING) && !defined(POP_WARNING)
#ifdef __WINDOWS__
    #define DO_PRAGMA(x) __pragma(x)

    #define PUSH_WARNING_ DO_PRAGMA(warning(push))
    #define PUSH_WARNING_ARG_(WARNING) DO_PRAGMA(warning(disable: WARNING))
    #define POP_WARNING_ DO_PRAGMA(warning(pop))

#else
    #define DO_PRAGMA(x) _Pragma(#x)

    #if defined(__clang__)
        #define PUSH_WARNING_ _Pragma("clang diagnostic push")
        #define PUSH_WARNING_ARG_(WARNING) DO_PRAGMA(clang diagnostic ignored #WARNING)
        #define POP_WARNING_ _Pragma("clang diagnostic pop")

    #elif (__GNUC__ >= 4)
        #define PUSH_WARNING_ _Pragma("GCC diagnostic push")
        #define PUSH_WARNING_ARG_(WARNING) DO_PRAGMA(GCC diagnostic ignored WARNING)
        #define POP_WARNING_ _Pragma("GCC diagnostic pop")

    #else
        #define PUSH_WARNING_(WARNING)
        #define PUSH_WARNING_ARG_
        #define POP_WARNING_
    #endif
#endif

#define DEFINE_STRING_1(parameter) #parameter
#define DEFINE_STRING(parameter) DEFINE_STRING_1(parameter)
#define CONCAT_STRINGS_1(ARG1, ARG2)  ARG1##ARG2
#define CONCAT_STRINGS(ARG1, ARG2)  CONCAT_STRINGS_1(ARG1,ARG2)
#define PUSH_WARNING_ROLL_1(WARNING, ...) WARNING
#define PUSH_WARNING_ROLL_2(WARNING, ...) WARNING PUSH_WARNING_ROLL_1(__VA_ARGS__)
#define PUSH_WARNING_ROLL_3(WARNING, ...) WARNING PUSH_WARNING_ROLL_2(__VA_ARGS__)
#define PUSH_WARNING_ROLL_4(WARNING, ...) WARNING PUSH_WARNING_ROLL_3(__VA_ARGS__)
#define PUSH_WARNING_ROLL_5(WARNING, ...) WARNING PUSH_WARNING_ROLL_4(__VA_ARGS__)

// Seems to be a MSVC issue, see: https://stackoverflow.com/questions/9183993/msvc-variadic-macro-expansion
#define PUSH_RETURN_ARG_COUNT(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, count, ...) count
#define PUSH_EXPAND_ARGS(args) PUSH_RETURN_ARG_COUNT args
#define PUSH_COUNT_ARGS(...) PUSH_EXPAND_ARGS((__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define PUSH_WARNING_ARG(N, ...) CONCAT_STRINGS(PUSH_WARNING_ROLL_, N)(__VA_ARGS__)
#define PUSH_WARNING(...) \
    PUSH_WARNING_ PUSH_WARNING_ARG(PUSH_COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)

#define POP_WARNING() POP_WARNING_

#ifdef __WINDOWS__
// W4 -- Make sure the "conditional expression is constant"
#define DISABLE_WARNING_CONDITIONAL_EXPRESSION_IS_CONSTANT PUSH_WARNING_ARG_(4127)
// W4 -- Nonstandard extension used : zero-sized array in struct/union
#define DISABLE_WARNING_NON_STANDARD_EXTENSION_USED PUSH_WARNING_ARG_(4200)
// W3 -- Make sure the "clas 'xxxx' needs to have dll-interface to be used by clients of class 'xxxx'"
#define DISABLE_WARNING_DLL_INTERFACE_UNAVAILABLE PUSH_WARNING_ARG_(4251)
// W3 -- C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
#define DISABLE_WARNING_EXCEPTION_SPECIFICATION PUSH_WARNING_ARG_(4290)
// W3 -- No matching operator delete found; memory will not be freed if initialization throws an exception
#define DISABLE_WARNING_NO_MATCHING_OPERATOR_DELETE PUSH_WARNING_ARG_(4291)
// W2 -- Conversion : truncation from 'type 1' to 'type 2'
#define DISABLE_WARNING_CONVERSION_TRUNCATION PUSH_WARNING_ARG_(4302)
// W1 -- Variable : pointer truncation from 'type' to 'type'
#define DISABLE_WARNING_POINTER_TRUNCATION PUSH_WARNING_ARG_(4311)
// W1 -- Operation : conversion from 'type1' to 'type2' of greater size
#define DISABLE_WARNING_CONVERSION_TO_GREATERSIZE PUSH_WARNING_ARG_(4312)
// W1 & 4 -- The 'this' pointer : used in base member initializer list
#define DISABLE_WARNING_THIS_IN_MEMBER_INITIALIZER_LIST PUSH_WARNING_ARG_(4355)
// W3 -- Make sure the "C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc"
#define DISABLE_WARNING_UNWIND_SEMANTICS_NOT_ENABLED PUSH_WARNING_ARG_(4530)
// W1 -- 'class1' : base-class 'class2' is already a base-class of 'class3'.
#define DISABLE_WARNING_MULTPILE_INHERITENCE_OF_BASE_CLASS PUSH_WARNING_ARG_(4584)
// W1 -- Discarding return value of function with 'nodiscard' attribute
#define DISABLE_WARNING_DISCARD_RETURN_VALUE_FOR_NONDISCARD_FUNCTION PUSH_WARNING_ARG_(4834)
// W3 -- Code uses a function, class member, variable, or typedef that's marked deprecated
#define DISABLE_WARNING_DEPRECATED_USE PUSH_WARNING_ARG_(4996)
#define DISABLE_WARNING_MISSING_FIELD_INITIALIZERS
#define DISABLE_WARNING_UNUSED_VARIABLES
#define DISABLE_WARNING_DEPRECATED_COPY
#define DISABLE_WARNING_NON_VIRTUAL_DESTRUCTOR

#else
#define DISABLE_WARNING_CONDITIONAL_EXPRESSION_IS_CONSTANT
#define DISABLE_WARNING_NON_STANDARD_EXTENSION_USED
#define DISABLE_WARNING_DLL_INTERFACE_UNAVAILABLE
#define DISABLE_WARNING_EXCEPTION_SPECIFICATION
#define DISABLE_WARNING_NO_MATCHING_OPERATOR_DELETE
#define DISABLE_WARNING_CONVERSION_TRUNCATION
#define DISABLE_WARNING_POINTER_TRUNCATION
#define DISABLE_WARNING_CONVERSION_TO_GREATERSIZE
#define DISABLE_WARNING_THIS_IN_MEMBER_INITIALIZER_LIST
#define DISABLE_WARNING_MULTPILE_INHERITENCE_OF_BASE_CLASS
#define DISABLE_WARNING_DISCARD_RETURN_VALUE_FOR_NONDISCARD_FUNCTION

#if defined(__clang__) || (__GNUC__ >= 4)
#define DISABLE_WARNING_MISSING_FIELD_INITIALIZERS PUSH_WARNING_ARG_("-Wmissing-field-initializers")
#define DISABLE_WARNING_UNUSED_VARIABLES PUSH_WARNING_ARG_("-Wunused-variable")
#define DISABLE_WARNING_DEPRECATED_USE PUSH_WARNING_ARG_("-Wdeprecated-declarations")
#define DISABLE_WARNING_DEPRECATED_COPY PUSH_WARNING_ARG_("-Wdeprecated-copy")
#define DISABLE_WARNING_NON_VIRTUAL_DESTRUCTOR PUSH_WARNING_ARG_("-Wnon-virtual-dtor")
#endif
#endif
#endif
