/*
 *  real.h
 *
 *  v1.0 Created by sambeau on Sat Mar 26 2005.
 *
 *  Copyleft (L) 2005 Sam Phillips. Most rights returned.
 *
 * ----------------------------------------------------------------------
 * 
 * Copyright (C) 2005  Sam Phillips <sambeau@sambeau.com>
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of The Artistic License a copy of which should have been
 * distributed with this file.
 * 
 * You may make and give away verbatim copies of the source form of the
 * Standard Version of this Package without restriction, provided that you
 * duplicate all of the original copyright notices and associated
 * disclaimers.
 * 
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *  
 * ----------------------------------------------------------------------
 *
 *
 */


#ifndef _H_bz_REAL_H_
#define _H_bz_REAL_H_

#include "size.h"
#include "class.h"
#include "list.h"
#include "string.h"

#define bz_REALP  6
#define bz_REALV  double
#define bz_REALF  L"%.6f"

typedef struct {
  const bz_Type* type;
  bz_REALV value;
} bz_Real;


#define bz_REAL &bz_real_type


bz_Real*     bz_real_new(bz_REALV r);
bz_Real*     bz_real_copy(bz_Real* r);

bz_SIZE      bz_real_length(bz_Real* r);
bz_SIZE      bz_real_charsize(bz_Real* r);

int       bz_real_compare(bz_Real* x, bz_Real* y);

void      bz_real_show(bz_Real* r); 

#define real(x) bz_real_new(x)

#endif /* _H_bz_REAL_H_ */

