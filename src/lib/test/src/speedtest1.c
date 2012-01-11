#include "../../src/empty.h"
#include "../../src/list.h"
#include "../../src/debug.h"
#include "../../src/integer.h"


#define PRINT printf("%d]",__LINE__);printf


int main(int argc, char** argv)
{
   list* zs;
   list* ys;

   DEBUG_INIT(argv[0]);
   BEGIN;

   zs = EMPTY;

   PRINT(bz_SIZEF "\n",bz_list_length(zs));

   zs = bz_list_cons(zs,"sam");
   zs = bz_list_cons(zs,"was");
   zs = bz_list_cons(zs,"here");
   {
     int i;
     for(i=0;i<4094;i++) {
       zs = bz_list_cons(zs,"ok?");
     }
   }
   PRINT("%i\n",bz_list_length(zs));

   printf("---\n");


   zs = EMPTY;
   ys = EMPTY;

   {
     int i;
     for(i=0;i<32;i++) {
       ys = cons(int(i),ys);
     }
   }

   PRINT(" ");bz_list_show(ys);printf("\n");
   zs = bz_list_mergesort(ys);
   PRINT(" ");bz_list_show(zs);printf("\n");
   PRINT(" ");bz_list_show(ys);printf("\n");

   printf("---\n");

   zs = EMPTY;
   ys = EMPTY;

   {
     int i;
     for(i=32;i>=0;i--) {
       ys = cons(int(i),ys);
     }
   }

   PRINT(" ");bz_list_show(ys);printf("\n");
   zs = bz_list_mergesort(ys);
   PRINT(" ");bz_list_show(zs);printf("\n");
   bz_list_show(ys);printf("\n");

   printf("---\n");

   zs = EMPTY;
   ys = EMPTY;

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
									 cons(int(1),EMPTY
									      ))))))))))))));
   
   PRINT(" ");bz_list_show(ys);printf("\n");
   zs = bz_list_mergesort(ys);
   PRINT(" ");bz_list_show(zs);printf("\n");
   PRINT(" ");bz_list_show(ys);printf("\n");

   printf("---\n");

   zs = EMPTY;
   ys = EMPTY;

   {
     int i;
     for(i=10;i>0;i--) {
       ys = cons(int(i),ys);
     }
   }


   PRINT(" ");bz_list_show(ys);printf("\n");
   zs = bz_list_copy(ys);
   PRINT(" ");bz_list_show(zs);printf("\n");
   PRINT(" ");bz_list_show(ys);printf("\n");

   printf("-- lists of strings --\n");
   PRINT(" ");bz_list_show(list(str("sam"),str("was"),str("here"),str("ok")));printf("\n");
   
   printf("-- mixed lists --\n");
   {
     int i;
     for(i=0;i<10;i++) {
       PRINT(" ");bz_list_show(list(str("number: "),int(i),str("\n")));
     }
   }
   printf("-- empty lists --\n");
   PRINT(" >>>");bz_list_show(EMPTY);printf("<<<\n");
   PRINT(" >>>");bz_list_show(list(EMPTY,EMPTY,EMPTY));printf("<<<\n");
   PRINT(" ");bz_list_show(list(str("sam"),EMPTY,str("was"),EMPTY,str("here"),EMPTY,str("ok")));printf("\n");
   END; exit(0);

}

