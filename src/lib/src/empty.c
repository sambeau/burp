/*
 *  empty.c
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
#include "empty.h"
#include "cast.h"


const bz_Type bz_Empty_type;

const bz_Empty bz_Empty_value = {
  &bz_Empty_type
};


const bz_Empty* bz_empty_new(bz_Empty* e) 
{
  return bz_EMPTY;
}


const bz_Empty* bz_empty_clone(bz_Empty* e) 
{
  return bz_EMPTY;
}


bz_SIZE bz_empty_length(bz_Empty* e) 
{
  return 0;
}


bz_SIZE   bz_empty_charsize(bz_Empty* e) 
{
  return 0;
}


int bz_empty_compare(bz_Empty* e) 
{
  return (e == bz_EMPTY ? 0 : -1 );
}

void bz_empty_show(bz_Empty* e)
{
  /* show nothin' */
}

const bz_Type bz_Empty_type = {
   L"Empty",
   sizeof(bz_Empty),
   (const void*) &bz_empty_new,
   (const void*) &bz_empty_clone,
   (const void*) &bz_empty_length,
   (const void*) &bz_empty_charsize,
   (const void*) &bz_empty_compare,
   (const void*) &bz_empty_to_integer,
   (const void*) &bz_empty_to_real,
   (const void*) &bz_empty_to_string,
   (const void*) &bz_empty_to_list,
   (const void*) &bz_empty_to_wstr,
   (const void*) &bz_empty_show
};
