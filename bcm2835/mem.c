/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems.
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

#include "bcm2835.h"

int
devg_get_memfuncs(disp_adapter_t *adp, disp_memfuncs_t *funcs, int tabsize)
{	
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "devg_get_memfuncs");

	DISP_ADD_FUNC(disp_memfuncs_t, funcs,
	    init, bcm2835_mem_init, tabsize);
	DISP_ADD_FUNC(disp_memfuncs_t, funcs,
	    fini, bcm2835_mem_fini, tabsize);
	DISP_ADD_FUNC(disp_memfuncs_t, funcs,
	    module_info, bcm2835_module_info, tabsize);
	DISP_ADD_FUNC(disp_memfuncs_t, funcs,
	    reset, bcm2835_mem_reset, tabsize);
	DISP_ADD_FUNC(disp_memfuncs_t, funcs,
	    alloc_surface, bcm2835_alloc_surface, tabsize);
	DISP_ADD_FUNC(disp_memfuncs_t, funcs,
	    free_surface, bcm2835_free_surface, tabsize);
	DISP_ADD_FUNC(disp_memfuncs_t, funcs,
	    mem_avail, bcm2835_mem_avail, tabsize);
 	DISP_ADD_FUNC(disp_memfuncs_t, funcs,
                query_apertures, bcm2835_query_apertures, tabsize);
    DISP_ADD_FUNC(disp_memfuncs_t, funcs,
            query_surface, bcm2835_query_surface, tabsize);
  DISP_ADD_FUNC(disp_memfuncs_t, funcs,
            get_alloc_info, bcm2835_get_alloc_info, tabsize);
    DISP_ADD_FUNC(disp_memfuncs_t, funcs,
            get_alloc_layer_info, bcm2835_get_alloc_layer_info, tabsize);
	
	return 0;

}

int
bcm2835_mem_init(disp_adapter_t *adapter, char *optstring)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_mem_init");
	
    return 0;
}

void
bcm2835_mem_fini(disp_adapter_t *adapter)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_mem_fini");
}

int
bcm2835_mem_reset(disp_adapter_t *adapter, disp_surface_t *surf)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_mem_reset");

	return 0;
}

disp_surface_t *
bcm2835_alloc_surface(disp_adapter_t *adapter,
    int width, int height, unsigned format, unsigned flags, unsigned user_flags)
{	
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_alloc_surface");

    return 0;
}

int
bcm2835_free_surface(disp_adapter_t *adapter, disp_surface_t *surf)
{	
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_free_surface");

	return 0;
}

unsigned long
bcm2835_mem_avail(disp_adapter_t *adapter, unsigned flags)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_mem_avail");

	return 0;
}

int
bcm2835_query_apertures(disp_adapter_t *adp, disp_aperture_t *ap)
{	
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_query_apertures");

    return 1;
}

/*
 * return the aperture within which the memory surface resides, and
 * the physical offset of the memory within that aperture
 */
int
bcm2835_query_surface(disp_adapter_t *adp,
    disp_surface_t *surf, disp_surface_info_t *info)
{       
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_query_surface");

    return 0;
}

/*
 * If a client of the driver wants to allocate memory itself,
 * it must allocate it in accordance with the parameters returned by
 * this process.  Since this memory will not be coming from
 * video memory, we must check the flags accordingly.
 */
int
bcm2835_get_alloc_info(disp_adapter_t *adp,
    int width, int height, unsigned format,
    unsigned flags, unsigned user_flags, disp_alloc_info_t *info)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_get_alloc_info");

    return 0;
}

int
bcm2835_get_alloc_layer_info(disp_adapter_t *adp, int dispno[], int layer_idx[],
    int nlayers, unsigned format, int surface_index, int width, int height,
    unsigned sflags, unsigned hint_flags, disp_alloc_info_t *info)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_get_alloc_layer_info");

    /* No layers */
    return -1;
}

