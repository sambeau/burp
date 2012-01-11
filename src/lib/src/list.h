/*
 *  list.h
 *
 *
 *  v1.0 Created by sambeau on Wed Jan 26 2005.
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

 
#ifndef _H_bz_LIST_H_
#define _H_bz_LIST_H_


#include "class.h"
#include "size.h"


typedef struct bz_list_node
{
   const  bz_Type* type;
   void*   node;
   struct bz_list_node* next;

} bz_List;

const bz_Type bz_List_type;
#define bz_LIST &bz_List_type

bz_List*  bz_list_new(void);
bz_SIZE   bz_list_length(bz_List* xs);
bz_SIZE   bz_list_charsize(bz_List* xs);

bz_List*   bz_list_cons(bz_List* xs, void* x);
#define cons(x,xs) bz_list_cons(xs,x)

bz_List*  bz_list_mergesort(bz_List* xs);
void   bz_list_show(bz_List* xs);
void   bz_list_debug_show(bz_List* xs);

bz_List*  bz_list_copy(bz_List* xs);

bz_List* bz_list_concat(bz_List* xs, bz_List* ys);

bz_List* _bz_list_of(void *x, ...);

#define  list(x, ...)  _bz_list_of(x, __VA_ARGS__, NULL)

bz_List* bz_list_flatten(bz_List* xs);

int bz_list_compare(bz_List* xs, bz_List*  ys);

bz_List* bz_list_reverse(bz_List* xs);

#endif /* _bz_LIST_H_ */

