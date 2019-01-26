/****************************************************************
 *								*
 * Copyright (c) 2018-2019 YottaDB LLC. and/or its subsidiaries.*
 * All rights reserved.						*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"

#include "libyottadb_int.h"

/* Routine to drive ydb_lock_incr_s() in a worker thread so YottaDB access is isolated. Note because this drives ydb_lock_incr_s(),
 * we don't do any of the exclusive access checks here. The thread management itself takes care of most of that currently
 * but also the check in LIBYOTTADB_INIT*() macro will happen in ydb_lock_incr_s() still so no need for it here. The one
 * exception to this is that we need to make sure the run time is alive.
 *
 * Parms and return - same as ydb_lock_incr_s() except for the addition of tptoken and errstr.
 */
int ydb_lock_incr_st(uint64_t tptoken, ydb_buffer_t *errstr, unsigned long long timeout_nsec, ydb_buffer_t *varname, int subs_used,
		     ydb_buffer_t *subsarray)
{
	intptr_t	retval;
#	ifndef GTM64
	unsigned int	tparm1, tparm2;
#	endif
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	LIBYOTTADB_RUNTIME_CHECK((int), errstr);
	VERIFY_THREADED_API((int), errstr);
#	ifdef GTM64
	retval = ydb_stm_args4(tptoken, errstr, LYDB_RTN_LOCK_INCR, (uintptr_t)timeout_nsec, (uintptr_t)varname,
			       (uintptr_t)subs_used, (uintptr_t)subsarray);
#	else
	/* 32 bit addresses - have to split long long parm into 2 pieces and pass as 2 parms */
#	ifdef BIGENDIAN
	tparm1 = (uintptr_t)(timeout_nsec >> 32);
	tparm2 = (uintptr_t)(timeout_nsec & 0xffffffff);
#	else
	tparm1 = (uintptr_t)(timeout_nsec & 0xffffffff);
	tparm2 = (uintptr_t)(timeout_nsec >> 32);
#	endif
	retval = ydb_stm_args5(tptoken, errstr, LYDB_RTN_LOCK_INCR, (uintptr_t)tparm1, (uintptr_t)tparm2, (uintptr_t)varname,
			       (uintptr_t)subs_used, (uintptr_t)subsarray);

#	endif
	return (int)retval;
}
