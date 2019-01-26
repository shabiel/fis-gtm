/****************************************************************
 *								*
 * Copyright (c) 2001-2017 Fidelity National Information	*
 * Services, Inc. and/or its subsidiaries. All rights reserved.	*
 *								*
 * Copyright (c) 2017-2019 YottaDB LLC. and/or its subsidiaries.*
 * All rights reserved.						*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

/* Note: Some constructs in this header file were taken from gtmxc_types.h which has an
 * FIS copyright hence the copyright is copied over here even though this header file was
 * not created by FIS.
 */

/*	libyottadb.h - YottaDB type and routine definitions for call_ins, call-outs, plugins, etc.  */
#ifndef LIBYOTTADB_TYPES_H
#define LIBYOTTADB_TYPES_H

#include <sys/types.h>	/* For intptr_t */
#include <inttypes.h>	/* .. ditto (defined different places in different platforms) .. */
#include <stdlib.h>	/* For abs() */

/* Enumerated parameter values. List value of each enum (not just first in list) as it is relied upon by the YottaDB Go Wrapper */
enum
{
	YDB_DEL_TREE = 1,
	YDB_DEL_NODE = 2,
};

/* Enumerated parameter values. List value of each enum (not just first in list) as it is relied upon by the YottaDB Go Wrapper */
enum
{
	YDB_SEVERITY_WARNING = 0,	/* Warning - Something is potentially incorrect */
	YDB_SEVERITY_SUCCESS = 1,	/* Success */
	YDB_SEVERITY_ERROR = 2,		/* Error - Something is definitely incorrect */
	YDB_SEVERITY_INFORMATIONAL = 3,	/* Informational - won't see these returned as they continue running */
	YDB_SEVERITY_FATAL = 4		/* Fatal - Something happened that is so bad, YottaDB cannot continue */
};

#define	YDB_RELEASE		123	/* Corresponds to YottaDB release r1.23 (i.e. YDB_ZYRELEASE in sr_linux/release_name.h) */

/* Maximum values */
#define	YDB_MAX_IDENT		31		/* Maximum size of global/local name (not including '^') */
#define	YDB_MAX_NAMES		35		/* Maximum number of variable names can be specified in a single ydb_*_s() call */
#define	YDB_MAX_STR		(1 * 1024 * 1024)	/* Maximum YottaDB string length */
#define	YDB_MAX_SUBS		31		/* Maximum subscripts currently supported */
#define	YDB_MAX_TIME_NSEC	(0x7fffffffllu * 1000llu * 1000llu)	/* Max specified time in (long long) nanoseconds */
#define	YDB_MAX_YDBERR		(2 ** 30)	/* Maximum (absolute) value for a YottaDB error */
#define	YDB_MAX_ERRORMSG	1024		/* Will hold any message we return. Not used in YottaDB C code but relied upon
						 * by the GoWrapper/Golang interface to YottaDB.
						 */
/* Minimum values */
#define	YDB_MIN_YDBERR		(2 ** 27)	/* Minimum (absolute) value for a YottaDB error */

/* Non-error return codes (all positive) */
#define	YDB_OK		0		/* Successful return code */
/* Keep the below YDB_* macros a very high positive error # to avoid intersection with system errors #s
 * (e.g. EINTR etc. all of which are mostly <= 1024). Can use INT_MAX but not sure if that will change
 * in the future to a higher value in <limits.h> so set YDB_INT_MAX to the hardcoded fixed value of ((2**31)-1).
 */
#define	YDB_INT_MAX		((int)0x7fffffff)
#define	YDB_TP_RESTART		(YDB_INT_MAX - 1)	/* 0x7ffffffe */
#define	YDB_TP_ROLLBACK		(YDB_INT_MAX - 2)	/* 0x7ffffffd */
#define	YDB_NOTOK		(YDB_INT_MAX - 3)	/* 0x7ffffffc */
#define	YDB_LOCK_TIMEOUT	(YDB_INT_MAX - 4)	/* 0x7ffffffb */

/* Miscellaneous defines */
#ifndef TRUE
#	define	TRUE	1
#endif
#ifndef FALSE
#	define	FALSE	0
#endif
#ifndef NULL
#	define	NULL	((void *)0)
#endif

/* Value for tptoken for SimpleThreadAPI calls if NOT in a TP transaction */
#define	YDB_NOTTP	0

/* Macro to create/fill-in a ydb_buffer_t structure from a literal - use - literal varnames, subscripts
 * or values.
 */
#define YDB_LITERAL_TO_BUFFER(LITERAL, BUFFERP)					\
{										\
	(BUFFERP)->buf_addr = LITERAL;						\
	(BUFFERP)->len_used = (BUFFERP)->len_alloc = sizeof(LITERAL) - 1;	\
}

/* Below macro returns TRUE if two input ydb_buffer_t structures pointer to the same string and FALSE otherwise. */
#define YDB_BUFFER_IS_SAME(BUFFERP1, BUFFERP2)										\
	(((BUFFERP1)->len_used == (BUFFERP2)->len_used) && !memcmp((BUFFERP1)->buf_addr, (BUFFERP2)->buf_addr, (BUFFERP2)->len_used))

/* Below macro copies SRC ydb_buffer_t to DST ydb_buffer_t.
 * If DST does not have space allocated to hold SRC->len_used, then no copy is done
 *	and COPY_DONE will be set to FALSE.
 * Else the copy is done and COPY_DONE will be set to TRUE.
 */
#define	YDB_COPY_BUFFER_TO_BUFFER(SRC, DST, COPY_DONE)				\
{										\
	if ((SRC)->len_used <= (DST)->len_alloc)				\
	{									\
		memcpy((DST)->buf_addr, (SRC)->buf_addr, (SRC)->len_used);	\
		(DST)->len_used = (SRC)->len_used;				\
		COPY_DONE = TRUE;						\
	} else									\
		COPY_DONE = FALSE;						\
}

/* Macro to copy a strlit to an already allocated ydb_buffer_t structure.
 * If BUFFERP does not have space allocated to hold LITERAL, then no copy is done
 *	and COPY_DONE will be set to FALSE.
 * Else the copy is done and COPY_DONE will be set to TRUE.
 * Note that this is similar to the YDB_LITERAL_TO_BUFFER macro except that this does not update (BUFFERP)->len_alloc.
 */
#define YDB_COPY_LITERAL_TO_BUFFER(LITERAL, BUFFERP, COPY_DONE)	\
{								\
	int	len;						\
								\
	len = sizeof(LITERAL) - 1;				\
	if (len <= (BUFFERP)->len_alloc)			\
	{							\
		memcpy((BUFFERP)->buf_addr, LITERAL, len);	\
		(BUFFERP)->len_used = len;			\
		COPY_DONE = TRUE;				\
	} else							\
		COPY_DONE = FALSE;				\
}

/* Macro to copy a string (i.e. "char *" pointer in C) to an already allocated ydb_buffer_t structure.
 * If BUFFERP does not have space allocated to hold STRING, then no copy is done
 *	and COPY_DONE will be set to FALSE.
 * Else the copy is done and COPY_DONE will be set to TRUE.
 * User of this macro needs to include <string.h> (needed for "strlen" prototype).
 */
#define YDB_COPY_STRING_TO_BUFFER(STRING, BUFFERP, COPY_DONE)	\
{								\
	int	len;						\
								\
	len = strlen(STRING);					\
	if (len <= (BUFFERP)->len_alloc)			\
	{							\
		memcpy((BUFFERP)->buf_addr, STRING, len);	\
		(BUFFERP)->len_used = len;			\
		COPY_DONE = TRUE;				\
	} else							\
		COPY_DONE = FALSE;				\
}

/* Macro to allocate a buffer using "malloc" of length LEN and assign it to an already allocated ydb_buffer_t structure.
 * BUFFERP->buf_addr is set to the malloced buffer.
 * BUFFERP->len_alloc is set to the malloced length.
 * BUFFERP->len_used is set to 0.
 */
#define	YDB_MALLOC_BUFFER(BUFFERP, LEN)			\
{							\
	(BUFFERP)->len_alloc = LEN;			\
	(BUFFERP)->len_used = 0;			\
	(BUFFERP)->buf_addr = malloc(LEN);		\
	YDB_ASSERT_DBG(NULL != (BUFFERP)->buf_addr);	\
}

/* Macro to free the buffer malloced using "YDB_MALLOC_BUFFER" */
#define	YDB_FREE_BUFFER(BUFFERP)			\
{							\
	YDB_ASSERT_DBG(NULL != (BUFFERP)->buf_addr);	\
	free((BUFFERP)->buf_addr);			\
	(BUFFERP)->buf_addr = NULL;			\
}

/* Macro to verify an assertion is true before proceeding - put expression to test as the parameter */
#define YDB_ASSERT(X)														\
{																\
	if (!(X))														\
	{															\
		fprintf(stderr, "YDB_ASSERT: ** Assert failed (%s) at line %d in routine %s - generating core\n",		\
			#X, __LINE__, __FILE__);										\
		fflush(stderr);													\
		fflush(stdout);													\
		ydb_fork_n_core();												\
		exit(1);		/* Shouldn't return but just in case */							\
	}															\
}

/* Macro to determine if a return code is a YottaDB error/message code or not */
#define YDB_IS_YDB_ERRCODE(MSGNUM) ((YDB_MIN_YDBERR <= abs(MSGNUM)) && (YDB_MAX_YDBERR >= abs(MSGNUM)))

/* Macro to determine severity of error returned from simpleapi call. Note a possible return value is an errno value. These
 * errno values do not follow the same rules as YottaDB generated errors so this macro does not work on them. YottaDB
 * generated errors numbers are all (absolute value) LARGER than 2**27 so anything under that is not supported by this macro.
 */
#define YDB_SEVERITY(MSGNUM, SEVERITY)										\
{													\
	/* Minor subterfuge because YDB_OK is 0 (per normal UNIX return code) but the rest of the codes,	\
	 * when the error is out of the range of errno values, have 1 as a success value.			\
	 */													\
	if (YDB_OK == (MSGNUM))											\
		SEVERITY = YDB_SEVERITY_SUCCESS;								\
	else													\
		SEVERITY = ((int)abs(MSGNUM) & 7);	/* Doing abs so always have positive version */		\
}

/* If only want assertions in DEBUG mode (-DDEBUG option specified), use this macro instead */
#ifdef DEBUG
#  define YDB_ASSERT_DBG(X)	YDB_ASSERT(X)
#else
#  define YDB_ASSERT_DBG(X)
#endif

/* Basic/standard types */
typedef	int		ydb_status_t;
typedef	int		ydb_int_t;
typedef	unsigned int	ydb_uint_t;
typedef	long		ydb_long_t;
typedef	unsigned long	ydb_ulong_t;
typedef	float		ydb_float_t;
typedef	double		ydb_double_t;
typedef	char		ydb_char_t;
typedef	int		(*ydb_pointertofunc_t)();
typedef	void		(*ydb_funcptr_retvoid_t)();

/* Structure for passing (non-NULL-terminated) character arrays whose length corresponds to the value of the
 * 'length' field. Note that for output-only ydb_string_t * arguments the 'length' field is set to the
 * preallocation size of the buffer pointed to by 'address', while the first character of the buffer is '\0'.
 */
typedef struct
{
	unsigned long	length;
	char		*address;
} ydb_string_t;

/* Structure for interfacing with simple API routines. Meant to be used with the YDB_* macros defined
 * above in this header file and with simple API calls.
 */
typedef struct
{
	unsigned int	len_alloc;
	unsigned int	len_used;
	char		*buf_addr;
} ydb_buffer_t;

typedef intptr_t	ydb_tid_t;		/* Timer id */
typedef void		*ydb_fileid_ptr_t;

/* Structure used to reduce name lookup for callins. The handle field (should be zeroed on first call) after
 * the first call using ydb_cij() contains information that allows quick resolution of the routine for a
 * faster call.
 */
typedef struct
{
	ydb_string_t	rtn_name;
	void		*handle;
} ci_name_descriptor;

/* Java types with special names for clarity. */
typedef	ydb_int_t	ydb_jboolean_t;
typedef	ydb_int_t	ydb_jint_t;
typedef	ydb_long_t	ydb_jlong_t;
typedef	ydb_float_t	ydb_jfloat_t;
typedef	ydb_double_t	ydb_jdouble_t;
typedef	ydb_char_t	ydb_jstring_t;
typedef	ydb_char_t	ydb_jbyte_array_t;
typedef	ydb_char_t	ydb_jbig_decimal_t;

/* Function pointer types for use in the APIs below */
typedef	int		(*ydb_tpfnptr_t)(void *tpfnparm);					   /* For use in SimpleAPI */
typedef	int		(*ydb_tp2fnptr_t)(uint64_t tptoken, ydb_buffer_t *errstr, void *tpfnparm); /* For use in SimpleThreadAPI */
typedef	uintptr_t	(*ydb_vplist_func)(uintptr_t cnt, ...);

#	ifdef GTM_PTHREAD
int	ydb_jinit(void);
#	endif
int	ydb_cij(const char *c_rtn_name, char **arg_blob, int count, int *arg_types, unsigned int *io_vars_mask,
		unsigned int *has_ret_value);
void	ydb_zstatus(char* msg, int len);

int ydb_call_variadic_plist_func_s(ydb_vplist_func cgfunc, uintptr_t cvplist);	/* Used by Golang to call variadic C function */

/* Utility entry points accessable in libyottadb.so */
int	ydb_child_init(void *param);
int	ydb_ci(const char *c_rtn_name, ...);				/* Call-in interface */
int	ydb_cip(ci_name_descriptor *ci_info, ...);			/* Slightly faster "ydb_ci" */
int	ydb_exit(void);
int	ydb_file_id_free(ydb_fileid_ptr_t fileid);
int	ydb_file_is_identical(ydb_fileid_ptr_t fileid1, ydb_fileid_ptr_t fileid2);
int	ydb_file_name_to_id(ydb_string_t *filename, ydb_fileid_ptr_t *fileid);
void	ydb_fork_n_core(void);
void	ydb_free(void *ptr);
int	ydb_hiber_start(unsigned long long sleep_nsec);
int	ydb_hiber_start_wait_any(unsigned long long sleep_nsec);
int	ydb_init(void);
void	*ydb_malloc(size_t size);
int	ydb_message(int status, ydb_buffer_t *msg_buff);
int	ydb_stdout_stderr_adjust(void);
int	ydb_thread_is_main(void);
void	ydb_timer_cancel(int timer_id);
int	ydb_timer_start(int timer_id, unsigned long long limit_nsec, ydb_funcptr_retvoid_t handler, unsigned int hdata_len,
			void *hdata);

/* Utility routines for use in threaded applications - SimpleThreadAPI.
 * Note that "ydb_init" and "ydb_exit" are multi-thread safe utility routines and so can be used in SimpleAPI and SimpleThreadAPI.
 */
int	ydb_ci_t(uint64_t tptoken, ydb_buffer_t *errstr, const char *c_rtn_name, ...);	/* SimpleThreadAPI version of "ydb_ci" */
int	ydb_cip_t(uint64_t tptoken, ydb_buffer_t *errstr, ci_name_descriptor *ci_info, ...);
											/* SimpleThreadAPI version of "ydb_cip" */
int	ydb_file_id_free_t(uint64_t tptoken, ydb_buffer_t *errstr, ydb_fileid_ptr_t fileid);
int	ydb_file_is_identical_t(uint64_t tptoken, ydb_buffer_t *errstr, ydb_fileid_ptr_t fileid1, ydb_fileid_ptr_t fileid2);
int	ydb_file_name_to_id_t(uint64_t tptoken, ydb_buffer_t *errstr, ydb_string_t *filename, ydb_fileid_ptr_t *fileid);
int	ydb_message_t(uint64_t tptoken, ydb_buffer_t *errstr, int status, ydb_buffer_t *msg_buff);
int	ydb_stdout_stderr_adjust_t(uint64_t tptoken, ydb_buffer_t *errstr);
void	ydb_timer_cancel_t(uint64_t tptoken, ydb_buffer_t *errstr, int timer_id);
int	ydb_timer_start_t(uint64_t tptoken, ydb_buffer_t *errstr, int timer_id, unsigned long long limit_nsec,
					ydb_funcptr_retvoid_t handler, unsigned int hdata_len, void *hdata);

/* Simple API routine declarations */
int	ydb_data_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray, unsigned int *ret_value);
int	ydb_delete_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray, int deltype);
int	ydb_delete_excl_s(int namecount, ydb_buffer_t *varnames);
int	ydb_get_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray, ydb_buffer_t *ret_value);
int	ydb_incr_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray, ydb_buffer_t *increment, ydb_buffer_t *ret_value);
int	ydb_lock_s(unsigned long long timeout_nsec, int namecount, ...);
	/* ... above translates to one or more sets of [ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray] */
int	ydb_lock_decr_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray);
int	ydb_lock_incr_s(unsigned long long timeout_nsec, ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray);
int	ydb_node_next_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray, int *ret_subs_used,
			ydb_buffer_t *ret_subsarray);
int	ydb_node_previous_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray, int *ret_subs_used,
			ydb_buffer_t *ret_subsarray);
int	ydb_set_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray, ydb_buffer_t *value);
int	ydb_str2zwr_s(ydb_buffer_t *str, ydb_buffer_t *zwr);
int	ydb_subscript_next_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray, ydb_buffer_t *ret_value);
int	ydb_subscript_previous_s(ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray, ydb_buffer_t *ret_value);
int	ydb_tp_s(ydb_tpfnptr_t tpfn, void *tpfnparm, const char *transid, int namecount, ydb_buffer_t *varnames);
int	ydb_zwr2str_s(ydb_buffer_t *zwr, ydb_buffer_t *str);

/* SimpleAPI via thread interface (aka threaded Simple API).
 * Currently only one main thread runs the YottaDB engine. Once YottaDB itself is multi-threaded, we can support more threads.
 */
int	ydb_call_variadic_plist_func_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_vplist_func cgfunc, uintptr_t cvplist);
		/* Used by Golang to call a variadic C function */
int	ydb_data_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray,
			unsigned int *ret_value);
int	ydb_delete_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray,
			int deltype);
int	ydb_delete_excl_st(uint64_t tptoken, ydb_buffer_t *errstr, int namecount, ydb_buffer_t *varnames);
int	ydb_get_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray,
			ydb_buffer_t *ret_value);
int	ydb_incr_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray,
			ydb_buffer_t *increment, ydb_buffer_t *ret_value);
int	ydb_lock_st(uint64_t tptoken, ydb_buffer_t *errstr, unsigned long long timeout_nsec, int namecount, ...);
	/* ... above translates to one or more sets of [ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray] */
int	ydb_lock_decr_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray);
int	ydb_lock_incr_st(uint64_t tptoken, ydb_buffer_t *errstr, unsigned long long timeout_nsec, ydb_buffer_t *varname,
			int subs_used, ydb_buffer_t *subsarray);
int	ydb_node_next_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray,
			int *ret_subs_used, ydb_buffer_t *ret_subsarray);
int	ydb_node_previous_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray,
			int *ret_subs_used, ydb_buffer_t *ret_subsarray);
int	ydb_set_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used, ydb_buffer_t *subsarray,
			ydb_buffer_t *value);
int	ydb_str2zwr_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *str, ydb_buffer_t *zwr);
int	ydb_subscript_next_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used,
			ydb_buffer_t *subsarray, ydb_buffer_t *ret_value);
int	ydb_subscript_previous_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *varname, int subs_used,
			ydb_buffer_t *subsarray, ydb_buffer_t *ret_value);
int	ydb_tp_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_tp2fnptr_t tpfn, void *tpfnparm, const char *transid, int namecount,
			ydb_buffer_t *varnames);
int	ydb_zwr2str_st(uint64_t tptoken, ydb_buffer_t *errstr, ydb_buffer_t *zwr, ydb_buffer_t *str);

#include "libydberrors.h"	/* needed for various errors returned by SimpleAPI/SimpleThreadAPI (e.g. YDB_ERR_TPTIMEOUT etc.) */

#endif /* LIBYOTTADB_TYPES_H */
