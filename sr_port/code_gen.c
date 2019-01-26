/****************************************************************
 *								*
 * Copyright (c) 2001-2016 Fidelity National Information	*
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

#include "compiler.h"
#include "opcode.h"
#include "mdq.h"
#include "cgp.h"
#include "cmd_qlf.h"
#include "obj_file.h"
#include "list_file.h"
#include <emit_code.h>
#include "dumptable.h"

LITREF	octabstruct	oc_tab[];	/* op-code table */
GBLREF	triple		t_orig;		/* head of triples */
GBLREF	char		cg_phase;	/* code generation phase */
GBLREF	command_qualifier	cmd_qlf;
GBLREF	int4		curr_addr;	/* current address */
GBLREF	src_line_struct	src_head;
GBLREF	short		source_line;
GBLREF int		source_column;
GBLREF	int4		pending_errtriplecode;	/* if non-zero contains the error code to invoke ins_errtriple with */

void	code_gen(void)
{
	int4		old_line, pad_len;
	src_line_struct	*sl;
	triple		*ct;	/* current triple */
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	if (CGP_ASSEMBLY == cg_phase)
	{
		curr_addr = t_orig.exorder.fl->rtaddr;
		old_line = -1;
	}
	assert(0 == pending_errtriplecode);	/* we should never have a pending ins_errtriple at this point */
	assert(&t_orig == TREF(curtchain));	/* curtchain should still be pointing to what it was originally */
	DEBUG_ONLY(chktchain(&t_orig));	/* if this assert fails, then recompile with DEBUG_TRIPLES to catch the issue sooner */
	dqloop(&t_orig, exorder, ct)
	{
		if (CGP_APPROX_ADDR == cg_phase)
			ct->rtaddr = curr_addr;
		else if (CGP_ASSEMBLY == cg_phase)
		{
			if (ct->src.line != old_line && (cmd_qlf.qlf & (CQ_LIST | CQ_CROSS_REFERENCE | CQ_EMBED_SOURCE)))
			{
				list_line("");
				dqloop(&src_head, que, sl)
				{
					if (sl->line > ct->src.line)
						break;
					assert(sl->str.len == STRLEN(sl->str.addr));
					NEWLINE_TO_NULL(sl->str.addr[sl->str.len - 1]);
					list_line_number();
					list_line(sl->str.addr);
				}
				/* Delete traversed lines, so we don't list them again during subsequent iters of the outer loop */
				dqdelchain(&src_head, sl, que);
				old_line = ct->src.line;
			}
		}
		source_line = ct->src.line;
		source_column = ct->src.column;
		if (!(oc_tab[ct->opcode].octype & OCT_CGSKIP))
			trip_gen(ct);
	}/* dqloop */
#ifdef	_AIX
	emit_epilog();
#endif
	/* The code section needs to be padded so the next section (variable name table) can be optimally aligned
	   for use by the hashing functions (ex use 8 byte loads on alpha requires 8 byte alignment). We compute the
	   pad length and record it and add it to the code size. Later when the code is optimized, the pad length
	   will be subtracted back out, rechecked for padding and an appropriate pad length recomputed.
	*/
	if (CGP_APPROX_ADDR == cg_phase)
		TREF(codegen_padlen) = PADLEN(curr_addr, SECTION_ALIGN_BOUNDARY);	/* Length to pad to align next section */
	if (TREF(codegen_padlen))
	{
		assert(STR_LIT_LEN(PADCHARS) >= TREF(codegen_padlen));
		if (CGP_MACHINE == cg_phase)
			emit_immed(PADCHARS, TREF(codegen_padlen));			/* Pad out with extraneous info */
		else
			curr_addr += TREF(codegen_padlen);
	}
	if (CGP_ASSEMBLY == cg_phase)
		dumptable();
}/* code_gen */
