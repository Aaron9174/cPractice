#include <stdio.h>

#define ARRAY_SIZE 5

int main() {
  int i;

  char char_array[ARRAY_SIZE] = {'a', 'b', 'c', 'd', 'e'};
  int int_array[ARRAY_SIZE] = {1, 2, 3, 4, 5};
  
  unsigned int hack_nonpointer = (unsigned int) char_array;

  for (i=0; i < ARRAY_SIZE; i++) {
    printf("[char pointer] points to 0x%08x, which contains the character %c\n", hack_nonpointer, *((char *)hack_nonpointer));
    hack_nonpointer += sizeof(char);
  }

  hack_nonpointer = (unsigned int) int_array;

  for (i=0; i < ARRAY_SIZE; i++) {
    printf("[integer pointer] points to 0x%08x, which contains the integer %d\n", hack_nonpointer, *((int *)hack_nonpointer));
    hack_nonpointer += sizeof(int);
  }
}
