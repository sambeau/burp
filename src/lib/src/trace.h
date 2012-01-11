/*
 *  trace.h
 *
 *
 * Simple trace log
 * Produces a file called trace.log 
 * Use perl script 'prof' to produce statistics
 *
 *  v2.0 Created by sambeau on Mon Jan 25 2005.
 *  v1.0 Created by sambeau on Thu Feb 26 2004.
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


#ifndef __BZ_TRACE_H__
#define __BZ_TRACE_H__


#ifdef TRACE

void bz_trace_init(const char* prog_name);
void bz_trace_push(const char *file, const char* function);
void bz_trace_pop(void);

#define  bz_TRACE_INIT(x)  bz_trace_init(x)
#define  bz_TAF            bz_trace_push(__FILE__,__PRETTY_FUNCTION__)
#define  bz_TIF            bz_trace_pop()
#define  bz_TOF(X)         bz_trace_push(__FILE__,X)

#else

#define  bz_TRACE_INIT(x)
#define  bz_TAF     
#define  bz_TIF     
#define  bz_TOF(x)  

#endif /* TRACE */

#endif /* __BZ_TRACE_H__ */
