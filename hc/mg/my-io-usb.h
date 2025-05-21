
struct USB_Controller_Inner4;
struct UsbdiGlobals_Inner_0x178;


struct usbd_urb
{
    int Data_0; //4
    struct usbd_urb* Data_4; //4
    struct
    {
        int fill_0[3]; //0
        int Data_0xc; //0xc
        //???
    }* Data_8; //8
    struct
    {
        int Data_0; //0
        //???
    }* Data_0xc; //0xc
    struct
    {
        int fill_0[3]; //0
        int Data_0xc; //0xc
        int fill_0x10; //0x10
        int Data_0x14; //0x14
        //???
    }* Data_0x10; //0x10
    struct Struct_10bab4* Data_0x14; //0x14
    void* Data_0x18; //0x18
    void (*Data_0x1c)(struct usbd_urb*, struct usbd_pipe*, void*); //0x1c
    uint16_t wData_0x20; //0x20
    uint16_t wData_0x22; //0x22
    int Data_0x24; //0x24
    uint8_t bData_0x28; //0x28
    uint8_t bData_0x29; //0x29
    uint8_t wData_0x2a; //0x2a
    int Data_0x2c; //0x2c
    int Data_0x30; //0x30
    int Data_0x34; //0x34
    int Data_0x38; //0x38
    int Data_0x3c; //0x3c
    int Data_0x40; //0x40
    void* pData; //0x44
    int dwLength; //0x48
    int fill_0x4c; //0x4c
    int Data_0x50; //0x50
    int Data_0x54; //0x54
    uint16_t wValue; //0x58
    uint16_t wData_0x5a; //0x5a
    uint8_t request; //0x5c
    uint8_t request_type; //0x5d
    uint16_t wData_0x5e; //0x5e
    int Data_0x60; //0x60
    int Data_0x64; //0x64
    uint16_t wData_0x68; //0x68
    int fill_0x6c; //0x6c
    //0x70
};



struct Struct_10bab4 //_st_URB_TRANSFER = _iousb_transfer
{
    int Data_0___; //0
    int Data_4; //4
    int Data_8; //8
    int fill_0xc; //0xc
    int Data_0x10; //0x10
    int Data_0x14; //0x14
    uint32_t Data_0x18; //0x18
    uint32_t Data_0x1c; //0x1c
    int Data_0x20; //0x20
    int Data_0x24; //0x24
    int Data_0x28; //0x28
    void* pData; //0x2c
    uint32_t dwLength; //0x30
    int Data_0x34; //0x34
    int direction; //0x38
    int request; //0x3c //e.g. USB_GET_DESCRIPTOR
    int request_type; //0x40 //e.g. USB_TYPE_STANDARD
    int request_recipient; //0x44
    int value_high; //0x48
    int value_low; //0x4c
    uint32_t Data_0x50; //0x50
    int Data_0x54; //0x54
    void (*Func_0x58)(struct Struct_10bab4*); //0x58
    struct usbd_urb* Data_0x5c; //0x5c
    struct USB_Client* Data_0x60; //0x60
    //0x64
}; //iousb_transfer_t


struct USB_Controller_Inner4
{
    uint16_t DeviceId; //0
    uint16_t VendorId; //2
    int fill_4[4]; //4
    uint8_t bData_0x14[4]; //0x14
    int fill_0x18[6]; //0x18
    uint8_t bData_0x30; //0x30
    uint8_t bData_0x31; //0x31
    uint8_t bData_0x32; //0x32
    uint8_t bData_0x33; //0x33
    uint8_t bData_0x34; //0x34
    uint8_t bData_0x35; //0x35
    uint8_t bData_0x36; //0x36
    uint8_t bData_0x37; //0x37
    int fill_0x38[12]; //0x38
    unsigned long long Data_0x68; //0x68
    int fill_0x70[6]; //0x70
    unsigned long long Data_0x88; //0x88
    int fill_0x90[2]; //0x90
    uint8_t bData_0x98; //0x98
    uint8_t bData_0x99; //0x99
    uint8_t bData_0x9a; //0x9a
    uint8_t bData_0x9b; //0x9b
    int fill_0x9c[3]; //0x9c
    uint8_t bData_0xa8; //0xa8
    uint8_t bData_0xa9; //0xa9
    uint8_t bData_0xaa; //0xaa
    uint8_t bData_0xab; //0xab
    int fill_0xac[17]; //0xac
    //0xf0???
};

#ifndef USB_CONTROLLER_PRIV_T
#define USB_CONTROLLER_PRIV_T void
#endif


struct Struct_10467c
{
    struct Struct_10467c* Data_0; //0
    int Data_4; //4
    int fill_8[2]; //8
    int Data_0x10; //0x10
    int Data_0x14; //0x14
    int Data_0x18; //0x18
    int Data_0x1c; //0x1c
    void* Data_0x20; //0x20 = 32
    //???
};


struct Struct_1047a8
{
    int fill_0; //0
    struct Struct_10467c* Data_4; //4
    void* Data_8; //8
    //12
};


struct Struct_112b08 //TODO: struct UsbEndpoint = _st_ENDPOINT_DESCRIPTOR = _iousb_endpoint_t
{
    usbd_endpoint_descriptor_t endpoint_descriptor; //0
    int fill_8; //8
    struct Struct_0xa4* Data_0xc; //0xc
    int fill_0x10; //0x10
    int Data_0x14; //0x14
    struct 
    {
        int Data_0; //0
        //???
    }* Data_0x18; //0x18
    int Data_0x1c; //0x1c
    struct 
    {
        int Data_0; //0
        //???
    }* Data_0x20; //0x20
    int Data_0x24; //0x24
    int Data_0x28; //0x28
    struct Struct_10a110
    {
        struct Struct_10a110* next; //0
        void* Data_4; //4
        uint32_t Data_8; //8
        struct USB_Client* Data_0xc; //0xc
        void* Data_0x10; //0x10
        //0x14 = 20
    }* Data_0x2c; //0x2c
    pthread_mutex_t Data_0x30; //0x30
    pthread_cond_t Data_0x38; //0x38
    //0x40
}; //iousb_endpoint_t


struct USB_Controller_Inner_0x7c
{
    int device_address; //0
    int new_device_address; //4
    int fill_8; //8
    uint8_t bData_0xc; //0xc
    uint8_t bData_0xd; //0xd
    uint16_t wData_0xe; //0xe
    int Data_0x10; //0x10
    int Data_0x14; //0x14
    struct ArrayClass* Data_0x18; //0x18
    void* Data_0x1c; //0x1c
    int Data_0x20; //0x20
    int fill_0x24[2]; //0x24
    usbd_device_descriptor_t device_descriptor; //0x2c +0x12 = 0x3e
    struct Struct_112b08 Data_0x40; //0x40
#if 0
    pthread_mutex_t Data_0x70; //0x70
    pthread_cond_t Data_0x78; //0x78
#endif
    int fill_0x80; //0x80
    struct UsbConfiguration* Data_0x84; //0x84
    int Data_0x88; //0x88
    struct Struct_1047a8* Data_0x8c; //0x8c
    int fill_0x90; //0x90
    pthread_mutex_t Data_0x94; //0x94
    pthread_cond_t Data_0x9c; //0x9c
    int fill_0xa4; //0xa4
    int Data_0xa8; //0xa8
    //0xac
};


struct USB_Controller // = st_USB_Hc
{
    char* cname; //0
    struct USB_Controller_Inner4* pci_inf; //4
    int cindex; //8
    int chid; //12
    int coid; //16
    pthread_t tid; //0x14
    void* pdev; //0x18
    int fill_0x1c; //0x1c
    int usb_iid; //0x20
    pthread_mutex_t usb_rwlock; //0x24
    int fill_0x2c[12]; //0x2c
    int AvailableBandwidth; //0x5c
    int MaxTransferSize; //0x60
    int MaxUnalignedTransferSize; //0x64
    int buff_alignment_mask; //0x68
    uint32_t capabilities; //0x6c
    int ctrl_retry; //0x70
    int fill_0x74; //0x74
    struct USB_Controller_Inner_0x7c** ArrayUsbDevices; //0x78
    struct USB_Controller_Inner_0x7c* UsbDevices; //0x7c
    struct UsbdiGlobals_Inner_0x178* dll_hdl; //0x80
    USB_CONTROLLER_PRIV_T* hc_data; //0x84
    hc_methods_t* hc_methods; //0x88
    hc_pipe_methods_t* ctrl_pipe_methods; //0x8c
    hc_pipe_methods_t* int_pipe_methods; //0x90
    hc_pipe_methods_t* bulk_pipe_methods; //0x94
    hc_pipe_methods_t* isoch_pipe_methods; //0x98
    //0x9c
};


