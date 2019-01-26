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

#include "gtm_string.h"

#include "compiler.h"
#include "opcode.h"
#include "cmd_qlf.h"
#include "mdq.h"
#include "cgp.h"
#include "error.h"
#include "mmemory.h"
#include "stringpool.h"
#include "list_file.h"
#include "source_file.h"
#include "lb_init.h"
#include "reinit_externs.h"
#include "comp_esc.h"
#include "resolve_blocks.h"
#include "hashtab_str.h"
#include "rtn_src_chksum.h"

#define HOPELESS_COMPILE 128

GBLREF short int source_line;
GBLREF int	source_column;

GBLREF unsigned char		source_file_name[];
GBLREF src_line_struct 		src_head;
GBLREF triple			t_orig, *curr_fetch_trip, *curr_fetch_opr;
GBLREF int4			curr_fetch_count;
GBLREF command_qualifier	cmd_qlf;
GBLREF int			mlmax;
GBLREF mline			mline_root;
GBLREF char			cg_phase;	/* code generation phase */
GBLREF boolean_t		mstr_native_align, save_mstr_native_align;
GBLREF hash_table_str		*complits_hashtab;

LITDEF char compile_terminated[] = "COMPILATION TERMINATED DUE TO EXCESS ERRORS";

boolean_t compiler_startup(void)
{
#ifdef DEBUG
	void			dumpall();
#endif
	boolean_t		compile_w_err, need_source_lines, use_src_queue, creating_list_file;
	unsigned char		err_buf[45];
	unsigned char 		*cp, *cp2;
	int			errknt;
	int4			n;
	uint4			line_count, total_source_len;
	mlabel			*null_lab;
	src_line_struct		*sl;
	mident			null_mident;
	gtm_rtn_src_chksum_ctx	checksum_ctx;
	mstr			str;
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	/* Although we have an invocation of compiler cleanups at the end of this module, there exist ways to avoid this
	 * cleanup by working in direct mode, getting certain types of errors combined with an argumentless ZGOTO that unwinds
	 * pretty much everything that can bypass that cleanup. So do a quick check if it is needed and if so, git-r-done
	 * (test is part of the macro invocation). Note this is the easiest place to make this check rather than complicating
	 * error handling to provide a similar effect.
	 */
	COMPILE_HASHTAB_CLEANUP;
	reinit_externs();
	memset(&null_mident, 0, SIZEOF(null_mident));
	ESTABLISH_RET(compiler_ch, FALSE);
	/* Since the stringpool alignment is solely based on mstr_native_align, we need to initialize it based
	 * on the ALIGN_STRINGS qualifier so that all strings in the literal text pool are aligned.
	 * However, when a module is compiled at runtime, we need to preserve the existing runtime setting
	 * (that was initialized at GT.M startup) once the compilation is done.  save_mstr_native_align is used for
	 * this purpose. */
	save_mstr_native_align = mstr_native_align;
	/* mstr_native_align = (cmd_qlf.qlf & CQ_ALIGN_STRINGS) ? TRUE : FALSE; */
	mstr_native_align = FALSE; /* TODO: remove this line and  uncomment the above line */
	cg_phase = CGP_NOSTATE;
	TREF(source_error_found) = errknt = 0;
	if (!open_source_file())
	{
		mstr_native_align = save_mstr_native_align;
		REVERT;
		return FALSE;
	}
	rtn_src_chksum_init(&checksum_ctx);
	cg_phase = CGP_PARSE;
	creating_list_file = (cmd_qlf.qlf & CQ_LIST) || (cmd_qlf.qlf & CQ_CROSS_REFERENCE);
	need_source_lines = (cmd_qlf.qlf & CQ_EMBED_SOURCE) || creating_list_file;
	use_src_queue = (cmd_qlf.qlf & CQ_EMBED_SOURCE) || (creating_list_file && (cmd_qlf.qlf & CQ_MACHINE_CODE));
	dqinit(&src_head, que);
	if (creating_list_file)
		open_list_file();
	if (cmd_qlf.qlf & CQ_CE_PREPROCESS)
		open_ceprep_file();
	tripinit();
	null_lab = get_mladdr(&null_mident);
	null_lab->ml = &mline_root;
	mlmax++;
	curr_fetch_trip = curr_fetch_opr = newtriple(OC_LINEFETCH);
	curr_fetch_count = 0;
	TREF(code_generated) = FALSE;
	line_count = 1;
	total_source_len = 0;
	for (source_line = 1;  errknt <= HOPELESS_COMPILE;  source_line++)
	{
		if (-1 == (n = read_source_file()))
			break;
		rtn_src_chksum_line(&checksum_ctx, (TREF(source_buffer)).addr, n);
		/* Save the source lines; a check later determines whether to include them in the object file */
		/* Accumulate list of M source lines */
		sl = (src_line_struct *)mcalloc(SIZEOF(src_line_struct));
		dqrins(&src_head, que, sl);
		sl->str.addr = mcalloc(n + 1);		/* +1 for zero termination */
		sl->str.len = n;
		sl->line = source_line;
		memcpy(sl->str.addr, (TREF(source_buffer)).addr, n + 1);
		total_source_len += n;
		cp = (unsigned char *)((TREF(source_buffer)).addr + n - 1);
		NEWLINE_TO_NULL(*cp); /* avoid SPOREOL errors due to trailing newlines */
		if (need_source_lines && creating_list_file && !(cmd_qlf.qlf & CQ_MACHINE_CODE))
		{	/* list now. for machine_code we intersperse machine code and M code, thus can't list M code yet */
			list_line_number();
			list_line((TREF(source_buffer)).addr);
		}
		TREF(source_error_found) = 0;
		lb_init();
		if (cmd_qlf.qlf & CQ_CE_PREPROCESS)
			put_ceprep_line();
		if (!line(&line_count))
		{
			assert(TREF(source_error_found));
			errknt++;
		}
	}
	rtn_src_chksum_digest(&checksum_ctx);
	close_source_file();
	if (cmd_qlf.qlf & CQ_CE_PREPROCESS)
		close_ceprep_file();
	cg_phase = CGP_RESOLVE;
	if (t_orig.exorder.fl == &t_orig)	/* if no lines in routine, set up line 0 */
		newtriple(OC_LINESTART);
	newtriple(OC_RET);			/* always provide a default QUIT */
	mline_root.externalentry = t_orig.exorder.fl;
	INVOKE_STP_GCOL(0);
	/* The above invocation of stp_gcol with a parameter of 0 is a critical part of compilation
	 * (both routine compilations and indirect dynamic compilations). This collapses the indirect
	 * (compilation) stringpool so that only the literals are left. This stringpool is then written
	 * out to the compiled object as the literal pool for that compilation. Temporary stringpool
	 * use for conversions or whatever are eliminated. Note the path is different in stp_gcol for
	 * the indirect stringpool which is only used during compilations.
	 */
	if (cmd_qlf.qlf & CQ_EMBED_SOURCE)
	{	/* Append source text to text pool */
		ENSURE_STP_FREE_SPACE(total_source_len);
		DBG_MARK_STRINGPOOL_UNEXPANDABLE;
		TREF(routine_source_offset) = (uint4)(stringpool.free - stringpool.base);
		dqloop(&src_head, que, sl)
		{
			str = sl->str;
			s2pool(&str); /* changes str.addr, points it into stringpool */
		}
		DBG_MARK_STRINGPOOL_EXPANDABLE;
	}
	start_fetches(OC_NOOP);
	resolve_blocks();
	errknt = resolve_ref(errknt);
	compile_w_err = (errknt <= HOPELESS_COMPILE && (cmd_qlf.qlf & CQ_IGNORE));
	if (cmd_qlf.qlf & CQ_LIST || cmd_qlf.qlf & CQ_CROSS_REFERENCE)
	{
		list_line("");
		if (errknt)
			cp = i2asc(err_buf, errknt);
		else
		{
			cp = err_buf;
			*cp++ = 'n';
			*cp++ = 'o';
		}
		memcpy(cp, " error", SIZEOF(" error"));
		cp += SIZEOF(" error") - 1;
		if (1 != errknt)
			*cp++ = 's';
		*cp = 0;
		list_line((char *)err_buf);
		if (errknt > HOPELESS_COMPILE)
			list_line((char *)compile_terminated);
		if (cmd_qlf.qlf & CQ_MACHINE_CODE && compile_w_err)
			list_head(1);
	}
	if ((!errknt || compile_w_err) && (cmd_qlf.qlf & CQ_OBJECT || cmd_qlf.qlf & CQ_MACHINE_CODE))
	{
		obj_code(line_count, &checksum_ctx);
		cg_phase = CGP_FINI;
	}
	if (cmd_qlf.qlf & CQ_LIST || cmd_qlf.qlf & CQ_CROSS_REFERENCE)
	{
		list_cmd();
		close_list_file();
	}
	COMPILE_HASHTAB_CLEANUP;
	reinit_externs();
	mstr_native_align = save_mstr_native_align;
	REVERT;
	return errknt ? TRUE : FALSE;
}
