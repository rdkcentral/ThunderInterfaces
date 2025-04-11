#pragma once
#include "Module.h"
#include "IDRM.h"

// @stubgen:include <com/IIteratorType.h>

namespace WPEFramework {
namespace Exchange {

    // @json
    struct EXTERNAL IRadioControl : virtual public Core::IUnknown {
        enum { ID = ID_RADIOCONTROL };

        struct RadioConfig {
            uint8_t radioIndex;
            string hwmode;
	    uint32_t channel;
	    bool acsEnable;
	    bool dfsEnable;
	    uint16_t guardInterval;
	    bool status;
        };

	struct RadioCap {
            uint8_t phyIndex;
            uint8_t noofBands;
	    string suppFreqBands;
            uint8_t maxnoofVaps;

        };

        using IRadioCapIterator = RPC::IIteratorType<RadioCap, ID_RADIOCONTROL_RADIOCAP_ITERATOR>;

        // @event
        struct EXTERNAL INotification : virtual public Core::IUnknown {
            enum { ID = ID_RADIOCONTROL_NOTIFICATION };
            ~INotification() override = default;

	    // events

        };
        ~IRadioControl() override = default;

        virtual uint32_t Register(IRadioControl::INotification* sink) = 0;
        virtual uint32_t Unregister(IRadioControl::INotification* sink) = 0;

        // @brief Provides available networks information
        virtual uint32_t DeviceCapabilities(string& country /* @out */, uint8_t& noofradios /* @out */, IRadioCapIterator*& radioCap /* @out */) const = 0;

	// @property
        // NOTE: Setting the config by indicating the radioindex.
        // @brief Provide config details for requested radioindex.
	virtual uint32_t Config(const uint8_t radioIndex /* @index */, RadioConfig& radioConfig /* @out */) const = 0;
	virtual uint32_t Config(const uint8_t radioIndex /* @index */,const RadioConfig& radioConfig) = 0;

        // @brief Change channel for provided radioIndex
	virtual uint32_t Channel(const uint8_t radioIndex,const uint32_t radioChannel) = 0;

        // @brief Change status for provided radioIndex
	virtual uint32_t Status(const uint8_t radioIndex, const bool status) = 0;

    };

} // namespace Exchange
} // namespace WPEFramework
