#ifndef __bcm2835_H_INCLUDED
#define __bcm2835_H_INCLUDED

#include <graphics/display.h>
#include <graphics/ffb.h>
#include <sys/slog.h>
#include <sys/slogcodes.h>


/*
 * Mode related entry points
 */
int bcm2835_init(disp_adapter_t *adapter, char *opt);
void bcm2835_fini(disp_adapter_t *adapter);
void bcm2835_module_info(disp_adapter_t *adapter, disp_module_info_t *info);
int bcm2835_get_modelist(disp_adapter_t *adapter, int dispno,
    disp_mode_t *list, int index, int size);
int bcm2835_get_modeinfo(disp_adapter_t *adapter, int dispno,
    disp_mode_t mode, disp_mode_info_t *info);
int bcm2835_set_mode(disp_adapter_t *adapter, int dispno, disp_mode_t mode,
    disp_crtc_settings_t *settings, disp_surface_t *surf, unsigned flags);
int bcm2835_set_display_offset(disp_adapter_t *ctx, int dispno,
    unsigned offset, int wait_vsync);

/* Miscellaneous draw related functions */
int bcm2835_draw_init(disp_adapter_t *adapter, char *opt);
void bcm2835_draw_fini(disp_adapter_t *adapter);
int bcm2835_attach_external(disp_adapter_t *adapter, disp_aperture_t aper[]);
int bcm2835_detach_external(disp_adapter_t *adapter);
int bcm2835_recover(disp_adapter_t *adapter);
int bcm2835_misc_wait_idle(disp_adapter_t *adapter);

/*
 * Memory manager entry points
 */
int bcm2835_mem_init(disp_adapter_t *adapter, char *optstring);
void bcm2835_mem_fini(disp_adapter_t *adapter);
int bcm2835_mem_reset(disp_adapter_t *adapter, disp_surface_t *surf);
disp_surface_t *bcm2835_alloc_surface(disp_adapter_t *adapter,
    int width, int height, unsigned format, unsigned flags, unsigned user_flags);
int bcm2835_free_surface(disp_adapter_t *adapter, disp_surface_t *surf);
unsigned long bcm2835_mem_avail(disp_adapter_t *adapter, unsigned sflags);

int bcm2835_query_apertures(disp_adapter_t *adp, disp_aperture_t *aptertures);
int bcm2835_query_surface(disp_adapter_t *adapter,
    disp_surface_t *surf, disp_surface_info_t *info);
int bcm2835_get_alloc_info(disp_adapter_t *adp,
    int width, int height, unsigned format,
    unsigned flags, unsigned user_flags, disp_alloc_info_t *info);
int bcm2835_get_alloc_layer_info(disp_adapter_t *adp, int dispno[], int layer_idx[],
    int nlayers, unsigned format, int surface_index, int width, int height,
    unsigned sflags, unsigned hint_flags, disp_alloc_info_t *info);

#endif /* __bcm2835_H_INCLUDED */
