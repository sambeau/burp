/*
 *  minihash.c
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

#include <string.h>

#include "debug.h"
#include "empty.h"
#include "minihash.h"

const bz_Type bz_Minihash_type;

bz_Minihash* bz_minihash_new(void)
{
  bz_Minihash* m;
  new(bz_Minihash,m);

  return m;
}

bz_Minihash* bz_minihash_copy(bz_Minihash* m)
{
  bz_Minihash* mm;
  new(bz_Minihash,mm);
  memcpy(mm,m,sizeof(bz_Minihash));
  return m;
}



bz_SIZE bz_minihash_length(bz_Minihash* m)
{
  bz_SIZE n = 0;
  int i;

    for (i=0; i<BZ_MINIHASH_SIZE; i++)
      if(m->name[i])
	    n ++;
    
    return n;
}


bz_SIZE bz_minihash_charsize(bz_Minihash* m)
{
  bz_SIZE n = 0;
  int i;

    for (i=0; i<BZ_MINIHASH_SIZE; i++)
      if(m->name[i])
	    n += bz_string_length(m->name[i]);
    
    return n;
}



int bz_minihash_compare(bz_Minihash* x, bz_Minihash* y)
{
  return(0);
}



void bz_minihash_show(bz_Minihash* m)
{
   ;
}

 

void* bz_minihash_get(bz_Minihash* m, bz_String* name)
{
  int i;
  
  for (i=0; i<BZ_MINIHASH_SIZE; i++)
    if(m->name[i])
      if(bz_string_eq(name,m->name[i]))
	    return m->value[i];
  
  return bz_EMPTY;
}


void bz_minihash_put(bz_Minihash* m, bz_String* name, bz_String* filename, bz_SIZE line, void* value)
{
  int i;

  for (i=0; i<BZ_MINIHASH_SIZE; i++)
    if(m->name[i]) {
      if(bz_string_eq(name,m->name[i])) {	
	     m->filename[i] = filename;
	     m->line[i] = line;
	     m->value[i] = value;
	     return;
      }
    }
    else {
      m->name[i] = name;
      m->filename[i] = filename;
      m->line[i] = line;
      m->value[i] = value;
      return;
    }
  
  FAIL("Hash is full");

  /* failure - should error at this point */
}

bz_String* bz_minihash_get_filename(bz_Minihash* m, bz_String* name)
{
  int i;
  
  for (i=0; i<BZ_MINIHASH_SIZE; i++)
    if(m->name[i]) 
      if(bz_string_eq(name,m->name[i]))
	    return m->filename[i];
  
  
  return bz_EMPTY;
}


bz_SIZE bz_minihash_get_line(bz_Minihash* m, bz_String* name)
{
  int i;
  
  for (i=0; i<BZ_MINIHASH_SIZE; i++)
    if(m->name[i]) 
      if(bz_string_eq(name,m->name[i]))
	    return m->line[i];
  
  return 0;
}

void bz_minihash_delete(bz_Minihash* m, bz_String* name)
{
  int i;
  
  for (i=0; i<BZ_MINIHASH_SIZE; i++)
    if(m->name[i]) 
      if(bz_string_eq(name,m->name[i])) {
	    m->name[i]=NULL;
	    return;
      }
  /* return(error("name doesn't exist")) */
}




const bz_Type bz_Minihash_type = {

   /* name */      L"Minihash",
   /* size */      sizeof(bz_Minihash),

   /* new */       (const void*)  &bz_minihash_new,

   /* copy */      (const void*)  &bz_minihash_copy,
   /* length */    (const void*)  &bz_minihash_length,
   /* charsize */  (const void*)  &bz_minihash_charsize,   

   NULL, 
   NULL, NULL, NULL, NULL
};
