
#include "bcm2835.h"



int
devg_get_modefuncs(disp_adapter_t *adp, disp_modefuncs_t *funcs, int tabsize)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "devg_get_modefuncs");

	//slogf(0,0,"devg_get_modefuncs(mode) \n");
	DISP_ADD_FUNC(disp_modefuncs_t, funcs,
	    init, bcm2835_init, tabsize);
	DISP_ADD_FUNC(disp_modefuncs_t, funcs,
	    fini, bcm2835_fini, tabsize);
	DISP_ADD_FUNC(disp_modefuncs_t, funcs,
	    module_info, bcm2835_module_info, tabsize);
	DISP_ADD_FUNC(disp_modefuncs_t, funcs,
	    get_modeinfo, bcm2835_get_modeinfo, tabsize);
	DISP_ADD_FUNC(disp_modefuncs_t, funcs,
	    get_modelist, bcm2835_get_modelist, tabsize);
	DISP_ADD_FUNC(disp_modefuncs_t, funcs,
	    set_mode, bcm2835_set_mode, tabsize);
	DISP_ADD_FUNC(disp_modefuncs_t, funcs,
	    set_display_offset, bcm2835_set_display_offset, tabsize);
	    
	return 0;
}

int
bcm2835_get_modeinfo(disp_adapter_t *adapter,
    int dispno, disp_mode_t mode, disp_mode_info_t *info)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_get_modeinfo");

	return 0;
}

int
bcm2835_set_mode(disp_adapter_t *adapter, int dispno, disp_mode_t mode,
    disp_crtc_settings_t *settings, disp_surface_t *surf, unsigned flags)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_set_mode");

	return 0;
}


int
bcm2835_get_modelist(disp_adapter_t *adapter, int dispno, disp_mode_t *list,
    int index, int size)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_get_modelist");

	return 0;
}

int  
bcm2835_set_display_offset(disp_adapter_t *adapter,
    int dispno, unsigned offset, int wait_vsync)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_set_display_offset");

	return 0;
}

