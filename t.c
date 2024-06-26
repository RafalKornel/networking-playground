#include <stdio.h>
#include <stdlib.h>

// Define a struct with a flexible array member
struct flexible_array_struct {
  int length;
  int array[]; // Flexible array member
};

int main() {
  int n = 5; // Size of the flexible array
  // Allocate memory for the struct, including space for the flexible array
  struct flexible_array_struct *fa =
      malloc(sizeof(struct flexible_array_struct) + n * sizeof(int));

  printf("sizeof struct: %d\n", sizeof(struct flexible_array_struct));

  if (fa == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
  }

  fa->length = n;

  // Initialize and use the flexible array member
  for (int i = 0; i < fa->length; i++) {
    fa->array[i] = i * 10;
  }

  // Print the values
  for (int i = 0; i < fa->length; i++) {
    printf("fa->array[%d] = %d\n", i, fa->array[i]);
  }

  // Free the allocated memory
  free(fa);

  return EXIT_SUCCESS;
}
