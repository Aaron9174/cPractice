
void fatal(char *message) {
  char error_message[100];

  strcpy(error_message, "[!!] Fatal Error ");
  strncat(error_message, message, 83);
  perror(error_message);

  exit(-1);
}

/**
 * An error-checked malloc() wrapper function
 *
 * NOTE: malloc() can return NULL for a few reasons:
 * 1) Physical RAM/swap is full
 * 2) Program has severe memory (allocations without frees), draining the memory pool
 * 3) No contiguous space (100MB of space exist, just not contiguously)
 * 4) Invalid or zero-size requested
 *    - malloc(0) is invalid
 *    - The size_t overflow (negative number or too large of a number)
 *
 * This function protects use against this
 */
void *ec_malloc(unsigned int size) {
  void *ptr;
  ptr = malloc(size);
  if (ptr == NULL) {
    fatal("in ec_malloc() on memory allocation");
  }
  return ptr;
}
