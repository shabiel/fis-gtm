/****************************************************************
 *								*
 * Copyright (c) 2006-2017 Fidelity National Information	*
 * Services, Inc. and/or its subsidiaries. All rights reserved.	*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"

#include "gtm_string.h"
#include "stringpool.h"
#include "min_max.h"
#include "fnpc.h"
#include "op.h"
#include "gtm_utf8.h"

GBLREF spdesc		stringpool;
GBLREF boolean_t	gtm_utf8_mode;		/* We are indeed doing the UTF8 thang */
GBLREF boolean_t	badchar_inhibit;	/* No BADCHAR errors should be signaled */

#ifdef DEBUG
#  define SETWON setp_work = TRUE;
#  define SETWOFF setp_work = FALSE;
#else
#  define SETWON
#  define SETWOFF
#endif

error_def(ERR_MAXSTRLEN);

/*
 * ----------------------------------------------------------
 * Fast path setpiece when delimiter is one (lit) char replacing
 * a single piece (last is same as first). Unicode flavor.
 *
 * Arguments:
 *	src	- source mval
 *	delim	- delimiter char
 *	expr	- expression string mval
 *	ind	- index in source mval to be set
 *	dst	- destination mval where the result is saved.
 *
 * Return:
 *	none
 * ----------------------------------------------------------
 */
void CYGWIN64_ABI op_setp1(mval *src, int delim, mval *expr, int ind, mval *dst)
{
	size_t		str_len, delim_cnt;
	int		len, pfx_str_len, sfx_start_offset, sfx_str_len, rep_str_len, pfx_scan_offset;
	int		dlmlen, cpy_cache_lines, mblen, lmsdelim;
	unsigned char	*start_sfx, *str_addr, *end_pfx, *end_src, *start_pfx;
	boolean_t	do_scan, delim_last_scan, valid_char;
	mval		dummymval;	/* It's value is not used but is part of the call to op_fnp1() */
	fnpc		*cfnpc, *pfnpc;
	delimfmt	ldelim;
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	assert(gtm_utf8_mode);
	do_scan = FALSE;
	cpy_cache_lines = -1;
	ldelim.unichar_val = delim;
        if (!UTF8_VALID(ldelim.unibytes_val, (ldelim.unibytes_val + SIZEOF(ldelim.unibytes_val)), dlmlen)
	    && !badchar_inhibit)
	{	/* The delimiter is a bad character so error out if badchar not inhibited */
		UTF8_BADCHAR(0, ldelim.unibytes_val, ldelim.unibytes_val + SIZEOF(ldelim.unibytes_val), 0, NULL);
	}
	MV_FORCE_STR(expr);	/* Expression to put into piece place */
	if (MV_DEFINED(src))
	{
		/* We have 3 possible scenarios:
		 * 1) The source string is null. Nothing to do but proceed to building output.
		 * 2) If the requested piece is larger than can be cached by op_fnp1, call fnp1
		 *    for the maximum piece possible, use the cache info to "prime the pump" and
		 *    then process the rest of the string ourselves.
		 * 3) If the requested piece can be obtained from the cache, call op_fnp1 to validate
		 *    and rebuild the cache if necessary and then retrieve the necessary info from
		 *    the fnpc cache.
		 */
		MV_FORCE_STR(src);	/* Make sure is string prior to length check */
		if (0 == src->str.len)
		{	/* We have a null source string */
			pfx_str_len = sfx_str_len = sfx_start_offset = 0;
			delim_cnt = (0 < ind) ? (size_t)ind - 1 : 0;
		} else if (FNPC_ELEM_MAX >= ind)
		{	/* 3) Best of all possible cases. The op_fnp1 can do most of our work for us
			 *    and we can preload the cache on the new string to help its subsequent
			 *    uses along as well.
			 */
			SETWON;
			op_fnp1(src, delim, ind, &dummymval);
			SETWOFF;
			cfnpc = &(TREF(fnpca)).fnpcs[src->fnpc_indx - 1];
			assert(cfnpc->last_str.addr == src->str.addr);
			assert(cfnpc->last_str.len == src->str.len);
			assert(cfnpc->delim == delim);
			assert(0 < cfnpc->npcs);
			/* Three more scenarios: #1 piece all in cache, #2 piece would be in cache but ran
			 * out of text or #3 piece is beyond what can be cached
			 */
			if (cfnpc->npcs >= ind)
			{	/* #1 The piece we want is totally within the cache which is good news */
				pfx_str_len = cfnpc->pstart[ind - 1];
				delim_cnt = 0;
				sfx_start_offset = cfnpc->pstart[ind] - dlmlen;				/* Include delimiter */
				rep_str_len = cfnpc->pstart[ind] - cfnpc->pstart[ind - 1] - dlmlen;	/* Replace string length */
				sfx_str_len = src->str.len - pfx_str_len - rep_str_len;
				cpy_cache_lines = ind - 1;
			} else
			{	/* #2 The string was too short so the cache does not contain our string. This means
				 * that the prefix becomes any text that IS in the cache and we set the delim_cnt
				 * to be the number of missing pieces so the delimiters can be put in as part of the
				 * prefix when we build the new string.
				 */
				pfx_str_len = cfnpc->pstart[cfnpc->npcs] - dlmlen;
				delim_cnt = (size_t)(ind - cfnpc->npcs);
				sfx_start_offset = 0;
				sfx_str_len = 0;
				cpy_cache_lines = cfnpc->npcs;
			}
		} else
		{	/* 2) We have a element that would not be able to be in the fnpc cache. Go ahead
			 *    and call op_fnp1 to get cache info up to the maximum and then we will continue
			 *    the scan on our own.
			 */
			SETWON;
			op_fnp1(src, delim, FNPC_ELEM_MAX, &dummymval);
			SETWOFF;
			cfnpc = &(TREF(fnpca)).fnpcs[src->fnpc_indx - 1];
			assert(cfnpc->last_str.addr == src->str.addr);
			assert(cfnpc->last_str.len == src->str.len);
			assert(cfnpc->delim == delim);
			assert(0 < cfnpc->npcs);
			if (FNPC_ELEM_MAX > cfnpc->npcs)
			{	/* We ran out of text so the scan is complete. This is basically the same
				 * as case #2 above.
				 */
				pfx_str_len = cfnpc->pstart[cfnpc->npcs] - dlmlen;
				delim_cnt = (size_t)(ind - cfnpc->npcs);
				sfx_start_offset = 0;
				sfx_str_len = 0;
				cpy_cache_lines = cfnpc->npcs;
			} else
			{	/* We have a case where the piece we want cannot be kept in cache. In the special
				 * case where there is no more text to handle, we don't need to scan further. Otherwise
				 * we prime the pump and continue the scan where the cache left off.
				 */
				if ((pfx_scan_offset = cfnpc->pstart[FNPC_ELEM_MAX]) < src->str.len)	/* Note assignment */
					/* Normal case where we prime the pump */
					do_scan = TRUE;
				else
				{	/* Special case -- no more text to scan */
					pfx_str_len = cfnpc->pstart[FNPC_ELEM_MAX] - dlmlen;
					sfx_start_offset = 0;
					sfx_str_len = 0;
				}
				delim_cnt = (size_t)ind - FNPC_ELEM_MAX;
				cpy_cache_lines = FNPC_ELEM_MAX;
			}
		}
	} else
	{	/* Source is not defined -- treat as a null string */
		pfx_str_len = sfx_str_len = sfx_start_offset = 0;
		delim_cnt = (size_t)ind - 1;
	}
	/* If we have been forced to do our own scan, do that here. Note the variable pfx_scan_offset has been
	 * set to where the scan should begin in the src string and delim_cnt has been set to how many delimiters
	 * still need to be processed.
	 */
	if (do_scan)
	{	/* Scan the line isolating prefix piece, and end of the
		 * piece being replaced
		 */
		COUNT_EVENT(small);
		end_pfx = start_sfx = (unsigned char *)src->str.addr + pfx_scan_offset;
		end_src = (unsigned char *)src->str.addr + src->str.len;
		/* The compiler would unroll this loop this way anyway but we want to
		 * adjust the start_sfx pointer after the loop but only if we have gone
		 * into it at least once.
		 */
		if ((0 < delim_cnt) && (start_sfx < end_src))
		{
			do
			{
				end_pfx = start_sfx;
				delim_last_scan = FALSE;		/* Whether delimiter is last character scanned */
				while (start_sfx < end_src)
				{
					valid_char = UTF8_VALID(start_sfx, end_src, mblen); /* Length of next char */
					if (!valid_char)
					{	/* Next character is not valid unicode. If badchar error is not inhibited,
						 * signal it now. If it is inhibited, just treat the character as a single
						 * character and continue.
						 */
						if (!badchar_inhibit)
							utf8_badchar(0, start_sfx, end_src, 0, NULL);
						assert(1 == mblen);
					}
					/* Getting mblen first allows us to do quick length compare before the
					 * heavier weight memcmp call.
					 */
					assert(0 < mblen);
					if (mblen == dlmlen && 0 == memcmp(start_sfx, ldelim.unibytes_val, dlmlen))
					{
						delim_last_scan = TRUE;
						break;
					}
					/* Increment ptrs by size of found char */
					start_sfx += mblen;
				}
				start_sfx += dlmlen;
				delim_cnt--;
			} while ((0 < delim_cnt) && (start_sfx < end_src));
			/* We have to backup up the suffix start pointer except under the condition
			 * that the last character in the buffer is the last delimiter we were looking
			 * for.
			 */
			if ((0 == delim_cnt) || (start_sfx < end_src) || !delim_last_scan)
				start_sfx -= dlmlen;			/* Back up suffix to include delimiter char */
			/* If we scanned to the end (no text left) and still have delimiters to
			 * find, the entire src text should be part of the prefix
			 */
			if ((start_sfx >= end_src) && (0 < delim_cnt))
			{
				end_pfx = start_sfx;
				if (delim_last_scan)			/* if last char was delim, reduce delim cnt */
					--delim_cnt;
			}
		} else
		{
			/* If not doing any token finding, then this count becomes the number
			 * of tokens to output. Adjust accordingly.
			 */
			if (0 < delim_cnt)
				--delim_cnt;
		}
		INCR_COUNT(small_pcs, (int)((size_t)ind - delim_cnt));
		/* Now having the following situation:
		 * end_pfx	-> end of the prefix piece including delimiter
		 * start_sfx	-> start of suffix piece (with delimiter) or = end_pfx/src->str.addr if none
		 */
		pfx_str_len = (int)(end_pfx - (unsigned char *)src->str.addr);
		if (0 > pfx_str_len)
			pfx_str_len = 0;
		sfx_start_offset = (int)(start_sfx - (unsigned char *)src->str.addr);
		sfx_str_len = src->str.len - sfx_start_offset;
		if (0 > sfx_str_len)
			sfx_str_len = 0;
	}
	/* Calculate total string len. delim_cnt has needed padding delimiters for null fields */
	str_len = (size_t)expr->str.len + (size_t)pfx_str_len + (delim_cnt * (size_t)dlmlen) + (size_t)sfx_str_len;
	if (MAX_STRLEN < str_len)
		rts_error_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_MAXSTRLEN);
	ENSURE_STP_FREE_SPACE((int)str_len);
	str_addr = stringpool.free;
	start_pfx = (unsigned char *)src->str.addr;
	/* copy prefix */
	if (0 < pfx_str_len)
	{
		memcpy(str_addr, src->str.addr, pfx_str_len);
		str_addr += pfx_str_len;
	}
	/* copy delimiters */
	if (gtm_utf8_mode && (1 < dlmlen))
	{	/* In this mode, delimiters can exceed 1 character so copy them this way */
		while (0 < delim_cnt--)
		{
			memcpy(str_addr, ldelim.unibytes_val, dlmlen);
			str_addr += dlmlen;
		}
	} else
	{	/* If delimiters are 1 byte (M mode always and perhaps UTF8 mode), use this simpler/faster method */
		lmsdelim = (gtm_utf8_mode) ? ldelim.unibytes_val[0] : delim;
		memset(str_addr, lmsdelim, delim_cnt);
		str_addr += delim_cnt;
	}
	/* copy expression */
	if (0 < expr->str.len)
	{
		memcpy(str_addr, expr->str.addr, expr->str.len);
		str_addr += expr->str.len;
	}
	/* copy suffix */
	if (0 < sfx_str_len)
	{
		memcpy(str_addr, start_pfx + sfx_start_offset, sfx_str_len);
		str_addr += sfx_str_len;
	}
	assert(IS_AT_END_OF_STRINGPOOL(str_addr, -str_len));
	dst->mvtype = MV_STR;
	dst->str.len = INTCAST(str_addr - stringpool.free);
	dst->str.addr = (char *)stringpool.free;
	stringpool.free = str_addr;
	/* If available, update the cache information for this newly created mval to hopefully
	 * give it a head start on its next usage. Note that we can only copy over the cache info
	 * for the prefix. We cannot include information for the 'expression' except where it starts
	 * because the expression could itself contain delimiters that would be found on a rescan.
	 */
	if (0 < cpy_cache_lines)
	{
		pfnpc = cfnpc;				/* pointer for src mval's cache */
		do
		{
			cfnpc = (TREF(fnpca)).fnpcsteal;	/* Next cache element to steal */
			if ((TREF(fnpca)).fnpcmax < cfnpc)
				cfnpc = &(TREF(fnpca)).fnpcs[0];
			(TREF(fnpca)).fnpcsteal = cfnpc + 1;	/* -> next element to steal */
		} while (cfnpc == pfnpc);		/* Make sure we don't step on ourselves */
		cfnpc->last_str = dst->str;		/* Save validation info */
		cfnpc->delim = delim;
		cfnpc->npcs = cpy_cache_lines;
		dst->fnpc_indx = cfnpc->indx + 1;	/* Save where we are putting this element
							 * (1 based index in mval so 0 isn't so common)
							 */
		memcpy(&cfnpc->pstart[0], &pfnpc->pstart[0], (cfnpc->npcs + 1) * SIZEOF(unsigned int));
	} else
		/* No cache available -- just reset index pointer to get fastest cache validation failure */
		dst->fnpc_indx = (unsigned char)-1;
}
