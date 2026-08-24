#include <stdio.h>

#define ARRAY_SIZE 5

int main() {
  int i;

  char char_array[ARRAY_SIZE] = {'a', 'b', 'c', 'd', 'e'};
  int int_array[ARRAY_SIZE] = {1, 2, 3, 4, 5};
  
  void* void_pointer;

  void_pointer = (void *) char_array;

  for (i=0; i < ARRAY_SIZE; i++) {
    printf("[char pointer] points to 0x%08x, which contains the character %c\n", void_pointer, *((char *)void_pointer));
    void_pointer = ((char *) void_pointer) + 1;
  }

  void_pointer = (void *) int_array;

  for (i=0; i < ARRAY_SIZE; i++) {
    printf("[integer pointer] points to 0x%08x, which contains the integer %d\n", void_pointer, *((int *)void_pointer));
    void_pointer = ((int *) void_pointer) + 1;
  }
}
