/*
 *  lazy.c
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
#include "lazy.h"
#include "integer.h"

const bz_Type bz_Lazy_type;

bz_Lazy* bz_lazy_new(const bz_Lazy*  (*next)(),void* arg)
{
   // will we ever call this?
   BEGIN;
   RETURN((bz_Lazy* )next(arg));
}


bz_SIZE bz_lazy_length(bz_Lazy* xs)
// how many elements
{
   int n = 0;
   
   BEGIN;
   
   while((xs != bz_EMPTY) && (xs->next != bz_EMPTY)) {
      n++;
      xs = xs->next(xs->arg);
   }
   
   RETURN(n);
}


bz_SIZE bz_lazy_charsize(bz_Lazy* xs)
// how many characters when flattened
{
   int n = 0;
   
   BEGIN;
   
   n = CALL_METHOD(xs->node,charsize);
   
   RETURN(n);
   
}


bz_Lazy* bz_lazy_copy(bz_Lazy* xs)
{
   BEGIN;
   
   RETURN(bz_EMPTY);   
}


void bz_lazy_show(bz_Lazy* xs)
{
   if(xs != bz_EMPTY) {
      wprintf(L"%i",(int)xs->node);
      bz_lazy_show(xs->next(xs->arg));
   }
}


/* -- xto ------------------------------------ */

bz_Lazy* bz_lazy_xto(int n)
{
   bz_Lazy* xs;
   xs = malloc(sizeof(bz_Lazy));
   xs->type = bz_LAZY;
   xs->node = (void*)n;
   xs->next = (void*)&bz_lazy_xto;
   xs->arg = (void*)n+1;
   return xs;
}

bz_Lazy* bz_lazy_xdownto(int n)
{
   bz_Lazy* xs;
   xs = malloc(sizeof(bz_Lazy));
   if(!xs) FATAL("Out of memory");
   xs->type = bz_LAZY;
   xs->node = (void*)n;
   xs->next = (void*)&bz_lazy_xdownto;
   xs->arg = (void*)n-1;
   return xs;
}


/* -- xtoy ----------------------------------- */

typedef struct {
   int x;
   int y;
} xtoy_arg;

static bz_Lazy* _xtoy(xtoy_arg* arg)
{
   xtoy_arg* new_arg;
   bz_Lazy* xs;
   
   if(arg->x <= arg->y) {
      
      new_arg = malloc(sizeof(xtoy_arg));
      if(!new_arg) FATAL("Out of memory");
      
      new_arg->x = arg->x+1;
      new_arg->y = arg->y;
      
      xs = malloc(sizeof(bz_Lazy));
      
      xs->type = bz_LAZY;
      xs->node = (void*)arg->x;
      xs->next = (void*)&_xtoy;
      xs->arg = new_arg;
      
      return xs;
   } 
   else return bz_EMPTY;
}

static bz_Lazy* _xdowntoy(xtoy_arg* arg)
{
   xtoy_arg* new_arg;
   bz_Lazy* xs;
   
   if(arg->x >= arg->y) {
      
      new_arg = malloc(sizeof(xtoy_arg));
      if(!new_arg) FATAL("Out of memory");
      
      new_arg->x = arg->x-1;
      new_arg->y = arg->y;
      
      xs = malloc(sizeof(bz_Lazy));
      if(!xs) FATAL("Out of memory");
      
      xs->type = bz_LAZY;
      xs->node = (void*)arg->x;
      xs->next = (void*)&_xdowntoy;
      xs->arg = new_arg;
      
      return xs;
   } 
   else return bz_EMPTY;
}

bz_Lazy* bz_lazy_xtoy(int x, int y)
{
   xtoy_arg* arg;
   
   arg = malloc(sizeof(xtoy_arg));
   if (!arg) FATAL("Out of memory");
   
   arg->x = x;
   arg->y = y;
   //  return _xtoy(arg);
   
   if (x>=y)
      return _xdowntoy(arg);
   else
      return _xtoy(arg);
   
   
}

/* -- filter ----------------------------------- */

typedef struct {
  void* (*f)();
   void* xs;
} filter_arg;

bz_Lazy* _filter(filter_arg* arg)
{
   
   /* return */
   filter_arg* new_arg;
   bz_Lazy* xs;
   
   /* args */
   bz_Lazy* ys = arg->xs;
   void* (*f)() = arg->f;
   
   void* fx;
   
   if(ys != bz_EMPTY) {
      fx =f(ys->node);
      if(fx != bz_EMPTY) {
	 xs = malloc(sizeof(bz_Lazy));
	 if(!xs) FATAL("Out of memory");
	 
	 xs->type = bz_LAZY;
	 xs->node = fx;
	 xs->next = (void*)&_filter;
	 
	 new_arg = malloc(sizeof(filter_arg));
	 
	 new_arg->f = f;
	 new_arg->xs = ys->next(ys->arg);
	 xs->arg = new_arg;
	 
	 return xs;
      } 
      else return bz_EMPTY;
   }
   else return bz_EMPTY;
}

bz_Lazy* bz_lazy_filter(void* f, bz_Lazy* xs)
{
   filter_arg* arg = malloc(sizeof(arg));
   if(!arg) FATAL("Out of memory");
   
   arg->f = f;
   arg->xs = xs;
   return _filter(arg);
}

/* -- file ----------------------------------- */

/* files will be mmaped - so we only need lazy strings */


/* -- lazy class ----------------------------------- */
/*
  
typedef struct 
{
   const char* name;
   const size_t size;

   const void* (*new)();

   const void* (*clone)();
   const bz_SIZE  (*length)();
   const bz_SIZE  (*charsize)();
   
   const int   (*compare)();
   
   const void* (*to_int)();
   const void* (*to_real)();
   const void* (*to_string)();
   const void* (*to_lazy)();
   
} class;

 */

const bz_Type bz_lazy_type = {
   
   /* name */      L"Lazy",
   /* size */      sizeof(bz_Lazy),
   
   /* new */       (const void*)  &bz_lazy_new,
   
   /* copy */      (const void*)  &bz_lazy_copy,
   /* length */    (const void*)  &bz_lazy_length,
   /* charsize */  (const void*)  &bz_lazy_charsize,   
   
   NULL, 
   NULL, NULL, NULL, NULL
};


