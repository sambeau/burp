/*
 *  cast.c
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


#include <math.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <errno.h>

#include "debug.h"
#include "cast.h"


/* - - integer - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


bz_Integer* bz_integer_to_integer(bz_Integer* I) 
{
  BEGIN; 
  RETURN( I );
}


bz_Real* bz_integer_to_real(bz_Integer* I) 
{
  BEGIN; 
  RETURN( real((bz_REALV) I->value) );
}


bz_String* bz_integer_to_string(bz_Integer* I) 
{
  BEGIN; 
  RETURN( bz_string_new(bz_integer_to_wstr(I)) );
}


bz_List* bz_integer_to_list(bz_Integer* I) 
{
  BEGIN; 
  RETURN( cons(I,bz_EMPTY) );
}

/*
need to convert to something like this!:
     wchar_t *
     itow (unsigned long int val)
{
  static wchar_t buf[30];
  wchar_t *wcp = &buf[29];
  *wcp = L'\0';
  while (val != 0)
    {
      *--wcp = btowc ('0' + val % 10);
      val /= 10;
    }
  if (wcp == &buf[29])
    *--wcp = L'0';
  return wcp;
}

 */

CHAR* bz_integer_to_wstr(bz_Integer* I) 
{
  BEGIN;
  INTV v = I->value;
  INTV n = bz_INTEGER_CHAR_SIZE(I) + 1; /* +1 for the NULL char */


  CHAR* s = malloc(sizeof(CHAR) * n);
  if(s == NULL)
    FATAL("Out of Memory");

  if(swprintf(s,n,INTF,v) == -1) {
    FATAL("Could not convert integer to string");
  }


  RETURN(s);
}


/* - - real - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


bz_Integer*  bz_real_to_integer(bz_Real* r)
{
  BEGIN; 
  RETURN( int((INTV)r->value) );
}

bz_Real* bz_real_to_real(bz_Real* r)
{
    BEGIN; RETURN( r );
}

bz_String* bz_real_to_string(bz_Real* r)
{
  BEGIN; RETURN( str(bz_real_to_wstr(r)) );  
}

bz_List* bz_real_to_list(bz_Real* r)
{
  BEGIN; RETURN( cons(r,bz_EMPTY) );
}

CHAR* bz_real_to_wstr(bz_Real* r)
{
  CHAR* s;
  bz_SIZE size;
  BEGIN;

  if(NULL == r) 
    FATAL("real is not defined");
  
  size = bz_real_charsize(r) + 1; /* +1 for null */
  
  s = malloc(sizeof(CHAR) * (size));
  if(s == NULL) {
    FATAL("Out of Memory");
  }
  
  if(swprintf(s,size,bz_REALF,r->value) == -1) {
    FATAL("Could not convert real to string");
  }

  RETURN(s);
}


/* - - string - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


bz_Integer* bz_string_to_integer(bz_String* s)
{
  /*
   * see: http://www.gnu.org/software/libc/manual/html_node/Parsing-of-Integers.html
   */
  BEGIN;
  CHAR *error;
  errno = 0;
  bz_Integer* I  = int( wcstol(s->string, &error , 0) );
  if(errno){
    // this will catch an overflow but overlook garbage
    // eg "arse"=>0, "123bum"=>123
    FATAL ("bz_Integer too long");
  }
  RETURN( I );
}


bz_Real* bz_string_to_real(bz_String* s)
{
  /* TODO: put some proper error checking in here!
   * 
   * see: http://www.gnu.org/software/libc/manual/html_node/Parsing-of-Floats.html
   */
  BEGIN; 
  CHAR *error;
  errno = 0;
  bz_Real* R = real( wcstod(s->string,&error) );
  if(errno) {
    FATAL ("bz_Real too long");
  }
  RETURN( R );
}


bz_String* bz_string_to_string(bz_String* s)
{
  BEGIN; RETURN( s );
}


bz_List* bz_string_to_list(bz_String* s)
{
  BEGIN; RETURN( cons(s,bz_EMPTY) );
}


CHAR* bz_string_to_wstr(bz_String* e)
{	
  BEGIN; RETURN( e->string );
}



/* - - empty - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


bz_Integer* bz_empty_to_integer(bz_Empty* e) 
{
  BEGIN; RETURN( int(0) );
}


bz_Real* bz_empty_to_real(bz_Empty* e) 
{
  BEGIN; RETURN( real((bz_REALV)0.0) );
}


bz_String* bz_empty_to_string(bz_Empty* e) 
{
  return str(L"");
}


CHAR* bz_empty_to_wstr(bz_Empty* e) 
{
  return L"";
}


bz_List* bz_empty_to_list(bz_Empty* e) 
{
  return (bz_List*)e;
}


/* - - cstr - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

CHAR* cstr_to_wstr(char *cstr)
{
	CHAR *wstr;  
	size_t wstrlength;
	
	BEGIN;
	
	wstrlength = mbstowcs(NULL,cstr,0);	// run through once to find buffer size	
	wstr = malloc(sizeof(CHAR)*(wstrlength + 1));
	
	wstrlength = mbstowcs(wstr, cstr, wstrlength);
	if (wstrlength < 0)
		BARF("Unreadable UTF-8 string");

	wstr[wstrlength]=L'\0';
	
	RETURN( wstr );
}

char* wstr_to_cstr(CHAR* wstr)
{
  char *cstr;
  size_t cstrlength;

  BEGIN;

 	
 	cstrlength = wcstombs(NULL,wstr,0);	// run through once to find buffer size
	cstr = malloc(sizeof(char)*(cstrlength + 1));

	cstrlength = wcstombs(cstr, wstr, cstrlength);
	if (cstrlength < 0){
		printf("oops!");
		BARF("Unreadable string");
	}
	cstr[cstrlength]='\0';

  	RETURN( cstr );
}

/* - - list - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bz_Integer* bz_list_to_integer(bz_List* e) 
{
  BEGIN;
  RETURN( (bz_Integer *) CAST(e->node,integer) );
}


bz_Real* bz_list_to_real(bz_List* e) 
{
  BEGIN; RETURN( bz_integer_to_real(bz_list_to_integer(e)) );
}


bz_String* bz_list_to_string(bz_List* e) 
{
  BEGIN;
  bz_List* e1 =  bz_list_flatten(e);
  bz_String* s = bz_string_new(NULL);
  while (e1 && e1 != bz_EMPTY) {    
    s = bz_string_cat(s,CAST(e1->node,string));
    e1 = e1->next;
  }
  RETURN( s );
}


CHAR* bz_list_to_wstr(bz_List* e) 
{
  BEGIN;
  bz_String*s = bz_list_to_string(e);
  RETURN (s->string);
}


bz_List* bz_list_to_list(bz_List* e) 
{
  return e;
}
