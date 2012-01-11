/*
 *  cast.h
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

#ifndef _H_BZ_CAST_H_
#define _H_BZ_CAST_H_


//#include "class.h"

#include "list.h"
#include "integer.h"
#include "string.h"
#include "empty.h"
#include "real.h"


/* -- integer -- */

bz_Integer*  bz_integer_to_integer(bz_Integer* I);
bz_Real*     bz_integer_to_real(bz_Integer* I);
bz_String*   bz_integer_to_string(bz_Integer* I);
bz_List*     bz_integer_to_list(bz_Integer* I);
CHAR*        bz_integer_to_wstr(bz_Integer* I);


/* -- real -- */

bz_Integer*  bz_real_to_integer(bz_Real* r);
bz_Real*     bz_real_to_real(bz_Real* r);
bz_String*   bz_real_to_string(bz_Real* r);
bz_List*     bz_real_to_list(bz_Real* r);
CHAR*        bz_real_to_wstr(bz_Real* r);


/* -- string --*/

bz_Integer*  bz_string_to_integer(bz_String* s);
bz_Real*     bz_string_to_real(bz_String* s);
bz_String*   bz_string_to_string(bz_String* s);
bz_List*     bz_string_to_list(bz_String *s);
CHAR*        bz_string_to_wstr(bz_String* e);


/* -- empty -- */

bz_Integer*  bz_empty_to_integer(bz_Empty* e);
bz_Real*     bz_empty_to_real(bz_Empty* e);
bz_String*   bz_empty_to_string(bz_Empty* e);
bz_List*     bz_empty_to_list(bz_Empty* e);
CHAR*        bz_empty_to_wstr(bz_Empty* e);

/* -- cstr -- */

CHAR* cstr_to_wstr(char *cstr);
char* wstr_to_cstr(CHAR* wstr);

#define cstr(x) cstr_to_wstr(x)
#define cstr_to_string(x) str(cstr(x))

/* -- list -- */

bz_Integer* bz_list_to_integer(bz_List* e); 
bz_Real*    bz_list_to_real(bz_List* e); 
bz_String*  bz_list_to_string(bz_List* e); 
CHAR*       bz_list_to_wstr(bz_List* e); 
bz_List*    bz_list_to_list(bz_List* e); 


#endif /* _H_BZ_CAST_H_ */

