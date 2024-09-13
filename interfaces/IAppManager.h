/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
namespace WPEFramework {
namespace Exchange {
  // @json @text:keep
struct EXTERNAL IAppManager : virtual public Core::IUnknown {
  enum { ID = ID_APP_MANAGER };

  // @event
  struct EXTERNAL INotification : virtual public Core::IUnknown {
    enum { ID = ID_APP_MANAGER_NOTIFICATION };

    // @text onAppInstalled
    // @brief Triggered when a new launchable app is installed for the first time or a different version is installed
    // @param appId: id of the application
    // @param version: The version string of the app. This is a free form non-empty string
    virtual void OnAppInstalled(const string& appId, const string& version) = 0;

    // @text onAppUninstalled
    // @brief Triggered when a launchable app has been uninstalled. Apps may be uninstalled while running, uninstalling an app doesn't force it to close.
    // @param appId: id of the application
    virtual void OnAppUninstalled(const string& appId) = 0;

    // @text onAppStateChanged
    // @brief Triggered whenever there is a change in the lifecycle state of a running app.
    // @param appId: id of the application
    // @param version: The lifecycle state of a running app
    virtual void OnAppStateChanged(const string& appId, const string& state) = 0;

    // @text onAppLaunchRequest
    // @brief This event is a stop-gap and expected to be deprecated in the future. Triggered when an app launch request is received from an external component. For example DIAL launch request, or app to app launch requested from a running Firebolt app.
    // @param appId: id of the application
    // @param intent: intent object (JSON format)
    // @param appId: 	The source of the launch request
    virtual void OnAppLaunchRequest(const string& appId, const string& intent, const string& source) = 0;
  };

  using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

  virtual uint32_t Register(Exchange::IAppManager::INotification* notification /* @in */) = 0;
  virtual uint32_t Unregister(Exchange::IAppManager::INotification* notification /* @in */) = 0;

  // @text getLaunchableApps
  virtual uint32_t GetLaunchableApps(IStringIterator*& result /* @out */) = 0;

  // @text getLoadedApps
  virtual uint32_t GetLoadedApps(IStringIterator*& result /* @out */) = 0;

  // @text launchApp
  virtual uint32_t LaunchApp(const string& appId /* @in */, const string& intent /* @in */, const string& launchArgs/* @in */) = 0;

  // @text loadApp
  virtual uint32_t LoadApp(const string& appId /* @in */, const string& intent /* @in */, const string& launchArgs/* @in */) = 0;

  // @text prepareApp
  virtual uint32_t PrepareApp(const string& appId /* @in */) = 0;

  // @text sendMessage
  virtual uint32_t SendMessage(const string& appId /* @in */, const string& messagae /* @in */) = 0;

  // @text closeApp
  virtual uint32_t CloseApp(const string& appId /* @in */) = 0;

  // @text terminateApp
  virtual uint32_t TerminateApp(const string& appId /* @in */) = 0;

  // @text clearAppData
  virtual uint32_t ClearAppData(const string& appId /* @in */) = 0;

  // @text setAppFocus
  virtual uint32_t SetAppFocus(const string& appId /* @in */) = 0;

  // @text getAppMetaData
  virtual uint32_t GetAppMetaData(const string& appId /* @in */, const string& key /* @in */) = 0;

  // @text getAppProperty
  virtual uint32_t GetAppProperty(const string& appId /* @in */, const string& key /* @in */) = 0;

  // @text setAppProperty
  virtual uint32_t SetAppProperty(const string& appId /* @in */, const string& key /* @in */, const string& value /* @in */) = 0;

  // @text setMaxInactiveApps
  // @property  
  // @param maxInteractiveApps : maxInteractiveApps
  virtual uint32_t SetMaxInactiveApps(const uint32_t maxInteractiveApps  /* @in */) = 0;

  // @text getMaxInactiveApps
  // @property
  // @param maxInteractiveApps : maxInteractiveApps
  virtual uint32_t GetMaxInactiveApps(uint32_t &maxInteractiveApps  /* @out */) const = 0;

  // @text setMaxHibernatedApps
  // @property  
  // @param maxHibernatedApps : maxHibernatedApps
  virtual uint32_t SetMaxHibernatedApps(const uint32_t maxHibernatedApps  /* @in */) = 0;

  // @text getMaxHibernatedApps
  // @property
  // @param maxHibernatedApps : maxHibernatedApps
  virtual uint32_t GetMaxHibernatedApps(uint32_t &maxHibernatedApps /* @out */) const = 0;

  // @text setMaxHibernatedFlashUsage
  // @property  
  // @param maxHibernatedFlashUsage : maxHibernatedFlashUsage
  virtual uint32_t SetMaxHibernatedFlashUsage(const uint32_t maxHibernatedFlashUsage  /* @in */) = 0;

  // @text getMaxHibernatedFlashUsage
  // @property
  // @param maxHibernatedFlashUsage : maxHibernatedFlashUsage
  virtual uint32_t GetMaxHibernatedFlashUsage(uint32_t &maxHibernatedFlashUsage /* @out */) const = 0;

  // @text setMaxInactiveRamUsage
  // @property  
  // @param maxInactiveRamUsage : maxInactiveRamUsage
  virtual uint32_t SetMaxInactiveRamUsage(const uint32_t maxInactiveRamUsage /* @in */) = 0;

  // @text getMaxInactiveRamUsage
  // @property
  // @param maxInactiveRamUsage : maxInactiveRamUsage
  virtual uint32_t GetMaxInactiveRamUsage(uint32_t &maxInactiveRamUsage /* @out */) const = 0;
};
} // namespace Exchange
} // namespace WPEFramework