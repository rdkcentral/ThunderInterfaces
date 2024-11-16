#pragma once
 
#include "Module.h"

// @stubgen:include <com/IIteratorType.h>
 
namespace Thunder {

namespace Exchange {

// @json
struct EXTERNAL IUSBHub : virtual public Core::IUnknown {

  enum { ID = ID_USB_HUB };

  ~IUSBHub() override = default;

  enum Speed : uint8_t {
      SPEED_LOW = 1,
      SPEED_FULL = 2,
      SPEED_HIGH = 3,
      SPEED_SUPER = 4
  };

  enum Flags : uint8_t {
      FLAGS_AVAILABLE = 1,
      FLAGS_SWITCHABLE = 2
  };

  enum Status : uint8_t {
      STATUS_ACTIVE = 0x01,
      STATUS_NO_DEVICE_CONNECTED = 0x02,
      STATUS_SELF_POWERED = 0x03
  };

  struct ProductMetadata {
      uint8_t languageId    /* @brief language id present on the device */;
      string  serialNumber  /* @brief unicode string representing the serial number of the device */;
      string  manufacturer  /* @brief unicode string representing the manufacturer of the device */;
      string  product       /* @brief unicode string representing the product */;
  };

  struct DeviceMetadata { 
    string          deviceName     /* @brief Name of the USB device */;
    uint32_t        parentId       /* @brief Parent Node ID of the device */;
    Status          status         /* @brief current device status */;
    uint8_t         deviceLevel    /* @brief device level */;
    uint8_t         portNumber     /* @brief port number of USB on which the device is attached */;
    uint8_t         protocol       /* @brief Protocol supported by the device */;
    Speed           busSpeed       /* @brief Speed of the device */;
    string          serialNumber   /* @brief Serial number of the device */;
    Flags           flags          /* @brief Flags of the device */;
    uint16_t        vendorId       /* @brief the vendor Id assigned to this device */;
    uint16_t        productId      /* @brief the product Id assigned to this device */;
    uint8_t         deviceClass    /* @brief USB class of the device as per USB specificiation */ ;
    uint8_t         deviceSubclass /* @brief USB sub class of the device as per USB specificiation */;
    string          devicePath     /* @brief the path to be used for the USB device ex: /dev/sdX */;
    uint32_t        features       /* @brief Features supported by the device - reserved */;
    uint8_t         numLanguageIds /* @brief number of language ids present on the device */;
    ProductMetadata productInfo1;
    ProductMetadata productInfo2;
    ProductMetadata productInfo3;
    ProductMetadata productInfo4;
  };

  using IStringIterator = RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>;

  // @event 
  struct EXTERNAL INotification : virtual public Core::IUnknown {
    enum { ID = ID_USB_HUB_NOTIFICATION };

    ~INotification() override = default;

    // @brief Device Plugged in on the bus notification
    // @param device: USB information of the plugged in device
    virtual void Announce(const DeviceMetadata& device) = 0;

    // @brief Device removed from the bus notification
    // @param device: USB information of the plugged in device
    virtual void Revoke(const DeviceMetadata& device) = 0;
  };

  struct EXTERNAL IDevice : virtual public Core::IUnknown {

      enum { ID = ID_USB_DEVICE };

      ~IDevice() override = default;
  };

  /** Register notification interface */
  virtual Core::hresult Register(INotification *notification) = 0;

  /** Unregister notification interface */
  virtual Core::hresult Unregister(const INotification *notification) = 0;
  
  // @brief Get a string array defning al devices hooked up to this hub.
  // @param iterator : List of USB devices (deviceName).
  virtual Core::hresult Devices(IStringIterator*& iterator /* @out */) const = 0;

  // @brief Get a string array defning all devices hooked up to this hub cmpliant to the given vendorId/ProductId.
  // @param iterator : List of USB devices (deviceName).
  virtual Core::hresult Devices(const uint16_t vendorId, const uint16_t productId, IStringIterator*& iterator /* @out */) const = 0;

  /** Gets the device metadata of a connected USB Devices.*/
  // @brief Get the metadata information about the name passed in the paramater.
  // @param deviceName: Name of the device
  // @param device: all the metadata of the requested deviceName device.
  virtual Core::hresult Device(const string& deviceName, struct DeviceMetadata& device /* @out */ ) const = 0;

  // @brief Acquire the respective driver for the device */
  // @param deviceName: Name of the device
  // @param device: interface to access the device.
  /* @json:omit */
  virtual Core::hresult Acquire(const string& deviceName /* @in */, IDevice*& device /* @out */ ) const = 0;

  // @brief Relinquish the respective driver for the device */
  // @param device: Device to be released
  /* @json:omit */
  virtual Core::hresult Relinquish(const IDevice*& device /* @out */) const = 0;
};
 
} // namespace Exchange

} // namespace Thunder

