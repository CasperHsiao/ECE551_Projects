#include <assert.h>

#include <cmath>
#include <cstdlib>
#include <ostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);
class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int maxInvoke;
  if (high > low) {
    maxInvoke = log2(high - low) + 1;
  }
  else {
    maxInvoke = 1;
  }
  CountedIntFn * countFn = new CountedIntFn(maxInvoke, f, mesg);
  int ans = binarySearchForZero(countFn, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "Not expected %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  LinearFunction fn;
  SinFunction sn;
  check(&sn, 0, 150000, 52359, "Sin\n");
  check(&fn, -1, 3, 0, "Regular\n");
  check(&fn, -3, -1, -2, "Negative\n");
  check(&fn, 1, 3, 1, "Positive\n");
  return EXIT_SUCCESS;
}
