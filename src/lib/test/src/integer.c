#include "../../src/debug.h"
#include "../../src/integer.h"
#include "../../src/string.h"
#include "../../src/cast.h"

#define PRINT wprintf(L"%d]",__LINE__);wprintf

int main(int argc, char** argv)
{

  bz_Integer* I;
  bz_Integer* J;
  
  DEBUG_INIT(argv[0]);
  BEGIN;
  
  PRINT(L"--basic values-------\n");
 
  I = int(65536);
  PRINT(L"65536:" INTF L"\n",I->value);

  J = bz_integer_copy(I);
  PRINT(L"65536:" INTF L"\n",J->value);

  PRINT(L"--length-------\n");
   
  PRINT(L"1:" bz_SIZEF L"\n",bz_integer_length(I));
  PRINT(L"1:" bz_SIZEF L"\n",bz_integer_length(J));

  PRINT(L"--charsize-------\n");

  PRINT(L"5:" bz_SIZEF L"\n",bz_integer_charsize(I));
  PRINT(L"5:" bz_SIZEF L"\n",bz_integer_charsize(J));

  PRINT(L"--comparison-------\n");
  
  PRINT(L"0:" L"%i\n",bz_integer_compare(int(0),int(0)));
  PRINT(L"1:" L"%i\n",bz_integer_compare(int(1),int(0)));
  PRINT(L"-1:" L"%i\n",bz_integer_compare(int(0),int(1)));

  PRINT(L"0:" L"%i\n",bz_integer_compare(int(65536),int(65536)));

  PRINT(L"--basic negative values-------\n");

  I = int(-65536);
  PRINT(L"-65536:" INTF L"\n",I->value);

  J = bz_integer_copy(I);
  PRINT(L"-65536:" INTF L"\n",J->value);
   
  PRINT(L"--length of negative values-------\n");

  PRINT(L"1:" bz_SIZEF L"\n",bz_integer_length(I));
  PRINT(L"1:" bz_SIZEF L"\n",bz_integer_length(J));

  PRINT(L"--charsize of negative values-------\n");

  PRINT(L"6:" bz_SIZEF L"\n",bz_integer_charsize(I));
  PRINT(L"6:" bz_SIZEF L"\n",bz_integer_charsize(J));
  
  PRINT(L"--comparison of negative values-------\n");

  PRINT(L"0:" L"%i\n",bz_integer_compare(int(-0),int(-0)));
  PRINT(L"-1:" L"%i\n",bz_integer_compare(int(-1),int(0)));
  PRINT(L"1:" L"%i\n",bz_integer_compare(int(0),int(-1)));
  PRINT(L"0:" L"%i\n",bz_integer_compare(int(-1),int(-1)));

  PRINT(L"--comparison of big values-------\n");

  PRINT(L"0:" L"%i\n",bz_integer_compare(int(999999999),int(999999999)));
  PRINT(L"0:" L"%i\n",bz_integer_compare(int(-999999999),int(-999999999)));

  PRINT(L"--integer_to_charsize-------\n");

  PRINT(L"10 = %d\n",bz_integer_charsize(int(-999999999)));
  PRINT(L"9 = %d\n",bz_integer_charsize(int(-99999999)));
  PRINT(L"8 = %d\n",bz_integer_charsize(int(-9999999)));
  PRINT(L"7 = %d\n",bz_integer_charsize(int(-999999)));
  PRINT(L"6 = %d\n",bz_integer_charsize(int(-99999)));
  PRINT(L"5 = %d\n",bz_integer_charsize(int(-9999)));
  PRINT(L"4 = %d\n",bz_integer_charsize(int(-999)));
  PRINT(L"3 = %d\n",bz_integer_charsize(int(-99)));
  PRINT(L"2 = %d\n",bz_integer_charsize(int(-9)));
  PRINT(L"1 = %d\n",bz_integer_charsize(int(0)));
  PRINT(L"1 = %d\n",bz_integer_charsize(int(1)));
  PRINT(L"2 = %d\n",bz_integer_charsize(int(10)));
  PRINT(L"3 = %d\n",bz_integer_charsize(int(100)));
  PRINT(L"4 = %d\n",bz_integer_charsize(int(1000)));
  PRINT(L"5 = %d\n",bz_integer_charsize(int(10000)));
  PRINT(L"6 = %d\n",bz_integer_charsize(int(100000)));
  PRINT(L"7 = %d\n",bz_integer_charsize(int(1000000)));
  PRINT(L"8 = %d\n",bz_integer_charsize(int(10000000)));
  PRINT(L"9 = %d\n",bz_integer_charsize(int(100000000)));
  PRINT(L"10 = %d\n",bz_integer_charsize(int(1000000000)));
  
  {
    INTV i;

    PRINT(L"--integer_to_wstr-------\n");

    i=1000000;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=100000;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=10000;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=1000;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=100;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=10;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=1;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=0;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=-9;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=-99;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=-999;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=-9999;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=-99999;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=-999999;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=-9999999;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=-99999999;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));
    i=-999999999;I=int(i);PRINT(INTF L" = %ls\n",i,bz_integer_to_wstr(I));

    PRINT(L"--integer_show-------\n");

    i=10000000;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=1000000;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=100000;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=10000;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=1000;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=100;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=10;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=1;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=0;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=-9;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=-99;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=-999;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=-9999;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=-99999;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=-999999;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=-9999999;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=-99999999;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
    i=-999999999;I=int(i);PRINT(INTF L" = ",i);bz_integer_show(I);wprintf(L"\n");
  }

  {
    bz_String *s;

    PRINT(L"--integer_to_string / string_length vs integer_charsize-------\n");

    I = int(-99); s = bz_integer_to_string(I); PRINT(L"3=" bz_SIZEF L"=" bz_SIZEF L"\n",bz_string_length(s),bz_integer_charsize(I));
    I = int(-9); s = bz_integer_to_string(I); PRINT(L"2=" bz_SIZEF L"=" bz_SIZEF L"\n",bz_string_length(s),bz_integer_charsize(I));
    I = int(0); s = bz_integer_to_string(I); PRINT(L"1=" bz_SIZEF L"=" bz_SIZEF L"\n",bz_string_length(s),bz_integer_charsize(I));

    I = int(1); s = bz_integer_to_string(I); PRINT(L"1=" bz_SIZEF L"=" bz_SIZEF L"\n",bz_string_length(s),bz_integer_charsize(I));
    I = int(10); s = bz_integer_to_string(I); PRINT(L"2=" bz_SIZEF L"=" bz_SIZEF L"\n",bz_string_length(s),bz_integer_charsize(I));
    I = int(999); s = bz_integer_to_string(I); PRINT(L"3=" bz_SIZEF L"=" bz_SIZEF L"\n",bz_string_length(s),bz_integer_charsize(I));
  }

  PRINT(L"-- string to integer -------\n");
  bz_Integer* D;
  D = bz_string_to_integer(str(L"-1"));PRINT(L"-1:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"0"));PRINT(L"0:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"1"));PRINT(L"1:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"32768"));PRINT(L"32768:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"65536"));PRINT(L"65536:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"0xf"));PRINT(L"0xf:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"0xff"));PRINT(L"0xff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"0xfff"));PRINT(L"0xfff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"0xffff"));PRINT(L"0xffff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"0xfffff"));PRINT(L"0xfffff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"0xffffff"));PRINT(L"0xffffff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"0xfffffff"));PRINT(L"0xfffffff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"-0xfffffff"));PRINT(L"-0xfffffff:" INTF L"\n",D->value);
  //  D = bz_string_to_integer(str(L"-0xffffffff"));PRINT(L"-0xfffffff:" INTF L"\n",D->value); // overflow
  D = bz_string_to_integer(str(L"-0xffffff"));PRINT(L"-0xffffff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"-0xfffff"));PRINT(L"-0xfffff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"-0xffff"));PRINT(L"-0xffff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"-0xfff"));PRINT(L"-0xfff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"-0xff"));PRINT(L"-0xff:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"-0xf"));PRINT(L"-0xf:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"-0x00000000"));PRINT(L"-0x00000000:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"0x00000000"));PRINT(L"0x00000000:" INTF L"\n",D->value);
  D = bz_string_to_integer(str(L"000000000"));PRINT(L"000000000:" INTF L"\n",D->value);
//  D = bz_string_to_integer(str(L""));PRINT(L"0?:" INTF L"\n",D->value);
//  D = bz_string_to_integer(str(L"-"));PRINT(L"0?:" INTF L"\n",D->value);
//  D = bz_string_to_integer(str(L"1-1-1"));PRINT(L"0?:" INTF L"\n",D->value);
//  D = bz_string_to_integer(str(L"arse"));PRINT(L"1?:" INTF L"\n",D->value);
//  D = bz_string_to_integer(str(L"!\"$%^&*"));PRINT(L"0?:" INTF L"\n",D->value);
//  D = bz_string_to_integer(str(L"\\\\"));PRINT(L"0?:" INTF L"\n",D->value);

  END; exit(0);

}

