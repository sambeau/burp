#include<stdio.h>

#include "../../src/debug.h"

void test1(int i) 
{
   int x,y,z;
   PAF;
   for(x=0;x<i;x++){
      for(y=0;y<i;y++){
         z=y;
      }
   }
   PIF;
}


void test2(int i) 
{
   int x,y,z;
   PAF;
   for(x=0;x<i;x++){
      for(y=0;y<i;y++){
         z = y;
      }
   }
   PIF;
}



int main(void)
{
   int i;

   DEBUG_INIT("debug_test");

   PAF;

   for(i=0;i<100;i++)
      test1(i);

   for(i=0;i<100;i++)
      test2(i);

   PIF;

   exit(0);
}

