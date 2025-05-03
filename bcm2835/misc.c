

#include "bcm2835.h"


/*
 * Populate the miscellaneuous graphics driver function table.  
 * tabsize is the size of the function table in bytes.
 */
int
devg_get_miscfuncs(disp_adapter_t *adapter,
    disp_draw_miscfuncs_t *funcs, int tabsize)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "devg_get_miscfuncs");

	DISP_ADD_FUNC(disp_draw_miscfuncs_t, funcs,
	    init, bcm2835_draw_init, tabsize);
	DISP_ADD_FUNC(disp_draw_miscfuncs_t, funcs,
	    fini, bcm2835_draw_fini, tabsize);
	DISP_ADD_FUNC(disp_draw_miscfuncs_t, funcs,
	    module_info, bcm2835_module_info, tabsize);
    DISP_ADD_FUNC(disp_draw_miscfuncs_t, funcs,
        get_corefuncs_sw, ffb_get_corefuncs, tabsize);
    DISP_ADD_FUNC(disp_draw_miscfuncs_t, funcs,
        get_contextfuncs_sw, ffb_get_contextfuncs, tabsize);
        DISP_ADD_FUNC(disp_draw_miscfuncs_t, funcs,
        attach_external, bcm2835_attach_external, tabsize);
    DISP_ADD_FUNC(disp_draw_miscfuncs_t, funcs,
        detach_external, bcm2835_detach_external, tabsize);
    DISP_ADD_FUNC(disp_draw_miscfuncs_t, funcs,
        recover, bcm2835_recover, tabsize);
    DISP_ADD_FUNC(disp_draw_miscfuncs_t, funcs,
        wait_idle, bcm2835_misc_wait_idle, tabsize);

	return 0;
	
}

void
bcm2835_module_info(disp_adapter_t *adapter, disp_module_info_t *info)
{	
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_module_info");

		info->description = "BCM2835 Processor";
        info->ddk_version_major = DDK_VERSION_MAJOR;
        info->ddk_version_minor = DDK_VERSION_MINOR;
        info->ddk_rev = DDK_REVISION;
        info->driver_rev = 0;
}


int
bcm2835_draw_init(disp_adapter_t *adapter, char *opt)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_draw_init");

    /* empty */

	return 0;
}

void
bcm2835_draw_fini(disp_adapter_t *adapter)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_draw_fini");

    /* empty */
}

/*
 * Set up things so that miscfuncs, corefuncs and contextfuncs
 * can be called by an external process.
 */
int
bcm2835_attach_external(disp_adapter_t *adapter, disp_aperture_t aper[])
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_attach_external");

    at91sam9xx_context_t		*at91sam9xx = adapter->shmem;
	adapter->ms_ctx = at91sam9xx;

	return 0;

}

int
bcm2835_detach_external(disp_adapter_t *adapter)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_detach_external");

    /* empty */

    return 0;
}

/*
 * Called when a client process terminated unexpectedly.  This could have
 * happened in the middle of adding draw commands to the ring buffer.
 * Reset the ring buffer so any partial draw commands are not sent to
 * the Radeon.
 */
int
bcm2835_recover(disp_adapter_t *adapter)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_recover");
    
    return 0;
}	

int
bcm2835_misc_wait_idle(disp_adapter_t *adapter)
{
	at91sam9xx_context_t             *at91sam9xx = adapter->shmem;

	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_misc_wait_idle");

    /* empty */

    return 0;
}

