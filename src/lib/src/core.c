#include <stdio.h>
#include <wchar.h>

#include "lib/src/empty.h"
#include "lib/src/gc.h"
#include "lib/src/string.h"
#include "lib/src/list.h"
#include "lib/src/integer.h"
#include "lib/src/real.h"
#include "lib/src/cast.h"
#include "lib/src/debug.h"

#define FALSE  EMPTY
string true = {STRING,5,4,L"true"};
#define TRUE &true


void* bz_core_null(void)
{
   BEGIN;
   RETURN( EMPTY );
}

void* bz_core_true(void)
{
   BEGIN;
   RETURN( TRUE );
}

void* bz_core_false(void)
{
   BEGIN;
   RETURN( FALSE );
}

void* bz_core_seq(void* x, void* y)
{
   BEGIN;
   //  if( ((list *)x)->class != bz_LIST ) {
   RETURN( cons(x,y) );
   //  } else {
   //    RETURN( bz_list_concat(x,y) );
   //  }
}

void* bz_core_or(void* x, void* y)
{
   BEGIN;
   
   if (bz_list_flatten(x) != EMPTY ) {
      RETURN( x );
   } else {
      RETURN( y );
   }
}

void* bz_core_and(void* x, void* y)
{
   BEGIN;
   
   if ((bz_list_flatten(x) != FALSE) && (bz_list_flatten(y) != FALSE)) {
      RETURN( TRUE );
   } else {
      RETURN( FALSE );
   }
}


void* bz_core_not(void* x)
{
   BEGIN;
   
   if ((bz_list_flatten(x) == EMPTY)) {
      RETURN( TRUE );
   }  else {
      RETURN( EMPTY );
   }
}


void* bz_core_if(void* x, void *y)
{
   BEGIN;
   
   if ((bz_list_flatten(x) == EMPTY)) { // should use a lazy flatten instead
      RETURN( EMPTY );
   } else {
      RETURN( y );
   }
}


void* bz_core_if_else(void* x, void *y, void* z)
{
   BEGIN;
   
   if (bz_list_flatten(x) == FALSE) { // should use a lazy flatten instead
      RETURN( z );
   } else {
      RETURN( y );
   }
}


void* bz_core_id(char* x)
{
   BEGIN;
   RETURN( cstr_to_string(x) );
}


void* bz_core_string(char* x)
{
   BEGIN;
   RETURN( x );
}

void* bz_core_char(char* x)
{
   BEGIN;
   RETURN( x );
}

void* bz_core_tag(char* x)
{
   BEGIN;
   RETURN( x );
}


void* bz_core_integer(long x)
{
   BEGIN;
   RETURN( int(x) );
}


void* bz_core_real(double x)
{
   BEGIN;
   RETURN( real(x) );
}


void* bz_core_block(void* x)
{
   BEGIN;
   RETURN( do_parse(wstr_to_cstr(((string*)x)->string)) );
}


void* bz_core_add(void* x, void* y)
{
   //assume int only for now
   BEGIN;
   if(((string *) x)->class != bz_INTEGER) {
      x = CAST(x,integer);
   }
   if(((string *)y)->class != bz_INTEGER) {
      y = CAST(y,integer);
   }
   RETURN( int(((integer *)x)->value + ((integer *)y)->value) );
}


void* bz_core_sub(void* x, void* y)
{
   //assume int only for now
   BEGIN;
   if(((string *) x)->class != bz_INTEGER) {
      x = CAST(x,integer);
   }
   if(((string *)y)->class != bz_INTEGER) {
      y = CAST(y,integer);
   }
   RETURN( int(((integer *)x)->value - ((integer *)y)->value) );
}

void* bz_core_mul(void* x, void* y)
{
   //assume int only for now
   BEGIN;
   if(((string *)x)->class != bz_INTEGER) {
      x = CAST(x,integer);
   }
   if(((string *)y)->class != bz_INTEGER) {
      y = CAST(y,integer);
   }
   
   RETURN( int(((integer *)x)->value * ((integer *)y)->value) );
}

void* bz_core_div(void* x, void* y)
{
   //assume int only for now
   BEGIN;
   if(((string *)x)->class == bz_INTEGER) {
      x = CAST(x,integer);
   }
   if(((string *)y)->class != bz_INTEGER) {
      y = CAST(y,integer);
   }
   
   RETURN( int(((integer *)x)->value * ((integer *)y)->value) );
}

void* bz_core_rem(void* x, void* y)
{
   //assume int only for now
   BEGIN;
   if(((string *)x)->class == bz_INTEGER) {
      x = CAST(x,integer);
   }
   if(((string *)y)->class != bz_INTEGER) {
      y = CAST(y,integer);
   }
   
   RETURN( int(((integer *)x)->value * ((integer *)y)->value) );
   
}

void* bz_core_bang(void* x)
{
   
   BEGIN;
   if ((bz_list_flatten(x) == EMPTY)) {
      RETURN( TRUE );
   }  else {
      RETURN( EMPTY );
   }
}

void* bz_core_pos(void* x)
{
   //assume int only for now
   BEGIN;
   RETURN( int(((integer *)x)->value) );
}

void* bz_core_neg(void* x)
{
   //assume int only for now
   BEGIN;
   RETURN( int(0-(((integer *)x)->value)) );
}

void* bz_core_pow(void* x)
{
   //assume int only for now
   BEGIN;
   RETURN( int(((integer *)x)->value));
}

void* bz_core_inc(void* x)
{
   //assume int only for now
   BEGIN;
   RETURN( int(((integer *)x)->value + 1) );
}

void* bz_core_dec(void* x)
{
   //assume int only for now
   BEGIN;
   RETURN( int(((integer *)x)->value - 1) );
}

void* bz_core_brackets(void* x)
{
   BEGIN;
   //  RETURN( bz_list_flatten( x ) );
   RETURN( x );
}

void* bz_core_do(void* x)
{
   BEGIN;
   RETURN( yyparse( ((string *)x)->string) );
}
