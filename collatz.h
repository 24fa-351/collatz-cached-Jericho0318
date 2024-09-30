#include <stdio.h>
#include <stdlib.h>

#include "lrucache.h"

unsigned long long int collatz(LRUCache* cache, unsigned long long int n)
{
    unsigned count = 0;
    if (n <= 1) {return n;}
    while (n != 1) {
        if (n % 2 == 0)
        {
            n = n / 2;
        } else {
            n = (3 * n) + 1;
        }
        count++;
    }
    return count;
}