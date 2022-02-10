#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int array[], size_t n, size_t ans) {
  size_t result = maxSeq(array, n);
  if (result != ans) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  int arr1[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  run_check(arr1, 10, 4);
  int arr2[] = {2, 2, 2, 2, 2, 5};
  run_check(arr2, 6, 2);
  int arr3[] = {5, 4, 3, 2, 1, 0};
  run_check(arr3, 6, 1);
  int arr4[] = {-1, 0, 2, 2, 2, 5};
  run_check(arr4, 6, 3);
  int arr5[1] = {0};
  run_check(arr5, 0, 0);
  return EXIT_SUCCESS;
}
