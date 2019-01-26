/****************************************************************
 *								*
 * Copyright 2001, 2013 Fidelity Information Services, Inc	*
 *								*
 * Copyright (c) 2019 YottaDB LLC. and/or its subsidiaries.	*
 * All rights reserved.						*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"

#include <errno.h>
#include "gtm_signal.h"
#ifdef GTM_PTHREAD
#  include "gtm_pthread.h"
#endif
#include "gtm_stdio.h"

#include "ctrlc_handler.h"
#include "std_dev_outbndset.h"
#include "generic_signal_handler.h"
#include "gtmio.h"
#include "io.h"
#include "invocation_mode.h"
#include "libyottadb_int.h"

GBLREF	struct sigaction	orig_sig_action[];

void ctrlc_handler(int sig, siginfo_t *info, void *context)
{
	int4    ob_char;
	int	save_errno;

	assert(SIGINT == sig);
	FORWARD_SIG_TO_MAIN_THREAD_IF_NEEDED(sig, IS_EXI_SIGNAL_FALSE, NULL, NULL);
	if (!(MUMPS_CALLIN & invocation_mode))
	{	/* Normal procedure from MUMPS is to set our outofband trigger to handle this signal */
		save_errno = errno;
		ob_char = 3;
		std_dev_outbndset(ob_char);
		errno = save_errno;
	} else
	{	/* If this is call-in/simpleAPI mode and a handler exists for this signal, call it */
		DRIVE_NON_YDB_SIGNAL_HANDLER_IF_ANY("ctrlc_handler", sig, info, context, TRUE);
		/* If we returned from the caller's handler (or none was driven), we need to exit */
		EXIT(-1);
	}
}
