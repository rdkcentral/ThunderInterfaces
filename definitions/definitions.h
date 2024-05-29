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

#include <messaging/messaging.h>
#include <com/com.h>

#if defined(__WINDOWS__) 
#if defined(DEFINITIONS_EXPORTS)
#undef EXTERNAL
#define EXTERNAL EXTERNAL_EXPORT
#else
#pragma comment(lib, "definitions.lib")
#endif
#endif

#include <interfaces/IComposition.h>
#include <interfaces/IExternal.h>
#include <interfaces/IValuePoint.h>
#include <interfaces/IStream.h>
#include <interfaces/IVoiceHandler.h>
#include <interfaces/IPower.h>
#include <interfaces/json/ExternalMetadata.h>
#include <interfaces/IDeviceInfo.h>

namespace WPEFramework {

	ENUM_CONVERSION_HANDLER(Exchange::IComposition::ScreenResolution)
	ENUM_CONVERSION_HANDLER(Exchange::IStream::streamtype)
	ENUM_CONVERSION_HANDLER(Exchange::IStream::state)
	ENUM_CONVERSION_HANDLER(Exchange::IValuePoint::basic)
	ENUM_CONVERSION_HANDLER(Exchange::IValuePoint::specific)
	ENUM_CONVERSION_HANDLER(Exchange::IValuePoint::dimension)
}
