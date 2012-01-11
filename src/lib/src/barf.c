/*
 *  barf.c
 *
 *  v2.0 Created by sambeau on Mon Jan 24 2005.
 *  v1.0 Created by sambeau on Sat Jul 07 2001.
 *
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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/signal.h> // if this causes problems try just <signal.h>


#ifdef USE_GARBAGE_COLLECTOR
//#include "/usr/local/include/gc.h"
#include "/usr/include/gc/gc.h"
#define malloc(n) GC_malloc(n)
#define calloc(m,n) GC_malloc((m)*(n))
#endif


#ifdef THIS_IS_A_CGI
#include <time.h>
#endif


#include "barf.h"

/* We can't barf from barf or else we'll loop so we need a simple version */
#define SIMPLE_BARF(x) {fprintf(stderr,"[!] %s: Error in barf.c '%s'\n",prog_name,x);exit(0);}

typedef struct bz_barf_stack_node {
   void *barf_data;
   struct bz_barf_stack_node* next;
} bz_barf_stack;


bz_barf_stack *pfs;
const char* prog_name;


inline const char* bz_barf_prog_name(void) // for logs
{
   return prog_name;
}


static inline bz_barf_stack* bz_barf_stack_new()
{
   bz_barf_stack* new;

   new = malloc(sizeof(bz_barf_stack));
   if(new==NULL) 
      SIMPLE_BARF("Out of memory");

   new->barf_data = NULL;
   new->next = NULL;
   
   return new;
}


static inline bz_barf_stack* bz_barf_stack_push(bz_barf_stack* s, const char *item)
{
   bz_barf_stack* t;
   
   t = bz_barf_stack_new();

   s->barf_data = (void *)item;
   t->next = s;

   return t;
}


static inline bz_barf_stack* bz_barf_stack_pop(bz_barf_stack* s)
{		
   if(s->next == NULL)
   {
      SIMPLE_BARF("Trying to pop an empty stack");
   }
   
   s->next->barf_data = NULL;
   
   return s->next;
}

static inline char *bz_barf_stack_top(bz_barf_stack *s)
{
   return s->next->barf_data;
}


/* remove reliance on str.o */

static char* cat3(const char* s1, const char* s2, const char* s3)
{
	char* new;
	
	size_t n1;
	size_t n2;
	size_t n3;
	size_t len;
	
	n1=strlen(s1);
	n2=strlen(s2);
	n3=strlen(s3);

	len = n1 + n2 + n3;
	
	new = (char *) malloc(sizeof(char) * (len + 1));
	if(new==NULL) 
		SIMPLE_BARF ("out of memory");
 
	memcpy(new,s1,n1);
	memcpy(new+n1,s2,n2);
	memcpy(new+n1+n2,s3,n3);

	new[len]='\0';
	
	return new;
}


static inline char *bz_barf_stack_show(bz_barf_stack* s, const char *divider)
{
   char* r = (char *)"";
   char*	d;
   
   if(s->barf_data) 
   {
      d = cat3(r,divider,s->barf_data);
      r=d;
   }
   while(s->next != NULL)
   {
      s=s->next;
      if(s->barf_data)
      { 
         d = cat3(r,divider,s->barf_data);
         r=d;
      }
   }
   
   return r;
}


inline void bz_barf_push_function(const char* x)
{
   
   pfs = (bz_barf_stack*) bz_barf_stack_push(pfs,x);
}


inline void bz_barf_pop_function()
{
   
   pfs = (bz_barf_stack*) bz_barf_stack_pop(pfs);
}


int already_barfing = 0;

static void signal_handler(int sig)
{

   // try to avoid an infinite loop

   if(already_barfing) {
      exit(1);
   }

   switch (sig)
   {

   case SIGTERM:
#ifdef THIS_IS_A_CGI
      BARF("Terminated");
#else
#ifdef DEBUG
      BARF("Terminated");
#else
      // This is what Perl does:
      fprintf(stderr,"Terminated\n");
      exit(1);
#endif
#endif
      break;

   case SIGINT:
#ifdef THIS_IS_A_CGI
      BARF("Interrupted");
#else
      // most shell tools exit silently on SIGINT
      exit(1);
#endif
      break;

   case SIGBUS:
      BARF("Bus error");
      break;

   case SIGSEGV:
      BARF("Segmentation violation");
      break;

   case SIGILL:
      BARF("Illegal instruction");
      break;

   case SIGFPE:
      BARF("Floating point exception");
      break;
   }
}


static void set_signals(void)
{
   signal(SIGILL, signal_handler);
   signal(SIGFPE, signal_handler);
   signal(SIGBUS, signal_handler);
   signal(SIGSEGV, signal_handler);
   signal(SIGTERM, signal_handler);
   signal(SIGINT, signal_handler);
}


#ifdef THIS_IS_A_CGI
char* timestring;

void bz_barf_log_time(void)
{
   struct tm *ltime;
   time_t t;
   size_t bytes_written;

// Essentially, this is just a figure plucked out of my arse
// It is safe though as strftime doesn't allow buffer overflows
#define TIMESTRING_bz_SIZE 20

   t = time(NULL);
   ltime = localtime(&t);

   timestring = (char *) malloc(sizeof(char) * (TIMESTRING_bz_SIZE+1)); 
   if(timestring==NULL)
      SIMPLE_BARF("Out of memory");

// strftime doesn't allow buffer overflows
// it returns 0 if the string doesn't fit
   bytes_written = strftime(timestring,TIMESTRING_bz_SIZE,"%d %b %Y %I:%M%p",ltime);
   if(bytes_written == 0) 
      SIMPLE_BARF("Couldn't initialise log time due to potential buffer overflow. Increase TIMESTRING_bz_SIZE");
}
#endif


void bz_barf(const char* bz_barf_text)
{
   
   already_barfing = 1;

   fprintf(stderr,"\n**ERROR****************************************************************\n");
   fprintf(stderr,"Program:  %s\n", prog_name);

#ifdef THIS_IS_A_CGI		
   fprintf(stderr,"Time:     %s\n", timestring);
   fprintf(stderr,"Who:      %s\n", getenv("REMOTE_ADDR"));
#endif

   fprintf(stderr,"Error:    %s\n", bz_barf_text);
   fprintf(stderr,"In:       %s()\n", bz_barf_stack_top(pfs));
   fprintf(stderr,"Trace:    error%s\n", bz_barf_stack_show(pfs,(char *)"<-"));

   fprintf(stderr,"***********************************************************************\n");

   exit(0);
}


void bz_barf_init(const char* name)
{
   set_signals();
   prog_name = name;

#ifdef THIS_IS_A_CGI
   bz_barf_log_time();
#endif


   pfs = bz_barf_stack_new();
   
}
