/*
 *  class.h
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
 
/* No not real classes - just faked-up ones */

#ifndef _H_BZ_TYPE_H_
#define _H_BZ_TYPE_H_

#include <stddef.h>
#include "barf.h"

typedef struct
{
  const wchar_t* name;
  const size_t   size;

  const void* (*new)();

  const void* (*clone)();
        int   (*length)();
        int   (*charsize)();
 
        int   (*compare)();

  const void* (*to_integer)();
  const void* (*to_real)();
  const void* (*to_string)();
  const void* (*to_list)();

  const void* (*to_wstr)();
  const void* (*show)();

} bz_Type;

typedef struct
{
   const bz_Type* type;

} bz_node;

#define CALL_METHOD(object,method)  ((bz_Type *)((bz_node *)object)->type)->method(object)
#define COMPARE(object_1,object_2)  ((bz_Type *)((bz_node *)object_1)->type)->compare(object_1,object_2)
#define SHOW(x) CALL_METHOD(x,show);
#define CAST(x,type) (void *)CALL_METHOD(x,to_##type)

#define   new(_t_,_x_) \
_x_ = malloc(sizeof(_t_)); \
if(!_x_) FATAL("Out of memory"); \
_x_->type = &_t_##_type


#endif /* _H_BZ_TYPE_H_ */

