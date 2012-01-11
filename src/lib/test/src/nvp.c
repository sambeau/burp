#include "../../src/nvp.h"
#include "../../src/debug.h"
#include "../../src/cast.h"

#define PRINT wprintf(L"%d]",__LINE__);wprintf

int main(int argc, char** argv)
{
  bz_Nvp* n;

  DEBUG_INIT(argv[0]);
  BEGIN;
  
  PRINT(L"-- nvp --------------------------------\n");		
  
  n = bz_nvp_new(str(L"Basil"), (void *)8525);
  PRINT(L"class:");wprintf(L"%ls=%i",wstr(n->name),(int)n->value);wprintf(L"\n");

  /*
bz_nvp_length(nvp* xs);
bz_nvp_charsize(nvp* xs);
bz_nvp_show(nvp *xs);
bz_nvp_copy(nvp* xs);
  */
  END; exit(0);
}

