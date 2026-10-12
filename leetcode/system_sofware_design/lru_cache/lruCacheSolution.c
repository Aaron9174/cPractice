#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int key;
  int val;
  struct Node *next;
  struct Node *prev;
};

#define CAPACITY 3000
#define MAX_VALUE_SIZE 105
#define MAX_KEY_SIZE 104

struct LRUCache {
  struct Node head;
  struct Node tail;
  uint32_t capacity;
};

LRUCache *lRUCacheCreate(int capacity) {}

int lRUCacheGet(LRUCache *obj, int key) {}

void lRUCachePut(LRUCache *obj, int key, int value) {}

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
