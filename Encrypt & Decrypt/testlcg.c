#include <stdio.h>
#include "lcg.h"

/* Print LCG values along with a message */
void printLCG(struct LinearCongruentialGenerator* lcg, char* msg)
{
  printf("%s (m=%lu,a=%lu,c=%lu,x=%lu)\n", msg, lcg->m, lcg->a, lcg->c, lcg->x);
}

/* Print message and n values generated by the LCG */
void testValues(struct LinearCongruentialGenerator* lcg, char* msg, int n)
{
  int i;
  printf("%s\n", msg);

  for(i = 0; i < n; ++i)
  {
    unsigned long x = getNextRandomValue(lcg);
    printf("%lu\n", x);
  }
}

/* Create and test a few LCGs */
int main()
{
  struct LinearCongruentialGenerator lcg1 = makeLCG(126,25);
  struct LinearCongruentialGenerator lcg2 = makeLCG(38875,1234);
  struct LinearCongruentialGenerator lcg3 = makeLCG(4611686018427387904,961168601842738797);

  /* Some error cases */
  struct LinearCongruentialGenerator lcg4 = makeLCG(4,3);
  struct LinearCongruentialGenerator lcg5 = makeLCG(0,5);
  struct LinearCongruentialGenerator lcg6 = makeLCG(5,0);

  
  printLCG(&lcg1, "initialized lcg1");
  printLCG(&lcg2, "initialized lcg2");
  printLCG(&lcg3, "initialized lcg3");

  printLCG(&lcg4, "initialized error test lcg4");
  printLCG(&lcg5, "initialized error test lcg5");
  printLCG(&lcg6, "initialized error test lcg6");
  
  testValues(&lcg1, "test lcg1", 10);
  testValues(&lcg2, "test lcg2", 10);
  testValues(&lcg3, "test lcg3", 10);

  printLCG(&lcg1, "lcg1 after first test");
  printLCG(&lcg2, "lcg2 after first test");
  printLCG(&lcg3, "lcg3 after first test");

  testValues(&lcg1, "test lcg1 again", 20);

  printLCG(&lcg1, "lcg1 after second test");
  
  return 0;
}