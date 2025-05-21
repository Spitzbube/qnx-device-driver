/******************************************************************
 *                                                                *
 *        Copyright Mentor Graphics Corporation 2004              *
 *                                                                *
 *                All Rights Reserved.                            *
 *                                                                *
 *    THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY INFORMATION *
 *  WHICH IS THE PROPERTY OF MENTOR GRAPHICS CORPORATION OR ITS   *
 *  LICENSORS AND IS SUBJECT TO LICENSE TERMS.                    *
 *                                                                *
 ******************************************************************/

 #ifndef __MUSB_HDRC_DEFS_H__
 #define __MUSB_HDRC_DEFS_H__
 
 #include "mu_drcdf.h"
 
 /* Common USB registers */
 #define MGC_O_HDRC_POWER	    0x01	/* 8-bit */
 #define MGC_O_HDRC_INTRTX	    0x02	/* 16-bit */
 #define MGC_O_HDRC_INTRRX       0x04
 #define MGC_O_HDRC_INTRTXE      0x06
 #define MGC_O_HDRC_INTRRXE      0x08
 #define MGC_O_HDRC_INTRUSB      0x0A   /* 8 bit */
 #define MGC_O_HDRC_INTRUSBE     0x0B   /* 8 bit */
 #define MGC_O_HDRC_INDEX        0x0E   /* 8 bit */
 #define MGC_O_HDRC_TESTMODE     0x0F   /* 8 bit */
 
 /* Additional Control Registers */
 
 #define	MGC_O_HDRC_DEVCTL	    0x60	   /* 8 bit */
 
 /* These are actually indexed: */
 #define MGC_O_HDRC_TXFIFOSZ	    0x62	/* 8-bit (see masks) */
 #define MGC_O_HDRC_RXFIFOSZ	    0x63	/* 8-bit (see masks) */
 #define MGC_O_HDRC_TXFIFOADD	0x64	/* 16-bit offset shifted right 3 */
 #define MGC_O_HDRC_RXFIFOADD	0x66	/* 16-bit offset shifted right 3 */
 
 /* Endpoint registers */
 #define MGC_O_HDRC_TXMAXP	0x00
 #define MGC_O_HDRC_TXCSR	0x02
 #define MGC_O_HDRC_CSR0		MGC_O_HDRC_TXCSR	/* re-used for EP0 */
 #define MGC_O_HDRC_RXMAXP	0x04
 #define MGC_O_HDRC_RXCSR	0x06
 #define MGC_O_HDRC_RXCOUNT	0x08
 #define MGC_O_HDRC_COUNT0	MGC_O_HDRC_RXCOUNT	/* re-used for EP0 */
 #define MGC_O_HDRC_TXTYPE	0x0A
 #define MGC_O_HDRC_TYPE0	MGC_O_HDRC_TXTYPE	/* re-used for EP0 */
 #define MGC_O_HDRC_TXINTERVAL	0x0B
 #define MGC_O_HDRC_NAKLIMIT0	MGC_O_HDRC_TXINTERVAL	/* re-used for EP0 */
 #define MGC_O_HDRC_RXTYPE	    0x0C
 #define MGC_O_HDRC_RXINTERVAL	0x0D
 #define MGC_O_HDRC_FIFOSIZE	    0x0F
 #define MGC_O_HDRC_CONFIGDATA	MGC_O_HDRC_FIFOSIZE	/* re-used for EP0 */
 
 /* "bus control" registers */
 #define MGC_O_HDRC_TXFUNCADDR	0x00
 #define MGC_O_HDRC_TXHUBADDR	0x02
 #define MGC_O_HDRC_TXHUBPORT	0x03
 
 #define MGC_O_HDRC_RXFUNCADDR	0x04
 #define MGC_O_HDRC_RXHUBADDR	0x06
 #define MGC_O_HDRC_RXHUBPORT	0x07
 
 
 
 /*
  *     MUSBHDRC Register bit masks
  */
 
 /* POWER */
 
 #define MGC_M_POWER_ISOUPDATE   0x80
 #define	MGC_M_POWER_SOFTCONN    0x40
 #define	MGC_M_POWER_HSENAB	0x20
 #define	MGC_M_POWER_HSMODE	0x10
 #define MGC_M_POWER_RESET       0x08
 #define MGC_M_POWER_RESUME      0x04
 #define MGC_M_POWER_SUSPENDM    0x02
 #define MGC_M_POWER_ENSUSPEND   0x01
 
 /*
  *  DRC register access macros
  */
 
 /* Get offset for a given FIFO */
 #define MGC_FIFO_OFFSET(_bEnd) (MGC_M_FIFO_EP0 + (_bEnd * 4))
 
 #define MGC_END_OFFSET(_bEnd, _bOffset)	(0x100 + (0x10*_bEnd) + _bOffset)
 
 #define MGC_BUSCTL_OFFSET(_bEnd, _bOffset)	(0x80 + (8*_bEnd) + _bOffset)
 
 
 /* indexed vs. flat register model */
 #ifdef MUSB_FLAT_REG
 #define MGC_SelectEnd(_pBase, _bEnd)
 #define MGC_ReadCsr8(_pBase, _bOffset, _bEnd) \
     MGC_Read8(_pBase, MGC_END_OFFSET(_bEnd, _bOffset))
 #define MGC_ReadCsr16(_pBase, _bOffset, _bEnd) \
     MGC_Read16(_pBase, MGC_END_OFFSET(_bEnd, _bOffset))
 #define MGC_WriteCsr8(_pBase, _bOffset, _bEnd, _bData) \
     MGC_Write8(_pBase, MGC_END_OFFSET(_bEnd, _bOffset), _bData)
 #define MGC_WriteCsr16(_pBase, _bOffset, _bEnd, _bData) \
     MGC_Write16(_pBase, MGC_END_OFFSET(_bEnd, _bOffset), _bData)
 #else
 #define MGC_SelectEnd(_pBase, _bEnd) \
     MGC_Write8(_pBase, MGC_O_HDRC_INDEX, _bEnd)
 #define MGC_ReadCsr8(_pBase, _bOffset, _bEnd) \
     MGC_Read8(_pBase, (_bOffset + 0x10))
 #define MGC_ReadCsr16(_pBase, _bOffset, _bEnd) \
     MGC_Read16(_pBase, (_bOffset + 0x10))
 #define MGC_WriteCsr8(_pBase, _bOffset, _bEnd, _bData) \
     MGC_Write8(_pBase, (_bOffset + 0x10), _bData)
 #define MGC_WriteCsr16(_pBase, _bOffset, _bEnd, _bData) \
     MGC_Write16(_pBase, (_bOffset + 0x10), _bData)
 #endif
 
 #endif	/* multiple inclusion protection */
 