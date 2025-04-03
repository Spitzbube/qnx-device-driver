
/*
#ifdef __USAGE
%C Driver for DM816X USB OTG Controller (Host Only)

Syntax:
io-usb-otg -d dm816x-mg [option[,option ...]] ... &

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
	ctrl_noping		Disable PING on high-speed Control transfers
	out_rndis		Enable RNDIS in OUT Bulk transfers (default disabled).
	in_rndis		Disable RNDIS DMA mode for IN Bulk transfers
	swtoggle		Enable sw Data toggle workardound for rx dma
	edma			Use EDMA other than the default CPPI DMA
	edmachannel		The first EDMA channel available for this driver (default 0)	
	edmairq			The IRQ number corresponds to 'edmachannel'. 
    charge_detect   The GPIO base address and pin number to control the battery controller

Examples:
        io-usb-otg -d dm816x-mg ioport=0x47401400,irq=18
        io-usn -d dm816x-mg ioport=0x47401C00,irq=19
        io-usb-otg -d dm816x-mg ioport=0x47401400,irq=18,edma
        io-usb-otg -d dm816x-mg ioport=0x47401400,irq=18,edma,edmachannel=5,edmairq=517
        io-usn -d dm816x-mg ioport=0x47401C00,irq=19,charge_detect=0x4804C000^6

#endif
*/
