#include "../../src/debug.h"
#include "../../src/real.h"
#include "../../src/string.h"
#include "../../src/cast.h"

#define PRINT wprintf(L"%d]",__LINE__);wprintf

int main(int argc, char** argv)
{

  bz_Real* R;
  
  DEBUG_INIT(argv[0]);
  BEGIN;
  
  PRINT(L"--basic values-------\n");
 
  R = real(0);
  PRINT(L"0: " bz_REALF "\n",R->value);

  R = real(1);
  PRINT(L"1: " bz_REALF "\n",R->value);

  R = real(-1);
  PRINT(L"-1: " bz_REALF "\n",R->value);

  R = real(3.1415926535897932384);
  PRINT(L"3.141593: " bz_REALF "\n",R->value);

  R = real(22.0/7.0);
  PRINT(bz_REALF L": " bz_REALF "\n",22.0/7.0,R->value);

  PRINT(L"--real to wstr-------\n");

  R = real(0);
  PRINT(L"0: %ls\n",bz_real_to_wstr(R));
  R = real(1);
  PRINT(L"1: %ls\n",bz_real_to_wstr(R));
  R = real(-1);
  PRINT(L"-1: %ls\n",bz_real_to_wstr(R));
  R = real(3.1415926535897932384);
  PRINT(L"3.141593: %ls\n",bz_real_to_wstr(R));
  R = real(1.0/3.0);
  PRINT(L"0.333333: %ls\n",bz_real_to_wstr(R));

  PRINT(L"--bz_real_length-------\n");

  PRINT(L"1: %i\n",bz_real_length(real(1.123456)));
  PRINT(L"1: %i\n",bz_real_length(real(-12.123456)));
  PRINT(L"1: %i\n",bz_real_length(real(123.123456)));
  PRINT(L"1: %i\n",bz_real_length(real(-1234.123456)));
  PRINT(L"1: %i\n",bz_real_length(real(12345.123456)));
  PRINT(L"1: %i\n",bz_real_length(real(-123456.123456)));

  PRINT(L"--bz_real_charsize-------\n");

  PRINT(L"8: %i\n",bz_real_charsize(real(0)));
  PRINT(L"9: %i\n",bz_real_charsize(real(-1)));
  PRINT(L"8: %i\n",bz_real_charsize(real(1.123456)));
  PRINT(L"9: %i\n",bz_real_charsize(real(12.123456)));
  PRINT(L"10: %i\n",bz_real_charsize(real(123.123456)));
  PRINT(L"11: %i\n",bz_real_charsize(real(1234.123456)));
  PRINT(L"12: %i\n",bz_real_charsize(real(12345.123456)));
  PRINT(L"13: %i\n",bz_real_charsize(real(123456.123456)));
  PRINT(L"9: %i\n",bz_real_charsize(real(-1.123456)));
  PRINT(L"10: %i\n",bz_real_charsize(real(-12.123456)));
  PRINT(L"11: %i\n",bz_real_charsize(real(-123.123456)));
  PRINT(L"12: %i\n",bz_real_charsize(real(-1234.123456)));
  PRINT(L"13: %i\n",bz_real_charsize(real(-12345.123456)));
  PRINT(L"14: %i\n",bz_real_charsize(real(-123456.123456)));
  
  PRINT(L"--bz_real_compare-------\n");

  PRINT(L"0: %i\n",bz_real_compare(real(0),real(0)));
  PRINT(L"0: %i\n",bz_real_compare(real(0.00001),real(0.00001)));
  PRINT(L"1: %i\n",bz_real_compare(real(0.000001),real(0)));
  PRINT(L"-1: %i\n",bz_real_compare(real(0),real(0.000001)));

  PRINT(L"--bz_real_copy-------\n");

  PRINT(L"1: ");
  bz_real_show(bz_real_copy(real(1)));
  wprintf(L"\n");

  R=real(0);
  PRINT(L"0: ");
  bz_real_show(bz_real_copy(R));
  wprintf(L"\n");

  R=real(0.1);
  PRINT(L"0.100000: ");
  bz_real_show(bz_real_copy(R));
  wprintf(L"\n");

  R=real(-0.1);
  PRINT(L"-0.100000: ");
  bz_real_show(bz_real_copy(R));
  wprintf(L"\n");

  R = real(1.0/3.0);
  PRINT(L"0.333333: ");
  bz_real_show(bz_real_copy(R));
  wprintf(L"\n");

  PRINT(L"--string_to_real-------\n");
  {
    bz_Real* R;
    R = bz_string_to_real(str(L"0"));PRINT(L"0:"bz_REALF"\n",R->value);
    R = bz_string_to_real(str(L"0.0"));PRINT(L"0:"bz_REALF"\n",R->value);
    R = bz_string_to_real(str(L"1.0"));PRINT(L"0:"bz_REALF"\n",R->value);
    R = bz_string_to_real(str(L"-1.0"));PRINT(L"0:"bz_REALF"\n",R->value);
    R = bz_string_to_real(str(L"0.000001"));PRINT(L"0:"bz_REALF"\n",R->value);
    R = bz_string_to_real(str(L"-0.000001"));PRINT(L"0:"bz_REALF"\n",R->value);
    R = bz_string_to_real(str(L"1.11111111111111111"));PRINT(L"0:"bz_REALF"\n",R->value);
    R = bz_string_to_real(str(L"3.141592653589793"));PRINT(L"0:"bz_REALF"\n",R->value);
    R = bz_string_to_real(str(L"99999999.999999"));PRINT(L"0:"bz_REALF"\n",R->value);
  }
  END;
  exit(0);
}
