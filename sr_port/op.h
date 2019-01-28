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

#ifdef VMS
/* Define a TWO-argument VMS_ONLY macro (first argument is empty string but is needed because of the VMS-only , that follows) */
#define	UNIX1_VMS2(X,Y)	X, Y
#else
#define	UNIX1_VMS2(X,Y)	X
#endif

void __attribute__ ((sysv_abi))	op_add(mval *u, mval *v, mval *s);
void __attribute__ ((sysv_abi))	add_mvals(mval *u, mval *v, int subtraction, mval *result);	/* function defined in op_add.c */
void __attribute__ ((sysv_abi))	op_bindparm(UNIX_ONLY_COMMA(int frmc) int frmp_arg, ...);
void __attribute__ ((sysv_abi))	op_break(void);
void __attribute__ ((sysv_abi))	op_cat(UNIX_ONLY_COMMA(int srcargs) mval *dst, ...);
void __attribute__ ((sysv_abi))	op_close(mval *v, mval *p);
void __attribute__ ((sysv_abi))	op_commarg(mval *v, unsigned char argcode);
int __attribute__ ((sysv_abi))	op_currhd(void);
void __attribute__ ((sysv_abi))	op_cvtparm(int iocode, mval *src, mval *dst);
int __attribute__ ((sysv_abi))	op_decrlock(mval *timeout);
void __attribute__ ((sysv_abi))	op_div(mval *u, mval *v, mval *q);
void __attribute__ ((sysv_abi))	op_dmode(void);
void __attribute__ ((sysv_abi))	op_dt_false(void);
int __attribute__ ((sysv_abi))	op_dt_get(void);
void __attribute__ ((sysv_abi))	op_dt_store(int truth_value);
void __attribute__ ((sysv_abi))	op_dt_true(void);
void __attribute__ ((sysv_abi))	op_exfunret(mval *retval);
void __attribute__ ((sysv_abi))	op_exfunretals(mval *retval);
void __attribute__ ((sysv_abi))	op_exp(mval *u, mval *v, mval *p);
/*	op_fetch currently does not exist. Instead gtm_fetch is the name (should be renamed to op_fetch to keep naming scheme) */
void __attribute__ ((sysv_abi))	gtm_fetch(UNIX_ONLY_COMMA(unsigned int cnt_arg) unsigned int indxarg, ...);
int	op_fetchintrrpt();
void __attribute__ ((sysv_abi))	op_fgnlookup(void);
void __attribute__ ((sysv_abi))	op_fnascii(int4 num, mval *in, mval *out);
void __attribute__ ((sysv_abi))	op_fnchar(UNIX_ONLY_COMMA(int cnt) mval *dst, ...);
void __attribute__ ((sysv_abi))	op_fnextract(int last, int first, mval *src, mval *dest);
void __attribute__ ((sysv_abi))	op_fnfgncal(uint4 n_mvals, mval *dst, mval *package, mval *extref, uint4 mask, int4 argcnt, ...);
int4 __attribute__ ((sysv_abi))	op_fnfind(mval *src, mval *del, mint first, mval *dst);
void __attribute__ ((sysv_abi))	op_fnfnumber(mval *src, mval *fmt, boolean_t use_fract, int fract, mval *dst);
void __attribute__ ((sysv_abi))	op_fnget1(mval *src, mval *dst);
void __attribute__ ((sysv_abi))	op_fnget2(mval *src, mval *def, mval *dst);
void __attribute__ ((sysv_abi))	op_fngetdvi(mval *device, mval *keyword, mval *ret);
void __attribute__ ((sysv_abi))	op_fngetjpi(mint jpid, mval *kwd, mval *ret);
void __attribute__ ((sysv_abi))	op_fngetlki(mval *lkid_mval, mval *keyword, mval *ret);
void __attribute__ ((sysv_abi))	op_fngetsyi(mval *keyword, mval *node, mval *ret);
void __attribute__ ((sysv_abi))	op_fngvget(mval *dst);
void __attribute__ ((sysv_abi))	op_fngvget1(mval *dst);
void __attribute__ ((sysv_abi))	op_fnj2(mval *src, int len, mval *dst);
void __attribute__ ((sysv_abi))	op_fnj3(mval *src, int width, int fract, mval *dst);
void __attribute__ ((sysv_abi))	op_fnlength(mval *a1, mval *a0);
void __attribute__ ((sysv_abi))	op_fnlvname(mval *src, boolean_t return_undef_alias, mval *dst);
void __attribute__ ((sysv_abi))	op_fnlvnameo2(mval *src, mval *dst, mval *direct);
void __attribute__ ((sysv_abi))	op_fnlvprvname(mval *src, mval *dst);
void __attribute__ ((sysv_abi))	op_fnname(UNIX_ONLY_COMMA(int sub_count) mval *finaldst, ...);
void __attribute__ ((sysv_abi))	op_fnp1(mval *src, int del, int trgpcidx, UNIX1_VMS2(mval *dst, boolean_t srcisliteral));
void __attribute__ ((sysv_abi))	op_fnpiece(mval *src, mval *del, int first, int last, UNIX1_VMS2(mval *dst, boolean_t srcisliteral));
void __attribute__ ((sysv_abi))	op_fnpopulation(mval *arg1, mval *arg2, mval *dst);
void __attribute__ ((sysv_abi))	op_fnqlength(mval *name, mval *subscripts);
void __attribute__ ((sysv_abi))	op_fnqsubscript(mval *name, int seq, mval *subscript);
void __attribute__ ((sysv_abi))	op_fnquery(UNIX_ONLY_COMMA(int sbscnt) mval *dst, ...);
void __attribute__ ((sysv_abi))	op_fnquery_va(int sbscnt, mval *dst, va_list var);
void __attribute__ ((sysv_abi))	op_fnreversequery(UNIX_ONLY_COMMA(int sbscnt) mval *dst, ...);
void __attribute__ ((sysv_abi))	op_fnreversequery_va(int sbscnt, mval *dst, va_list var);
void __attribute__ ((sysv_abi))	op_fnrandom(int4 interval, mval *ret);
void __attribute__ ((sysv_abi))	op_fnreverse(mval *src, mval *dst);
void __attribute__ ((sysv_abi))	op_fnstack1(int level, mval *result);
void __attribute__ ((sysv_abi))	op_fnstack2(int level, mval *info, mval *result);
void __attribute__ ((sysv_abi))	op_fntext(mval *label, int int_exp, mval *rtn, mval *ret);
void __attribute__ ((sysv_abi))	op_fntranslate(mval *src, mval *in_str, mval *out_str, mval *dst);
void __attribute__ ((sysv_abi))	op_fnview(UNIX_ONLY_COMMA(int numarg) mval *dst, ...);
void __attribute__ ((sysv_abi))	op_fnzascii(int4 num, mval *in, mval *out);
void __attribute__ ((sysv_abi))	op_fnzbitand(mval *dst, mval *bitstr1, mval *bitstr2);
void __attribute__ ((sysv_abi))	op_fnzbitcoun(mval *dst, mval *bitstr);
void __attribute__ ((sysv_abi))	op_fnzbitfind(mval *dst, mval *bitstr, int truthval, int pos);
void __attribute__ ((sysv_abi))	op_fnzbitget(mval *dst, mval *bitstr, int pos);
void __attribute__ ((sysv_abi))	op_fnzbitlen(mval *dst, mval *bitstr);
void __attribute__ ((sysv_abi))	op_fnzbitnot(mval *dst, mval *bitstr);
void __attribute__ ((sysv_abi))	op_fnzbitor(mval *dst, mval *bitstr1, mval *bitstr2);
void __attribute__ ((sysv_abi))	op_fnzbitset(mval *dst, mval *bitstr, int pos, int truthval);
void __attribute__ ((sysv_abi))	op_fnzbitstr(mval *bitstr, int size, int truthval);
void __attribute__ ((sysv_abi))	op_fnzbitxor(mval *dst, mval *bitstr1, mval *bitstr2);
void __attribute__ ((sysv_abi))	op_fnzcall(void);	/* stub only */
void __attribute__ ((sysv_abi))	op_fnzchar(UNIX_ONLY_COMMA(int cnt) mval *dst, ...);
void __attribute__ ((sysv_abi))	op_fnzconvert2(mval *str, mval *kase, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzconvert3(mval *str, mval *from_chset, mval *to_chset, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzcollate(mval *src, int col, int reverse, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzdate(mval *src, mval *fmt, mval *mo_str, mval *day_str, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzdebug(mval *cmd, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzechar(UNIX_ONLY_COMMA(int cnt) mval *dst, ...);
void __attribute__ ((sysv_abi))	op_fnzextract(int last, int first, mval *src, mval *dest);
void __attribute__ ((sysv_abi))	op_fnzfile(mval *name, mval *key, mval *ret);
int4 __attribute__ ((sysv_abi))	op_fnzfind(mval *src, mval *del, mint first, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzj2(mval *src, int len, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzjobexam(mval *prelimSpec, mval *finalSpec);
void __attribute__ ((sysv_abi))	op_fnzlength(mval *a1, mval *a0);
void __attribute__ ((sysv_abi))	op_fnzlkid(mint boolex, mval *retval);
void __attribute__ ((sysv_abi))	op_fnzm(mint x, mval *v);
void __attribute__ ((sysv_abi))	op_fnzp1(mval *src, int del, int trgpcidx, UNIX1_VMS2(mval *dst, boolean_t srcisliteral));
void __attribute__ ((sysv_abi))	op_fnzparse(mval *file, mval *field, mval *def1, mval *def2, mval *type, mval *ret);
void __attribute__ ((sysv_abi))	op_fnzpeek(mval *baseaddr, int offset, int len, mval *format, mval *ret);
void __attribute__ ((sysv_abi))	op_fnzpid(mint boolexpr, mval *ret);
void __attribute__ ((sysv_abi))	op_fnzpiece(mval *src, mval *del, int first, int last, UNIX1_VMS2(mval *dst, boolean_t srcisliteral));
void __attribute__ ((sysv_abi))	op_fnzpopulation(mval *arg1, mval *arg2, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzpriv(mval *prv, mval *ret);
void __attribute__ ((sysv_abi))	op_fnzqgblmod(mval *v);
void __attribute__ ((sysv_abi))	op_fnzreverse(mval *src, mval *dst);
int __attribute__ ((sysv_abi))	op_fnzsearch(mval *file, mint indx, mint mfunc, mval *ret);		/***type int added***/
void __attribute__ ((sysv_abi))	op_fnzsetprv(mval *prv, mval *ret);
void __attribute__ ((sysv_abi))	op_fnzsigproc(int processid, int signum, mval *retcode);
void __attribute__ ((sysv_abi))	op_fnzsocket(UNIX_ONLY_COMMA(int numarg) mval *dst, ...);
void __attribute__ ((sysv_abi))	op_fnzsqlexpr(mval *value, mval *target);
void __attribute__ ((sysv_abi))	op_fnzsqlfield(int findex, mval *target);
void __attribute__ ((sysv_abi))	op_fnzsubstr(mval *src, int start, int bytelen, mval *dest);
void __attribute__ ((sysv_abi))	op_fnzsyslog(mval *src, mval *dst);
void __attribute__ ((sysv_abi))	op_fnztranslate(mval *src, mval *in_str , mval *out_str, mval *dst);
void __attribute__ ((sysv_abi))	op_fnztrigger(mval *func, mval *arg1, mval *arg2, mval *dst);
void __attribute__ ((sysv_abi))	op_fnztrnlnm(mval *name, mval *table, int4 ind, mval *mode, mval *case_blind, mval *item, mval *ret);
void __attribute__ ((sysv_abi))	op_fnztrnlnm(mval *name, mval *table, int4 ind, mval *mode, mval *case_blind, mval *item, mval *ret);
void __attribute__ ((sysv_abi))	op_fnzwidth(mval *str, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzwrite(boolean_t direction, mval *str, mval *dst);
void __attribute__ ((sysv_abi))	op_fnzatransform(mval *src, int col, int reverse, int forcenum, mval *dst);
int __attribute__ ((sysv_abi))	op_forchk1();
int __attribute__ ((sysv_abi))	op_forintrrpt();
int __attribute__ ((sysv_abi))	op_forloop();
void __attribute__ ((sysv_abi))	op_gvdata(mval *v);
void __attribute__ ((sysv_abi))	op_gvextnam(UNIX_ONLY_COMMA(int4 count) mval *val1, ...);
void __attribute__ ((sysv_abi))	op_gvextnam_fast(UNIX_ONLY_COMMA(int4 count) int hash_code, mval *val1, ...);
boolean_t __attribute__ ((sysv_abi)) op_gvget(mval *v);
void __attribute__ ((sysv_abi))	op_gvincr(mval *increment, mval *result);
void __attribute__ ((sysv_abi))	op_gvkill(void);
void __attribute__ ((sysv_abi))	op_gvnaked(UNIX_ONLY_COMMA(int count_arg) mval *val_arg, ...);
void __attribute__ ((sysv_abi))	op_gvnaked_fast(UNIX_ONLY_COMMA(int count_arg) int hash_code, mval *val_arg, ...);
void __attribute__ ((sysv_abi))	op_gvname(UNIX_ONLY_COMMA(int count_arg) mval *val_arg, ...);
void __attribute__ ((sysv_abi))	op_gvname_fast(UNIX_ONLY_COMMA(int count_arg) int hash_code, mval *val_arg, ...);
void __attribute__ ((sysv_abi))	op_gvnext(mval *v);
void __attribute__ ((sysv_abi))	op_gvo2(mval *dst, mval *direct);
void __attribute__ ((sysv_abi))	op_gvorder(mval *v);
void __attribute__ ((sysv_abi))	op_gvput(mval *var);
void __attribute__ ((sysv_abi))	op_gvquery(mval *v);
void __attribute__ ((sysv_abi))	op_gvreversequery(mval *v);
boolean_t __attribute__ ((sysv_abi)) op_gvqueryget(mval *key, mval *val);
void __attribute__ ((sysv_abi))	op_gvq2(mval *dst, mval *direct);
void __attribute__ ((sysv_abi))	op_gvrectarg(mval *v);
void __attribute__ ((sysv_abi))	op_gvsavtarg(mval *v);
void __attribute__ ((sysv_abi))	op_gvzwithdraw(void);
void __attribute__ ((sysv_abi))	op_gvzwrite(UNIX_ONLY_COMMA(int4 count) int4 pat, ...);
void __attribute__ ((sysv_abi))	op_hang(mval *num);
void __attribute__ ((sysv_abi))	op_hardret(void);
void __attribute__ ((sysv_abi))	op_horolog(mval *s);
void __attribute__ ((sysv_abi))	op_idiv(mval *u, mval *v, mval *q);
mval __attribute__ ((sysv_abi))	*op_igetdst(void);
void __attribute__ ((sysv_abi))	op_igetsrc(mval *v);
int __attribute__ ((sysv_abi))	op_incrlock(mval *timeout);
void __attribute__ ((sysv_abi))	op_inddevparms(mval *devpsrc, int4 ok_iop_parms, mval *devpiopl);
void __attribute__ ((sysv_abi))	op_indfnname(mval *dst, mval *target, mval *value);
void __attribute__ ((sysv_abi))	op_indfnname2(mval *finaldst, mval *depthval, mval *prechomp);
void __attribute__ ((sysv_abi))	op_indfun(mval *v, mint argcode, mval *dst);
void __attribute__ ((sysv_abi))	op_indget1(uint4 indx, mval *dst);					/* Used by [SET] */
void __attribute__ ((sysv_abi))	op_indget2(mval *dst, uint4 indx);
void __attribute__ ((sysv_abi))	op_indglvn(mval *v, mval *dst);
void __attribute__ ((sysv_abi))	op_indincr(mval *dst, mval *increment, mval *target);
void __attribute__ ((sysv_abi))	op_indlvadr(mval *target);
void __attribute__ ((sysv_abi))	op_indlvarg(mval *v, mval *dst);
void __attribute__ ((sysv_abi))	op_indlvnamadr(mval *target);
void __attribute__ ((sysv_abi))	op_indmerge(mval *glvn_mv, mval *arg1_or_arg2);
void __attribute__ ((sysv_abi))	op_indmerge2(uint4 indx);
void __attribute__ ((sysv_abi))	op_indname(mval *dst, mval *target, mval *subs);
void __attribute__ ((sysv_abi))	op_indo2(mval *dst, uint4 indx, mval *value);
void __attribute__ ((sysv_abi))	op_indpat(mval *v, mval *dst);
void __attribute__ ((sysv_abi))	op_indq2(mval *dst, uint4 indx, mval *value);
void __attribute__ ((sysv_abi))	op_indrzshow(mval *s1, mval *s2);
void __attribute__ ((sysv_abi))	op_indset(mval *target, mval *value);
void __attribute__ ((sysv_abi))	op_indtext(mval *lab, mint offset, mval *rtn, mval *dst);
void __attribute__ ((sysv_abi))	op_iocontrol(UNIX_ONLY_COMMA(int4 n) mval *vparg, ...);
void __attribute__ ((sysv_abi))	op_iretmval(mval *v, mval *dst);
int __attribute__ ((sysv_abi))	op_job(int4 argcnt, ...);
void __attribute__ ((sysv_abi))	op_killaliasall(void);
void __attribute__ ((sysv_abi))	op_killall(void);
void __attribute__ ((sysv_abi))	op_killall(void);
int __attribute__ ((sysv_abi))	op_linefetch();
int __attribute__ ((sysv_abi))	op_linestart();
void __attribute__ ((sysv_abi))	op_litc(mval *dst, mval *src);
void __attribute__ ((sysv_abi))	op_lkinit(void);
void __attribute__ ((sysv_abi))	op_lkname(UNIX_ONLY_COMMA(int subcnt) mval *extgbl1, ...);
int __attribute__ ((sysv_abi))	op_lock(mval *timeout);
int __attribute__ ((sysv_abi))	op_lock2(mval *timeout, unsigned char laflag);
void __attribute__ ((sysv_abi))	op_lvpatwrite(UNIX_ONLY_COMMA(int4 count) UINTPTR_T arg1, ...);
void __attribute__ ((sysv_abi))	op_lvzwrite(UNIX_ONLY_COMMA(int4 count) long arg1, ...);
/*	op_merge     : prototype defined separately in op_merge.h */
/*	op_merge_arg : prototype defined separately in op_merge.h */
int __attribute__ ((sysv_abi))	op_mprofforchk1();
int __attribute__ ((sysv_abi))	op_mproflinefetch();
int __attribute__ ((sysv_abi))	op_mproflinestart();
void __attribute__ ((sysv_abi))	op_mul(mval *u, mval *v, mval *p);
void __attribute__ ((sysv_abi))	op_newintrinsic(int intrtype);
void __attribute__ ((sysv_abi))	op_newvar(uint4 arg1);
mval __attribute__ ((sysv_abi))	*op_nullexp(void);
void __attribute__ ((sysv_abi))	op_oldvar(void);
int __attribute__ ((sysv_abi))	op_open(mval *device, mval *devparms, mval *timeout, mval *mspace);
int __attribute__ ((sysv_abi))	op_open_dummy(mval *v, mval *p, mval *timeout, mval *mspace);
int __attribute__ ((sysv_abi))	op_rdone(mval *v, mval *timeout);
int __attribute__ ((sysv_abi))	op_read(mval *v, mval *timeout);
int __attribute__ ((sysv_abi))	op_readfl(mval *v, int4 length, mval *timeout);
int __attribute__ ((sysv_abi))	op_ret();
int __attribute__ ((sysv_abi))	op_retarg();
void __attribute__ ((sysv_abi))	op_rterror(int4 sig, boolean_t subrtn);
void __attribute__ ((sysv_abi))	op_setextract(mval *src, mval *expr, int schar, int echar, mval *dst);
void __attribute__ ((sysv_abi))	op_setp1(mval *src, int delim, mval *expr, int ind, mval *dst);
void __attribute__ ((sysv_abi))	op_setpiece(mval *src, mval *del, mval *expr, int4 first, int4 last, mval *dst);
void __attribute__ ((sysv_abi))	op_setzbrk(mval *rtn, mval *lab, int offset, mval *act, int cnt);
void __attribute__ ((sysv_abi))	op_setzextract(mval *src, mval *expr, int schar, int echar, mval *dst);
void __attribute__ ((sysv_abi))	op_setzp1(mval *src, int delim, mval *expr, int ind, mval *dst);
void __attribute__ ((sysv_abi))	op_setzpiece(mval *src, mval *del, mval *expr, int4 first, int4 last, mval *dst);
void __attribute__ ((sysv_abi))	op_sqlinddo(mstr *m_init_rtn);
int __attribute__ ((sysv_abi))	op_startintrrpt();
void __attribute__ ((sysv_abi))	op_stolitc(mval *val);
void __attribute__ ((sysv_abi))	op_sub(mval *u, mval *v, mval *s);
void __attribute__ ((sysv_abi))	op_sub(mval *u, mval *v, mval *s);
void __attribute__ ((sysv_abi))	op_svget(int varnum, mval *v);
void __attribute__ ((sysv_abi))	op_svput(int varnum, mval *v);
/*	op_tcommit : prototype defined separately in op_tcommit.h since it returns "enum cdb_sc" type. */
void __attribute__ ((sysv_abi))	op_trestart(int newlevel);

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


void __attribute__ ((sysv_abi))	op_trollback(int rb_levels);/*BYPASSOK*/
void __attribute__ ((sysv_abi))	op_unlock(void);
void __attribute__ ((sysv_abi))	op_unwind(void);
void __attribute__ ((sysv_abi))	op_use(mval *v, mval *p);
void __attribute__ ((sysv_abi))	op_view(UNIX_ONLY_COMMA(int numarg) mval *keyword, ...);
void __attribute__ ((sysv_abi))	op_write(mval *v);
void __attribute__ ((sysv_abi))	op_wteol(int4 n);
void __attribute__ ((sysv_abi))	op_wtff(void);
void __attribute__ ((sysv_abi))	op_wtone(int c);
void __attribute__ ((sysv_abi))	op_wttab(mint x);
void __attribute__ ((sysv_abi))	op_xkill(UNIX_ONLY_COMMA(int n) mval *lvname_arg, ...);
void __attribute__ ((sysv_abi))	op_xnew(UNIX_ONLY_COMMA(unsigned int argcnt_arg) mval *s_arg, ...);
int __attribute__ ((sysv_abi))	op_zallocate(mval *timeout);
void __attribute__ ((sysv_abi))	op_zattach(mval *);
int __attribute__ ((sysv_abi))	op_zbfetch();
int __attribute__ ((sysv_abi))	op_zbstart();
void __attribute__ ((sysv_abi))	op_zcompile(mval *v, boolean_t ignore_dollar_zcompile);
void __attribute__ ((sysv_abi))	op_zcont(void);
void __attribute__ ((sysv_abi))    op_zcollate(mval *v, int c, mval *p);
void __attribute__ ((sysv_abi))	op_zdealloc2(mval *timeout, UINTPTR_T auxown);
void __attribute__ ((sysv_abi))	op_zdeallocate(mval *timeout);
void __attribute__ ((sysv_abi))	op_zedit(mval *v, mval *p);
void __attribute__ ((sysv_abi))	op_zg1(int4 level);
void __attribute__ ((sysv_abi))	op_zgoto(mval *rtnname, mval *lblname, int offset, int level);
void __attribute__ ((sysv_abi))    op_zrupdate(int argcnt, ...);
void __attribute__ ((sysv_abi))	op_ztrigger(void);
void __attribute__ ((sysv_abi))	op_zhalt(int4 is_zhalt, boolean_t retcode);
void __attribute__ ((sysv_abi))	op_zhelp_xfr(mval *subject, mval *lib);
void __attribute__ ((sysv_abi))	op_zhorolog(mval *s);
void __attribute__ ((sysv_abi))	op_zlink(mval *v, mval *quals);
void __attribute__ ((sysv_abi))	op_zmess(unsigned int cnt, ...);
void __attribute__ ((sysv_abi))	op_zprevious(mval *v);
void __attribute__ ((sysv_abi))	op_zprint(mval *rtn, mval *start_label, int start_int_exp, mval *end_label, int end_int_exp);
void __attribute__ ((sysv_abi))	op_zst_break(void);
int __attribute__ ((sysv_abi))	op_zst_fet_over();
void __attribute__ ((sysv_abi))	op_zst_over(void);
int __attribute__ ((sysv_abi))	op_zst_st_over();
void __attribute__ ((sysv_abi))	op_zstep(uint4 code, mval *action);
int __attribute__ ((sysv_abi))	op_zstepfetch();
void __attribute__ ((sysv_abi))	op_zstepret(void);
int __attribute__ ((sysv_abi))	op_zstepstart();
int __attribute__ ((sysv_abi))	op_zstzb_fet_over();
int __attribute__ ((sysv_abi))	op_zstzb_st_over();
int __attribute__ ((sysv_abi))	op_zstzbfetch();
int __attribute__ ((sysv_abi))	op_zstzbstart();
void __attribute__ ((sysv_abi))	op_zsystem(mval *v);
void __attribute__ ((sysv_abi))	op_ztcommit(int4 n);
void __attribute__ ((sysv_abi))	op_ztstart(void);
int __attribute__ ((sysv_abi))	opp_ret();
int __attribute__ ((sysv_abi))	opp_zst_over_ret();
int __attribute__ ((sysv_abi))	opp_zst_over_retarg();
int __attribute__ ((sysv_abi))	opp_zstepret();
int __attribute__ ((sysv_abi))	opp_zstepretarg();
void __attribute__ ((sysv_abi))	op_zut(mval *s);
void __attribute__ ((sysv_abi))	op_zwritesvn(int svn);
void __attribute__ ((sysv_abi))	op_zst_over_retarg_helper(void);
void __attribute__ ((sysv_abi))	op_zstepretarg_helper(void);
#endif
