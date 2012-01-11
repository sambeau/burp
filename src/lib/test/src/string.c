#include "../../src/string.h"
#include "../../src/debug.h"
#include "../../src/cast.h"

#define PRINT wprintf(L"%d]",__LINE__);wprintf

int main(int argc, char** argv)
{
	int i;
	bz_String* e;
	bz_String* e2;
	
	DEBUG_INIT(argv[0]);
	BEGIN;

	e = bz_string_new(NULL);
	PRINT(L"0:%d\n", e->length);
	for(i=0;i<1000;i++)
	  bz_string_cat_wstr(e, L"0123456789");

	PRINT(L"10000:%d\n", e->length);

	e = str(L"Hello, World!");
	PRINT(L"Hello, World!:%ls\n",wstr(e));

	e = bz_string_wstr_cat(L"Hello", L", ", L"World", L"!");
	PRINT(L"Hello, World!:%ls\n",wstr(e));

	e = bz_string_wstr_cat(L"",L"");
	PRINT(L"(emptystring):%ls\n",wstr(e));

	e = bz_string_cat(str(L"Hello"), str(L", "), str(L"World"), str(L"!"));
	PRINT(L"Hello, World!:%ls\n",wstr(e));

	e = bz_string_cat(str(L""), str(L""));
	PRINT(L"(emptystring:)%ls\n",wstr(e));

	PRINT(L"--str_wstr_cat--buffer size--------------------------------\n");		

	e = bz_string_wstr_cat(
			    L"012345678901234567890123",
			    L"012345678901234567890123012345678901234567890123",
			    L"012345678901234567890123012345678901234567890123"
			    L"012345678901234567890123012345678901234567890123",
			    L"012345678901234567890123012345678901234567890123"
			    L"012345678901234567890123012345678901234567890123"
			    L"012345678901234567890123012345678901234567890123"
			    L"012345678901234567890123012345678901234567890123"
			    );
	PRINT(L"360 numbers:%ls\n",wstr(e));
	PRINT(L"buffer size:%d\n", e->buffer_size);
	PRINT(L"360:%d\n", e->length);

	PRINT(L"--str_wstr_cat--string length--------------------------------\n");		
	e = bz_string_wstr_cat(
			    L"0123456789",
			    L"0123456789",
			    L"0123456789",
			    L"0123456789",
			    L"0123456789",
			    L"0123456789",
			    L"0123456789",
			    L"0123456789",
			    L"0123456789",
			    L"0123456789"
			    );
	PRINT(L"100 numbers:%ls\n",wstr(e));
	PRINT(L"buffer size:%d\n", e-> buffer_size);
	PRINT(L"100:%d\n", e->length);

	PRINT(L"--string_copy--------------------------------\n");		

	e2 = bz_string_copy(e);

	PRINT(L"--original--------------------------------\n");		
	PRINT(L"100 numbers:%ls\n",wstr(e));
	PRINT(L"--copy--------------------------------\n");		
	PRINT(L"100 numbers:%ls\n",wstr(e2));

	PRINT(L"original length 100: %d\n", e->length);
	PRINT(L"copy length 100:     %d\n", e2->length);

	PRINT(L"--string_compare--------------------------------\n");		

	PRINT(L" 0:%i\n",bz_string_compare( str(L""), str(L"") ));
	PRINT(L">0:%i\n",bz_string_compare( str(L"a"), str(L"") ));
	PRINT(L"<0:%i\n",bz_string_compare( str(L""), str(L"a") ));

	PRINT(L"<0:%i\n",bz_string_compare( str(L"a"), str(L"b") ));
	PRINT(L" 0:%i\n",bz_string_compare( str(L"a"), str(L"a") ));
	PRINT(L">0:%i\n",bz_string_compare( str(L"b"), str(L"a") ));

	PRINT(L"<0:%i\n",bz_string_compare( str(L"aaa"), str(L"aab") ));
	PRINT(L" 0:%i\n",bz_string_compare( str(L"aaa"), str(L"aaa") ));
	PRINT(L">0:%i\n",bz_string_compare( str(L"aab"), str(L"aaa") ));

	PRINT(L"<0:%i\n",bz_string_compare_ignorecase( str(L"AaA"), str(L"AaB") ));
	PRINT(L" 0:%i\n",bz_string_compare_ignorecase( str(L"aAa"), str(L"AaA") ));
	PRINT(L">0:%i\n",bz_string_compare_ignorecase( str(L"aAB"), str(L"aaa") ));

	PRINT(L"<0:%i\n",bz_string_compare_ignorecase( str(L"0000001"), str(L"0000002") ));
	PRINT(L"<0:%i\n",bz_string_compare_ignorecase( str(L"\t\t1"), str(L"\t\t2") ));
	PRINT(L" 0:%i\n",bz_string_compare_ignorecase( str(L"   "), str(L"     ") ));

	PRINT(L"hello:%ls",cstr_to_wstr("hello\n"));
	PRINT(L"hello:");wprintf(L"%s",wstr_to_cstr(L"hello\n"));

	PRINT(L"--string cat wchar--------------------------------\n");		
	{
	  bz_String* q = bz_string_new(NULL);
	  PRINT(L"0:%d\n", q->length);
	  for(i=0;i<1000;i++)
	    bz_string_cat_wchar(q, L'.');
	  PRINT(L"1000:%d\n", q->length);
	  PRINT(L"1000x'.':%ls\n", q->string);
	}
   END; exit(0);

}



