#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "collatz.h"

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("./main <num of times> <min> <max> <LRU> <cache size>\n");
        return 1;
    }
    unsigned steps = 0, max_steps = 0;
    unsigned long long int num = atoi(argv[1]), min_num = atoi(argv[2]), max_num = atoi(argv[3]),
                           cache_size = atoi(argv[5]) - min_num - 1;
    LRUCache *cache = createLRUCache(cache_size);
    if (num <= min_num || num  >= max_num) {
        printf("Num should be between min and max\n");
        return 1;
    }
    if (!strcmp(argv[4], "lru")) {
        for (int i = 0; i < num; i++)
        {
            unsigned long long int rn = min_num + rand() % (max_num - min_num);
            steps = collatz(cache, rn);
            if  (steps > max_steps) {
                printf("(%7d) %20llu: new max %u\n", i, rn, steps);
                max_steps = steps;
            }
        }
        printf("Final max: %u\n", max_steps);
        printf("Hits: %.2f%%\n", getCacheHitRatio(cache));
        freeLRUCache(cache);
    } else {
        printf("./main <num of times> <min> <max> <LRU> <cache size>\n");
    }
    return 0;
}