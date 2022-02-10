#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  int count = 1;
  size_t maxCount = count;
  int prev = array[0];
  for (int i = 1; i < n; i++) {
    int curr = array[i];
    if (curr > prev) {
      count++;
    }
    else {
      count = 1;
    }
    if (count > maxCount) {
      maxCount = count;
    }
    prev = curr;
  }
  return maxCount;
}
