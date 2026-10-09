/**
 * Design a data structure that follows the constraints of a Least Recently Used
 * (LRU) cache.
 *
 * Implement the LRUCache class:
 *
 * LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
 * int get(int key) Return the value of the key if the key exists, otherwise
 * return -1. void put(int key, int value) Update the value of the key if the
 * key exists. Otherwise, add the key-value pair to the cache. If the number of
 * keys exceeds the capacity from this operation, evict the least recently used
 * key. The functions get and put must each run in O(1) average time complexity.
 *
 *
 *
 * Example 1:
 *
 * Input
 * ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
 * [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
 * Output
 * [null, null, null, 1, null, -1, null, -1, 3, 4]
 *
 * Explanation
 * LRUCache lRUCache = new LRUCache(2);
 * lRUCache.put(1, 1); // cache is {1=1}
 * lRUCache.put(2, 2); // cache is {1=1, 2=2}
 * lRUCache.get(1);    // return 1
 * lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
 * lRUCache.get(2);    // returns -1 (not found)
 * lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
 * lRUCache.get(1);    // return -1 (not found)
 * lRUCache.get(3);    // return 3
 * lRUCache.get(4);    // return 4
 *
 *
 * Constraints:
 *
 * 1 <= capacity <= 3000
 * 0 <= key <= 104
 * 0 <= value <= 105
 * At most 2 * 105 calls will be made to get and put.
 */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 3000
#define MAX_VALUE_SIZE 105
#define MAX_KEY_SIZE 104
#define SENTINAL -1

typedef struct {
  int key;
  int value;
} CacheEntry;

typedef struct {
  uint16_t curIndex;
  CacheEntry cache[CAPACITY];
  uint32_t capacity;
  uint32_t lastUsedVal;
  int lastUsedValCache[MAX_KEY_SIZE];
} LRUCache;

LRUCache *lRUCacheCreate(int capacity) {
  LRUCache *lruCache = (LRUCache *)calloc(1, sizeof(LRUCache));
  lruCache->capacity = capacity;
  // Start at 1, zero the default unused value in the last used value cache
  lruCache->lastUsedVal = 1;
  return lruCache;
}

int lRUCacheGet(LRUCache *obj, int key) {
  int result = SENTINAL;
  // The cache isn't filled
  if (obj->curIndex < obj->capacity - 1) {
    // The key was never put in the cache
    if (obj->lastUsedValCache[key] == 0) {
      return result;
    }
  }

  for (uint16_t i = 0; i < obj->curIndex; i++) {
    const CacheEntry entry = obj->cache[i];
    if (entry.key == key) {
      result = entry.value;
      // Update last used value, as it was received
      obj->lastUsedValCache[key] = obj->lastUsedVal++;
    }
  }

  return result;
}

void lRUCachePut(LRUCache *obj, int key, int value) {
  // Determines if the number has been put in the cache
  bool isInCache = (obj->lastUsedValCache[key] > 0);

  if (!isInCache) {
    // If not in the cache, and the capacity of the cache is reached, replace
    // the least used entry
    if (obj->curIndex >= obj->capacity) {
      // Set the minimum value to the first last used value in the cache and the
      // key to the first value in the cache
      int lruKey = obj->cache[0].key;
      int minVal = obj->lastUsedValCache[lruKey];

      // Start at one past the first value and look for a minumum, update the
      // key when we get a new minimum
      for (uint32_t i = 1; i < obj->capacity; i++) {
        const int curCacheKey = obj->cache[i].key;
        // Zero is the starting condition
        if (obj->lastUsedValCache[curCacheKey] < minVal &&
            obj->lastUsedValCache[curCacheKey] != 0) {
          minVal = obj->lastUsedValCache[curCacheKey];
          lruKey = curCacheKey;
        }
      }

      for (uint32_t i = 0; i < obj->capacity; i++) {
        if (obj->cache[i].key == lruKey) {
          obj->cache[i].key = key;
          obj->cache[i].value = value;
        }
      }

      obj->lastUsedValCache[key] = obj->lastUsedVal++;
      return;
    }

    // If not in the cache, create a new entry, add it to the cache, and update
    // last used
    CacheEntry entry;
    entry.key = key;
    entry.value = value;
    obj->cache[obj->curIndex++] = entry;
    obj->lastUsedValCache[key] = obj->lastUsedVal++;
  } else {
    printf("Found in cache, updating value and last used\n");
    // If in the cache, search by the key, update entry value, and update last
    // used
    for (int i = 0; i < obj->curIndex; i++) {
      if (obj->cache[i].key == key) {
        obj->cache[i].value = value;
        obj->lastUsedValCache[key] = obj->lastUsedVal++;
      }
    }
  }
}

void lRUCacheFree(LRUCache *obj) { free(obj); }

void printResult(const uint32_t length, char *results[length]) {
  printf("[ ");
  for (uint8_t i = 0; i < length; i++) {
    if (i == length - 1) {
      printf("%s ", results[i]);
    } else {
      printf("%s, ", results[i]);
    }
  }
  printf("]\n");
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);
 `
 * lRUCacheFree(obj);
*/
int main() {
#define INPUT_LENGTH 10

  //
  // ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
  // [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
  // Output
  // [null, null, null, 1, null, -1, null, -1, 3, 4]

  // LRUCache *obj = lRUCacheCreate(100);
  // int param1 = lRUCacheGet(obj, 10);
  // Set up input
  const char *inputLabels[INPUT_LENGTH] = {"LRUCache", "put", "put", "get",
                                           "put",      "get", "put", "get",
                                           "get",      "get"};
  const int input[INPUT_LENGTH][2] = {{2}, {1, 1}, {2, 2}, {1}, {3, 3},
                                      {2}, {4, 4}, {1},    {3}, {4}};

  // Set up results array
  char *results[INPUT_LENGTH];
  for (uint8_t i = 0; i < INPUT_LENGTH; i++) {
    results[i] = "null";
  }

  // Parse input
  LRUCache *cache;
  for (uint32_t i = 0; i < INPUT_LENGTH; i++) {
    const char *label = inputLabels[i];
    if (strcmp(label, "LRUCache") == 0) {
      cache = lRUCacheCreate(input[i][0]);
    } else if (strcmp(label, "put") == 0) {
      lRUCachePut(cache, input[i][0], input[i][1]);
    } else if (strcmp(label, "get") == 0) {
      const int result = lRUCacheGet(cache, input[i][0]);
      char str[20];
      snprintf(str, sizeof(str), "%d", result);
      results[i] = strdup(str);
    } else {
      printf("Unrecognized input: %s\n", label);
    }
  }

  printResult(INPUT_LENGTH, results);
}
