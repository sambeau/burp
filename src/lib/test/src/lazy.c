#include "../../src/lazy.h"
#include "../../src/debug.h"
#include "../../src/cast.h"

#define PRINT wprintf(L"%d]",__LINE__);wprintf

int doublef(int x) {return x*2;}
int lte10(int x) {if(x<=10) return x; else return (int)bz_EMPTY;}
int lte100(int x) {if(x<=100) return x; else return (int)bz_EMPTY;}
int gte0(int x) {if(x>=0) return x; else return (int)bz_EMPTY;}

int main(int argc, char** argv)
{
  DEBUG_INIT(argv[0]);
  BEGIN;
  
  PRINT(L"-- x to y --------------------------------\n");		
  
  PRINT(L"0..0:");bz_lazy_show(bz_lazy_xtoy(0,0));wprintf(L"\n");
  PRINT(L"0..1:");bz_lazy_show(bz_lazy_xtoy(0,1));wprintf(L"\n");
  PRINT(L"1..1:");bz_lazy_show(bz_lazy_xtoy(1,1));wprintf(L"\n");

  PRINT(L"1..-1:");bz_lazy_show(bz_lazy_xtoy(1,-1));wprintf(L"\n");

  PRINT(L"1..10:");bz_lazy_show(bz_lazy_xtoy(1,10));wprintf(L"\n");
  PRINT(L"10..1:");bz_lazy_show(bz_lazy_xtoy(10,1));wprintf(L"\n");
  PRINT(L"10..-10:");bz_lazy_show(bz_lazy_xtoy(10,-10));wprintf(L"\n");

  PRINT(L"-- filter --------------------------------\n");		

  PRINT(L"double 1..10:");bz_lazy_show(bz_lazy_filter(&doublef,(bz_lazy_xtoy(1,10))));wprintf(L"\n");
  PRINT(L"1..10:");bz_lazy_show(bz_lazy_filter(&lte10,(bz_lazy_xtoy(1,20))));wprintf(L"\n");

  PRINT(L"-- stop xto --------------------------------\n");		

  PRINT(L"1..10:");bz_lazy_show(bz_lazy_filter(&lte10,(bz_lazy_xto(1))));wprintf(L"\n");
  PRINT(L"double 1..100:");bz_lazy_show(bz_lazy_filter(&doublef,bz_lazy_filter(&lte100,(bz_lazy_xto(1)))));wprintf(L"\n");
  PRINT(L"double 100..0:");bz_lazy_show(bz_lazy_filter(&doublef,bz_lazy_filter(&gte0,(bz_lazy_xdownto(100)))));wprintf(L"\n");
  
  PRINT(L"-- length --------------------------------\n");		

  PRINT(L"length 0..0:");wprintf(L"%i",bz_lazy_length(bz_lazy_xtoy(0,0)));wprintf(L"\n");
  PRINT(L"length 0..1:");wprintf(L"%i",bz_lazy_length(bz_lazy_xtoy(0,1)));wprintf(L"\n");
  PRINT(L"length 1..1:");wprintf(L"%i",bz_lazy_length(bz_lazy_xtoy(1,1)));wprintf(L"\n");

  PRINT(L"length 1..-1:");wprintf(L"%i",bz_lazy_length(bz_lazy_xtoy(1,-1)));wprintf(L"\n");

  PRINT(L"length 1..10:");wprintf(L"%i",bz_lazy_length(bz_lazy_xtoy(1,10)));wprintf(L"\n");
  PRINT(L"length 10..1:");wprintf(L"%i",bz_lazy_length(bz_lazy_xtoy(10,1)));wprintf(L"\n");
  PRINT(L"length 10..-10:");wprintf(L"%i",bz_lazy_length(bz_lazy_xtoy(10,-10)));wprintf(L"\n");

  END; exit(0);
}



