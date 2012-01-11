#include "trie.h"

typedef struct {

  bz_string* filename;
  int file;
  bz_SIZE size;
  void* contents;
  int is_writeable;
  int is_dirty;
  time_t was_cached;

} bz_cached_file;

typedef bz_dict* bz_cache;

bz_cache_init;

bz_string* bz_cache_get(bz_string* filename);
bz_cache_put;
