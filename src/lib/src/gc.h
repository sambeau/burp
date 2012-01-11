/*
 *  gc.h
 *
 *  - Garbage Collecting replacements for malloc & calloc
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


#ifndef _GC_H_
#define _GC_H_

#ifdef USE_GARBAGE_COLLECTOR

#include "/usr/include/gc/gc.h"
//#include "/usr/local/include/gc.h"

#define malloc(n)    GC_malloc(n)
#define calloc(m,n)  GC_malloc((m)*(n))
#define realloc(m,n) GC_realloc(m,n)

/* allocate something with no pointers in it */
#define malloc_atomic(n)    GC_malloc(n)

/* allocate something huge (>100k) */
#define malloc_huge(n)      GC_malloc(n)

#else

#include  <stdlib.h>

#define malloc_atomic(n)    malloc(n)
#define malloc_huge(n)      malloc(n)

#endif

#endif /* _GC_H_ */

