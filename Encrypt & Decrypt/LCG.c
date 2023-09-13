#include <stdio.h>
#include "lcg.h"
#include <math.h>
 
/**
 * returns a product of prime factors
*/
 unsigned long product_of_unique_prime_factors(unsigned long m)
 {
    unsigned long product = 1;

    unsigned long test_divisor = 2;

    if(m <= 1)
    {
        return 0;
    }

    while (test_divisor * test_divisor <= m)
    {
        if (m % test_divisor == 0)
        {
            product *= test_divisor;
            while (m % test_divisor == 0)
            {
                m /= test_divisor;
            }
        }
        test_divisor++;
    }
    if(m > 1)
    {
        product *= m;
    }
    return product;
 }

 /**
  * calling function from the header file
 */
struct LinearCongruentialGenerator makeLCG(unsigned long m, unsigned long c)
{
  struct LinearCongruentialGenerator lcg;
  unsigned long p;


  lcg.m = m;
  lcg.c = c;
  lcg.x = c;

  p = product_of_unique_prime_factors(m);

  if(m % 4 == 0)
  {
    lcg.a = 1 + 2 * p;
  }

  else{
    lcg.a = 1 + p;
  }


  if(m <= 0)
  {
    lcg.a = 0;
    lcg.c = 0;
    lcg.m = 0;
    lcg.x = 0;
  }

  if(lcg.a >= m || lcg.a <= 0)
  {
    lcg.a = 0;
    lcg.c = 0;
    lcg.m = 0;
    lcg.x = 0;
  }


  if(c >= m || c < 0)
  {
    lcg.a = 0;
    lcg.c = 0;
    lcg.m = 0;
    lcg.x = 0;
  }
  return lcg;

}

unsigned long getNextRandomValue(struct LinearCongruentialGenerator* lcg)
{
    unsigned long xo = lcg -> x;

    /* Calculate the next value in the sequence */
        lcg->x = (lcg->a * lcg->x + lcg->c) % lcg->m;
        return xo;
}
