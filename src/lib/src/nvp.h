/*
 *  nvp.h
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
 
#ifndef _H_BZ_NVP_H_
#define _H_BZ_NVP_H_

#include "class.h"
#include "size.h"
#include "string.h"


typedef struct
{
  const bz_Type* type;

  bz_String* name;
  void*   value;

  bz_String* filename;
  int line;  

} bz_Nvp;


#define bz_NVP &bz_Nvp_type

bz_Nvp*   bz_nvp_new(bz_String* name, void* val);
bz_SIZE   bz_nvp_length(bz_Nvp* xs);
bz_SIZE   bz_nvp_charsize(bz_Nvp* xs);
void      bz_nvp_show(bz_Nvp *xs);
bz_Nvp*   bz_nvp_copy(bz_Nvp* xs);

#define bz_nvp_name_length(x) bz_nvp_length(x)

#endif /*_BZ_NVP_H_*/
