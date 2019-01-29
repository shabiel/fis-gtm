/****************************************************************
 *								*
 * Copyright (c) 2001-2015 Fidelity National Information 	*
 * Services, Inc. and/or its subsidiaries. All rights reserved.	*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"
#include "mvalconv.h"
#include "op.h"

#ifdef UNICODE_SUPPORTED
#include "gtm_utf8.h"

GBLREF	boolean_t	badchar_inhibit;
GBLREF boolean_t        gtm_utf8_mode;

/* Returns the Unicode code point of a character in a string at a given index */
void CYGWIN64_ABI	op_fnascii(int4 num, mval* in, mval* out)
{
	int	bytelen;
	unsigned int code;
	char	*in_ptr, *in_top;

	DCL_THREADGBL_ACCESS;
	SETUP_THREADGBL_ACCESS;

	/* We should never check badchar_inhibit if we are in compile_time and have badchar's;
		ie, we should never get this far with badchar's during compile time */
	assert(!TREF(compile_time) || valid_utf_string(&in->str));

	num--;	/* make it a 0-index based */
	if (!gtm_utf8_mode || MV_IS_SINGLEBYTE(in))
	{ /* Fast path evaluation for strings with no multi-byte characters */
		assert(MV_IS_STRING(in));  /* MV_UTF_LEN must subsume MV_STR */
		if ((num < in->str.len) && (num >= 0))
		{
			if ((code = *(unsigned char *)(in->str.addr + num)) > ASCII_MAX)
			{	/* Isolated bytes in the range [0x80,0xFF] must be considered illegal */
				if (!gtm_utf8_mode || badchar_inhibit)
					code = (unsigned int)-1;
				else
					UTF8_BADCHAR(1, in->str.addr + num, NULL, 0, NULL);
			}

		} else
			code = (unsigned int)-1;
	} else
	{ /* Generic processing for strings with multi-byte characters */
		MV_FORCE_STR(in);
		in_ptr = in->str.addr;
		in_top = in->str.addr + in->str.len;
		if (!badchar_inhibit)
		{
			for (; (0 < num && in_ptr < in_top); --num)
			{
				if (!UTF8_VALID(in_ptr, in_top, bytelen))
					UTF8_BADCHAR(0, in_ptr, in_top, 0, NULL);
				in_ptr += bytelen;
			}
		} else
		{
			for (; (0 < num && in_ptr < in_top); --num)
				in_ptr = (char *)UTF8_MBNEXT(in_ptr, in_top);  /* Note: code for invalid character ?? */
		}
		if (0 == num && in_ptr < in_top)
		{
			UTF8_MBTOWC(in_ptr, in_top, code);
			if (WEOF == code)
			{
				if (badchar_inhibit)
					code = (unsigned int)-1;
				else
					UTF8_BADCHAR(0, in_ptr, in_top, 0, NULL);
			}
		} else
			code = (unsigned int)-1; /* required character position exceeds the character length */
	}
	MV_FORCE_MVAL(out, (int)code);
}
#endif /* UNICODE_SUPPORTED */

void CYGWIN64_ABI	op_fnzascii(int4 num, mval* in, mval* out)
{
	int	k ;
	MV_FORCE_STR(in);
	num--;
	if ( num >= in->str.len || num < 0 )
	{
		k = -1 ;
	} else
		k = *(unsigned char *)(in->str.addr + num) ;
	MV_FORCE_MVAL(out,k) ;
}
