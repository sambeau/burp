/*
 *  debug.h
 *
 *
 *  v1.0 Created by sambeau on Mon Jan 24 2005.
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
 
#ifndef __BZ_DEBUG_H__
#define __BZ_DEBUG_H__


/*
 * DEBUG only does its stuff in debug mode
 *
 */
#include <assert.h>

#include "barf.h"

#define FATAL(x) BARF(x)
#define FAIL(x)  BARF(x)

#ifdef DEBUG

#include "trace.h"

/*
 * PIF, PAF & POF
 *
 * POF(x) - push function x onto trace stacks
 * PAF    - push current function onto trace stacks
 * PIF    - pop last entry on the trace stacks
 *
 */

#define DEBUG_INIT(x)      {bz_BARF_INIT(x);bz_TRACE_INIT(x);}
#define POF(x)             {bz_BOF(x);bz_TOF(x);}
#define PAF                {bz_BAF;bz_TAF;}
#define PIF                {bz_TIF;bz_BIF;}
#define BEGINF(x)          {bz_BOF(x);bz_TOF(x);}
#define BEGIN              {bz_BAF;bz_TAF;}
#define END                {bz_TIF;bz_BIF;}
#define RETURN(x)          {bz_TIF;bz_BIF;return (x);}
#define RETURN_VOID        {bz_TIF;bz_BIF;return;}

#define _(x)               {fprintf(stderr,"[%s]",#x);fflush(stderr);}
#define _i(x)              {fprintf(stderr,"[%i]",x);fflush(stderr);}
#define _s(x)              {fprintf(stderr,"[%s]",x);fflush(stderr);}
//#define _L(x)            {wfprintf(stderr,L"[%ls]",x);fflush(stderr);}

#else

#define NDEBUG

#define DEBUG_INIT(x) 	
#define POF(x) 		
#define PAF			
#define PIF	
#define BEGINF(x) 		
#define BEGIN			
#define END
#define RETURN(x)       return (x)
#define RETURN_VOID     return
			
#define _(x)

#endif /* DEBUG */

#endif /* __BZ_DEBUG_H__ */
