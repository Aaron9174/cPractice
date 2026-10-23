/**
 * HashMap: string keys -> int values, implemented from scratch.
 *
 * Requirements:
 *
 * R1. Hashing
 *     - Hash keys with a string hash such as djb2 or FNV-1a.
 *     - bucket index = hash % capacity (or hash & (capacity - 1) if capacity is
 *       always a power of two).
 *
 * R2. Collision handling (pick one)
 *     - Separate chaining: each bucket holds a linked list of entries.
 *     - Open addressing: linear probing, with tombstones for removals.
 *
 * R3. Key ownership
 *     - The map stores its OWN copy of every key (strdup/malloc + strcpy).
 *       The caller may free or reuse their buffer right after put().
 *
 * R4. put
 *     - If the key exists, overwrite its value. Size does not change.
 *     - Otherwise insert it and increment size.
 *     - Return false only on allocation failure or a NULL map/key.
 *
 * R5. get
 *     - If found, write the value to *out_value and return true.
 *     - Otherwise return false and leave *out_value untouched.
 *
 * R6. remove
 *     - Free the entry and its key copy, decrement size, return true.
 *     - Return false if the key is missing.
 *
 * R7. Resizing
 *     - When size / capacity exceeds 0.75, double the capacity and rehash
 *       every entry into the new buckets.
 *     - A capacity of 0 passed to create() falls back to a default (e.g. 16).
 *
 * R8. Memory
 *     - destroy() frees every entry, every key copy, the bucket array, and
 *       the map itself. Valgrind/ASan should report zero leaks.
 *
 * R9. Complexity
 *     - put/get/remove run in O(1) average time.
 */
#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>
typedef enum { OK = 0, FAILED_MEMORY_ALLOC = 1 } HmStatus;

#include <stdbool.h>
#include <stddef.h>

struct HashEntry {
  struct HashEntry *prev;
  struct HashEntry *next;
};

struct HashBucket {
  struct HashEntry *head;
};

struct HashMap {
  size_t size;
  size_t capacity;
  struct HashBucket *buckets;
};

// Allocation & Lifecycle
HmStatus hashmap_create(size_t initial_capacity, struct HashMap **hashmap);
HmStatus hashmap_allocate_buckets(size_t initial_capacity,
                                  struct HashBucket **buckets);
void hashmap_destroy(struct HashMap *map);

// Core Mutations & Accessors
bool hashmap_put(struct HashMap *map, const char *key, int value);
bool hashmap_get(struct HashMap *map, const char *key, int *out_value);
bool hashmap_remove(struct HashMap *map, const char *key);

// Helper functions
uint64_t createFNV1aHash(const char *key);

// State Inspection
size_t hashmap_size(const struct HashMap *map);

#endif // HASHMAP_H
