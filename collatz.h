#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "lrucache.h"

uint64_t collatz(LRUCache* cache, uint64_t num) {
    if (num <= 1) {
        return num;
    }

    uint64_t result = get(cache, num);
    if (result != -1) {
        return result;
    }

    uint64_t count = 0;
    uint64_t original_num = num;

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