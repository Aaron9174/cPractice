/**
 * Tests for hashMap.c. Build and run with AddressSanitizer to catch leaks:
 *
 *   clang -g -fsanitize=address,undefined -Wall -Wextra \
 *     hashMap.c hashMapTest.c -o build/hashMapTest && ./build/hashMapTest
 */
#include "hashMap.h"

#include <stdio.h>
#include <string.h>

static int failures = 0;

#define CHECK(cond)                                                            \
  do {                                                                         \
    if (!(cond)) {                                                             \
      printf("  FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);                 \
      failures++;                                                              \
    }                                                                          \
  } while (0)

static void test_create_empty(void) {
  printf("create_empty\n");
  struct HashMap *map = NULL;
  HmStatus result = hashmap_create(8, &map);
  CHECK(map != NULL && result == OK);

  CHECK(hashmap_size(map) == 0);
  int out = 0;
  CHECK(!hashmap_get(map, "missing", &out));
  hashmap_destroy(map);
}

static void test_put_get(void) {
  printf("put_get (R4, R5)\n");
  struct HashMap *map = NULL;
  HmStatus result = hashmap_create(8, &map);
  CHECK(map != NULL && result == OK);

  CHECK(hashmap_put(map, "one", 1));
  CHECK(hashmap_put(map, "two", 2));
  int out = 0;
  CHECK(hashmap_get(map, "one", &out) && out == 1);
  CHECK(hashmap_get(map, "two", &out) && out == 2);
  CHECK(hashmap_size(map) == 2);

  // get on a missing key must not modify out_value
  out = 42;
  CHECK(!hashmap_get(map, "three", &out));
  CHECK(out == 42);
  hashmap_destroy(map);
}

static void test_overwrite(void) {
  printf("overwrite (R4)\n");
  struct HashMap *map = NULL;
  HmStatus result = hashmap_create(8, &map);
  CHECK(map != NULL && result == OK);

  hashmap_put(map, "k", 1);
  hashmap_put(map, "k", 99);
  int out = 0;
  CHECK(hashmap_get(map, "k", &out) && out == 99);
  CHECK(hashmap_size(map) == 1);
  hashmap_destroy(map);
}

static void test_key_copy(void) {
  printf("key_copy (R3)\n");
  struct HashMap *map = NULL;
  HmStatus result = hashmap_create(8, &map);
  CHECK(map != NULL && result == OK);

  char buf[16];
  strcpy(buf, "alpha");
  hashmap_put(map, buf, 7);
  strcpy(buf, "XXXXX"); // caller reuses their buffer
  int out = 0;
  CHECK(hashmap_get(map, "alpha", &out) && out == 7);
  CHECK(!hashmap_get(map, "XXXXX", &out));
  hashmap_destroy(map);
}

static void test_remove(void) {
  printf("remove (R6)\n");
  struct HashMap *map = NULL;
  HmStatus result = hashmap_create(8, &map);
  CHECK(map != NULL && result == OK);

  hashmap_put(map, "a", 1);
  hashmap_put(map, "b", 2);
  CHECK(hashmap_remove(map, "a"));
  CHECK(!hashmap_remove(map, "a"));
  CHECK(hashmap_size(map) == 1);
  int out = 0;
  CHECK(!hashmap_get(map, "a", &out));
  CHECK(hashmap_get(map, "b", &out) && out == 2);

  // re-insert after remove
  CHECK(hashmap_put(map, "a", 3));
  CHECK(hashmap_get(map, "a", &out) && out == 3);
  hashmap_destroy(map);
}

static void test_collisions_and_resize(void) {
  printf("collisions_and_resize (R2, R7)\n");
  // Tiny capacity forces collisions and several resizes
  struct HashMap *map = NULL;
  HmStatus result = hashmap_create(1, &map);
  CHECK(map != NULL && result == OK);

  char key[32];
  const int n = 10000;
  int bad = 0;
  for (int i = 0; i < n; i++) {
    snprintf(key, sizeof(key), "key%d", i);
    if (!hashmap_put(map, key, i)) {
      bad++;
    }
  }
  CHECK(bad == 0);
  CHECK(hashmap_size(map) == (size_t)n);

  bad = 0;
  for (int i = 0; i < n; i++) {
    snprintf(key, sizeof(key), "key%d", i);
    int out = -1;
    if (!hashmap_get(map, key, &out) || out != i) {
      bad++;
    }
  }
  CHECK(bad == 0);

  // remove every even key, odd keys must survive
  for (int i = 0; i < n; i += 2) {
    snprintf(key, sizeof(key), "key%d", i);
    hashmap_remove(map, key);
  }
  CHECK(hashmap_size(map) == (size_t)n / 2);
  bad = 0;
  for (int i = 0; i < n; i++) {
    snprintf(key, sizeof(key), "key%d", i);
    int out = -1;
    bool found = hashmap_get(map, key, &out);
    if ((i % 2 == 0) == found) {
      bad++;
    }
  }
  CHECK(bad == 0);
  hashmap_destroy(map);
}

static void test_zero_capacity(void) {
  printf("zero_capacity (R7)\n");
  struct HashMap *map = NULL;
  HmStatus result = hashmap_create(0, &map);
  CHECK(map != NULL && result == OK);

  CHECK(hashmap_put(map, "x", 5));
  int out = 0;
  CHECK(hashmap_get(map, "x", &out) && out == 5);
  hashmap_destroy(map);
}

static void test_empty_string_key(void) {
  printf("empty_string_key\n");
  struct HashMap *map = NULL;
  HmStatus result = hashmap_create(8, &map);
  CHECK(map != NULL && result == OK);

  CHECK(hashmap_put(map, "", 11));
  int out = 0;
  CHECK(hashmap_get(map, "", &out) && out == 11);
  hashmap_destroy(map);
}

int main(void) {
  test_create_empty();
  test_put_get();
  test_overwrite();
  test_key_copy();
  test_remove();
  test_collisions_and_resize();
  test_zero_capacity();
  test_empty_string_key();

  if (failures == 0) {
    printf("\nAll tests passed\n");
    return 0;
  }
  printf("\n%d check(s) failed\n", failures);
  return 1;
}
