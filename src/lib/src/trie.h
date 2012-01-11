/*
 *  trie.h
 *
 *
 *  v1.0 Created by sambeau on Tue Apr 12 2005.
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
 

#ifndef _H_BZ_TRIE_H_
#define _H_BZ_TRIE_H_

#include "class.h"
#include "string.h"
#include "list.h"

#ifndef BZ_TRIE_MIN_NODES
#define BZ_TRIE_MIN_NODES 2
#endif

typedef struct 
{
  CHAR c;
  void* data;
  void* next; /*is a trie really*/
} bz_trie_node;


typedef struct
{
  bz_SIZE node_array_size;
  bz_SIZE length;
  bz_trie_node* nodes;
} bz_trie;

/* private stuff */

bz_trie* bz_trie_find_top(bz_trie* T, CHAR* key, bz_SIZE key_index);
void     bz_trie_find_and_graft(bz_trie* T, CHAR* key, bz_SIZE key_index, void* data);
bz_trie* bz_trie_make(CHAR* key, bz_SIZE key_index, bz_SIZE node_size, void* data);
void*    bz_trie_find(bz_trie* T, CHAR* key, bz_SIZE key_index);

/* public interface */

#define  bz_trie_new(n,v)   bz_trie_make(n, 0, BZ_TRIE_MIN_NODES, v)
#define  bz_trie_get(t,k)   bz_trie_find(t,k,0)
#define  bz_trie_put(t,k,d) bz_trie_find_and_graft(t,k,0,d)

void     bz_trie_delete(bz_trie* T, CHAR* key);
bz_List* bz_trie_flatten(bz_trie* T, bz_String* s);

/* debug interface */
void     bz_trie_show(bz_trie* T, int n);


#endif /* _H_BZ_TRIE_H_ */
