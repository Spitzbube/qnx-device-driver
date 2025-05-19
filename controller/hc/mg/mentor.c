
#define USE_ORIGINAL_DLL
#define DEBUG_ED
#define DEBUG_INTERRUPT_THREAD
#define DEBUG_CTRL_TRANSFER

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <atomic.h>
#include <sys/mman.h>
#include <sys/rsrcdbmgr.h>
#include <sys/slog.h>
#include "pci.h"
#include <sys/io-usb-otg.h>
#include "mentor.h"


#ifndef USE_ORIGINAL_DLL
/*static*/ iousb_self_t mentor_iousb_self;
/*static*/int dma_nums;
#else
extern iousb_self_t mentor_iousb_self;
extern int mentor_slogf(hctrl_t* hc, 
    int opcode, int severity, int verbosity,
    const char* fmt, ...);

#endif

static int mentor_init(void*, dispatch_t*, iousb_self_t*, char*);
static int mentor_shutdown(void*);
static int mentor_ctrl_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
static int mentor_ctrl_endpoint_disable(void*, iousb_endpoint_t*);
static int mentor_bulk_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
static int mentor_bulk_endpoint_disable(void*, iousb_endpoint_t*);
static int mentor_int_endpoint_disable(void*, iousb_endpoint_t*);
static int mentor_isoch_endpoint_disable(void*, iousb_endpoint_t*);
static void* mentor_interrupt_thread(void*);
static void* mentor_error_pulse_handler(void*);
void mentor_bottom_half(hctrl_t*);
static int mentor_ctrl_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);
static int mentor_ctrl_transfer_abort(void*, iousb_transfer_t*, iousb_endpoint_t*);

extern const struct sigevent * mentor_interrupt_handler(void* a, int b);

#ifdef USE_ORIGINAL_DLL
extern int mentor_controller_init(usb_hcd_t*, uint32_t, char*);
extern int mentor_controller_start(usb_hcd_t*);
extern int mentor_controller_stop(usb_hcd_t*);
extern int mentor_controller_shutdown(usb_hcd_t*);
extern int mentor_set_bus_state(usb_hcd_t*, uint32_t);
extern int mentor_set_port_feature(usb_hcd_t*, uint32_t, uint32_t);
extern int mentor_clear_port_feature(usb_hcd_t*, uint32_t, uint32_t);
extern int mentor_check_port_status(usb_hcd_t*, uint32_t*);
extern int mentor_check_device_connected(usb_hcd_t*, uint32_t);
extern int mentor_get_root_device_speed(usb_hcd_t*, uint32_t);
extern int mentor_get_timer_from_controller(usb_hcd_t*);

extern int mentor_isoch_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
extern int mentor_isoch_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);
extern int mentor_transfer_abort(void*, iousb_transfer_t*, iousb_endpoint_t*);

extern int mentor_bulk_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);

extern int mentor_int_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
extern int mentor_int_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);
#else
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

static int mentor_isoch_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
static int mentor_isoch_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);
static int mentor_transfer_abort(void*, iousb_transfer_t*, iousb_endpoint_t*);

static int mentor_bulk_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);

static int mentor_int_endpoint_enable(void*, iousb_device_t*, iousb_endpoint_t*);
static int mentor_int_transfer(void*, iousb_transfer_t*, iousb_endpoint_t*, uint8_t*, uint32_t, uint32_t);

#endif

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
#ifdef USE_ORIGINAL_DLL
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, "mentor_init");
#endif

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
    usb_hcd_t* uhcd = p;
    hctrl_t* r4 = uhcd->hc_data;
    struct sched_param sp44;
    int res;

    res = pthread_setname_np(0, "mentor_pulse_handler");
    if (res != 0)
    {
        //6f56
        mentor_slogf(r4, 12, 2, 1, 
            "%s - %s : pthread_setname_np() failed ( error = %d )",
            "devu-dm816x-mg.so", 
            "mentor_interrupt_thread",
            res);
    }
    //6f78
    res = ThreadCtl(14, 0);
    if (res == -1)
    {
        mentor_slogf(r4, 12, 2, 1, 
            "%s - %s: Unable to obtain I/O privity.",
            "devu-dm816x-mg.so", 
            "mentor_interrupt_thread");
        //return (void*)res;
        goto end;
    }
    //6fa8
    res = pthread_getschedparam(pthread_self(), NULL, &sp44);
    if (res != 0)
    {
        //6fb8
        res = -1;

        mentor_slogf(r4, 12, 2, 1, 
            "%s - %s: Unable to get priority.",
            "devu-dm816x-mg.so", 
            "mentor_interrupt_thread");
        //return (void*)res;
        goto end;
    }
    //6fde
    SIGEV_PULSE_INIT( &r4->intr_event, r4->Data_0x64/*coid*/, 
        sp44.sched_priority, 1/*MUSB_PULSE_INTR*/, 0 );
    //6ff8
    while ((r4->flags & 0x10) == 0)
    {
        //loc_803c
        delay(1);
    }
    //7006
    r4->Data_0x68/*irq*/ = uhcd->hw_ctrl.pci_inf->Irq;

    r4->Data_0x6c/*intr_id*/ = InterruptAttach(r4->Data_0x68/*irq*/, 
        mentor_interrupt_handler, r4, 0x108, 8);
    if (r4->Data_0x6c/*intr_id*/ == -1)
    {
        res = -1;

        mentor_slogf(r4, 12, 2, 1, 
            "%s - %s: InterruptAttach failed.",
            "devu-dm816x-mg.so", 
            "mentor_interrupt_thread");

        //return (void*)-1;
        goto end;
    }
    //loc_80e0
    while (1)
    {
        //7050
        struct _pulse pulse; //fp_0x30

        if (MsgReceivePulse(r4->Data_0x60/*chid*/, &pulse, sizeof(pulse), 0) == -1)
        {
            break;
        }
        
#ifdef DEBUG_INTERRUPT_THREAD
        mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
            ">>>>>>>>>>>> mentor_interrupt_thread: pulse.code=%d",
            pulse.code);
#endif    
        
        switch (pulse.code)
        {
            case 1:
                //7072
                mentor_bottom_half(r4);
                break;

            case 2:
                pthread_exit(NULL);
                break;

            default:
                //707a
                mentor_slogf(r4, 12, 2, 1, 
                    "%s - %s: Unknown pulse",
                    "devu-dm816x-mg.so", 
                    "mentor_interrupt_thread");
                break;
        }
        //->loc_8100
    } //while (1)

    InterruptDetach(r4->Data_0x6c/*intr_id*/);

end:
    return (void*)res /*NULL*/;
}


/* todo */
static void* mentor_error_pulse_handler(void* p)
{
    hctrl_t* hc = p;
    int res;
    struct _pulse pulse;
    struct
    {
        int Data_0; //0
        int fill_4[8]; //4
        int Data_0x24; //36 = 0x24
        void (*Data_0x28)(); //40 = 0x28
    }* r1;

    res = pthread_setname_np(0, "mentor_error_pulse_handler");
    if (res != 0)
    {
        //4f68
        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "%s: pthread_setname_np() failed ( error = %d )",
            "mentor_error_pulse_handler",
            res);
    }
    //4f84
    while (1)
    {
        //4f8e
        if (-1 == MsgReceivePulse(hc->Data_0x50, &pulse, sizeof(pulse), NULL))
        {
            if ((errno & ~0x100) != 4)
            {
                //->4fe8
                break;
            }
            //->4f8e
        }
        else
        {
            //4fae
            switch (pulse.code)
            {
                case 0:
                    //4fbe
                    r1 = pulse.value.sival_ptr;

                    if ((r1 != NULL) && (r1->Data_0x28 != NULL))
                    {
                        (r1->Data_0x28)(0, r1, r1->Data_0, r1->Data_0x24);
                    }
                    break;

                case 2:
                    //4fb8
                    pthread_exit(NULL);
                    break;

                default:
                    //4fd6
                    mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
                        "%s: Unknown pulse",
                        "mentor_error_pulse_handler");
                    //->4f8e
                    break;
            }
        }
    }
    //4fe8
    return NULL;
}


#ifndef USE_ORIGINAL_DLL


/* todo */
int mentor_fifo_init(hctrl_t* hc, char* b)
{

}


/* todo */
int MENTOR_ProcessInComplete(hctrl_t* hc/*r5*/,
        struct _musb_transfer* td/*r4*/, int32_t r7, int r8)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessInComplete: TODO!!!\n");
#endif

    struct Struct_0xa4* r6 = td->Data_0x30;

    if (r6->bData_0x1f == 0)
    {
        //46f8
        if (td->flags & 0xff0000)
        {
            //4700
            InterruptLock(&hc->Data_0xe4/*r6*/);

            SIMPLEQ_INSERT_TAIL(&hc->transfer_complete_q, td, link);

            InterruptUnlock(&hc->Data_0xe4/*r6*/);
        }
        else
        {
            //471e
            td->bytes_xfered += r7;

            int r2 = (td->flags & (1 << 14)) || 
                (r7 % r6->mps) || (r7 == 0);
            
            if ((r8 != 0) || 
                (td->bytes_xfered >= td->xfer_length) || 
                r2)
            {
                //4750
                HW_Write16(hc, MUSB_RXCSR(r6->num), 0);

                if (r8 != 0)
                {
                    HW_Write16(hc, MUSB_RXCSR(r6->num), RXCSR_FLUSHFIFO);
                    HW_Write16(hc, MUSB_RXCSR(r6->num), RXCSR_FLUSHFIFO);
                }

                InterruptLock(&hc->Data_0xe4/*r7*/);

                td->status = r8;

                if ((r6->Data_8.sqh_first = SIMPLEQ_NEXT(td, link)) == NULL)
                {
                    r6->Data_8.sqh_last = &r6->Data_8.sqh_first;
                }
                //4784
                SIMPLEQ_INSERT_TAIL(&hc->transfer_complete_q, td, link);

                if ((r8 == 0) &&
                    ((td = r6->Data_8.sqh_first) != NULL))
                {
                    //479e
                    MUSB_UNLOCK
                    //->47c8
                    MENTOR_StartEtd(hc, td);
                }
                else
                {
                    //47a6
                    hc->Data_0xd8[r6->num] = 0;

                    if (r8 == 0)
                    {
                        //47b8
                        r6->Data_0x10 &= ~(1 << 0);

                    }
                    //47c0
                    MUSB_UNLOCK
                }
            }
            else
            {
                //47c8
                MENTOR_StartEtd(hc, td);
            }
        }
    }
    //47d0
    return 0;
}


/* complete */
int MENTOR_AllocateTD(hctrl_t* hc)
{
    uint32_t i;
    struct _musb_transfer* td;

    SIMPLEQ_INIT( &hc->transfer_free_q );
    SIMPLEQ_INIT( &hc->transfer_complete_q );

    td = calloc(1, sizeof(struct _musb_transfer) * (hc->num_td + 1));
    if (td == NULL)
    {
        return 12;
    }

    hc->transfer_mem = td;

    memset(td, 0, (hc->num_td + 1) * sizeof(struct _musb_transfer));

    for (i = 0; i < hc->num_td; i++, td++)
    {
        SIMPLEQ_INSERT_TAIL( &hc->transfer_free_q, td, link );
    }

    return 0;
}


/* complete */
void MENTOR_FreeTD(hctrl_t* hc)
{
    free(hc->transfer_mem);
}

#endif //!USE_ORIGINAL_DLL


/* complete */
void mentor_free_dma_sched()
{
}


/* complete */
int mentor_free_dma_channel()
{
    return 0;
}


/* todo */
void edma3_transfer_done(struct _hctrl_t_Inner_0x28* a, int b)
{

}


/* complete */
static void edma_detach_channel(struct _hctrl_t_Inner_0x28_Inner0* a, int b)
{
    struct _hctrl_t_Inner_0x28_Inner0* r4 = &a[b];

    if (r4->Data_4 != -1)
    {
        rsrc_request_t sp = {0};

        sp.length = 1;
        sp.flags = 0x03;
        sp.start = sp.end = r4->Data_4;

        rsrcdbmgr_detach(&sp, 1);

        r4->Data_4 = -1;
    }

    if (r4->Data_12 != -1)
    {
        InterruptDetach(r4->Data_12);

        r4->Data_12 = -1;
    }
}


/* complete */
int mentor_edma_shutdown(hctrl_t* hc)
{
    struct _hctrl_t_Inner_0x28* r4 = hc->Data_0x28;
    int i;

    for (i = 1; i < r4->Data_8; i++)
    {
        int r1 = r4->Data_0[i].Data_4;
        if (r1 != -1)
        {
            edma3_transfer_done(r4, r1);
            edma_detach_channel(r4->Data_0, i);
        }
    }

    munmap_device_memory(r4->Data_12, 0x5000);
    free(r4->Data_0);
    free(r4);

    return 0;
}


/* complete */
void mentor_edma_free_channel(hctrl_t* hc, int r5)
{
    struct _hctrl_t_Inner_0x28* r4 = hc->Data_0x28;

    if ((r5 > 0) && (r5 < r4->Data_8))
    {
        int r1 = r4->Data_0[r5].Data_4;
        if (r1 != -1)
        {
            edma3_transfer_done(r4, r1);
            edma_detach_channel(r4->Data_0, r5);
        }
    }
}


/* complete */
int MENTOR_FreeEtd(hctrl_t* hc, struct Struct_0xa4* r4)
{
    int r5 = r4->num;

    if (r4->Data_0x30 != NULL)
    {
        mentor_fifo_free(hc, r4->Data_0x30);
    }

    r4->Data_0x30 = NULL;

    if (r4->Data_0x38 != 0)
    {
        mentor_free_dma_sched(hc, r4->Data_0x38);

        r4->Data_0x38 = 0;
    }

    if (r4->Data_0x2c != -1)
    {
        mentor_free_dma_channel(hc, r4->Data_0x2c);

        r4->Data_0x2c = -1;
    }

    if ((r5 > 0) && (r5 < hc->Data_0x1c))
    {
        if (hc->flags & (1 << 12))
        {
            mentor_edma_free_channel(hc, r4->num);
        }

        r4->num = -1;
        r4->Data_0x2c = -1;

        hc->Data_0xdc[r5] = NULL;
    }
    else
    {
        return -1;
    }

    return r5;
}


/* complete */
int MENTOR_AllocateED(hctrl_t* hc)
{
    uint32_t i;
    struct Struct_0xa4* r4;
    
    r4 = calloc(1, (hc->num_ed + 1) * sizeof(struct Struct_0xa4));
    if (r4 == NULL)
    {
        return 12;
    }

    hc->Data_0xc0 = r4;

#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> MENTOR_AllocateED: r4=%p, num_ed=%d",
        r4, hc->num_ed);
#endif    

    memset(r4, 0, (hc->num_ed + 1) * sizeof(struct Struct_0xa4));

    SIMPLEQ_INIT(&r4->Data_8);

    r4->Data_0x10 = 0;
    hc->Data_0xc4 = r4;

    for (i = 0; i < hc->num_ed; i++)
    {
        r4->Data_0x2c = -1;
        r4->link.next = r4 + 1;
        r4->link.next->link.prev = r4;

        SIMPLEQ_INIT(&r4->link.next->Data_8);

        r4->link.next->Data_0x10 = 0;

        r4++;
    }

    r4->link.next = hc->Data_0xc4;
    hc->Data_0xc4->link.prev = r4;

    return 0;
}


/* complete */
void MENTOR_FreeED(hctrl_t* hc)
{
    free(hc->Data_0xc0);
}


/* complete */
struct Struct_0xa4* MENTOR_GetEDPool(hctrl_t* hc)
{
    struct Struct_0xa4* r4;
    struct Struct_0xa4* r6 = hc->Data_0xc4;

    MUSB_MUTEX_LOCK(Data_4, 0x133);
    //547c
    r4 = r6->link.next;
    if (r4 == r6)
    {
        //5482
        MUSB_MUTEX_UNLOCK(Data_4, 0x136);

        r4 = NULL;
    }
    else
    {
        //54a6
#ifdef DEBUG_ED
        mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
            ">>>>>>>>>>>> MENTOR_GetEDPool: r6=%p, r4=%p",
            r6, r4);
#endif    

        r6->link.next = r4->link.next;
        r4->link.next->link.prev = r6;
        r4->Data_0x10 |= (1 << 31);
        r4->Data_0x38 = 0;

        MUSB_MUTEX_UNLOCK(Data_4, 0x141);
    }
    //loc_5428
    return r4;
}


/* complete */
int MENTOR_BuildEDList(hctrl_t* hc, struct Struct_0xa4** b)
{
    struct Struct_0xa4* r3;
    
    r3 = MENTOR_GetEDPool(hc);
    if (r3 == NULL)
    {
        return 12;
    }

#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> MENTOR_BuildEDList: r3=%p",
        r3);
#endif

    *b = r3;
    r3->Data_0x10 |= (1 << 30) | (1 << 3);
    SIMPLEQ_INIT(&r3->Data_8);
    r3->link.prev = r3;
    r3->link.next = r3;

    return 0;
}


/* complete */
int MENTOR_HookED(hctrl_t* hc, 
    struct Struct_0xa4* r6, 
    struct Struct_0xa4* r4)
{
    struct Struct_0xa4* r3;

    MUSB_MUTEX_LOCK(Data_4, 0x335);

    r3 = r6->link.prev;

#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> MENTOR_HookED: r6=%p, r4=%p, r3=%p",
        r6, r4, r3);
#endif

    r3->link.next = r4;
    r4->link.next = r6;
    r6->link.prev = r4;
    r4->link.prev = r3;

    SIMPLEQ_INIT(&r4->Data_8);

    MUSB_MUTEX_UNLOCK(Data_4, 0x340);

    return 0;
}


/* complete */
int MENTOR_UnHookED(hctrl_t* hc, struct Struct_0xa4* r4)
{
    struct Struct_0xa4* r3;

    if (r4 != NULL)
    {
        MUSB_MUTEX_LOCK(Data_4, 0x34d);

        MENTOR_FreeEtd(hc, r4);

        r3 = r4->link.prev;
        r3->link.next = r4->link.next;
        r4->link.next->link.prev = r3;
    
        MUSB_MUTEX_LOCK(Data_4, 0x356);

        MENTOR_PutEDPool(hc, r4);
    }

    return 0;
}


/* complete */
int MENTOR_InitializeEndpoint(hctrl_t* hc, 
    /*struct USB_Controller_Inner_0x7c*/iousb_device_t* iousbdev, 
    /*struct Struct_112b08*/iousb_endpoint_t* iousbep)
{
    struct Struct_0xa4* r1 = iousbep->user;

#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> MENTOR_InitializeEndpoint: r1=%p",
        r1);
#endif

    if (r1 == NULL)
    {
        r1 = MENTOR_GetEDPool(hc);
        if (r1 == NULL)
        {
            mentor_slogf(hc, 12, 2, 1, "%s - No ED for Endpoint",
                "devu-dm816x-mg.so");

            return 12;
        }
        //637a
        iousbep->user = r1;
        r1->Data_0x34 = iousbep;
        r1->num = -1;
    }
    //6384
    r1->transferType = iousbep->edesc.bmAttributes & 0x03;
    r1->mps = iousbep->edesc.wMaxPacketSize;
    r1->bData_0x1b = iousbep->edesc.bEndpointAddress & ~0x7f;
    r1->Data_0x20 = 0;
    r1->Data_0x14 = ((iousbdev->device_address & 0x7f) << 4) | 
            (iousbep->edesc.bEndpointAddress & 0x0f);

    switch (iousbdev->device_speed & 0x03)
    {
        case IOUSB_DEVICE_FULL_SPEED:
            r1->bData_0x1c = 0x80;
            break;

        case IOUSB_DEVICE_LOW_SPEED:
            r1->bData_0x1c = 0xc0;
            break;

        case IOUSB_DEVICE_HIGH_SPEED:
            r1->bData_0x1c = 0x40;
            break;
    }
    //63c8
    r1->Data_0x24 = iousbep->edesc.bInterval;

    if ((r1->bData_0x1c != 0x40) && 
        (NULL != hc->uhc->hcd_self->iousb_get_parent_device(iousbdev)))
    {
        iousb_device_t* parent;

        while ((parent = hc->uhc->hcd_self->iousb_get_parent_device(iousbdev)) != NULL)
        {
            if (parent->device_speed == IOUSB_DEVICE_HIGH_SPEED)
            {
                break;
            }

            iousbdev = parent;
        }

        if (parent == NULL)
        {
            return -1;
        }        
        //63fc
        r1->bData_0x1d = parent->device_address;
        r1->bData_0x1e = iousbdev->device_port;
    }
    //6404
    return 0;
}


/* complete */
int mentor_ctrl_endpoint_enable(
#if 0
    struct USB_Controller* a, 
    struct USB_Controller_Inner_0x7c* b, 
    struct Struct_112b08* c)
#else
    void* chdl, 
    iousb_device_t* iousbdev, 
    iousb_endpoint_t* iousbep)
#endif
{
#if 0
    fprintf(stderr, "mentor_ctrl_endpoint_enable: a=%p, b=%p, c=%p\n",
        a, b, c);
#endif

    hctrl_t* hc = ((struct _usb_hcd*)chdl)->hc_data;
    struct Struct_0xa4* r7 = iousbep->user;

#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> mentor_ctrl_endpoint_enable: hc=%p, r7=%p",
        hc, r7);
#endif

    int res = MENTOR_InitializeEndpoint(hc, iousbdev, iousbep);

    if (res == 0)
    {
        if (r7 == NULL)
        {
            ((struct Struct_0xa4*)iousbep->user)->Data_0x24 = 0;

            MENTOR_HookED(hc, hc->Data_0xc8, iousbep->user);
        }
    }

    return res;
}


int mentor_ctrl_endpoint_disable(void* chdl, iousb_endpoint_t* iousbep)
{
#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> mentor_ctrl_endpoint_disable: iousbep=%p",
        iousbep);
#endif
    return mentor_isoch_endpoint_disable(chdl, iousbep);
}


int mentor_bulk_endpoint_disable(void* chdl, iousb_endpoint_t* iousbep)
{
#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> mentor_bulk_endpoint_disable: iousbep=%p",
        iousbep);
#endif
    return mentor_isoch_endpoint_disable(chdl, iousbep);
}


int mentor_int_endpoint_disable(void* chdl, iousb_endpoint_t* iousbep)
{
#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> mentor_int_endpoint_disable: iousbep=%p",
        iousbep);
#endif
    return mentor_isoch_endpoint_disable(chdl, iousbep);
}


int mentor_isoch_endpoint_disable(void* chdl, iousb_endpoint_t* iousbep)
{
    hctrl_t* hc = ((struct _usb_hcd*)chdl)->hc_data;
    struct Struct_0xa4* r1 = iousbep->user;

#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> mentor_isoch_endpoint_disable: r1=%p",
        r1);
#endif

    return MENTOR_UnHookED(hc, r1);
}



/* complete */
int mentor_bulk_endpoint_enable(
#if 0
    struct USB_Controller* a, 
    struct USB_Controller_Inner_0x7c* b, 
    struct Struct_112b08* r6)
#else
    void* chdl, 
    iousb_device_t* iousbdev, 
    iousb_endpoint_t* iousbep)
#endif
{
#if 0
    fprintf(stderr, "mentor_bulk_endpoint_enable: a=%p, b=%p, r6=%p\n",
        a, b, r6);
#endif

    hctrl_t* hc = ((struct _usb_hcd*)chdl)->hc_data;
    struct Struct_0xa4* r4 = iousbep->user;

#ifdef DEBUG_ED
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> mentor_bulk_endpoint_enable: hc=%p, r4=%p",
        hc, r4);
#endif

    int res = MENTOR_InitializeEndpoint(hc, iousbdev, iousbep);

    if ((res == 0) && (r4 == NULL))
    {
        r4 = iousbep->user;

        MENTOR_HookED(hc, hc->Data_0xcc, r4);
    }
    else
    {
        if (r4 != NULL)
        {
            if (r4->num > 0)
            {
                MENTOR_FreeEtd(hc, r4);
            }
        }
    }

    r4->Data_0x24 = 0;

    return res;
}

#ifndef USE_ORIGINAL_DLL


/* todo */
const struct sigevent* dma_interrupt_handler(void *__area, int __id)
{

}


/* todo */
int mentor_handle_extra_complete()
{

}



/* todo */
int mentor_handle_device_connected()
{

}


struct hc_0xfc
{
    int Data_0; //0
    int Data_4; //4
    int fill_8; //8
    char bData_0xc; //12
    int fill_0x10[3]; //0x10
    int Data_0x1c; //0x1c
    int Data_0x20; //0x20
    //44 = 0x2c???
};


static int create_bds(hctrl_t* hc)
{
    //32be
    struct hc_0xfc* sl = hc->Data_0xfc;

    //TODO
}


static int dma_init(hctrl_t* hc)
{
    struct hc_0xfc* r8 = hc->Data_0xfc;
    int r7;

    mentor_slogf(hc, 12, _SLOG_ERROR, 3, 
        "devu-dm816x-mg.so: init dma CDMA_REVID=%x USBSS_REVREG=%x",
        *((volatile uint32_t*)(r8->Data_4 + 0x2000)),
        *((volatile uint32_t*)(r8->Data_4 + 0)));

    r8->Data_0x20 = InterruptAttach(r8->Data_0x1c, 
        dma_interrupt_handler,hc, 0x108, 0x08);
    if (r8->Data_0x20 == -1)
    {
        //3284
        r7 = errno;

        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "devu-dm816x-mg.so: %s - failed to attached dma intr",
            "dma_init");
        
        return r7;
    }
    else
    {
        //32ac
        if (dma_nums/*r9*/ == 0)
        {
            //32be
            create_bds(hc);

        }
        //3514

        //TODO!!!

        //3554
        int r2 = r8->Data_4;

        //TODO!!!

        //35da
        if (r8->bData_0xc == 0)
        {
            //35e0
            *((volatile uint32_t*)(r2 + 0x2c)) = 0x305;
            *((volatile uint32_t*)(r2 + 0x140)) = 0xfffefffe;
        }
        //35f0
        else if (r8->bData_0xc == 1)
        {
            *((volatile uint32_t*)(r2 + 0x2c)) = 0xc05;
            *((volatile uint32_t*)(r2 + 0x144)) = 0xfffefffe;
        }
        //3602
        dma_nums++;
    }
    //->363a
    return 0;
}



/* todo */
int mentor_board_specific_init1(hctrl_t* hc/*r4*/)
{
    int r7;
    struct hc_0xfc* r5;

    usb_hcd_t* sp20 = hc->uhc;

    hc->Data_0x40 = 0x400;
    hc->Data_0x1c = 16;
    hc->Data_0x100 = mentor_handle_extra_complete;
    hc->Data_0x104 = mentor_handle_device_connected;

    atomic_toggle(&hc->flags, (1 << 9));
    //TODO!!!

    //30d0
    hc->Data_0xfc = r5 = calloc(1, 44);
    if (hc->Data_0xfc == NULL)
    {
        //30e2
        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "devu-dm816x-mg.so : %s - failed to create dm816x context",
            "mentor_board_specific_init1");

        return 12;
    }
    //30fe

    //TODO!!!

    //3178
    r5->Data_4 = mmap_device_memory(NULL, 
        0x8000, 0xb00, 0x10001, 0x47400000);
    if (r5->Data_4 == 0)
    {
        //3198
        r7 = 12;

        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "devu-dm816x-mg.so : %s - couldn't map dm816x-sepecific registers",
            "mentor_board_specific_init1");
        //->loc_3632
        goto error_3632;

    }
    //31b4
    //int r8_ = sp20->hw_ctrl.pci_inf->CpuBaseAddress[0];
    //int r9_ = sp20->hw_ctrl.pci_inf->CpuBaseAddress[1];

    r5->Data_0 = r5->Data_4 + /*r8_*/sp20->hw_ctrl.pci_inf->CpuBaseAddress[0] + 0xB8BFFC00;

    if (sp20->hw_ctrl.pci_inf->CpuBaseAddress[0] == 0x47401c00)
    {
        r5->bData_0xc = 1;
    }
    else
    {
        r5->bData_0xc = 0;
    }

    *((volatile uint32_t*)(r5->Data_0 + 0x14)) = 1;

    while (*((volatile uint32_t*)(r5->Data_0 + 0x14)) & 1)
    {
        //31e8
        delay(1);
    }
    //31fa
    *((volatile uint32_t*)(r5->Data_0 + 0xe8)) = 0;
    *((volatile uint32_t*)(r5->Data_0 + 0xe0)) = 2;
    *((volatile uint32_t*)(r5->Data_0 + 0x70)) = 0;
    *((volatile uint32_t*)(r5->Data_0 + 0x74)) = 0;
    *((volatile uint32_t*)(r5->Data_0 + 0x14)) &= ~(1 << 4);
    *((volatile uint32_t*)(r5->Data_0 + 0xd0)) = 0;

    if (hc->fconfig_string == NULL)
    {
        //321a
        hc->fconfig_string = strdup("16:8;4:16;8:64;2:128;30:512");
    }
    //3226
    mentor_fifo_init(hc, hc->fconfig_string);

    if (hc->flags & (1 << 0))
    {
        //3238
        r5->Data_0x1c = 0x11;

#if 0
        r8 = hc->Data_0xfc;

        mentor_slogf(hc, 12, _SLOG_ERROR, 3, 
            "devu-dm816x-mg.so: init dma CDMA_REVID=%x USBSS_REVREG=%x",
            *((volatile uint32_t*)(r8->Data_4 + 0x2000)),
            *((volatile uint32_t*)(r8->Data_4 + 0)));

        r8->Data_0x20 = InterruptAttach(r8->Data_0x1c, dma_interrupt_handler,
            hc, 0x108, 0x08);
        if (r8->Data_0x20 == -1)
        {
            //3284
            r7 = errno;

            mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
                "devu-dm816x-mg.so: %s - failed to attached dma intr",
                "dma_init");
            if (r7 != 0)
            {
                //->3610
                goto error_3610;
            }
            //->360c
            //TODO!!!
        }
        else
        {
            //32ac
            //TODO!!!
        }
#else
        r7 = dma_init(hc);
        if (r7 != 0)
        {
            //->3610
            goto error_3610;
        }
#endif
    }
    //360c
    return 0;

error_3610:
    mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
        "devu-dm816x-mg.so : %s - couldn't init the dma... restart the driver with nodma option",
        "mentor_board_specific_init1");

    munmap_device_memory(r5->Data_4, 0x8000);

error_3632:
    free(r5);

    return r7;
}


/* todo */
int mentor_board_specific_shutdown1(hctrl_t* hc)
{

}


/* todo */
int mentor_board_specific_init2(hctrl_t* hc)
{
    
}


/* todo */
int mentor_board_specific_shutdown2(hctrl_t* hc)
{

}


/* todo */
int mentor_edma_init(hctrl_t* hc)
{

}


/* todo */
int mentor_edma_shutdown(hctrl_t* hc)
{

}

#endif //!USE_ORIGINAL_DLL


/* todo */
static int mentor_create_completion_thread(usb_hcd_t* uhcd)
{
    hctrl_t* r6 = uhcd->hc_data;
    pthread_attr_t sp_0x60;
    struct sched_param sp_0x176;

    int r5;
    r6->Data_0x60 = ChannelCreate(_NTO_CHF_DISCONNECT);
    if (r6->Data_0x60 < 0)
    {
        //7570
        mentor_slogf(r6, 12, _SLOG_ERROR, 0/*r5*/, 
            "%s : %s - Unable to create channel",
            "devu-hcd-dm816x-mg.so", 
            "mentor_create_completion_thread");
        r5 = r6->Data_0x60;
        //->763e
        goto error_763e;
    }
    //7596
    r6->Data_0x64 = ConnectAttach(0, 0, r6->Data_0x60, 
        0x40000000, 0);
    if (r6->Data_0x64 < 0)
    {
        //75aa
        mentor_slogf(r6, 12, _SLOG_ERROR, 0/*r5*/, 
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

    r5 = pthread_create(&r6->Data_0x5c, &sp_0x60/*r5*/, 
        mentor_interrupt_thread, uhcd/*r7*/);
    if (r5 == 0)
    {
        //->7644
        goto success_7644;
    }
    //7610
    mentor_slogf(r6, 12, _SLOG_ERROR, 0/*r8*/, 
        "%s : %s - Unable to create interrupt thread",
        "devu-hcd-dm816x-mg.so", 
        "mentor_create_completion_thread");

    ConnectDetach(r6->Data_0x64);
error_7638:
    ChannelDestroy(r6->Data_0x60);

error_763e:
success_7644:
    return r5;
}


/* todo */
int mentor_create_error_pulse_thread(usb_hcd_t* uhcd)
{
    hctrl_t* hc/*r4*/ = uhcd->hc_data;
    pthread_attr_t sp_0x30;
    struct sched_param sp_0x80;
    int res;

    hc->Data_0x50 = ChannelCreate(_NTO_CHF_DISCONNECT);
    if (hc->Data_0x50 < 0)
    {
        //7396
        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "%s : Unable to create channel",
            "mentor_create_error_pulse_thread");

        res = hc->Data_0x50;
        goto error_7468;
    }
    //73b6
    hc->Data_0x54 = ConnectAttach(0, 0, hc->Data_0x50, 
        0x40000000, 0);
    if (hc->Data_0x54 < 0)
    {
        //73cc
        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "%s : Unable to connect to channel",
            "mentor_create_error_pulse_thread");

        res = hc->Data_0x54;
        goto error_7460;
    }
    //73ec
    if (hc->Data_0x58 == 0)
    {
        hc->Data_0x58 = hc->prio;
    }
    //73f4
    pthread_attr_init(&sp_0x30/*r6*/);
    pthread_attr_setschedpolicy(&sp_0x30/*r6*/, 2);
    sp_0x80.sched_priority = hc->Data_0x58;
    pthread_attr_setschedparam(&sp_0x30/*r6*/, &sp_0x80);
    pthread_attr_setinheritsched(&sp_0x30/*r6*/, 2);
    //741a
    res = pthread_create(&hc->Data_0x4c, &sp_0x30/*r6*/, 
        mentor_error_pulse_handler, hc/*r4*/);
    if (res != 0)
    {
        //742e
        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "%s : Unable to create interrupt thread",
            "mentor_create_error_pulse_thread");

        pthread_attr_destroy(&sp_0x30/*r6*/);
        ConnectDetach(hc->Data_0x54);
        //->7460
        goto error_7460;
    }
    //7458
    pthread_attr_destroy(&sp_0x30/*r6*/);

    return 0;

error_7460:
    ChannelDestroy(hc->Data_0x50);

error_7468:
    return res;
}


/* todo */
int mentor_destroy_error_pulse_thread(usb_hcd_t* uhcd)
{
    hctrl_t* hc = uhcd->hc_data;

    if (-1 == MsgSendPulse(hc->Data_0x54, hc->Data_0x58, 2, 0))
    {
        //72ac
        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "%s : MsgSendPulse error %s",
            "mentor_destroy_error_pulse_thread",
            strerror(errno));
    }

    pthread_join(hc->Data_0x4c, 0);
    ConnectDetach(hc->Data_0x54);
    ChannelDestroy(hc->Data_0x50);
}



int mentor_controller_start(usb_hcd_t* uhcd/*r7*/)
{
    int res; //r5
    pthread_mutexattr_t mattr; //sp_0x18;

    hctrl_t* hc/*r4*/ = uhcd->hc_data;

#if 1
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> mentor_controller_start: hc=%p",
        hc);
#endif

    pthread_mutexattr_init(&mattr);
    pthread_mutexattr_setrecursive(&mattr, 2);
    
    res = pthread_mutex_init(&hc->Data_4/*sl*/, &mattr);
    if (res != 0)
    {
        //74d8
        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
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
        mentor_slogf(hc, 12, _SLOG_ERROR, 0/*r8*/, 
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

    res = mentor_create_completion_thread(uhcd);
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
    res = MENTOR_BuildEDList(hc, &hc->Data_0xc8);
    if (res != 0)
    {
        //->77f0
        goto error_77f0;
    }
    //7672
    res = MENTOR_BuildEDList(hc, &hc->Data_0xcc);
    if (res != 0)
    {
        //->77f0
        goto error_77f0;
    }
    //7684
    res = MENTOR_BuildEDList(hc, &hc->Data_0xd4);
    if (res != 0)
    {
        //->77f0
        goto error_77f0;
    }
    //7696
    res = MENTOR_BuildEDList(hc, &hc->Data_0xd0);
    if (res != 0)
    {
        //->77f0
        goto error_77f0;
    }
    //76a8
    res = mentor_board_specific_init1(hc);
    if (res != 0)
    {
        //76b2
        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "%s : %s - mentor_board_specific_init1 failed",
            "devu-hcd-dm816x-mg.so", 
            "mentor_controller_start");
        //->77f0
        goto error_77f0;
    }
    //76d6
    if (hc->flags & (1 << 12))
    {
        //7726
        res = mentor_edma_init(hc);
        if (res != 0)
        {
            //->77f0
            goto error_77f0;
        }
    }
    //76dc
    *((volatile uint8_t*)(hc->Data_0x14 + 0x0f)) = 0; //r6
    *((volatile uint16_t*)(hc->Data_0x14 + 0x60)) = 0; //r6
    *((volatile uint16_t*)(hc->Data_0x14 + 0x414)) = 0; //r6
    *((volatile uint16_t*)(hc->Data_0x14 + 0x404)) = 0x1008;

    res = mentor_board_specific_init2(hc);
    if (res != 0)
    {
        //7702
        mentor_slogf(hc, 12, _SLOG_ERROR, 0/*r6*/, 
            "%s : %s - mentor_board_specific_init2 failed",
            "devu-hcd-dm816x-mg.so", 
            "mentor_controller_start");
        //->77de
        goto error_77de;
    }
    //7734
    int r6_ = hc->Data_0x1c;
    hc->Data_0xd8 = calloc(r6_, 4);
    if (hc->Data_0xd8 == NULL)
    {
        //7744
        res = 12;

        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "%s : %s - calloc failed",
            "devu-hcd-dm816x-mg.so", 
            "mentor_controller_start");
        //->77d8
        goto error_77d8;
    }
    //776a
    hc->Data_0xdc = calloc(r6_, 4);
    if (hc->Data_0xdc == NULL)
    {
        //7778
        res = 12;

        mentor_slogf(hc, 12, _SLOG_ERROR, 0, 
            "%s : %s - calloc failed",
            "devu-hcd-dm816x-mg.so", 
            "mentor_controller_start");
        //->77d0
        goto error_77d0;
    }
    //779e
    res = mentor_create_error_pulse_thread(uhcd/*r7*/);
    if (res != 0)
    {
        //->77c8
        goto error_77c8;
    }
    //77a8
    hc->flags |= (1 << 4);

    *((volatile uint8_t*)(hc->Data_0x14 + 0x01)) = 0x60;

    res = mentor_set_bus_state(uhcd/*r7*/, 0x05);
    if (res == 0)
    {
        //->781e
        goto success_781e;
    }

error_77c2:
    mentor_destroy_error_pulse_thread(uhcd/*r7*/);

error_77c8:
    free(hc->Data_0xdc);

error_77d0:
    free(hc->Data_0xd8);

error_77d8:
    mentor_board_specific_shutdown2(hc);

error_77de:
    mentor_board_specific_shutdown1(hc);
    
    if (hc->flags & (1 << 12))
    {
        mentor_edma_shutdown(hc);
    }

error_77f0:
    MENTOR_FreeED(hc);

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

success_781e:
    return res;
}

#ifndef USE_ORIGINAL_DLL

/* complete */
static int mentor_controller_stop(usb_hcd_t* uhcd)
{
    hctrl_t* hc = uhcd->hc_data;

    mentor_set_bus_state(uhcd, USB_BUS_STATE_STOP);

    *((volatile uint8_t*)(hc->Data_0x14 + 0x60)) = 0x00;
    *((volatile uint8_t*)(hc->Data_0x14 + 0x01)) = 0x00;

    mentor_board_specific_shutdown2(hc);
    mentor_board_specific_shutdown1(hc);

    if (hc->flags & (1 << 12))
    {
        mentor_edma_shutdown(hc);
    }

    mentor_destroy_error_pulse_thread(uhcd);
    InterruptDetach(hc->Data_0x6c);
    mentor_destroy_completion_thread(uhcd->hc_data);
    pthread_mutex_destroy(&hc->Data_4);
    pthread_mutex_destroy(&hc->Data_0xc);
    munmap_device_memory(hc->Data_0x14, 0x2000);
    free(hc->Data_0xc0);
    free(hc->transfer_mem);
    free(hc->Data_0xd8);
    free(hc->Data_0xdc);

    return 0;
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


/* todo */
static int mentor_set_bus_state(usb_hcd_t* uhcd, uint32_t bus_state)
{
    hctrl_t* hc = uhcd->hc_data;

    mentor_slogf(hc, 12, _SLOG_ERROR, 3, 
        "%s(%d): bus_state=%x",
        "mentor_set_bus_state", 2732, bus_state);

    switch (bus_state)
    {
        case USB_BUS_STATE_START: //5:
            //4f2c
            *((volatile uint8_t*)(hc->Data_0x14 + 0x60)) |= (1 << 0);
            break;

        case USB_BUS_STATE_STOP: //6:
            //4f16
            *((volatile uint8_t*)(hc->Data_0x14 + 0x60)) &= ~(1 << 0);
            delay(5);
            break;
    }

    return 0;
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

#endif //!USE_ORIGINAL_DLL













































































































































































































































































































































































































































































































































































































































































































































































































































































































































/* todo */
void mentor_bottom_half(hctrl_t* hc)
{
    struct _musb_transfer* td;

    while (1)
    {
        //6e80
        MUSB_LOCK

        td = SIMPLEQ_FIRST(&hc->transfer_complete_q);
        if (td == NULL)
        {
            //->6f0c
            break;
        }

#if 0 //def DEBUG_INTERRUPT_THREAD
        mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
            ">>>>>>>>>>>> mentor_bottom_half: td=%p",
            td);
#endif

        SIMPLEQ_REMOVE_HEAD(&hc->transfer_complete_q, link);

        MUSB_UNLOCK

        MUSB_MUTEX_LOCK(Data_4, 0xa55);
        //6ec6
        if (((td->flags & 0xff0000) != 0) &&
            (hc->Data_0x100 != NULL))
        {
            (hc->Data_0x100)(hc, td);
        }
        else
        {
            //6edc
            MENTOR_URB_complete(hc, 
                td->Data_0x30, 
                td, 
                td->Data_0x30->transferType,
                td->status);
        }
        //6eec
        MUSB_MUTEX_UNLOCK(Data_4, 0xa5c);
        //->6e80
    } //while (1)
    //6f0c
    hc->wData_0xea = 0;

    MUSB_UNLOCK
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
int mentor_controller_init(usb_hcd_t* uhcd/*r5*/, 
    uint32_t flags, 
    char *args/*r7*/)
{
    hctrl_t* hc;

    mentor_slogf(NULL, 12, _SLOG_INFO, 0, 
        "%s(%d): %s (%s %s):  args %s",
#ifdef USE_ORIGINAL_DLL
        __FUNCTION__, __LINE__,
        "devu-hcd-dm816x-mg.so",
        __DATE__, __TIME__,
#else
        "mentor_controller_init", 3481,
        "devu-hcd-dm816x-mg.so",
        "Feb 15 2017", "16:12:54",
#endif
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
    hc->Data_0x100 = NULL; //r3
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



/* complete */
void MENTOR_LoadFIFO(hctrl_t* hc, uint16_t b, int c, uint16_t r8)
{
    uint16_t r6 = c + r8;
    uint32_t* r5 = c;

    while (1)
    {
        uint16_t r4 = (int)r6 - (int)r5;
        if (r4 < 4)
        {
            break;
        }

        *((volatile uint32_t*)(hc->Data_0x14 + 0x20 + b * 4)) = *r5++;
    }

    int r6_ = (r8 >> 2) * 0x3fff;
    int r5_ = c + ((r8 >> 2) << 2);
    uint16_t r3 = r8  + (r6_ << 2);
    if (r3 & 0x02)
    {
        *((volatile uint16_t*)(hc->Data_0x14 + 0x20 + b*4)) = *((volatile uint16_t*)r5_);
        r5_ += 2;
    }

    if (r3 & 0x01)
    {
        *((volatile uint8_t*)(hc->Data_0x14 + 0x20 + b*4)) = *((volatile uint8_t*)r5_);
    }
}



/* complete */
struct _musb_transfer* MENTOR_TD_Setup(hctrl_t* hc, 
    iousb_transfer_t* urb, 
    struct Struct_0xa4* c, 
    uint32_t flags)
{
    struct _musb_transfer* td;

    MUSB_LOCK

    td = SIMPLEQ_FIRST(&hc->transfer_free_q);
    if (td == NULL)
    {
        urb->status = 0x2000010;

        MUSB_UNLOCK

        mentor_slogf(hc, 12, _SLOG_ERROR, 1, 
            "%s - No TD's available",
            "devu-hcd-dm816x-mg.so");
    }
    else
    {
        SIMPLEQ_REMOVE_HEAD(&hc->transfer_free_q, link);

        MUSB_UNLOCK

        td->flags = flags & 0x8000003f;
        td->bytes_xfered = 0;
        td->status = 0;
        td->Data_0x30 = c;
        td->Data_0x34 = urb;
    }

    return td;
}


/* todo */
void MENTOR_StartControlEtd(hctrl_t* hc/*r6*/, struct _musb_transfer* td)
{
    struct Struct_0xa4* r5 = td->Data_0x30;
    uint16_t csr; //r4
    int csrH = 0;
    int r1 = 0;
    int length;

    td->flags |= (1 << 8);

    r5->bData_0x1f = 0;

    if (td->flags & PIPE_FLAGS_TOKEN_SETUP)
    {
        r5->Data_0x20 = 0;
        csr = CSR0_SETUPPKT;
    }
    else if (td->flags & PIPE_FLAGS_TOKEN_STATUS)
    {
        csr = CSR0_STATUS_PKT;
        r5->Data_0x20 = 1;
    }
    else
    {
        csr = 0;
    }

    if (r5->Data_0x20 != 0)
    {
        csrH = CSR0_DATA_TOGGLE;
    }
    csrH |= CSR0_FLUSH_FIFO | CSR0_DATA_TOGGLE_WR_EN;
    r1 = (hc->flags & (1 << 7))? CSR0_DISPING: 0;
    csrH |= r1;

    HW_Write16(hc, MUSB_CSR0, csrH);
    HW_Write16(hc, MUSB_TXFUNCADDR(0), (r5->Data_0x14 >> 4) & 0x7f);

    if (r5->bData_0x1c != 0x40)
    {
        HW_Write8(hc, MUSB_TXHUBADDR(0), r5->bData_0x1d);
        HW_Write8(hc, MUSB_TXHUBPORT(0), r5->bData_0x1e);
    }

    HW_Write8(hc, MUSB_NAKLIMIT0(0), 0);

    if (td->flags & PIPE_FLAGS_TOKEN_SETUP)
    {
        csr |= CSR0_SETUPPKT | CSR0_TXPKTRDY; //0x0a;

        MENTOR_LoadFIFO(hc, 0, td->xfer_buffer, td->xfer_length);
    }
    else
    {
        if (td->flags & PIPE_FLAGS_TOKEN_OUT)
        {
            if (r5->mps >= td->xfer_length)
            {
                length = td->xfer_length;
            }
            else
            {
                length = r5->mps;
            }

            td->bytes_xfered += length;

            if (length > 0)
            {
                MENTOR_LoadFIFO(hc, 0, td->xfer_buffer, length);
            }

            csr |= CSR0_TXPKTRDY;
        }
        else
        {
            csr |= CSR0_REQ_PKT;            
        }
    }

    HW_Write16(hc, MUSB_TXTYPE(0), r5->bData_0x1c);
    HW_Write16Or(hc, MUSB_CSR0, csr);
}


/* complete */
int mentor_ctrl_transfer_abort(void* chdl, 
    iousb_transfer_t* urb, 
    iousb_endpoint_t* iousbep)
{
    hctrl_t* hc/*r6*/ = ((struct _usb_hcd*)chdl)->hc_data;
    struct Struct_0xa4* r5;
    struct _musb_transfer* r4;

    MUSB_MUTEX_LOCK(Data_4, 0x435);
    if ((r5 = iousbep->user) == NULL)
    {
        MUSB_MUTEX_UNLOCK(Data_4, 0x438);
        return 2;
    }
    //4648
    HW_Write16(hc, MUSB_CSR0, CSR0_FLUSH_FIFO);

    MUSB_LOCK

    while ((r4 = r5->Data_8.sqh_first) != NULL)
    {
        //4666
        if ((r5->Data_8.sqh_first = r4->link.sqe_next) == NULL)
        {
            r5->Data_8.sqh_last = &r5->Data_8.sqh_first;
        }
        //466e
        r4->flags = 0;

        SIMPLEQ_INSERT_TAIL(&hc->transfer_free_q, r4, link);
    }
    //4680
    MUSB_UNLOCK

    hc->Data_0xd8[0] = 0;

    r5->Data_0x10 &= ~(1 << 0);

    MUSB_MUTEX_UNLOCK(Data_4, 0x449);
    //46ba
    return 0;
}


/* complete */
int mentor_ctrl_transfer(void* chdl, 
    iousb_transfer_t* urb/*sl*/, 
    iousb_endpoint_t* iousbep, 
    uint8_t* buffer/*fp*/, 
    uint32_t length/*sp48*/, 
    uint32_t flags/*sp52*/)
{
    hctrl_t* hc = ((struct _usb_hcd*)chdl)->hc_data;
    struct Struct_0xa4* r6 = iousbep->user;
    struct _musb_transfer* td; //r7;

#ifdef DEBUG_CTRL_TRANSFER
    mentor_slogf(NULL, 12, _SLOG_ERROR, 3, 
        ">>>>>>>>>>>> mentor_ctrl_transfer: length=%d",
        length);
#endif

    MUSB_MUTEX_LOCK(Data_0xc, 0x517);
    MUSB_MUTEX_LOCK(Data_4, 0x518);
    //4d0c
    if ((hc->Data_0x8c & 0x06) != 0x06)
    {
        MUSB_MUTEX_UNLOCK(Data_4, 0x51b);
        MUSB_MUTEX_UNLOCK(Data_0xc, 0x51c);
        urb->status = 0x2000005;
        return 0x13;
    }
    //4d62
    if ((td = MENTOR_TD_Setup(hc, urb, r6, flags)) == NULL) {
        MUSB_MUTEX_UNLOCK(Data_4, 0x522);
        MUSB_MUTEX_UNLOCK(Data_0xc, 0x523);
        //4db2
        urb->status = 0x2000010;

        return 0x0c;
    }
    //4dbc
    td->xfer_buffer = buffer;
    td->xfer_length = length;

    MUSB_LOCK

    SIMPLEQ_INSERT_TAIL(&r6->Data_8, td, link);

    if ((r6->Data_0x10 & (1 << 0)) == 0)
    {
        //4de4
        r6->Data_0x10 |= (1 << 0);
        r6->num = 0;

        hc->Data_0xd8[0] = td;

        MUSB_UNLOCK

        MENTOR_StartControlEtd(hc, SIMPLEQ_FIRST(&r6->Data_8));
        //->4e08
    }
    else
    {
        //4e02
        MUSB_UNLOCK
    }
    //4e08
    MUSB_MUTEX_UNLOCK(Data_4, 0x538);
    //4e28
    MUSB_MUTEX_UNLOCK(Data_0xc, 0x53a);
    //4e4a
    return 0;
}

