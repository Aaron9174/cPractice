#include "hashMap.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// TODO: define your entry/bucket type and the map's fields
struct HashMap {
  size_t size;
  size_t capacity;
};

HashMap *hashmap_create(size_t initial_capacity) {
  HashMap *map = calloc(initial_capacity, sizeof(HashMap));
  return map;
}

void hashmap_destroy(HashMap *map) { free(map); }

bool hashmap_put(HashMap *map, const char *key, int value) {}

bool hashmap_get(HashMap *map, const char *key, int *out_value) {
  return false;
}

bool hashmap_remove(HashMap *map, const char *key) { return false; }

size_t hashmap_size(const HashMap *map) { return 0; }
