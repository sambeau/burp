/*
 *  integer.c
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


#include "class.h"
#include "debug.h"
#include "integer.h"
#include "string.h"
#include "cast.h"


const bz_Type bz_Integer_type;


bz_Integer* bz_integer_new(INTV i) 
{
   bz_Integer* I;

   BEGIN;

   I = malloc(sizeof(bz_Integer));
   if(I == NULL)
      FATAL("Out of Memory");

   I->type = bz_INTEGER;
   I->value  = i;

   RETURN(I);
}


bz_Integer* bz_integer_copy(bz_Integer* J) 
{
   bz_Integer* I;

   BEGIN;

   I = malloc(sizeof(bz_Integer));
   if(I == NULL)
      FATAL("Out of Memory");

   I->type = bz_INTEGER;
   I->value  = J->value;

   RETURN(I);
}


bz_SIZE bz_integer_length(bz_Integer* I) 
{
  return 1;
}


bz_SIZE bz_integer_charsize(bz_Integer* I) 
{
  return bz_INTEGER_CHAR_SIZE(I);
}


int bz_integer_compare(bz_Integer* x, bz_Integer* y) 
{

  return x->value - y->value;
}


void bz_integer_show(bz_Integer* I) 
{
  fputws(bz_integer_to_wstr(I),stdout);
}


const bz_Type bz_Integer_type = {

   L"Integer",
   sizeof(bz_Integer),

   (const void*) &bz_integer_new,
   (const void*) &bz_integer_copy,
   (const void*) &bz_integer_length,
   (const void*) &bz_integer_charsize,
   (const void*) &bz_integer_compare,
   (const void*) &bz_integer_to_integer,
   (const void*) &bz_integer_to_real,
   (const void*) &bz_integer_to_string,
   (const void*) &bz_integer_to_list,
   (const void*) &bz_integer_to_wstr,
   (const void*) &bz_integer_show

};

