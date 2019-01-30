/****************************************************************
 *								*
 *	Copyright 2001, 2014 Fidelity Information Services, Inc	*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"
#include "op.h"

error_def(ERR_LABELNOTFND);

void CYGWIN64_ABI op_rterror(int4 sig, boolean_t subrtn)
{
	/* If this module is called as an M subroutine, the message we generate will not have the correct M line-of-code reference
	 * because (1) we have already created the stackframe for the subroutine call we are not now going to make and (2) the code
	 * generator puts the code to call us at the end of the module. Therefore the Mref generated will be the last line in the
	 * module. To get around this, if this is a subroutine/function call we will unwind this (bogus) frame prior to making the
	 * error call so the M reference in the error message will be the actual subroutine call itself instead of the last
	 * physical line of the module. Inline calls will not do an unwind() based on the distinguished error for GOTO or the
	 * subrtn flag.
	 */
	if (subrtn && (ERR_LABELNOTFND != sig))
		op_unwind();
	rts_error_csa(CSA_ARG(NULL) VARLSTCNT(2) sig, 0);
}
