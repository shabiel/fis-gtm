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

#include "gtm_string.h"
#include "error.h"
#include "io.h"
#include "iottdef.h"

UNIX_ONLY(error_def(ERR_ZINTRECURSEIO);)

/* essentially the same as ionl_wteol */
void iott_wteol(int4 val, io_desc *io_ptr)
{
	mstr		eol;
	int		eol_cnt;
	boolean_t	ch_set;
	UNIX_ONLY(d_tt_struct	*tt_ptr;)
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	assert(val);
	tt_ptr = (d_tt_struct *)io_ptr->dev_sp;
	if (tt_ptr->mupintr)
		rts_error_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_ZINTRECURSEIO);
	ESTABLISH_GTMIO_CH(&io_ptr->pair, ch_set);
	io_ptr->esc_state = START;
	eol.len = STRLEN(NATIVE_TTEOL);
	eol.addr = (char *)NATIVE_TTEOL;
	for (eol_cnt = val; eol_cnt--; )
	{
		io_ptr->dollar.x = 0; /* so that iott_write doesn't try to wrap (based on escape state and width) */
		iott_write(&eol);
	}
	/* $X is maintained in VMS without the below assignment (resetting to 0) because the NATIVE_TTEOL is \015\012
	 * and the <CR> (\015) triggers appropriate maintenance of $X.  In UNIX, NATIVE_TTEOL is \012, so
	 * FILTER=CHARACTER effectively turns off all $X maintenance (except for WRAP logic).
	 * In VMS the below assignment is not necessary, but harmless; it is always logically correct.
	 */
	io_ptr->dollar.x = 0;
	if (!(io_ptr->write_filter & CHAR_FILTER))
	{	/* If no FILTER and EOL, also maintain $Y;
		 * If FILTER, dollarx() of the linefeed character \012 takes care of this maintenance.
		 */
		io_ptr->dollar.y += val;
		if (io_ptr->length)
			io_ptr->dollar.y %= io_ptr->length;
	}
	REVERT_GTMIO_CH(&io_ptr->pair, ch_set);
	return;
}
