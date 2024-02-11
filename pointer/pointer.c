#include <stdio.h>
#include <string.h>

int main() {
  char str_a[20]; // 20 ele char array
  char *pointer; // A pointer to the address of a char
  char *pointer2;

  strcpy(str_a, "Hello, world!\n");
  pointer = str_a; // Sets its value to the start of the array
  printf("%s",pointer);

  pointer2 = pointer + 1; // Sets it's value 2 bytes further in
  printf("%s",pointer2);
  strcpy(pointer2, "owdy assembler!\n");
  printf("%s",pointer);
}
