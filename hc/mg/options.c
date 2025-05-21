/*
 * $QNXLicenseC:
 * Copyright 2008-2009, QNX Software Systems.
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


/*
#ifdef __USAGE
%C - USB Server  ( Universal Serial Bus )

%C [options] &
Options:
    ioport=addr     Register base address
    irq=num         Interrupt request number
    num_ed=num      Number endpoint descriptors to preallocate.
    num_td=num      Number transfer descriptors to preallocate.
    verbose=num     Set verbosity level.
    prio=num        Set Priority of the Interrupt handler worker thread.
    fconfig=fcfg    Configure FIFO sizes num:size[;num:size]
                    (default 16:8;4:16;8:64;2:128;14:512 )
    nodma           Disable DMA
    dma_reserved    Reserve DMA channels for endpoints.(default share)
	isoc_pio		force isoc to use pio mode
Examples:
        io-usb -d dm816x-mg ioport=0x47401400,irq=18
        io-usn -d dm816x-mg ioport=0x47401C00,irq=19


#endif
*/
