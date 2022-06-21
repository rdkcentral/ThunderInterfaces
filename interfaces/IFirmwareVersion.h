#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IFirmwareVersion : virtual public Core::IUnknown {
        enum { ID = ID_FIRMWARE_VERSION };

        virtual ~IFirmwareVersion() override = default;

        virtual uint32_t Imagename(string& imagename /* @out */) const = 0;
        virtual uint32_t Sdk(string& sdk /* @out */) const = 0;
        virtual uint32_t Mediarite(string& mediarite /* @out */) const = 0;
        virtual uint32_t Yocto(string& yocto /* @out */) const = 0;
    };
}
}
