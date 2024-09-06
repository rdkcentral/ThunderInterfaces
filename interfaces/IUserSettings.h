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

namespace WPEFramework {
namespace Exchange {
  // @json @text:keep
  struct EXTERNAL IUserSettings : virtual public Core::IUnknown {
  enum { ID = ID_USER_SETTINGS };

  // @event
  struct EXTERNAL INotification : virtual public Core::IUnknown {
    enum { ID = ID_USER_SETTINGS_NOTIFICATION };

    // @alt onAudioDescriptionChanged
    // @brief The AudioDescription setting has changed.
    // @param enabled: Enabled/Disabled.
    virtual void OnAudioDescriptionChanged(const bool enabled) = 0;

    // @alt onPreferredAudioLanguagesChanged
    // @brief The preferredLanguages setting has changed.
    // @param preferredLanguages: PreferredLanguages.
    virtual void OnPreferredAudioLanguagesChanged(const string& preferredLanguages /* @text preferredLanguages */) = 0;

    // @alt onPresentationLanguageChanged
    // @brief The PresentationLanguages setting has changed.
    // @param presentationLanguage: PresentationLanguage.
    virtual void OnPresentationLanguageChanged(const string& presentationLanguage /* @text presentationLanguage */) = 0;

    // @alt onCaptionsChanged
    // @brief The Captions setting has changed.
    // @param enabled: Enabled/Disabled.
    virtual void OnCaptionsChanged(const bool enabled) = 0;

    // @alt onPreferredCaptionsLanguagesChanged
    // @brief The PreferredCaptionsLanguages setting has changed.
    // @param preferredLanguages: PreferredLanguages.
    virtual void OnPreferredCaptionsLanguagesChanged(const string& preferredLanguages /* @text preferredLanguages */) = 0;

    // @alt onPreferredClosedCaptionServiceChanged
    // @brief The PreferredClosedCaptionService setting has changed.
    // @param service: "CC[1-4]", "TEXT[1-4]", "SERVICE[1-64]".
    virtual void OnPreferredClosedCaptionServiceChanged(const string& service) = 0;

    // @alt onPrivacyModeChanged
    // @brief The PrivacyMode setting has changed.
    // @param privacyMode: "SHARE", "DO_NOT_SHARE".
    virtual void OnPrivacyModeChanged(const string& privacyMode /* @text privacyMode */) = 0;

    // @alt onPinControlChanged
    // @brief The PinControl setting has changed.
    // @param enabled: Enabled/Disabled.
    virtual void OnPinControlChanged(const bool enabled) = 0;

    // @alt onViewingRestrictionsChanged
    // @brief The ViewingRestrictions setting has changed.
    // @param viewingRestrictions:  Empty string
    virtual void OnViewingRestrictionsChanged(const string& viewingRestrictions /* @text viewingRestrictions */) = 0;

    // @alt onViewingRestrictionsWindowChanged
    // @brief The ViewingRestrictionsWindow setting has changed.
    // @param viewingRestrictionsWindow: "ALWAYS"
    virtual void OnViewingRestrictionsWindowChanged(const string& viewingRestrictionsWindow /* @text viewingRestrictionsWindow */) = 0;

    // @alt onLiveWatershedChanged
    // @brief The LiveWatershed setting has changed.
    // @param enabled: Enabled/Disabled.
    virtual void onLiveWatershedChanged(const bool enabled) = 0;

    // @alt onPlaybackWatershedChanged
    // @brief The PlaybackWatershed setting has changed.
    // @param enabled: Enabled/Disabled.
    virtual void OnPlaybackWatershedChanged(const bool enabled) = 0;

    // @alt onBlockNotRatedContentChanged
    // @brief The BlockNotRatedContent setting has changed.
    // @param enabled: Enabled/Disabled.
    virtual void OnBlockNotRatedContentChanged(const bool enabled) = 0;

    // @alt onPinOnPurchaseChanged
    // @brief The PinOnPurchase setting has changed.
    // @param enabled: Enabled/Disabled.
    virtual void OnPinOnPurchaseChanged(const bool enabled) = 0;

  };

  virtual uint32_t Register(Exchange::IUserSettings::INotification* notification /* @in */) = 0;
  virtual uint32_t Unregister(Exchange::IUserSettings::INotification* notification /* @in */) = 0;

  // @alt setAudioDescription
  // @brief Sets AudioDescription ON/OFF. Players should preferred Audio Descriptive tracks over normal audio track when enabled
  // @param enabled: Enabled/Disabled
  virtual uint32_t SetAudioDescription(const bool enabled /* @in */) = 0;

  // @alt getAudioDescription
  // @brief Gets the current AudioDescription setting
  // @param enabled: Enabled/Disabled
  virtual uint32_t GetAudioDescription(bool &enabled /* @out */) const = 0;

  // @alt setPreferredAudioLanguages
  // @brief A prioritized list of ISO 639-2/B codes for the preferred audio languages,
  // expressed as a comma separated lists of languages of zero of more elements.
  // The players will pick the audio track that has the best match compared with
  // this list. In the absence of a matching track, the player should by best
  // effort select the preferred audio track.*/
  // @param preferredLanguages: PreferredLanguages
  virtual uint32_t SetPreferredAudioLanguages(const string& preferredLanguages  /* @in @text preferredLanguages */) = 0;

  // @alt getPreferredAudioLanguages
  // @brief Gets the current PreferredAudioLanguages setting
  // @param preferredLanguages: PreferredLanguages
  virtual uint32_t GetPreferredAudioLanguages(string &preferredLanguages /* @out @text preferredLanguages */) const = 0;

  // @alt setPresentationLanguage
  // @brief Sets the presentationLanguage in a full BCP 47 value, including script, region, variant
  // @param presentationLanguage: "en-US", "es-US", "en-CA", "fr-CA"
  virtual uint32_t SetPresentationLanguage(const string& presentationLanguage /* @in @text presentationLanguage */) = 0;

  // @alt getPresentationLanguage
  // @brief Gets the presentationLanguage
  // @param presentationLanguage: "en-US", "es-US", "en-CA", "fr-CA"
  virtual uint32_t GetPresentationLanguage(string &presentationLanguage /* @out @text presentationLanguage */) const = 0;

  // @alt setCaptions
  // @brief brief Sets Captions ON/OFF.
  // @details A setting of ON indicates that Players should select a subtitle track for presentation
  // The Setting does not influence any running sessions. It is up to the player to enforce the setting.
  // This is a global state persisted by the TextTrack plug-in applying to all forms of text; closed captions, Captions
  // and timed text types.
  // Media players should to listen to OnCaptionsChanged notifications to react to platform wide dynamic state changes
  // of this state while a playback is active.
  // When media players start playback, they should also call the GetCaptions method to retrieve the current enabled state.
  // This holds true for media players that utilize TextTrack render sessions for text track decode-display and also for media
  // players or apps that decode-display internally 
  // @param enabled: Sets the state
  virtual uint32_t SetCaptions(const bool enabled  /* @in */) = 0;

  // @alt getCaptions
  // @brief Gets the Captions setting.
  // @param enabled: Receives the state
  virtual uint32_t GetCaptions(bool &enabled /* @out */) const = 0;

  // @alt setPreferredCaptionsLanguages
  // @brief Set preferred languages for captions.
  // @details A prioritized list of ISO 639-2/B codes for the preferred Captions languages,
  // expressed as a comma separated lists of languages of zero of more elements.
  // The players will pick the subtitle track that has the best match compared with
  // this list. In the absence of a matching track, the player should by best
  // effort select the preferred subtitle track. 
  // @param preferredLanguages: Is the list to set (e.g. "eng,fra")
  virtual uint32_t SetPreferredCaptionsLanguages(const string& preferredLanguages  /* @in @text preferredLanguages */) = 0;

  // @alt getPreferredCaptionsLanguages
  // @brief Gets the current PreferredCaptionsLanguages setting.
  // @param preferredLanguages: "eng,fra"
  virtual uint32_t GetPreferredCaptionsLanguages(string &preferredLanguages /* @out @text preferredLanguages */) const = 0;

  // @alt setPreferredClosedCaptionService
  // @brief Sets the PreferredClosedCaptionService.
  // @details The setting should be honored by the player. The behaviour of AUTO may be player specific.
  // Valid input for service is "CC[1-4]", "TEXT[1-4]", "SERVICE[1-64]" 
  // @param service: Identifies the service to display e.g. "CC3".
  virtual uint32_t SetPreferredClosedCaptionService(const string& service  /* @in */) = 0;

  // @alt getPreferredClosedCaptionService
  // @brief Gets the current PreferredClosedCaptionService setting.
  // @param service: Identifies the service to display e.g. "CC3".
  virtual uint32_t GetPreferredClosedCaptionService(string &service /* @out */) const = 0;

  // @alt setPrivacyMode
  // @brief Sets the PrivacyMode.
  // @details The setting should be honored by the Telemetry.
  // If privacyMode is "DO_NOT_SHARE", logs and crash report should not be uploaded.
  // @param privacyMode: "SHARE", "DO_NOT_SHARE"
  virtual uint32_t SetPrivacyMode(const string& privacyMode /* @in @text privacyMode*/) = 0;

  // @alt getPrivacyMode
  // @brief Gets the current PrivacyMode setting.
  // @param privacyMode: "SHARE"
  virtual uint32_t GetPrivacyMode(string &privacyMode /* @out @text privacyMode */) const = 0;

  // @alt setPinControl
  // @brief Sets PinControl ON/OFF. Parental Control as a whole is enabled or disabled.
  // @param enabled: Enabled/Disabled
  virtual uint32_t SetPinControl(const bool enabled /* @in */) = 0;

  // @alt getPinControl
  // @brief Gets the PinControl setting
  // @param enabled: Enabled/Disabled
  virtual uint32_t GetPinControl(bool &enabled /* @out */) const = 0;

  // @alt setViewingRestrictions
  // @brief Sets the ViewingRestrictions.
  // @details A JSON document that escribes the rating scheme(s) and ratings that are blocked.
  // @param viewingRestrictions: A JSON document that describes the rating scheme(s) and ratings that are blocked.
  virtual uint32_t SetViewingRestrictions(const string& viewingRestrictions /* @in @text viewingRestrictions */) = 0;

  // @alt getViewingRestrictions
  // @brief Gets the current ViewingRestrictions.
  // @param viewingRestrictions: A JSON document that escribes the rating scheme(s) and ratings that are blocked.
  virtual uint32_t GetViewingRestrictions(string &viewingRestrictions /* @out @text viewingRestrictions */) const = 0;

  // @alt setViewingRestrictionsWindow
  // @brief Sets the ViewingRestrictionsWindow.
  // @details A project-specific representation of the time interval when viewing
  // restrictions are to be applied, if applicable for the project
  // @param viewingRestrictionsWindow: A project-specific representation of the time interval.Eg: "ALWAYS"
  virtual uint32_t SetViewingRestrictionsWindow(const string &viewingRestrictionsWindow /* @in @text viewingRestrictionsWindow */) = 0;
  
  // @alt getViewingRestrictionsWindow
  // @brief Gets the current ViewingRestrictionsWindow.
  // @param viewingRestrictionsWindow: A project-specific representation of the time interval.Eg: "ALWAYS"
  virtual uint32_t GetViewingRestrictionsWindow(string &viewingRestrictionsWindow /* @out @text viewingRestrictionsWindow */) const = 0;

  // @alt setLiveWatershed
  // @brief Sets LiveWatershed ON/OFF.Whether project-specific watershed rules
  // should be applied for live content, if applicable for the project.
  // @param enabled: Enabled/Disabled
  virtual uint32_t SetLiveWatershed(const bool enabled /* @in */) = 0;

  // @alt getLiveWatershed
  // @brief Gets the LiveWatershed setting
  // @param enabled: Enabled/Disabled
  virtual uint32_t GetLiveWatershed(bool &enabled /* @out */) const = 0;

  // @alt setPlaybackWatershed
  // @brief Sets PlaybackWatershed ON/OFF. Whether project-specific watershed rules
  // should be applied for non-live content, if applicable for the project.
  // @param enabled: Enabled/Disabled
  virtual uint32_t SetPlaybackWatershed(const bool enabled /* @in */) = 0;

  // @alt getPlaybackWatershed
  // @brief Gets the PlaybackWatershed setting
  // @param enabled: Enabled/Disabled
  virtual uint32_t GetPlaybackWatershed(bool &enabled /* @out */) const = 0;

  // @alt setBlockNotRatedContent
  // @brief Sets BlockNotRatedContent ON/OFF. Whether content that is not rated should be
  // blocked, if applicable for the project.
  // @param enabled: Enabled/Disabled
  virtual uint32_t SetBlockNotRatedContent(const bool enabled /* @in */) = 0;

  // @alt getBlockNotRatedContent
  // @brief Gets the BlockNotRatedContent setting
  // @param enabled: Enabled/Disabled
  virtual uint32_t GetBlockNotRatedContent(bool &enabled /* @out */) const = 0;

  // @alt setPinOnPurchase
  // @brief Sets PinOnPurchase ON/OFF.Whether a PIN challenge should be made
  // when a purchase is attempted.
  // @param enabled: Enabled/Disabled
  virtual uint32_t SetPinOnPurchase(const bool enabled /* @in */) = 0;

  // @alt getPinOnPurchase
  // @brief Gets the PinOnPurchase setting
  // @param enabled: Enabled/Disabled
  virtual uint32_t GetPinOnPurchase(bool &enabled /* @out */) const = 0;

};
} // namespace Exchange
} // namespace WPEFramework

