#include "../../../src/debug.h"
#include "../../../src/cast.h"
#include "../../../src/string.h"
#include "../../../src/trie.h"

#define PRINT wprintf(L"%d]",__LINE__);wprintf

int main(int argc, char** argv)
{
  DEBUG_INIT(argv[0]);

  BEGIN;

  int i;
  for(i=0;i<500;i++) {
    bz_trie* t =  bz_trie_make(L"Jacob", 0, BZ_TRIE_MIN_NODES, L"29195");  
    bz_trie_put(t, L"Emily", L"25494");
    bz_trie_put(t, L"Michael", L"26991");
    bz_trie_put(t, L"Emma", L" 22532");
    bz_trie_put(t, L"Joshua", L"24950");
    bz_trie_put(t, L"Madison", L"19986");
    bz_trie_put(t, L"Matthew", L" 23706");
    bz_trie_put(t, L"Hannah", L"17393");
    bz_trie_put(t, L"Andrew", L"21852");
    bz_trie_put(t, L"Olivia", L"15982");
    bz_trie_put(t, L"Joseph", L"21265");
    bz_trie_put(t, L"Abigail", L"15789");
    bz_trie_put(t, L"Ethan", L"21206");
    bz_trie_put(t, L"Alexis", L"14659");
    bz_trie_put(t, L"Daniel", L"20947");
    bz_trie_put(t, L"Ashley", L"14402");
    bz_trie_put(t, L"Christopher", L"20781");
    bz_trie_put(t, L"Elizabeth", L"13927");
    bz_trie_put(t, L"Anthony", L"19990");
    bz_trie_put(t, L"Samantha", L"13733");
    bz_trie_put(t, L"William", L"19853");
    bz_trie_put(t, L"Isabella", L"13635");
    bz_trie_put(t, L"Ryan", L"19478");
    bz_trie_put(t, L"Sarah", L"13602");
    bz_trie_put(t, L"Nicholas", L"19457");
    bz_trie_put(t, L"Grace", L"12659");
    bz_trie_put(t, L"David", L"18440");
    bz_trie_put(t, L"Alyssa", L"12618");
    bz_trie_put(t, L"Tyler", L"17989");
    bz_trie_put(t, L"Lauren", L"10955");
    bz_trie_put(t, L"Alexander", L"17800");
    bz_trie_put(t, L"Kayla", L"10823");
/*    bz_trie_put(t, L"John", L"17198");
    bz_trie_put(t, L"Brianna", L"10445");
    bz_trie_put(t, L"James", L"16665");
    bz_trie_put(t, L"Jessica", L"10371");
    bz_trie_put(t, L"Dylan", L"15649");
    bz_trie_put(t, L"Taylor", L"10200");
    bz_trie_put(t, L"Zachary", L"15341");
    bz_trie_put(t, L"Sophia", L"9665");
    bz_trie_put(t, L"Brandon", L"15071");
    bz_trie_put(t, L"Anna", L"9382");
    bz_trie_put(t, L"Jonathan", L"14954");
    bz_trie_put(t, L"Victoria", L"9226");
    bz_trie_put(t, L"Samuel", L"14523");
    bz_trie_put(t, L"Natalie", L"9105");
    bz_trie_put(t, L"Christian", L"14022");
    bz_trie_put(t, L"Chloe", L"9012");
    bz_trie_put(t, L"Benjamin", L"13948");
    bz_trie_put(t, L"Sydney", L"8815");
    bz_trie_put(t, L"Justin", L"13639");
    bz_trie_put(t, L"Hailey", L"8682");
    bz_trie_put(t, L"Nathan", L"13497");
    bz_trie_put(t, L"Jasmine", L"7959");
    bz_trie_put(t, L"Jose", L"13082");
    bz_trie_put(t, L"Rachel", L"7888");
    bz_trie_put(t, L"Logan", L"13065");
    bz_trie_put(t, L"Morgan", L"7851");
    bz_trie_put(t, L"Gabrie", L"l12806");
    bz_trie_put(t, L"Megan", L"7743");
    bz_trie_put(t, L"Kevin", L"12031");
    bz_trie_put(t, L"Jennifer", L"7503");
    bz_trie_put(t, L"Noah", L"11700");
    bz_trie_put(t, L"Kaitlyn", L"7486");
    bz_trie_put(t, L"Austin", L"11553");
    bz_trie_put(t, L"Julia", L"7394");
    bz_trie_put(t, L"Caleb", L"11513");
    bz_trie_put(t, L"Haley", L"7110");
    bz_trie_put(t, L"Robert", L"11234");
    bz_trie_put(t, L"Mia", L"7059");
    bz_trie_put(t, L"Thomas", L"10879");
    bz_trie_put(t, L"Katherine", L"7056");
    bz_trie_put(t, L"Elijah", L"10505");
    bz_trie_put(t, L"Destiny", L"6859");
    bz_trie_put(t, L"Jordan", L"10214");
    bz_trie_put(t, L"Alexandra", L"6647");
    bz_trie_put(t, L"Aidan", L"9987");
    bz_trie_put(t, L"Nicole", L"6343");
    bz_trie_put(t, L"Cameron", L"9863");
    bz_trie_put(t, L"Maria", L"6221");
    bz_trie_put(t, L"Hunter", L"9828");
    bz_trie_put(t, L"Ava", L"6206");
    bz_trie_put(t, L"Jason", L"9729");
    bz_trie_put(t, L"Savannah", L"6073");
    bz_trie_put(t, L"Angel", L"9707");
    bz_trie_put(t, L"Brooke", L"5911");
    bz_trie_put(t, L"Connor", L"9604");
    bz_trie_put(t, L"Ella", L"5865");
    bz_trie_put(t, L"Evan", L"9345");
    bz_trie_put(t, L"Allison", L"5819");
    bz_trie_put(t, L"Jack", L"9257");
    bz_trie_put(t, L"Mackenzie", L"5804");
    bz_trie_put(t, L"Luke", L"9206");
    bz_trie_put(t, L"Paige", L"5717");
    bz_trie_put(t, L"Isaac", L"8860");
    bz_trie_put(t, L"Stephanie", L"5637");
    bz_trie_put(t, L"Aaron", L"8773");
    bz_trie_put(t, L"Jordan", L"5578");
    bz_trie_put(t, L"Isaiah", L"8707");
    bz_trie_put(t, L"Kylie", L"5516");
*/    
    int j;
    for(j=0;j<2000;j++) {
      bz_trie_get(t,L"Joshua");
      bz_trie_get(t,L"Emily");
      bz_trie_get(t,L"Hannah");
      bz_trie_get(t,L"Emma");
      bz_trie_get(t,L"Madison");
      bz_trie_get(t,L"Matthew");
      bz_trie_get(t,L"Grace");
      bz_trie_get(t,L"David");
      bz_trie_get(t,L"Daniel");
      bz_trie_get(t,L"Kayla");
      bz_trie_get(t,L"Bignose");
    }
  }
  END; exit(0);
  
}
