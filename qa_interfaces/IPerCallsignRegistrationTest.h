#pragma once

#include "Module.h"

namespace Thunder {
namespace QualityAssurance {

    // @json 1.0.0
    struct EXTERNAL IPerCallsignRegistrationTest
        : virtual public Core::IUnknown {
        enum { ID = ID_PERCALLSIGNREGISTRATION_TEST };

        /** @brief Start monitoring plugin lifecycle notifications through IShell. */
        virtual Core::hresult MonitorShell(
            const Core::OptionalType<string>& callsign /* @index */) = 0;

        /** @brief Stop an IShell notification registration. */
        virtual Core::hresult StopMonitoringShell(
            const Core::OptionalType<string>& callsign /* @index */) = 0;

        /** @brief Clear notifications received through IShell. */
        virtual Core::hresult ClearShellNotifications() = 0;

        /** @brief Return the IShell notification count. @param count The count. */
        virtual Core::hresult ShellNotificationCount(uint32_t& count /* @out */) const = 0;

        /** @brief Return the latest IShell notification. @param notification The notification. */
        virtual Core::hresult LastShellNotification(string& notification /* @out */) const = 0;

        /** @brief Start monitoring plugin state notifications through IController. */
        virtual Core::hresult MonitorController(
            const Core::OptionalType<string>& callsign /* @index */) = 0;

        /** @brief Stop an IController notification registration. */
        virtual Core::hresult StopMonitoringController(
            const Core::OptionalType<string>& callsign /* @index */) = 0;

        /** @brief Clear notifications received through IController. */
        virtual Core::hresult ClearControllerNotifications() = 0;

        /** @brief Return the IController notification count. @param count The count. */
        virtual Core::hresult ControllerNotificationCount(uint32_t& count /* @out */) const = 0;

        /** @brief Return the latest IController notification. @param notification The notification. */
        virtual Core::hresult LastControllerNotification(string& notification /* @out */) const = 0;
    };

} // namespace QualityAssurance
} // namespace Thunder