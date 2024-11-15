#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int key;
    int val;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    unsigned capacity;
    unsigned size;
    Node* head;
    Node* tail;
    Node** hash;
    double hits;
    double misses;
} LRUCache;

Node* createNode(int key, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->val = val;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

LRUCache* createLRUCache(unsigned long long int capacity) {
    LRUCache* newcache = (LRUCache*)malloc(sizeof(LRUCache));
    newcache->capacity = capacity;
    newcache->size = 0;
    newcache->head = createNode(INT_MIN, INT_MIN);
    newcache->tail = createNode(INT_MIN, INT_MIN);
    newcache->head->next = newcache->tail;
    newcache->tail->prev = newcache->head;
    newcache->hash = (Node**)calloc(10000000, sizeof(Node*));
    newcache->hits = 0;
    newcache->misses = 0;
    return newcache;
}

void removeNode(LRUCache* cache, Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void addNode(LRUCache* cache, Node* node) {
    node->next = cache->head->next;
    node->prev = cache->head;
    cache->head->next->prev = node;
    cache->head->next = node;
}

void moveToHead(LRUCache* cache, Node* node) {
    removeNode(cache, node);
    addNode(cache, node);
}

unsigned long long int get(LRUCache* cache, int key) {
    Node* newNode = cache->hash[key];
    if (newNode == NULL) {
        cache->misses++;
        return -1;
    }
    cache->hits++;
    moveToHead(cache, newNode);
    return newNode->val;
}

void put(LRUCache* cache, int key, int value) {
    Node* node = cache->hash[key];
    if (node != NULL) {
        node->val = value;
        moveToHead(cache, node);
    } else {
        if (cache->size >= cache->capacity) {
            Node* lru = cache->tail->prev;
            removeNode(cache, lru);
            cache->hash[lru->key] = NULL;
            free(lru);
            cache->size--;
            //printf("Capacity is full");
        }
        Node* newNode = createNode(key, value);
        addNode(cache, newNode);
        cache->hash[key] = newNode;
        cache->size++;
    }
}

double getCacheHitRatio(LRUCache* cache) {
    if (cache->misses == 0) {
        return 0.0;
    }
    return (cache->hits / (cache->hits + cache->misses)) * 100;
}

void freeLRUCache(LRUCache* cache) {
    Node* current = cache->head->next;
    while (current != cache->tail) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(cache->head);
    free(cache->tail);
    free(cache->hash);
    free(cache);
}