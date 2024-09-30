#include <stdio.h>
#include <stdlib.h>

#include "collatz.h"
#define CACHE_CAPACITY 100

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("Please provide six arguments\n");
        return 1;
    }
    unsigned steps = 0, max_steps = 0;
    unsigned long long int num = atoi(argv[1]), min_num = atoi(argv[2]), max_num = atoi(argv[3]),
                           cache_size = atoi(argv[5]) - min_num - 1;
    LRUCache *cache = createLRUCache(CACHE_CAPACITY);
    if (num <= min_num || num  >= max_num) {
        printf("Num should be between min and max\n");
        return 1;
    }
    double cache_miss = 0;
    for (int i = 0; i < num; i++)
    {
        unsigned long long int rn = min_num + rand() % (max_num - min_num);
        steps = collatz(rn);
        put(cache, rn, steps);
        if (get(cache, rn) == -1) {
            cache_miss++;
        }
        if  (steps > max_steps) {
            printf("(%7d) %20llu: new max %u\n", i, rn, steps);
            max_steps = steps;
        }
    }
    printf("Final max: %u\n", max_steps);
    double hit_ratio = 100 * (cache_size / (cache_size + cache_miss));
    printf("Hits: %.2f%%\n", hit_ratio);
    freeLRUCache(cache);
    return 0;
}