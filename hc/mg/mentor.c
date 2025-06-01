
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <gulliver.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/slog.h>
#include <sys/usbdi.h>
#include <pthread.h>
#include <queue.h>
#include <arm/mb86h60.h>


//_GLOBAL_OFFSET_TABLE_ //0x0000bd5c

struct _hctrl_t;
#define USB_CONTROLLER_PRIV_T struct _hctrl_t
#include <sys/io-usb.h>
#include "my-io-usb.h"
#include <sys/io-usb_dcd.h>



struct Struct_0xa4;
struct _musb_transfer;
struct Struct_0x94
{
    struct _musb_transfer* Data_0; //0
};


struct _musb_transfer_Inner_0x18_Inner_8
{
    int Data_0; //0
    int fill_4; //4
    int Data_8; //8
    //???
};

struct _musb_transfer_Inner_0x18
{
    uint16_t wData_0; //0
    int fill_4; //4
    struct _musb_transfer_Inner_0x18_Inner_8* Data_8; //8
    //???
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
    struct Struct_10bab4* Data_0x34; //0x34
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
    

struct Struct_0xe4_Inner_0x1c
{
    int Data_0; //0
    int Data_4; //4
    int Data_8; //8
    int Data_0xc__; //0xc
    int Data_0x10; //0x10
    int Data_0x14; //0x14
    int Data_0x18; //0x18
    int Data_0x1c; //0x1c
    int fill_0x20[2]; //0x20
    uint32_t Data_0x28; //0x28
    struct _musb_transfer* td; //0x2c
    struct Struct_0xa4* Data_0x30; //0x30
#if 0
    struct Struct_0xe4_Inner_0x1c* le_next; //0x34
    struct Struct_0xe4_Inner_0x1c** le_prev; //0x38
#else
    LIST_ENTRY(Struct_0xe4_Inner_0x1c) link; //0x34
#endif
    int fill_0x3c; //0x3c
    //0x40???
};

struct _bdbase
{
    struct Struct_0xe4_Inner_0x1c Data_0[2][512]; //0
};


struct Struct_0xe4
{
    void* Data_0; //0
    void* Data_4__; //4
    struct Struct_0xe4_Inner_0x1c* Data_8; //8
    uint8_t bData_0xc; //0xc
    int Data_0x10; //0x10
    int Data_0x14; //0x14
    LIST_HEAD(, Struct_0xe4_Inner_0x1c) dma_free_q; //0x18
    LIST_HEAD(, Struct_0xe4_Inner_0x1c) dma_active_q; //0x1c
    //0x20
};


struct Mentor_Controller_Inner_0x8c
{
    int fill_0[6]; //0
    struct fp_0x34_Inner_0x18
    {
        int fill_0[2]; //8
        int Data_8; //8
        uint32_t Data_0xc; //12 = 0xc
        struct fp_0x34_Inner_0x18_Inner_0x10
        {
            int Data_0; //0
            int Data_4; //4
            int Data_8; //8
            struct fp_0x34_Inner_0x18* Data_0xc; //0xc 
            //16 = 0x10
        }* Data_0x10; //16 = 0x10
        //0x14
    } Data_0x18[]; //0x18, size???
    //???
};


struct _hctrl_t
{
    struct USB_Controller* Data_0; //0
    pthread_mutex_t Data_4; //4
    pthread_mutex_t Data_0xc; //12
    void* Data_0x14; //0x14
    uint32_t Data_0x18; //0x18
    int fill_ox1c[3]; //0x1c
    int Data_0x28; //0x28
    int Data_0x2c; //0x2c
    int fill_0x30[2]; //0x30
    int Data_0x38; //0x38
    pthread_t Data_0x3c; //0x3c
    int chid; //0x40
    int coid; //0x44
    int irq; //0x48
    int intr_id; //0x4c
    int flags; //0x50
    int Data_0x54; //0x54
    int Data_0x58; //0x58
    struct sigevent intr_event; //0x5c
    int Data_0x6c; //0x6c
    uint32_t Data_0x70; //0x70
    uint32_t num_td; //0x74
    uint32_t verbosity; //0x78
    int Data_0x7c; //0x7c
    int fill_0x80; //0x80
    int Data_0x84; //0x84
    char* fconfig_string; //0x88
    struct Mentor_Controller_Inner_0x8c* Data_0x8c; //0x8c
    SIMPLEQ_HEAD(, _musb_transfer) transfer_free_q; //0x90
    SIMPLEQ_HEAD(, _musb_transfer) transfer_complete_q; //0x98
    void* transfer_mem; //0xa0
    struct Struct_0xa4* Data_0xa4; //0xa4
    struct Struct_0xa4* Data_0xa8; //0xa8
    struct Struct_0xa4* Data_0xac; //0xac
    struct Struct_0xa4* Data_0xb0; //0xb0
    struct Struct_0xa4* Data_0xb4; //0xb4
    struct Struct_0xa4* Data_0xb8; //0xb8
    struct Struct_0xa4* Data_0xbc; //0xbc
    struct Struct_0xa4* Data_0xc0; //0xc0
    struct _musb_transfer** Data_0xc4; //0xc4
    struct Struct_0xa4** Data_0xc8; //0xc8
    int fill_0xcc; //0xcc
    struct intrspin Data_0xd0; //0xd0
    uint16_t wData_0xd4; //0xd4
    int fill_0xd8[3]; //0xd8
    struct Struct_0xe4* dma_hdl; //0xe4
    //0xe8
};

#include "mentor.h"
#include "mu_hdrdf.h"


extern void MENTOR_LoadFIFO(struct _hctrl_t*, uint16_t, int, uint16_t);
extern void MENTOR_ReadFIFO(struct _hctrl_t*, struct _musb_transfer*, uint16_t, int, uint16_t);


#ifndef MB86H60

static const uint32_t dma_sched_table[15] = //0x0000bed0
{
    0x81018000, 0x83038202, 0x85058404, 0x87078606,
    0x89098808, 0x8b0b8a0a, 0x8d0d8c0c, 0x8f0f8e0e,
    0x91119010, 0x93139212, 0x95159414, 0x97179616,
    0x99199818, 0x9b1b9a1a, 0x9d1d9c1c
};

int dma_nums = 0; //0x0000c010
int g_dma_nums = 0; //0x0000c014
uint8_t usbss_intstat_Val[2]; //0x0000c018
uint32_t g_usb_tx_intr[2]; //0x0000c01c
void* g_teardownbd_paddr; //0x0000c024;
struct _bdbase* g_bdbase; //0x0000c028
uint32_t g_usb_rx_intr[2]; //0x0000c02c
void* g_linkram; //0x0000c034

#endif


#ifdef MB86H60

volatile uint8_t bUsbIntStatus;

void* dma_regs = NULL;
uint32_t dma_dwUsbMode = 0;


void dma_SetUsbIntMask(struct _hctrl_t* c, int a)
{
    ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_INT_MASK/sizeof(uint32_t)] = a;
}

uint32_t dma_GetUsbIntStatus(struct _hctrl_t* c)
{
    return ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_INT_STATUS/sizeof(uint32_t)];
}

void dma_SetUsbIntClear(struct _hctrl_t* c, int a)
{
    ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_INT_CLEAR/sizeof(uint32_t)] = a;
}

void dma_SetUsbMode_LengthInput(struct _hctrl_t* c, int a)
{
	int mask = MB86H60_DMA_USB_MODE_LENGTH_INPUT;
	a = (a << 1) & mask;

	dma_dwUsbMode = (dma_dwUsbMode & ~mask) | a;

    ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_MODE/sizeof(uint32_t)] = dma_dwUsbMode;
}

void dma_SetUsbMode_PacedEpWriteChannel(struct _hctrl_t* c, uint32_t value)
{
    uint32_t mask = MB86H60_DMA_USB_MODE_PACED_EP_WRITE_CHANNEL;
    value = (value << 3) & mask;

    dma_dwUsbMode = (dma_dwUsbMode & ~mask) | value;

    ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_MODE/sizeof(uint32_t)] = dma_dwUsbMode;
}


void dma_SetUsbMode_PacedEpReadChannel(struct _hctrl_t* c, uint32_t value)
{
    uint32_t mask = MB86H60_DMA_USB_MODE_PACED_EP_READ_CHANNEL;
    value = (value << 5) & mask;

    dma_dwUsbMode = (dma_dwUsbMode & ~mask) | value;

    ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_USB_MODE/sizeof(uint32_t)] = dma_dwUsbMode;
}


uint8_t MGC_Read8(struct _hctrl_t* c, uint16_t offset)
{
    uint8_t data;
	dma_SetUsbMode_LengthInput(c, 0);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
    return data;
}


uint16_t MGC_Read16(struct _hctrl_t* c, uint16_t offset)
{
    uint16_t data;
	dma_SetUsbMode_LengthInput(c, 1);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
    return data;
}


uint32_t MGC_Read32(struct _hctrl_t* c, uint16_t offset)
{
    uint32_t data;
	dma_SetUsbMode_LengthInput(c, 2);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
    return data;
}


void MGC_Write8(struct _hctrl_t* c, uint16_t offset, uint8_t data)
{
	dma_SetUsbMode_LengthInput(c, 0);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
}


void MGC_Write16(struct _hctrl_t* c, uint16_t offset, uint16_t data)
{
	dma_SetUsbMode_LengthInput(c, 1);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
}


void MGC_Write32(struct _hctrl_t* c, uint16_t offset, uint32_t data)
{
	dma_SetUsbMode_LengthInput(c, 2);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
}

#endif //MB86H60



/* 0x0000611c - complete */
int mentor_slogf(struct _hctrl_t* a, 
        int opcode, int severity, int verbosity,
        const char* fmt, ...)
{
    int res;

    if (a->verbosity < verbosity)
    {
        return 0;
    }

    va_list arglist;

    va_start(arglist, fmt);
#if 0
    res = vslogf(opcode, severity, fmt, arglist);
#else
    res = vfprintf(stderr, fmt, arglist);
    fprintf(stderr, "\n");
#endif
    va_end( arglist );
    return res;
}


/* 0x00004cbc - todo */
void MENTOR_ProcessControlDone(struct _hctrl_t* r5)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessControlDone: TODO\n");
#endif

    struct _musb_transfer* r4 = r5->Data_0xc4[0];
    if (r4 == NULL)
    {
        //->loc_4ee8
        return;
    }

    struct Struct_0xa4* r6 = r4->Data_0x30;
    
    if (r6->bData_0x1f != 0)
    {
        //->loc_4ee8
        return;
    }
    //0x00004cf0
    int status; //r8
    uint16_t wCsr; //r7

    wCsr = HW_Read16(r5, MUSB_CSR0);

    status = (wCsr & (1 << 2)/*RxStall*/)? USBD_STATUS_STALL: 0;

    if (wCsr & ((1 << 7)/*NAK Timeout*/ | (1 << 4)/*Error*/))
    {
        status = USBD_STATUS_NOT_ACCESSED;
        //->loc_4e3c
    }
    //0x00004d10
    if (status == 0)
    {
        //0x00004d18
        if (r4->flags & PIPE_FLAGS_TOKEN_IN) //4)
        {
            //0x00004d24
            uint16_t sl;
            sl = HW_Read16(r5, MUSB_COUNT0);
#if 0 //No printf in ISR
            fprintf(stderr, "MENTOR_ProcessControlDone: sl=%d\n", sl);
#endif
            int sb = sl;

            if (sl > (uint32_t)(r4->xfer_length - r4->bytes_xfered))
            {
                status = USBD_STATUS_DATA_OVERRUN;
                //->0x00004e3c
            }
            else if (/*sl*/sb > 0)
            {
                //0x00004d50
                MENTOR_ReadFIFO(r5, r4, 0, 
                    r4->xfer_buffer + r4->bytes_xfered,
                    sl);

                r4->bytes_xfered += sl;

                if ((r6->mps == sl) && (r4->xfer_length > r4->bytes_xfered))
                {
                    //0x00004d94
                    HW_Write16(r5, MUSB_CSR0, wCsr | 0x20);
                    //->loc_4ee8
                    return;
                }
                //0x00004e3c
            }
            //->0x00004e3c
        } //if (r4->flags & PIPE_FLAGS_TOKEN_IN) //4)
        //loc_4dac
        else if (r4->flags & PIPE_FLAGS_TOKEN_OUT) //8)
        {
            //0x00004db8
            if (r4->xfer_length > r4->bytes_xfered)
            {
                //0x00004dc8
                uint32_t r6_ = r6->mps;
                if (r6_ >= (r4->xfer_length - r4->bytes_xfered))
                {
                    r6_ = r4->xfer_length - r4->bytes_xfered;
                }

                MENTOR_LoadFIFO(r5, 0, 
                    r4->xfer_buffer + r4->bytes_xfered,
                    r6_);

                r4->bytes_xfered += r6_;

                HW_Write16(r5, MUSB_CSR0, HW_Read16(r5, MUSB_CSR0) | 0x02);
                //->loc_4ee8
                return;
            }
            //loc_4e3c
        } //else if (r4->flags & PIPE_FLAGS_TOKEN_OUT) //8)
        //loc_4e2c
        else if (r4->flags & PIPE_FLAGS_TOKEN_SETUP) //1)
        {
            r4->bytes_xfered = r4->xfer_length;
        } //else if (r4->flags & 1)
    } //if (status == 0)
    //loc_4e3c
    r6->Data_0x20 = (wCsr >> 9) & 1;

    HW_Write16(r5, MUSB_CSR0, 0);

    InterruptLock(&r5->Data_0xd0);

    r5->Data_0xc4[0] = NULL;

    r6->Data_8__ = SIMPLEQ_NEXT(r4, link);
    if (r6->Data_8__ == 0)
    {
        r6->Data_0xc = &r6->Data_8__;
    }
    r6->Data_0x10 &= ~0x01;

    r4->status = status;

    SIMPLEQ_INSERT_TAIL(&r5->transfer_complete_q, r4, link);

    InterruptUnlock(&r5->Data_0xd0);
    //loc_4ee8
    return;
}


/* 0x00004220 - todo */
struct fp_0x34_Inner_0x18_Inner_0x10* mentor_fifo_alloc(struct _hctrl_t* r5,
        int fp_0x2c, 
        struct Struct_0xa4* c,
        int fp_0x30)
{
#if 0
    fprintf(stderr, "mentor_fifo_alloc: TODO!!!\n");
#endif

    struct fp_0x34_Inner_0x18_Inner_0x10* r0 = NULL;
    int r8;
    uint32_t r3;
    struct Mentor_Controller_Inner_0x8c* r4 = r5->Data_0x8c;
    int r6 = c->mps;
    //r7 = 0x24;
    //sb = 0x20;
    //->loc_4364
    while ((r8/*r0*/ = find_block_list(r4, r6)) != -1)
    {
        //loc_4250
#if 1
        fprintf(stderr, "mentor_fifo_alloc: r6=%d, fifo_size=%d\n", r6, r8);
#endif
        uint32_t sl = r4->Data_0x18[r8].Data_0xc;
        for (r3 = 0; r3 < r4->Data_0x18[r8].Data_8; r3++)
        {
#if 1
            fprintf(stderr, "mentor_fifo_alloc: r3=%d, sl=0x%04x\n", r3, sl);
#endif
            //if (sl & (1 << r3))
            if (sl & 1)
            {
                r4->Data_0x18[r8].Data_0xc = sl & ~(1 << r3);

#if 1
                fprintf(stderr, "mentor_fifo_alloc: fp_0x30=%d, ep=%d, fifo_add=%d\n", 
                    fp_0x30, fp_0x2c, r4->Data_0x18[r8].Data_0x10[r3].Data_4);
#endif

#ifdef MB86H60
                //MGC_SelectEnd(r5, fp_0x2c & 0xff);
                MGC_Write8(r5, MGC_O_HDRC_INDEX, fp_0x2c & 0xff);
#else
                ((volatile uint8_t*)(r5->Data_0x14))[0x0e/*INDEX*/] = fp_0x2c & 0xff;
#endif

                if (fp_0x30 != 0)
                {
                    //0x000042c0
#ifdef MB86H60
#if 0 //Dynfifo!
                    MGC_Write8(r5, MGC_O_HDRC_RXFIFOSZ, r8/*r0*/ & 0xff);
                    HW_Write16(r5, MGC_O_HDRC_RXFIFOADD, 
                        (r4->Data_0x18[r8].Data_0x10[r3].Data_4 << 13) >> 16);
#endif
#else
                    ((volatile uint8_t*)(r5->Data_0x14))[0x63/*RXFIFOSZ*/] = r8/*r0*/ & 0xff;
                    ((volatile uint16_t*)(r5->Data_0x14))[0x66/2/*RXFIFOADD*/] = 
                        (r4->Data_0x18[r8].Data_0x10[r3].Data_4 << 13) >> 16;
#endif
                    //->loc_4334
                }
                else
                {
                    //loc_42fc
#ifdef MB86H60
#if 0 //Dynfifo!
                    MGC_Write8(r5, MGC_O_HDRC_TXFIFOSZ, r8/*r0*/ & 0xff);
                    HW_Write16(r5, MGC_O_HDRC_TXFIFOADD, 
                        (r4->Data_0x18[r8].Data_0x10[r3].Data_4 << 13) >> 16);
#endif
#else
                    ((volatile uint8_t*)(r5->Data_0x14))[0x62/*TXFIFOSZ*/] = r8/*r0*/ & 0xff;
                    ((volatile uint16_t*)(r5->Data_0x14))[0x64/2/*TXFIFOADD*/] = 
                        (r4->Data_0x18[r8].Data_0x10[r3].Data_4 << 13) >> 16;
#endif
                }
                //loc_4334
                r0 = &r4->Data_0x18[r8].Data_0x10[r3];
                //->loc_437c
                return r0;
            }
            
            sl >>= 1;
        } //for (r3 = 0; r3 < r4->Data_0x18[r8].Data_8; r3++)
        //loc_4360
        r6 *= 2;
    } //while ((r8/*r0*/ = find_block_list(r4, r6)) != -1)
    //0x00004378
    return r0;
}


/* 0x00008284 - todo */
int MENTOR_AllocEtd(struct _hctrl_t* r5, 
        struct Struct_0xa4* r6, 
        int r8)
{
#if 1
    fprintf(stderr, "MENTOR_AllocEtd: TODO!!!\n");
#endif

    int r4 = r6->num;
    if ((r4 > 0) && (r4 < r5->Data_0x18))
    {
        //->loc_84f0
        return r4;
    }
    //loc_82b4
    for (r4 = 1; (r4 < r5->Data_0x18) && (r5->Data_0xc8[r4] != NULL); r4++)
    {
    }

    if (r4 >= r5->Data_0x18)
    {
        //loc_8304
        int r3 = r5->wData_0xd4;
        if (r3 != 0)
        {
            //0x00008310
            for (r4 = 1; (r4 < r5->Data_0x18) && 
                (r5->Data_0xc8[r4]->Data_0x10 & 0x01); r4++)
            {
                //loc_832c
            }

            if (r4 >= r5->Data_0x18)
            {
                //->loc_84ec
                return -1;
            }
            //loc_8344
            if (MENTOR_FreeEtd(r5, r5->Data_0xc8[r4]) < 0)
            {
                //0x000083f8
                mentor_slogf(r5, 12, 2, 1, 
                    "%s - %s: Trying to relinquish an unreserved ETD failed",
                    "devu-dm816x-mg.so", "MENTOR_AllocEtd");
            }
            //loc_8390
            r5->wData_0xd4 = 0;
            //->loc_8464
        }
        else
        {
            //loc_83b8
            for (r4 = 1; (r4 < r5->Data_0x18) && 
                (r5->Data_0xc8[r4]->Data_0x10 & 0x01); r4++)
            {
            }

            if (r4 >= r5->Data_0x18)
            {
                //->loc_84ec
                return -1;
            }
            //loc_83e8
            if (MENTOR_FreeEtd(r5, r5->Data_0xc8[r4]) < 0)
            {
                //0x000083f8
                mentor_slogf(r5, 12, 2, 1, 
                    "%s - %s: Trying to relinquish an unreserved ETD failed",
                    "devu-dm816x-mg.so", "MENTOR_AllocEtd");
            }
            //loc_8434
            r5->wData_0xd4 = 1;
            //->loc_8464
        }
    }
    //loc_8464
    r6->Data_0x30 = mentor_fifo_alloc(r5, r4, r6, r8);
    if (r6->Data_0x30 == 0)
    {
        //0x00008484
        mentor_slogf(r5, 12, 2, 1, 
            "%s - %s: Allocate FIFO failed, bEnd=%d, maxPacketSize=%d",
            "devu-dm816x-mg.so", "MENTOR_AllocEtd",
            r4, r6->mps);

        r4 = -1;
        //->loc_84f0
    }
    else
    {
        //loc_84d4
        r6->num = r4;
        r6->bData_0x1f = 0;
        r5->Data_0xc8[r4] = r6;
    }
    //loc_84f0
    return r4;
}


void MENTOR_EtdConfigureTX(struct _hctrl_t* a, 
    struct Struct_0xa4* b, int c)
{
#if 0
    fprintf(stderr, "MENTOR_EtdConfigureTX: TODO!!!\n");
#endif

    int r4 = b->transferType;
    int r3 = c * 16;

    HW_Write16(a, 0x106 + r3, 0);

    if (b->Data_0x20 != 0)
    {
        //0x00004794
        HW_Write16(a, 0x102 + r3, 0x2308);
        //->loc_47c8
    }
    else
    {
        //loc_47b0
        HW_Write16(a, 0x102 + r3, 0x2048);
    }
    //loc_47c8
    int r2 = c * 8;

    HW_Write16(a, 0x80 + r2, (b->Data_0x14 >> 4) & 0x7f);

    if (b->bData_0x1c & 0x40)
    {
        //0x000047f4
        HW_Write8(a, 0x82 + r2, b->bData_0x1d);
        HW_Write8(a, 0x83 + r2, b->bData_0x1e);
    }
    //loc_481c
    HW_Write16(a, 0x10a + r3, 
        (r4 << 4) | (b->Data_0x14 & 0x0f) | b->bData_0x1c);
    
    if (r4 & 0x01)
    {
        //0x00004854
        HW_Write8(a, 0x10b + r3, b->Data_0x24);
    }
    else
    {
        //loc_4870
        HW_Write8(a, 0x10b + r3, 0);
    }
    //loc_4888
}


/* 0x00004898 - todo */
void MENTOR_EtdConfigureRX(struct _hctrl_t* a, 
    struct Struct_0xa4* b, int c)
{
#if 1
    fprintf(stderr, "MENTOR_EtdConfigureRX: c=%d, addr=%d\n", 
        c, (b->Data_0x14 >> 4) & 0x7f);
#endif

    int r4 = b->transferType;
    int r3 = c * 16;

    HW_Write16(a, 0x102 + r3, 0);

    int r2 = c * 8;
#ifdef MB86H60
    MGC_Write8(a, 0x84 + c*8, (b->Data_0x14 >> 4) & 0x7f);
//    MGC_Write16(a, /*0x84 + r2*/MGC_BUSCTL_OFFSET(c, MGC_O_HDRC_RXFUNCADDR), 
//        (b->Data_0x14 >> 4) & 0x7f);
#else
    ((volatile uint16_t*)(a->Data_0x14))[0x84/2 + r2] = (b->Data_0x14 >> 4) & 0x7f;
#endif

    if (b->bData_0x1c != 0x40)
    {
        //0x000048e8
#ifdef MB86H60
        MGC_Write8(a, /*0x86 + r2*/MGC_BUSCTL_OFFSET(c, MGC_O_HDRC_RXHUBADDR), 
            b->bData_0x1d);
        MGC_Write8(a, /*0x87 + r2*/MGC_BUSCTL_OFFSET(c, MGC_O_HDRC_RXHUBPORT), 
            b->bData_0x1e);
#else
        ((volatile uint8_t*)(a->Data_0x14))[0x86 + r2] = b->bData_0x1d;
        ((volatile uint8_t*)(a->Data_0x14))[0x87 + r2] = b->bData_0x1e;
#endif
    }
    //loc_4910: Write RXTYPE
    uint8_t rxType = b->bData_0x1c | (r4 << 4) | (b->Data_0x14 & 0x0f);

#if 1
    fprintf(stderr, "MENTOR_EtdConfigureRX: rxType=0x%x, speed=0x%0x, protocol=%d, ep=%d\n", 
        rxType, b->bData_0x1c, r4, b->Data_0x14 & 0x0f);
#endif

#ifdef MB86H60
    MGC_Write8(a, 0x1c, rxType);
//    MGC_Write8(a, 0x10c + r3, rxType);
#else
    ((volatile uint8_t*)(a->Data_0x14))[0x10c + r3] = rxType;
#endif

#ifdef MB86H60
    MGC_Read16(a, 0x16);
//    int r2_ = MGC_Read16(a, 0x106 + r3);
#else
    int r2_ = ((volatile uint16_t*)(a->Data_0x14))[0x106/2 + r3];
#endif

    if (r4 & 0x01)
    {
#ifdef MB86H60
        MGC_Write8(a, 0x1d, b->Data_0x24); //RXINTERVAL
//        MGC_Write8(a, 0x10d + r3, b->Data_0x24); //RXINTERVAL
#else
        ((volatile uint8_t*)(a->Data_0x14))[0x10d + r3] = b->Data_0x24;
#endif
    }
    else
    {
#ifdef MB86H60
        MGC_Write8(a, 0x1b, 0); //TXINTERVAL

//        MGC_Write8(a, 0x10b + r3, 0); //TXINTERVAL
#else
        ((volatile uint8_t*)(a->Data_0x14))[0x10b + r3] = 0;
#endif
    }

    if (b->Data_0x20 != 0)
    {
        //0x0000497c
#ifdef MB86H60
        MGC_Write16(a, 0x16, 0x610);
//        MGC_Write16(a, 0x106 + r3, 0x610);
#else
        ((volatile uint16_t*)(a->Data_0x14))[0x106/2 + r3] = 0x610;
#endif
        //->loc_49b0
    }
    else
    {
        //loc_4998
#ifdef MB86H60
        MGC_Write16(a, 0x16, 0x90);
//        MGC_Write16(a, 0x106 + r3, 0x90);
#else
        ((volatile uint16_t*)(a->Data_0x14))[0x106/2 + r3] = 0x90;
#endif
    }
    //loc_49b0
#ifdef MB86H60
    MGC_Write16(a, 0x16, 0x10);
//    MGC_Write16(a, 0x106 + r3, 0x10);
#else
    ((volatile uint16_t*)(a->Data_0x14))[0x106/2 + r3] = 0x10;
#endif
}


/* 0x00006cc0 - todo */
void MENTOR_StartEtd(struct _hctrl_t* r4, 
    struct _musb_transfer* r6)
{
#if 0
    fprintf(stderr, "MENTOR_StartEtd: TODO!!!\n");
#endif

    struct Struct_0xa4* r8 = r6->Data_0x30;

#if 1
    fprintf(stderr, "MENTOR_StartEtd: r8=%p, r8->num=%d\n",
        r8, r8->num);
#endif

    if (r8->num >= 0)
    {
        //0x00006cf4
        r8->bData_0x1f = 0;

        int ep_num/*fp_0x30*/ = r8->num;
        r4->Data_0xc4[ep_num] = r6;
        r6->flags |= 0x100;

        int r7 = ep_num * 16;

        uint16_t wCsr;
        int retry/*r5*/ = 1000;
        while (((wCsr = HW_Read16(r4, 0x102 + r7)) & 0x03) && retry--)
        {
            //loc_6d68
#if 0
            fprintf(stderr, "MENTOR_StartEtd: r7=%d, wCsr=0x%04x, retry=%d\n", r7, wCsr, retry);
#endif
            nanospin_ns(1000);
        }

#if 0
        fprintf(stderr, "MENTOR_StartEtd: r7=%d, wCsr=0x%04x, retry=%d\n", r7, wCsr, retry);
#endif

        if (retry <= 0)
        {
            //loc_6d9c
            mentor_slogf(r4, 12, 2, 1, 
                " %s : MENTOR_StartEtd - %s: TX FIFO still not Empty (%x)",
                "devu-dm816x-mg.so", "MENTOR_StartEtd", wCsr);
        }
        //loc_6de0
        uint32_t r5 = r6->xfer_length - r6->bytes_xfered;

#if 1
        fprintf(stderr, "MENTOR_StartEtd: r5=%d, r6->flags=0x%x\n",
            r5, r6->flags);
#endif

        if ((r6->flags & 0x400) &&
            (r4->flags & 0x200) &&
            (r5 > r8->mps) &&
            ((r8->mps & 0x3f) == 0) &&
            (r8->transferType == USB_ATTRIB_BULK)) //2))
        {
            //0x00006e24
            r6->Data_0x10 = r5;
            r6->flags |= 0x800;
            //->loc_6e58
        }
        else
        {
            //loc_6e38
            r6->flags &= ~0x800;

            if (r5 > r8->Data_0x30->Data_0)
            {
#if 0
                fprintf(stderr, "MENTOR_StartEtd: r8->Data_0x30->Data_0=%d\n",
                    r8->Data_0x30->Data_0);
#endif
                r5 = r8->Data_0x30->Data_0;
            }
            r6->Data_0x10 = r5;
        }
        //loc_6e58
        if (r6->flags & 0x04)
        {
            //0x00006e64
            int sb = HW_Read16(r4, 0x106 + r7);
#if 1
            fprintf(stderr, "MENTOR_StartEtd: 0x106 -> 0x%x\n", sb);
#endif

            if ((r8->transferType == USB_ATTRIB_ISOCHRONOUS/*1*/) || 
                (r8->transferType == USB_ATTRIB_INTERRUPT/*3*/))
            {
                sb |= (1 << 12); //0x1000; /* PID Error ?*/
            }

            if (r6->flags & 0x800)
            {
                //0x00006e94: write RXMAXP
#if 1
                fprintf(stderr, "MENTOR_StartEtd: 0x104 <- 0x%x\n", r8->mps);
#endif
                HW_Write16(r4, 0x104 + r7, r8->mps);
                HW_Write16(r4, 0x106 + r7, sb & 0x2792);

                if (r6->flags & 0x400)
                {
                    //0x00006ec8
                    mentor_start_dma_transfer(r4, r8, r6, 1,
                        ep_num, r8->Data_0x2c, 
                        r6->xfer_buffer_paddr + r6->bytes_xfered, 
                        r5);
                }
                //loc_6f00
                uint32_t r0 = HW_Read16(r4, 0x106 + r7);
                r0 |= RXCSR_DMA_REQ_EN 
//                    | RXCSR_AUTOREQ | RXCSR_AUTOCLEAR
//                    | RXCSR_DMA_REQ_MODE
                    | 0x6d;
//                r0 &= ~RXCSR_REQ_PKT;
#if 1
                fprintf(stderr, "MENTOR_StartEtd: 0x106 <- 0x%x\n", r0);
#endif
                HW_Write16(r4, 0x106 + r7, r0);
                //->loc_71bc
            } //if (r6->flags & 0x800)
            else
            {
                //loc_6f24
                uint32_t m = 0;
                int r0 = (r6->Data_0x10 / r8->mps) -1;
                if (r0 > 0)
                {
                    m = (r6->Data_0x10 / r8->mps) - 1;
                }
                //loc_6f58: write RXMAXP
#if 0
                fprintf(stderr, "MENTOR_StartEtd: 0x104 <- 0x%x\n", r8->mps | (m << 11));
#endif
                HW_Write16(r4, 0x104 + r7, r8->mps | (m << 11));

                int sl;
                if ((r6->flags & 0x400) == 0)
                {
                    sl = sb & 0x9fff;
                    //->loc_6fc8
                }
                else
                {
                    //0x00006f84
                    sl = sb & 0x2792;
                    sl |= (RXCSR_DMA_REQ_EN | RXCSR_AUTOREQ); //0x6000;

                    mentor_start_dma_transfer(r4, r8, r6, 1,
                        ep_num, r8->Data_0x2c,
                        r6->xfer_buffer_paddr + r6->bytes_xfered,
                        r5);
                }
                //loc_6fc8: write RxCSR
#if 1
                fprintf(stderr, "MENTOR_StartEtd: 0x106 <- 0x%x\n",
                    sl | 0x6d);
#endif
                HW_Write16(r4, 0x106 + r7, sl | 0x6d); //01101101
                    //Clear: RxStall, DataError/NAK Timeout, Error, RxPktRdy
                    //Set: ReqPkt
            }
            //->loc_71bc
        } //if (r6->flags & 0x04)
        else
        {
            //loc_6fe4
            uint32_t m = 0;
            //uint32_t sl = r8->mps;
            int r0_ = ((r6->Data_0x10 + r8->mps - 1) / r8->mps) - 1;
            if (r0_ > 0)
            {
                m = ((r6->Data_0x10 + r8->mps - 1) / r8->mps) - 1;
            }
            //loc_7024
            int txCsr/*sb*/ = HW_Read16(r4, 0x102 + r7);

            if (r6->flags & 0x600)
            {
                //0x00007044
                if (r6->flags & 0x800)
                {
                    //0x00007050
                    HW_Write16(r4, 0x100 + r7, r8->mps);

                    int r3 = (txCsr & 0x7b5a) | TXCSR_MODE/*0x2000*/;
                    HW_Write16(r4, 0x102 + r7, r3);

                    mentor_start_dma_transfer(r4, r8, r6, 1,
                        ep_num, r8->Data_0x2c, 
                        r6->xfer_buffer_paddr + r6->bytes_xfered, r5);

                    HW_Write16(r4, 0x102 + r7, 
                        HW_Read16(r4, 0x102 + r7) |
                        TXCSR_AUTOSET |
                        TXCSR_DMA_REQ_EN | //0x1480
                        TXCSR_DMA_REQ_MODE |
                        TXCSR_NAK_TIMEOUT |
                        TXCSR_RX_STALL | //0x26
                        TXCSR_ERROR |
                        TXCSR_FIFO_NOT_EMPTY);
                    //->loc_71bc
                } //if (r6->flags & 0x800)
                else
                {
                    //loc_70d0
                    HW_Write16(r4, 0x100 + r7, r8->mps | (m << 11));

                    if (r6->flags & 0x400)
                    {
                        //0x000070f0
                        int r2 = (txCsr | 
                            TXCSR_AUTOSET |
                            TXCSR_MODE | //0x3000
                            TXCSR_DMA_REQ_EN);
                        HW_Write16(r4, 0x102 + r7, 
                            (r2 & ~TXCSR_DMA_REQ_MODE/*0x400*/) |
                            TXCSR_NAK_TIMEOUT | //0xa6
                            TXCSR_RX_STALL |
                            TXCSR_ERROR |
                            TXCSR_FIFO_NOT_EMPTY);
                    }
                    //loc_7118
                    mentor_start_dma_transfer(r4, r8, r6, 
                        ((r6->flags >> 9) ^ 1) & 0x01,
                        ep_num, r8->Data_0x2c,
                        r6->xfer_buffer_paddr + r6->bytes_xfered, r5);
                    //->loc_71bc
                }
            } //if (r6->flags & 0x600)
            else
            {
                //loc_7160
                HW_Write16(r4, 0x100 + r7, r8->mps | (m << 11));

                MENTOR_LoadFIFO(r4, ep_num, r6->xfer_buffer, r5);

                HW_Write16(r4, 0x102 + r7, 
                    (txCsr & ~0x9400) | 0x2080 | 
                    TXCSR_RX_STALL | //0x27
                    TXCSR_ERROR |
                    TXCSR_FIFO_NOT_EMPTY |
                    TXCSR_TXPKTRDY);
            }
        }
    }
    //loc_71bc
}


/* 0x00006cc0 - todo */
void MENTOR_RestartEtd(struct _hctrl_t* r4, 
    struct _musb_transfer* r6)
{
#if 0
    fprintf(stderr, "MENTOR_RestartEtd: TODO!!!\n");
#endif

    //fp_0x2c = _GLOBAL_OFFSET_TABLE_;

    struct Struct_0xa4* r8 = r6->Data_0x30;

#if 0
    fprintf(stderr, "MENTOR_RestartEtd: r8=%p, r8->num=%d\n",
        r8, r8->num);
#endif

    if (r8->num >= 0)
    {
        //0x00006cf4
        r8->bData_0x1f = 0;

        //int ep/*fp_0x30*/ = r8->num;
        r4->Data_0xc4[r8->num] = r6;
        r6->flags |= 0x100;

        int r7 = r8->num * 16;

        uint16_t wCsr;
        int retry/*r5*/ = 1000;
        while (((wCsr = HW_Read16(r4, 0x102 + r7)) & 0x03) && retry--)
        {
            //loc_6d68
            nanospin_ns(1000);
        }

        if (retry <= 0)
        {
            //loc_6d9c
            mentor_slogf(r4, 12, 2, 1, 
                " %s : MENTOR_RestartEtd - %s: TX FIFO still not Empty (%x)",
                "devu-dm816x-mg.so", "MENTOR_RestartEtd", wCsr);
        }
        //loc_6de0
        uint32_t r5 = r6->xfer_length - r6->bytes_xfered;

#if 0
        fprintf(stderr, "MENTOR_RestartEtd: r5=%d, r6->flags=0x%x\n",
            r5, r6->flags);
#endif

        if ((r6->flags & 0x400) &&
            (r4->flags & 0x200) &&
            (r5 > r8->mps) &&
            ((r8->mps & 0x3f) == 0) &&
            (r8->transferType == USB_ATTRIB_BULK)) //2))
        {
            //0x00006e24
            r6->Data_0x10 = r5;
            r6->flags |= 0x800;
            //->loc_6e58
        }
        else
        {
            //loc_6e38
            r6->flags &= ~0x800;

            if (r5 > r8->Data_0x30->Data_0)
            {
#if 0
                fprintf(stderr, "MENTOR_RestartEtd: r8->Data_0x30->Data_0=%d\n",
                    r8->Data_0x30->Data_0);
#endif
                r5 = r8->Data_0x30->Data_0;
            }
            r6->Data_0x10 = r5;
        }
        //loc_6e58
        if (r6->flags & 0x04)
        {
            //0x00006e64
            int sb = HW_Read16(r4, 0x106 + r7);
#if 0
            fprintf(stderr, "MENTOR_RestartEtd: 0x106 -> 0x%x\n", sb);
#endif

            if ((r8->transferType == USB_ATTRIB_ISOCHRONOUS/*1*/) || 
                (r8->transferType == USB_ATTRIB_INTERRUPT/*3*/))
            {
                sb |= (1 << 12); //0x1000; /* PID Error ?*/
            }

            if (r6->flags & 0x800)
            {
                //0x00006e94
                HW_Write16(r4, 0x104 + r7, r8->mps);
                HW_Write16(r4, 0x106 + r7, sb & 0x2792);

                if (r6->flags & 0x400)
                {
                    //0x00006ec8
                    mentor_start_dma_transfer(r4, r8, r6, 1,
                        r8->num, r8->Data_0x2c, 
                        r6->xfer_buffer_paddr + r6->bytes_xfered, 
                        r5);
                }
                //loc_6f00
                uint32_t r0 = HW_Read16(r4, 0x106 + r7);
                r0 |= RXCSR_DMA_REQ_EN 
//                    | RXCSR_AUTOREQ | RXCSR_AUTOCLEAR
                    | 0x6d;
                HW_Write16(r4, 0x106 + r7, r0);
                //->loc_71bc
            } //if (r6->flags & 0x800)
            else
            {
                //loc_6f24
                uint32_t m = 0;
                int r0 = (r6->Data_0x10 / r8->mps) -1;
                if (r0 > 0)
                {
                    m = (r6->Data_0x10 / r8->mps) - 1;
                }
                //loc_6f58: write RXMAXP
                HW_Write16(r4, 0x104 + r7, r8->mps | (m << 11));

                int sl;
                if ((r6->flags & 0x400) == 0)
                {
                    sl = sb & 0x9fff;
                    //->loc_6fc8
                }
                else
                {
                    //0x00006f84
                    sl = sb & 0x2792;
                    sl |= (RXCSR_DMA_REQ_EN | RXCSR_AUTOREQ); //0x6000;

                    mentor_start_dma_transfer(r4, r8, r6, 1,
                        r8->num, r8->Data_0x2c,
                        r6->xfer_buffer_paddr + r6->bytes_xfered,
                        r5);
                }
                //loc_6fc8: write RxCSR
                HW_Write16(r4, 0x106 + r7, sl | 0x6d); //01101101
                    //Clear: RxStall, DataError/NAK Timeout, Error, RxPktRdy
                    //Set: ReqPkt
            }
            //->loc_71bc
        } //if (r6->flags & 0x04)
        else
        {
            //loc_6fe4
            uint32_t m = 0;
            int r0_ = (r6->Data_0x10 - 1 + r8->mps) / r8->mps;
            if ((r0_ - 1) > 0)
            {
                m = ((r6->Data_0x10 - 1 + r8->mps) / r8->mps) - 1;
            }
            //loc_7024
            int sb = HW_Read16(r4, 0x102 + r7);

            if (r6->flags & 0x600)
            {
                //0x00007044
                if (r6->flags & 0x800)
                {
                    //0x00007050
                    HW_Write16(r4, 0x100 + r7, r8->mps);

                    int r3 = (sb & 0x7b5a) | 0x2000;
                    HW_Write16(r4, 0x102 + r7, r3);

                    mentor_start_dma_transfer(r4, r8, r6, 1, 
                        r8->num, r8->Data_0x2c, 
                        r6->xfer_buffer_paddr + r6->bytes_xfered, r5);

                    HW_Write16(r4, 0x102 + r7, 
                        HW_Read16(r4, 0x102 + r7) |
                        0x1480 | 0x26);
                    //->loc_71bc
                } //if (r6->flags & 0x800)
                else
                {
                    //loc_70d0
                    HW_Write16(r4, 0x100 + r7, r8->mps | (m << 11));

                    if (r6->flags & 0x400)
                    {
                        //0x000070f0
                        int r2 = (sb | 0x3000);
                        HW_Write16(r4, 0x102 + r7, (r2 & ~0x400) |
                            0xa6);
                    }
                    //loc_7118
                    mentor_start_dma_transfer(r4, r8, r6, 
                        ((r6->flags >> 9) ^ 1) & 0x01,
                        r8->num, r8->Data_0x2c,
                        r6->xfer_buffer_paddr + r6->bytes_xfered, r5);
                    //->loc_71bc
                }
            } //if (r6->flags & 0x600)
            else
            {
                //loc_7160
                HW_Write16(r4, 0x100 + r7, r8->mps | (m << 11));

                MENTOR_LoadFIFO(r4, r8->num, r6->xfer_buffer, r5);

                HW_Write16(r4, 0x102 + r7, 
                    (sb & ~0x9400) | 0x2080 | 0x27);
            }
        }
    }
    //loc_71bc
}


/* 0x000025c8 - todo */
int mentor_start_dma_transfer(struct _hctrl_t* r0, 
    struct Struct_0xa4* r1, struct _musb_transfer* td/*r2*/, int rx/*r3*/,
    int ep/*r4*//*sp_0x2c*/, int f/*sp_0x30*/, 
    uint32_t start_addr_paddr/*r6*//*sp_0x34*/, uint32_t length/*r5*//*sp_0x38*/)
{
#if 0
    fprintf(stderr, "mentor_start_dma_transfer: rx=%d, ep=%d, f=%d, start_addr_paddr=0x%x, length=%d\n",
        rx, ep, f, start_addr_paddr, length);
#endif

    struct Struct_0xe4* ip = r0->dma_hdl;

    InterruptLock(&r0->Data_0xd0);

    struct Struct_0xe4_Inner_0x1c* r3 = ip->dma_free_q.lh_first;
    if (r3 == NULL)
    {
        //0x00002624
        InterruptUnlock(&r0->Data_0xd0);
        return 12; //->0x000028d8
    }
    //0x00002640
    LIST_REMOVE(r3, link);
    LIST_INSERT_HEAD(&ip->dma_active_q, r3, link);

    InterruptUnlock(&r0->Data_0xd0);

#ifdef MB86H60

    int channel = 3;
    int ch_offset = 0x40 * channel;

    uint32_t fifo_addr = 0x880 + (ep << 4);
    uint32_t maxPacketSize = r1->mps;

    uint32_t line = length / maxPacketSize;
    uint32_t dwConfig;

    if (td->flags & 0x04)
    {
        //rx
        dma_SetUsbMode_PacedEpReadChannel(r0, ep);

#if 1
        if (length > maxPacketSize)
        {
            length = maxPacketSize;
        }
#endif

        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_LENGTH + ch_offset)/sizeof(uint32_t)] = length;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_LLADDR + ch_offset)/sizeof(uint32_t)] = 0;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_RDADDR + ch_offset)/sizeof(uint32_t)] = fifo_addr;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_RDLINE + ch_offset)/sizeof(uint32_t)] = 0;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_RDINC + ch_offset)/sizeof(uint32_t)] = 4;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_RDLPADDR + ch_offset)/sizeof(uint32_t)] = fifo_addr;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_WRADDR + ch_offset)/sizeof(uint32_t)] = start_addr_paddr;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_WRLINE + ch_offset)/sizeof(uint32_t)] = line;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_WRINC + ch_offset)/sizeof(uint32_t)] = maxPacketSize;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_WRLPADDR + ch_offset)/sizeof(uint32_t)] = 0;
        //Peripheral Address Read: 0x7 = USB DMA Channel
        dwConfig = (0x07 << 8);
    }
    else
    {
        //tx
        dma_SetUsbMode_PacedEpWriteChannel(r0, ep);

        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_LENGTH + ch_offset)/sizeof(uint32_t)] = length;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_LLADDR + ch_offset)/sizeof(uint32_t)] = 0;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_RDADDR + ch_offset)/sizeof(uint32_t)] = start_addr_paddr;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_RDLINE + ch_offset)/sizeof(uint32_t)] = line;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_RDINC + ch_offset)/sizeof(uint32_t)] = maxPacketSize;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_RDLPADDR + ch_offset)/sizeof(uint32_t)] = 0;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_WRADDR + ch_offset)/sizeof(uint32_t)] = fifo_addr;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_WRLINE + ch_offset)/sizeof(uint32_t)] = 0;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_WRINC + ch_offset)/sizeof(uint32_t)] = 4;
        ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_WRLPADDR + ch_offset)/sizeof(uint32_t)] = fifo_addr;
        //Peripheral Address Write: 0x7 = USB DMA Channel
        dwConfig = (0x07 << 16);
    }

    ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_CONFIG + ch_offset)/sizeof(uint32_t)] = dwConfig | (1 << 2);

#endif

    int r7_;
    int r8_;

    if ((td->Data_0x34->direction & 0x80) == 0)
    {
        //0x000026a8: TX?
#ifdef MB86H60
        r7_ = 0;
        r8_ = 0;
#else
        InterruptLock(&r0->Data_0xd0);

        int sl = *((volatile uint32_t*)((uint8_t*)(ip->Data_0) + 0x74));

        int sp;        
        int sp4;
        int sp8;
        
        int r8 = ep - 1;
        sp = r8;
        int sb = r8 * 2;
        sp8 = sb;
        r8 = 0x03 << sb;
        sp4 = r8;
        sb = ~r8;
        r8 = sb & sl;

        if (td->flags & 0x800)
        {
            r8 |= sp4;
        }

        *((volatile uint32_t*)((uint8_t*)(ip->Data_0) + 0x74)) = r8;

        r8 = *((volatile uint32_t*)((uint8_t*)(ip->Data_0) + 0xd0));

        sb = sb & r8;

        if (td->flags & 0x800)
        {
            sb |= (1 << sp8);
        }

        *((volatile uint32_t*)((uint8_t*)(ip->Data_0) + 0xd0)) = sb;

        InterruptUnlock(&r0->Data_0xd0);

        if (td->flags & 0x800)
        {
            //0x00002768
            *((volatile uint32_t*)((uint8_t*)(ip->Data_0) + 4*(ep + 0x1f))) =
                (r1->mps - 1 + length) & -r1->mps;

            //->0x000027a4
        }
        else
        {
            //0x00002790
            *((volatile uint32_t*)((uint8_t*)(ip->Data_0) + 4*(ep + 0x1f))) = 0;
        }
        //0x000027a4
        r7_ = (ip->bData_0xc * 15) + sp;
        r8_ = (ip->bData_0xc * 32) + ep + 0x6c;
#endif

        r3->Data_0xc__ = 0;
        r3->Data_0 = 0x80000000;
        //->0x0000287c
    } //if ((r2->Data_0x34->direction & 0x80) == 0)
    else
    {
        //0x000027d0
#ifdef MB86H60
        r7_ = 0;
        r8_ = 0;
#else
        InterruptLock(&r0->Data_0xd0);
        //0x00002808
        int sl = *((volatile uint32_t*)((uint8_t*)(ip->Data_0) + 0x70));

        int sb = ep - 1;
        sb = sb << 1;
        sb = 0x03 << sb;
        int r8 = sl & ~sb;

        if (td->flags & 0x800)
        {
            r8 = r8 | sb;
        }

        *((volatile uint32_t*)((uint8_t*)(ip->Data_0) + 0x70)) = r8;

        InterruptUnlock(&r0->Data_0xd0);

        r7_ = ((ip->bData_0xc * 15) + 0x0f + ep) * 2;
        r8_ = (ip->bData_0xc * 32) + ep + 0x5c;
#endif

        r3->Data_0 = ((length & ~0xff000000) & ~0xc00000) | 0x80000000;
        r3->Data_0xc__ = length;
    }
    //0x0000287c
    r3->Data_4 = (ep << 27) & 0x78000000;
    r3->Data_8 = (r8_ & 0xffff) | 0x14000000;
    r3->Data_0x10 = start_addr_paddr;
    r3->Data_0x18 = length | 0x80000000;
    r3->Data_0x1c = start_addr_paddr;
    r3->Data_0x14 = 0;
    r3->td = td;
    r3->Data_0x30 = r1;

    r1->Data_0x3c = r3;

#ifndef MB86H60
    *((uint32_t*)((uint8_t*)(ip->Data_4__) + 0x600c + (r7_ * 16))) = 
        r3->Data_0x28 | 0x0a;
#endif

    return 0;
}


void MENTOR_AbortDMA_TX(struct _hctrl_t* a, struct Struct_0xa4* b)
{
#if 1
    fprintf(stderr, "MENTOR_AbortDMA_TX: TODO!!!\n");
#endif

}


void MENTOR_AbortDMA_RX(struct _hctrl_t* a, struct Struct_0xa4* b)
{
#if 1
    fprintf(stderr, "MENTOR_AbortDMA_RX: TODO!!!\n");
#endif

}


/* 0x00005738 - todo */
int MENTOR_ProcessETDDone(struct _hctrl_t* sl, uint16_t r5)
{
#if 0 //No printf in ISR
    fprintf(stderr, "MENTOR_ProcessETDDone: TODO!!!\n");
#endif

    int fp_0x34;
//    void* fp_0x30 = &sl->Data_0x54;
    int r7 = 16;
    int r6 = 1;

    while ((r5 >>= 1) != 0)
    {
        //loc_5768
        if (r5 & 0x01)
        {
            //0x00005770
            struct _musb_transfer* r8 = sl->Data_0xc4[r6];
            if (r8 == NULL)
            {
                //0x00005780
                HW_Write16(sl, 0x106 + r7, 0);
                HW_Write16(sl, 0x102 + r7, 0);
                //->loc_59e8
            }
            else
            {
                //loc_57b0
                int fp_0x2c = r8->flags;
                struct Struct_0xa4* sb = r8->Data_0x30;

                if (sb->bData_0x1f == 0)
                {
                    //0x000057c8
                    if (fp_0x2c/*r2*/ & 0x04)
                    {
                        //0x000057d0
                        uint32_t r3 = HW_Read16(sl, 0x106 + r7);
                        r3 = r3 << 16;
                        uint32_t r4 = r3 >> 16;
                        r3 = (r3 >> 25) & 0x01;
                        sb->Data_0x20 = r3;

                        if ((r4 & 0x14c) == 0)
                        {
                            //0x00005800
                            if ((1 << r6) & sl->Data_0x54)
                            {
                                //->loc_582c
                                atomic_clr(/*fp_0x30*/&sl->Data_0x54);
                                r4 = 8;
                                //->loc_5848
                                if (r4 & 0x400)
                                {
                                    //0x00005854
                                    MENTOR_AbortDMA_RX(sl, sb);
                                }
                                //loc_5860
                                (r8->Func_0x38)(sl, r8, 0, r4);
                                //->loc_59e8
                            } //if ((1 << r6) & sl->Data_0x54)
                            else
                            {
                                //loc_587c: Read RXCOUNT
                                r3 = HW_Read16(sl, 0x108 + r7);
                                fp_0x34 = r3/*r1*/;
                                if ((r3/*r1*/ + r8->bytes_xfered) > r8->xfer_length)
                                {
                                    //0x000058a8
                                    (r8->Func_0x38)(sl, r8, 0, 8);
                                    //->loc_59e8
                                }
                                else
                                {
                                    //loc_58c4
                                    if (fp_0x2c & 0x200)
                                    {
                                        //0x000058d0

                                        mentor_start_dma_transfer(sl, sb, r8, 0, 
                                            r6, sb->Data_0x2c, 
                                            r8->xfer_buffer_paddr + r8->bytes_xfered,
                                            r3/*r1*/);
                                        //->loc_59e8
                                    }
                                    else
                                    {
                                        //loc_5908
                                        if ((fp_0x2c & 0x600) == 0)
                                        {
                                            //0x00005914
                                            MENTOR_ReadFIFO(sl, r8, r6, 
                                                r8->xfer_buffer + r8->bytes_xfered,
                                                fp_0x34);

#ifdef MB86H60
                                            MGC_Write16(sl, 0x106 + r7, (uint16_t)(r4 & ~1));
#else
                                            ((volatile uint16_t*)(sl->Data_0x14))[0x106/2 + r7] = 
                                                (uint16_t)(r4 & ~1);
#endif
                                        }
                                        //loc_595c
                                        (r8->Func_0x38)(sl, r8, fp_0x34, 0);
                                        //->loc_59e8
                                    }
                                }
                            }
                        } //if ((r4 & 0x14c) == 0)
                        else
                        {
                            //loc_5818
                            if ((1 << r6) & sl->Data_0x54)
                            {
                                //->loc_582c
                                atomic_clr(/*fp_0x30*/&sl->Data_0x54);
                                r4 = 8;
                                //->loc_5848
                            }
                            else
                            {
                                //loc_583c
                                if (r4 & 0x40)
                                {
                                    r4 = 4;
                                }
                                else
                                {
                                    r4 = 0x0f;
                                }
                            }
                            //loc_5848
                            if (fp_0x2c & 0x400)
                            {
                                //0x00005854
                                MENTOR_AbortDMA_RX(sl, sb);
                            }
                            //loc_5860
                            (r8->Func_0x38)(sl, r8, 0, r4);
                            //->loc_59e8
                        }
                    } //if (fp_0x2c/*r2*/ & 0x04)
                    else
                    {
                        //loc_5978
                        uint32_t r3 = HW_Read16(sl, 0x102 + r7);
                        r3 = r3 << 16;
                        uint32_t r2 = r3 >> 24;
                        sb->Data_0x20 = r2 & 0x01;
                        r3 = r3 >> 16;

                        int r4;
                        if ((r3 & 0xa4) == 0)
                        {
                            r4 = 0;
                            //->loc_59d0
                        }
                        else
                        {
                            //0x000059ac
                            if (r3 & 0x20)
                            {
                                r4 = 0x04;
                            }
                            else
                            {
                                r4 = 0x0f;
                            }

                            if (fp_0x2c & 0x400)
                            {
                                //0x000059c4
                                MENTOR_AbortDMA_TX(sl, sb);
                            }
                            //loc_59d0
                        }
                        //loc_59d0
                        (r8->Func_0x38)(sl, r8, r8->Data_0x10, r4);
                        //loc_59e8
                    }
                } //if (sb->bData_0x1f == 0)
                //loc_59e8
            }
            //loc_59e8
        }
        //loc_59e8
        r7 += 16;
        r6++;
        //->loc_5768
    } //while ((r5 >>= 1) != 0)
    //loc_59f8
    return 0;
}


/* 0x000029a8 - complete */
int mentor_alloc_dma_sched(struct _hctrl_t* a, struct Struct_0xa4* b)
{
#if 1
    fprintf(stderr, "mentor_alloc_dma_sched\n");
#endif

    return 1;
}


/* 0x000025b8 - complete */
int mentor_claim_dma_channel(struct _hctrl_t* a, struct _musb_transfer* b, int c, int* d)
{
#if 1
    fprintf(stderr, "mentor_claim_dma_channel\n");
#endif

    return 0;
}



/* 0x00002a80 - complete */
void mentor_get_ext_intstatus(struct _hctrl_t* ctrl, 
            uint16_t* int_rx, uint16_t* int_tx, uint16_t* int_usb)
{
#if 0
    fprintf(stderr, "mentor_get_ext_intstatus: TODO\n");
#endif

#ifdef MB86H60

    // Bit conversion???
    *int_usb = MGC_Read8(ctrl, MGC_O_HDRC_INTRUSB);
    *int_rx = MGC_Read16(ctrl, MGC_O_HDRC_INTRRX);
    *int_tx = MGC_Read16(ctrl, MGC_O_HDRC_INTRTX);

#else //DM8xx

#define AM35X_INTR_USB_SHIFT	0
#define AM35X_INTR_USB_MASK	(0x1ff << AM35X_INTR_USB_SHIFT)

#define AM35X_INTR_RX_SHIFT	16
#define AM35X_INTR_TX_SHIFT	0
#define AM35X_TX_EP_MASK	0xffff		/* EP0 + 15 Tx EPs */
#define AM35X_RX_EP_MASK	0xfffe		/* 15 Rx EPs */
#define AM35X_TX_INTR_MASK	(AM35X_TX_EP_MASK << AM35X_INTR_TX_SHIFT)
#define AM35X_RX_INTR_MASK	(AM35X_RX_EP_MASK << AM35X_INTR_RX_SHIFT)

    struct Struct_0xe4* r4 = ctrl->dma_hdl;

    /* Get endpoint interrupts */
    uint32_t epintr = ((volatile uint32_t*)(r4->Data_0))[0x30/4];
    ((volatile uint32_t*)(r4->Data_0))[0x30/4] = epintr; //Clear

    *int_rx = (epintr & AM35X_RX_INTR_MASK) >> AM35X_INTR_RX_SHIFT;
    *int_tx = (epintr & AM35X_TX_INTR_MASK) >> AM35X_INTR_TX_SHIFT;

    uint32_t usbintr = ((volatile uint32_t*)(r4->Data_0))[0x34/4];
    ((volatile uint32_t*)(r4->Data_0))[0x34/4] = usbintr; //Clear

    *int_usb = (usbintr & AM35X_INTR_USB_MASK) >> AM35X_INTR_USB_SHIFT;
#endif
}


/* 0x00002ac4 - complete */
void mentor_clr_ext_int(struct _hctrl_t* a)
{
#if 0
    fprintf(stderr, "mentor_clr_ext_int: TODO\n");
#endif

    /* Empty, because all active interrupts were already cleared
        when status registers were read.*/
}


int MENTOR_RemoveTDFromEndpoint(struct _hctrl_t* a, 
    struct Struct_10bab4* b, 
    struct Struct_0xa4* c)
{
#if 1
    fprintf(stderr, "MENTOR_RemoveTDFromEndpoint: TODO!!!\n");
#endif

    return 0;
}


/* 0x000079c0 - todo */
void MENTOR_URB_complete(struct _hctrl_t* r5,
    struct Struct_0xa4 * r7, 
    struct _musb_transfer* r4, 
    int transferType, int err)
{
#if 0
    if (transferType != 0)
    {
    fprintf(stderr, "MENTOR_URB_complete: transferType=%d, r4->flags=0x%x, r4->xfer_length=%d\n",
        transferType, r4->flags, r4->xfer_length);

    if ((r4->flags & PIPE_FLAGS_TOKEN_IN) && (r4->xfer_length != 0))
    {
        if (r4->xfer_buffer != 0)
        {
            hex_dump("MENTOR_URB_complete(xfer_buffer)", (void*) r4->xfer_buffer, r4->xfer_length);
        }

        if (r4->xfer_buffer_paddr != 0)
        {
//            hex_dump("MENTOR_URB_complete(xfer_buffer_paddr)", (void*) r4->xfer_buffer_paddr, r4->xfer_length);
            fprintf(stderr, "MENTOR_URB_complete: r4->xfer_buffer_paddr=0x%x\n",
                r4->xfer_buffer_paddr);
        }
    }
    }
#endif

    struct Struct_10bab4* r6 = r4->Data_0x34;
    int r8 = r4->bytes_xfered;

    if (r7->bData_0x1f != 0)
    {
        //->0x00007e14
        return;
    }

    r6->Data_8 = err/*fp4 = r2*/;

    switch (transferType)
    {
        case USB_ATTRIB_CONTROL: //0:
            //0x00007a1c
            if (err != 0)
            {
                //0x00007a24
                r7->Data_0x20 = 0;

                mentor_slogf(r5, 12, 2, 1, 
                    "%s - Error on Control Transfer ( %d, %x ) ",
                    "devu-dm816x-mg.so", err, r7->Data_0x14);
            }
            //0x00007a60
            pthread_sleepon_lock();

            r6->Data_4 = 1;

            if ((r4->flags & 1) == 0)
            {
                r6->Data_0x34 += r8;
            }

            InterruptLock(&r5->Data_0xd0);

            r4->flags = 0;

            SIMPLEQ_INSERT_TAIL(&r5->transfer_free_q, r4, link);

            InterruptUnlock(&r5->Data_0xd0);

            pthread_sleepon_signal(&r6->Data_4);

            pthread_sleepon_unlock();
            //->0x00007e14
            break;

        case USB_ATTRIB_INTERRUPT: //3:
            //0x00007af4
            r5->Data_0x84++;
            //break; /* fall through */

        case USB_ATTRIB_BULK: //2:
            //0x00007b00
            r6->Data_0x34/*r1*/ += r8;

            if (err != 0)
            {
                //0x00007b14
                //0x00007b28
                mentor_slogf(r5, 12, 2, 1, "%s - Error on %s status 0x%x",
                    "devu-dm816x-mg.so", 
                    (transferType != USB_ATTRIB_BULK/*2*/)? "Interrupt": "Bulk", err);

                InterruptLock(&r5->Data_0xd0);

                r4->flags = 0;

                SIMPLEQ_INSERT_TAIL(&r5->transfer_free_q, r4, link);

                InterruptUnlock(&r5->Data_0xd0);

                MENTOR_RemoveTDFromEndpoint(r5, r6, r7);

                if (r6->Func_0x58 != NULL)
                {
                    //0x00007be4
                    (r6->Func_0x58)(r6);
                }
                //->0x00007e14
            }
            else
            {
                //0x00007bf4
                if (((r6->Data_0___ & 0x04) == 0) &&
                    ((r4->flags & 0x04) != 0))
                {
                    //0x00007c0c
                    if (/*r1*/r6->Data_0x34 != r6->dwLength)
                    {
                        r6->Data_8 = 9;
                    }
                }
                //0x00007c1c
                if (((r4->flags & 0x80000000 /*< 0*/) && (r4->flags & 0x08)) || 
                    (((r4->xfer_length != r8) || (r4->flags & 0x80000000 /*< 0*/)) 
                        && (r4->flags & 0x04)))
                {
                    //0x00007c58
                    InterruptLock(&r5->Data_0xd0);

                    r4->flags = 0;

                    SIMPLEQ_INSERT_TAIL(&r5->transfer_free_q, r4, link);

                    InterruptUnlock(&r5->Data_0xd0);

                    if (r6->Func_0x58 != NULL)
                    {
                        //0x00007cc8
                        (r6->Func_0x58)(r6);
                    }
                    //->0x00007e14
                }
                else
                {
                    //0x00007cd8
                    InterruptLock(&r5->Data_0xd0);

                    r4->flags = 0;

                    SIMPLEQ_INSERT_TAIL(&r5->transfer_free_q, r4, link);

                    InterruptUnlock(&r5->Data_0xd0);
                    //->0x00007e14
                }
            }
            //->0x00007e14
            break;

#if 0
        case USB_ATTRIB_ISOCHRONOUS: //1:
            //0x00007d40
            //TODO!!!
            break;
#endif

        default:
            //->0x00007e14
#if 1
            fprintf(stderr, "MENTOR_URB_complete: transferType=%d: TODO!!!\n", transferType);
#endif
            break;
    }
    //0x00007e14
    return;
}


/* 0x00007e38 - todo */
void mentor_bottom_half(struct _hctrl_t* hc)
{
    struct _musb_transfer* td;

#if 0
    fprintf(stderr, "mentor_bottom_half: TODO\n");
#endif

    while (1)
    {
        MUSB_LOCK

        td = SIMPLEQ_FIRST(&hc->transfer_complete_q);
        if (td == NULL)
        {
            break;
        }

        SIMPLEQ_REMOVE_HEAD(&hc->transfer_complete_q, link);

        MUSB_UNLOCK

        MUSB_MUTEX_LOCK(Data_4, 0x943);

        MENTOR_URB_complete(hc, 
            td->Data_0x30, 
            td, 
            td->Data_0x30->transferType,
            td->status);

        MUSB_MUTEX_UNLOCK(Data_4, 0x946);

    } //while (1)
    
    MUSB_UNLOCK
}



/* 0x00005a04 - todo */
const struct sigevent * mentor_interrupt_handler(void* a, int b)
{
//    fprintf(stderr, "mentor_interrupt_handler: TODO\n");

    struct _hctrl_t *r4 = a;
    uint16_t int_usb;
    uint16_t int_tx;
    uint16_t int_rx;

#ifdef MB86H60
    int status = dma_GetUsbIntStatus(r4);
    dma_SetUsbIntClear(r4, status);
    if (status & 1) //USB General IRQ?
    {
#endif
    mentor_get_ext_intstatus(r4, &int_rx, &int_tx, &int_usb);

    if (int_tx & 1) //EP0?
    {
        MENTOR_ProcessControlDone(r4);
    }

    uint16_t r1 = (int_rx | int_tx) & 0xfffe;
    if (r1 != 0)
    {
        MENTOR_ProcessETDDone(r4, r1);
    }

    if (int_usb != 0)
    {
#ifdef MB86H60
#if 1
        bUsbIntStatus = int_usb;
#endif
        if ((int_usb & (1 << 6)/*Sess Req*/) != 0)
        {
            MGC_Write8(r4, MGC_O_HDRC_DEVCTL, MGC_M_DEVCTL_SESSION);
        }
#endif
        if ((int_usb & (1 << 4)/*Conn???*/) != 0)
        {
            r4->Data_0x6c = (r4->Data_0x6c | 0x02) & ~0x04;
        }
        //loc_5a80
        else if ((int_usb & 
            ((1 << 7)/*VBus Error???*/ || 
            (1 << 5)/*Discon???*/ || 
            (1 << 2)/*Reset/Babble???*/)) != 0)
        {
            r4->Data_0x6c &= ~(0x02 | 0x04);
        }
    }
    //loc_5a90
    mentor_clr_ext_int(r4);
#ifdef MB86H60
    } //if (status & 1)
#endif

    if (SIMPLEQ_EMPTY(&r4->transfer_complete_q))
    {
        return NULL;
    }

    return &r4->intr_event;
}


/* 0x00007f88 - todo */
static void* mentor_interrupt_thread(void* a)
{

    st_USB_Hc* r7 = a;
    struct _hctrl_t* hc = r7->hc_data;

    if (ThreadCtl(1, 0) == -1)
    {
        mentor_slogf(hc, 12, 2, 1, "%s - %s: Unable to obtain I/O privity.",
            "devu-dm816x-mg.so", "mentor_interrupt_thread");
        return (void*)-1;
    }
    //loc_8000
    SIGEV_PULSE_INIT( &hc->intr_event, hc->coid, 
        getprio(0), MUSB_PULSE_INTR, 0 );

    while ((hc->flags & 0x10) == 0)
    {
        //loc_803c
        delay(1);
    }
    //loc_8050
#if 0//def MB86H60
    hc->irq = MB86H60_INTR_USB;
#else
    hc->irq = r7->pci_inf->Irq;
#endif

    hc->intr_id = InterruptAttach(hc->irq, 
        mentor_interrupt_handler, hc, 0xe8, 8);

#if 0
    fprintf(stderr, "mentor_interrupt_thread: hc->irq=%d, hc->intr_id=%d\n",
        hc->irq, hc->intr_id);
#endif
            
    if (hc->intr_id == -1)
    {
        mentor_slogf(hc, 12, 2, 1, "%s - %s: InterruptAttach failed.",
            "devu-dm816x-mg.so", "mentor_interrupt_thread");

        return (void*)-1;
    }
    //loc_80e0
    while (1)
    {
        //loc_8100
        struct _pulse pulse; //fp_0x30

#if 0
        fprintf(stderr, "mentor_interrupt_thread: before MsgReceivePulse\n");
#endif

        if (MsgReceivePulse(hc->chid, &pulse, sizeof(pulse), 0) == -1)
        {
            //->loc_8154
            break;
        }

#if 0
        fprintf(stderr, "mentor_interrupt_thread: after MsgReceivePulse, code=%d\n",
            pulse.code);
#endif
        //0x0000811c
        switch (pulse.code)
        {
            case MUSB_PULSE_INTR:
                mentor_bottom_half(hc);
                break;

            default:
                mentor_slogf(hc, 12, 2, 1, "%s - %s: Unknown pulse",
                    "devu-dm816x-mg.so", "mentor_interrupt_thread");
                break;
        }
        //->loc_8100
    } //while (1)

    InterruptDetach(hc->intr_id);

    return NULL;
}


/* 0x000041b8 - todo */
int find_block_list(struct Mentor_Controller_Inner_0x8c* a, unsigned long b)
{
#if 0
    fprintf(stderr, "find_block_list: TODO!!!\n");
#endif

    int r2 = 1;

    while (r2 < b)
    {
        r2 *= 2;
    }

    uint32_t r3 = r2;

    for (r2 = 0; ((r3 % 2) == 0) && (r2 < 14); r2++)
    {
        r3 /= 2;
    }

    r2 = r2 - 3;
    if (r2 > 10)
    {
        return -1;
    }

    return r2 < 0? 0: r2;
}


/* 0x000043a0 - todo */
int mentor_init_fifo_config(struct _hctrl_t* fp_0x40, 
        char* fconfig_string/*r6*/)
{
#if 0
    fprintf(stderr, "mentor_init_fifo_config: TODO\n");
#endif

    char* fconfig_default; //fp_0x3c
    int fp_0x38 = 64;

    struct Mentor_Controller_Inner_0x8c* fp_0x34;
    int32_t fp_0x30;
    char* fp_0x2c;
//    int sb;

    fp_0x34 = calloc(1, 0xf4);
    if (fp_0x34 == NULL)
    {
        return 12; //->loc_45bc
    }

//    fp_0x38 = 64;
    if (fconfig_string != NULL)
    {
        fconfig_default = NULL;
        //->loc_4408
//        fp_0x38 = 64;
//        sb = 4;
        //->loc_442c
    }
    else
    {
        //0x000043ec
        fconfig_default = strdup("16:8;4:16;8:64;2:128;14:512");
        if (fconfig_default != NULL)
        {
            fconfig_string = fconfig_default;
            //loc_4408
//            fp_0x38 = 64;
//            sb = 4;
            //->loc_442c
        }
        else
        {
            //loc_4418
            free(fp_0x34);
            return 12; //->loc_45bc
        }
    }
#if 0
    //loc_4428
#endif
    for (; fconfig_string != NULL; fconfig_string = fp_0x2c)
    {
        //loc_442c
        fp_0x2c = strchr(fconfig_string, 0x3b);
        if (fp_0x2c != NULL)
        {
            *fp_0x2c++ = 0;
        }

        char* r4 = strchr(fconfig_string, 0x3a);
        if (r4 != NULL)
        {
            //0x00004464
            *r4++ = 0;

            fp_0x30 = strtoul(fconfig_string, NULL, 0);

            if (r4 != NULL)
            {
                //0x00004484
                unsigned long r4_, r5; 
                r4_ = strtoul(r4, NULL, 0);
                r5 = r4_;

                *fconfig_string = 0;

                int r6_ = find_block_list(fp_0x34, r4_);
                //r7 = r6_ * 20;
                //sl = r7 + 0x18;
                //sl = fp_0x34 + sl;
                //r7 = fp_0x34 + r7;
                //r7->Data_0x20 = fp_0x30;
#if 1
                fprintf(stderr, "mentor_init_fifo_config: r6_=%d, fp_0x30=%d, r4_=%d\n",
                    r6_, fp_0x30, r4_);
#endif
                fp_0x34->Data_0x18[r6_].Data_8 = fp_0x30;
                fp_0x34->Data_0x18[r6_].Data_0x10 = calloc(fp_0x30, 16);

                if (fp_0x34->Data_0x18[r6_].Data_0x10 == NULL)
                {
                    //loc_44fc
                    free(fconfig_default);
                    return 12; //->loc_45bc
                }
                //0x000044ec
//                if (fp_0x30/*r7*/ > 0)
                {
                    //loc_450c
//                    int r0 = fp_0x38;
                    int32_t r3; // = 0;
                    //r1 = &fp_0x34->Data_0x18[r6_].Data_0x10;
                    //ip = &fp_0x34->Data_0x18[r6_].Data_0xc;
                    //r8 = 1;
                    for (r3 = 0; r3 < fp_0x30/*r7*/; r3++)
                    {
                        //loc_452c
                        //r2 = r3*16;
                        fp_0x34->Data_0x18[r6_].Data_0x10[r3].Data_0 = r4_;
                        fp_0x34->Data_0x18[r6_].Data_0x10[r3].Data_4 = fp_0x38/*r0*/;
                        fp_0x34->Data_0x18[r6_].Data_0x10[r3].Data_0xc = 
                            &fp_0x34->Data_0x18[r6_]/*sl*/;
                        fp_0x34->Data_0x18[r6_].Data_0x10[r3].Data_8 = r3;

                        fp_0x34->Data_0x18[r6_].Data_0xc |= (1/*r8*/ << r3);
                        
                        fp_0x38/*r0*/ += r5;
                    } //for (r3 = 0; r3 < fp_0x30/*r7*/; r3++)
                    //0x00004578
//                    fp_0x38 += r5 + (fp_0x30 - 1) * r5;
                }
                //loc_4590
            }
            //loc_4590
        }
        //loc_4590
//        fconfig_string = fp_0x2c;
        //loc_442c
    }
//    while (fp_0x2c != NULL);
    //0x0000459c
    if (fconfig_default != NULL)
    {
        free(fconfig_default);
    }

    fp_0x40->Data_0x8c = fp_0x34;

    return 0;
}


/* 0x000045cc - complete */
int mentor_fifo_init(struct _hctrl_t* cntrl, char* fconfig)
{
#if 0
    fprintf(stderr, "mentor_fifo_init: TODO\n");
#endif

    uint8_t epInfo;
    uint8_t configData;
    uint8_t dynFifo;

    uint8_t rxFifoSize;
    uint8_t txFifoSize;
    uint16_t rxFifoAddr;
    uint16_t txFifoAddr;


#if 1
    fprintf(stderr, "hwvers=0x%x\n", MGC_Read16(cntrl, 0x6c));

    epInfo = MGC_Read8(cntrl, 0x78);
    fprintf(stderr, "mentor_fifo_init: epInfo=0x%x, Rx=%d, Tx=%d\n", 
        epInfo, (epInfo >> 4), (epInfo & 0x0f));

    int i;
    for (i = 0; i < 6; i++)
    {
        MGC_SelectEnd(cntrl, i);

        if (i == 0)
        {
            configData = MGC_Read8(cntrl, 0x1f);
            dynFifo = (configData & (1 << 2))? 1: 0;

            fprintf(stderr, "mentor_fifo_init: configData=0x%x DynFIFO=%d, SoftConE=%d\n", 
                configData,
                dynFifo,
                (configData & (1 << 1))? 1: 0);
        }
        else
        {
            uint8_t fifoSize = MGC_Read8(cntrl, 0x1f);
            rxFifoSize = (fifoSize >> 4);
            txFifoSize = (fifoSize & 0x0f);

            fprintf(stderr, 
                "mentor_fifo_init: FifoSize[%d]=0x%x, Rx=0x%x(%d bytes), Tx=0x%x(%d bytes)\n", 
                i, fifoSize,
                rxFifoSize, 1 << rxFifoSize,
                txFifoSize, 1 << txFifoSize);
        }
    }

    if (dynFifo)
    {
        for (i = 1; i < 6; i++)
        {
            MGC_SelectEnd(cntrl, i);

            rxFifoSize = MGC_Read8(cntrl, MGC_O_HDRC_RXFIFOSZ);
            txFifoSize = MGC_Read8(cntrl, MGC_O_HDRC_TXFIFOSZ);
            rxFifoAddr = MGC_Read16(cntrl, MGC_O_HDRC_RXFIFOADD);
            txFifoAddr = MGC_Read16(cntrl, MGC_O_HDRC_TXFIFOADD);

            fprintf(stderr, "mentor_fifo_init(1): %d: Rx(%d/%d), Tx(%d/%d)\n", i,
                rxFifoSize, rxFifoAddr, txFifoSize, txFifoAddr);
        }
    }
#endif

#ifdef MB86H60
    if (dynFifo)
    {
        MGC_SelectEnd(cntrl, 0);
        MGC_Write8(cntrl, MGC_O_HDRC_RXFIFOSZ, 3);
        MGC_Write16(cntrl, MGC_O_HDRC_RXFIFOADD, 0);
        MGC_Write8(cntrl, MGC_O_HDRC_TXFIFOSZ, 3);
        MGC_Write16(cntrl, MGC_O_HDRC_TXFIFOADD, 0);
    }
#else
    ((volatile uint8_t*)(cntrl->Data_0x14))[0x0e] = 0;
    ((volatile uint8_t*)(cntrl->Data_0x14))[0x63] = 0x03; //RXFIFOSZ
    ((volatile uint16_t*)(cntrl->Data_0x14))[0x66/2] = 0; //RXFIFOADD
    ((volatile uint8_t*)(cntrl->Data_0x14))[0x62] = 0x03; //TXFIFOSZ
    ((volatile uint16_t*)(cntrl->Data_0x14))[0x64/2] = 0; //TXFIFOADD
#endif

    mentor_init_fifo_config(cntrl, fconfig);

#if 1
    if (dynFifo)
    {
        int j;
        for (j = 0; j < 6; j++)
        {
            MGC_SelectEnd(cntrl, j);

            fprintf(stderr, "mentor_fifo_init(2): %d: Rx(%d/%d), Tx(%d/%d)\n", j,
                MGC_Read8(cntrl, MGC_O_HDRC_RXFIFOSZ),
                MGC_Read16(cntrl, MGC_O_HDRC_RXFIFOADD),
                MGC_Read8(cntrl, MGC_O_HDRC_TXFIFOSZ),
                MGC_Read16(cntrl, MGC_O_HDRC_TXFIFOADD));
        }
    }
#endif

    return 0;
}


/* 0x00004f3c - complete */
int mentor_init()
{
#if 0
    fprintf(stderr, "mentor_init\n");
#endif

    return 0;
}


/* 0x00004f44 - complete */
int mentor_shutdown()
{
    fprintf(stderr, "mentor_shutdown\n");

    return 0;
}


/* 0x00004fa8 - todo */
int mentor_controller_shutdown()
{
    fprintf(stderr, "mentor_controller_shutdown\n");

    return 0;
}


/* 0x00005f98 - todo */
int MENTOR_AllocateTD(struct _hctrl_t* r4)
{
#if 0
    fprintf(stderr, "MENTOR_AllocateTD: TODO!!!\n");
#endif

    uint32_t i;
    struct _musb_transfer* td;

    SIMPLEQ_INIT( &r4->transfer_free_q );
    SIMPLEQ_INIT( &r4->transfer_complete_q );

    td = calloc(1, sizeof(struct _musb_transfer) * (r4->num_td + 1));
    if (td == NULL)
    {
        return 12;
    }

    r4->transfer_mem = td;

    memset(td, 0, (r4->num_td + 1) * sizeof(struct _musb_transfer));

    for (i = 0; i < r4->num_td; i++, td++)
    {
        SIMPLEQ_INSERT_TAIL( &r4->transfer_free_q, td, link );
    }

    return 0;
}


/* 0x00006050 - todo */
int MENTOR_AllocateED(struct _hctrl_t* r5)
{
#if 0
    fprintf(stderr, "MENTOR_AllocateED: TODO!!!\n");
#endif

    uint32_t i;
    struct Struct_0xa4* r4;
    
    r4 = calloc(1, (r5->Data_0x70 + 1) * sizeof(struct Struct_0xa4));
    if (r4 == NULL)
    {
        return 12;
    }

    r5->Data_0xa4 = r4;

    memset(r4, 0, (r5->Data_0x70 + 1) * sizeof(struct Struct_0xa4));

    r4->Data_8__ = 0;
    r4->Data_0xc = &r4->Data_8__;
    r4->Data_0x10 = 0;
    r5->Data_0xa8 = r4;

    for (i = 0; i < r5->Data_0x70; i++)
    {
        r4->Data_0x2c = -1;
        r4->Data_0 = r4 + 1;
        r4->Data_0->Data_4 = r4;
        r4->Data_0->Data_8__ = 0;
        r4->Data_0->Data_0xc = &r4->Data_0->Data_8__;
        r4->Data_0->Data_0x10 = 0;

        r4++;
    }

    r4->Data_0 = r5->Data_0xa8;
    r5->Data_0xa8->Data_4 = r4;

    return 0;
}



/* 0x00005340 - todo */
struct Struct_0xa4* MENTOR_GetEDPool(struct _hctrl_t* a)
{
#if 0
    fprintf(stderr, "MENTOR_GetEDPool: TODO!!!\n");
#endif

    struct Struct_0xa4* r4;
    struct Struct_0xa4* r6 = a->Data_0xa8;

    if (pthread_mutex_lock(&a->Data_4) != 0)
    {
        fprintf(stderr, "mutex error\n"/*TODO*/);
    }
    //loc_538c
    r4 = r6->Data_0;
    if (r4 == r6)
    {
        if (pthread_mutex_unlock(&a->Data_4) == 0)
        {
            r4 = 0;
            //->loc_5428
        }
        else
        {
            fprintf(stderr, "mutex error\n"/*TODO*/);
            r4 = 0;
            //->loc_5428
        }
    }
    else
    {
        //loc_53d4
        r6->Data_0 = r4->Data_0;
        r4->Data_0->Data_4 = r6;
        r4->Data_0x10 |= 0x80000000;
        r4->Data_0x38 = 0;

        if (pthread_mutex_unlock(&a->Data_4) != 0)
        {
            fprintf(stderr, "mutex error\n"/*TODO*/);
        }
    }
    //loc_5428
    return r4;
}



/* 0x0000544c - todo */
int MENTOR_BuildEDList(struct _hctrl_t* a, struct Struct_0xa4** b)
{
#if 0
    fprintf(stderr, "MENTOR_BuildEDList: TODO!!!\n");
#endif

    struct Struct_0xa4* r3;
    
    r3 = MENTOR_GetEDPool(a);
    if (r3 == NULL)
    {
        return 12;
    }

    *b = r3;
    r3->Data_0x10 |= 0x40000008;
    r3->Data_8__ = 0;
    r3->Data_0xc = &r3->Data_8__;
    r3->Data_4 = r3;
    r3->Data_0 = r3;

    return 0;

}


int mentor_abort_dma_transfer(struct _hctrl_t* a, struct Struct_0xa4* b)
{
#if 1
    fprintf(stderr, "mentor_abort_dma_transfer: TODO\n");
#endif

    return 0;
}


/* 0x000028e8 - complete */
struct Struct_0xe4_Inner_0x1c* lookup_by_paddr(struct _hctrl_t* r3, uint32_t b)
{
#if 0
    fprintf(stderr, "lookup_by_paddr: TODO\n");
#endif

    struct Struct_0xe4* r2 = r3->dma_hdl;

    InterruptLock(&r3->Data_0xd0);

    struct Struct_0xe4_Inner_0x1c* p;
#ifdef MB86H60
    LIST_FOREACH(p, &r2->dma_active_q, link)
    {
        //TODO: Decision based on parameter b
        LIST_REMOVE(p, link);
        break;
    }
#else
    LIST_FOREACH(p, &r2->dma_active_q, link)
    {
        if (p->Data_0x28 == b)
        {
            LIST_REMOVE(p, link);
            break;
        }
    }
#endif

    InterruptUnlock(&r3->Data_0xd0);

    return p;
}



/* 0x00003bd8 - todo */
const struct sigevent * dma_interrupt_handler(void* a, int b)
{
#if 0
    fprintf(stderr, "dma_interrupt_handler: TODO\n");
#endif

    struct _hctrl_t* r5 = a;
    struct Struct_0xe4* r7 = r5->dma_hdl;

#ifdef MB86H60

    // Read IRQ status
    uint32_t status = ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_INT_STATUS/sizeof(uint32_t)];

    //Stop the channel by config reg
    int channel = 3;
    int ch_offset = 0x40 * channel;

    ((volatile uint32_t*)(dma_regs))[(MB86H60_DMA_CH_CONFIG + ch_offset)/sizeof(uint32_t)] = 0;

    // Clear IRQ
    ((volatile uint32_t*)(dma_regs))[MB86H60_DMA_INT_CLEAR/sizeof(uint32_t)] = status;

    struct Struct_0xe4_Inner_0x1c* r5_ = lookup_by_paddr(r5, 0);
    if (r5_ != NULL)
    {
        //0x00003d74
        struct _musb_transfer* td = r5_->td;
        struct Struct_0xa4* r4 = td->Data_0x30;

        if (td->flags & 0x04)
        {
            uint32_t rxCsr = HW_Read16(r5, MUSB_RXCSR(r4->num));
            if ((rxCsr & RXCSR_AUTOCLEAR) == 0)
            {
                rxCsr &= ~RXCSR_RXPKTRDY;
                HW_Write16(r5, MUSB_RXCSR(r4->num), rxCsr);
            }
            rxCsr &= ~RXCSR_DMA_REQ_EN; 
//            | RXCSR_AUTOREQ | RXCSR_AUTOCLEAR | RXCSR_DMA_REQ_MODE
            HW_Write16(r5, MUSB_RXCSR(r4->num), rxCsr);

            (td->Func_0x3c)(r5, td, r5_->Data_0xc__, 0);

            InterruptLock(&r5->Data_0xd0);

            LIST_INSERT_HEAD(&r7->dma_free_q, r5_, link);

            InterruptUnlock(&r5->Data_0xd0);
        }
        else
        {
            uint32_t txCsr = HW_Read16(r5, MUSB_TXCSR(r4->num));

            int r6_ = 0;
            int r4_ = 0;
            while ((r6_ <= 4) && (r4_ <= 19999/*sb*/))
            {
                if (txCsr & 0x03)
                {
                    r6_ = 0;
                }
                else
                {
                    r6_++;
                }
                nanospin_ns(1000);

                r4_++;
                txCsr = HW_Read16(r5, MUSB_TXCSR(r4->num));
            }

            if ((td != NULL) && (td->flags & 0x800))
            {
                (td->Func_0x3c)(r5, td, td->Data_0x10, 0);
            }

            InterruptLock(&r5->Data_0xd0);

            LIST_INSERT_HEAD(&r7->dma_free_q, r5_, link);

            InterruptUnlock(&r5->Data_0xd0);
        }
    }

#else

    if (g_dma_nums == 0)
    {
        //0x00003c10
        uint32_t status = *((volatile uint32_t*)(r7->Data_4__ + 0x28));
        if (status != 0)
        {
            *((volatile uint32_t*)(r7->Data_4__ + 0x28)) = status;

            if (status & 0x01)
            {
                usbss_intstat_Val[0] = 1;
                usbss_intstat_Val[1] = 1;
            }
        }
        //0x00003c40
        uint32_t r1 = *((volatile uint32_t*)(r7->Data_4__ + 0x4098));
        uint32_t r3 = *((volatile uint32_t*)(r7->Data_4__ + 0x409c));
        uint32_t r0 = *((volatile uint32_t*)(r7->Data_4__ + 0x40a0));

        g_dma_nums = dma_nums;

        g_usb_tx_intr[0] = ((r3 & 0xfff) << 3) | (r1 >> 29);
        g_usb_rx_intr[0] = ((r3 & 0xfffe000) >> 13);
        g_usb_tx_intr[1] = ((r0 & 0xfff) << 3) | (r3 >> 29);
        g_usb_rx_intr[1] = ((r0 & 0xfffe000) >> 13);
    }
    //0x00003cd8
    uint32_t fp_0x34 = g_usb_tx_intr[r7->bData_0xc];
    uint32_t r4 = g_usb_rx_intr[r7->bData_0xc];

    g_dma_nums--;

    //if (r4 != 0)
    {
        //0x00003d20
        //int fp_0x30 = &r7->Data_0x18;
        int r8 = 0;
        //int sb = &r5->Data_0xd0;
        //int sl = 0;
        //struct _hctrl_t* r6 = r5;

        while (r4 != 0)
        {
            //0x00003d38
            if (r4 & 0x01)
            {
                //0x00003d40
                uint32_t r1 = *((volatile uint32_t*)(r7->Data_4__ + 
                    0x600c + (((r7->bData_0xc * 32) + r8 + 0x6d) * 16)));
                
                struct Struct_0xe4_Inner_0x1c* r5_ = lookup_by_paddr(r5/*r6*/, r1 & ~0x1f);
                if (r5_ != NULL)
                {
                    //0x00003d74
                    struct _musb_transfer* td/*ip*/ = r5_->td;

                    InterruptLock(&r5->Data_0xd0/*sb*/);

                    if (td->flags & 0x800)
                    {
                        //0x00003db4
                        *((volatile uint32_t*)(r7->Data_0 + 0xd0)) &= 
                            ~(0x03 << ((r5_->Data_0x30->num - 1) << 1));

                        *((volatile uint32_t*)(r7->Data_0 + 0x74)) &= 
                            ~(0x03 << ((r5_->Data_0x30->num - 1) << 1));
                    }
                    //0x00003df8
                    InterruptUnlock(&r5->Data_0xd0/*sb*/);

                    (td->Func_0x3c)(r5/*r6*/, td, r5_->Data_0xc__, 0/*sl*/);

                    InterruptLock(&r5->Data_0xd0/*sb*/);
                    //0x00003e54
                    LIST_INSERT_HEAD(&r7->dma_free_q, r5_, link);
                    //0x00003e74
                    InterruptUnlock(&r5->Data_0xd0/*sb*/);
                }
                //0x00003e8c
            }
            //0x00003e8c
            r4 >>= 1;
            r8++;
        } //while (r4 != 0)
    }
    //0x00003e9c
    //if (fp_0x34 != 0)
    {
        //0x00003ea8
        //fp_0x48 = &r7->Data_0x18;
        int r8 = 0x10;
        int r6 = 0;
        int r4 = 0;
        int fp_0x30 = 0;
        //sl = 0x102;
        //sb = 0x4e1f;
        //fp_0x4c = &r5->Data_0xd0;
        //fp_0x3c = 0;
        //struct Struct_0xe4* fp_0x38 = r7;
        //r7 = fp_0x34;

        while (fp_0x34 != 0)
        {
            //0x00003edc
            if (fp_0x34/*r7*/ & 0x01)
            {
                //0x00003ee4
                uint32_t r1 = *((volatile uint32_t*)(r7/*fp_0x38*/->Data_4__ +
                    0x600c + (((r7/*fp_0x38*/->bData_0xc * 32) + fp_0x30 + 0x5d) * 16)));

                struct Struct_0xe4_Inner_0x1c* fp_0x34_ = lookup_by_paddr(r5, r1 & ~0x1f);
                if (fp_0x34_ != 0)
                {
                    //0x00003f24
                    struct _musb_transfer* td/*fp_0x44*/ = fp_0x34_->td;
                    int r3 = *((volatile uint16_t*)(r5->Data_0x14 + /*sl*/0x102 + r8));

                    while ((r6 <= 4) && (r4 <= 19999/*sb*/))
                    {
                        //0x00003f48
                        if (r3 & 0x03)
                        {
                            r6 = 0/*fp_0x3c*/;
                        }
                        else
                        {
                            r6++;
                        }
                        nanospin_ns(1000);

                        r4++;
                        r3 = *((volatile uint16_t*)(r5->Data_0x14 + /*sl*/0x102 + r8));
                    }
                    //0x00003f7c
                    if ((td != NULL) && (td->flags & 0x800))
                    {
                        //0x00003f94
                        (td->Func_0x3c)(r5, td, td->Data_0x10, 0);
                    }
                    //0x00003fac
                    InterruptLock(&r5->Data_0xd0/*fp_0x4c*/);
                    //0x00003fe4
                    LIST_INSERT_HEAD(&r7/*fp_0x38*/->dma_free_q, fp_0x34_, link);
                    //0x00004018
                    InterruptUnlock(&r5->Data_0xd0);
                }
                //0x00004030
            }
            //0x00004030
            r8 += 0x10;
            fp_0x34/*r7*/ >>= 1;
            fp_0x30++;
            //->0x00003edc
        } //while (fp_0x34 != 0)
    }
    //0x00004050
    if (usbss_intstat_Val[r7->bData_0xc] != 0)
    {
        //0x0000406c
        int sb = r7->bData_0xc << 2;
        //if (sb < ((r7->bData_0xc + 1) << 2))
        {
            //0x0000407c
            uint32_t fp_0x30 = (sb + 0x1008) << 2;
            uint32_t sl = sb << 2;

            sl = sl + 5;
            //r8 = r7;
            //r7 = r5;
            while (sb < ((r7->bData_0xc + 1) << 2))
            {
                //0x0000409c
                uint32_t r6 = *((volatile uint32_t*)(r7/*r8*/->Data_4__ + fp_0x30));
                if (r6 != 0)
                {
                    int r5_ = sl - 4;
                    while ((r5_ != sl)) // && (r6 != 0))
                    {
                        //0x000040b4
                        //int r5_ = sl - 4;
                        //0x000040b8
                        if (r6 & 0xff)
                        {
                            //0x000040c0
                            int r3 = r5_;
                            if (r5_ > 0x0f)
                            {
                                r3 = r5_ - 0x0f;
                            }

                            struct _musb_transfer* r4 = r5/*r7*/->Data_0xc4[r3];
                            if (r4 != NULL)
                            {
                                //0x000040dc
                                mentor_abort_dma_transfer(r5/*r7*/, r4->Data_0x30);

                                (r4->Func_0x3c)(r5/*r7*/, r4, 0, 8);
                            }
                            //0x00004100
                        }
                        //0x00004100
                        r5_++;
                        r6 >>= 8;
                        //->0x000040b8
                    }
                    //0x00004110
                }
                //0x00004110
                sb++;
                fp_0x30 += 4;
                sl += 4;
            } //while (sb < ((r7->bData_0xc + 1) << 2))
        }
        //0x0000413c
        usbss_intstat_Val[r7->bData_0xc] = 0;

    } //if (usbss_intstat_Val[r7->bData_0xc] != 0)
    //0x00004150
    if (g_dma_nums == 0)
    {
        *((volatile uint32_t*)(r7->Data_4__ + 0x20)) = 0;
    }
#endif

#if 1
    if (!SIMPLEQ_EMPTY(&r5->transfer_complete_q))
    {
        return &r5->intr_event;
    }
#endif

    return NULL;
}


static int create_bds(struct _hctrl_t* r6)
{
#ifdef MB86H60
#if 1
    fprintf(stderr, "create_bds: TODO!!!\n");
#endif
    return 0;
#else
    int sl;
    struct Struct_0xe4* r7 = r6->dma_hdl;

    r7->Data_8 = mmap(NULL, 0x8000/*0x200*0x40*/, 0xb00, 0x90002, -1, 0);
    if (r7->Data_8 == -1)
    {
        //0x00003110
        mentor_slogf(r6, 12, 2, 0,
            "devu-dm816x-mg.so : %s - failed to alloc descriptor ram",
            "create_bds");
        return 12;
        //->loc_33a0
    }
    //loc_3148
    off64_t fp_0x30;

    sl = mem_offset64(r7->Data_8, -1, 0x8000, &fp_0x30, NULL);
    if (sl != 0)
    {
        //0x00003168
        mentor_slogf(r6, 12, 2, 0,
            "devu-dm816x-mg.so : %s - failed to get bdesc paddr",
            "create_bds");
        //->loc_3394
        munmap(r7->Data_8, 0x8000);
        //->loc_33a0
        return sl;
    }
    //loc_319c
    off64_t sb = fp_0x30;

    g_linkram = mmap(NULL, 0x800, 0xb00, 0x90002, -1, 0);
    if (g_linkram == -1)
    {
        //0x000031d4
        mentor_slogf(r6, 12, 2, 0,
            "devu-dm816x-mg.so : %s - failed to alloc link ram",
            "create_bds");
        sl = 12;
        //->loc_3394
        munmap(r7->Data_8, 0x8000);
        //->loc_33a0
        return sl;
    }
    //loc_320c
    sl = mem_offset64(g_linkram, -1, 0x800, &fp_0x30, NULL);
    if (sl != 0)
    {
        //0x0000322c
        mentor_slogf(r6, 12, 2, 0,
            "devu-dm816x-mg.so : %s - failed to get linkram paddr",
            "create_bds");
        munmap(g_linkram, 0x800);
        //->loc_3394
        munmap(r7->Data_8, 0x8000);
        //->loc_33a0
        return sl;
    }
    //loc_3274
    *((volatile uint32_t*)(r7->Data_4__ + 0x4080)) = fp_0x30;
    *((volatile uint32_t*)(r7->Data_4__ + 0x4084)) = 0x200;
    *((volatile uint32_t*)(r7->Data_4__ + 0x5000)) = sb;
    *((volatile uint32_t*)(r7->Data_4__ + 0x5004)) = 0x104;
    *((volatile uint32_t*)(r7->Data_4__ + 0x4088)) = 0;
    *((volatile uint32_t*)(r7->Data_4__ + 0x5010)) = 0;
    *((volatile uint32_t*)(r7->Data_4__ + 0x5014)) = 0;
    *((volatile uint32_t*)(r7->Data_4__ + 0x2004)) = 0x1e;

    //r2 = sb;
    //r0 = 0x28;
    int r3;
    for (r3 = 0; r3 < 0x200; r3++) //, r2 += 0x40)
    {
        //loc_330c
        r7->Data_8[r3].Data_0x28 = (uint32_t)sb + (r3 * 0x40); //r2;
    }
    //0x00003328
    g_teardownbd_paddr = (uint32_t)sb + 0x1e2 * 0x40; ///*0x7880*/;
    //ip, =0x61ec
    //r0 = 0x28;
    for (r3 = 0x1E2; r3 < 0x200; r3++)
    {
        //loc_3344
        *((volatile uint32_t*)(r7->Data_4__ + 0x61ec)) = 
            r7->Data_8[r3].Data_0x28 | 0x0a;
    }
    //0x0000336c
    g_bdbase = r7->Data_8;

    return sl;
#endif
}


static int dma_init(struct _hctrl_t* r6)
{
    int sl;
    struct Struct_0xe4* r4_ = r6->dma_hdl;

    mentor_slogf(r6, 12, 2, 3, "devu-dm816x-mg.so: init dma");

#ifdef MB86H60 
    //Hard-coded: TODO: Get from args
    r4_->Data_0x10 = MB86H60_INTR_DMA;
#endif
    //0x0000305c
    r4_->Data_0x14 = InterruptAttach(r4_->Data_0x10, 
                            dma_interrupt_handler, r6, 0xe8, 0x08);
    if (r4_->Data_0x14 == -1)
    {
        //0x00003088
        sl = errno;

        mentor_slogf(r6, 12, 2, 0, "devu-dm816x-mg.so: %s - failed to attached dma intr",
            "dma_init");

        return sl;
    }
    //loc_30cc
#ifdef MB86H60
    r4_->Data_8 = mmap(NULL, 16/*size: TODO!!!*/ * 0x40, 0xb00, 0x90002, -1, 0);
#else
    if (dma_nums == 0)
    {
        //0x000030e0
        sl = create_bds(r6);
        if (sl != 0)
        {
            mentor_slogf(r6, 12, 2, 0,
                "devu-dm816x-mg.so : %s - failed to create BDs",
                "dma_init");
            //->loc_35bc
            return sl;
        }
        //0x0000337c
        struct Struct_0xe4* r0 = r6->dma_hdl;
        //int r2_; //r2 = 0;
        int r3; //r3 = 0;
        //r1 = 0x15c;
        //ip, [r8, r1] = BEB8 = dma_sched_table
        //->loc_33d4
        for (r3 = 0/*, r2_ = 0*/; r3 < 0x0f; r3++) //, r2_++)
        {
            //loc_33d4
            *((volatile uint32_t*)(r0->Data_4__ + 0x3800 + /*r2_*/r3 * 4)) = 
                dma_sched_table[r3];
        }
        //0x000033f8
        *((volatile uint32_t*)(r0->Data_4__ + 0x3000)) = 0x8000003b;
        //loc_3408
    } //if (dma_nums == 0)
    //loc_3408
    r4_->Data_8 = g_bdbase->Data_0[r4_->bData_0xc];
#endif
    r4_->dma_free_q.lh_first = NULL;
    r4_->dma_active_q.lh_first = NULL;
    //r5 = &r4_->Data_0x18;
    //ip = 0x34;
    //r0 = 0x38;
    uint32_t i;
#ifdef MB86H60
    for (i = 0; i < 16/*size: TODO!!!*/; i++)
    {
        //loc_3440
        LIST_INSERT_HEAD(&r4_->dma_free_q, &r4_->Data_8[i], link);
    }
#else
    for (i = 0; i < 241; i++)
    {
        //loc_3440
        LIST_INSERT_HEAD(&r4_->dma_free_q, &r4_->Data_8[i], link);
    }
    //0x00003484
    //int i/*r3*/;
    //r5, =0x280c
    //ip, =0x2810
    //r0, =0x2808
    //r1, =0x81004000 
    for (i = 0; i < 0x0f; i++)
    {
        //loc_3498
        uint32_t r2 = (r4_->bData_0xc * 15) + i/*r3*/;
        *((volatile uint32_t*)(r4_->Data_4__ + 0x280c/*r5*/ + r2 * 32)) = 
            r2 | (r2 << 16);

        r2 = (r4_->bData_0xc * 15) + i/*r3*/;
        *((volatile uint32_t*)(r4_->Data_4__ + 0x2810/*ip*/ + r2 * 32)) = 
            r2 | (r2 << 16);

        *((volatile uint32_t*)(r4_->Data_4__ + 0x2808/*r0*/ + ((r4_->bData_0xc * 15) + i/*r3*/) * 32)) = 
            (0x6d + i + r4_->bData_0xc * 32) | 0x81004000/*r1*/;

        *((volatile uint32_t*)(r4_->Data_4__ + 0x2800 + ((r4_->bData_0xc * 15) + i/*r3*/) * 32)) = 
            (0x5d + i + r4_->bData_0xc * 32) | 0x80000000;
    }
    //0x00003534
    *((volatile uint32_t*)(r4_->Data_4__ + 0x20)) = 0;

    if (r4_->bData_0xc == 0)
    {
        //0x00003550
        *((volatile uint32_t*)(r4_->Data_4__ + 0x2c)) = 0x305;
        *((volatile uint32_t*)(r4_->Data_4__ + 0x140)) = 0xfffefffe;
        //->loc_35a0
    }
    else if (r4_->bData_0xc == 1)
    {
        //0x0000357c
        *((volatile uint32_t*)(r4_->Data_4__ + 0x2c)) = 0xc05;
        *((volatile uint32_t*)(r4_->Data_4__ + 0x144)) = 0xfffefffe;
    }
    //loc_35a0
    dma_nums++;
#endif

    return 0;
}



/* 0x00002e08 - todo */
int mentor_board_specific_init1(struct _hctrl_t* r6)
{
#if 1
    fprintf(stderr, "mentor_board_specific_init1: TODO!!!\n");
#endif

    struct Struct_0xe4* r5;

    int sl;

    struct USB_Controller* r4 = r6->Data_0;

    r6->Data_0x38 = 0x400;
    r6->Data_0x18 = 16;
    r6->flags |= 0x200;
    r6->dma_hdl = r5 = calloc(1, 0x20);

    if (r5 == NULL)
    {
        mentor_slogf(r6, 12, 2, 0, "mentor_board_specific_init1: calloc error1\n"/*TODO*/);
        sl = 12;
        //->loc_35fc
        return sl;
    }
    //loc_2e90
#ifdef MB86H60
    r5->Data_4__ = dma_regs = mmap_device_memory(NULL/*void * addr*/,
                           MB86H60_DMA_SIZE/*size_t len*/,
                           0xb00/*int prot*/,
                           0x10001/*int flags*/,
                            MB86H60_DMA_BASE);
#else
    r5->Data_4__ = mmap_device_memory(NULL, 0x8000, 0xb00, 0x10001, 
                    0x47400000);
    if (r5->Data_4__ == -1)
    {
        mentor_slogf(r6, 12, 2, 0, "mentor_board_specific_init1: mmap_device_memory error1\n"/*TODO*/);
        sl = 12;
        //->loc_35f4
        free(r5);
        return sl;
    }
    //loc_2ef0
    r5->Data_0 = r5->Data_4__ + 
        ((struct pci_dev_info*)(r4->pci_inf))->CpuBaseAddress[0] - 0x47400400;

    if (((struct pci_dev_info*)(r4->pci_inf))->CpuBaseAddress[0] == 0x47401c00)
    {
        r5->bData_0xc = 1;
    }
    else
    {
        //loc_2f78
        r5->bData_0xc = 0;
    }
    //loc_2f80
    ((volatile uint32_t*)(r5->Data_0))[0x14/4] = 1;

    while (((volatile uint32_t*)(r5->Data_0))[0x14/4] & 1)
    {
        //loc_2fa8
        delay(1);
    }
    //loc_2fc4
    ((volatile uint32_t*)(r5->Data_0))[0xe8/4] = 0;
    ((volatile uint32_t*)(r5->Data_0))[0xe0/4] = 2;
    ((volatile uint32_t*)(r5->Data_0))[0x70/4] = 0;
    ((volatile uint32_t*)(r5->Data_0))[0x74/4] = 0;
    ((volatile uint32_t*)(r5->Data_0))[0x14/4] &= ~0x10;
    ((volatile uint32_t*)(r5->Data_0))[0xd0/4] = 0;
#endif

    mentor_fifo_init(r6, r6->fconfig_string);

    if ((r6->flags & 1) == 0)
    {
        sl = 0;
        //->loc_35fc
        return sl;
    }
    //0x00003030
    r5->Data_0x10 = 0x11;

    sl = dma_init(r6);
    if (sl != 0)
    {
        //->loc_35bc
        mentor_slogf(r6, 12, 2, 0, 
            "devu-dm816x-mg.so : %s - couldn't init the dma... restart the driver with nodma option",
            "mentor_board_specific_init1");

#ifdef MB86H60
        munmap_device_memory(r5->Data_4__, MB86H60_DMA_SIZE);
#else
        munmap_device_memory(r5->Data_4__, 0x8000);
#endif
        //loc_35f4
        free(r5);
    }
    //loc_35fc
    return sl;
}


/* 0x000029b4 - complete */
int mentor_board_specific_init2(struct _hctrl_t* ctrl)
{
#if 0
    fprintf(stderr, "mentor_board_specific_init2: TODO!!!\n");
#endif

#ifdef MB86H60

    MGC_Write16(ctrl, MGC_O_HDRC_INTRTXE, 0xffff);
    MGC_Write16(ctrl, MGC_O_HDRC_INTRRXE, 0xfffe);
    MGC_Write8(ctrl, MGC_O_HDRC_INTRUSBE, (1 << 4)); //0xff);

    uint32_t dma_usb_int_mask = 0x7f;
    dma_usb_int_mask &= ~(1 << 0); //Bit 0: USB General IRQ
//    dma_usb_int_mask &= ~(7 << 1); //Bit 1...3: USB DMA Endpoint Write Request IRQ
//    dma_usb_int_mask &= ~(7 << 4); //Bit 4...6: USB DMA Endpoint Read Request IRQ
//    dma_usb_int_mask &= ~(1 << 5);
    dma_SetUsbIntMask(ctrl, dma_usb_int_mask); 

#else
    struct Struct_0xe4* r3 = ctrl->dma_hdl;

    ((volatile uint32_t*)(r3->Data_0))[0x40/4] = 0xfffeffff; //Rx/Tx?
    ((volatile uint32_t*)(r3->Data_0))[0x44/4] = 0x1ff; //Usb Core?

    ((volatile uint16_t*)(ctrl->Data_0x14))[0x06/2] = 0xffff; //INTRTXE?
    ((volatile uint16_t*)(ctrl->Data_0x14))[0x08/2] = 0xfffe; //INTRRXE?
    ((volatile uint8_t*)(ctrl->Data_0x14))[0x0b] = /*0xf6;*/ //INTRUSBE
        (1 << 7)/*VBus Error?*/ |
        (1 << 6)/*Sess Req*/ |
        (1 << 5)/*Discon*/ |
        (1 << 4)/*Conn*/ |
        (1 << 2)/*Reset/Babble*/ |
        (1 << 1)/*Resume*/;

    ((volatile uint32_t*)(r3->Data_0))[0x38/4] = 0xfffeffff;
    ((volatile uint32_t*)(r3->Data_0))[0x3c/4] = 0x1ff;
#endif

    return 0;

}


int mentor_board_specific_shutdown2(struct _hctrl_t* ctrl)
{
#if 1
    fprintf(stderr, "mentor_board_specific_shutdown2: TODO!!!\n");
#endif

    return 0;

}


int mentor_board_specific_shutdown1(struct _hctrl_t* a)
{
#if 1
    fprintf(stderr, "mentor_board_specific_shutdown1: TODO!!!\n");
#endif

    return 0;

}


int MENTOR_FreeED(struct _hctrl_t* a)
{
#if 1
    fprintf(stderr, "MENTOR_FreeED: TODO!!!\n");
#endif

    return 0;
}


int MENTOR_FreeTD(struct _hctrl_t* a)
{
#if 1
    fprintf(stderr, "MENTOR_FreeTD: TODO!!!\n");
#endif

    return 0;
}


int mentor_destroy_completion_thread(struct USB_Controller* a)
{
#if 1
    fprintf(stderr, "mentor_destroy_completion_thread: TODO!!!\n");
#endif

    return 0;
}


char* mentor_opts[] = 
{
    "verbose",
    "num_ed",
    "num_td",
    "prio",
    "dirq",
    "nodma",
    "fconfig",
    "dma_reserve",
    "num_dma",
    "isoc_pio",
    "no_cfg_pmic",
    "ctrl_noping",
    0,
};


/* 0x0000615c - todo */
int mentor_controller_init(struct USB_Controller* r7, int b, char* r5)
{
    fprintf(stderr, "mentor_controller_init: r5='%s'\n", r5);

    struct _hctrl_t* r4;

#ifdef MB86H60
    r7->cname = "mb86h60";
#else
    r7->cname = "dm816x";
#endif

    if ((r7->hc_data = r4 = calloc(1, sizeof(struct _hctrl_t))) == NULL)
    {
        return 12;
    }

    r4->Data_0 = r7;
    r4->Data_0x58 = 0x18;
    r4->verbosity = 5; //0;
    r4->Data_0x70 = 0xaa;
    r4->num_td = 0x60;
    r4->Data_0x7c = 1000;
    r4->Data_0x6c = 0x04;
    r4->flags = 0x40 | 0x04 | 0x01/*dma?*/;
    r4->Data_0x2c = -1;
    r4->Data_0x28 = -1;
    r4->Data_0x18 = 4;
    r4->Data_0x38 = 0x200;

    pthread_mutexattr_t mattr; //fp_0x48;
    char* fp_0x4c = r5;
    char* fp_0x50;
    struct sched_param fp_0x78;
    pthread_attr_t fp_0xc4;

    if (r5 != NULL)
    {
        //loc_6414
        //r8 = &fp_0x4c;
        //sl = 0xf0;
        while (r5[0] != 0)
        {
            //loc_6218
            switch (getsubopt(&fp_0x4c, mentor_opts, &fp_0x50))
            {
                case 0:
                    //loc_6264: "verbose"
                    if (fp_0x50 == NULL)
                    {
                        r4->verbosity = 5;
                    }
                    else
                    {
                        r4->verbosity = strtol(fp_0x50, 0, 10);
                    }
                    //->loc_6404
                    break;

                case 5:
                    //loc_6328?: "nodma"
                    r4->flags &= ~1;
                    //->loc_6404
                    break;

                case 6:
                    //loc_6338: "fconfig"
                    if (fp_0x50 != NULL)
                    {
                        r4->fconfig_string = strdup(fp_0x50);
                    }
                    //->loc_6404
                    break;

                default:
                    //loc_63d4
#if 0
                    mentor_slogf(r4, 12, 2, 0, "%s : %s - Unknown option %s", "", "", fp_0x50);
#endif
                    break;
            }
            //loc_6404
            r5 = fp_0x4c;
            if (r5 == NULL)
            {
                //->loc_6448
                break;
            }
        } //while (r5[0] != 0)
        //loc_6448
    }
    //loc_6448
    r7->MaxTransferSize = 0x8000;

    pthread_mutexattr_init(&mattr);
    pthread_mutexattr_setrecursive(&mattr, 2);
    int res = pthread_mutex_init(&r4->Data_4/*r8*/, &mattr);
    if (res != 0)
    {
        mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to initialize mutex", "", "");
        //->loc_69d4
        free(r4);
        return res;
    }
    //loc_64c0
    res = pthread_mutex_init(&r4->Data_0xc/*sl*/, &mattr);
    if (res != 0)
    {
        mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to initialize mutex", "", "");
        //->loc_69cc
        pthread_mutex_destroy(&r4->Data_4/*r8*/);
        free(r4);
        return res;
    }
    //loc_6518
    r4->Data_0x14 = mmap_device_memory(NULL/*void * addr*/,
                           0x2000/*size_t len*/,
                           0xb00/*int prot*/,
                           0x10001/*int flags*/,
#ifndef MB86H60
                            0);
//                           *(uint64_t*)(char*)&(r7->Data_4->Data_0x68)/*uint64_t physical*/);
                            //UNALIGNED_RET64(r7->Data_4->Data_0x68_));
                            //ENDIAN_BE64(*((uint64_t*)(r7->Data_4->Data_0x68_))));
#else
                            MB86H60_USB_BASE);
#endif
    if (r4->Data_0x14 == -1)
    {
        return errno;
    }
    //loc_6584
    struct _hctrl_t* sb = r7->hc_data;

    sb->chid = ChannelCreate(0x08);
    if (sb->chid < 0)
    {
        mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to create channel", "", "");
        //->loc_66f8
        //TODO!!!
    }
    else
    {
        //loc_65e4
        sb->coid = ConnectAttach(0, 0, sb->chid, 0x40000000, 0);
        if (sb->coid < 0)
        {
            mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to connect to channel", "", "");
            //->loc_66f0
            //TODO
        }
        else
        {
            //loc_6648
            pthread_attr_init(&fp_0xc4/*r5*/);
            pthread_attr_setschedpolicy(&fp_0xc4, 2);
            fp_0x78.sched_priority = sb->Data_0x58;
            pthread_attr_setschedparam(&fp_0xc4, &fp_0x78);
            pthread_attr_setinheritsched(&fp_0xc4, 2);
            pthread_attr_setdetachstate(&fp_0xc4, 1);

            res = pthread_create(&sb->Data_0x3c, &fp_0xc4, mentor_interrupt_thread, r7);
            if (res != 0)
            {
                mentor_slogf(r4, 12, 2, 0, "%s : %s - Unable to create interrupt thread", "", "");

                ConnectDetach(sb->coid);
                //loc_66f0
                ChannelDestroy(sb->chid);
                //loc_66f8
                //TODO!!!
            }
            else
            {
                //loc_6700
                struct _hctrl_t* r2 = r7->hc_data;

                r7->AvailableBandwidth = 1000;
                r7->capabilities = 0x4000064f;
                r7->MaxTransferSize = 0x8000;
                r7->MaxUnalignedTransferSize = 0x8000;
                r7->buff_alignment_mask = 3;

                if ((r2->flags & 0x01) == 0)
                {
                    r7->capabilities = 0x4000044f;
                }

                res = MENTOR_AllocateTD(r4);
                if (res != 0)
                {
                    //->loc_69a8
                }
                else
                {
                    res = MENTOR_AllocateED(r4);
                    if (res != 0)
                    {
                        //->loc_69a0
                    }
                    else
                    {
                        res = MENTOR_BuildEDList(r4, &r4->Data_0xac);
                        if (res != 0)
                        {
                            //->loc_6998
                        }
                        else
                        {
                            res = MENTOR_BuildEDList(r4, &r4->Data_0xb0);
                            if (res != 0)
                            {
                                //->loc_6998
                            }
                            else
                            {
                                r4->Data_0xbc = r4->Data_0xb0;

                                res = MENTOR_BuildEDList(r4, &r4->Data_0xb8);
                                if (res != 0)
                                {
                                    //->loc_6998
                                }
                                else
                                {
                                    r4->Data_0xc0 = r4->Data_0xb8;

                                    res = MENTOR_BuildEDList(r4, &r4->Data_0xb4);
                                    if (res != 0)
                                    {
                                        //->loc_6998
                                    }
                                    else
                                    {
                                        //0x000067b8
                                        res = mentor_board_specific_init1(r4);
                                        if (res != 0)
                                        {
                                            mentor_slogf(r4, 12, 2, 0, "%s : %s - mentor_board_specific_init1 failed", "", "");
                                            //->loc_6998
                                        }
                                        else
                                        {
                                            //loc_6808
#ifdef MB86H60
                                            MGC_Write8(r4, MGC_O_HDRC_TESTMODE, 0);
                                            MGC_Write8(r4, MGC_O_HDRC_DEVCTL, 0);
#else
                                            ((volatile uint8_t*)(r4->Data_0x14))[0x0f] = 0;
                                            ((volatile uint8_t*)(r4->Data_0x14))[0x60] = 0;
                                            ((volatile uint32_t*)(r4->Data_0x14))[0x414/4] = 0;
                                            ((volatile uint32_t*)(r4->Data_0x14))[0x404/4] = 0x1008;
#endif

                                            res = mentor_board_specific_init2(r4);
                                            if (res != 0)
                                            {
                                                mentor_slogf(r4, 12, 2, 0, "%s : %s - mentor_board_specific_init2 failed", "", "");
                                                //->loc_6990
                                            }
                                            else
                                            {
                                                //loc_6898
                                                r4->Data_0xc4 = calloc(r4->Data_0x18, 4);
                                                if (r4->Data_0xc4 == NULL)
                                                {
                                                    mentor_slogf(r4, 12, 2, 0, "%s : %s - calloc failed", "", "");
                                                    //->loc_6984
                                                }
                                                else
                                                {
                                                    //loc_68f0
                                                    r4->Data_0xc8 = calloc(r4->Data_0x18, 4);
                                                    if (r4->Data_0xc8 == NULL)
                                                    {
                                                        mentor_slogf(r4, 12, 2, 0, "%s : %s - calloc failed", "", "");
                                                        free(r4->Data_0xc4);
                                                        //->loc_6984
                                                        //TODO!!!
                                                    }
                                                    else
                                                    {
                                                        //loc_6950
                                                        r4->flags |= 0x10;

#ifdef MB86H60
                                                        MGC_Write8(r4, MGC_O_HDRC_POWER,
                                                            MGC_M_POWER_SOFTCONN|MGC_M_POWER_HSENAB);
                                                        MGC_Write8(r4, MGC_O_HDRC_DEVCTL, MGC_M_DEVCTL_SESSION);
#else
                                                        ((volatile uint8_t*)(r4->Data_0x14))[0x01] = 0x60;
                                                        ((volatile uint8_t*)(r4->Data_0x14))[0x60] = 0x01;
#endif

                                                        return 0;
                                                    }
                                                }
                                                //loc_6984
                                                mentor_board_specific_shutdown2(r4);
                                                res = 12;
                                            }
                                            //loc_6990
                                            mentor_board_specific_shutdown1(r4);
                                        }
                                    }
                                }
                            }
                        }
                        //loc_6998
                        MENTOR_FreeED(r4);
                    }
                    //loc_69a0
                    MENTOR_FreeTD(r4);
                }
                //loc_69a8
                InterruptDetach(r4->intr_id);
                mentor_destroy_completion_thread(r7);
                //loc_69b8
                munmap_device_memory(r4->Data_0x14, 0x2000);
                //loc_69c4
                pthread_mutex_destroy(&r4->Data_0xc/*sl*/);
                //loc_69cc
                pthread_mutex_destroy(&r4->Data_4/*r8*/);
                //loc_69d4
                free(r4);
            }
        }
    }

    return res;
}


void mentor_ulpi_write()
{
    fprintf(stderr, "mentor_ulpi_write: TODO!!!\n");

}


void mentor_board_specific_reset()
{
    fprintf(stderr, "mentor_board_specific_reset: TODO!!!\n");

}


/* 0x00006b1c - todo */
int mentor_check_port_status(struct USB_Controller* a, uint32_t* b)
{
    struct _hctrl_t* r4 = a->hc_data;

#if 0
    fprintf(stderr, "mentor_check_port_status: r4->Data_0x6c=0x%x\n", r4->Data_0x6c);
#endif

    if (r4->Data_0x6c & 0x04)
    {
        *b = 0;
    }
    else
    {
        *b = 1;

        r4->Data_0x6c |= 0x04;

        if ((r4->Data_0x6c & 0x02) == 0)
        {
#ifdef MB86H60
            if ((MGC_Read8(r4, MGC_O_HDRC_DEVCTL) & MGC_M_DEVCTL_SESSION) == 0)
            {
                uint8_t r3 = MGC_Read8(r4, MGC_O_HDRC_DEVCTL);
#else
            if ((((volatile uint8_t*)(r4->Data_0x14))[0x60] & (1 << 0)/*Session?*/) == 0)
            {
                uint8_t r3 = ((volatile uint8_t*)(r4->Data_0x14))[0x60];
#endif

                mentor_slogf(r4, 12, 2, 1, "%s - %s: Session off %x, trying to recover ...",
                    "devu-dm816x-mg.so", "mentor_check_port_status", r3);

                delay(10);

                if (r4->flags & 0x100)
                {
                    mentor_ulpi_write(r4, 0x05, 0x20);

                    delay(5);
                    //->loc_6bf4
                }
                else
                {
                    //loc_6bec
                    mentor_board_specific_reset(r4);
                }
                //loc_6bf4
#ifdef MB86H60
                MGC_Write8(r4, MGC_O_HDRC_DEVCTL, MGC_M_DEVCTL_SESSION);
#else
                ((volatile uint8_t*)(r4->Data_0x14))[0x60] = 1;
#endif

                delay(1);

#ifdef MB86H60
                if ((MGC_Read8(r4, MGC_O_HDRC_DEVCTL) & MGC_M_DEVCTL_SESSION) == 0)
                {
                    uint8_t r3 = MGC_Read8(r4, MGC_O_HDRC_DEVCTL);
#else
                if ((((volatile uint8_t*)(r4->Data_0x14))[0x60] & (1 << 0)/*Session?*/) == 0)
                {
                    //0x00006c18
                    uint8_t r3 = ((volatile uint8_t*)(r4->Data_0x14))[0x60];
#endif

                    mentor_slogf(r4, 12, 2, 1, "%s - %s: Session recover failed %x",
                        "devu-dm816x-mg.so", "mentor_check_port_status", r3);
                    //->loc_6c9c
                }
                else
                {
                    //loc_6c60
                    mentor_slogf(r4, 12, 2, 1, "%s - %s: Session recover sucessful",
                        "devu-dm816x-mg.so", "mentor_check_port_status");
                }
            } //if ((((volatile uint8_t*)(r4->Data_0x14))[0x60] & (1 << 0)/*Session?*/) == 0)
            //loc_6c9c
        } //if ((r4->Data_0x6c & 0x02) == 0)
        //loc_6c9c
    }
    //loc_6c9c
    return 0;
}


/* 0x00004f00 - complete */
int mentor_check_device_connected(struct USB_Controller* a, int b)
{
#if 1
    fprintf(stderr, "mentor_check_device_connected: b = %d, TODO!!!\n", b);
#endif

    return ((a->hc_data->Data_0x6c & 0x02) == 0)? -1: 0;
}


/* 0x00005044 - complete */
int mentor_clear_port_feature(struct USB_Controller* a, int b, int c)
{
#if 1
    fprintf(stderr, "mentor_clear_port_feature: b=%d, c=%d, TODO!!!\n", b, c);
#endif

    struct _hctrl_t* ctrl = a->hc_data;

    switch (c)
    {
        case 3:
#ifdef MB86H60
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) & ~MGC_M_POWER_SUSPENDM);
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) | MGC_M_POWER_SUSPENDM);
#else
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] &= ~(1 << 1);
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] |= (1 << 1);
#endif

            delay(20);

#ifdef MB86H60
            if (MGC_Read8(ctrl, MGC_O_HDRC_POWER) & MGC_M_POWER_SUSPENDM)
#else
            if (((volatile uint8_t*)(ctrl->Data_0x14))[1] & (1 << 1))
#endif
            {
                return -1;
            }
            break;
    }

    return 0;
}


/* 0x000050a8 - complete */
int mentor_set_port_feature(struct USB_Controller* a, int b, int c)
{
#if 1
    fprintf(stderr, "mentor_set_port_feature: b=%d, c=%d, TODO!!!\n", b, c);
#endif

    struct _hctrl_t* ctrl = a->hc_data;

    switch (c)
    {
        case 2:
            //loc_50cc
#ifdef MB86H60

#if 1
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) | MGC_M_POWER_RESET);
#endif
            {
                uint8_t bData = MGC_Read8(ctrl, MGC_O_HDRC_POWER);
                uint16_t wData = MGC_Read16(ctrl, 0x12);
                fprintf(stderr, "bData=0x%02x, wData=0x%04x\n", bData, wData);
            }
#else
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] |= (1 << 3);
#endif

            delay(20);

#ifdef MB86H60

#if 1
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) & ~MGC_M_POWER_RESET);
#endif

            {
                uint8_t bData = MGC_Read8(ctrl, MGC_O_HDRC_POWER);
                uint16_t wData = MGC_Read16(ctrl, 0x12);
                fprintf(stderr, "bData=0x%02x, wData=0x%04x\n", bData, wData);
            }

#else
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] &= ~(1 << 3);
#endif
            break;

        case 3:
            //loc_50f8
#ifdef MB86H60
            MGC_Write8(ctrl, MGC_O_HDRC_POWER, 
                MGC_Read8(ctrl, MGC_O_HDRC_POWER) | MGC_M_POWER_SUSPENDM);
#else
            ((volatile uint8_t*)(ctrl->Data_0x14))[1] |= (1 << 1);
#endif
            break;

        default:
            break;
    }

    return 0;
}


/* 0x00005110 - complete */
int mentor_get_root_device_speed(struct USB_Controller* a, int b)
{
#if 1
    fprintf(stderr, "mentor_get_root_device_speed: b=%d, TODO!!!\n", b);
#endif

    struct _hctrl_t* ctrl = a->hc_data;

    delay(200);

#ifdef MB86H60
    if ((MGC_Read8(ctrl, MGC_O_HDRC_DEVCTL) & MGC_M_DEVCTL_LSDEV) != 0)
    {
        return 1;
    }
    else if ((MGC_Read8(ctrl, MGC_O_HDRC_POWER) & MGC_M_POWER_HSMODE) != 0)
    {
        return 2;
    }
#else
    if ((((volatile uint8_t*)(ctrl->Data_0x14))[0x60] & 0x20) != 0)
    {
        return 1;
    }
    else if ((((volatile uint8_t*)(ctrl->Data_0x14))[0x01] & 0x10) != 0)
    {
        return 2;
    }
#endif

    return 0;
}


int mentor_get_timer_from_controller(struct USB_Controller* a)
{
#if 1
    fprintf(stderr, "mentor_get_timer_from_controller: TODO!!!\n");
#endif

    return 0;
}



/* 5278 - todo */
void MENTOR_PutEDPool(struct _hctrl_t* r4, struct Struct_0xa4* r5)
{
#if 1
    fprintf(stderr, "MENTOR_PutEDPool: TODO!!!\n");
#endif

}


/* 99d0 - todo */
int MENTOR_InitializeEndpoint(struct _hctrl_t* r7, 
    struct USB_Controller_Inner_0x7c* r5, 
    struct Struct_112b08* r4)
{
#if 1
    fprintf(stderr, "MENTOR_InitializeEndpoint: TODO!!!\n");
#endif

    struct Struct_0xa4* r1 = r4->Data_0xc;
    if (r1 == NULL)
    {
        r1 = MENTOR_GetEDPool(r7);
        if (r1 == NULL)
        {
            mentor_slogf(r7, 12, 2, 1, "%s - No ED for Endpoint",
                "devu-dm816x-mg.so");

            return 12;
        }
        //9a40
        r4->Data_0xc = r1;
        r1->Data_0x34 = r4;
        r1->num = -1;
    }
    //9a50
    r1->transferType = r4->endpoint_descriptor.bmAttributes & 0x03;
    r1->mps = r4->endpoint_descriptor.wMaxPacketSize;
    r1->bData_0x1b = r4->endpoint_descriptor.bEndpointAddress & ~0x7f;
    r1->Data_0x20 = 0;
    r1->Data_0x14 = ((r5->device_address & 0x7f) << 4) | 
            (r4->endpoint_descriptor.bEndpointAddress & 0x0f);

    switch (r5->bData_0xc & 0x03)
    {
        case 1:
            r1->bData_0x1c = 0xc0;
            break;

        case 2:
            r1->bData_0x1c = 0x40;
            break;

        case 0:
            r1->bData_0x1c = 0x80;
            break;
    }
    //9ac4
    r1->Data_0x24 = r4->endpoint_descriptor.bInterval;

    if ((r1->bData_0x1c != 0x40) &&
        (r5->Data_0x1c != NULL))
    {
        struct USB_Controller_Inner_0x7c* r3;
        while (1)
        {
            //9ae4
            r3 = r5->Data_0x1c;

            if (r3->bData_0xc == 2)
            {
                break;
            }

            if (r3->Data_0x1c == NULL)
            {
                break;
            }
            
            r5 = r3;
        }
        //9b04
        if (r5 == NULL)
        {
            MENTOR_PutEDPool(r7, r1);

            return -1;
        }
        //9b1c
        r1->bData_0x1d = r3->device_address;
        r1->bData_0x1e = r5->Data_0x20;

        return 0;
    }
    //9b34
    return 0;
}


/* 0x00004384 - complete */
void mentor_fifo_free(struct _hctrl_t* a, struct fp_0x34_Inner_0x18_Inner_0x10* b)
{
#if 0
    fprintf(stderr, "mentor_fifo_free\n");
#endif

    b->Data_0xc->Data_0xc |= (1 << b->Data_8);
}



/* 0x000029b0 - complete */
void mentor_free_dma_sched()
{
#if 0
    fprintf(stderr, "mentor_free_dma_sched\n");
#endif

}


/* 0x000025c0 - complete */
int mentor_free_dma_channel()
{
#if 0
    fprintf(stderr, "mentor_free_dma_channel\n");
#endif

    return 0;
}



/* 0x00005ab4 - todo */
int MENTOR_FreeEtd(struct _hctrl_t* r6, struct Struct_0xa4* r4)
{
#if 0
    fprintf(stderr, "MENTOR_FreeEtd: TODO!!!\n");
#endif

    int r5 = r4->num;

    if (r4->Data_0x30 != NULL)
    {
        mentor_fifo_free(r6, r4->Data_0x30);
    }

    r4->Data_0x30 = NULL;

    if (r4->Data_0x38 != 0)
    {
        //0x00005aec
        mentor_free_dma_sched(r6);

        r4->Data_0x38 = 0;
    }
    //loc_5afc
    if (r4->Data_0x2c != -1)
    {
        mentor_free_dma_channel(r6);

        r4->Data_0x2c = -1;
    }
    //loc_5b18
    if ((r5 > 0) && (r5 < r6->Data_0x18))
    {
        //0x00005b2c
        r4->num = -1;
        r4->Data_0x2c = -1;

        r6->Data_0xc8[r5] = NULL;
        //->loc_5b4c
    }
    else
    {
        //loc_5b48
        r5 = -1;
    }

    return r5;
}


/* 51b4 - todo */
int MENTOR_HookED(struct _hctrl_t* a, 
    struct Struct_0xa4* r6, 
    struct Struct_0xa4* r4)
{
#if 0
    fprintf(stderr, "MENTOR_HookED: TODO!!!\n");
#endif

    if (pthread_mutex_lock(&a->Data_4) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x2f2);
    }
    //5204
    r6->Data_4->Data_0 = r4;
    r4->Data_0 = r6;
    r6->Data_4 = r4;
    r4->Data_4 = r6->Data_4;
    r4->Data_8__ = NULL;
    r4->Data_0xc = &r4->Data_8__;

    if (pthread_mutex_unlock(&a->Data_4) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x2fd);
    }

    return 0;
}


/* 0x00009bb8 - complete */
int mentor_int_endpoint_enable(struct USB_Controller* a, 
    struct USB_Controller_Inner_0x7c* b, 
    struct Struct_112b08* r6)
{
#if 1
    fprintf(stderr, "mentor_int_endpoint_enable: a=%p, b=%p, c=%p\n",
        a, b, r6);
#endif

    struct _hctrl_t* r5 = a->hc_data;
    struct Struct_0xa4* r4 = r6->Data_0xc;

    int res = MENTOR_InitializeEndpoint(r5, b, r6);

    if ((res == 0) && (r4 == NULL))
    {
        MENTOR_HookED(r5, r5->Data_0xb8, r6->Data_0xc);
    }
    else 
    {
        //loc_9bfc
        if ((r4 != NULL) && (r4->num > 0))
        {
            MENTOR_FreeEtd(r5, r4);
        }
    }

    return res;    
}



/* 9c9c - complete */
int mentor_ctrl_endpoint_enable(struct USB_Controller* a, 
    struct USB_Controller_Inner_0x7c* b, 
    struct Struct_112b08* c)
{
#if 1
    fprintf(stderr, "mentor_ctrl_endpoint_enable: a=%p, b=%p, c=%p\n",
        a, b, c);
#endif

    struct _hctrl_t* r5 = a->hc_data;
    struct Struct_0xa4* r7 = c->Data_0xc;

#if 1
    fprintf(stderr, "mentor_ctrl_endpoint_enable: r5=%p, r7=%p\n",
        r5, r7);
#endif

    int res = MENTOR_InitializeEndpoint(r5, b, c);

    if (res == 0)
    {
        if (r7 == NULL)
        {
            c->Data_0xc->Data_0x24 = 0;

            MENTOR_HookED(r5, r5->Data_0xac, c->Data_0xc);
        }
    }

    return res;
}


/* 0x00008184 - todo */
struct _musb_transfer* MENTOR_TD_Setup(struct _hctrl_t* a, 
    struct Struct_10bab4* b, struct Struct_0xa4* c, int flags)
{
#if 0
    fprintf(stderr, "MENTOR_TD_Setup: TODO!!!\n");
#endif

    struct _musb_transfer* td; //r4

    InterruptLock(&a->Data_0xd0);

    td = SIMPLEQ_FIRST(&a->transfer_free_q);
    if (td == NULL)
    {
        b->Data_8 = 12;

        InterruptUnlock(&a->Data_0xd0);

        mentor_slogf(a, 12, 2, 1, "%s - No TD's available",
            "devu-dm816x-mg.so");
    }
    else
    {
        SIMPLEQ_REMOVE_HEAD(&a->transfer_free_q, link);

        InterruptUnlock(&a->Data_0xd0);

        td->flags = flags & 0x8000003f;
        td->bytes_xfered = 0;
        td->status = 0;
        td->Data_0x30 = c;
        td->Data_0x34 = b;
    }

    return td;
}


/* 0x00004628 - todo */
void MENTOR_ReadFIFO(struct _hctrl_t* a, 
    struct _musb_transfer* b, uint16_t r6, int d, uint16_t r7)
{
#ifdef MB86H60
#if 0
    fprintf(stderr, "MENTOR_ReadFIFO: b=%d, r8=%d\n", b, r8);
#endif
    int i;
    for (i = 0; i < r7; i++)
    {
#if 0
        fprintf(stderr, "MENTOR_ReadFIFO: c[%d]=0x%02x\n", i, ((uint8_t*)c)[i]);
#endif

        ((uint8_t*)d)[i] = MGC_Read8(a, MGC_FIFO_OFFSET(r6));
    }
#else
    if (r7 > 3)
    {
        //0x00004640
        //TODO!!!
    }
    //loc_4688
    if (r7 != 0)
    {
        //0x00004690
        uint32_t r2;

        r2 = ((volatile uint32_t*)(a->Data_0x14))[MGC_FIFO_OFFSET(r6)/4];

        if (r7 & 2)
        {
            uint16_t wData = r2 & 0xffff;
            *((uint16_t*)d) = wData;
            d += 2;
            r2 >>= 16;
        }

        if (r7 & 1)
        {
            uint8_t bData = r2 & 0xff;
            *((uint8_t*)d) = bData;
        }
    }
#endif
    //loc_46c0
}



/* 0x000046c8 - todo */
void MENTOR_LoadFIFO(struct _hctrl_t* a, uint16_t b, int c, uint16_t r8)
{
#ifdef MB86H60
#if 0
    fprintf(stderr, "MENTOR_LoadFIFO: b=%d, r8=%d\n", b, r8);
    hex_dump("MENTOR_LoadFIFO", c, r8);
#endif
    int i;
    for (i = 0; i < r8; i++)
    {
        MGC_Write8(a, MGC_FIFO_OFFSET(b), ((uint8_t*)c)[i]);
    }
#else
    int r7;
    int r6;
    int r5;

//    b &= 0xffff;
//    uint16_t r8 = d & 0xffff;

    if (r8 > 3)
    {
//        r6 = b * 4;
        r8 -= 4;
        r7 = r8 / 4;
        //r5 = c + 4 + r7 * 4;
        uint32_t* r3 = c;
        
        do
        {
            //loc_4704
            ((volatile uint32_t*)(a->Data_0x14))[MGC_FIFO_OFFSET(b)/4] = *r3++;
        }
        while (r3 != /*r5*/(c + 4 + r7 * 4));
        
        r7++;
        c = c + r7 * 4;
        r8 = r8 & 0x03;
    }
    //loc_472c
    if (r8 & 2)
    {
        ((volatile uint16_t*)(a->Data_0x14))[MGC_FIFO_OFFSET(b)] = *((uint16_t*)c);
        c += 2;
    }
    if (r8 & 1)
    {
        ((volatile uint8_t*)(a->Data_0x14))[MGC_FIFO_OFFSET(b)] = *((uint8_t*)c);
    }
#endif
}


/* 0x00005b54 - todo */
int mentor_transfer_abort(struct USB_Controller* a, 
        struct Struct_10bab4* b, struct Struct_112b08* r5_)
{
#if 0
    fprintf(stderr, "mentor_transfer_abort: TODO!!!\n");
#endif

    struct _hctrl_t* r4 = a->hc_data;

    if (pthread_mutex_lock(&r4->Data_4/*r7*/) != 0)
    {
        //0x00005b88
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x38b);
    }
    //0x00005ba8
    struct Struct_0xa4* r5;
    int r8;

    if (((r5 = r5_->Data_0xc) == NULL) || ((r8 = r5->num) < 0))
    {
        //0x00005bc0
        if (pthread_mutex_unlock(&r4->Data_4/*r7*/) != 0)
        {
            //0x00005bd8
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
                0x38e);
        }
        
        return 2;
    }
    //0x00005c00
    struct _musb_transfer* r2 = r5->Data_8__;
    r5->bData_0x1f = 1;
    if (r8 == 0)
    {
        //0x00005c14
        HW_Write16(r4, MUSB_CSR0, 0x100);
        //->0x00005d40
    }
    else
    {
        //0x00005c2c
        if (r5->bData_0x1b & 0x80)
        {
            //0x00005c38
            if ((r2 != NULL) && (r2->flags & 0x600))
            {
                MENTOR_AbortDMA_RX(r4, r5);
            }
            //0x00005c58
            HW_Write8(r4, 0x10d + r8*16, 0);
            HW_Write8(r4, 0x10b + r8*16, 0);
            uint32_t r2 = (HW_Read16(r4, 0x106 + r8*16) & 0x3f92) | 0x10;
            HW_Write16(r4, 0x106 + r8*16, r2);
            HW_Write16(r4, 0x106 + r8*16, r2);
            //->0x00005d40
        }
        else
        {
            //0x00005cc0
            if ((r2 != NULL) && (r2->flags & 0x600))
            {
                MENTOR_AbortDMA_TX(r4, r5);
            }
            //0x00005ce0
            HW_Write8(r4, 0x10b + r8*16, 0);
            HW_Write8(r4, 0x10b + r8*16, 0);
            uint32_t r2 = (HW_Read16(r4, 0x102 + r8*16) & 0x7f58) | 0x08;
            HW_Write16(r4, 0x102 + r8*16, r2);
            HW_Write16(r4, 0x102 + r8*16, r2);
        }
        //0x00005d40
    }
    //0x00005d40
    InterruptLock(&r4->Data_0xd0);

    struct _musb_transfer* r3 = r5->Data_8__;
    while (r3 != NULL)
    {
        //0x00005d88
        r5->Data_8__ = SIMPLEQ_NEXT(r3, link);
        if (r5->Data_8__  == NULL)
        {
            r5->Data_0xc = &r5->Data_8__;
        }
        r3->flags = 0;

        SIMPLEQ_INSERT_TAIL(&r4->transfer_free_q, r3, link);

        r3 = r5->Data_8__;
    }
    //0x00005dbc
    InterruptUnlock(&r4->Data_0xd0);

    r4->Data_0xc4[r8] = NULL;

    MENTOR_FreeEtd(r4, r5);

    if (r5->transferType == USB_ATTRIB_INTERRUPT) //3)
    {
        r4->Data_0x84--;
    }

    r5->Data_0x10 &= ~0x01;

    if (pthread_mutex_unlock(&r4->Data_4/*r7*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x3dc);
    }

    return 0;
}


/* 0x00009378 - todo */
int MENTOR_WaitEndControl(struct USB_Controller* fp_0x30, 
    struct Struct_10bab4* r4, 
    struct Struct_112b08* fp_0x2c,
    struct _musb_transfer* fp_0x34)
{
#if 0
    fprintf(stderr, "MENTOR_WaitEndControl: TODO!!!\n");
#endif

    struct _hctrl_t* r8 = fp_0x30->hc_data;

    pthread_sleepon_lock();
    //->loc_9444
    while (r4->Data_4 == 0)
    {
        //->loc_93b4
        if (pthread_sleepon_timedwait(&r4->Data_4, 
                1000000ULL * r4->Data_0x1c) != 0)
        {
            //0x000093d4
            pthread_sleepon_unlock();

            int r2 = fp_0x34->flags;
            uint16_t wCsr = HW_Read16(r8, MUSB_CSR0);

            mentor_slogf(r8, 12, 2, 1, 
                "%s - Timeout on Control Transfer Status 0x%x 0x%x ",
                "devu-dm816x-mg.so", r2, wCsr);

            mentor_transfer_abort(fp_0x30, r4, fp_0x2c);

            r4->Data_8 = 0x0f;

            return -1;
        }
        //->loc_9444
    }
    //0x00009450
    pthread_sleepon_unlock();

    if (r4->Data_8 != 0)
    {
        return -1;
    }

    return 0;
}


/* 0x000071e8 - todo */
int MENTOR_ProcessMultiOutComplete(struct _hctrl_t* a,
        struct _musb_transfer* b, int c, int d)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessMultiOutComplete: TODO!!!\n");
#endif

    struct Struct_0xa4* ip = b->Data_0x30;

    if (ip->bData_0x1f == 0)
    {
        //0x00007208
        b->bytes_xfered += c;

        if (d == 0)
        {
            if (b->bytes_xfered < b->xfer_length)
            {
                //->0x0000733c
                goto l_733c;
            }

            if ((b->Data_0x24 + 1) <= b->Data_0x20)
            {
                //0x000072f4
                goto l_72f4;
            }
            //0x00007240
        }
        //0x00007240
        InterruptLock(&a->Data_0xd0);

        a->Data_0xc4[ip->num] = NULL;

        ip->Data_0x10 &= ~0x01;

        HW_Write16(a, MUSB_TXCSR(ip->num), 0);

        b->Data_0x10 = 0;
        b->status = d;

        if ((ip->Data_8__ = b->link.sqe_next) == NULL)
        {
            ip->Data_0xc = &ip->Data_8__;
        }

        SIMPLEQ_INSERT_TAIL(&a->transfer_complete_q, b, link);

        InterruptUnlock(&a->Data_0xd0);

        return 0;

l_72f4:
        //0x000072f4
        b->Data_0x34->Data_0x34 += b->bytes_xfered;
        b->Data_0x24++;

        struct _musb_transfer_Inner_0x18_Inner_8 * r3 = &b->Data_0x1c__[b->Data_0x24];
        b->xfer_buffer_paddr = r3->Data_0;
        b->xfer_length = r3->Data_8;
        b->bytes_xfered = 0;

l_733c:
        //0x0000733c
        MENTOR_StartEtd(a, b);
    }
    //0x00007340
    return 0;
}



/* 0x00007348 - todo */
int MENTOR_ProcessMultiInComplete(struct _hctrl_t* r6,
        struct _musb_transfer* r4, uint32_t r2, int r7)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessMultiInComplete: TODO!!!\n");
#endif

    if (r7 != 0)
    {
        fprintf(stderr, "MENTOR_ProcessMultiInComplete: r7=%d\n", r7);
    }

    struct Struct_0xa4* r5 = r4->Data_0x30;
    
    if (r5->bData_0x1f == 0)
    {
        //0x00007374
        r4->bytes_xfered += r2;

        int remaining;
        if ((r2 != 0) && ((r2 % r5->mps) == 0))
        {
            //0x0000739c
            remaining = r4->xfer_length - r4->bytes_xfered;

            if ((r7 == 0) && (remaining > 0))
            {
                //0x000073c0
                MENTOR_RestartEtd(r6, r4);
                //->0x000074e4
                return 0;
            }
            //0x000073d4
        }
        else
        {
            //0x000073d0
            remaining = 0;
        }
        //0x000073d4
        if ((r7 != 0) ||
            ((r4->Data_0x24 + 1) > r4->Data_0x20) ||
            (remaining == 0))
        {
            //0x000073f8
            InterruptLock(&r6->Data_0xd0);

            r5->Data_0x10 &= ~0x1;

            r4->status = r7;

            r6->Data_0xc4[r5->num] = NULL;

            if ((r5->Data_8__ = r4->link.sqe_next) == NULL)
            {
                r5->Data_0xc = &r5->Data_8__;
            }
            //0x00007460
            SIMPLEQ_INSERT_TAIL(&r6->transfer_complete_q, r4, link);

            InterruptUnlock(&r6->Data_0xd0);
            //->0x000074e4
        }
        else
        {
            //0x00007490
            struct Struct_10bab4* r3 = r4->Data_0x34;

            r3->Data_0x34 += r4->bytes_xfered;
            r4->Data_0x24++;

            struct _musb_transfer_Inner_0x18_Inner_8* r3_;
            
            r3_ = &r4->Data_0x1c__[r4->Data_0x24];
            r4->xfer_buffer_paddr = r3_->Data_0;
            r4->xfer_length = r3_->Data_8;
            r4->bytes_xfered = 0;

            MENTOR_StartEtd(r6, r4);
        }
    }
    //0x000074e4
    return 0;
}




/* 0x000074ec - todo */
int MENTOR_ProcessInComplete(struct _hctrl_t* r6,
        struct _musb_transfer* r5, uint32_t r8, int r7)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessInComplete: TODO!!!\n");
#endif

    struct Struct_0xa4* r4 = r5->Data_0x30;

    if (r4->bData_0x1f == 0)
    {
        //0x0000751c
        r5->bytes_xfered += r8;

        if ((r7 != 0) || (r5->bytes_xfered >= r5->xfer_length) ||  
            ((r8 % r4->mps) || (r8 == 0)))
        {
            //0x00007564
            HW_Write16(r6, MUSB_RXCSR(r4->num), 0);

            InterruptLock(&r6->Data_0xd0);

            r6->Data_0xc4[r4->num] = NULL;
            r4->Data_0x10 &= ~0x01;
            r5->status = r7;

            r4->Data_8__ = SIMPLEQ_NEXT(r5, link);
            if (r4->Data_8__ == 0)
            {
                r4->Data_0xc = &r4->Data_8__;
            }

            SIMPLEQ_INSERT_TAIL(&r6->transfer_complete_q, r5, link);

            InterruptUnlock(&r6->Data_0xd0);
            //->0x00007620
        }
        else
        {
            //0x00007614: Restart receive for more than 512 bytes...
            MENTOR_RestartEtd(r6, r5);
        }
    }
    //0x00007620
    return 0;
}


/* 0x0000549c - todo */
int MENTOR_ProcessOutComplete(struct _hctrl_t* r6,
        struct _musb_transfer* r4, int r2, int r3)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessOutComplete: TODO!!!\n");
#endif

    struct Struct_0xa4* r5 = r4->Data_0x30;
    if (r5->bData_0x1f == 0)
    {
        //0x000054c4
        r4->bytes_xfered += r2;

        if ((r3 != 0) ||
            (r4->bytes_xfered >= r4->xfer_length))
        {
            //loc_54e8
            InterruptLock(&r6->Data_0xd0);

            r6->Data_0xc4[r5->num] = NULL;
            r5->Data_0x10 &= ~0x01;

            HW_Write16(r6, MUSB_TXCSR(r5->num), 0);

            r4->Data_0x10 = 0;
            r4->status = r3;

            r5->Data_8__ = SIMPLEQ_NEXT(r4, link);
            if (r5->Data_8__ == NULL)
            {
                r5->Data_0xc = &r5->Data_8__;
            }

            SIMPLEQ_INSERT_TAIL(&r6->transfer_complete_q, r4, link);

            InterruptUnlock(&r6->Data_0xd0);
            //->loc_56d0
        }
        else
        {
            //0x0000559c
            r4->flags &= ~0x800;

            uint32_t r3 = r5->Data_0x30->Data_0;
            int r1 = r4->xfer_length;
            int r2 = r4->bytes_xfered;
            r2 = r1 - r2;
            if (r3 >= r2)
            {
                r3 = r4->xfer_length - r4->bytes_xfered;
            }
            r4->Data_0x10 = r3;

            uint32_t m = 0;
            int r0 = ((r4->Data_0x10 + r5->mps - 1) / r5->mps) - 1;
            if (r0 > 0)
            {
                //0x000055fc
                m = ((r4->Data_0x10 + r5->mps - 1) / r5->mps) - 1;
            }
            //0x00005614
            HW_Write16(r6, MUSB_TXMAXP(r5->num),
                r5->mps | (m << 11));

            if (r4->flags & 0x600)
            {
                //0x00005640
#if 1
                fprintf(stderr, "MENTOR_ProcessOutComplete: 0x00005640: TODO!!!\n");
#endif
                //TODO!!!

                //->0x000056d0
            }
            else
            {
                //0x0000568c
                MENTOR_LoadFIFO(r6, r5->num, 
                    r4->xfer_buffer + r4->bytes_xfered, r4->Data_0x10);
                
                HW_Write16(r6, 0x102 + r5->num * 16, 
                    HW_Read16(r6, 0x102 + r5->num * 16) | 0x01);
            }
        }
    }
    //loc_56d0
    return 0;
}


/* 0x00004a98 - todo */
int MENTOR_ProcessOutDMAComplete(struct _hctrl_t* a,
        struct _musb_transfer* b, int c, int d)
{
#if 0
    fprintf(stderr, "MENTOR_ProcessOutDMAComplete: TODO!!!\n");
#endif

    struct Struct_0xa4* ep = b->Data_0x30;

    if (ep->bData_0x1f == 0)
    {
        uint32_t txCsr = HW_Read16(a, MUSB_TXCSR(ep->num));

        txCsr = (txCsr & ~0x9400) 
            | TXCSR_MODE | TXCSR_NAK_TIMEOUT //0x2080 
            | TXCSR_RX_STALL | TXCSR_ERROR | TXCSR_FIFO_NOT_EMPTY | TXCSR_TXPKTRDY; //0x27;

        HW_Write16(a, MUSB_TXCSR(ep->num), txCsr);
    }

    return 0;
}


/* 0x00008990 - todo */ 
int mentor_int_transfer(struct USB_Controller* ctrl, 
    struct Struct_10bab4* r8, 
    struct Struct_112b08* r2, 
    void* buffer/*fp_0x34*//*fp52*/, 
    uint32_t length/*sb*//*arg0*/, 
    int flags/*arg4*//*fp8*/)
{
#if 0
    fprintf(stderr, "mentor_int_transfer: buffer=%p, length=%d, flags=0x%x: TODO!!!\n",
        buffer, length, flags);
#endif

    struct _hctrl_t* r5 = ctrl->hc_data;
    struct Struct_0xa4* r4 = r2->Data_0xc;
    struct _musb_transfer* td; //r6;

    if (pthread_mutex_lock(&r5->Data_4/*sl*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x593);
    }
    //loc_89f0
    td = MENTOR_TD_Setup(r5, r8, r4, flags/*arg4*/);
    if (td == NULL)
    {
        if (pthread_mutex_unlock(&r5->Data_4/*sl*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
                0x596);
        }
        //loc_8a3c
        r8->Data_8 = 0x2000010;
        return 12; //->loc_8dd8
    }
    //loc_8a4c
    td->xfer_buffer = (uint32_t) buffer; //fp_0x34;
    td->xfer_buffer_paddr = r8->Data_0x5c->pData;
    td->xfer_length = length;

    r5->Data_0x84++;

    if ((length > r4->mps) || (length > 64))
    {
        td->flags |= r5->Data_0x38;
    }

    if (flags & 0x04)/*fp_0x30*/
    {
        //0x00008ab0
        td->Func_0x3c = td->Func_0x38 = MENTOR_ProcessInComplete;
        //->0x00008af8
    }
    else
    {
        //0x00008ac4
        td->Func_0x38 = MENTOR_ProcessOutComplete;

        if ((r5->Data_0x38 & 0x400) == 0)
        {
            //0x00008adc
            td->Func_0x3c = MENTOR_ProcessOutComplete;
            //->0x00008af8
        }
        else
        {
            //0x00008aec
            td->Func_0x3c = MENTOR_ProcessOutDMAComplete;
        }
    }
    //0x00008af8
    InterruptLock(&r5->Data_0xd0);

#if 1
    td->link.sqe_next = NULL;
    r4->Data_0xc->Data_0 = td;

#if 0
    struct Struct_0x94* fp_0x30;
    fp_0x30 = &td->Data_0x2c;
#else
#endif
    r4->Data_0xc = &td->link.sqe_next; //sb;
#else
    SIMPLEQ_INSERT_TAIL()
#endif

    if ((r4->Data_0x10 & 0x01) == 0)
    {
        //0x00008b50
        InterruptUnlock(&r5->Data_0xd0);

        if (r4->num == -1)
        {
            //0x00008b74
            if (MENTOR_AllocEtd(r5, r4, td->flags & 0x04) < 0)
            {
                //0x00008b90
                mentor_slogf(r5, 12, 2, 1, "%s - %s Call to MENTOR_AllocEtd() failed",
                    "devu-dm816x-mg.so", "mentor_int_transfer");

                InterruptLock(&r5->Data_0xd0);

                r4->Data_8__ = SIMPLEQ_NEXT(td, link);
                if (r4->Data_8__ == 0)
                {
                    r4->Data_0xc = &r4->Data_8__;
                }

                SIMPLEQ_INSERT_TAIL(&r5->transfer_free_q, td, link);

                InterruptUnlock(&r5->Data_0xd0);

                if (pthread_mutex_unlock(&r5->Data_4/*sl*/) != 0)
                {
                    //0x00008c50
                    fprintf(stderr, "mutex lock %s %d\n", 
                        "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
                        0x5be);
                }
                //0x00008c70
                r8->Data_8 = 0x2000010;
                return 12; //->0x00008dd8
            } //if (MENTOR_AllocEtd() < 0)
            //0x00008c80
            if (flags/*fp_0x30*/ & 0x04/*PIPE_FLAGS_TOKEN_IN?*/)
            {
                //0x00008c8c
                MENTOR_EtdConfigureRX(r5, r4, r4->num);
                //->0x00008cb0
            }
            else
            {
                //0x00008ca0
                MENTOR_EtdConfigureTX(r5, r4, r4->num);
            }
        }
        //0x00008cb0
        if ((td->flags & 0x600) && (r4->Data_0x38 == 0))
        {
            //0x00008cc8
            r4->Data_0x38 = mentor_alloc_dma_sched(r5, r4);
            if (r4->Data_0x38 == 0)
            {
                td->flags &= ~0x600;
            }

            if (((r5->flags & 0x04) == 0) &&
                (r4->Data_0x2c == -1))
            {
                //0x00008d00
                if (mentor_claim_dma_channel(r5, td, 
                        r4->num, &r4->Data_0x2c) != 0)
                {
                    td->flags &= ~0x600;
                }
            }
        }
        //0x00008d24
        if (r4->Data_8__ != NULL)
        {
            //0x00008d30
            r4->Data_0x10 |= 0x01;
            r5->Data_0xc0 = r4;

            MENTOR_StartEtd(r5, r4->Data_8__);
        }
        //->0x00008da4
    } //if ((r4->Data_0x10 & 0x01) == 0)
    else
    {
        //0x00008d4c
        InterruptUnlock(&r5->Data_0xd0);

        if (pthread_mutex_unlock(&r5->Data_4/*sl*/) != 0)
        {
            //0x00008d74
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
                0x5e0);
        }
        //0x00008d94
        r8->Data_8 = 0x200000f;

        return 0x10; //->0x00008dd8
    }
    //0x00008da4
    if (pthread_mutex_unlock(&r5->Data_4/*sl*/) != 0)
    {
        //0x00008db4
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x5e5);
    }

    return 0;
}



/* 0x00008e20 - todo */ /* refer musb_transfer */
int mentor_bulk_transfer(struct USB_Controller* ctrl, 
    struct Struct_10bab4* r8, 
    struct Struct_112b08* r2, 
    void* buffer/*fp_0x34*//*fp52*/, 
    uint32_t length/*fp4*/, 
    int flags/*sb*//*arg4*/)
{
#if 1
    fprintf(stderr, "mentor_bulk_transfer: buffer=%p, length=%d, flags=0x%x: TODO!!!\n",
        buffer, length, flags);

    if ((buffer != NULL) && (length > 0) && ((flags & 0x04) == 0))
    {
        hex_dump("mentor_bulk_transfer", buffer, length);
    }
#endif

    struct _hctrl_t* r6 = ctrl->hc_data;
    struct Struct_0xa4* r5 = r2->Data_0xc;
    struct _musb_transfer* td; //r4;

    if (pthread_mutex_lock(&r6->Data_4/*sl*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x505);
    }
    //loc_8e80
    td = MENTOR_TD_Setup(r6, r8, r5, flags/*sb*/);
    if (td == NULL)
    {
        if (pthread_mutex_unlock(&r6->Data_4/*sl*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
                0x508);
        }
        //loc_8ecc
        r8->Data_8 = 0x2000010;
        return 12; //->loc_932c
    }
    //loc_8edc
    td->xfer_buffer = (uint32_t) buffer; //fp_0x34;
    td->xfer_buffer_paddr = r8->Data_0x5c->pData;
    td->xfer_length = length;

#if 1
    fprintf(stderr, "mentor_bulk_transfer: r6->flags=0x%x\n",
        r6->flags);
#endif

    if (r6->flags & 0x01)
    {
        //0x00008f04
        if (flags/*sb*/ & 0x20/*PIPE_FLAGS_MULTI_XFER?*/)
        {
            //0x00008f0c
            struct _musb_transfer_Inner_0x18* r3 = r8 + 1;
            struct _musb_transfer_Inner_0x18_Inner_8* r2 = r3->Data_8;

            td->Data_0x18 = r3;
            td->Data_0x1c__ = r3->Data_8;
            td->Data_0x20 = r3->wData_0 - 1;
            td->Data_0x24 = 0;

#if 1
            fprintf(stderr, "mentor_bulk_transfer: multi: td->Data_0x20=%d, r2->Data_0=0x%x, r2->Data_8=%d, r6->Data_0x38=0x%x\n",
                td->Data_0x20, r2->Data_0, r2->Data_8, r6->Data_0x38);
#endif

            td->xfer_buffer_paddr = r2->Data_0;
            td->xfer_length = r2->Data_8;

            if (flags/*sb*/ & 0x04)
            {
                //0x00008f4c
                td->Func_0x3c = td->Func_0x38 = MENTOR_ProcessMultiInComplete;

                //->0x00008f94
            }
            else
            {
                //0x00008f60
                td->Func_0x38 = MENTOR_ProcessMultiOutComplete;

                if (r6->Data_0x38 == 0x400)
                {
                    //0x00008f78
                    td->Func_0x3c = MENTOR_ProcessMultiOutComplete;
                }
                else
                {
                    //0x00008f88
                    td->Func_0x3c = MENTOR_ProcessOutDMAComplete;
                }
                //0x00008f94
            }
            //0x00008f94
            td->flags |= r6->Data_0x38;
            //->0x00009088
        } //if (flags/*sb*/ & 0x20/*PIPE_FLAGS_MULTI_XFER?*/)
        else
        {
            //0x00008fa8
            if ((length/*fp4*/ > r5->mps) || 
                (length/*fp4*/ > 0x40))
            {
                //0x00008fcc
                if ((((uint32_t)buffer/*fp_0x34*/) & 0x03) == 0)
                {
                    td->flags |= r6->Data_0x38;
                }
            }
            //0x00008fe4
            if (flags/*sb*/ & 0x04)
            {
                //0x00008fec
                td->Func_0x3c = td->Func_0x38 = MENTOR_ProcessInComplete;
                //->0x00009088
            }
            else
            {
                //0x00009000
                td->Func_0x38 = MENTOR_ProcessOutComplete;

                if (r6->Data_0x38 == 0x400)
                {
                    //0x00009018
                    td->Func_0x3c = MENTOR_ProcessOutComplete;
                }
                else
                {
                    //0x00009028
                    td->Func_0x3c = MENTOR_ProcessOutDMAComplete;
                }
                //->0x00009088
            }
        }
    } //if (r6->flags & 0x01)
    else
    {
        //0x00009038
        if (flags/*sb*/ & 0x04/*PIPE_FLAGS_TOKEN_IN?*/)
        {
            //0x00009040
            td->Func_0x3c = td->Func_0x38 = MENTOR_ProcessInComplete;
            //->0x00009088
        }
        else
        {
            //0x00009054
            td->Func_0x38 = MENTOR_ProcessOutComplete;

            if (r6->Data_0x38 == 0x400)
            {
                //0x0000906c
                td->Func_0x3c = MENTOR_ProcessOutComplete;
            }
            else
            {
                //0x0000907c
                td->Func_0x3c = MENTOR_ProcessOutDMAComplete;
            }
            //0x00009088
        }
    }
    //0x00009088
    InterruptLock(&r6->Data_0xd0);

#if 1
    td->link.sqe_next = NULL;
    r5->Data_0xc->Data_0 = td;

#if 0
    struct Struct_0x94* fp_0x30;
    fp_0x30 = &td->Data_0x2c;
#else
#endif
    r5->Data_0xc = &td->link.sqe_next; //fp_0x30;
#else
    SIMPLEQ_INSERT_TAIL()
#endif

    if ((r5->Data_0x10 & 0x01) == 0)
    {
        //0x000090e4
        InterruptUnlock(&r6->Data_0xd0);

        if (r5->num == -1)
        {
            //0x00009108
            if (MENTOR_AllocEtd(r6, r5, td->flags & 0x04) < 0)
            {
                //0x00009124
                mentor_slogf(r6, 12, 2, 1, "%s - %s Call to MENTOR_AllocEtd() failed",
                    "devu-dm816x-mg.so", "mentor_bulk_transfer");

                InterruptLock(&r6->Data_0xd0);

                r5->Data_8__ = SIMPLEQ_NEXT(td, link);
                if (r5->Data_8__ == 0)
                {
                    r5->Data_0xc = &r5->Data_8__;
                }

                SIMPLEQ_INSERT_TAIL(&r6->transfer_free_q, td, link);

                InterruptUnlock(&r6->Data_0xd0);

                if (pthread_mutex_unlock(&r6->Data_4/*sl*/) != 0)
                {
                    fprintf(stderr, "mutex lock %s %d\n", 
                        "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
                        0x55f);
                }
                //0x00009208
                r8->Data_8 = 0x10;
                return 12; //->loc_932c
            } //if (MENTOR_AllocEtd() < 0)
            //0x00009218
            if (flags/*sb*/ & 0x04/*PIPE_FLAGS_TOKEN_IN?*/)
            {
                //0x00009220
                MENTOR_EtdConfigureRX(r6, r5, r5->num);
                //->0x00009244
            }
            else
            {
                //0x00009234
                MENTOR_EtdConfigureTX(r6, r5, r5->num);
            }
        }
        //0x00009244
        if ((td->flags & 0x600) && 
            (r5->Data_0x38 == 0))
        {
            //0x0000925c
            r5->Data_0x38 = mentor_alloc_dma_sched(r6, r5);
            if (r5->Data_0x38 == 0)
            {
                td->flags &= ~0x600;
            }

            if (((r6->flags & 0x04) == 0) &&
                (r5->Data_0x2c == -1))
            {
                //0x00009288
                if (mentor_claim_dma_channel(r6, td, 
                        r5->num, &r5->Data_0x2c) != 0)
                {
                    td->flags &= ~0x600;
                }
            }
            //0x000092b8
        }
        //0x000092b8
        if (r5->Data_8__ != 0)
        {
            //0x000092c4
            r5->Data_0x10 |= 0x01;
            r6->Data_0xbc = r5;

            MENTOR_StartEtd(r6, r5->Data_8__);
        }
        //0x000092f8
    } //if ((r5->Data_0x10 & 0x01) == 0)
    else
    {
        //0x000092e0
        InterruptUnlock(&r6->Data_0xd0);
    }
    //0x000092f8
    if (pthread_mutex_unlock(&r6->Data_4/*sl*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c",
            0x584);
    }
    //loc_932c
    return 0;    
}


/* 0x0000947c - todo */
int mentor_ctrl_transfer(struct USB_Controller* sl, 
    struct Struct_10bab4* r8, 
    struct Struct_112b08* sb, 
    uint8_t* buffer/*fp_0x34*//*fp52*/, 
    uint32_t length/*fp4*/, 
    uint32_t flags/*fp8*/)
{
#if 0
    fprintf(stderr, "mentor_ctrl_transfer: buffer=%p, length=%d, flags=0x%x\n", 
        buffer, length, flags);

    if ((flags & PIPE_FLAGS_TOKEN_SETUP) && (length == 8) && (buffer != NULL))
    {
        fprintf(stderr, "mentor_ctrl_transfer: Setup Packet:\n");
        fprintf(stderr, "mentor_ctrl_transfer: bmRequestType.Recipient=%d\n", buffer[0] & 0x1f);
        fprintf(stderr, "mentor_ctrl_transfer: bmRequestType.Type=%d\n", (buffer[0] >> 5) & 0x03);
        fprintf(stderr, "mentor_ctrl_transfer: bmRequestType.Direction=%d\n", (buffer[0] >> 7) & 0x01);
        fprintf(stderr, "mentor_ctrl_transfer: bRequest=0x%02x\n", buffer[1]);
        fprintf(stderr, "mentor_ctrl_transfer: wValue=0x%04x\n", buffer[2] | (buffer[3] << 8));
        fprintf(stderr, "mentor_ctrl_transfer: wIndex=0x%04x\n", buffer[4] | (buffer[5] << 8));
        fprintf(stderr, "mentor_ctrl_transfer: wLength=0x%04x\n", buffer[6] | (buffer[7] << 8));
    }
#endif

    int res;

    struct _musb_transfer* td; //fp_0x38
    struct _hctrl_t* r5 = sl->hc_data;
    struct Struct_0xa4* fp_0x30/*fp48*/ = sb->Data_0xc;

    if (pthread_mutex_lock(&r5->Data_0xc/*r7*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4c9);
    }

    if (pthread_mutex_lock(&r5->Data_4/*r6*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4ca);
    }
    //loc_9518
    if ((r5->Data_0x6c & 0x06) != 0x06)
    {
        if (pthread_mutex_unlock(&r5->Data_4/*r6*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4cd);
        }
        //loc_9558
        if (pthread_mutex_unlock(&r5->Data_0xc/*r7*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4ce);
        }
        //loc_9588
        r8->Data_8 = 0x2000005;

        return 0x13;
        //->loc_9988
    }
    //loc_9598
    td = MENTOR_TD_Setup(r5, r8, fp_0x30, flags/*fp8*/);
    if (td == NULL)
    {
        //0x000095b8
        if (pthread_mutex_unlock(&r5->Data_4/*r6*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4cd);
        }
        //0x000095e8
        if (pthread_mutex_unlock(&r5->Data_0xc/*r7*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4ce);
        }
        //0x00009618
        r8->Data_8 = 0x2000010;

        return 0x0c;
        //->loc_9988
    }
    //0x00009628
    td->xfer_buffer = (uint32_t) buffer; //fp_0x34;
    td->xfer_length = length/*fp4*/;

    r8->Data_4 = 0;
    //0x00009648
    InterruptLock(&r5->Data_0xd0);
    //0x0000967c
#if 0
    td->Data_0x2c.Data_0 = NULL;
    fp_0x30->Data_0xc->Data_0 = td;
    fp_0x30->Data_0xc = &td->Data_0x2c;
#else
    td->link.sqe_next = NULL;
    fp_0x30->Data_0xc->Data_0 = td;
    fp_0x30->Data_0xc = &td->link.sqe_next;
    //SIMPLEQ_INSERT_TAIL()
#endif

    if ((fp_0x30->Data_0x10 & 1) == 0)
    {
        //0x000096a4
        fp_0x30->Data_0x10 |= 1;
        fp_0x30->num = 0;

        r5->Data_0xc4[0] = td;
        //0x000096bc
        InterruptUnlock(&r5->Data_0xd0);
        //0x000096d0
        struct _musb_transfer* r2 = fp_0x30->Data_8__;
#if 0
        fprintf(stderr, "r2->xfer_length=%d, r2->flags=0x%x, r2->xfer_buffer=%p, \n",
            r2->xfer_length, r2->flags, (void*) r2->xfer_buffer);
#endif

        fp_0x30 = r2->Data_0x30;
        r2->flags |= 0x100;
        fp_0x30->bData_0x1f = 0; //r3; //TODO!!!

        int fp_0x34_;
        uint32_t wCsrH; //r1;
        if (r2->flags & PIPE_FLAGS_TOKEN_SETUP) //1)
        {
            //0x00009700
            fp_0x30->Data_0x20 = 0;

            fp_0x34_ = 0x08;
            //->0x00009760
            wCsrH = 0;
            //0x00009764
        }
        //0x00009714
        else if (r2->flags & PIPE_FLAGS_TOKEN_STATUS) //2)
        {
            //0x00009720
            fp_0x30->Data_0x20 = 1;

            fp_0x34_ = 0x40;
            wCsrH = 0x200;
            //->0x00009764
        }
        else
        {
            //0x0000973c
            if (fp_0x30->Data_0x20 != 0)
            {
                fp_0x34_ = 0;
                wCsrH = 0x200;
                //->0x00009764
            }
            else
            {
                //0x00009758
                fp_0x34_ = 0;
                wCsrH = 0;
            }
        }
        //0x00009764
        wCsrH |= (r5->flags & 0x80)? 0x800: 0;
        wCsrH |= 0x500;
        wCsrH &= 0xf00;

#if 0
        fprintf(stderr, "mentor_ctrl_transfer: wCsrH=0x%04x, fp_0x30->Data_0x14=0x%x\n", 
            wCsrH, fp_0x30->Data_0x14);
#endif

        HW_Write16(r5, MUSB_CSR0, wCsrH);
        HW_Write16(r5, 0x80, (fp_0x30->Data_0x14 >> 4) & 0x7f);

        if (fp_0x30->bData_0x1c != 0x40)
        {
            //0x000097b8
#ifdef MB86H60
            fprintf(stderr, "mentor_ctrl_transfer: fp_0x30->bData_0x1d=0x%x, fp_0x30->bData_0x1e=0x%x\n", 
                fp_0x30->bData_0x1d, fp_0x30->bData_0x1e);

            MGC_Write8(r5, MGC_BUSCTL_OFFSET(0/*bEnd*/, MGC_O_HDRC_TXHUBADDR),
                fp_0x30->bData_0x1d);
            MGC_Write8(r5, MGC_BUSCTL_OFFSET(0/*bEnd*/, MGC_O_HDRC_TXHUBPORT),
                fp_0x30->bData_0x1e);
#else
            ((volatile uint8_t*)(r5->Data_0x14))[0x82] = fp_0x30->bData_0x1d;
            ((volatile uint8_t*)(r5->Data_0x14))[0x83] = fp_0x30->bData_0x1e;
#endif
        }
        //0x000097d8
#ifdef MB86H60
        MGC_Write8(r5, 0x10b, 0); //TxInterval?
#else
        ((volatile uint8_t*)(r5->Data_0x14))[0x10b] = 0;
#endif

        uint16_t r2_;
        if (r2->flags & PIPE_FLAGS_TOKEN_SETUP) //1)
        {
            //0x000097f8
            MENTOR_LoadFIFO(r5, 0, r2->xfer_buffer, r2->xfer_length & 0xffff);

            r2_ = fp_0x34_ | (1 << 3)/*SetupPkt*/ | (1 << 1)/*TxPktRdy*/; //0x0a;
            //->0x0000987c
        }
        //0x0000981c
        else if (r2->flags & PIPE_FLAGS_TOKEN_OUT) //8)
        {
            //0x00009828
            int r3 = fp_0x30->mps;
            if (r3 > r2->xfer_length)
            {
                r3 = r2->xfer_length;
            }

            r2->bytes_xfered += r3;

            if (r3 > 0)
            {
                //0x00009850
                MENTOR_LoadFIFO(r5, 0, r2->xfer_buffer, r3 & 0xffff);
            }
            //0x00009868
            r2_ = fp_0x34_ | (1 << 1)/*TxPktRdy*/; //0x02;
            //->0x0000987c
        }
        else
        {
            //0x00009874
            r2_ = fp_0x34_ | (1 << 5)/*ReqPkt*/; //0x20;
        }
        //0x0000987c
#if 0
        fprintf(stderr, "mentor_ctrl_transfer: r2_=0x%04x, fp_0x30->bData_0x1c=0x%x\n", 
            r2_, fp_0x30->bData_0x1c);
#endif

        HW_Write16(r5, 0x10a, fp_0x30->bData_0x1c);
        HW_Write16(r5, MUSB_CSR0, HW_Read16(r5, MUSB_CSR0) | r2_);
        //->0x000098c8
    }
    else
    {
        //0x000098b0
        InterruptUnlock(&r5->Data_0xd0);
    }
    //0x000098c8
    if (pthread_mutex_unlock(&r5->Data_4/*r6*/) != 0)
    {
        fprintf(stderr, "mutex lock %s %d\n", 
            "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4ed);
    }
    //0x000098f8
    if (flags/*fp8*/ & 0x80000000) // < 0)
    {
        //0x00009904
        res = MENTOR_WaitEndControl(sl, r8, sb, td);

        if (pthread_mutex_unlock(&r5->Data_0xc/*r7*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4f1);
        }
        //0x00009988
    }
    else
    {
        //0x00009950
        if (pthread_mutex_unlock(&r5->Data_0xc/*r7*/) != 0)
        {
            fprintf(stderr, "mutex lock %s %d\n", 
                "C:/projects/beaglebone/bsp-ti-beaglebone-src/src/hardware/devu/hc/mg/mentor.c", 0x4f1);
        }

        res = 0;
    }
    //loc_9988
    return res;
}


int mentor_ctrl_transfer_abort(struct USB_Controller* a, 
    struct Struct_10bab4* b, 
    struct Struct_112b08* c)
{
#if 1
    fprintf(stderr, "mentor_ctrl_transfer_abort: TODO!!!\n");
#endif

    return 0;
}



int mentor_ctrl_endpoint_disable(struct USB_Controller* a, struct Struct_112b08* b)
{
#if 1
    fprintf(stderr, "mentor_ctrl_endpoint_disable: TODO!!!\n");
#endif

    return 0;
}



int mentor_int_endpoint_disable(struct USB_Controller* a, struct Struct_112b08* b)
{
#if 1
    fprintf(stderr, "mentor_int_endpoint_disable: TODO!!!\n");
#endif

    return 0;
}



/* 0x00009c24 - complete */
int mentor_bulk_endpoint_enable(struct USB_Controller* a, 
    struct USB_Controller_Inner_0x7c* b, 
    struct Struct_112b08* r6)
{
#if 1
    fprintf(stderr, "mentor_bulk_endpoint_enable: a=%p, b=%p, r6=%p\n",
        a, b, r6);
#endif

    struct _hctrl_t* r5 = a->hc_data;
    struct Struct_0xa4* r4 = r6->Data_0xc;

#if 1
    fprintf(stderr, "mentor_bulk_endpoint_enable: r5=%p, r4=%p\n",
        r5, r4);
#endif

    int res = MENTOR_InitializeEndpoint(r5, b, r6);

    if ((res == 0) && (r4 == NULL))
    {
        r4 = r6->Data_0xc;

        MENTOR_HookED(r5, r5->Data_0xb0, r4);
    }
    else
    {
        //loc_9c6c
        if (r4 != NULL)
        {
            if (r4->num > 0)
            {
                MENTOR_FreeEtd(r5, r4);
            }
        }
    }
    //loc_9c8c
    r4->Data_0x24 = 0;

    return res;
}


int mentor_bulk_endpoint_disable(struct USB_Controller* a, struct Struct_112b08* b)
{
#if 1
    fprintf(stderr, "mentor_bulk_endpoint_disable: TODO!!!\n");
#endif

    return 0;
}



static hc_methods_t mentor_controller_methods; //0x0000bf64
static hc_pipe_methods_t mentor_ctrl_pipe_methods; //0x0000bf98
static hc_pipe_methods_t mentor_int_pipe_methods; //0x0000bfac
static hc_pipe_methods_t mentor_bulk_pipe_methods; //0x0000bfc0

struct _io_usb_dll_entry io_usb_dll_entry = //0x0000bf40
{
    "devu-mb86h60-mg.so",
    0xffffffff,
    mentor_init,
    mentor_shutdown,
    &mentor_controller_methods,
    &mentor_ctrl_pipe_methods,
    &mentor_int_pipe_methods,
    &mentor_bulk_pipe_methods,
#if 1 //TODO
    0, //&mentor_isoch_pipe_methods,
#endif
};


static hc_methods_t mentor_controller_methods = //0x0000bf64
{
    9,
    mentor_controller_init,
    mentor_controller_shutdown,
    0, //mentor_set_bus_state,
    0, 0, 0,
    mentor_set_port_feature,
    mentor_clear_port_feature,
    mentor_check_port_status,
    mentor_check_device_connected,
    mentor_get_root_device_speed,
    mentor_get_timer_from_controller,
};


static hc_pipe_methods_t mentor_ctrl_pipe_methods = //0x0000bf98
{
    mentor_ctrl_endpoint_enable,
    mentor_ctrl_endpoint_disable,
    mentor_ctrl_transfer,
    mentor_ctrl_transfer_abort,
    NULL
};


static hc_pipe_methods_t mentor_int_pipe_methods = //0x0000bfac
{
    mentor_int_endpoint_enable,
    mentor_int_endpoint_disable,
    mentor_int_transfer,
    mentor_transfer_abort,
    NULL   
};


static hc_pipe_methods_t mentor_bulk_pipe_methods = //0x0000bfc0
{
    mentor_bulk_endpoint_enable,
    mentor_bulk_endpoint_disable,
    mentor_bulk_transfer,
    mentor_transfer_abort,
    NULL
};

