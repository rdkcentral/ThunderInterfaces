#pragma once

#include "Module.h"

namespace Thunder {
namespace QualityAssurance {

    // @json 1.0.0
    struct EXTERNAL IPerCallsignRegistrationIShellTest
        : virtual public Core::IUnknown {
        enum { ID = ID_PERCALLSIGNREGISTRATION_ISHELL_TEST };

        /**
         * @brief Start monitoring plugin lifecycle notifications through IShell.
         *
         * @param callsign The plugin callsign to monitor; when unset, monitor all plugins.
         */
        virtual Core::hresult Monitor(
            const Core::OptionalType<string>& callsign /* @index */) = 0;

        /**
         * @brief Stop monitoring plugin lifecycle notifications through IShell.
         *
         * @param callsign The selection used when monitoring started; when unset, stop monitoring all plugins.
         */
        virtual Core::hresult StopMonitoring(
            const Core::OptionalType<string>& callsign /* @index */) = 0;

        /**
         * @brief Clear all lifecycle notifications recorded by this test plugin.
         */
        virtual Core::hresult ClearNotifications() = 0;

        /**
         * @brief Return the number of lifecycle notifications recorded since the last clear operation.
         *
         * @param count The number of recorded notifications.
         */
        virtual Core::hresult NotificationCount(uint32_t& count /* @out */) const = 0;

        /**
         * @brief Return the most recently recorded lifecycle notification.
         *
         * @param notification The most recently recorded event and callsign.
         */
        virtual Core::hresult LastNotification(string& notification /* @out */) const = 0;
    };

} // namespace QualityAssurance
} // namespace Thunder