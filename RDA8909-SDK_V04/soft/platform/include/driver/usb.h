#ifndef _USB_H_
#define _USB_H_

#include <stdint.h>

// USB direction
// out: host => device
// in : device => host
#define USB_DIR_OUT 0
#define USB_DIR_IN  0x80

// USB request types, bRequestType[6:5] fields
#define USB_TYPE_MASK           (0x03 << 5)
#define USB_TYPE_STANDARD       (0x00 << 5)
#define USB_TYPE_CLASS          (0x01 << 5)
#define USB_TYPE_VENDOR         (0x02 << 5)
#define USB_TYPE_RESERVED       (0x03 << 5)

// USB request recipients, bRequestType[4:0] field.
#define USB_RECIP_MASK          0x1f
#define USB_RECIP_DEVICE        0x00
#define USB_RECIP_INTERFACE     0x01
#define USB_RECIP_ENDPOINT      0x02
#define USB_RECIP_OTHER         0x03
// From Wireless USB 1.0
#define USB_RECIP_PORT          0x04
#define USB_RECIP_RPIPE         0x05

struct usb_ctrl_request
{
    uint8_t bRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} __attribute__((packed));

typedef struct usb_ctrl_request usb_ctrl_request_t;


// Descriptor types ... USB 2.0 spec table 9.5
#define USB_DT_DEVICE               0x01
#define USB_DT_CONFIG               0x02
#define USB_DT_STRING               0x03
#define USB_DT_INTERFACE            0x04
#define USB_DT_ENDPOINT             0x05
#define USB_DT_DEVICE_QUALIFIER     0x06
#define USB_DT_OTHER_SPEED_CONFIG   0x07
#define USB_DT_INTERFACE_POWER      0x08
// these are from a minor usb 2.0 revision (ECN)
#define USB_DT_OTG                  0x09
#define USB_DT_DEBUG                0x0a
#define USB_DT_INTERFACE_ASSOCIATION    0x0b
// these are from the Wireless USB spec
#define USB_DT_SECURITY             0x0c
#define USB_DT_KEY                  0x0d
#define USB_DT_ENCRYPTION_TYPE      0x0e
#define USB_DT_BOS                  0x0f
#define USB_DT_DEVICE_CAPABILITY    0x10
#define USB_DT_WIRELESS_ENDPOINT_COMP   0x11
#define USB_DT_WIRE_ADAPTER         0x21
#define USB_DT_RPIPE                0x22
#define USB_DT_CS_RADIO_CONTROL     0x23
// From the T10 UAS specification
#define USB_DT_PIPE_USAGE           0x24

// Standard request, for the bRequest field of SETUP packet.
#define USB_REQ_GET_STATUS          0x00
#define USB_REQ_CLEAR_FEATURE       0x01
#define USB_REQ_SET_FEATURE         0x03
#define USB_REQ_SET_ADDRESS         0x05
#define USB_REQ_GET_DESCRIPTOR      0x06
#define USB_REQ_SET_DESCRIPTOR      0x07
#define USB_REQ_GET_CONFIGURATION   0x08
#define USB_REQ_SET_CONFIGURATION   0x09
#define USB_REQ_GET_INTERFACE       0x0A
#define USB_REQ_SET_INTERFACE       0x0B
#define USB_REQ_SYNCH_FRAME         0x0C
#define USB_REQ_SET_SEL             0x30
#define USB_REQ_SET_ISOCH_DELAY     0x31

struct usb_device_descriptor
{
    uint8_t bLength;
    uint8_t bDescriptorType;

    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
} __attribute__((packed));

#define USB_DT_DEVICE_SIZE  18


struct usb_config_descriptor
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterface;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;      /* max current in 2 mA units */
} __attribute__((packed));

#define USB_DT_CONFIG_SIZE  9


struct usb_interface_descriptor
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} __attribute__((packed));

#define USB_DT_INTERFACE_SIZE 9

struct usb_endpoint_descriptor
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;

    /* NOTE:  these two are _only_ in audio endpoints. */
    /* use USB_DT_ENDPOINT*_SIZE in bLength, not sizeof. */
#if 0
    uint8_t bRefresh;
    uint8_t bSynchAddress;
#endif
} __attribute__((packed));

#define USB_DT_ENDPOINT_SIZE        7
#define USB_DT_ENDPOINT_AUDIO_SIZE  9   /* Audio extension */


#define USB_EP_ADDRESS_MASK	0x0f    /* in bEndpointAddress */
#define USB_EP_DIR_MASK		0x80

#define USB_EP_TYPE_MASK		0x03    /* in bmAttributes */
#define USB_EP_TYPE_CONTROL	0
#define USB_EP_TYPE_ISOCHRONOUS	1
#define USB_EP_TYPE_BULK		2
#define USB_EP_TYPE_INTERRUPT	3


typedef struct usb_device_descriptor usb_device_desc_t;
typedef struct usb_config_descriptor usb_config_desc_t;
typedef struct usb_interface_descriptor usb_intf_desc_t;
typedef struct usb_endpoint_descriptor usb_ep_desc_t;


// USB_DT_INTERFACE_ASSOCIATION: groups interfaces
struct usb_interface_association_descriptor
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bFirstInterface;
    uint8_t bInterfaceCount;
    uint8_t bFunctionClass;
    uint8_t bFunctionSubClass;
    uint8_t bFunctionProtocol;
    uint8_t iFunction;
} __attribute__((packed));

typedef struct usb_interface_association_descriptor usb_interface_assoc_desc_t;

#endif // _USB_H_
