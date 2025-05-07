
#include <queue.h>

typedef struct _hctrl_t hctrl_t;

#define HC_FLAG_USE_DMA           ( 1 << 0 )


struct Struct_0x94
{
    struct _musb_transfer* Data_0; //0
};


struct _musb_transfer
{
    volatile uint32_t xfer_length; //0
    volatile uint32_t flags; //4
    uint32_t xfer_buffer_paddr; //8
    uint32_t xfer_buffer; //0xc
    volatile uint32_t Data_0x10; //0x10
    volatile uint32_t bytes_xfered; //0x14
    struct _musb_transfer_Inner_0x18* Data_0x18; //0x18
    struct _musb_transfer_Inner_0x18_Inner_8* Data_0x1c__; //0x1c
    int Data_0x20; //0x20
    volatile int Data_0x24; //0x24
    int status; //0x28
    SIMPLEQ_ENTRY(_musb_transfer) link; //0x2c
    struct Struct_0xa4* Data_0x30; //0x30
    /*struct Struct_10bab4*/iousb_transfer_t* Data_0x34; //0x34
    void (*Func_0x38)(struct _hctrl_t*, struct _musb_transfer*, uint32_t, int); //0x38
    void (*Func_0x3c)(struct _hctrl_t*, struct _musb_transfer*, uint32_t, int); //0x3c
    int fill_0x40; //0x40
    //0x44
};


struct Struct_0xa4
{
    struct Struct_0xa4* Data_0; //0
    struct Struct_0xa4* Data_4; //4
    struct _musb_transfer* Data_8__; //8
    struct Struct_0x94* Data_0xc; //12
    int Data_0x10; //0x10 = 16
    int Data_0x14; //0x14 = 20
    uint16_t mps; //0x18 = 24
    uint8_t transferType; //0x1a = 26
    uint8_t bData_0x1b; //0x1b = 27
    uint8_t bData_0x1c; //0x1c = 28
    uint8_t bData_0x1d; //0x1d = 29
    uint8_t bData_0x1e; //0x1e = 30
    uint8_t bData_0x1f; //0x1f = 31
    int Data_0x20; //0x20
    int Data_0x24; //0x24
    int num; //0x28
    int Data_0x2c; //0x2c
    struct fp_0x34_Inner_0x18_Inner_0x10* Data_0x30; //0x30
    struct Struct_112b08* Data_0x34; //0x34
    int Data_0x38; //0x38
    struct Struct_0xe4_Inner_0x1c* Data_0x3c; //0x3c
    //0x40 = 64
};


struct _hctrl_t {
    usb_hcd_t* uhc; //0
    pthread_mutex_t Data_4; //4
    pthread_mutex_t Data_0xc; //12
    int Data_0x14; //0x14
    uint32_t Data_0x18; //0x18 = 24
    int Data_0x1c; //0x1c
    int fill_0x20[3]; //0x20
    int Data_0x2c; //0x2c
    int num_dma; //0x30
    int dirq; //0x34
    int fill_0x38[2]; //0x38
    int Data_0x40; //0x40
    int Data_0x44; //0x44
    int edmairq; //0x48
    pthread_t Data_0x4c; //0x4c
    int Data_0x50; //0x50
    int Data_0x54; //0x54
    int Data_0x58; //0x58
    pthread_t Data_0x5c; //0x5c = 92
    int Data_0x60; //0x60
    int Data_0x64; //0x64
    int fill_0x68; //0x68
    int Data_0x6c; //0x6c
    int flags; //0x70
    int fill_0x74; //0x74
    int prio; //0x78 = 120
    int fill_0x7c[4]; //0x7c
    int Data_0x8c; //0x8c
    int num_ed; //0x90
    int num_td; //0x94
    uint32_t verbosity; //152 = 0x98
    int Data_0x9c; //0x9c
    int Data_0xa0; //0xa0
    char* fconfig_string; //0xa4
    int fill_0xa8; //0xa8
    SIMPLEQ_HEAD(, _musb_transfer) transfer_free_q; //0xac
    SIMPLEQ_HEAD(, _musb_transfer) transfer_complete_q; //0xb4
    void* transfer_mem; //0xbc
    void* Data_0xc0; //0xc0
    int fill_0xc4; //0xc4
    int Data_0xc8; //0xc8
    int Data_0xcc; //0xcc
    int Data_0xd0; //0xd0
    int Data_0xd4; //0xd4
    int* Data_0xd8; //0xd8
    void* Data_0xdc; //0xdc
    int fill_0xe0; //0xe0
    int Data_0xe4; //0xe4
    int fill_0xe8[3]; //0xe8
    void* args_copy; //0xf4
    int fill_0xf8; //0xf8
    void* Data_0xfc; //0xfc
    void (*Data_0x100)(); //0x100
    void (*Data_0x104)(); //0x104
    //0x108
};

