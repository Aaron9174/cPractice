#include "hashMap.h"

#include <cstddef>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct HashEntry {
  struct HashEntry *prev;
  struct HashEntry *next;
};

struct HashBucket {
  struct HashEntry *head;
};

// TODO: define your entry/bucket type and the map's fields
struct HashMap {
  size_t size;
  size_t capacity;
  struct HashBucket *buckets;
};

HmStatus hashmap_create(size_t initial_capacity, HashMap *hashmap) {
  HmStatus status = OK;

  hashmap = calloc(1, sizeof(struct HashMap));
  if (hashmap == NULL) {
    status = FAILED_MEMORY_ALLOC;
  }

  hashmap->capacity = initial_capacity;
  if (!status) {
    status = hashmap_allocate_buckets(initial_capacity, hashmap->buckets);
  }

  return status;
}

HmStatus hashmap_allocate_buckets(size_t initial_capacity,
                                  struct HashBucket *buckets) {
  HmStatus status = OK;
  buckets = calloc(initial_capacity, sizeof(struct HashBucket));
  if (buckets == NULL) {
    status = FAILED_MEMORY_ALLOC;
  }
  return status;
}

void hashmap_destroy(HashMap *map) {
  free(map->buckets);
  free(map);
}

bool hashmap_put(HashMap *map, const char *key, int value) { return false; }

bool hashmap_get(HashMap *map, const char *key, int *out_value) {
  return false;
}

bool hashmap_remove(HashMap *map, const char *key) { return false; }

size_t hashmap_size(const HashMap *map) { return 0; }
