/*
 *  string.h
 *
 *	elastic strings
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
 *
 */


#ifndef _H_BZ_STRING_H_
#define _H_BZ_STRING_H_

#include <wchar.h>

#include "class.h"
#include "list.h"
#include "size.h"

#define CHAR wchar_t

typedef struct {
  
  const bz_Type* type;
  bz_SIZE buffer_size;
  bz_SIZE length;
  CHAR *string;
  
} bz_String;

const bz_Type bz_String_type;

#define bz_STRING  &bz_String_type

#define  str    bz_string_new
#define  wstr   bz_string_to_wstr

bz_String*      bz_string_new(CHAR* s);
bz_String*      bz_string_copy(bz_String* e);
bz_SIZE         bz_string_length(bz_String* e);

int          bz_string_compare(bz_String* e1, bz_String* e2);
int          bz_string_compare_ignorecase(bz_String* e1, bz_String* e2);

int          bz_string_eq(bz_String* e1, bz_String* e2);

void         bz_string_cat_wstr(bz_String* e, CHAR* s);
void         bz_string_cat_wchar(bz_String* e, CHAR c);

void         bz_string_show(bz_String* s);

bz_String*      _bz_string_wstr_cat(CHAR* s, ...);
bz_String*      _bz_string_cat(bz_String* e, ...);

#define      bz_string_wstr_cat(s, ...)   _bz_string_wstr_cat(s, __VA_ARGS__, NULL)
#define      bz_string_cat(e, ...)        _bz_string_cat(e, __VA_ARGS__, NULL)

#endif /*_H_BZ_STRING_H_*/
