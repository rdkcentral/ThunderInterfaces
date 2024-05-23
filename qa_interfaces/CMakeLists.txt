# If not stated otherwise in this file or this component's license file the
# following copyright and licenses apply:
#
# Copyright 2020 Metrological
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.3)

project(QAMarshalling)

find_package(WPEFramework)

project_version(1.0.0)

find_package(CompileSettingsDebug REQUIRED)
find_package(ProxyStubGenerator REQUIRED)
find_package(${NAMESPACE}Core REQUIRED)
find_package(${NAMESPACE}COM REQUIRED)

set(Target ${NAMESPACE}${PROJECT_NAME})

if(NOT GENERATOR_SEARCH_PATH)
    set(GENERATOR_SEARCH_PATH ${CMAKE_SYSROOT}${CMAKE_INSTALL_PREFIX}/include/${NAMESPACE})
endif()

separate_arguments(INTERFACES_PATTERNS)
file(GLOB QA_INTERFACES_HEADERS ${INTERFACES_PATTERNS})

ProxyStubGenerator(NAMESPACE "WPEFramework::QualityAssurance" INPUT "${QA_INTERFACES_HEADERS}" OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/qa_generated" INCLUDE_PATH ${GENERATOR_SEARCH_PATH})

list(APPEND QA_INTERFACES_HEADERS Module.h QAIds.h)

file(GLOB QA_PROXY_STUB_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/qa_generated/ProxyStubs*.cpp")
add_library(${Target} SHARED
        Module.cpp
        ${QA_PROXY_STUB_SOURCES}
        )

target_include_directories(${Target} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/..)

target_link_libraries(${Target}
        PRIVATE
          ${NAMESPACE}Core::${NAMESPACE}Core
          ${NAMESPACE}COM::${NAMESPACE}COM
          CompileSettingsDebug::CompileSettingsDebug
        )

set_target_properties(${Target} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        FRAMEWORK FALSE
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        )

string(TOLOWER ${NAMESPACE} NAMESPACE_LIB)

install(
        TARGETS ${Target} EXPORT ${Target}Targets  # for downstream dependencies
        LIBRARY DESTINATION lib/${NAMESPACE_LIB}/proxystubs COMPONENT libs      # shared lib
)

install(
        FILES ${QA_INTERFACES_HEADERS}
        DESTINATION include/${NAMESPACE}/qa_interfaces
)








