#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  high = high - 1;
  while (high > low) {
    int mid = (high + low);
    if (mid % 2 == 1) {
      mid = mid / 2 + 1;
    }
    else {
      mid /= 2;
    }

    int val = f->invoke(mid);
    if (val > 0) {
      high = mid - 1;
    }
    else if (val < 0) {
      low = mid;
    }
    else {
      low = mid;
    }
  }
  return low;
}
