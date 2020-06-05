#ifndef DEVICE_UART_H
#define  DEVICE_UART_H

struct DEVICE_T;
typedef struct DEVICE_T DEVICE_T;

struct DEVICE_T
{
    void (*destroy)(DEVICE_T *th);
    bool (*open)(DEVICE_T *th);
    void (*close)(DEVICE_T *th);
    int (*write)(DEVICE_T *th, const uint8_t *data, unsigned length);
    int (*read)(DEVICE_T *th, uint8_t *data, unsigned size);
    void (*sleep)(DEVICE_T *th, bool wakeupEnabled);
    void (*wakeup)(DEVICE_T *th);
    bool (*isBaudSupported)(DEVICE_T *th, int baud);
    bool (*setFlowCtrl)(DEVICE_T *th, uint8_t rxfc, uint8_t txfc);
    void (*setFormat)(DEVICE_T *th, int baud);

    uint8_t devno;
//    struct AT_DISPATCH_T *recv;
};

typedef struct
{
    int id; // 1/UART1, 2/UART2
    int baud;
    enum DRV_UART_DATA_BITS dataBits;
    enum DRV_UART_STOP_BITS stopBits;
    enum DRV_UART_PARITY parity;
    bool ctsEnabled;
    bool rtsEnabled; // whether to output RTS
    bool autoBaudLC; // TRUE/at, FALSE/AT
} DEVICE_UART_CONFIG_T;

DEVICE_T *UartCreate(DEVICE_UART_CONFIG_T *cfg, uint8_t devno);
VOID uart_register_rx_cb(DEVICE_T *th, COS_CALLBACK_FUNC_T callfunc);

#endif
