
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

	at91sam9xx_context_t		*at91sam9xx = adapter->ms_ctx;
	memset(info, 0, sizeof (*info));
	
	info->size = sizeof (*info);
	info->mode = mode;

	switch (mode) {

		case 16:
			info->pixel_format = DISP_SURFACE_FORMAT_RGB565;
			break;
		case 24:
			info->pixel_format = DISP_SURFACE_FORMAT_RGB888;
			break;
		case 32:
			info->pixel_format = DISP_SURFACE_FORMAT_ARGB8888;
				break;
	}

	info->xres = at91sam9xx->width;
	info->yres = at91sam9xx->height;
	info->u.fixed.refresh[0] = LCD_DFT_FRAMERATE;
	info->u.fixed.refresh[1] = 0;	

	return 0;
}

int
bcm2835_set_mode(disp_adapter_t *adapter, int dispno, disp_mode_t mode,
    disp_crtc_settings_t *settings, disp_surface_t *surf, unsigned flags)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_set_mode");

	/* empty */

	return 0;
}


int
bcm2835_get_modelist(disp_adapter_t *adapter, int dispno, disp_mode_t *list,
    int index, int size)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_get_modelist");

	static unsigned modes[] = {16, 24,32};
	int i, j = 0;
	for (i=index; j<size-1 && i < sizeof(modes)/sizeof(modes[0]); i++)
		list[j++] = modes[i];

	list[j] = DISP_MODE_LISTEND;

	return 0;
}

int  
bcm2835_set_display_offset(disp_adapter_t *adapter,
    int dispno, unsigned offset, int wait_vsync)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_set_display_offset");

	/* empty */

	return 0;
}

