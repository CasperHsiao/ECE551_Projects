#include "bstset.h"

int main(void) {
  BstSet<int> * s = new BstSet<int>();
  s->add(1);
  delete s;
}
