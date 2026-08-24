#include <stdio.h>

#define ARRAY_SIZE 5

int main() {
  int i;

  char char_array[ARRAY_SIZE] = {'a', 'b', 'c', 'd', 'e'};
  int int_array[ARRAY_SIZE] = {1, 2, 3, 4, 5};
  
  char* char_pointer;
  int* int_pointer;

  char_pointer = int_array;
  int_pointer = char_array;

  for (i=0; i < ARRAY_SIZE; i++) {
    printf("[char pointer] points to 0x%08x, which contains the character %d\n", char_pointer, *char_pointer);
    char_pointer++;
  }

  for (i=0; i < ARRAY_SIZE; i++) {
    printf("[integer pointer] points to 0x%08x, which contains the integer %c\n", int_pointer, *int_pointer);
    int_pointer++;
  }
}
