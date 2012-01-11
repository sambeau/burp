/*
 *  nvp.c
 *
 *  Created by sambeau on Wed Apr 6 2005.
 *  Copyleft (L) 2003 Sam Phillips. Most rights returned.
 *
 * ----------------------------------------------------------------------
 * 
 * Copyright (C) 2003  Sam Phillips <sambeau@sambeau.com>
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
 *
 */

#include "debug.h" 
#include "nvp.h"


const bz_Type bz_Nvp_type;

bz_Nvp* bz_nvp_new(bz_String* name, void* value)
{
  bz_Nvp* n;

  new(bz_Nvp,n);

  n->name = name;
  n->value = value;
  
  return n;
}


bz_Nvp* bz_nvp_copy(bz_Nvp* n)
{
  return bz_nvp_new(n->name,n->value);		
}


bz_SIZE bz_nvp_length(bz_Nvp* xs)
{
  return 1;
}


bz_SIZE bz_nvp_charsize(bz_Nvp* n)
{
  return bz_string_length(n->name);
}


void bz_nvp_show(bz_Nvp* n)
{
  bz_string_show(n->name);
}
 

