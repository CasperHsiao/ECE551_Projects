#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

unsigned helper(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  return x * helper(x, y - 1);
}

unsigned power(unsigned x, unsigned y) {
  return helper(x, y);
}
