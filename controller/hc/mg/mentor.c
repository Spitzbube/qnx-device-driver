
#include <stdint.h>


typedef struct _io_usb_otg_dll_entry io_usb_otg_dll_entry_t;

typedef struct _usb_controller_methods {
    /*usb_hcd_methods_t*/void       *hc_methods;
    /*usb_dcd_methods_t*/void       *dc_methods;
//              usb_rhub_methods_t      *rhub_methods;
    /*usb_otg_methods_t*/void       *otg_methods;
    void                            *reserved;
} usb_controller_methods;


struct _io_usb_otg_dll_entry {
    char* name; //0
    uint32_t version; //4
    uint32_t rsvd; //8
    uint32_t device_interest; //12
    uint32_t vid; //16
    uint32_t did; //20
    uint32_t ctrl_type; //24
    /*<48e0>*/int (*init)(void*, /*dispatch_t*/void*, /*iousb_self_t*/void*, char*); //28
    /*<490a>*/int (*shutdown)(void*); //32
    usb_controller_methods* usbctrl_methods; //36
}; //size: 40

#if 0 //TODO!!!
static iousb_self_t mentor_iousb_self;
#endif

static int mentor_init(void*, /*dispatch_t*/void*, /*iousb_self_t*/void*, char*);
static int mentor_shutdown(void*);
static usb_controller_methods mentor_usb_controller_methods; //TODO!!!


io_usb_otg_dll_entry_t io_usb_otg_dll_entry = {
    "devu-hcd-dm816x-mg.so",
    0,
    0,
    0xffffffff,
    0xffff,
    0xffff,
    1,
    mentor_init,
    mentor_shutdown,
    &mentor_usb_controller_methods
};



static int mentor_init(void* dll_hdl, /*dispatch_t*/void* dpp, /*iousb_self_t*/void* iousb_self, char* options)
{
#if 0 //TODO!!!
    mentor_iousb_self.self.hcd = iousb_self->self.hcd;
#endif
    return 0;
}


static int mentor_shutdown(void* dll_hdl)
{
    return 0;
}


static int mentor_controller_init(/*usb_hcd_t*/void* uhcd, uint32_t flags, char *args)
{

}


static int mentor_controller_start(/*usb_hcd_t*/void* uhcd)
{

}


static int mentor_controller_stop(/*usb_hcd_t*/void* uhcd)
{

}


static int mentor_controller_shutdown(/*usb_hcd_t*/void* uhcd)
{

}


static int mentor_set_bus_state(/*usb_hcd_t*/void* uhcd, uint32_t bus_state)
{

}


static int mentor_set_port_feature(/*usb_hcd_t*/void* uhcd, uint32_t port, uint32_t feature)
{

}


static int mentor_clear_port_feature(/*usb_hcd_t*/void* uhcd, uint32_t port, uint32_t feature)
{

}


static int mentor_check_port_status(/*usb_hcd_t*/void* uhcd, uint32_t* portno_status)
{

}


static int mentor_check_device_connected(/*usb_hcd_t*/void* uhcd, uint32_t port)
{

}


static int mentor_get_root_device_speed(/*usb_hcd_t*/void* uhcd, uint32_t port)
{

}



