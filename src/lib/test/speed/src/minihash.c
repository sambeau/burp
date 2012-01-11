#include "../../../src/debug.h"
#include "../../../src/cast.h"
#include "../../../src/string.h"
#include "../../../src/minihash.h"

#define PRINT wprintf(L"%d]",__LINE__);wprintf

int main(int argc, char** argv)
{
  DEBUG_INIT(argv[0]);

  BEGIN;

  int i;
  for(i=0;i<500;i++) {
    bz_Minihash* m;
    m = bz_minihash_new();    
    put(m,str(L"Jacob"), L"29195");  
    put(m,str(L"Emily"), L"25494");
    put(m,str(L"Michael"), L"26991");
    put(m,str(L"Emma"), L" 22532");
    put(m,str(L"Joshua"), L"24950");
    put(m,str(L"Madison"), L"19986");
    put(m,str(L"Matthew"), L" 23706");
    put(m,str(L"Hannah"), L"17393");
    put(m,str(L"Andrew"), L"21852");
    put(m,str(L"Olivia"), L"15982");
    put(m,str(L"Joseph"), L"21265");
    put(m,str(L"Abigail"), L"15789");
    put(m,str(L"Ethan"), L"21206");
    put(m,str(L"Alexis"), L"14659");
    put(m,str(L"Daniel"), L"20947");
    put(m,str(L"Ashley"), L"14402");
    put(m,str(L"Christopher"), L"20781");
    put(m,str(L"Elizabeth"), L"13927");
    put(m,str(L"Anthony"), L"19990");
    put(m,str(L"Samantha"), L"13733");
    put(m,str(L"William"), L"19853");
    put(m,str(L"Isabella"), L"13635");
    put(m,str(L"Ryan"), L"19478");
    put(m,str(L"Sarah"), L"13602");
    put(m,str(L"Nicholas"), L"19457");
    put(m,str(L"Grace"), L"12659");
    put(m,str(L"David"), L"18440");
    put(m,str(L"Alyssa"), L"12618");
    put(m,str(L"Tyler"), L"17989");
    put(m,str(L"Lauren"), L"10955");
    put(m,str(L"Alexander"), L"17800");
    put(m,str(L"Kayla"), L"10823");
/*    put(m,str(L"John"), L"17198");
    put(m,str(L"Brianna"), L"10445");
    put(m,str(L"James"), L"16665");
    put(m,str(L"Jessica"), L"10371");
    put(m,str(L"Dylan"), L"15649");
    put(m,str(L"Taylor"), L"10200");
    put(m,str(L"Zachary"), L"15341");
    put(m,str(L"Sophia"), L"9665");
    put(m,str(L"Brandon"), L"15071");
    put(m,str(L"Anna"), L"9382");
    put(m,str(L"Jonathan"), L"14954");
    put(m,str(L"Victoria"), L"9226");
    put(m,str(L"Samuel"), L"14523");
    put(m,str(L"Natalie"), L"9105");
    put(m,str(L"Christian"), L"14022");
    put(m,str(L"Chloe"), L"9012");
    put(m,str(L"Benjamin"), L"13948");
    put(m,str(L"Sydney"), L"8815");
    put(m,str(L"Justin"), L"13639");
    put(m,str(L"Hailey"), L"8682");
    put(m,str(L"Nathan"), L"13497");
    put(m,str(L"Jasmine"), L"7959");
    put(m,str(L"Jose"), L"13082");
    put(m,str(L"Rachel"), L"7888");
    put(m,str(L"Logan"), L"13065");
    put(m,str(L"Morgan"), L"7851");
    put(m,str(L"Gabrie"), L"l12806");
    put(m,str(L"Megan"), L"7743");
    put(m,str(L"Kevin"), L"12031");
    put(m,str(L"Jennifer"), L"7503");
    put(m,str(L"Noah"), L"11700");
    put(m,str(L"Kaitlyn"), L"7486");
    put(m,str(L"Austin"), L"11553");
    put(m,str(L"Julia"), L"7394");
    put(m,str(L"Caleb"), L"11513");
    put(m,str(L"Haley"), L"7110");
    put(m,str(L"Robert"), L"11234");
    put(m,str(L"Mia"), L"7059");
    put(m,str(L"Thomas"), L"10879");
    put(m,str(L"Katherine"), L"7056");
    put(m,str(L"Elijah"), L"10505");
    put(m,str(L"Destiny"), L"6859");
    put(m,str(L"Jordan"), L"10214");
    put(m,str(L"Alexandra"), L"6647");
    put(m,str(L"Aidan"), L"9987");
    put(m,str(L"Nicole"), L"6343");
    put(m,str(L"Cameron"), L"9863");
    put(m,str(L"Maria"), L"6221");
    put(m,str(L"Hunter"), L"9828");
    put(m,str(L"Ava"), L"6206");
    put(m,str(L"Jason"), L"9729");
    put(m,str(L"Savannah"), L"6073");
    put(m,str(L"Angel"), L"9707");
    put(m,str(L"Brooke"), L"5911");
    put(m,str(L"Connor"), L"9604");
    put(m,str(L"Ella"), L"5865");
    put(m,str(L"Evan"), L"9345");
    put(m,str(L"Allison"), L"5819");
    put(m,str(L"Jack"), L"9257");
    put(m,str(L"Mackenzie"), L"5804");
    put(m,str(L"Luke"), L"9206");
    put(m,str(L"Paige"), L"5717");
    put(m,str(L"Isaac"), L"8860");
    put(m,str(L"Stephanie"), L"5637");
    put(m,str(L"Aaron"), L"8773");
    put(m,str(L"Jordan"), L"5578");
    put(m,str(L"Isaiah"), L"8707");
    put(m,str(L"Kylie"), L"5516");
*/    
    int j;
    for(j=0;j<2000;j++) {
      get(m,str(L"Joshua"));
      get(m,str(L"Emily"));
      get(m,str(L"Hannah"));
      get(m,str(L"Emma"));
      get(m,str(L"Madison"));
      get(m,str(L"Matthew"));
      get(m,str(L"Grace"));
      get(m,str(L"David"));
      get(m,str(L"Daniel"));
      get(m,str(L"Kayla"));
      get(m,str(L"Bignose"));
    }
  }
  END; exit(0);
  
}
