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

namespace WPEFramework
{
    namespace Exchange
    {
        // @json
        struct EXTERNAL IPowerManager : virtual public Core::IUnknown {
        enum { ID = ID_POWER_MANAGER };

        enum PowerState : uint8_t {
            POWER_STATE_OFF                = 0  /* @text Power State is off */,
            POWER_STATE_STANDBY            = 1  /* @text Power State is Standby */,
            POWER_STATE_ON                 = 2  /* @text Power State is On */,
            POWER_STATE_STANDBY_LIGHT_SLEEP  = 3  /* @text Power State is Light Sleep Standby */,
            POWER_STATE_STANDBY_DEEP_SLEEP   = 4  /* @text Power State is Deep Sleep Standby */,
            POWER_STATE_UNKNOWN   = 5  /* @text Power State is unknown */
        };

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown
        {
            enum { ID = ID_POWER_MANAGER_NOTIFICATION };

            // @brief Power mode changed
            // @text OnPowerModeChanged
            // @alt onPowerModeChanged
            // @param currentState: Current Power State
            // @param newState: New Power State
            virtual void onPowerModeChanged(const PowerState &currentState, const PowerState &newState) = 0;
            /** The Power Mode is going to change - sent before actual power mode change. */

            // @brief Power mode Pre-change event
            // @text OnPowerModePreChange
            // @alt onPowerModePreChange
            // @param currentState: Current Power State
            // @param newState: Changing power state to this New Power State
            virtual void onPowerModePreChange(const PowerState &currentState, const PowerState &newState) = 0;

            // @brief Deep sleep timeout event
            // @text OnDeepSleepTimeout
            // @alt onDeepSleepTimeout
            // @param wakeupTimeout: Deep sleep wakeup timeout in seconds
            virtual void onDeepSleepTimeout(const int &wakeupTimeout) = 0;

            // @brief Network Standby Mode changed event - only on XIone
            // @text OnNetworkStandbyModeChanged
            // @alt onNetworkStandbyModeChanged
            // @param enabled: network standby enabled or disabled
            virtual void onNetworkStandbyModeChanged(const bool &enabled) = 0;

            // @brief Thermal Mode changed event
            // @text OnThermalModeChanged
            // @alt onThermalModeChanged
            // @param currentThermalLevel: current thermal level
            // @param newThermalLevel: new thermal level
            // @param currentTemperature: current temperature
            virtual void onThermalModeChanged(const int &currentThermalLevel, const int &newThermalLevel, const float &currentTemperature) = 0;

            // @brief Reboot begin event
            // @text OnRebootBegin
            // @alt onRebootBegin
            // @param rebootReasonCustom: Reboot reason custom
            // @param rebootReasonOther: Reboot reason other
            // @param rebootRequestor: Reboot requested by 
            virtual void onRebootBegin(const string &rebootReasonCustom, const string &rebootReasonOther, const string &rebootRequestor) = 0;

        };
 
        virtual uint32_t Register(Exchange::IPowerManager::INotification* notification /* @in */) = 0;
        virtual uint32_t Unregister(Exchange::IPowerManager::INotification* notification /* @in */) = 0;

        enum ThermalTemperature : uint8_t {
            THERMAL_TEMPERATURE_NORMAL     = 0  /* @text Normal Thermal Temperature */,
            THERMAL_TEMPERATURE_HIGH       = 1  /* @text High Thermal Temperature */,
            THERMAL_TEMPERATURE_CRITICAL   = 2  /* @text Critial Thermal Temperature */
        };

        enum WakeupSrcType : uint8_t {
            WAKEUP_SRC_VOICE = 0            /* @text Wake up Source is Voice */,
            WAKEUP_SRC_PRESENCEDETECTED = 1 /* @text Wake up Source is Presence */,
            WAKEUP_SRC_BLUETOOTH = 2        /* @text Wake up Source is Bluetooth */,
            WAKEUP_SRC_RF4CE = 3            /* @text Wake up Source is RF4CE remote */,
            WAKEUP_SRC_WIFI = 4             /* @text Wake up Source is Wifi */,
            WAKEUP_SRC_IR = 5               /* @text Wake up Source is IR */,
            WAKEUP_SRC_POWERKEY = 6         /* @text Wake up Source is Power Key */,
            WAKEUP_SRC_TIMER = 7            /* @text Wake up Source is Timer */,
            WAKEUP_SRC_CEC = 8              /* @text Wake up Source is CEC */,
            WAKEUP_SRC_LAN = 9              /* @text Wake up Source is LAN */
        };

        enum WakeupReason : uint8_t {
            WAKEUP_REASON_IR = 0              /* @text Wake up reason is IR key */,
            WAKEUP_REASON_BLUETOOTH = 1       /* @text Wake up reason is Bluetooth remote */,
            WAKEUP_REASON_RF4CE = 2           /* @text Wake up reason is RF4CE remote */,
            WAKEUP_REASON_GPIO = 3            /* @text Wake up reason is GPIO */,
            WAKEUP_REASON_LAN = 4             /* @text Wake up reason is LAN */,
            WAKEUP_REASON_WIFI = 5            /* @text Wake up reason is Wifi */,
            WAKEUP_REASON_TIMER = 6           /* @text Wake up reason is Timer */,
            WAKEUP_REASON_FRONTPANEL = 7      /* @text Wake up reason is Front Panel Key */,
            WAKEUP_REASON_WATCHDOG = 8        /* @text Wake up reason is Watch dog timer firing */,
            WAKEUP_REASON_SOFTWARERESET = 9   /* @text Wake up reason is Software reset */,
            WAKEUP_REASON_THERMALRESET = 10   /* @text Wake up reason is Thermal reset */,
            WAKEUP_REASON_WARMRESET = 11      /* @text Wake up reason is Warm reset */,
            WAKEUP_REASON_COLDBOOT = 12       /* @text Wake up reason is ColdBoot */,
            WAKEUP_REASON_STRAUTHFAIL = 13    /* @text Wake up reason is Auth failure */,
            WAKEUP_REASON_CEC = 14            /* @text Wake up reason is CEC */, 
            WAKEUP_REASON_PRESENCE = 15       /* @text Wake up reason is Presence */,
            WAKEUP_REASON_VOICE = 16 
        };

        enum SystemMode : uint8_t {
            SYSTEM_MODE_NORMAL      = 0  /* @text System Mode normal */,
            SYSTEM_MODE_EAS         = 1  /* @text EAS System mode */,
            SYSTEM_MODE_WAREHOUSE   = 2  /* @text Warehouse mode */
        };

        /** Sets Power State . */
        // @text SetPowerState
        // @alt setPowerState
        // @brief Set Power State
        // @param powerState: Set power to this state
        // @param reason: Reason for moving to the power state
        virtual uint32_t setPowerState(const PowerState &powerState,const string &reason) = 0;

        /** Gets the Power State.*/
        // @property
        // @text GetPowerState
        // @alt getPowerState
        // @brief Get Power State
        // @param powerState: Get current power state
        virtual uint32_t getPowerState(PowerState &powerState /* @out */) const = 0;

        /** Gets the current Thermal state.*/
        // @property
        // @text GetThermalState
        // @alt getThermalState
        // @brief Get Current Thermal State (temperature)
        // @param currentTemperature: current temperature
        virtual uint32_t getThermalState(float& currentTemperature /* @out */) const = 0;

        /** Sets the Temperature Thresholds.*/
        // @text SetTemperatureThresholds
        // @alt setTemperatureThresholds
        // @brief Set Temperature Thresholds
        // @param high: high threshold 
        // @param critical : critical threshold 
        virtual uint32_t setTemperatureThresholds(float high /* @in */, float critical /* @in */) = 0;

        /** Gets the current Temperature Thresholds.*/
        // @text GetTemperatureThresholds
        // @alt getTemperatureThresholds
        // @brief Get Temperature Thresholds
        // @param high: high threshold 
        // @param critical : critical threshold 
        virtual uint32_t getTemperatureThresholds(float& high /* @out */, float& critical /* @out */) const = 0;

        /** Sets the current Temperature Grace interval.*/
        // @property
        // @text SetOvertempGraceInterval
        // @alt setOvertempGraceInterval
        // @brief Set Temperature Thresholds
        // @param graceInterval: interval in secs? 
        virtual uint32_t setOvertempGraceInterval(const int graceInterval /* @in */) = 0;

        /** Gets the current Temperature Thresholds.*/
        // @property
        // @text GetOvertempGraceInterval
        // @alt getOvertempGraceInterval
        // @brief Get Temperature Grace interval
        // @param graceInterval: interval in secs? 
        virtual uint32_t getOvertempGraceInterval(int& graceInterval /* @out */) const = 0;

        /** Set Deep Sleep Timer for later wakeup */
        // @property
        // @text SetDeepSleepTimer
        // @alt setDeepSleepTimer
        // @brief Set Deep sleep timer for timeOut period
        // @param timeOut: deep sleep timeout 
        virtual uint32_t setDeepSleepTimer(const int timeOut /* @in */) = 0;

        /** Get Last Wakeup reason */
        // @property
        // @text GetLastWakeupReason
        // @alt getLastWakeupReason
        // @brief Get Last Wake up reason
        // @param wakeupReason: wake up reason 
        virtual uint32_t getLastWakeupReason(int &wakeupReason /* @out */) const = 0;

        /** Get Last Wakeup key code */
        // @property
        // @text GetLastWakeupKeyCode
        // @alt getLastWakeupKeyCode
        // @brief Get the key code that can be used for wakeup
        // @param keycode: Key code for wakeup
        virtual uint32_t getLastWakeupKeyCode(int &keycode /* @out */) const = 0;

        /** Perform Reboot */
        // @property
        // @text Reboot
        // @alt reboot
        // @brief Reboot device
        virtual uint32_t reboot(const string &rebootReason /* @in */ ) = 0;

        /** Set Network Standby Mode */
        // @property
        // @text SetNetworkStandbyMode
        // @alt setNetworkStandbyMode
        // @brief Set the standby mode for Network
        // @param standbyMode: Network standby mode
        virtual uint32_t setNetworkStandbyMode(const bool &standbyMode /* @in */) = 0;

        /** Get Network Standby Mode */
        // @text GetNetworkStandbyMode
        // @alt getNetworkStandbyMode
        // @brief Get the standby mode for Network
        // @param standbyMode: Network standby mode
        virtual uint32_t getNetworkStandbyMode(bool &standbyMode /* @out */) = 0;

        /** Set Wakeup source configuration */
        // @text SetWakeupSrcConfig
        // @alt setWakeupSrcConfig
        // @brief Set the source configuration for device wakeup
        // @param powerMode: power mode
        // @param wakeSrcType: source type
        // @param config: config
        virtual uint32_t setWakeupSrcConfig(const int &powerMode /* @in */, const int &wakeSrcType /* @in */, int config /* @in */ ) = 0;

        /** Get Wakeup source configuration */
        // @text GetWakeupSrcConfig
        // @alt getWakeupSrcConfig
        // @brief Get the source configuration for device wakeup
        // @param powerMode: power mode
        // @param srcType: source type
        // @param config: config
        virtual uint32_t getWakeupSrcConfig(int &powerMode /* @out */, int &srcType /* @out */, int &config /* @out */) const = 0;

        /** Initiate System mode change */
        // @text SystemModeChange
        // @alt systemModeChange
        // @brief System mode change
        // @param oldMode: old mode
        // @param newMode: new mode
        virtual uint32_t systemModeChange(const SystemMode &oldMode /* @in */, const SystemMode &newMode /* @in */) const = 0;

        /** Get Power State before reboot */
        // @text GetPowerStateBeforeReboot
        // @alt getPowerStateBeforeReboot
        // @brief Get Power state before reboot
        // @param powerStateBeforeReboot: power state 
        virtual uint32_t getPowerStateBeforeReboot(int &powerStateBeforeReboot /* @out */) = 0;

};
} // namespace Exchange
} // namespace WPEFramework


/* JPowerManager.h will be generated with auto generated tool and it is calling _impl_(object of IPowerManager.h) methods
   starting with Capital letters,which will cause compilation error as IPowerManager interface method names are starting with
   small letters.
   To avoid the compilation error we have added below macros, which will replace method names as below in JPowerManager.h
   Eg: Setxxxx replaced with setxxxx */


/* Event names macros*/
#define OnPowerModeChanged onPowerModeChanged
#define OnPowerModePreChange onPowerModePreChange
#define OnNetworkStandbyModeChanged onNetworkStandbyModeChanged
#define OnThermalModeChanged onThermalModeChanged
#define OnRebootBegin onRebootBegin
#define OnDeepSleepTimeout onDeepSleepTimeout


/* method names macros */
#define SetPowerState setPowerState
#define GetPowerState getPowerState
#define GetThermalState getThermalState
#define SetTemperatureThresholds setTemperatureThresholds
#define GetTemperatureThresholds getTemperatureThresholds
#define SetOvertempGraceInterval setOvertempGraceInterval
#define GetOvertempGraceInterval getOvertempGraceInterval
#define SetDeepSleepTimer setDeepSleepTimer
#define GetLastWakeupReason getLastWakeupReason
#define GetLastWakeupKeyCode getLastWakeupKeyCode
#define Reboot reboot
#define SetNetworkStandbyMode setNetworkStandbyMode
#define GetNetworkStandbyMode getNetworkStandbyMode
#define SetWakeupSrcConfig setWakeupSrcConfig
#define GetWakeupSrcConfig getWakeupSrcConfig
#define SystemModeChange systemModeChange
#define GetPowerStateBeforeReboot getPowerStateBeforeReboot

