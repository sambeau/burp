#include "lib/src/string.h"
#include "lib/src/integer.h"
#include "lib/src/real.h"

void* bz_core_null(void);
void* bz_core_true(void);
void* bz_core_false(void);
void* bz_core_seq(void* x, void* y);
void* bz_core_or(void* x, void* y);
void* bz_core_and(void* x, void* y);
void* bz_core_not(void* x);
void* bz_core_if(void* x, void *y);
void* bz_core_if_else(void* x, void *y, void* z);
void* bz_core_id(char* x);
void* bz_core_string(char* x);
void* bz_core_char(char* x);
void* bz_core_tag(char* x);
void* bz_core_integer(long x);
void* bz_core_real(double x);
void* bz_core_block(char* x);
void* bz_core_add(void* x, void* y);
void* bz_core_sub(void* x, void* y);
void* bz_core_mul(void* x, void* y);
void* bz_core_div(void* x, void* y);
void* bz_core_rem(void* x, void* y);
void* bz_core_bang(void* x);
void* bz_core_pos(void* x);
void* bz_core_neg(void* x);
void* bz_core_pow(void* x, void* y);
void* bz_core_inc(void* x);
void* bz_core_dec(void* x);
void* bz_core_brackets(void* x);

