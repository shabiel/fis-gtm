/****************************************************************
 *								*
 * Copyright (c) 2001-2017 Fidelity National Information	*
 * Services, Inc. and/or its subsidiaries. All rights reserved.	*
 *								*
 * Copyright (c) 2017-2018 YottaDB LLC. and/or its subsidiaries.*
 * All rights reserved.						*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#ifndef OP_INCLUDED
#define OP_INCLUDED

#include "op_tstart.h"	/* for "op_tstart" prototype */
#include "mdef.h"       /* for CYGWIN64_ABI */

#ifdef VMS
/* Define a TWO-argument VMS_ONLY macro (first argument is empty string but is needed because of the VMS-only , that follows) */
#define	UNIX1_VMS2(X,Y)	X, Y
#else
#define	UNIX1_VMS2(X,Y)	X
#endif

void CYGWIN64_ABI	op_add(mval *u, mval *v, mval *s);
void CYGWIN64_ABI	add_mvals(mval *u, mval *v, int subtraction, mval *result);	/* function defined in op_add.c */
void CYGWIN64_ABI	op_bindparm(UNIX_ONLY_COMMA(int frmc) int frmp_arg, ...);
void CYGWIN64_ABI	op_break(void);
void CYGWIN64_ABI	op_cat(UNIX_ONLY_COMMA(int srcargs) mval *dst, ...);
void CYGWIN64_ABI	op_close(mval *v, mval *p);
void CYGWIN64_ABI	op_commarg(mval *v, unsigned char argcode);
int CYGWIN64_ABI	op_currhd(void);
void CYGWIN64_ABI	op_cvtparm(int iocode, mval *src, mval *dst);
int CYGWIN64_ABI	op_decrlock(mval *timeout);
void CYGWIN64_ABI	op_div(mval *u, mval *v, mval *q);
void CYGWIN64_ABI	op_dmode(void);
void CYGWIN64_ABI	op_dt_false(void);
int CYGWIN64_ABI	op_dt_get(void);
void CYGWIN64_ABI	op_dt_store(int truth_value);
void CYGWIN64_ABI	op_dt_true(void);
void CYGWIN64_ABI	op_exfunret(mval *retval);
void CYGWIN64_ABI	op_exfunretals(mval *retval);
void CYGWIN64_ABI	op_exp(mval *u, mval *v, mval *p);
/*	op_fetch currently does not exist. Instead gtm_fetch is the name (should be renamed to op_fetch to keep naming scheme) */
void CYGWIN64_ABI	gtm_fetch(UNIX_ONLY_COMMA(unsigned int cnt_arg) unsigned int indxarg, ...);
int  CYGWIN64_ABI	op_fetchintrrpt(); /* CYGWIN X64 NOTE: This is assembly code */
void CYGWIN64_ABI	op_fgnlookup(void);
void CYGWIN64_ABI	op_fnascii(int4 num, mval *in, mval *out);
void CYGWIN64_ABI	op_fnchar(UNIX_ONLY_COMMA(int cnt) mval *dst, ...);
void CYGWIN64_ABI	op_fnextract(int last, int first, mval *src, mval *dest);
void CYGWIN64_ABI	op_fnfgncal(uint4 n_mvals, mval *dst, mval *package, mval *extref, uint4 mask, int4 argcnt, ...);
int4 CYGWIN64_ABI	op_fnfind(mval *src, mval *del, mint first, mval *dst);
void CYGWIN64_ABI	op_fnfnumber(mval *src, mval *fmt, boolean_t use_fract, int fract, mval *dst);
void CYGWIN64_ABI	op_fnget1(mval *src, mval *dst);
void CYGWIN64_ABI	op_fnget2(mval *src, mval *def, mval *dst);
void CYGWIN64_ABI	op_fngetdvi(mval *device, mval *keyword, mval *ret);
void CYGWIN64_ABI	op_fngetjpi(mint jpid, mval *kwd, mval *ret);
void CYGWIN64_ABI	op_fngetlki(mval *lkid_mval, mval *keyword, mval *ret);
void CYGWIN64_ABI	op_fngetsyi(mval *keyword, mval *node, mval *ret);
void CYGWIN64_ABI	op_fngvget(mval *dst);
void CYGWIN64_ABI	op_fngvget1(mval *dst);
void CYGWIN64_ABI	op_fnj2(mval *src, int len, mval *dst);
void CYGWIN64_ABI	op_fnj3(mval *src, int width, int fract, mval *dst);
void CYGWIN64_ABI	op_fnlength(mval *a1, mval *a0);
void CYGWIN64_ABI	op_fnlvname(mval *src, boolean_t return_undef_alias, mval *dst);
void CYGWIN64_ABI	op_fnlvnameo2(mval *src, mval *dst, mval *direct);
void CYGWIN64_ABI	op_fnlvprvname(mval *src, mval *dst);
void CYGWIN64_ABI	op_fnname(UNIX_ONLY_COMMA(int sub_count) mval *finaldst, ...);
void CYGWIN64_ABI	op_fnp1(mval *src, int del, int trgpcidx, UNIX1_VMS2(mval *dst, boolean_t srcisliteral));
void CYGWIN64_ABI	op_fnpiece(mval *src, mval *del, int first, int last, UNIX1_VMS2(mval *dst, boolean_t srcisliteral));
void CYGWIN64_ABI	op_fnpopulation(mval *arg1, mval *arg2, mval *dst);
void CYGWIN64_ABI	op_fnqlength(mval *name, mval *subscripts);
void CYGWIN64_ABI	op_fnqsubscript(mval *name, int seq, mval *subscript);
void CYGWIN64_ABI	op_fnquery(UNIX_ONLY_COMMA(int sbscnt) mval *dst, ...);
void CYGWIN64_ABI	op_fnquery_va(int sbscnt, mval *dst, va_list var);
void CYGWIN64_ABI	op_fnreversequery(UNIX_ONLY_COMMA(int sbscnt) mval *dst, ...);
void CYGWIN64_ABI	op_fnreversequery_va(int sbscnt, mval *dst, va_list var);
void CYGWIN64_ABI	op_fnrandom(int4 interval, mval *ret);
void CYGWIN64_ABI	op_fnreverse(mval *src, mval *dst);
void CYGWIN64_ABI	op_fnstack1(int level, mval *result);
void CYGWIN64_ABI	op_fnstack2(int level, mval *info, mval *result);
void CYGWIN64_ABI	op_fntext(mval *label, int int_exp, mval *rtn, mval *ret);
void CYGWIN64_ABI	op_fntranslate(mval *src, mval *in_str, mval *out_str, mval *dst);
void CYGWIN64_ABI	op_fnview(UNIX_ONLY_COMMA(int numarg) mval *dst, ...);
void CYGWIN64_ABI	op_fnzascii(int4 num, mval *in, mval *out);
void CYGWIN64_ABI	op_fnzbitand(mval *dst, mval *bitstr1, mval *bitstr2);
void CYGWIN64_ABI	op_fnzbitcoun(mval *dst, mval *bitstr);
void CYGWIN64_ABI	op_fnzbitfind(mval *dst, mval *bitstr, int truthval, int pos);
void CYGWIN64_ABI	op_fnzbitget(mval *dst, mval *bitstr, int pos);
void CYGWIN64_ABI	op_fnzbitlen(mval *dst, mval *bitstr);
void CYGWIN64_ABI	op_fnzbitnot(mval *dst, mval *bitstr);
void CYGWIN64_ABI	op_fnzbitor(mval *dst, mval *bitstr1, mval *bitstr2);
void CYGWIN64_ABI	op_fnzbitset(mval *dst, mval *bitstr, int pos, int truthval);
void CYGWIN64_ABI	op_fnzbitstr(mval *bitstr, int size, int truthval);
void CYGWIN64_ABI	op_fnzbitxor(mval *dst, mval *bitstr1, mval *bitstr2);
void CYGWIN64_ABI	op_fnzcall(void);	/* stub only */
void CYGWIN64_ABI	op_fnzchar(UNIX_ONLY_COMMA(int cnt) mval *dst, ...);
void CYGWIN64_ABI	op_fnzconvert2(mval *str, mval *kase, mval *dst);
void CYGWIN64_ABI	op_fnzconvert3(mval *str, mval *from_chset, mval *to_chset, mval *dst);
void CYGWIN64_ABI	op_fnzcollate(mval *src, int col, int reverse, mval *dst);
void CYGWIN64_ABI	op_fnzdate(mval *src, mval *fmt, mval *mo_str, mval *day_str, mval *dst);
void CYGWIN64_ABI	op_fnzdebug(mval *cmd, mval *dst);
void CYGWIN64_ABI	op_fnzechar(UNIX_ONLY_COMMA(int cnt) mval *dst, ...);
void CYGWIN64_ABI	op_fnzextract(int last, int first, mval *src, mval *dest); /* CYGWIN X64 NOTE: THIS IS ASSEMBLY! */
void CYGWIN64_ABI	op_fnzfile(mval *name, mval *key, mval *ret);
int4 CYGWIN64_ABI	op_fnzfind(mval *src, mval *del, mint first, mval *dst);
void CYGWIN64_ABI	op_fnzj2(mval *src, int len, mval *dst);
void CYGWIN64_ABI	op_fnzjobexam(mval *prelimSpec, mval *finalSpec);
void CYGWIN64_ABI	op_fnzlength(mval *a1, mval *a0);
void CYGWIN64_ABI	op_fnzlkid(mint boolex, mval *retval);
void CYGWIN64_ABI	op_fnzm(mint x, mval *v);
void CYGWIN64_ABI	op_fnzp1(mval *src, int del, int trgpcidx, UNIX1_VMS2(mval *dst, boolean_t srcisliteral));
void CYGWIN64_ABI	op_fnzparse(mval *file, mval *field, mval *def1, mval *def2, mval *type, mval *ret);
void CYGWIN64_ABI	op_fnzpeek(mval *baseaddr, int offset, int len, mval *format, mval *ret);
void CYGWIN64_ABI	op_fnzpid(mint boolexpr, mval *ret);
void CYGWIN64_ABI	op_fnzpiece(mval *src, mval *del, int first, int last, UNIX1_VMS2(mval *dst, boolean_t srcisliteral));
void CYGWIN64_ABI	op_fnzpopulation(mval *arg1, mval *arg2, mval *dst);
void CYGWIN64_ABI	op_fnzpriv(mval *prv, mval *ret);
void CYGWIN64_ABI	op_fnzqgblmod(mval *v);
void CYGWIN64_ABI	op_fnzreverse(mval *src, mval *dst);
int CYGWIN64_ABI	op_fnzsearch(mval *file, mint indx, mint mfunc, mval *ret);		/***type int added***/
void CYGWIN64_ABI	op_fnzsetprv(mval *prv, mval *ret);
void CYGWIN64_ABI	op_fnzsigproc(int processid, int signum, mval *retcode);
void CYGWIN64_ABI	op_fnzsocket(UNIX_ONLY_COMMA(int numarg) mval *dst, ...);
void CYGWIN64_ABI	op_fnzsqlexpr(mval *value, mval *target); /* does not exist */
void CYGWIN64_ABI	op_fnzsqlfield(int findex, mval *target); /* does not exist */
void CYGWIN64_ABI	op_fnzsubstr(mval *src, int start, int bytelen, mval *dest);
void CYGWIN64_ABI	op_fnzsyslog(mval *src, mval *dst);
void CYGWIN64_ABI	op_fnztranslate(mval *src, mval *in_str , mval *out_str, mval *dst);
void CYGWIN64_ABI	op_fnztrigger(mval *func, mval *arg1, mval *arg2, mval *dst);
void CYGWIN64_ABI	op_fnztrnlnm(mval *name, mval *table, int4 ind, mval *mode, mval *case_blind, mval *item, mval *ret);
void CYGWIN64_ABI	op_fnzwidth(mval *str, mval *dst);
void CYGWIN64_ABI	op_fnzwrite(boolean_t direction, mval *str, mval *dst);
void CYGWIN64_ABI	op_fnzatransform(mval *src, int col, int reverse, int forcenum, mval *dst);
int CYGWIN64_ABI	op_forchk1();    /* CYGWIN X64 NOTE: THIS IS ASSEMBLY! */
int CYGWIN64_ABI	op_forintrrpt(); /* CYGWIN X64 NOTE: THIS IS ASSEMBLY! */
int CYGWIN64_ABI	op_forloop();    /* CYGWIN X64 NOTE: THIS IS ASSEMBLY! */
void CYGWIN64_ABI	op_gvdata(mval *v);
void CYGWIN64_ABI	op_gvextnam(UNIX_ONLY_COMMA(int4 count) mval *val1, ...);
void CYGWIN64_ABI	op_gvextnam_fast(UNIX_ONLY_COMMA(int4 count) int hash_code, mval *val1, ...);
boolean_t CYGWIN64_ABI	op_gvget(mval *v);
void CYGWIN64_ABI	op_gvincr(mval *increment, mval *result);
void CYGWIN64_ABI	op_gvkill(void);
void CYGWIN64_ABI	op_gvnaked(UNIX_ONLY_COMMA(int count_arg) mval *val_arg, ...);
void CYGWIN64_ABI	op_gvnaked_fast(UNIX_ONLY_COMMA(int count_arg) int hash_code, mval *val_arg, ...);
void CYGWIN64_ABI	op_gvname(UNIX_ONLY_COMMA(int count_arg) mval *val_arg, ...);
void CYGWIN64_ABI	op_gvname_fast(UNIX_ONLY_COMMA(int count_arg) int hash_code, mval *val_arg, ...);
void CYGWIN64_ABI	op_gvnext(mval *v);
void CYGWIN64_ABI	op_gvo2(mval *dst, mval *direct);
void CYGWIN64_ABI	op_gvorder(mval *v);
void CYGWIN64_ABI	op_gvput(mval *var);
void CYGWIN64_ABI	op_gvquery(mval *v);
void CYGWIN64_ABI	op_gvreversequery(mval *v);
boolean_t CYGWIN64_ABI op_gvqueryget(mval *key, mval *val);
void CYGWIN64_ABI	op_gvq2(mval *dst, mval *direct);
void CYGWIN64_ABI	op_gvrectarg(mval *v);
void CYGWIN64_ABI	op_gvsavtarg(mval *v);
void CYGWIN64_ABI	op_gvzwithdraw(void);
void CYGWIN64_ABI	op_gvzwrite(UNIX_ONLY_COMMA(int4 count) int4 pat, ...);
void CYGWIN64_ABI	op_hang(mval *num);
void CYGWIN64_ABI	op_hardret(void);
void CYGWIN64_ABI	op_horolog(mval *s);
void CYGWIN64_ABI	op_idiv(mval *u, mval *v, mval *q);
mval CYGWIN64_ABI	*op_igetdst(void);
void CYGWIN64_ABI	op_igetsrc(mval *v);
int CYGWIN64_ABI	op_incrlock(mval *timeout);
void CYGWIN64_ABI	op_inddevparms(mval *devpsrc, int4 ok_iop_parms, mval *devpiopl);
void CYGWIN64_ABI	op_indfnname(mval *dst, mval *target, mval *value);
void CYGWIN64_ABI	op_indfnname2(mval *finaldst, mval *depthval, mval *prechomp);
void CYGWIN64_ABI	op_indfun(mval *v, mint argcode, mval *dst);
void CYGWIN64_ABI	op_indget1(uint4 indx, mval *dst);					/* Used by [SET] */
void CYGWIN64_ABI	op_indget2(mval *dst, uint4 indx);
void CYGWIN64_ABI	op_indglvn(mval *v, mval *dst);
void CYGWIN64_ABI	op_indincr(mval *dst, mval *increment, mval *target);
void CYGWIN64_ABI	op_indlvadr(mval *target);
void CYGWIN64_ABI	op_indlvarg(mval *v, mval *dst);
void CYGWIN64_ABI	op_indlvnamadr(mval *target);
void CYGWIN64_ABI	op_indmerge(mval *glvn_mv, mval *arg1_or_arg2);
void CYGWIN64_ABI	op_indmerge2(uint4 indx);
void CYGWIN64_ABI	op_indname(mval *dst, mval *target, mval *subs);
void CYGWIN64_ABI	op_indo2(mval *dst, uint4 indx, mval *value);
void CYGWIN64_ABI	op_indpat(mval *v, mval *dst);
void CYGWIN64_ABI	op_indq2(mval *dst, uint4 indx, mval *value);
void CYGWIN64_ABI	op_indrzshow(mval *s1, mval *s2);
void CYGWIN64_ABI	op_indset(mval *target, mval *value);
void CYGWIN64_ABI	op_indtext(mval *lab, mint offset, mval *rtn, mval *dst);
void CYGWIN64_ABI	op_iocontrol(UNIX_ONLY_COMMA(int4 n) mval *vparg, ...);
void CYGWIN64_ABI	op_iretmval(mval *v, mval *dst);
int CYGWIN64_ABI	op_job(int4 argcnt, ...);
void CYGWIN64_ABI	op_killaliasall(void);
void CYGWIN64_ABI	op_killall(void);
int CYGWIN64_ABI	op_linefetch(); /* ASSEMBLY */
int CYGWIN64_ABI	op_linestart(); /* ASSEMBLY */
void CYGWIN64_ABI	op_litc(mval *dst, mval *src);
void CYGWIN64_ABI	op_lkinit(void);
void CYGWIN64_ABI	op_lkname(UNIX_ONLY_COMMA(int subcnt) mval *extgbl1, ...);
int CYGWIN64_ABI	op_lock(mval *timeout);
int CYGWIN64_ABI	op_lock2(mval *timeout, unsigned char laflag);
void CYGWIN64_ABI	op_lvpatwrite(UNIX_ONLY_COMMA(int4 count) UINTPTR_T arg1, ...);
void CYGWIN64_ABI	op_lvzwrite(UNIX_ONLY_COMMA(int4 count) long arg1, ...);
/*	op_merge     : prototype defined separately in op_merge.h */
/*	op_merge_arg : prototype defined separately in op_merge.h */
int CYGWIN64_ABI	op_mprofforchk1();   /* ASSEMBLY */
int CYGWIN64_ABI	op_mproflinefetch(); /* ASSEMBLY */
int CYGWIN64_ABI	op_mproflinestart(); /* ASSEMBLY */
void CYGWIN64_ABI	op_mul(mval *u, mval *v, mval *p);
void CYGWIN64_ABI	op_newintrinsic(int intrtype);
void CYGWIN64_ABI	op_newvar(uint4 arg1);
mval CYGWIN64_ABI	*op_nullexp(void);
void CYGWIN64_ABI	op_oldvar(void);
int CYGWIN64_ABI	op_open(mval *device, mval *devparms, mval *timeout, mval *mspace);
int CYGWIN64_ABI	op_open_dummy(mval *v, mval *p, mval *timeout, mval *mspace);
int CYGWIN64_ABI	op_rdone(mval *v, mval *timeout);
int CYGWIN64_ABI	op_read(mval *v, mval *timeout);
int CYGWIN64_ABI	op_readfl(mval *v, int4 length, mval *timeout);
int CYGWIN64_ABI	op_ret(); /* does not exist */
int CYGWIN64_ABI	op_retarg(); /*ASSEMBLY*/
void CYGWIN64_ABI	op_rterror(int4 sig, boolean_t subrtn);
void CYGWIN64_ABI	op_setextract(mval *src, mval *expr, int schar, int echar, mval *dst);
void CYGWIN64_ABI	op_setp1(mval *src, int delim, mval *expr, int ind, mval *dst);
void CYGWIN64_ABI	op_setpiece(mval *src, mval *del, mval *expr, int4 first, int4 last, mval *dst);
void CYGWIN64_ABI	op_setzbrk(mval *rtn, mval *lab, int offset, mval *act, int cnt);
void CYGWIN64_ABI	op_setzextract(mval *src, mval *expr, int schar, int echar, mval *dst);
void CYGWIN64_ABI	op_setzp1(mval *src, int delim, mval *expr, int ind, mval *dst);
void CYGWIN64_ABI	op_setzpiece(mval *src, mval *del, mval *expr, int4 first, int4 last, mval *dst);
void CYGWIN64_ABI	op_sqlinddo(mstr *m_init_rtn); /* does not exist */
int CYGWIN64_ABI	op_startintrrpt(); /*ASSEMBLY*/
void CYGWIN64_ABI	op_stolitc(mval *val);
void CYGWIN64_ABI	op_sub(mval *u, mval *v, mval *s);
void CYGWIN64_ABI	op_svget(int varnum, mval *v);
void CYGWIN64_ABI	op_svput(int varnum, mval *v);
/*	op_tcommit : prototype defined separately in op_tcommit.h since it returns "enum cdb_sc" type. */
void CYGWIN64_ABI	op_trestart(int newlevel);

/* Macro to be called by C Runtime code to invoke op_trollback. Sets implicit_trollback to TRUE. Note: The interface of
 * OP_TROLLBACK macro and op_trollback function needs to be maintained in parallel.
 */
#define OP_TROLLBACK(RB_LEVELS)													\
{																\
	GBLREF	boolean_t		implicit_trollback;									\
																\
	assert(!implicit_trollback); 												\
	implicit_trollback = TRUE;												\
	op_trollback(RB_LEVELS);/*BYPASSOK*/											\
	/* Should have been reset by op_trollback at the beginning of the function entry */					\
	assert(!implicit_trollback);												\
}


void CYGWIN64_ABI	op_trollback(int rb_levels);/*BYPASSOK*/
void CYGWIN64_ABI	op_unlock(void);
void CYGWIN64_ABI	op_unwind(void);
void CYGWIN64_ABI	op_use(mval *v, mval *p);
void CYGWIN64_ABI	op_view(UNIX_ONLY_COMMA(int numarg) mval *keyword, ...);
void CYGWIN64_ABI	op_write(mval *v);
void CYGWIN64_ABI	op_wteol(int4 n);
void CYGWIN64_ABI	op_wtff(void);
void CYGWIN64_ABI	op_wtone(int c);
void CYGWIN64_ABI	op_wttab(mint x);
void CYGWIN64_ABI	op_xkill(UNIX_ONLY_COMMA(int n) mval *lvname_arg, ...);
void CYGWIN64_ABI	op_xnew(UNIX_ONLY_COMMA(unsigned int argcnt_arg) mval *s_arg, ...);
int CYGWIN64_ABI	op_zallocate(mval *timeout);
void CYGWIN64_ABI	op_zattach(mval *);
int CYGWIN64_ABI	op_zbfetch(); /* ASSEMBLY */
int CYGWIN64_ABI	op_zbstart(); /* ASSEMBLY */
void CYGWIN64_ABI	op_zcompile(mval *v, boolean_t ignore_dollar_zcompile);
void CYGWIN64_ABI	op_zcont(void);
void CYGWIN64_ABI    op_zcollate(mval *v, int c, mval *p); /* does not exist */
void CYGWIN64_ABI	op_zdealloc2(mval *timeout, UINTPTR_T auxown);
void CYGWIN64_ABI	op_zdeallocate(mval *timeout);
void CYGWIN64_ABI	op_zedit(mval *v, mval *p);
void CYGWIN64_ABI	op_zg1(int4 level);
void CYGWIN64_ABI	op_zgoto(mval *rtnname, mval *lblname, int offset, int level);
void CYGWIN64_ABI    op_zrupdate(int argcnt, ...);
void CYGWIN64_ABI	op_ztrigger(void);
void CYGWIN64_ABI	op_zhalt(int4 is_zhalt, boolean_t retcode);
void CYGWIN64_ABI	op_zhelp_xfr(mval *subject, mval *lib);
void CYGWIN64_ABI	op_zhorolog(mval *s);
void CYGWIN64_ABI	op_zlink(mval *v, mval *quals);
void CYGWIN64_ABI	op_zmess(unsigned int cnt, ...);
void CYGWIN64_ABI	op_zprevious(mval *v);
void CYGWIN64_ABI	op_zprint(mval *rtn, mval *start_label, int start_int_exp, mval *end_label, int end_int_exp);
void CYGWIN64_ABI	op_zst_break(void);
int CYGWIN64_ABI	op_zst_fet_over(); /* ASSEMBLY */
void CYGWIN64_ABI	op_zst_over(void);
int CYGWIN64_ABI	op_zst_st_over(); /* ASSEMBLY */
void CYGWIN64_ABI	op_zstep(uint4 code, mval *action);
int CYGWIN64_ABI	op_zstepfetch(); /* ASSEMBLY */
void CYGWIN64_ABI	op_zstepret(void);
int CYGWIN64_ABI	op_zstepstart(); /* ASSEMBLY */
int CYGWIN64_ABI	op_zstzb_fet_over(); /* ASSEMBLY */
int CYGWIN64_ABI	op_zstzb_st_over(); /* ASSEMBLY */
int CYGWIN64_ABI	op_zstzbfetch(); /* ASSEMBLY */
int CYGWIN64_ABI	op_zstzbstart(); /* ASSEMBLY */
void CYGWIN64_ABI	op_zsystem(mval *v);
void CYGWIN64_ABI	op_ztcommit(int4 n);
void CYGWIN64_ABI	op_ztstart(void);
int CYGWIN64_ABI	opp_ret(); /* ASSEMBLY */
int CYGWIN64_ABI	opp_zst_over_ret(); /* ASSEMBLY */
int CYGWIN64_ABI	opp_zst_over_retarg(); /* ASSEMBLY */
int CYGWIN64_ABI	opp_zstepret(); /* ASSEMBLY */
int CYGWIN64_ABI	opp_zstepretarg(); /* ASSEMBLY */
void CYGWIN64_ABI	op_zut(mval *s);
void CYGWIN64_ABI	op_zwritesvn(int svn);
void CYGWIN64_ABI	op_zst_over_retarg_helper(void);
void CYGWIN64_ABI	op_zstepretarg_helper(void);
#endif
