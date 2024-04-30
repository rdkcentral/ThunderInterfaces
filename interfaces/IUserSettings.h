/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2024 Synamedia Ltd.
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

namespace WPEFramework {
namespace Exchange {
/* @json */
struct EXTERNAL IUserSettings : virtual public Core::IUnknown {
  enum { ID = ID_USER_SETTINGS };

  struct EXTERNAL INotification : virtual public Core::IUnknown {
    enum { ID = ID_USER_SETTINGS_NOTIFICATION };

    /** The AudioDescription setting has changed. */
    virtual void OnAudioDescriptionChanged(bool enabled) = 0;
    /** The PreferredAudioLanguages setting has changed. */
    virtual void OnPreferredAudioLanguagesChanged(const string preferredLanguages) = 0;
    /** The Locale setting has changed. */
    virtual void OnLocaleChanged(const string &locale) = 0;
    /**
     * @brief The Captions setting has changed.
     * @param enabled Indicates the new setting
     */
    virtual void OnCaptionsChanged(bool enabled) = 0;
    /**
     * @brief The PreferredCaptionsLanguages setting has changed.
     * @param preferredLanguages Indicates the new setting
     */
    virtual void OnPreferredCaptionsLanguagesChanged(const string &preferredLanguages) = 0;
    /**
     * @brief The PreferredClosedCaptionService setting has changed.
     * @param service Valid values for service is "CC[1-4]", "TEXT[1-4]", "SERVICE[1-64]"
     */
    virtual void OnPreferredClosedCaptionServiceChanged(const std::string &service) = 0;
  };

  /** Register notification interface */
  virtual uint32_t Register(Exchange::IUserSettings::INotification *notification /* @in */) = 0;
  /** Unregister notification interface */
  virtual uint32_t Unregister(Exchange::IUserSettings::INotification *notification /* @in */) = 0;

  /** Sets AudioDescription ON/OFF. Players should preferred Audio Descriptive
   * tracks over normal audio track when enabled.*/
  virtual uint32_t SetAudioDescription(const bool &enabled /* @in */) = 0;
  /** Gets the current AudioDescription setting.*/
  virtual uint32_t GetAudioDescription(bool &enabled /* @out */) const = 0;

  /** A prioritized list of ISO 639-2/B codes for the preferred audio languages,
   * expressed as a comma separated lists of languages of zero of more elements.
   * The players will pick the audio track that has the best match compared with
   * this list. In the absence of a matching track, the player should by best
   * effort select the preferred audio track.*/
  virtual uint32_t SetPreferredAudioLanguages(const string &preferredLanguages  /* @in */) = 0;
  /** Gets the current PreferredAudioLanguages setting.*/
  virtual uint32_t GetPreferredAudioLanguages(string &preferredLanguages /* @out */) const = 0;

  /** Sets the preferred locale in a full BCP 47 value, including script,
   * region, variant. I.e. "en-US", "es-US", "en-CA", "fr-CA"
   */
  virtual uint32_t SetLocale(const string &locale  /* @in */) = 0;
  /** Gets the preferred locale */
  virtual uint32_t GetLocale(string &locale /* @out */) const = 0;

   /**
   * @brief Sets Captions ON/OFF.
   * @details A setting of ON indicates that Players should select a subtitle track for presentation
   * The Setting does not influence any running sessions. It is up to the player to enforce the setting.
   * This is a global state persisted by the TextTrack plug-in applying to all forms of text; closed captions, Captions
   * and timed text types.
   * Media players should to listen to OnCaptionsChanged notifications to react to platform wide dynamic state changes
   * of this state while a playback is active.
   * When media players start playback, they should also call the GetCaptions method to retrieve the current enabled state.
   * This holds true for media players that utilize TextTrack render sessions for text track decode-display and also for media
   * players or apps that decode-display internally.
   * @param enabled Sets the state
   */
  virtual uint32_t SetCaptions(const bool &enabled  /* @in */) = 0;
  /**
   * @brief Gets the Captions setting.
   * @param enabled Receives the state
   */
  virtual uint32_t GetCaptions(bool &enabled /* @out */) const = 0;
 /**
   * @brief Set preferred languages for captions
   * @details A prioritized list of ISO 639-2/B codes for the preferred Captions languages,
   * expressed as a comma separated lists of languages of zero of more elements.
   * The players will pick the subtitle track that has the best match compared with
   * this list. In the absence of a matching track, the player should by best
   * effort select the preferred subtitle track.
   * @param preferredLanguages Is the list to set (e.g. "eng,fra")
   */
  virtual uint32_t SetPreferredCaptionsLanguages(const string &preferredLanguages  /* @in */) = 0;
  /**
   * @brief Gets the current PreferredCaptionsLanguages setting.
   */
  virtual uint32_t GetPreferredCaptionsLanguages(string &preferredLanguages /* @out */) const = 0;
 /**
   * @brief Sets the PreferredClosedCaptionService.
   * @details The setting should be honored by the player. The behaviour of AUTO may be player specific.
   * Valid input for service is "CC[1-4]", "TEXT[1-4]", "SERVICE[1-64]"
   * @param service Identifies the service to display e.g. "CC3".
   */
  virtual uint32_t SetPreferredClosedCaptionService(const std::string &service  /* @in */) = 0;
  /**
   * @brief Gets the current PreferredClosedCaptionService setting.
   * @param service Identifies the service to display e.g. "CC3".
   */
  virtual uint32_t GetPreferredClosedCaptionService(std::string &service /* @out */) const = 0;
};
} // namespace Exchange
} // namespace WPEFramework