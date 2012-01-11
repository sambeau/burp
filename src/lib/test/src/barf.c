#include "../../src/barf.h"

int main()
{
   int i;
   bz_BARF_INIT("barf");

   bz_BAF;   
   for(i=0;i<100000;i++){
      bz_BAF;   
      bz_BIF;
   }

   for(i=0;i<100000;i++){
      bz_BAF;   
   }

   for(i=0;i<100000;i++){
      bz_BIF;   
   }

   bz_BIF;

   exit(0);
}


