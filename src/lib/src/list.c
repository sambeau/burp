/*
 *  list.c
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

#include <stdarg.h>

#include "debug.h" 
#include "empty.h"
#include "list.h"
#include "integer.h"
#include "cast.h"

/*

typedef struct
{

  const wchar_t* name;
  const size_t   size;

  const void* (*new)();

  const void* (*clone)();
  const int   (*length)();
  const int   (*charsize)();

  const int   (*compare)();

  const void* (*to_integer)();
  const void* (*to_real)();
  const void* (*to_string)();
  const void* (*to_list)();

  const void* (*to_wstr)();
  const void* (*show)();



} class;

 */

void type_default(void)
{
  FATAL("Missing method");
}

const bz_Type bz_List_type = {

   /* name */      L"List",
   /* size */      sizeof(bz_List),

   /* new */       (const void*)  &bz_list_new,

   /* copy */      (const void*)  &bz_list_copy,
   /* length */    (const void*)  &bz_list_length,
   /* charsize */  (const void*)  &bz_list_charsize,   

   /* compare */   (const void *) &bz_list_compare,

   /* to_int */    (const void *) &bz_list_to_integer,
   /* to_real */   (const void *) &bz_list_to_real,
   /* to_string */ (const void *) &bz_list_to_string,
   /* to_list */   (const void *) &bz_list_to_list,
   
   /* to_wstr */   (const void *) &bz_list_to_wstr,

   /* show */      (const void *) &bz_list_show

};


bz_List* bz_list_new(void)
{
//   bz_List* xs;

   BEGIN;

//   new(bz_List,xs);

//   xs->next  = bz_EMPTY;
//   xs->node  = bz_EMPTY;

   RETURN(bz_EMPTY);
}


inline bz_List* bz_list_cons(bz_List* xs, void* x)
{
   bz_List* ys;

   BEGIN;

   new(bz_List,ys);

   ys->node = x;
   ys->next = xs;

   RETURN(ys);
}


bz_SIZE bz_list_length(bz_List* xs)
// how many elements
{
   BEGIN;

   assert(xs);
   if (xs == bz_EMPTY) {
      RETURN(0);
   }

   assert(xs->next);
   RETURN(1 + bz_list_length(xs->next));
}


bz_SIZE bz_list_charsize(bz_List* xs)
// how many characters when flattened
{
   int n = 0;

   BEGIN;

   n = CALL_METHOD(xs->node,charsize);

   RETURN(n);

}


bz_List* bz_list_copy(bz_List* xs)
{
  BEGIN;

  if(xs != bz_EMPTY) {
    RETURN(cons(xs->node,bz_list_copy(xs->next)));
  } else { 
    RETURN(bz_EMPTY);
  }
}


static inline int cmp(void* x, void* y) {
  // we need to cast types at this point
  BEGIN;
  RETURN(COMPARE(x,y));
}


static bz_List* merge(bz_List* xxs, bz_List* yys)
{
  /* merge([ ], ys)        = ys 
   * merge(xs, [ ])        = xs 
   * merge([x:xs], [y:ys]) = if x <= y
   *                         then [ x : merge(xs, [y:ys]) ]
   *                         else [ y : merge([x:xs], ys) ]
   */

  BEGIN;
  assert(xxs);
  assert(yys);

  if (xxs == bz_EMPTY) RETURN(yys);

  /* else */

  if (yys == bz_EMPTY) RETURN(xxs);  

  /* else */

  void* x = xxs->node;
  void* y = yys->node;

  assert(x);
  assert(y);

  if(cmp(x,y) <= 0) {

    bz_List* xs = xxs->next;
    assert(xs);
    //    assert(xs != bz_EMPTY);
    RETURN(cons ( x , merge (xs , yys)));    

  } else {

    bz_List* ys = yys->next;
    assert(ys);
    //    assert(ys != bz_EMPTY);
    RETURN(cons ( y , merge (xxs , ys)));

  }
  
}


static inline void splitAt(int n, bz_List* xs, bz_List** as, bz_List** bs)
{
  bz_List* aas;

  BEGIN;

  *as = bz_list_copy(xs);
  aas = *as;

  while (n && (aas != bz_EMPTY)) {
    aas = aas->next;
    n--;
  }

  if (aas != bz_EMPTY) { 
    *bs = aas->next;
    aas->next = bz_EMPTY;
  }

  END;
}


bz_List* bz_list_mergesort(bz_List* xs)
{
/*
 * mergesort([ ])        = [ ]
 *
 * mergesort([x])        = [x]
 *
 * mergesort(xs)         = let (as, bs) = splitAt(length(xs) # 2, xs)
 *                         in merge(mergesort(as), mergesort(bs))
 */
  BEGIN;

  if(xs == bz_EMPTY) RETURN(xs);

  if(xs->next == bz_EMPTY) RETURN(xs);

  {
    bz_List* as = bz_EMPTY;
    bz_List* bs = bz_EMPTY;

    splitAt((bz_list_length(xs)/2)-1,xs,&as,&bs);
   
    RETURN(merge(bz_list_mergesort(as),bz_list_mergesort(bs)));
  }
}


void bz_list_show(bz_List* xs)
{
  BEGIN;

  assert(xs);
//  wprintf(L"[xs type:%ls]",xs->type->name);
  assert((xs->type == bz_LIST) || (xs == bz_EMPTY));

  while (xs != bz_EMPTY) {
  
    assert(xs->node);
    assert(((bz_List* )xs->node)->type);

//    if( ((bz_List* )xs->node)->type == bz_LIST ) {
//      bz_list_show(xs->node); // why do I need this?
//    } else {
//  assert(((bz_String*)xs->node)->type->name);
//  wprintf(L"[node type:%ls]",((bz_String*)xs->node)->type->name);

      SHOW(xs->node); // is this somehow broken?
//    }
    
    assert(xs->next);
    xs = xs->next;

    assert(xs);
  }

  END;
}


void bz_list_debug_show(bz_List* xs)
{
  BEGIN;

  assert(xs);
  wprintf(L"[%ls:%i]",xs->type->name,bz_list_length(xs));fflush(0);
  assert((xs->type == bz_LIST) || (xs == bz_EMPTY));

  while ( xs != bz_EMPTY ) {
    assert(xs->node);

    if (((bz_String*)xs->node)->type == bz_STRING) {
      wprintf(L"-->[%ls:%ls]",((bz_String*)xs->node)->type->name,((bz_String*)xs->node)->string);fflush(0);
    } else if (((bz_String*)xs->node)->type == bz_INTEGER) {
      wprintf(L"-->[%ls:%ld]",((bz_String*)xs->node)->type->name,((bz_Integer*)xs->node)->value);fflush(0);
    } else {
      wprintf(L"-->[%ls]",((bz_String*)xs->node)->type->name,xs->node);fflush(0);
    }
    
    xs = xs->next;
    assert(xs);
  }
    wprintf(L"-->[/]");fflush(0);
  END;
}


static bz_List* _bz_list_of_args( bz_List* xs, void* x, va_list ap)
{
  BEGIN;

  if(x) {
    BEGINF("va_arg");
    void* y = va_arg(ap,void*);
    END;
    RETURN(cons(x, _bz_list_of_args( xs, y, ap)));
  } else {
    RETURN(bz_EMPTY);
  }

}


bz_List* _bz_list_of(void *x, ...)
{
  bz_List* xs;
  va_list ap;

  BEGIN;

  xs = bz_list_new();
  BEGINF("va_start");
  va_start(ap,x);
  END;
  xs = _bz_list_of_args(xs,x,ap);
  va_end(ap);  

  RETURN(xs);
}


bz_List* bz_list_concat(bz_List* xs, bz_List* ys) 
{
  assert(xs != NULL);
  assert(ys != NULL);

  BEGIN;

  if (xs == bz_EMPTY) {
    if (ys == bz_EMPTY) {
      RETURN( bz_EMPTY );
    }
    else {
      RETURN( ys );
    }
  }

  if (ys==bz_EMPTY)	
    RETURN( xs );

  assert(xs->node);
  assert(xs->next);

  RETURN( cons(xs->node, bz_list_concat(xs->next,ys)) );
}


bz_List* bz_list_flatten(bz_List* xs)
{
  BEGIN;
  /* we need a lazier version of this */
  assert(xs);

  if (xs == bz_EMPTY) {
    RETURN( bz_EMPTY );
  }
  if (xs->type != bz_LIST) {
    RETURN( cons(xs,bz_EMPTY) );
  }
 
  if (xs->node == bz_EMPTY) {
    RETURN( bz_list_flatten(xs->next) );
  }

  RETURN( bz_list_concat(bz_list_flatten(xs->node),bz_list_flatten(xs->next)) );
}


int bz_list_compare(bz_List* xs, bz_List*  ys)
{
  BEGIN;
  /*
   flatten list and do a while loop
   while 0 (eq) keep checking
   return first non zero (not eq)
   *
   this is another place where a lazy flatten would be good
   */
  if(xs == bz_EMPTY) {
    if(ys == bz_EMPTY)
      RETURN( 0 );
    RETURN( -1 );
  }
  if(ys == bz_EMPTY)
    RETURN( 1 );

  bz_List* xxs = bz_list_flatten(xs);
  bz_List* yys = bz_list_flatten(ys);

  /* non-recursive style */
  int cmp=0;
  assert(((bz_String*)xxs->node)->type == ((bz_String*)yys->node)->type);
  while ( xxs && yys ) {

    if(xxs == bz_EMPTY) {
      if(yys == bz_EMPTY)
	RETURN( 0 );
      RETURN( -1 );
    }
    if(yys == bz_EMPTY)
      RETURN( 1 );
    
    if(((bz_String*)xxs->node)->type != ((bz_String*)yys->node)->type)
      FATAL("comparing different things");
    /* should we do a cast here? */
    /* or should we generate a proper error here */
    
    cmp = COMPARE(xxs->node,yys->node);
    if (cmp != 0) RETURN( cmp );
    
    xxs = xxs->next;
    yys = yys->next;

  }
  RETURN( cmp );
}


bz_List* bz_list_reverse(bz_List* xs)
{
  BEGIN;
  
  bz_List* ys = bz_EMPTY;
  while ( xs != bz_EMPTY )
    {
      ys = cons(xs->node,ys);
      xs = xs->next;
    }
  
  RETURN( ys );
}
