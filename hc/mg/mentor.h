

#define MUSB_PULSE_INTR  				(_PULSE_CODE_MINAVAIL+1)



// EP Control  Host and Peripheral Mode ( indexed and non indexed ) 
#define MUSB_TXMAXP(n)				( 0x100 + ( 0x10 * (n) ) ) // 16-bit
#define MUSB_IDX_TXMAXP				0x10	// 16-bit
	#define TXMAXP_MPS_POS					0
	#define TXMAXP_MPS_MSK					( 0x3ff << TXMAXP_MPS_POS )
	#define TXMAXP_MULT_POS					11
	#define TXMAXP_MULT_MSK					( 0x1f << TXMAXP_MULT_POS )

#define MUSB_CSR0					0x102  // 16-bit

#define MUSB_TXCSR(n)				( 0x102 + ( 0x10 * (n) ) ) // 16-bit
#define MUSB_IDX_TXCSR				0x12	// 16-bit
	/* peripheral mode */
	#define TXCSR_TXPKTRDY					( 1 << 0 )
	#define TXCSR_FIFO_NOT_EMPTY			( 1 << 1 )
	#define TXCSR_UNDERRUN					( 1 << 2 )
	#define TXCSR_FLUSHFIFO					( 1 << 3 )
	#define TXCSR_SEND_STALL				( 1 << 4 )
	#define TXCSR_SENT_STALL				( 1 << 5 )
	#define TXCSR_CLR_DATA_TOGGLE			( 1 << 6 )
	#define TXCSR_INCOMP_TX					( 1 << 7 )
	#define TXCSR_DMA_REQ_MODE				( 1 << 10 )
	#define TXCSR_DMA_REQ_TYPE0				( 0 << 10 )
	#define TXCSR_DMA_REQ_TYPE1				( 1 << 10 )
	
	#define TXCSR_FORCE_DATA_TOGGLE			( 1 << 11 )
	#define TXCSR_DMA_REQ_EN				( 1 << 12 )
	#define TXCSR_MODE						( 1 << 13 )
	#define TXCSR_ISO						( 1 << 14 )
	#define TXCSR_AUTOSET					( 1 << 15 )
	
	/* host mode */
	//#define TXCSR_TXPKTRDY				( 1 << 0 )
	//#define TXCSR_FIFO_NOT_EMPTY			( 1 << 1 )
	#define TXCSR_ERROR						( 1 << 2 )
	//#define TXCSR_FLUSHFIFO				( 1 << 3 )
	#define TXCSR_SETUP_PKT					( 1 << 4 )
	#define TXCSR_RX_STALL					( 1 << 5 )
	//#define TXCSR_CLR_DATA_TOGGLE			( 1 << 6 )
	//#define TXCSR_INCOMP_TX				( 1 << 7 )
	#define TXCSR_NAK_TIMEOUT				( 1 << 7 )
	#define TXCSR_DATA_TOGGLE				( 1 << 8 )
	#define TXCSR_DATA_TOGGLE_WR_EN			( 1 << 9 )
	//#define TXCSR_DMA_REQ_MODE			( 1 << 10 )
	//#define TXCSR_FORCE_DATA_TOGGLE		( 1 << 11 )
	//#define TXCSR_DMA_REQ_EN				( 1 << 12 )
	//#define TXCSR_MODE					( 1 << 13 )
	//#define TXCSR_AUTOSET					( 1 << 15 )



#define MUSB_RXCSR(n)				( 0x106 + ( 0x10 * (n) ) ) // 16-bit
#define MUSB_IDX_RXCSR				0x16	// 16-bit

	/* peripheral */
	#define RXCSR_RXPKTRDY					( 1 << 0 )
	#define RXCSR_SEND_STALL				( 1 << 5 )
	#define RXCSR_DMA_REQ_MODE				( 1 << 11 )
	#define RXCSR_DMA_REQ_TYPE0				( 0 << 11 )
	#define RXCSR_DMA_REQ_TYPE1				( 1 << 11 )
	#define RXCSR_DMA_REQ_EN				( 1 << 13 )
	#define RXCSR_AUTOCLEAR					( 1 << 15 )

	/* host mode */ 	
	//#define RXCSR_RXPKTRDY				( 1 << 0 )
	#define RXCSR_REQ_PKT					( 1 << 5 )
	//#define RXCSR_DMA_REQ_MODE			( 1 << 11 )
	//#define RXCSR_DMA_REQ_EN				( 1 << 13 )
	#define RXCSR_AUTOREQ					( 1 << 14 )
	//#define RXCSR_AUTOCLEAR				( 1 << 15 )


#define MUSB_COUNT0					0x108	// 16-bit






//#undef MB86H60


static inline uint8_t HW_Read8( struct _hctrl_t* c/*uint8_t * iobase*/, uint32_t offset ) {
	uint8_t data;
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 0);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
#else
	data = *((uint8_t*)(/*iobase*/c->Data_0x14 + offset));
#endif
	return data;
}



static inline uint16_t HW_Read16( struct _hctrl_t* c, uint32_t offset ) {
    uint16_t data;
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 1);
    data = ((volatile uint32_t*)(c->Data_0x14))[offset];
#else
	data = *((uint16_t*)((c->Data_0x14) + offset));
#endif
	return data;
}



static inline void HW_Write8( struct _hctrl_t* c, uint32_t offset, uint8_t data ) {
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 0);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
#else
	*((uint8_t*)(c->Data_0x14 + offset)) = data;
#endif
}



static inline void HW_Write16( struct _hctrl_t* c, uint32_t offset, uint16_t data ) {
#ifdef MB86H60
	dma_SetUsbMode_LengthInput(c, 1);
    ((volatile uint32_t*)(c->Data_0x14))[offset] = data;
#else
	*((uint16_t*)((uint8_t*)(c->Data_0x14) + offset)) = data;
#endif
}



