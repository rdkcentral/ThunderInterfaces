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

namespace WPEFramework
{
    namespace Exchange
    {
        // @json @text:keep
        struct EXTERNAL IPowerManager : virtual public Core::IUnknown {
        enum { ID = ID_POWER_MANAGER };

        enum PowerState : uint8_t {
            POWER_STATE_UNKNOWN   = 0  /* @text UNKNOWN */,
            POWER_STATE_OFF                = 1  /* @text OFF */,
            POWER_STATE_STANDBY            = 2  /* @text STANDBY */,
            POWER_STATE_ON                 = 3  /* @text ON */,
            POWER_STATE_STANDBY_LIGHT_SLEEP  = 4  /* @text LIGHT_SLEEP */,
            POWER_STATE_STANDBY_DEEP_SLEEP   = 5  /* @text DEEP_SLEEP */
        };

        enum ThermalTemperature : uint8_t {
            THERMAL_TEMPERATURE_UNKNOWN     = 0  /* @text UNKNOWN Thermal Temperature */,
            THERMAL_TEMPERATURE_NORMAL     = 1  /* @text Normal Thermal Temperature */,
            THERMAL_TEMPERATURE_HIGH       = 2  /* @text High Thermal Temperature */,
            THERMAL_TEMPERATURE_CRITICAL   = 4  /* @text Critial Thermal Temperature */
        };

        enum WakeupSrcType : uint8_t {
            WAKEUP_SRC_UNKNOWN = 0            /* @text UNKNOWN */,
            WAKEUP_SRC_VOICE = 1            /* @text VOICE */,
            WAKEUP_SRC_PRESENCEDETECTED = 2 /* @text PRESENCEDETECTED */,
            WAKEUP_SRC_BLUETOOTH = 3        /* @text BLUETOOTH */,
            WAKEUP_SRC_RF4CE = 4            /* @text RF4CE */,
            WAKEUP_SRC_WIFI = 5             /* @text WIFI */,
            WAKEUP_SRC_IR = 6               /* @text IR */,
            WAKEUP_SRC_POWERKEY = 7         /* @text POWERKEY */,
            WAKEUP_SRC_TIMER = 8            /* @text TIMER */,
            WAKEUP_SRC_CEC = 9              /* @text CEC */,
            WAKEUP_SRC_LAN = 10              /* @text LAN */
        };

        enum WakeupReason : uint8_t {
            WAKEUP_REASON_UNKNOWN = 0              /* @text UNKNOWN */,
            WAKEUP_REASON_IR = 1              /* @text IR */,
            WAKEUP_REASON_BLUETOOTH = 2       /* @text BLUETOOTH */,
            WAKEUP_REASON_RF4CE = 3           /* @text RF4CE */,
            WAKEUP_REASON_GPIO = 4            /* @text GPIO */,
            WAKEUP_REASON_LAN = 5             /* @text LAN */,
            WAKEUP_REASON_WIFI = 6            /* @text WIFI */,
            WAKEUP_REASON_TIMER = 7           /* @text TIMER */,
            WAKEUP_REASON_FRONTPANEL = 8      /* @text FRONTPANEL */,
            WAKEUP_REASON_WATCHDOG = 9        /* @text WATCHDOG */,
            WAKEUP_REASON_SOFTWARERESET = 10   /* @text SOFTWARERESET */,
            WAKEUP_REASON_THERMALRESET = 11   /* @text THERMALRESET */,
            WAKEUP_REASON_WARMRESET = 12      /* @text WARMRESET */,
            WAKEUP_REASON_COLDBOOT = 13       /* @text COLDBOOT */,
            WAKEUP_REASON_STRAUTHFAIL = 14    /* @text STR_AUTH_FAIL */,
            WAKEUP_REASON_CEC = 15            /* @text CEC */,
            WAKEUP_REASON_PRESENCE = 16       /* @text PRESENCE */,
            WAKEUP_REASON_VOICE = 17       /* @text VOICE */
        };

        enum SystemMode : uint8_t {
            SYSTEM_MODE_UNKNOWN      = 0  /* @text UNKNOWN */,
            SYSTEM_MODE_NORMAL      = 1  /* @text NORMAL */,
            SYSTEM_MODE_EAS         = 2  /* @text EAS */,
            SYSTEM_MODE_WAREHOUSE   = 3  /* @text WAREHOUSE */
        };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown
        {
            enum { ID = ID_POWER_MANAGER_NOTIFICATION };

            // @brief Power mode changed
            // @text onPowerModeChanged
            // @param currentState: Current Power State
            // @param newState: New Power State
            virtual void OnPowerModeChanged(const PowerState &currentState, const PowerState &newState) = 0;
            /** The Power Mode is going to change - sent before actual power mode change. */

            // @brief Power mode Pre-change event
            // @text onPowerModePreChange
            // @param currentState: Current Power State
            // @param newState: Changing power state to this New Power State
            virtual void OnPowerModePreChange(const PowerState &currentState, const PowerState &newState) = 0;

            // @brief Deep sleep timeout event
            // @text onDeepSleepTimeout
            // @param wakeupTimeout: Deep sleep wakeup timeout in seconds
            virtual void OnDeepSleepTimeout(const int &wakeupTimeout) = 0;

            // @brief Network Standby Mode changed event - only on XIone
            // @text onNetworkStandbyModeChanged
            // @param enabled: network standby enabled or disabled
            virtual void OnNetworkStandbyModeChanged(const bool &enabled) = 0;

            // @brief Thermal Mode changed event
            // @text onThermalModeChanged
            // @param currentThermalLevel: current thermal level
            // @param newThermalLevel: new thermal level
            // @param currentTemperature: current temperature
            virtual void OnThermalModeChanged(const ThermalTemperature &currentThermalLevel, const ThermalTemperature &newThermalLevel, const float &currentTemperature) = 0;

            // @brief Reboot begin event
            // @text onRebootBegin
            // @param rebootReasonCustom: Reboot reason custom
            // @param rebootReasonOther: Reboot reason other
            // @param rebootRequestor: Reboot requested by 
            virtual void OnRebootBegin(const string &rebootReasonCustom, const string &rebootReasonOther, const string &rebootRequestor) = 0;

        };
 
        virtual uint32_t Register(Exchange::IPowerManager::INotification* notification /* @in */) = 0;
        virtual uint32_t Unregister(Exchange::IPowerManager::INotification* notification /* @in */) = 0;

        /** Sets Power State . */
        // @text setPowerState
        // @brief Set Power State
        // @param powerState: Set power to this state
        // @param reason: Reason for moving to the power state
        virtual uint32_t SetPowerState(const int &keyCode /* @in */, const PowerState &powerState /* @in */,const string &reason /* @in */) = 0;

        /** Gets the Power State.*/
        // @text getPowerState
        // @brief Get Power State
        // @param powerState: Get current power state
        virtual uint32_t GetPowerState(PowerState& currentState /* @out */, PowerState &previousState /* @out */) const = 0;

        /** Gets the current Thermal state.*/
        // @text getThermalState
        // @brief Get Current Thermal State (temperature)
        // @param currentTemperature: current temperature
        virtual uint32_t GetThermalState(float& currentTemperature /* @out */) const = 0;

        /** Sets the Temperature Thresholds.*/
        // @text setTemperatureThresholds
        // @brief Set Temperature Thresholds
        // @param high: high threshold 
        // @param critical : critical threshold 
        virtual uint32_t SetTemperatureThresholds(float high /* @in */, float critical /* @in */) = 0;

        /** Gets the current Temperature Thresholds.*/
        // @text getTemperatureThresholds
        // @brief Get Temperature Thresholds
        // @param high: high threshold 
        // @param critical : critical threshold 
        virtual uint32_t GetTemperatureThresholds(float& high /* @out */, float& critical /* @out */) const = 0;

        /** Sets the current Temperature Grace interval.*/
        // @property
        // @text setOvertempGraceInterval
        // @brief Set Temperature Thresholds
        // @param graceInterval: interval in secs? 
        virtual uint32_t SetOvertempGraceInterval(const int graceInterval /* @in */) = 0;

        /** Gets the current Temperature Thresholds.*/
        // @property
        // @text getOvertempGraceInterval
        // @brief Get Temperature Grace interval
        // @param graceInterval: interval in secs? 
        virtual uint32_t GetOvertempGraceInterval(int& graceInterval /* @out */) const = 0;

        /** Set Deep Sleep Timer for later wakeup */
        // @property
        // @text setDeepSleepTimer
        // @brief Set Deep sleep timer for timeOut period
        // @param timeOut: deep sleep timeout 
        virtual uint32_t SetDeepSleepTimer(const int timeOut /* @in */) = 0;

        /** Get Last Wakeup reason */
        // @property
        // @text getLastWakeupReason
        // @brief Get Last Wake up reason
        // @param wakeupReason: wake up reason 
        virtual uint32_t GetLastWakeupReason(WakeupReason &wakeupReason /* @out */) const = 0;

        /** Get Last Wakeup key code */
        // @property
        // @text getLastWakeupKeyCode
        // @brief Get the key code that can be used for wakeup
        // @param keycode: Key code for wakeup
        virtual uint32_t GetLastWakeupKeyCode(int &keycode /* @out */) const = 0;

        /** Perform Reboot */
        // @text reboot
        // @brief Reboot device
        virtual uint32_t Reboot(const string &rebootRequestor /* @in */, const string &rebootReasonCustom /* @in */, const string &rebootReasonOther /* @in */) = 0;

        /** Set Network Standby Mode */
        // @property
        // @text setNetworkStandbyMode
        // @brief Set the standby mode for Network
        // @param standbyMode: Network standby mode
        virtual uint32_t SetNetworkStandbyMode(const bool &standbyMode /* @in */) = 0;

        /** Get Network Standby Mode */
        // @text getNetworkStandbyMode
        // @brief Get the standby mode for Network
        // @param standbyMode: Network standby mode
        virtual uint32_t GetNetworkStandbyMode(bool &standbyMode /* @out */) = 0;

        /** Set Wakeup source configuration */
        // @text setWakeupSrcConfig
        // @brief Set the source configuration for device wakeup
        // @param powerMode: power mode
        // @param wakeSrcType: source type
        // @param config: config
        virtual uint32_t SetWakeupSrcConfig(const int &powerMode /* @in */, const int &wakeSrcType /* @in */, int config /* @in */ ) = 0;

        /** Get Wakeup source configuration */
        // @text getWakeupSrcConfig
        // @brief Get the source configuration for device wakeup
        // @param powerMode: power mode
        // @param srcType: source type
        // @param config: config
        virtual uint32_t GetWakeupSrcConfig(int &powerMode /* @out */, int &srcType /* @out */, int &config /* @out */) const = 0;

        /** Initiate System mode change */
        // @text setSystemMode
        // @brief System mode change
        // @param oldMode: old mode
        // @param newMode: new mode
        virtual uint32_t SetSystemMode(const SystemMode &currentMode /* @in */, const SystemMode &newMode /* @in */) const = 0;

        /** Get Power State before reboot */
        // @text getPowerStateBeforeReboot
        // @brief Get Power state before reboot
        // @param powerStateBeforeReboot: power state 
        virtual uint32_t GetPowerStateBeforeReboot(PowerState &powerStateBeforeReboot /* @out */) = 0;

};
} // namespace Exchange
} // namespace WPEFramework

