/*
 *  integer.h
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


#ifndef _H_bz_INTEGER_H_
#define _H_bz_INTEGER_H_

#include <math.h>
#include "size.h"
#include "class.h"
#include "list.h"
#include "string.h"

/*
 * We should maybe choose a more specific integer value?
 *
 * see http://www.gnu.org/software/libc/manual/html_node/Integers.html#bIntegers
 */

#define INTV  long long
#define INTF  L"%lld"

typedef struct {
  const bz_Type* type;
  INTV value;
} bz_Integer;


const bz_Type bz_Integer_type;
#define bz_INTEGER &bz_Integer_type


bz_Integer*  bz_integer_new(INTV i);
bz_Integer*  bz_integer_copy(bz_Integer* J);

bz_SIZE      bz_integer_length(bz_Integer* I);
bz_SIZE      bz_integer_charsize(bz_Integer* I);

int       bz_integer_compare(bz_Integer* x, bz_Integer* y);

void      bz_integer_show(bz_Integer* I); 


#define int(x) bz_integer_new(x)

#define bz_INTEGER_CHAR_SIZE(I)\
 (\
   (I->value == 0) ?\
      1\
   :\
      (floor( log10( abs(I->value) ) ) + 1 + (I->value < 0 ? 1 : 0))\
  )
#endif /* _H_bz_INTEGER_H_ */
