/****************************************************************
 *								*
 * Copyright 2001, 2014 Fidelity Information Services, Inc	*
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

#include "zbreak.h"

zbrk_struct *zr_add_zbreak(z_records *zrecs, zb_code *addr)
{
	z_records	temp;
	zbrk_struct 	*z_ptr;

	/* NOTE: Records are stored by decreasing addresses */
	assert(zrecs->free < zrecs->end);
	for (z_ptr = zrecs->beg; z_ptr < zrecs->free; z_ptr++)
	{
		if (z_ptr->mpc == addr)
			return (z_ptr);
		if (z_ptr->mpc < addr)		/* Insert here */
			break;
	}
	assert(z_ptr == zrecs->free || z_ptr->mpc < addr);
	if (1 == zrecs->end - zrecs->free)	/* Expand if necessary */
	{
		temp = *zrecs;
		zr_init(zrecs, 2 * (int)(zrecs->end - zrecs->beg));
		assert(2 * (temp.end - temp.beg) == (zrecs->end - zrecs->beg));
		memcpy((char *)zrecs->beg, (char *)temp.beg, (temp.free - temp.beg) * SIZEOF(zbrk_struct));
		assert(zrecs->free == zrecs->beg);
		zrecs->free += (temp.free - temp.beg);
		z_ptr = zrecs->beg + (z_ptr - temp.beg);
		free(temp.beg);
	}
	/* Shift records down into the bottom spot which was allocated */
	memmove((char *)(z_ptr + 1), (char *)z_ptr, (zrecs->free - z_ptr) * SIZEOF(zbrk_struct));
	memset((char *)z_ptr, 0, SIZEOF(zbrk_struct));
	z_ptr->mpc = addr;
	zrecs->free++;
	return (z_ptr);
}
