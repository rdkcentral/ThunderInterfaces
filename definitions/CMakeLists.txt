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

project(Definitions)

find_package(WPEFramework)

project_version(1.0.0)

find_package(CompileSettingsDebug REQUIRED)
find_package(JsonGenerator REQUIRED)
find_package(${NAMESPACE}Core REQUIRED)

set(Target ${NAMESPACE}${PROJECT_NAME})

separate_arguments(JSONRPC_PATTERNS)
set(WORKING_VARIABLE ${JSONRPC_PATTERNS})
list(TRANSFORM WORKING_VARIABLE PREPEND "${CMAKE_SOURCE_DIR}/jsonrpc/")
file(GLOB JSON_FILE ${WORKING_VARIABLE})

separate_arguments(JSONRPC_PATTERNS)
set(WORKING_VARIABLE ${JSONRPC_PATTERNS})
list(TRANSFORM WORKING_VARIABLE PREPEND "${CMAKE_SOURCE_DIR}/qa_jsonrpc/")
file(GLOB QA_JSON_FILE ${WORKING_VARIABLE})

separate_arguments(INTERFACES_PATTERNS)
set(WORKING_VARIABLE ${INTERFACES_PATTERNS})
list(TRANSFORM WORKING_VARIABLE PREPEND "${CMAKE_SOURCE_DIR}/interfaces/")
file(GLOB INTERFACE_FILE ${WORKING_VARIABLE})

separate_arguments(INTERFACES_PATTERNS)
set(WORKING_VARIABLE ${INTERFACES_PATTERNS})
list(TRANSFORM WORKING_VARIABLE PREPEND "${CMAKE_SOURCE_DIR}/qa_interfaces/")
file(GLOB QA_INTERFACE_FILE ${WORKING_VARIABLE})

set(PUBLIC_HEADERS "definitions.h" "ValuePoint.h" "Module.h")

if(NOT GENERATOR_SEARCH_PATH)
    set(GENERATOR_SEARCH_PATH ${CMAKE_SYSROOT}${CMAKE_INSTALL_PREFIX}/include/${NAMESPACE})
endif()

JsonGenerator(CODE INPUT ${JSON_FILE} OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated" INCLUDE_PATH ${GENERATOR_SEARCH_PATH} CPPIFDIR "${CMAKE_CURRENT_SOURCE_DIR}/../interfaces/")
JsonGenerator(CODE INPUT ${QA_JSON_FILE} OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/qa_generated" INCLUDE_PATH ${GENERATOR_SEARCH_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../jsonrpc/" CPPIFDIR "${CMAKE_CURRENT_SOURCE_DIR}/../qa_interfaces/" IFDIR "${CMAKE_CURRENT_SOURCE_DIR}/../jsonrpc/" CPP_INTERFACE_PATH "qa_interfaces" JSON_INTERFACE_PATH "qa_interfaces/json")
JsonGenerator(CODE INPUT ${INTERFACE_FILE} OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated" INCLUDE_PATH ${GENERATOR_SEARCH_PATH})
JsonGenerator(CODE NAMESPACE  WPEFramework::QualityAssurance INPUT ${QA_INTERFACE_FILE} OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/qa_generated" INCLUDE_PATH ${GENERATOR_SEARCH_PATH} CPP_INTERFACE_PATH "qa_interfaces" JSON_INTERFACE_PATH "qa_interfaces/json" )

file(GLOB JSON_ENUM_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/generated/JsonEnum*.cpp")
file(GLOB JSON_LINK_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/generated/J*.h")

file(GLOB QA_JSON_ENUM_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/qa_generated/JsonEnum*.cpp")
file(GLOB QA_JSON_LINK_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/qa_generated/J*.h")

list(APPEND JSON_LINK_HEADERS "Module.h")
list(APPEND QA_JSON_LINK_HEADERS "Module.h")

include(CreateLink)
#CreateLink(LINK "${CMAKE_CURRENT_BINARY_DIR}/generated/Module.h" TARGET "../Module.h")
#list(APPEND JSON_LINK_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/generated/Module.h")
#CreateLink(LINK "${CMAKE_CURRENT_BINARY_DIR}/generated/Ids.h" TARGET "../Ids.h")
#list(APPEND JSON_LINK_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/generated/Ids.h")
#CreateLink(LINK "${CMAKE_CURRENT_BINARY_DIR}/Module.h" TARGET "../interfaces/Module.h")
#list(APPEND PUBLIC_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/Module.h")
#CreateLink(LINK "${CMAKE_CURRENT_BINARY_DIR}/qa_generated/QAIds.h" TARGET "../QAIds.h")
#list(APPEND JSON_LINK_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/qa_generated/QAIds.h")

add_library(${Target} SHARED
        Definitions.cpp
        Module.cpp
        ${JSON_ENUM_SOURCES}
        ${QA_JSON_ENUM_SOURCES}
        )

target_link_libraries(${Target}
        PRIVATE
          ${NAMESPACE}Core::${NAMESPACE}Core
          CompileSettingsDebug::CompileSettingsDebug
        )

set_target_properties(${Target} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        FRAMEWORK FALSE
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        PUBLIC_HEADER "${PUBLIC_HEADERS}" # specify the public headers
        )

target_include_directories(${Target}
        PRIVATE
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
          $<INSTALL_INTERFACE:include/${NAMESPACE}>
       )

install(
        TARGETS ${Target} EXPORT ${Target}Targets  # for downstream dependencies
        ARCHIVE DESTINATION lib/ COMPONENT libs      # static lib
        LIBRARY DESTINATION lib/ COMPONENT libs      # shared lib
        RUNTIME DESTINATION bin COMPONENT libs      # binaries
        FRAMEWORK DESTINATION bin/ COMPONENT libs    # for mac
        PUBLIC_HEADER DESTINATION include/${NAMESPACE}/definitions COMPONENT devel   # headers for mac (note the different component -> different package)
        INCLUDES DESTINATION include/${NAMESPACE}   # default include path
)

install(
        FILES ${JSON_LINK_HEADERS}
        DESTINATION include/${NAMESPACE}/interfaces/json
)

install(
        FILES ${QA_JSON_LINK_HEADERS}
        DESTINATION include/${NAMESPACE}/qa_interfaces/json
)

InstallPackageConfig(
        TARGETS ${Target}
        DESCRIPTION "Share lookup tables associated with interface enums."
        )


InstallCMakeConfig(TARGETS ${Target})

