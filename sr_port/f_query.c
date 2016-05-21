/****************************************************************
 *								*
 *	Copyright 2001, 2012 Fidelity Information Services, Inc	*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"
#include "compiler.h"
#include "opcode.h"
#include "indir_enum.h"
#include "toktyp.h"
#include "mdq.h"
#include "fullbool.h"

GBLREF	boolean_t	run_time;
GBLREF	int		source_column;

error_def(ERR_VAREXPECTED);
error_def(ERR_QUERY2);

enum query_obj {
	GLOBAL = 0,
	LOCAL,
	INDIRECT,
	LAST_OBJECT
};

enum query_dir {
	FORWARD = 0,
	BACKWARD,
	TBD,
	LAST_DIRECTION
};

int f_query(oprtype *a, opctype op)
{
	enum query_dir	direction;
	enum query_obj	object;
	int4		intval;
	save_se		save_state;
	opctype		gv_oc;
	oprtype		control_slot, dir_opr, *dir_oprptr, *next_oprptr;
	short int	column;
	triple		*oldchain, *r, *r0, *r1;
	triple		*sav_dirref, *sav_gv1, *sav_gvn, *sav_lvn, *sav_ref, *share, *triptr;
	triple		*chain2, *obp, tmpchain2;
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	oldchain = sav_dirref = NULL;			/* default to no direction and no shifting indirection */
	used_glvn_slot = FALSE;
	r = maketriple(OC_NOOP);			/* We'll fill in the opcode later, when we figure out what it is */
	switch (TREF(window_token))
	{
	case TK_IDENT:
		object = LOCAL;
		ok = lvn(&r->operand[0], OC_FNQUERY, r);	/* TODO COME BACK *-* 2nd arg causes us to mess below with return from lvn */
		next_oprptr = &r->operand[1];
		break;
	case TK_CIRCUMFLEX:
		object = GLOBAL;
		sav_gv1 = TREF(curtchain);
		ok = gvn();
		sav_gvn = (TREF(curtchain))->exorder.bl;/
		if (OC_GVRECTARG == sav_gvn->opcode)
		{	/* because of shifting if we need to find it, look in the expr_start chain */
			assert(TREF(shift_side_effects));
			assert(((sav_gvn->operand[0].oprval.tref) == TREF(expr_start)) && (NULL != TREF(expr_start_orig)));
			sav_gv1 = TREF(expr_start_orig);
			sav_gvn = TREF(expr_start);
		}
		next_oprptr = &r->operand[0];
		break;
	case TK_ATSIGN:
		object = INDIRECT;
		if (SHIFT_SIDE_EFFECTS)
			START_GVBIND_CHAIN(&save_state, oldchain);
		ok = indirection(&r->operand[0]);
		next_oprptr = &r->operand[1];
		break;
	default:
		ok = FALSE;
		break;
	}
	if (!ok)
	{
		if (NULL != oldchain)
			setcurtchain(oldchain);
		stx_error(ERR_VAREXPECTED);
		return FALSE;
	}
	if (TK_COMMA != TREF(window_token))

	if (TK_IDENT == TREF(window_token))
		if (!lvn(a, OC_FNQUERY, 0))
			return FALSE;
		assert(TRIP_REF == a->oprclass);
		if (OC_FNQUERY == a->oprval.tref->opcode)
		{
			assert(OC_FNQUERY == a->oprval.tref->opcode);
			assert(TRIP_REF == a->oprval.tref->operand[0].oprclass);
			assert(OC_ILIT == a->oprval.tref->operand[0].oprval.tref->opcode);
			assert(ILIT_REF == a->oprval.tref->operand[0].oprval.tref->operand[0].oprclass);
			assert(0 < a->oprval.tref->operand[0].oprval.tref->operand[0].oprval.ilit);
			a->oprval.tref->operand[0].oprval.tref->operand[0].oprval.ilit += 2;
			assert(TRIP_REF == a->oprval.tref->operand[1].oprclass);
			assert(OC_PARAMETER == a->oprval.tref->operand[1].oprval.tref->opcode);
			assert(TRIP_REF == a->oprval.tref->operand[1].oprval.tref->operand[0].oprclass);
			r0 = a->oprval.tref->operand[1].oprval.tref->operand[0].oprval.tref;
			assert(OC_VAR == r0->opcode);
			assert(MVAR_REF == r0->operand[0].oprclass);
			r1 = maketriple(OC_PARAMETER);
			r1->operand[0] = put_str(r0->operand[0].oprval.vref->mvname.addr, r0->operand[0].oprval.vref->mvname.len);
			r1->operand[1] = a->oprval.tref->operand[1];
			a->oprval.tref->operand[1] = put_tref (r1);
			dqins (a->oprval.tref->exorder.fl, exorder, r1);
		} else
		{
			assert(OC_VAR == a->oprval.tref->opcode);
			r0 = newtriple(OC_FNQUERY);
			r0->operand[0] = put_ilit (3);
			r0->operand[1] = put_tref(newtriple(OC_PARAMETER));
			r0->operand[1].oprval.tref->operand[0] = put_str(a->oprval.tref->operand[0].oprval.vref->mvname.addr,
									a->oprval.tref->operand[0].oprval.vref->mvname.len);
			r1 = r0->operand[1].oprval.tref;
			r1->operand[1] = *a;
			*a = put_tref (r0);
		}
	} else
	{
		r = maketriple(op);
		switch (TREF(window_token))
		{
		case TK_CIRCUMFLEX:
			if (!gvn())
				return FALSE;
			r->opcode = OC_GVQUERY;
			ins_triple(r);
			break;
		case TK_ATSIGN:
			if (SHIFT_SIDE_EFFECTS)
			{
				START_GVBIND_CHAIN(&save_state, oldchain);
				if (!indirection(&(r->operand[0])))
				{
					setcurtchain(oldchain);
					return FALSE;
				}
				r->operand[1] = put_ilit((mint)indir_fnquery);
				ins_triple(r);
				PLACE_GVBIND_CHAIN(&save_state, oldchain);
			} else
			{
				if (!indirection(&(r->operand[0])))
					return FALSE;
				r->operand[1] = put_ilit((mint)indir_fnquery);
				ins_triple(r);
			}
			r->opcode = OC_INDFUN;
			break;
		default:
			stx_error(ERR_VAREXPECTED);
			return FALSE;
		}

	  *a = put_tref(r);
	}
	/* START HERE */
	if (TK_COMMA != TREF(window_token))
		direction = FORWARD;	/* default direction */
	else
	{	/* two argument form: ugly logic for direction */
		advancewindow();
		column = source_column;
		dir_oprptr = (oprtype *)mcalloc(SIZEOF(oprtype));
		dir_opr = put_indr(dir_oprptr);
		sav_ref = newtriple(OC_GVSAVTARG);
		DISABLE_SIDE_EFFECT_AT_DEPTH;		/* doing this here let's us know specifically if direction had SE threat */
		if (EXPR_FAIL == expr(dir_oprptr, MUMPS_EXPR))
		{
			if (NULL != oldchain)
				setcurtchain(oldchain);
			return FALSE;
		}
		assert(TRIP_REF == dir_oprptr->oprclass);
		triptr = dir_oprptr->oprval.tref;
		if (OC_LIT == triptr->opcode)
		{	/* if direction is a literal - pick it up and stop flailing about */
			if (MV_IS_TRUEINT(&triptr->operand[0].oprval.mlit->v, &intval) && (1 == intval || -1 == intval))
			{
				direction = (1 == intval) ? FORWARD : BACKWARD;
				sav_ref->opcode = OC_NOOP;
				sav_ref = NULL;
			} else
			{	/* bad direction */
				if (NULL != oldchain)
					setcurtchain(oldchain);
				stx_error(ERR_QUERY2);
				return FALSE;
			}
		} else
		{
			direction = TBD;
		}
	}

	return TRUE;
}
