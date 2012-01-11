#include <stdlib.h>
#include "../../src/trace.h"

void test1(int i) 
{
   int x,y,z;
   bz_TAF;
   for(x=0;x<i;x++){
      for(y=0;y<i;y++){
         z = y/(x+1);
      }
   }
   bz_TIF;
}

void test2(int i) 
{
   int x,y,z;
   bz_TAF;
   for(x=0;x<i;x++){
      for(y=0;y<i;y++){
         z = y+(x+1);
      }
   }
   bz_TIF;
}

int main(void)
{
   int i,j;
   bz_TRACE_INIT("trace");

   for(j=1;j<=20;j++) {

     char name[] = "loop_00";
     name[5] = (char)(j/10)+'0';
     name[6] = (char)(j%10)+'0';
     bz_TOF(name);
     
     for(i=0;i<100;i++)
       test1(i);
     
     for(i=0;i<100;i++)
       test2(i);
     
     bz_TIF;
   }

   for(j=1;j<=20;j++) {

     char name[] = "loop_00";
     name[5] = (char)(j/10)+'0';
     name[6] = (char)(j%10)+'0';

     bz_TOF(name);
     
     for(i=0;i<j;i++)
       test1(i);
     
     for(i=0;i<j;i++)
       test2(i);
     
   }
   
   for(j=1;j<=20;j++) {
     bz_TIF;
   }
   
   exit(0);
}

