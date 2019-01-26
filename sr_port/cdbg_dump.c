/****************************************************************
 *								*
 * Copyright (c) 2001-2017 Fidelity National Information	*
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

#include "gtm_stdio.h"
#include "gtm_string.h"

#include "gtmdbglvl.h"
#include "compiler.h"
#include "opcode.h"
#include "mvalconv.h"
#include "cdbg_dump.h"
#include "stringpool.h"
#include "cache.h"
#include "gtmio.h"
#include "have_crit.h"
#include "mdq.h"

LITDEF char *oprtype_names[] =
{
	"Operand[0]",
	"Operand[1]",
	"Destination"
};
/* This table needs to be synchronized with the operclass enum definition in compiler.h */
LITDEF char *oprtype_type_names[] =
{
	"NIL",		/* 0 */
	"TVAR_REF",	/* 1 */
	"TVAL_REF",	/* 2 */
	"TINT_REF",	/* 3 */
	"TVAD_REF",	/* 4 */
	"TCAD_REF",	/* 5 */
	"MLIT_REF",	/* 6 */
	"MVAR_REF",	/* 7 */
	"TRIP_REF",	/* 8 */
	"TNXT_REF",	/* 9 */
	"TJMP_REF",	/* 10 */
	"INDR_REF",	/* 11 */
	"MLAB_REF",	/* 12 */
	"ILIT_REF",	/* 13 */
	"CDLT_REF",	/* 14 */
	"TEMP_REF",	/* 15 */
	"MFUN_REF",	/* 16 */
	"MNXL_REF",	/* 17 */
	"TSIZ_REF",	/* 18 */
	"OCNT_REF",	/* 19 */
	"CDIDX_REF"	/* 20 */
};

LITDEF char *indents[11] =
{
	"",
	"  ",
	"    ",
	"      ",
	"        ",
	"          ",
	"            ",
	"              ",
	"                ",
	"                  ",
	"                    "
};

GBLREF char	*oc_tab_graphic[];
GBLREF spdesc	indr_stringpool;
GBLREF int4	sa_temps_offset[];
GBLREF int4	sa_temps[];
GBLREF triple	t_orig;			/* head of triples */

LITREF int4	sa_class_sizes[];

#define MAX_INDENT (32 * 1024)
STATICDEF char	*indent_str;
STATICDEF int	last_indent = 0;

/* Routine to dump all triples on "t_orig" chain - also callable from debugger */
void cdbg_dump_t_orig(void)
{
	triple	*ct;

	dqloop(&t_orig, exorder, ct)
	{
		PRINTF("\n ************************ Triple Start **********************\n");
		cdbg_dump_triple(ct, 0);
	}
}

/* Routine to dump all triples on "TREF(curtchain)" chain - also callable from debugger */
void cdbg_dump_curtchain(void)
{
	triple	*ct, *chain;
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	chain = TREF(curtchain);
	dqloop(chain, exorder, ct)
	{
		PRINTF("\n ************************ Triple Start **********************\n");
		cdbg_dump_triple(ct, 0);
	}
}

/* Routine to dump a single triple and its followers */
void cdbg_dump_triple(triple *dtrip, int indent)
{
	int		len;

	PRINTF("%s Triple %s [opc %d at 0x"lvaddr"]   fwdptr: 0x"lvaddr"   bkwdptr: 0x"lvaddr
	       "  srcline: %d  colmn: %d  rtaddr: %d\n",
	       cdbg_indent(indent), oc_tab_graphic[dtrip->opcode], dtrip->opcode, (long unsigned int)dtrip,
	       (long unsigned int)dtrip->exorder.fl, (long unsigned int)dtrip->exorder.bl, dtrip->src.line,
	       dtrip->src.column, dtrip->rtaddr);
	cdbg_dump_operand(indent + 1, &dtrip->operand[0], OP_0);
	cdbg_dump_operand(indent + 1, &dtrip->operand[1], OP_1);
	if (dtrip->destination.oprclass)
		cdbg_dump_operand(indent + 1, &dtrip->destination, OP_DEST);
	FFLUSH(stdout);
}

/* Routine to dump a triple that's been shrunk by shrink_trips() */
void cdbg_dump_shrunk_triple(triple *dtrip, int old_size, int new_size)
{
	PRINTF("Shrunken triple %s [0x"lvaddr"]   fwdptr: 0x"lvaddr"   bkwdptr: 0x"lvaddr"  srcline: %d  colmn: %d  rtaddr: %d\n",
	       oc_tab_graphic[dtrip->opcode], (long unsigned int)dtrip, (long unsigned int)dtrip->exorder.fl,
	       (long unsigned int)dtrip->exorder.bl, dtrip->src.line, dtrip->src.column, dtrip->rtaddr);
	PRINTF("    old size: %d  new size: %d  shrinkage: %d\n", old_size, new_size, (old_size - new_size));
	FFLUSH(stdout);
}

/* Routine to dump a triple operand (note possible recursion) */
void cdbg_dump_operand(int indent, oprtype *opr, int opnum)
{
	triple	*rtrip;
	int	offset;
        int	len;
	char	*buff;
	char 	mid[(SIZEOF(mident_fixed) * 2) + 1];	/* Sized to hold an labels name rtn.lbl */

	if (opr)
		PRINTF("%s %s  [0x"lvaddr"]  Type: %s\n", cdbg_indent(indent), oprtype_names[opnum], (long unsigned int)opr,
		       oprtype_type_names[opr->oprclass]);
	else
		PRINTF("%s ** Warning ** Null opr passed as operand\n", cdbg_indent(indent));
	if (!opr->oprclass)
	{
		FFLUSH(stdout);
		return;
	}
	/* We have a real oprclass, dump it's info */
	switch(opr->oprclass)
	{
		case TVAR_REF:
			PRINTF("%s  Temporary variable index %d\n", cdbg_indent(indent), opr->oprval.temp);
			break;
		case TCAD_REF:
		case TVAD_REF:
			PRINTF("%s  %s reference - whatever it means: value is %d\n", cdbg_indent(indent),
			       ((TCAD_REF == opr->oprclass) ? "TCAD_REF" : "TVAD_REF"), opr->oprval.temp);
			break;
		case MVAR_REF:
			if (opr->oprval.vref)
			{
				PRINTF("%s   LS vref: 0x"lvaddr"  RS vref: 0x"lvaddr"  index: %d  varname: %s  last triple: "
				       "0x"lvaddr"\n",
				       cdbg_indent(indent),(long unsigned int)opr->oprval.vref->lson,
				       (long unsigned int)opr->oprval.vref->rson, opr->oprval.vref->mvidx,
				       cdbg_makstr(opr->oprval.vref->mvname.addr, &buff, opr->oprval.vref->mvname.len),
				       (long unsigned int)opr->oprval.vref->last_fetch);
				free(buff);	/* allocated by cdbg_makstr */
			}
			else
				PRINTF("%s   ** Warning ** oprval.vref is NULL\n", cdbg_indent(indent));
			break;
		case TINT_REF:
		case TVAL_REF:
			offset = sa_temps_offset[opr->oprclass];
			offset -= (sa_temps[opr->oprclass] - opr->oprval.temp) * sa_class_sizes[opr->oprclass];
			PRINTF("%s   temp index: %d  offset: 0x%08x\n", cdbg_indent(indent), opr->oprval.temp, offset);
			break;
		case ILIT_REF:
			PRINTF("%s   ilit value: %d [0x%08x]\n", cdbg_indent(indent), opr->oprval.ilit, opr->oprval.ilit);
			break;
		case MLIT_REF:
			if (opr->oprval.mlit)
				PRINTF("%s   lit-ref fwdptr: 0x"lvaddr"  bkwdptr: 0x"lvaddr"  rtaddr: 0x"lvaddr"\n",
				       cdbg_indent(indent), (long unsigned int)opr->oprval.mlit->que.fl,
				       (long unsigned int)opr->oprval.mlit->que.bl, opr->oprval.mlit->rt_addr);
			else
				PRINTF("%s   ** Warning ** oprval.mlit is NULL\n", cdbg_indent(indent));
			cdbg_dump_mval(indent, &opr->oprval.mlit->v);
			break;
		case TJMP_REF:
			if (opr->oprval.tref)
				PRINTF("%s   tjmp-ref jump list ptr: 0x"lvaddr"\n", cdbg_indent(indent),
						(long unsigned int)&opr->oprval.tref->jmplist);
			else
				PRINTF("%s   ** Warning ** oprval.tref is NULL\n", cdbg_indent(indent));
			break;
		case TRIP_REF:
			rtrip = opr->oprval.tref;
			PRINTF("%s   Trip reference:\n", cdbg_indent(indent));
			cdbg_dump_triple(rtrip, indent + 1);
			break;
		case INDR_REF:
			cdbg_dump_operand(indent, opr->oprval.indr, opnum);
			break;
		case TSIZ_REF:
			if (opr->oprval.tsize)
				PRINTF("%s   triple at 0x"lvaddr" has size %d\n", cdbg_indent(indent),
						(long unsigned int)opr->oprval.tsize->ct, opr->oprval.tsize->size);
			else
				PRINTF("%s   ** Warning ** oprval.tsize is NULL\n", cdbg_indent(indent));
			break;
		case OCNT_REF:
			PRINTF("%s   offset from call to next triple: %d\n", cdbg_indent(indent), opr->oprval.offset);
			break;
		case MLAB_REF:
		case MFUN_REF:
			if (opr->oprval.lab)
			{
				len = opr->oprval.lab->mvname.len;
				memcpy(mid, opr->oprval.lab->mvname.addr, len);
				mid[len] = '\0';
				PRINTF("%s   ref type: %s  mlabel name: %s\n", cdbg_indent(indent),
				       oprtype_type_names[opr->oprclass], mid);
			} else
				PRINTF("%s   ref type: %s  ** Warning ** oprval.lab is NULL\n", cdbg_indent(indent),
				       oprtype_type_names[opr->oprclass]);
			break;
		case CDLT_REF:
			if (opr->oprval.cdlt)
			{
				len = opr->oprval.cdlt->len;
				memcpy(mid, opr->oprval.cdlt->addr, len);
				mid[len] = '\0';
				PRINTF("%s   cdlt-ref mstr->%s", cdbg_indent(indent), mid);
			} else
				PRINTF("%s   ref type: %s  ** Warning ** oprval.cdlt is NULL\n", cdbg_indent(indent),
				       oprtype_type_names[opr->oprclass]);
			break;
		case CDIDX_REF:
			if (opr->oprval.cdidx)
			{
				len = opr->oprval.cdidx->len;
				memcpy(mid, opr->oprval.cdidx->addr, len);
				mid[len] = '\0';
				PRINTF("%s   cdidx-ref mstr->%s", cdbg_indent(indent), mid);
			} else
				PRINTF("%s   ref type: %s  ** Warning ** oprval.cdidx is NULL\n", cdbg_indent(indent),
				       oprtype_type_names[opr->oprclass]);
			break;
		default:
			PRINTF("%s   %s bogus reference\n", cdbg_indent(indent), oprtype_type_names[opr->oprclass]);
	}
	FFLUSH(stdout);
}

/* Routine to dump a literal mval - note strings that either aren't setup completely yet or contain $ZCHAR() type
 * data can come out as garbage. Improvement would be to print value in $ZWRITE() format.
 */
void cdbg_dump_mval(int indent, mval *mv)
{
	boolean_t	first;
	double		mvf;
	int4		mvd;

	PRINTF("%s   Type: 0x%1x  (", cdbg_indent(indent), mv->mvtype);
	first = TRUE;
	if (mv->mvtype & MV_NM)
	{
		PRINTF("Number");
		first = FALSE;
	}
	if (mv->mvtype & MV_INT)
	{
		if (!first)
			PRINTF(", ");
		PRINTF("Integer");
		first = FALSE;
	}
	if (mv->mvtype & MV_STR)
	{
		if (!first)
			PRINTF(", ");
		PRINTF("String");
		FFLUSH(stdout);
		first = FALSE;
	}
	if (first)
	{
		PRINTF("Undefined MVAL)\n");
		return;
	}
	PRINTF(")  Sign: %d  Exp: %d\n", mv->sgn, mv->e);
	if (mv->mvtype & MV_NUM_MASK)
	{
		if (mv->mvtype & MV_INT)
		{
			mvd = mval2i(mv);
			PRINTF("%s   Integer value: %d\n", cdbg_indent(indent), mvd);
		} else
		{
			mvf = mval2double(mv);
			PRINTF("%s   Double value: %f\n", cdbg_indent(indent), mvf);
		}
	}
	if (mv->mvtype & MV_STR)
	{
		if (!mv->str.len)
			PRINTF("%s   String value: <null value>\n", cdbg_indent(indent));
		else
			cdbg_dump_mstr(indent, &mv->str);
	}
	FFLUSH(stdout);
}

/* Dump value of a given mstr. Assumes length is non-zero */
void cdbg_dump_mstr(int indent, mstr *ms)
{
	unsigned char	*buffer, *strp;
	int		len;
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	len = ms->len;
	strp = (unsigned char *)ms->addr;
#	if defined(USHBIN_SUPPORTED) || defined(VMS)
	/* In shared binary mode, shrink_trips is called after indir_lits() changes the addresses
	 * in the mvals to offsets. De-offset them if they don't point into the (indirect)
	 * stringpool. This *ONLY* happens during an indirect compilation.
	 */
	assert(TREF(compile_time) || indr_stringpool.base <= indr_stringpool.free);
	if (!TREF(compile_time) && strp < indr_stringpool.base)
		strp += (UINTPTR_T)(indr_stringpool.base - SIZEOF(ihdtyp) - PADLEN(SIZEOF(ihdtyp), NATIVE_WSIZE));
#	endif
	buffer = malloc(len + 1);
	memcpy(buffer, strp, len);
	buffer[len] = '\0';
	PRINTF("%s   String value: %s\n", cdbg_indent(indent), buffer);
	FFLUSH(stdout);
	free(buffer);
}

/* Provide string to do indenting of formatted output */
char *cdbg_indent(int indent)
{
	if (10 >= indent)
		return (char *)indents[indent];
	if (NULL == indent_str)
		indent_str = malloc(MAX_INDENT);
	if (MAX_INDENT < (indent * 2))
	{
		FFLUSH(stdout);
		assertpro(MAX_INDENT < (indent * 2));
	}
	if (indent > last_indent)
		memset(indent_str, ' ', indent * 2);
	indent_str[indent * 2] = 0;
	last_indent = indent;
	return indent_str;
}

/* Make a given addr/len string into a null terminate string */
char *cdbg_makstr(char *str, char **buf, int len)
{
	*buf = malloc(len + 1);
	memcpy(*buf, str, len);
	(*buf)[len] = '\0';
	return *buf;
}
