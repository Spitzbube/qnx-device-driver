
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/slog.h>
#include "pci.h"
#include <sys/io-usb-otg.h>
#include "mentor.h"


/*static*/ iousb_self_t mentor_iousb_self;

static int mentor_init(void*, dispatch_t*, iousb_self_t*, char*);
static int mentor_shutdown(void*);

static int mentor_controller_init(usb_hcd_t*, uint32_t, char*);
static int mentor_controller_start(usb_hcd_t*);
static int mentor_controller_stop(usb_hcd_t*);
static int mentor_controller_shutdown(usb_hcd_t*);
static int mentor_set_bus_state(usb_hcd_t*, uint32_t);
static int mentor_set_port_feature(usb_hcd_t*, uint32_t, uint32_t);
static int mentor_clear_port_feature(usb_hcd_t*, uint32_t, uint32_t);
static int mentor_check_port_status(usb_hcd_t*, uint32_t*);
static int mentor_check_device_connected(usb_hcd_t*, uint32_t);
static int mentor_get_root_device_speed(usb_hcd_t*, uint32_t);
static int mentor_get_timer_from_controller(usb_hcd_t*);

static int mentor_ctrl_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
static int mentor_ctrl_endpoint_disable(void*, iousb_endpoint_t*);
static int mentor_ctrl_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);
static int mentor_ctrl_transfer_abort(void*, iousb_transfer_t*, iousb_endpoint_t*);

static int mentor_isoch_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
static int mentor_isoch_endpoint_disable(void*, iousb_endpoint_t*);
static int mentor_isoch_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);
static int mentor_transfer_abort(void*, iousb_transfer_t*, iousb_endpoint_t*);

static int mentor_bulk_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
static int mentor_bulk_endpoint_disable(void*, iousb_endpoint_t*);
static int mentor_bulk_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);

static int mentor_int_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
static int mentor_int_endpoint_disable(void*, iousb_endpoint_t*);
static int mentor_int_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);

static iousb_pipe_methods_t mentor_ctrl_pipe_methods =
{
    mentor_ctrl_endpoint_enable,
    mentor_ctrl_endpoint_disable,
    mentor_ctrl_transfer,
    mentor_ctrl_transfer_abort,
    NULL //reserved
};

static iousb_pipe_methods_t mentor_isoch_pipe_methods =
{
    mentor_isoch_endpoint_enable,
    mentor_isoch_endpoint_disable,
    mentor_isoch_transfer,
    mentor_transfer_abort,
    NULL //reserved
};

static iousb_pipe_methods_t mentor_bulk_pipe_methods =
{
    mentor_bulk_endpoint_enable,
    mentor_bulk_endpoint_disable,
    mentor_bulk_transfer,
    mentor_transfer_abort,
    NULL //reserved
};

static iousb_pipe_methods_t mentor_int_pipe_methods =
{
    mentor_int_endpoint_enable,
    mentor_int_endpoint_disable,
    mentor_int_transfer,
    mentor_transfer_abort,
    NULL //reserved
};

static iousb_ep_pipe_methods_t mentor_ep_pipe_methods =
{
    &mentor_ctrl_pipe_methods,
    &mentor_isoch_pipe_methods,
    &mentor_bulk_pipe_methods,
    &mentor_int_pipe_methods,
};

static usb_hcd_methods_t mentor_controller_methods = 
{
    18,
    mentor_controller_init,
    mentor_controller_start,
    mentor_controller_stop,
    mentor_controller_shutdown,
    mentor_set_bus_state,
    NULL, //hc_dma_memory_malloc
    NULL, //hc_dma_memory_free
    NULL, //hc_interrupt
    mentor_set_port_feature,
    mentor_clear_port_feature,
    mentor_check_port_status,
    mentor_check_device_connected,
    mentor_get_root_device_speed,
    mentor_get_timer_from_controller,
    &mentor_ep_pipe_methods
};

static usb_controller_methods mentor_usb_controller_methods = 
{
    &mentor_controller_methods,
    NULL, NULL, NULL
};

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


/* complete */
int mentor_slogf(hctrl_t* hc, 
    int opcode, int severity, int verbosity,
    const char* fmt, ...)
{
    int res;

    if ((hc != NULL) && (hc->verbosity < verbosity))
    {
        return 0;
    }

    va_list arglist;

    va_start(arglist, fmt);

    res = vslogf(opcode, severity, fmt, arglist);

    va_end( arglist );

    return res;
}


/* complete */
static int mentor_init(void* dll_hdl, dispatch_t* dpp, iousb_self_t* iousb_self, char* options)
{
    mentor_iousb_self.self.hcd = iousb_self->self.hcd;

    return 0;
}


/* complete */
static int mentor_shutdown(void* dll_hdl)
{
    return 0;
}


/* todo */
static void* mentor_interrupt_thread(void* p)
{

}


/* todo */
int MENTOR_AllocateTD(hctrl_t* hc)
{

}


/* todo */
int MENTOR_AllocateED(hctrl_t* hc)
{

}


static int mentor_controller_start(usb_hcd_t* uhcd/*r7*/)
{
    int res; //r5
    pthread_mutexattr_t mattr; //sp_0x18;

    hctrl_t* hc/*r4*/ = uhcd->hc_data;

    pthread_mutexattr_init(&mattr);
    pthread_mutexattr_setrecursive(&mattr, 2);
    
    res = pthread_mutex_init(&hc->Data_4/*sl*/, &mattr);
    if (res != 0)
    {
        //74d8
        mentor_slogf(hc, 12, 2, 0, 
            "%s : %s - Unable to initialize mutex",
            "devu-hcd-dm816x-mg.so", 
            "mentor_controller_start");

        return res;
    }
    //74fe
    res = pthread_mutex_init(&hc->Data_0xc/*fp*/, &mattr);
    if (res != 0)
    {
        //750e
        mentor_slogf(hc, 12, 2, 0/*r8*/, 
            "%s : %s - Unable to initialize mutex",
            "devu-hcd-dm816x-mg.so", 
            "mentor_controller_start");
        //->7818
        goto error_7818;
        //return res;
    }
    //7532
    hc->Data_0x14 = mmap_device_memory(NULL, 0x2000, 
        0xb00, 0x10001, 
        uhcd->hw_ctrl.pci_inf->CpuBaseAddress[0]);

    if (hc->Data_0x14 == -1)
    {
        res = errno;
        //->7812
        goto error_7812;
    }
    //755a
    hc->Data_0x18 = (uint32_t) uhcd->hw_ctrl.pci_inf->CpuBaseAddress[0];

    hctrl_t* r6 = uhcd->hc_data;
    pthread_attr_t sp_0x60;
    struct sched_param sp_0x176;

    int r5;
    r6->Data_0x60 = ChannelCreate(8);
    if (r6->Data_0x60 < 0)
    {
        //7570
        mentor_slogf(r6, 12, 2, 0/*r5*/, 
            "%s : %s - Unable to create channel",
            "devu-hcd-dm816x-mg.so", 
            "mentor_create_completion_thread");
        r5 = r6->Data_0x60;
        //->763e: TODO!!!
    }
    //7596
    r6->Data_0x64 = ConnectAttach(0, 0, r6->Data_0x60, 
        0x40000000, 0);
    if (r6->Data_0x64 < 0)
    {
        //75aa
        mentor_slogf(r6, 12, 2, 0/*r5*/, 
            "%s : %s - Unable to connect to channel",
            "devu-hcd-dm816x-mg.so", 
            "mentor_create_completion_thread");
        r5 = r6->Data_0x64;
        //->7638:
        goto error_7638;
    }
    //75d0
    pthread_attr_init(&sp_0x60/*r5*/);
    pthread_attr_setschedpolicy(&sp_0x60/*r5*/, 2);
    sp_0x176.sched_priority = r6->prio;
    pthread_attr_setschedparam(&sp_0x60/*r5*/, &sp_0x176);
    pthread_attr_setinheritsched(&sp_0x60/*r5*/, 2);

    r5 = pthread_create(&r6->Data_0x5c, NULL, 
        mentor_interrupt_thread, uhcd/*r7*/);
    if (r5 != 0)
    {
        //7610
        mentor_slogf(r6, 12, 2, 0/*r8*/, 
            "%s : %s - Unable to create interrupt thread",
            "devu-hcd-dm816x-mg.so", 
            "mentor_create_completion_thread");

        ConnectDetach(r6->Data_0x64);
error_7638:
        ChannelDestroy(r6->Data_0x60);
error_763e:
            ;
    }
    //763e
    if (res != 0)
    {
        //->7808
        goto error_7808;
    }
    //7644
    res = MENTOR_AllocateTD(hc);
    if (res != 0)
    {
        //->77fc
        goto error_77fc;
    }
    //7652
    res = MENTOR_AllocateED(hc);
    if (res != 0)
    {
        //->77f6
        goto error_77f6;
    }
    //7660
    
    return res;

error_77f6:
    MENTOR_FreeTD(hc);

error_77fc:
    InterruptDetach(hc->Data_0x6c);

error_7808:
    munmap_device_memory(hc->Data_0x14, 0x2000);

error_7812:
    pthread_mutex_destroy(&hc->Data_0xc/*fp*/);

error_7818:
    pthread_mutex_destroy(&hc->Data_4/*sl*/);

    return res;
}


static int mentor_controller_stop(usb_hcd_t* uhcd)
{

}


/* complete */
static int mentor_controller_shutdown(usb_hcd_t* uhcd)
{
    hctrl_t* hc = uhcd->hc_data;

    if (hc->args_copy != NULL)
    {
        free(hc->args_copy);
    }

    free(hc);

    return 0;
}


static int mentor_set_bus_state(usb_hcd_t* uhcd, uint32_t bus_state)
{

}


static int mentor_set_port_feature(usb_hcd_t* uhcd, uint32_t port, uint32_t feature)
{

}


static int mentor_clear_port_feature(usb_hcd_t* uhcd, uint32_t port, uint32_t feature)
{

}


static int mentor_check_port_status(usb_hcd_t* uhcd, uint32_t* portno_status)
{

}


static int mentor_check_device_connected(usb_hcd_t* uhcd, uint32_t port)
{

}


static int mentor_get_root_device_speed(usb_hcd_t* uhcd, uint32_t port)
{

}




































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































static void process_args(hctrl_t* hc, char* args)
{
    static char* const mentor_opts[] = {
        "verbose", //0
        "num_ed",
        "num_td",
        "prio",
        "dirq",
        "nodma",
        "fconfig", //6
        "dma_reserve",
        "num_dma", //8
        "isoc_pio",
        "no_cfg_pmic",
        "ctrl_noping",
        "inherit_cfg", //12
        "out_rndis",
        "edma", //14
        "edmachannel",
        "edmairq", //16
        "in_rndis",
        "swtoggle", //18
        NULL
    };            
    
    char* value; //sp_0x30;
    int opt;

    if (args[0] != 0)
    {
        while ((args != NULL) && (args[0] != 0))
        {
            //51c4
            opt = getsubopt(&args, mentor_opts, &value);
            switch (opt)
            {
                case 0:
                    //5208: "verbose"
                    if (value != NULL)
                    {
                        hc->verbosity = strtol(value, 0, 10);
                    }
                    else
                    {
                        hc->verbosity = 5;
                    }
                    //->51cc
                    break;

                case 1:
                    //5222: "num_ed"
                    if (value != NULL)
                    {
                        hc->num_ed = (strtol(value, 0, 10) > 63)? 
                            strtol(value, 0, 10): 64;
                    }
                    //->51cc
                    break;

                case 2:
                    //5248: "num_td"
                    if (value != NULL)
                    {
                        hc->num_td = strtol(value, 0, 10);
                    }
                    //->51cc
                    break;

                case 3:
                    //525c: "prio"
                    if (value != NULL)
                    {
                        hc->prio = strtol(value, 0, 10);
                    }
                    //->51cc
                    break;

                case 4:
                    //526e: "dirq"
                    if (value != NULL)
                    {
                        hc->dirq = strtol(value, 0, 10);
                    }
                    //->51cc
                    break;

                case 6:
                    //5280: "fconfig"
                    if (value != NULL)
                    {
                        hc->fconfig_string = strdup(value);                
                    }
                    //->51cc
                    break;
                    
                case 7:
                    //5290: "dma_reserve"
                    hc->flags &= ~(1 << 2);
                    break;

                case 8:
                    //529a: "num_dma"
                    if (value != NULL)
                    {
                        hc->num_dma = strtol(value, 0, 10);
                        if (hc->num_dma != 0)
                        {
                            break;
                        }
                    }
                    //Fall through
                    
                case 5:
                    //52AC: "nodma"
                    hc->flags &= ~HC_FLAG_USE_DMA;
                    break;

                case 9:
                    //52b4: "isoc_pio"
                    hc->flags |= (1 << 5);
                    break;

                case 10:
                    //52bc: "no_cfg_pmic"
                    hc->flags &= ~(1 << 6);
                    break;

                case 11:
                    //52c4: "ctrl_noping"
                    hc->flags |= (1 << 7);
                    break;

                case 12:
                    //52cc: "inherit_cfg"
                    hc->flags |= 0x800;
                    break;

                case 13:
                    //52d4: "out_rndis"
                    hc->flags |= 0x400;
                    break;

                case 17:
                    //52dc: "in_rndis"
                    hc->flags |= 0x200;
                    break;

                case 18:
                    //52e4: "swtoggle"
                    hc->flags |= 0x2000;
                    break;

                case 14:
                    //52ec: "edma"
                    hc->flags &= ~HC_FLAG_USE_DMA;
                    hc->flags |= 0x1000;
                    break;

                case 15:
                    //52f8: "edmachannel"
                    if (value != NULL)
                    {
                        hc->Data_0x44 = strtol(value, 0, 10);
                    }
                    //->51cc
                    break;

                case 16:
                    //530c: "edmairq"
                    if (value != NULL)
                    {
                        hc->edmairq = strtol(value, 0, 10);
                    }
                    //->51cc
                    break;

                default:
                    break;
            }
            //51cc
        }
    }
}


/* todo */
static int mentor_controller_init(
    usb_hcd_t* uhcd/*r5*/, 
    uint32_t flags, 
    char *args/*r7*/)
{
    hctrl_t* hc;

    mentor_slogf(NULL, 12, _SLOG_INFO, 0, 
        "%s(%d): %s (%s %s):  args %s",
        "mentor_controller_init", 3481,
        "devu-hcd-dm816x-mg.so",
        "Feb 15 2017", "16:12:54",
        (args == NULL)? "": args);

    uhcd->hw_ctrl.cname = "dm816x";
    hc = uhcd->hc_data = (hctrl_t*) calloc(1, sizeof(hctrl_t));
    if (uhcd->hc_data == NULL)
    {
        return 12;
    }
    
    hc->uhc = uhcd;
    hc->prio = 24;
    hc->num_ed = 170;
    hc->verbosity = 0; //r3
    hc->flags = (1 << 6) | (1 << 2) | HC_FLAG_USE_DMA; //0x45;
    hc->num_td = 256;
    hc->Data_0x100 = 0; //r3
    hc->Data_0x8c = 4;
    hc->Data_0x1c = 4;
    hc->Data_0x9c = 61440000; //r9
    hc->dirq = -1;
    hc->num_dma = -1;
    hc->Data_0x40 = 0x200;
    hc->args_copy = strdup(args);

    process_args(hc, args);
    //518e
    uhcd->AvailableBandwidth = 61440000; //r7/r9;
    ((hctrl_t*) uhcd->hc_data)->Data_0xa0 = 0x8000; //r2

    uhcd->hw_ctrl.capabilities = 0x40000000000664f;
    uhcd->hw_ctrl.buff_alignment_mask = 0x03;
    uhcd->hw_ctrl.max_transfer_size = 0x8000; //r2
    uhcd->hw_ctrl.max_unaligned_xfer = 0x8000; //r2
    uhcd->num_root_hubs = 1; //r2
    ((hctrl_t*) uhcd->hc_data)->Data_0x2c = 1; //r2

    if ((((hctrl_t*) uhcd->hc_data)->flags & HC_FLAG_USE_DMA) == 0)
    {
        //5320
        uhcd->hw_ctrl.capabilities = 0x40000000000644f;
    }

    return 0;
}


