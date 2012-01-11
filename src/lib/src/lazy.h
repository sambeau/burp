/*
 *  lazy.h
 *
 *
 *  v1.0 Created by sambeau on Mon Apr 4 2005.
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

 
#ifndef _H_bz_LAZY_H_
#define _H_bz_LAZY_H_


#include "class.h"
#include "size.h"


typedef struct bz_lazy_node
{
  const bz_Type  *type;
  void*           node;
  void*         (*next)();
  void*           arg;
} bz_Lazy;


#define bz_LAZY &bz_Lazy_type


bz_Lazy*  bz_lazy_new(const bz_Lazy*  (*next)(),void* arg);
bz_SIZE   bz_lazy_length(bz_Lazy* xs);
bz_SIZE   bz_lazy_charsize(bz_Lazy* xs);
bz_Lazy*  bz_lazy_copy(bz_Lazy* xs);
void      bz_lazy_show(bz_Lazy* xs);
bz_Lazy*  bz_lazy_xto(int n);
bz_Lazy*  bz_lazy_xdownto(int n);
bz_Lazy*  bz_lazy_xtoy(int x, int y);
bz_Lazy*  bz_lazy_filter(void* f, bz_Lazy* xs);


#endif /* _H_bz_LAZY_H_ */

