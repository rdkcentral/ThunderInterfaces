# If not stated otherwise in this file or this component's license file the
# following copyright and licenses apply:
#
# Copyright 2020 RDK Management
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

project(Interfaces)

set(TargetMarshalling ${NAMESPACE}Marshallings)

set(GENERATOR_SEARCH_PATH ${CMAKE_SYSROOT}${CMAKE_INSTALL_PREFIX}/include/${NAMESPACE})
ProxyStubGenerator(INPUT "${CMAKE_CURRENT_SOURCE_DIR}" OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/generated/proxystubs" INCLUDE_PATH ${GENERATOR_SEARCH_PATH})

file(GLOB INTERFACES_HEADERS I*.h)
list(APPEND INTERFACES_HEADERS Module.h)

file(GLOB PROXY_STUB_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/generated/proxystubs/ProxyStubs*.cpp")
add_library(${TargetMarshalling} SHARED 
        Module.cpp
        ${PROXY_STUB_SOURCES}
        )

target_include_directories(${TargetMarshalling} PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(${TargetMarshalling}
        PRIVATE
          ${NAMESPACE}Core::${NAMESPACE}Core
          ${NAMESPACE}Tracing::${NAMESPACE}Tracing
          CompileSettingsDebug::CompileSettingsDebug
        )

target_compile_definitions(${TargetMarshalling}
        PUBLIC
            PROXYSTUB_BUILDING=1)

if (PROTOCOLS)
    target_link_libraries(${TargetMarshalling}
            PRIVATE
              ${NAMESPACE}Protocols::${NAMESPACE}Protocols
            )
else()
    target_link_libraries(${TargetMarshalling}
            PRIVATE
              ${NAMESPACE}COM::${NAMESPACE}COM
            )
endif ()

set_target_properties(${TargetMarshalling} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        FRAMEWORK FALSE
        VERSION ${VERSION}
        SOVERSION ${VERSION_MAJOR}
        )

string(TOLOWER ${NAMESPACE} NAMESPACE_LIB)

install(
        TARGETS ${TargetMarshalling} EXPORT ${TargetMarshalling}Targets  # for downstream dependencies
        LIBRARY DESTINATION lib/${NAMESPACE_LIB}/proxystubs COMPONENT libs      # shared lib
)

install(
        FILES ${INTERFACES_HEADERS}
        DESTINATION include/${NAMESPACE}/interfaces
)
