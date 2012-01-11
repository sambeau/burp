/*
 *  trace.c
 *
 * simple trace log - profile with prof
 *
 *  v2.0 Created by sambeau on Tue Jan 25 2005.
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "trace.h"


#ifdef USE_GARBAGE_COLLECTOR
#include "gc.h"
#endif


const char* prog_name;

/* Lets not rely on barf as this is very useful as it stands */
#define SIMPLE_BARF(x) {fprintf(stderr,"[!] %s: Error in trace.c '%s'\n",prog_name,x);exit(0);}

typedef struct bz_trace_rec {

  const char *file;
  const char *function;
  struct timeval start;
  struct timeval stop;
  long tot_time;
  long tot_child_time;
  struct bz_trace_rec *prev;

} bz_trace_stack;

bz_trace_stack *tstack;
FILE *bz_trace_log_file;
static struct timezone tz;

void bz_trace_init(const char* pn)
{
   prog_name = pn;
   bz_trace_log_file = fopen("trace.log","w+");
   if(bz_trace_log_file == NULL)
      SIMPLE_BARF("Could not open trace.log");
   tstack = NULL;
}

void bz_trace_cleanup(void)
{
  fclose(bz_trace_log_file);
}

void bz_trace_log(const char* file, const char* function,long time1,long time2)
{
  fprintf(bz_trace_log_file,"%s\t\t%s\t\t%12li\t\t%12li\n",file,function,time1,time2);
}

void bz_trace_push(const char *file, const char* function)
{
  bz_trace_stack *ts;
  ts = malloc(sizeof(bz_trace_stack));
  if (!ts) SIMPLE_BARF("Out of memory");
  ts->file = file;
  ts->function = function;
  ts->tot_child_time = 0;

  // move the stack along
  ts->prev = tstack;
  tstack = ts;

  // do this last
  gettimeofday(&ts->start,&tz);
}

void bz_trace_pop(void)
{
  bz_trace_stack *ts;
  ts = tstack;

   if (ts) {
      
      gettimeofday(&ts->stop,&tz); // stop the clock first
      ts->tot_time = 
         ((long)ts->stop.tv_sec*1000000 + (long)ts->stop.tv_usec) 
            - ((long)ts->start.tv_sec * 1000000 + (long)ts->start.tv_usec);
          
      bz_trace_log(ts->file, ts->function, ts->tot_time, ts->tot_time - ts->tot_child_time);
      
      tstack = ts->prev; // rewind
      if (tstack) {
         tstack->tot_child_time += ts->tot_time;
      }

#ifndef USE_GARBAGE_COLLECTOR      
      free(ts);
#endif
  
   } else {
    // error - hit the buffers
     SIMPLE_BARF("Tried to pop an empty trace stack");
   }
}

void bz_trace_dump(FILE *file)
{
  bz_trace_stack *ts;

  ts = tstack;

  if (ts) {
    
    fprintf(file,"error!");
    
    while (ts) {
      fprintf(file,"<-%s/%s()",ts->file,ts->function);
      ts=ts->prev;
    }
    
    fprintf(file,"\n");
  }
}

