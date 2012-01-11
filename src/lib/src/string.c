/*
 *  string.c
 *
 *	stringy strings
 *
 *  Created by sambeau on Fri Nov 09 2001.
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

 */
 
 
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <wchar.h>

#include "gc.h"
#include "debug.h"
#include "string.h"
#include "cast.h"

/* BZ_STRING_KNICKER_bz_SIZE
 * the minimum/increment to allocate buffer by
 */
#define	BZ_STRING_KNICKER_bz_SIZE	16

const bz_Type bz_String_type = {

   /* name      */ L"String",
   /* size      */ sizeof(bz_String),

   /* new       */ (const void*)  &bz_string_new,

   /* copy      */ (const void*)  &bz_string_copy,
   /* length    */ (const void*)  &bz_string_length,
   /* charsize  */ (const void*)  &bz_string_length,   /* (same as length) */

   /* compare   */ (const void*) &bz_string_compare,

   /* to_int    */  (const void*) &bz_string_to_integer,
   /* to_real   */  (const void*) &bz_string_to_real,
   /* to_String */  (const void*) &bz_string_to_string,
   /* to_list   */  (const void*) &bz_string_to_list,

   /* to_wstr   */  (const void*) &bz_string_to_wstr,
   /* show      */  (const void*) &bz_string_show


};


/*---------------------------------------------------------------------------*/


/*	
 * bz_string_new():
 *  make a new string from wstr s
 *  or return blank one from string(NULL)
 *
 */ 
 
bz_String* bz_string_new(CHAR *s)
{
  bz_String* e;
  BEGIN;  

  if(s)
    {
      bz_SIZE n = wcslen(s);
      bz_SIZE new_buffersize = n + 1;

      new(bz_String, e);

      e->string = (CHAR *) malloc(sizeof(CHAR) * new_buffersize);
      if(e->string == NULL)
	FATAL("Out of Memory");
      
      wcscpy(e->string,s);
      e->buffer_size = new_buffersize;
      e->length = n;
    }
  else
    {
      new(bz_String,e);

      e->string = (CHAR *) malloc(sizeof(CHAR) * BZ_STRING_KNICKER_bz_SIZE);
      if(e->string == NULL)
	FATAL("Out of Memory");
      
      e->string[0] = L'\0';
      e->buffer_size = BZ_STRING_KNICKER_bz_SIZE;
      e->length=0;
    }
  RETURN( e );
}


static bz_String* bz_string_new_buffersize(bz_SIZE n)
{
  // assumes n already has the +1
  bz_String* e;
  BEGIN;  

  new(bz_String,e);
  
  e->string = malloc(sizeof(CHAR) * (n));
  if(e->string == NULL)
    FATAL("Out of Memory");
  
  e->string[0] = L'\0';
  e->buffer_size = n;
  e->length = 0;
  
  RETURN( e );
}


/*	
 * bz_string_stretch():
 * increase the size of a string
 *
 */ 

static void bz_string_stretch(bz_String* e, bz_SIZE new_size)
{
  BEGIN;

  //  e->buffer_size = BZ_STRING_KNICKER_bz_SIZE;
  while(e->buffer_size <= new_size) // new_size must already account +1 for L'\0'
    e->buffer_size = e->buffer_size << 1; // double up
  
  e->string = (CHAR *) realloc(e->string, sizeof(CHAR) * e->buffer_size);
  if(e->string == NULL)
    FATAL("Out of Memory");

  END;
}


/*	
 * bz_string_cat_wstr():
 * concatenate a wstr onto a string
 *
 */ 
 
void bz_string_cat_wstr(bz_String* e, CHAR* s)
{
  BEGIN;
  bz_SIZE n = wcslen(s);

  if ((n + e->length + 1) > e->buffer_size) // +1 takes null into account
    {
      // buffer is too small, make it bigger
      (void) bz_string_stretch(e, e->length + n + 1);		
    }		
  // buffer is big enough, so copy it in

(void) wmemcpy(
		&e->string[e->length],// no +1 as we want to write over L'\0'
		s, 
		(n+1)); // +1 as we want to take the L'\0' along too
  
  e->length += n;
  assert(e->length < e->buffer_size);      
  END;
}


/*	
 * bz_string_charcat():
 * concatenate a char onto man string
 *
 */ 
 
void bz_string_cat_wchar(bz_String* e, CHAR c)
{
  BEGIN;	
  if ((e->length + 2) > e->buffer_size) // < takes null into account
  {
    // buffer is too small, make it bigger
    (void) bz_string_stretch(e, e->length + 2);		
  }		
  // buffer is big enough, so copy it in
  e->string[e->length]=c;
  e->length++; // move along now
  assert(e->length < e->buffer_size); 
  e->string[e->length]=L'\0';
  END;
}


/*	
 * bz_string_cat():
 * make a new string by joining two together
 *
 */ 
 
static bz_String* bz_string_cat2(bz_String* e1, bz_String* e2)
{
  BEGIN;
  
  bz_SIZE n = e1->length + e2->length;
  bz_String* e = bz_string_new_buffersize(n+1);

  // buffer is big enough, so copy it in

  (void) wmemcpy(e->string, 
		e1->string, 
		e1->length); // no +1 as we want to blat the '\0'
  
  (void) wmemcpy(&e->string[e1->length],
		e2->string, 
		(e2->length+1)); // take the '\0' too
  
  e->length = n;
  
  RETURN( e );
}


/*	
 * bz_string_cat():
 * make a new string by joining two together
 *
 */ 
 
bz_String* bz_string_copy(bz_String* e1)
{
  BEGIN;
  
  bz_SIZE n = e1->length;

  //  Why doesn't this work?:-
  bz_String* e = bz_string_new_buffersize(e1->length + 1);

  //    bz_String* e = bz_string_new_buffersize(e1->buffer_size);

  // buffer is big enough, so copy it in
  
  (void) wmemcpy(e->string, 
		e1->string, 
		(n+1)); // take the '\0' too
  
  e->length = n;
  
  RETURN( e );
}


/*	
 * bz_string_length():
 * return the size of a string
 *
 */ 
 
bz_SIZE bz_string_length(bz_String* e)
{
  BEGIN;
  RETURN( e->length );
}


bz_String* _bz_string_wstr_cat(CHAR *s, ...)
{
  va_list ap;

  BEGIN;

  bz_String* e = bz_string_new(NULL);

  va_start(ap,s);
  while (NULL != s) {
    bz_string_cat_wstr(e,s);
    s = va_arg(ap,CHAR*);
  }
  va_end(ap);

  RETURN(e);
}


bz_String* _bz_string_cat(bz_String* e, ...)
{
  va_list ap;

  BEGIN;

  bz_String* E = bz_string_new(NULL);

  va_start(ap,e);
  while (NULL != e) {
    E = bz_string_cat2(E,e);
    e = va_arg(ap,bz_String*);
  }
  va_end(ap);

  RETURN(E);
}


int bz_string_compare(bz_String* e1, bz_String* e2)
{
  BEGIN;
  RETURN(wcscmp(e1->string,e2->string));
}

/*---------------------------------------------------------------------------*/
/* Copyright (C) 1991, 1992, 1995, 1996, 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <wctype.h>
#include <wchar.h>

#ifndef weak_alias
# define __wcscasecmp wcscasecmp
# define TOLOWER(Ch) towlower (Ch)
#else
# ifdef USE_IN_EXTENDED_LOCALE_MODEL
#  define __wcscasecmp __wcscasecmp_l
#  define TOLOWER(Ch) __towlower_l ((Ch), loc)
# else
#  define TOLOWER(Ch) towlower (Ch)
# endif
#endif

#ifdef USE_IN_EXTENDED_LOCALE_MODEL
# define LOCALE_PARAM , loc
# define LOCALE_PARAM_DECL __locale_t loc;
#else
# define LOCALE_PARAM
# define LOCALE_PARAM_DECL
#endif

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.  */
int
__wcscasecmp (s1, s2 LOCALE_PARAM)
     const wchar_t *s1;
     const wchar_t *s2;
     LOCALE_PARAM_DECL
{
  wint_t c1, c2;

  if (s1 == s2)
    return 0;

  do
    {
      c1 = TOLOWER (*s1++);
      c2 = TOLOWER (*s2++);
      if (c1 == L'\0')
	break;
    }
  while (c1 == c2);

  return c1 - c2;
}
#ifndef __wcscasecmp
weak_alias (__wcscasecmp, wcscasecmp)
#endif

/*---------------------------------------------------------------------------*/

int bz_string_compare_ignorecase(bz_String* e1, bz_String* e2)
{
  BEGIN;
  RETURN(wcscasecmp(e1->string,e2->string));
}


int bz_string_eq(bz_String* e1, bz_String* e2)
{
  BEGIN;
  bz_SIZE n1,n2,i;

  n1 = e1->length;
  n2 = e2->length;

  if(n1 != n2)
    RETURN( 0 );

  for(i=0;i<n1;i++) 
    if(e1->string[i] != e2->string[i]) 
      RETURN( 0 );

  /* otherwise */   
  RETURN( 1 );
}


void bz_string_show(bz_String* s)
{
  assert(s);
  assert(s->type == bz_STRING );
  assert(s->string[s->length] == L'\0');

  fputws(s->string,stdout);
}
