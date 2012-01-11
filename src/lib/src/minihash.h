/*
 *  minihash.h
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


#ifndef _H_bz_MINIHASH_H_
#define _H_bz_MINIHASH_H_

#include "size.h"
#include "class.h"
#include "cast.h"
#include "string.h"


/**
 ** A minihash is just a linearly searched array with a small
 ** number of entries. Hopefully it will be plenty fast enough
 ** for small hashes (which are by far the most common).
 ** I have a hunch (but don't know for sure) that in most
 ** cases they will be faster than a full blown hash.
 ** Only testing can tell..
 **
 ** The intention is that once a minihash grows to fill all its 
 ** buckets we upgrade it to a 'real' hash.
 **
 ** And if an alias to the name-value pair is needed we upgrade the lot..
 **
 ** Although assignments will be slower..
 **
 **/

/**
 ** And the results are?
 ** minihashes are much slower than tries even for a small dictionary 
 **
 ** trie: 3.32s  vs  minihash8: 4.69s = 146%
 **
 ** Thus Minhashes will be dropped :-(
 **/
  
#define BZ_MINIHASH_SIZE 32 /* 16? just a guess - need to test for best size*/

/* no nvp - just as simple as we can get */

typedef struct {

  const    bz_Type *type;

  bz_String*  name[BZ_MINIHASH_SIZE];
  void*       value[BZ_MINIHASH_SIZE];

  bz_String*  filename[BZ_MINIHASH_SIZE];
  bz_SIZE        line[BZ_MINIHASH_SIZE];

} bz_Minihash;


#define bz_MINIHASH &bz_minihash_type


bz_Minihash*  bz_minihash_new(void);
bz_Minihash*  bz_minihash_copy(bz_Minihash* m);

bz_SIZE       bz_minihash_length(bz_Minihash* m);
bz_SIZE       bz_minihash_charsize(bz_Minihash* m);

int        bz_minihash_compare(bz_Minihash* x, bz_Minihash* y);

void       bz_minihash_show(bz_Minihash* m); 

void*      bz_minihash_get(bz_Minihash* m, bz_String* name);
void       bz_minihash_put(bz_Minihash* m, bz_String* name, bz_String* filename, bz_SIZE line, void* value);

void       bz_minihash_delete(bz_Minihash* m, bz_String* name);

bz_String*    bz_minihash_get_filename(bz_Minihash* m, bz_String* name);
bz_SIZE       bz_minihash_get_line(bz_Minihash* m, bz_String* name);

#define    get(h,n)            bz_minihash_get(h,n)
#define    put(h,n,v)          bz_minihash_put(h,n,str(cstr_to_wstr(__FILE__)),__LINE__,v)
#define    get_filename(h,n)   bz_minihash_get_filename(h,n)
#define    get_line(h,n)       bz_minihash_get_line(h,n)
#define    delete(h,n)         bz_minihash_delete(h,n)

#define    val(x)       ((void *)x)

#endif /* _bz_MINIHASH_H_ */

