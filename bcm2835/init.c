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
bcm2835_init(disp_adapter_t *adapter, char *optstring)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_init");

	return 0;
}

/*
 * Called when there's no more drawing to be done (e.g. a mode-switch is
 * about to occur or the driver is about to be unloaded).
 */
void
bcm2835_fini(disp_adapter_t *adapter)
{
	slogf(_SLOGC_GRAPHICS, _SLOG_INFO, "bcm2835_fini");
}

