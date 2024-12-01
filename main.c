#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "collatz.h"

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("./main <num of times> <min> <max> <LRU> <cache size>\n");
        exit(1);
    }
    unsigned steps = 0, max_steps = 0;
    uint64_t num = atoi(argv[1]), min_num = atoi(argv[2]), max_num = atoi(argv[3]),
                           cache_capacity = atoi(argv[5]) - min_num - 1;
    LRUCache *cache = createLRUCache(cache_capacity);
    if (num <= min_num || num >= max_num)
    {
        printf("Num should be between min and max\n");
        exit(1);
    }
    if (!strcmp(argv[4], "lru"))
    {
        for (int ix = 0; ix < num; ix++)
        {
            uint64_t rn = min_num + rand() % (max_num - min_num);
            steps = collatz(cache, rn);
            if (steps > max_steps)
            {
                printf("(%7d) %20lu: new max %u\n", ix, rn, steps);
                max_steps = steps;
            }
        }
        printf("Final max: %u\n", max_steps);
        printf("Hits: %.2f%%\n", getCacheHitRatio(cache));
        freeLRUCache(cache);
    }
    else
    {
        printf("./main <num of times> <min> <max> <LRU> <cache size>\n");
    }
    return 0;
}