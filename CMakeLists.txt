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

project(Interfaces)
find_package(WPEFramework)

project_version(1.0.0)

message(STATUS "Setting up ${PROJECT_NAME} v${PROJECT_VERSION}")

find_package(CompileSettingsDebug CONFIG REQUIRED)
find_package(${NAMESPACE}Core)
find_package(${NAMESPACE}Tracing)
find_package(${NAMESPACE}COM)

option(PROTOCOLS "Include the protocols library." ON)
option(CDMI      "Create symbolic link from IDRM.h into cdmi.h" OFF)

if (BUILD_REFERENCE)
    add_definitions (-DBUILD_REFERENCE=${BUILD_REFERENCE})
endif()

add_subdirectory(interfaces)
add_subdirectory(definitions)
