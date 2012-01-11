/*
 *  real.c
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

#include <math.h>

#include "class.h"
#include "debug.h"
#include "real.h"
#include "string.h"
#include "cast.h"


const bz_Type bz_real_type;


bz_Real* bz_real_new(bz_REALV r) 
{
   bz_Real* R;

   BEGIN;

   R = malloc(sizeof(bz_Real));
   if(R == NULL)
      FATAL("Out of Memory");

   R->type = bz_REAL;
   R->value  = r;

   RETURN(R);
}


bz_Real* bz_real_copy(bz_Real* x) 
{
   bz_Real* y;

   BEGIN;

   y = malloc(sizeof(bz_Real));
   if(y == NULL)
      FATAL("Out of Memory");

   y->type = bz_REAL;
   y->value  = x->value;

   RETURN(y);
}


bz_SIZE bz_real_length(bz_Real* r) 
{
  return 1;
}


bz_SIZE bz_real_charsize(bz_Real* r) 
{
  bz_REALV rv = r->value;
  
  if (rv == 0.0)
    return bz_REALP + 2;
  
  int x = (int)trunc(abs(rv));
  
  if (x == 0)
    return bz_REALP + 2 + (rv < 0.0 ? 1 : 0);
  else
    return ((int)floor( log10( x ) ) + bz_REALP + 2 + (rv < 0.0 ? 1 : 0));
}


int bz_real_compare(bz_Real* x, bz_Real* y) 
{
  bz_REALV r;
  BEGIN;
  r = x->value - y->value;
  if (r > 0) RETURN(1);
  if (r < 0) RETURN(-1);
  /* otherwise */ RETURN(0);
}


void bz_real_show(bz_Real* r) 
{
  fputws(bz_real_to_wstr(r),stdout);
}


const bz_Type bz_real_type = {

   L"Real",
   sizeof(bz_Real),

   (const void*) &bz_real_new,
   (const void*) &bz_real_copy,
   (const void*) &bz_real_length,
   (const void*) &bz_real_charsize,
   (const void*) &bz_real_compare,
   (const void*) &bz_real_to_integer,
   (const void*) &bz_real_to_real,
   (const void*) &bz_real_to_string,
   (const void*) &bz_real_to_list,
   (const void*) &bz_real_to_wstr,
   (const void*) &bz_real_show

};

