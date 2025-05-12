/*
 * $QNXLicenseC: 
 * Copyright 2010, QNX Software Systems.  
 *  
 * Licensed under the Apache License, Version 2.0 (the "License"). You  
 * may not reproduce, modify or distribute this software except in  
 * compliance with the License. You may obtain a copy of the License  
 * at: http://www.apache.org/licenses/LICENSE-2.0  
 *  
 * Unless required by applicable law or agreed to in writing, software  
 * distributed under the License is distributed on an "AS IS" basis,  
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied. 
 * 
 * This file may contain contributions from others, either as  
 * contributors under the License or as licensors under other terms.   
 * Please review this entire file for other proprietary rights or license  
 * notices, as well as the QNX Development Suite License Guide at  
 * http://licensing.qnx.com/license-guide/ for other information. 
 * $
 */

#ifndef _MENTOR_H_INCLUDED
#define _MENTOR_H_INCLUDED

#include <queue.h>

typedef struct _hctrl_t hctrl_t;

#define HC_FLAG_USE_DMA           ( 1 << 0 )

// Target Address Registers
#define MUSB_TXFUNCADDR(n)			( 0x80 + ( (n) * 8 ) )	// 8-bit
#define MUSB_TXHUBADDR(n)			( 0x82 + ( (n) * 8 ) )	// 8-bit
#define MUSB_TXHUBPORT(n)			( 0x83 + ( (n) * 8 ) )	// 8-bit
#define MUSB_RXFUNCADDR(n)			( 0x84 + ( (n) * 8 ) )	// 8-bit
#define MUSB_RXHUBADDR(n)			( 0x86 + ( (n) * 8 ) )	// 8-bit
#define MUSB_RXHUBPORT(n)			( 0x87 + ( (n) * 8 ) )	// 8-bit


#define MUSB_CSR0					0x102  // 16-bit
#define MUSB_IDX_CSR0				0x12	// 16-bit
	/* peripheral mode */
	#define CSR0_RXPKTRDY					( 1 << 0 ) 
	#define CSR0_TXPKTRDY					( 1 << 1 ) 
	#define CSR0_SENTSTALL					( 1 << 2 ) 
	#define CSR0_DATAEND					( 1 << 3 ) 
	#define CSR0_SETUPEND					( 1 << 4 ) 
	#define CSR0_SENDSTALL					( 1 << 5 ) 
	#define CSR0_SERVICED_RXPKTRDY			( 1 << 6 ) 
	#define CSR0_SERVICED_SETUP_END			( 1 << 7 ) 
	#define CSR0_FLUSH_FIFO					( 1 << 8 )

	/* host mode */
	//#define CSR0_RXPKTRDY					( 1 << 0 ) 
	//#define CSR0_TXPKTRDY					( 1 << 1 ) 
	#define CSR0_RXSTALL					( 1 << 2 ) 
	#define CSR0_SETUPPKT					( 1 << 3 ) 
	#define CSR0_ERROR						( 1 << 4 ) 
	#define CSR0_REQ_PKT					( 1 << 5 ) 
	#define CSR0_STATUS_PKT					( 1 << 6 ) 
	#define CSR0_NAK_TIMEOUT				( 1 << 7 ) 
	//#define CSR0_FLUSH_FIFO				( 1 << 8 )
	#define CSR0_DATA_TOGGLE				( 1 << 9 )
	#define CSR0_DATA_TOGGLE_WR_EN			( 1 << 10 )
	#define CSR0_DISPING					( 1 << 11 )


#define MUSB_RXCSR(n)				( 0x106 + ( 0x10 * (n) ) ) // 16-bit
#define MUSB_IDX_RXCSR				0x16	// 16-bit

	/* peripheral */
	#define RXCSR_RXPKTRDY					( 1 << 0 )
	#define RXCSR_FIFO_FULL					( 1 << 1 )
	#define RXCSR_OVERRUN					( 1 << 2 )
	#define RXCSR_DATA_ERROR				( 1 << 3 )
	#define RXCSR_FLUSHFIFO					( 1 << 4 )
	#define RXCSR_SEND_STALL				( 1 << 5 )
	#define RXCSR_SENT_STALL				( 1 << 6 )
	#define RXCSR_CLR_DATA_TOGGLE			( 1 << 7 )
	#define RXCSR_INCOMP_RX					( 1 << 8 )
	#define RXCSR_DMA_REQ_MODE				( 1 << 11 )
	#define RXCSR_DMA_REQ_TYPE0				( 0 << 11 )
	#define RXCSR_DMA_REQ_TYPE1				( 1 << 11 )
	#define RXCSR_DISNYET					( 1 << 12 )
	#define RXCSR_PID_ERR					( 1 << 12 )
	#define RXCSR_DMA_REQ_EN				( 1 << 13 )
	#define RXCSR_ISO						( 1 << 14 )
	#define RXCSR_AUTOCLEAR					( 1 << 15 )

	/* host mode */ 	
	//#define RXCSR_RXPKTRDY				( 1 << 0 )
	//#define RXCSR_FIFO_FULL				( 1 << 1 )
	#define RXCSR_ERROR						( 1 << 2 )
	//#define RXCSR_DATA_ERROR				( 1 << 3 )
	#define RXCSR_NAK_TIMEOUT				( 1 << 3 )
	//#define RXCSR_FLUSH_FIFO				( 1 << 4 )
	#define RXCSR_REQ_PKT					( 1 << 5 )
	#define RXCSR_RX_STALL					( 1 << 6 )
	//#define RXCSR_CLR_DATA_TOGGLE			( 1 << 7 )
	//#define RXCSR_INCOMP_RX					( 1 << 8 )
	#define RXCSR_DATA_TOGGLE				( 1 << 9 )
	#define RXCSR_DATA_TOGGLE_WR_EN			( 1 << 10 )
	//#define RXCSR_DMA_REQ_MODE			( 1 << 11 )
	//#define RXCSR_PID_ERR					( 1 << 12 )
	//#define RXCSR_DMA_REQ_EN				( 1 << 13 )
	#define RXCSR_AUTOREQ					( 1 << 14 )
	//#define RXCSR_AUTOCLEAR				( 1 << 15 )


#define MUSB_TXTYPE(n)				( 0x10a + ( 0x10 * (n) ) ) // 8-bit
#define MUSB_IDX_TXTYPE				0x1a	// 8-bit
	/* host only */
	#define TXTYPE_EPNUM_POS				0
	#define TXTYPE_EPNUM_MSK				( 0xf << TXTYPE_EPNUM_POS )
	#define TXTYPE_PROTOCOL_POS				4
	#define TXTYPE_PROTOCOL_MSK				( 3 << TXTYPE_PROTOCOL_POS )
	#define TXTYPE_PROTOCOL_CONTROL			( 0 << TXTYPE_PROTOCOL_POS )
	#define TXTYPE_PROTOCOL_ISOCH			( 1 << TXTYPE_PROTOCOL_POS )
	#define TXTYPE_PROTOCOL_BULK			( 2 << TXTYPE_PROTOCOL_POS )
	#define TXTYPE_PROTOCOL_INTERRUPT		( 3 << TXTYPE_PROTOCOL_POS )
	#define TXTYPE_SPEED_POS				6
	#define TXTYPE_SPEED_MSK				( 3 << TXTYPE_SPEED_POS )
	#define TXTYPE_SPEED_HIGH				( 1 << TXTYPE_SPEED_POS )
	#define TXTYPE_SPEED_FULL				( 2 << TXTYPE_SPEED_POS )
	#define TXTYPE_SPEED_LOW				( 3 << TXTYPE_SPEED_POS )
	

#define MUSB_NAKLIMIT0(n)			( 0x10b + ( 0x10 * (n) ) ) // 8-bit
#define MUSB_IDX_NAKLIMIT0			0x1b	// 8-bit

#define MUSB_TXINTERVAL(n)			( 0x10b + ( 0x10 * (n) ) ) // 8-bit
#define MUSB_IDX_TXINTERVAL			0x1b	// 8-bit



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
#if 0
    struct _musb_transfer* Data_8__; //8
    struct /*Struct_0x94*/_musb_transfer** Data_0xc; //12
#else
    SIMPLEQ_HEAD(, _musb_transfer) Data_8;
#endif
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
    struct Struct_0xa4* Data_0xc0; //0xc0
    struct Struct_0xa4* Data_0xc4; //0xc4
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


static inline uint16_t HW_Read16( hctrl_t* hc, uint32_t offset ) {
	uint16_t data;
	data = *((volatile uint16_t*)(hc->Data_0x14 + offset));
	return data;
}

static inline void HW_Write16( hctrl_t* hc, uint32_t offset, uint16_t data ) {
	*((volatile uint16_t*)(hc->Data_0x14 + offset)) = data;
}

static inline void HW_Write16Or( hctrl_t* hc, uint32_t offset, uint16_t data ) {
	data = HW_Read16( hc, offset ) | data;
	HW_Write16( hc, offset, data);
}


static inline void HW_Write8( hctrl_t* hc, uint32_t offset, uint8_t data ) {
	*((volatile uint8_t*)(hc->Data_0x14 + offset)) = data;
}


#endif
