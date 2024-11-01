#include <stdio.h>
#include <stdlib.h>

#include "lrucache.h"

unsigned long long int collatz(LRUCache* cache, unsigned long long int num) {
    if (num <= 1) {
        return num;
    }

    unsigned long long int result = get(cache, num);
    if (result != -1) {
        return result;
    }

    unsigned long long int count = 0;
    unsigned long long int original_num = num;

    while (num != 1) {
        if (num % 2 == 0) {
            num = num / 2;
        } else {
            num = (3 * num) + 1;
        }
        count++;
    }

    put(cache, original_num, count);
    return count;
}