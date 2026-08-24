#include <stdio.h>
#include <string.h>

int main() {
  char str_a[20];
  char *pointer;
  char *pointer2;

  strcpy(str_a, "Hello, world!\n");
  // Sets first pointer to the start of the array
  pointer = str_a;
  printf(pointer);

  // Sets pointer2 to point two indexes past pointer, which is at the beginning of character array
  pointer2 = pointer + 2;
  printf(pointer2);
  strcpy(pointer2, "y you guys!\n");
  // This updates since all of these are pointing to the same block of memory
  printf(pointer);
}
