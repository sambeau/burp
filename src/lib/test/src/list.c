#include "../../src/empty.h"
#include "../../src/list.h"
#include "../../src/debug.h"
#include "../../src/integer.h"
#include "../../src/cast.h"


#define PRINT wprintf(L"%d]",__LINE__);wprintf


int main(int argc, char** argv)
{
   bz_List* zs;
   bz_List* ys;

   DEBUG_INIT(argv[0]);
   BEGIN;

   zs = bz_EMPTY;

   PRINT(bz_SIZEF L"\n",bz_list_length(zs));
   zs = bz_list_cons(zs,str(L"sam"));
   PRINT(bz_SIZEF L"\n",bz_list_length(zs));
   zs = bz_list_cons(zs,str(L"was"));
   PRINT(bz_SIZEF L"\n",bz_list_length(zs));
   zs = bz_list_cons(zs,str(L"here"));
   
   {
     int i;
     for(i=0;i<4093;i++) {
       zs = bz_list_cons(zs,L"ok?");
     }
   }
   PRINT(L"%i\n",bz_list_length(zs));

   wprintf(L"---\n");

   zs = bz_EMPTY;
   ys = bz_EMPTY;

   {
     int i;
     for(i=0;i<32;i++) {
       ys = bz_list_cons(ys,bz_integer_new(i));
     }

   }

    PRINT(L" ");bz_list_show(ys);wprintf(L"\n");
    zs = bz_list_mergesort(ys);
    PRINT(L" ");bz_list_show(zs);wprintf(L"\n");
    PRINT(L" ");bz_list_show(ys);wprintf(L"\n");

   wprintf(L"---\n");

   zs = bz_EMPTY;
   ys = bz_EMPTY;

   {
     int i;
     for(i=32;i>=0;i--) {
       ys = cons(int(i),ys);
     }
   }

   PRINT(L" ");bz_list_show(ys);wprintf(L"\n");
   zs = bz_list_mergesort(ys);
   PRINT(L" ");bz_list_show(zs);wprintf(L"\n");
   bz_list_show(ys);wprintf(L"\n");

   wprintf(L"---\n");

   zs = bz_EMPTY;
   ys = bz_EMPTY;

   ys = cons(int(7),
	     cons(int(0),
		  cons(int(9),
		       cons(int(8),
			    cons(int(2),
				 cons(int(4),
				      cons(int(3),
					   cons(int(10),
						cons(int(5),
						     cons(int(6),
							  cons(int(10),
							       cons(int(1),
								    cons(int(0),
									 cons(int(1),bz_EMPTY
									      ))))))))))))));
   
   PRINT(L" ");bz_list_show(ys);wprintf(L"\n");
   zs = bz_list_mergesort(ys);
   PRINT(L" ");bz_list_show(zs);wprintf(L"\n");
   PRINT(L" ");bz_list_show(ys);wprintf(L"\n");

   wprintf(L"---\n");

   zs = bz_EMPTY;
   ys = bz_EMPTY;

   {
     int i;
     for(i=10;i>0;i--) {
       ys = cons(int(i),ys);
     }
   }


   PRINT(L" ");bz_list_show(ys);wprintf(L"\n");
   zs = bz_list_copy(ys);
   PRINT(L" ");bz_list_show(zs);wprintf(L"\n");
   PRINT(L" ");bz_list_show(ys);wprintf(L"\n");

   wprintf(L"-- lists of strings --\n");
   PRINT(L" ");bz_list_show(list(str(L"sam"),str(L"was"),str(L"here"),str(L"ok")));wprintf(L"\n");
   
   wprintf(L"-- mixed lists --\n");
   {
     int i;
     for(i=0;i<10;i++) {
       PRINT(L" ");bz_list_show(list(str(L"number: "),int(i),str(L"\n")));
     }
   }
   wprintf(L"-- empty lists --\n");
   PRINT(L" >>>");bz_list_show(bz_EMPTY);wprintf(L"<<<\n");
   PRINT(L" >>>");bz_list_show(list(bz_EMPTY,bz_EMPTY,bz_EMPTY));wprintf(L"<<<\n");
   PRINT(L" ");bz_list_show(list(str(L"sam"),bz_EMPTY,str(L"was"),bz_EMPTY,str(L"here"),bz_EMPTY,str(L"ok")));wprintf(L"\n");
   wprintf(L"-- concats of lists of strings --\n");
   {
     PRINT(L"the beatles:");
     bz_List* xs =   list(str(L"John"),str(L","),str(L"Paul"),str(L","));
     bz_List* ys =   list(str(L"George"),str(L","),str(L"Ringo"),str(L"."));
     bz_list_show(bz_list_concat(xs,ys));
   }
   wprintf(L"\n");
   wprintf(L"-- debug show --\n");
   PRINT(L">");bz_list_debug_show(list(str(L"sam"),str(L"was"),str(L"here"),str(L"ok")));wprintf(L"\n");
   PRINT(L">");bz_list_debug_show(cons(int(1),cons(int(2),cons(int(3),bz_EMPTY))));wprintf(L"\n");
   PRINT(L">");bz_list_debug_show(cons(int(1),cons(cons(int(2),cons(int(3),bz_EMPTY)),cons(int(4),bz_EMPTY))));wprintf(L"\n");
   PRINT(L">");bz_list_debug_show(
			       bz_list_flatten(
					    cons(
						 int(1),
						 cons(
						      cons(
							   int(2),
							   cons(int(3),bz_EMPTY)
							   ),
						      cons(int(4),bz_EMPTY)
						      )
						 )
					    )
			       );
   
   wprintf(L"\n");
   PRINT(L">");bz_list_debug_show(
			       bz_list_flatten(
					    cons(
						 bz_EMPTY,
						 cons(
						      cons(
							   bz_EMPTY,
							   cons(int(3),bz_EMPTY)
							   ),
						      cons(bz_EMPTY,bz_EMPTY)
						      )
						 )
					    )
			       );
   
   wprintf(L"\n");
   PRINT(L">");bz_list_debug_show(
			       bz_list_flatten(
					    cons(
						 bz_EMPTY,
						 cons(
						      cons(
							   bz_EMPTY,
							   cons(bz_EMPTY,bz_EMPTY)
							   ),
						      cons(bz_EMPTY,bz_EMPTY)
						      )
						 )
					    )
			       );
   
   wprintf(L"\n");

   wprintf(L"-- list compare --\n");

   PRINT(L"0:%i\n",
	 bz_list_compare( list(str(L"sam"),str(L"was"),str(L"here"),str(L"ok")) ,
		       list(str(L"sam"),str(L"was"),str(L"here"),str(L"ok")) )
	 );

   PRINT(L"-1:%i\n",
	 bz_list_compare( list(str(L"sam"),str(L"was"),str(L"here"),str(L"ok")) ,
		       list(str(L"sam"),str(L"was"),str(L"here"),str(L"possible")) )
	 );

   PRINT(L"1:%i\n",
	 bz_list_compare( list(str(L"sam"),str(L"was"),str(L"here"),str(L"ok")) ,
		       list(str(L"sam"),str(L"was"),str(L"here"),str(L"not")) )
	 );

   PRINT(L"-1:%i\n",
	 bz_list_compare( list(str(L"sam"),str(L"was"),str(L"here")) ,
		       list(str(L"sam"),str(L"was"),str(L"here"),str(L"possible")) )
	 );

   PRINT(L"1:%i\n",
	 bz_list_compare( list(str(L"sam"),str(L"was"),str(L"here"),str(L"ok")) ,
		       list(str(L"sam"),str(L"was"),str(L"here")) )
	 );

   wprintf(L"-- list to strings --\n");

   PRINT(L"1:%ls\n",
	 bz_list_to_wstr( list(str(L"sam"),str(L"was"),str(L"here"),str(L"ok")) )
	 );
   PRINT(L"1:%ls\n",
	 bz_list_to_wstr( list(str(L"sam"),str(L"was"),list(str(L"probably"),str(L"not")),str(L"here"),str(L"ok")) )
	 );

   END; exit(0);

}

