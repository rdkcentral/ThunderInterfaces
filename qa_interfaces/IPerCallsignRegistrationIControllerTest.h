#pragma once

#include "Module.h"

namespace Thunder {
namespace QualityAssurance {

// @json 1.0.0
struct EXTERNAL IPerCallsignRegistrationIControllerTest
    : virtual public Core::IUnknown {
    enum { ID = ID_PERCALLSIGNREGISTRATION_ICONTROLLER_TEST };

    /**
     * @brief Start monitoring plugin state notifications through IController.
     *
     * @param callsign The plugin callsign to monitor; when unset, monitor all plugins.
     */
    virtual Core::hresult Monitor(
        const Core::OptionalType<string>& callsign /* @index */) = 0;

    /**
     * @brief Stop monitoring plugin state notifications through IController.
     *
     * @param callsign The selection used when monitoring started.
     */
    virtual Core::hresult StopMonitoring(
        const Core::OptionalType<string>& callsign /* @index */) = 0;

    /**
     * @brief Clear all state notifications recorded by this test plugin.
     */
    virtual Core::hresult ClearNotifications() = 0;

    /**
     * @brief Return the number of notifications recorded since the last clear.
     *
     * @param count Number of recorded notifications.
     */
    virtual Core::hresult NotificationCount(
        uint32_t& count /* @out */) const = 0;

    /**
     * @brief Return the most recently recorded notification.
     *
     * @param notification Most recently recorded notification.
     */
    virtual Core::hresult LastNotification(
        string& notification /* @out */) const = 0;
};

} // namespace QualityAssurance
} // namespace Thunder