#pragma once

#include "Module.h"

namespace WPEFramework
{
    namespace Exchange
    {
        // @json 1.0.0 @text:keep
        struct EXTERNAL IPrivacy : virtual public Core::IUnknown
        {
            enum
            {
                ID = ID_PRIVACY
            };

            virtual ~IPrivacy() override = default;

            // @event
            struct EXTERNAL INotification : virtual public Core::IUnknown
            {
                enum
                {
                    ID = ID_PRIVACY_NOTIFICATION
                };

                // @text onAllowACRCollectionChanged
                // @brief The AllowACRCollection setting has changed.
                // @param allow: True to allow ACR collection, false to disallow
                virtual void OnAllowACRCollectionChanged(const bool allow) = 0;

                // @text onAllowAppContentAdTargetingChanged
                // @brief The AllowAppContentAdTargeting setting has changed.
                // @param allow: True to allow app content ad targeting, false to disallow
                virtual void OnAllowAppContentAdTargetingChanged(const bool allow) = 0;

                // @text onAllowCameraAnalyticsChanged
                // @brief The AllowCameraAnalytics setting has changed.
                // @param allow: True to allow camera analytics, false to disallow
                virtual void OnAllowCameraAnalyticsChanged(const bool allow) = 0;

                // @text onAllowPersonalizationChanged
                // @brief The AllowPersonalization setting has changed.
                // @param allow: True to allow personalization, false to disallow
                virtual void OnAllowPersonalizationChanged(const bool allow) = 0;

                // @text onAllowPrimaryBrowseAdTargetingChanged
                // @brief The AllowPrimaryBrowseAdTargeting setting has changed.
                // @param allow: True to allow primary browse ad targeting, false to disallow
                virtual void OnAllowPrimaryBrowseAdTargetingChanged(const bool allow) = 0;

                // @text onAllowPrimaryContentAdTargetingChanged
                // @brief The AllowPrimaryContentAdTargeting setting has changed.
                // @param allow: True to allow primary content ad targeting, false to disallow
                virtual void OnAllowPrimaryContentAdTargetingChanged(const bool allow) = 0;

                // @text onAllowProductAnalyticsChanged
                // @brief The AllowProductAnalytics setting has changed.
                // @param allow: True to allow product analytics, false to disallow
                virtual void OnAllowProductAnalyticsChanged(const bool allow) = 0;

                // @text onAllowRemoteDiagnosticsChanged
                // @brief The AllowRemoteDiagnostics setting has changed.
                // @param allow: True to allow remote diagnostics, false to disallow
                virtual void OnAllowRemoteDiagnosticsChanged(const bool allow) = 0;

                // @text onAllowResumePointsChanged
                // @brief The AllowResumePoints setting has changed.
                // @param allow: True to allow resume points, false to disallow
                virtual void OnAllowResumePointsChanged(const bool allow) = 0;

                // @text onAllowUnentitledPersonalizationChanged
                // @brief The AllowUnentitledPersonalization setting has changed.
                // @param allow: True to allow unentitled personalization, false to disallow
                virtual void OnAllowUnentitledPersonalizationChanged(const bool allow) = 0;

                // @text onAllowUnentitledResumePointsChanged
                // @brief The AllowUnentitledResumePoints setting has changed.
                // @param allow: True to allow unentitled resume points, false to disallow
                virtual void OnAllowUnentitledResumePointsChanged(const bool allow) = 0;

                // @text onAllowWatchHistoryChanged
                // @brief The AllowWatchHistory setting has changed.
                // @param allow: True to allow watch history, false to disallow
                virtual void OnAllowWatchHistoryChanged(const bool allow) = 0;

                // @text onAllowContinueWatchingOptOutChanged
                // @brief The AllowContinueWatchingOptOut setting has changed.
                // @param allow: True to allow continue watching opt out, false to disallow
                virtual void OnAllowContinueWatchingOptOutChanged(const bool allow) = 0;

                // @text onAllowPersonalisedRecsOptOutChanged
                // @brief The AllowPersonalisedRecsOptOut setting has changed.
                // @param allow: True to allow personalised recs opt out, false to disallow
                virtual void OnAllowPersonalisedRecsOptOutChanged(const bool allow) = 0;

                // @text onAllowProductAnalyticsOptOutChanged
                // @brief The AllowProductAnalyticsOptOut setting has changed.
                // @param allow: True to allow product analytics opt out, false to disallow
                virtual void OnAllowProductAnalyticsOptOutChanged(const bool allow) = 0;
            };

            virtual Core::hresult Register(INotification *notification /* @in */) = 0;
            virtual Core::hresult Unregister(INotification *notification /* @in */) = 0;

            // @property
            // @text allowACRCollection
            // @brief Allow ACR collection
            // @param allow: True to allow ACR collection, false to disallow
            virtual Core::hresult AllowACRCollection(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowACRCollection(bool &allow /* @out */) const = 0;

            // @property
            // @text allowAppContentAdTargeting
            // @brief Allow app content ad targeting
            // @param allow: True to allow app content ad targeting, false to disallow
            virtual Core::hresult AllowAppContentAdTargeting(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowAppContentAdTargeting(bool &allow /* @out */) const = 0; 

            // @property
            // @text allowCameraAnalytics
            // @brief Allow camera analytics
            // @param allow: True to allow camera analytics, false to disallow
            virtual Core::hresult AllowCameraAnalytics(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowCameraAnalytics(bool &allow /* @out */) const = 0;

            // @property
            // @text allowPersonalization
            // @brief Allow personalization
            // @param allow: True to allow personalization, false to disallow
            virtual Core::hresult AllowPersonalization(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowPersonalization(bool &allow /* @out */) const = 0;

            // @property
            // @text allowPrimaryBrowseAdTargeting
            // @brief Allow primary browse ad targeting
            // @param allow: True to allow primary browse ad targeting, false to disallow
            virtual Core::hresult AllowPrimaryBrowseAdTargeting(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowPrimaryBrowseAdTargeting(bool &allow /* @out */) const = 0;

            // @property
            // @text allowPrimaryContentAdTargeting
            // @brief Allow primary content ad targeting
            // @param allow: True to allow primary content ad targeting, false to disallow
            virtual Core::hresult AllowPrimaryContentAdTargeting(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowPrimaryContentAdTargeting(bool &allow /* @out */) const = 0;

            // @property
            // @text allowProductAnalytics
            // @brief Allow product analytics
            // @param allow: True to allow product analytics, false to disallow
            virtual Core::hresult AllowProductAnalytics(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowProductAnalytics(bool &allow /* @out */) const = 0;

            // @property
            // @text allowRemoteDiagnostics
            // @brief Allow remote diagnostics
            // @param allow: True to allow remote diagnostics, false to disallow
            virtual Core::hresult AllowRemoteDiagnostics(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowRemoteDiagnostics(bool &allow /* @out */) const = 0;

            // @property
            // @text allowResumePoints
            // @brief Allow resume points
            // @param allow: True to allow resume points, false to disallow
            virtual Core::hresult AllowResumePoints(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowResumePoints(bool &allow /* @out */) const = 0;

            // @property
            // @text allowUnentitledPersonalization
            // @brief Allow unentitled personalization
            // @param allow: True to allow unentitled personalization, false to disallow
            virtual Core::hresult AllowUnentitledPersonalization(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowUnentitledPersonalization(bool &allow /* @out */) const = 0;

            // @property
            // @text allowUnentitledResumePoints
            // @brief Allow unentitled resume points
            // @param allow: True to allow unentitled resume points, false to disallow
            virtual Core::hresult AllowUnentitledResumePoints(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowUnentitledResumePoints(bool &allow /* @out */) const = 0;

            // @property
            // @text allowWatchHistory
            // @brief Allow watch history
            // @param allow: True to allow watch history, false to disallow
            virtual Core::hresult AllowWatchHistory(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowWatchHistory(bool &allow /* @out */) const = 0;
            
            // @property
            // @text allowContinueWatchingOptOut
            // @brief Allow continue watching opt out
            // @param allow: True to allow continue watching opt out, false to disallow
            virtual Core::hresult AllowContinueWatchingOptOut(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowContinueWatchingOptOut(bool &allow /* @out */) const = 0;

            // @property
            // @text allowPersonalisedRecsOptOut
            // @brief Allow personalised recs opt out
            // @param allow: True to allow personalised recs opt out, false to disallow
            virtual Core::hresult AllowPersonalisedRecsOptOut(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowPersonalisedRecsOptOut(bool &allow /* @out */) const = 0;

            // @property
            // @text allowProductAnalyticsOptOut
            // @brief Allow product analytics opt out
            // @param allow: True to allow product analytics opt out, false to disallow
            virtual Core::hresult AllowProductAnalyticsOptOut(const bool allow /* @in */) = 0;
            virtual Core::hresult AllowProductAnalyticsOptOut(bool &allow /* @out */) const = 0;

            // @brief Get all privacy settings
            // @text getSettings
            // @param allowACRCollection: True if ACR collection is allowed, false if disallowed
            // @param allowAppContentAdTargeting: True if app content ad targeting is allowed, false if disallowed
            // @param allowCameraAnalytics: True if camera analytics is allowed, false if disallowed
            // @param allowPersonalization: True if personalization is allowed, false if disallowed
            // @param allowPrimaryBrowseAdTargeting: True if primary browse ad targeting is allowed, false if disallowed
            // @param allowPrimaryContentAdTargeting: True if primary content ad targeting is allowed, false if disallowed
            // @param allowProductAnalytics: True if product analytics is allowed, false if disallowed
            // @param allowRemoteDiagnostics: True if remote diagnostics is allowed, false if disallowed
            // @param allowResumePoints: True if resume points is allowed, false if disallowed
            // @param allowUnentitledPersonalization: True if unentitled personalization is allowed, false if disallowed
            // @param allowUnentitledResumePoints: True if unentitled resume points is allowed, false if disallowed
            // @param allowWatchHistory: True if watch history is allowed, false if disallowed
            // @param allowContinueWatchingOptOut: True if continue watching opt out is allowed, false if disallowed
            // @param allowPersonalisedRecsOptOut: True if personalised recs opt out is allowed, false if disallowed
            // @param allowProductAnalyticsOptOut: True if product analytics opt out is allowed, false if disallowed
            virtual Core::hresult GetSettings(bool &allowACRCollection /* @out */,
                                             bool &allowAppContentAdTargeting /* @out */,
                                             bool &allowCameraAnalytics /* @out */,
                                             bool &allowPersonalization /* @out */,
                                             bool &allowPrimaryBrowseAdTargeting /* @out */,
                                             bool &allowPrimaryContentAdTargeting /* @out */,
                                             bool &allowProductAnalytics /* @out */,
                                             bool &allowRemoteDiagnostics /* @out */,
                                             bool &allowResumePoints /* @out */,
                                             bool &allowUnentitledPersonalization /* @out */,
                                             bool &allowUnentitledResumePoints /* @out */,
                                             bool &allowWatchHistory /* @out */,
                                             bool &allowContinueWatchingOptOut /* @out */,
                                             bool &allowPersonalisedRecsOptOut /* @out */,
                                             bool &allowProductAnalyticsOptOut /* @out */) const = 0;
        };
    } // namespace Exchange
} // namespace WPEFramework
