/*
 *  barf.h
 *
 *
 *  v2.0 Created by sambeau on Mon Jan 24 2005.
 *  v1.0 Created by sambeau on Sat Jul 07 2001.
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

#include <stdlib.h>
#include <stdio.h>

 
#ifndef __BZ_BARF_H__
#define __BZ_BARF_H__


extern char* bz_timestring; // tsk! global!

#ifdef DEBUG

/*
 * BARF only does its stuff in debug mode
 *
 */

const char* bz_barf_prog_name(void); // for logs
void        bz_barf_push_function(const char* x);
void        bz_barf_pop_function();
void        bz_barf(const char* barf_text);
void        bz_barf_init();
void        bz_barf_log_time(void);

#define  bz_BARF_INIT(x)   bz_barf_init(x)
#define  BARF(x)           bz_barf(x)
#define  bz_BOF(x)         bz_barf_push_function(x)
#define  bz_BAF            bz_barf_push_function(__PRETTY_FUNCTION__)
#define  bz_BIF            bz_barf_pop_function()


#else


#define  bz_BARF_INIT(x)   bz_barf_init(x)
#define  BARF(x)           {(void)fprintf(stderr,"\n**ERROR: %s**\n",x);exit(1);}
#define  bz_BOF(x) 		
#define  bz_BAF			
#define  bz_BIF				


#endif /* DEBUG */


#endif /* __BZ_BARF_H__ */
