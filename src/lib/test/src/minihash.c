#include "../../src/minihash.h"
#include "../../src/debug.h"
#include "../../src/cast.h"
#include "../../src/string.h"

#define PRINT wprintf(L"%d]",__LINE__);wprintf

int main(int argc, char** argv)
{
  DEBUG_INIT(argv[0]);
  BEGIN;
  PRINT(L"-- minihash --------------------------------\n");		
  {  
    bz_Minihash* m;
    m = bz_minihash_new();

    PRINT(L"class: ");wprintf(L"%ls",m->type->name);wprintf(L"\n");
    
    put(m,str(L"x"),val(1));
    put(m,str(L"y"),val(2));
    put(m,str(L"z"),val(3));
    
    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    
    PRINT(L"x=1: ");wprintf(L"%i",(int)get(m,str(L"x")));wprintf(L"\n");
    PRINT(L"x=2: ");wprintf(L"%i",(int)get(m,str(L"y")));wprintf(L"\n");
    PRINT(L"x=3: ");wprintf(L"%i",(int)get(m,str(L"z")));wprintf(L"\n");
    
    put(m,str(L"x"),val(1));
    put(m,str(L"y"),val(2));
    put(m,str(L"z"),val(3));
    
    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    
    PRINT(L"x=1: ");wprintf(L"%i",(int)get(m,str(L"x")));wprintf(L"\n");
    PRINT(L"y=2: ");wprintf(L"%i",(int)get(m,str(L"y")));wprintf(L"\n");
    PRINT(L"z=3: ");wprintf(L"%i",(int)get(m,str(L"z")));wprintf(L"\n");
    
    put(m,str(L"x"),val(10));
    put(m,str(L"y"),val(20));
    put(m,str(L"z"),val(30));
    
    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    
    PRINT(L"x=10: ");wprintf(L"%i",(int)get(m,str(L"x")));wprintf(L"\n");
    PRINT(L"y=20: ");wprintf(L"%i",(int)get(m,str(L"y")));wprintf(L"\n");
    PRINT(L"z=30: ");wprintf(L"%i",(int)get(m,str(L"z")));wprintf(L"\n");
    
    put(m,str(L"sam"),val(L"SAM"));
    put(m,str(L"was"),val(L"WAS"));
    put(m,str(L"here"),val(L"HERE"));
    
    PRINT(L"sam=SAM: ");wprintf(L"%ls",(char*)get(m,str(L"sam")));wprintf(L"\n");
    PRINT(L"was=WAS: ");wprintf(L"%ls",(char*)get(m,str(L"was")));wprintf(L"\n");
    PRINT(L"here=HERE: ");wprintf(L"%ls",(char*)get(m,str(L"here")));wprintf(L"\n");
    
    PRINT(L"sam defined at: ");
    wprintf(L"file:%ls line:%i",bz_string_to_wstr(get_filename(m,str(L"sam"))),get_line(m,str(L"sam")));
    wprintf(L"\n");
    
    PRINT(L"was defined at: ");
    wprintf(L"file:%ls line:%i",bz_string_to_wstr(get_filename(m,str(L"was"))),get_line(m,str(L"was")));
    wprintf(L"\n");
    
    PRINT(L"here defined at: ");
    wprintf(L"file:%ls line:%i",bz_string_to_wstr(get_filename(m,str(L"here"))),get_line(m,str(L"here")));
    wprintf(L"\n");
    
    
  }
  {
    bz_Minihash* m = bz_minihash_new();

    put(m,str(L"00"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"01"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"02"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"03"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"04"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"05"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"06"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"07"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"08"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"09"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"10"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"11"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"12"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"13"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"14"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"15"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"16"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"17"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"18"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"19"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"20"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"21"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"22"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"23"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"24"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"25"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"26"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"27"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"28"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"29"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"30"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    put(m,str(L"31"),val(0));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");

    delete(m,str(L"31"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"30"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"29"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"28"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"27"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"26"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"25"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"24"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"23"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"22"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"21"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"20"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");

    delete(m,str(L"19"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"18"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"17"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"16"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"15"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"14"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"13"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"12"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"11"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");
    delete(m,str(L"10"));    PRINT(L"length: ");wprintf(L"%i",bz_minihash_length(m));wprintf(L"\n");

    PRINT(L"00: ");wprintf(L"%i",(int)(get(m,str(L"00")) == bz_EMPTY));wprintf(L"\n");
    PRINT(L"10: ");wprintf(L"%i",(int)(get(m,str(L"10")) == bz_EMPTY));wprintf(L"\n");

  }

  END; exit(0);
}

