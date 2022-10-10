#pragma once

#include "Module.h"

namespace WPEFramework {
    namespace Exchange {

        struct EXTERNAL IAirplay : virtual public Core::IUnknown {
            enum { ID = ID_AIRPLAY};

            virtual ~IAirplay() { }

            enum state : uint16_t {
                PLAYING = 0x0001,
                STOPPED = 0x0002,
                SUSPENDING = 0x0004
            };

            struct EXTERNAL INotification : virtual public Core::IUnknown {
                  enum { ID = ID_AIRPLAY_NOTIFICATION };
                  virtual void StateChange(const IAirplay::state state) = 0;
                  virtual void Exit(const uint32_t exitCode) = 0;
                  virtual void Event(const string& eventName) = 0;
            };

            virtual void Register(IAirplay::INotification* airplay) = 0;
            virtual void Unregister(IAirplay::INotification* airplay) = 0;
            virtual void FactoryReset() = 0;
            virtual void SetVisible(bool visibility) = 0;
            virtual uint32_t SystemCommand(const string& command) = 0;
            virtual uint32_t StartApp(const string& parametersJson) = 0;
            virtual uint32_t StopApp(const string& parametersJson) = 0;
        };
    }
}
