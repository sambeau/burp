/*
 *  trie.c
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

#include <wchar.h> 
#include "debug.h"
#include "empty.h"
#include "trie.h"

bz_trie* bz_trie_make(CHAR* key, bz_SIZE key_index, bz_SIZE node_size, void* data)
{
  BEGIN;

  assert(key != NULL);
  assert(key_index <= wcslen(key));

  if (L'\0' == key[key_index]) 
    RETURN( NULL );

  node_size = 
    (node_size <= BZ_TRIE_MIN_NODES) 
    ? BZ_TRIE_MIN_NODES 
    : node_size; // more robust than an assert() methinks

  bz_trie* T = malloc( sizeof(bz_trie) );
  if (T == NULL)
    FATAL("Out of memory");
  
  T->nodes = malloc(sizeof(bz_trie_node) * node_size);
  if (T->nodes == NULL)
    FATAL("Out of memory");

  T->node_array_size = node_size;
  T->length = 1;
  T->nodes[0].c = key[key_index];
  
  bz_trie* t = bz_trie_make(key, key_index + 1, node_size >> 1, data);
  T->nodes[0].next = t;
  if (t == NULL) 
    T->nodes[0].data = data;
  else 
    T->nodes[0].data = NULL;
  
  RETURN( T );
}


void* bz_trie_find(bz_trie* T, CHAR* key, bz_SIZE key_index)
{
  BEGIN;
  bz_SIZE i;

  assert(key != NULL);
  assert(key_index <= wcslen(key));
  assert(wcslen(key) > 0);

  for (i=0; i < T->length; i++) {

    if (T->nodes[i].c == key[key_index]) {

      // found node

      if (key[key_index + 1] == L'\0')
	RETURN( T->nodes[i].data );

      if (!T->nodes[i].next)
	RETURN( NULL );

      RETURN( bz_trie_find(T->nodes[i].next, key, key_index + 1)  );
    }
  }
  RETURN( NULL );
}

bz_trie* bz_trie_find_top(bz_trie* T, CHAR* key, bz_SIZE key_index)
{
  BEGIN;
  bz_SIZE i;

  assert(key != NULL);
  assert(key_index <= wcslen(key));
  assert(wcslen(key) > 0);

  for (i=0; i < T->length; i++) {

    if (T->nodes[i].c == key[key_index]) {

      // found node

      if (key[key_index + 1] == L'\0')
	RETURN( T );

      if (!T->nodes[i].next)
	RETURN( T );

      RETURN( bz_trie_find_top(T->nodes[i].next, key, key_index + 1)  );

    }

  }

  RETURN( T );
}

void bz_trie_graft(bz_trie* T, CHAR* key, bz_SIZE key_index, void* data)
{
  BEGIN;
  assert(key != NULL);
  assert(wcslen(key) > 0);

  if ((T->length + 1) > (T->node_array_size)) {
    /* grow T */

    T->node_array_size <<= 1;

    T->nodes = realloc( T->nodes, sizeof(bz_trie_node[T->node_array_size]));
    if (T->nodes == NULL)
      FATAL("Out of memory");
  }

  T->nodes[T->length].c = key[key_index];

  if(key[key_index + 1] == L'\0')
    T->nodes[T->length].data = data;
  else
    T->nodes[T->length].data = NULL;

  T->nodes[T->length].next = bz_trie_make(key, key_index + 1, BZ_TRIE_MIN_NODES, data);
  T->length++;
  END;
}

void bz_trie_find_and_graft(bz_trie* T, CHAR* key, bz_SIZE key_index, void* data)
{
  BEGIN;
  bz_SIZE i;

  assert(T != NULL);
  assert(key != NULL);
  assert(key_index <= wcslen(key));
  assert(wcslen(key) > 0);
  assert(T->nodes != NULL);

  for (i=0; i < T->length; i++) {

    if (T->nodes[i].c == key[key_index]) {

      // found node

      if (key[key_index + 1] == L'\0') {
	T->nodes[i].data = data;
	RETURN_VOID;
      }

      if (T->nodes[i].next == NULL) {
	T->nodes[i].next = bz_trie_make(key, key_index+1, BZ_TRIE_MIN_NODES, data);
	RETURN_VOID;
      }

      bz_trie_find_and_graft(T->nodes[i].next, key, key_index + 1, data);
      RETURN_VOID;
    }

  }

  bz_trie_graft( T, key, key_index, data);
  END;
}


#define spaces(x)   {int j;for(j=0;j<x;j++){wprintf(L"  ");};}
void bz_trie_show(bz_trie* T, int n)
{
  BEGIN;
  int i;
  assert(T);

  for(i=0;i<T->length;i++) {

    assert(T->nodes);  
    assert(&T->nodes[i]);  
    spaces(n);
    wprintf(L"%lc",T->nodes[i].c);

    if (T->nodes[i].data)
      wprintf(L"-->*");

    wprintf(L"\n");

    if (T->nodes[i].next)
      bz_trie_show(T->nodes[i].next,n+1);

  }

  END;
}

bz_trie* bz_trie_prune(bz_trie* T)
{
  BEGIN;
  if(T == NULL) 
    RETURN(NULL);

  if(T->length == 0) 
    RETURN(NULL);

  // make new node array
  // copy accross any nodes that contain data
  // delete the rest

  bz_SIZE kept = 0;
  bz_SIZE i;

  for (i=0;i<T->length;i++) {

    if (T->nodes[i].data) {
      // copy across
      T->nodes[kept].c = T->nodes[i].c;
      T->nodes[kept].data = T->nodes[i].data;
      T->nodes[kept].next = bz_trie_prune(T->nodes[i].next);
      kept++;
      continue;
    }

    if (T->nodes[i].next) {
      bz_trie* next = bz_trie_prune(T->nodes[i].next);
      if( next != NULL ) {
	// copy across
	T->nodes[kept].c = T->nodes[i].c;
	T->nodes[kept].data = NULL;
	T->nodes[kept].next = next;
	kept++;
      }
    }
  }

  if(kept == 0)
    RETURN( NULL );

  T->length = kept;  
  
  if((T->length > BZ_TRIE_MIN_NODES) && (T->length < T->node_array_size))
    T->nodes = realloc(T->nodes,sizeof(bz_trie_node) * T->length);

  RETURN( T );
}

void* bz_trie_find_and_delete(bz_trie* T, CHAR* key, bz_SIZE key_index)
{
  BEGIN;
  bz_SIZE i;

  assert(key != NULL);
  assert(key_index <= wcslen(key));
  assert(wcslen(key) > 0);

  for (i=0; i < T->length; i++) {

    if (T->nodes[i].c == key[key_index]) {

      if (T->nodes[i].data)

      // found node

      if (key[key_index + 1] == L'\0') {
	T->nodes[i].data = NULL;
	RETURN( T );
      }

      if (!T->nodes[i].next)
	RETURN( NULL );

      RETURN( bz_trie_find_and_delete(T->nodes[i].next, key, key_index + 1) );
    }
  }
  RETURN( NULL );
}

void bz_trie_delete(bz_trie* T, CHAR* key)
{
  BEGIN;
  assert(T);
  assert(key);
  assert(T->length > 0); //?
  assert(wcslen(key) > 0); //?

  // find the node
  bz_trie_find_and_delete(T, key, 0);

  //scan trie and delete all branches with no data in them
  T = bz_trie_prune(T); // prunes the lot - somewhat inneficient
  
  END;
}

bz_List* bz_trie_flatten(bz_trie* T, bz_String* s)
{
  BEGIN;

  if (T == NULL)
    RETURN( bz_EMPTY );
  
  if (T->length == 0)
    RETURN( bz_EMPTY );
  
  bz_List* L = bz_EMPTY;
  
  int i;
  for (i=0; i < T->length ;i++) {
    
    bz_String* name = bz_string_copy(s);
    bz_string_cat_wchar(name,T->nodes[i].c);
    if (T->nodes[i].data) {
      // found a name
      L = cons(name,L);
    }
    
    if (T->nodes[i].next) {
      // look for more
      L = bz_list_concat(L,bz_trie_flatten(T->nodes[i].next,name));
    }
  }
  RETURN( L );
}
