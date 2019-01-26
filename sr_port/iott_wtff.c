/****************************************************************
 *								*
 * Copyright (c) 2001-2015 Fidelity National Information 	*
 * Services, Inc. and/or its subsidiaries. All rights reserved.	*
 *								*
 * Copyright (c) 2018 YottaDB LLC. and/or its subsidiaries.	*
 * All rights reserved.						*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"

#include "io.h"
#include "iottdef.h"
#include "io_params.h"
#include "error.h"

GBLREF io_pair io_curr_device;

static readonly unsigned char home_param_list[] =
{
	(unsigned char)iop_x,
	0, 0, 0, 0,
	(unsigned char)iop_y,
	0, 0, 0, 0,
	(unsigned char)iop_clearscreen,
	(unsigned char)iop_eol
};
static readonly mval home_params = DEFINE_MVAL_LITERAL(MV_STR, 0, 0, SIZEOF(home_param_list) - 1, (char *)home_param_list, 0, 0);

void iott_wtff(void)
{
	boolean_t ch_set;
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	ESTABLISH_GTMIO_CH(&io_curr_device, ch_set);
	io_curr_device.out->esc_state = START;
	iott_use(io_curr_device.out, &home_params);
	REVERT_GTMIO_CH(&io_curr_device, ch_set);
}
