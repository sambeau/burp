/*
 *  empty.h
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


#ifndef _H_BZ_EMPTY_H_
#define _H_BZ_EMPTY_H_


#include "class.h"
#include "list.h"
#include "size.h"


typedef struct {
   const bz_Type* type;
} bz_Empty;


extern   const bz_Empty bz_Empty_value;

#define  bz_EMPTY ((void *)&bz_Empty_value)

const  bz_Empty* bz_empty_new(bz_Empty* e); 
const  bz_Empty* bz_empty_clone(bz_Empty* e); 
bz_SIZE   bz_empty_length(bz_Empty* e); 
bz_SIZE   bz_empty_charsize(bz_Empty* e); 
int    bz_empty_compare(bz_Empty* e); 


#endif /* _H_BZ_EMPTY_H_ */

