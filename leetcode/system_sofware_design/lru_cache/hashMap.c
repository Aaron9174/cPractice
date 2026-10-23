#include "hashMap.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNV_OFFSET_BASIS 14695981039346656037ULL
#define FNV_PRIME 1099511628211ULL

HmStatus hashmap_create(size_t initial_capacity, struct HashMap **hashmap) {
  HmStatus status = OK;

  if (initial_capacity == 0) {
    status = INVALID_LENGTH_PARAMETER;
  }

  if (!status) {
    *hashmap = calloc(1, sizeof(struct HashMap));
    if (*hashmap == NULL) {
      status = FAILED_MEMORY_ALLOC;
    }
  }

  if (!status) {
    (*hashmap)->capacity = initial_capacity;
    status = hashmap_allocate_buckets(initial_capacity, &((*hashmap)->buckets));
    if (status) {
      free(*hashmap);
      *hashmap = NULL;
    }
  }

  return status;
}

HmStatus hashmap_allocate_buckets(size_t initial_capacity,
                                  struct HashBucket **buckets) {
  HmStatus status = OK;
  *buckets = calloc(initial_capacity, sizeof(struct HashBucket));
  if (*buckets == NULL) {
    status = FAILED_MEMORY_ALLOC;
  }
  return status;
}

void hashmap_destroy(struct HashMap *map) {
  free(map->buckets);
  free(map);
}

bool hashmap_put(struct HashMap *map, const char *key, int value) {
  printf("map: %p", map);
  printf("key: %c", *key);
  printf("value: %d", value);
  return false;
}

bool hashmap_get(struct HashMap *map, const char *key, int *out_value) {
  printf("map: %p", map);
  printf("key: %c", *key);
  printf("out value: %d", *out_value);
  return false;
}

bool hashmap_remove(struct HashMap *map, const char *key) {
  printf("map: %p", map);
  printf("key: %c", *key);
  return false;
}

uint64_t createFNV1aHash(const char *key) {
  uint64_t hash = FNV_OFFSET_BASIS;

  const size_t byteLen = strlen(key);
  for (size_t i = 0; i < byteLen; i++) {
    uint8_t dataByte = key[i];
    hash ^= dataByte;
    hash *= FNV_PRIME;
  }

  return hash;
}

size_t hashmap_size(const struct HashMap *map) {
  printf("map: %p", map);
  return 0;
}
