#include "hashMap.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct HashEntry {
  struct HashNode *prev;
  struct HashNode *next;
};

struct HashBucket {
  struct HashEntry *head;
};

// TODO: define your entry/bucket type and the map's fields
struct HashMap {
  size_t size;
  size_t capacity;
  struct HashBucket buckets[];
};

HashMap *hashmap_create(size_t initial_capacity) {
  HashMap *map = calloc(1, sizeof(HashMap));
  map->capacity = initial_capacity;
  map->buckets = calloc(initial_capacity, sizeof(HashBucket));
  return map;
}

void hashmap_destroy(HashMap *map) { free(map); }

bool hashmap_put(HashMap *map, const char *key, int value) { return false; }

bool hashmap_get(HashMap *map, const char *key, int *out_value) {
  return false;
}

bool hashmap_remove(HashMap *map, const char *key) { return false; }

size_t hashmap_size(const HashMap *map) { return 0; }
