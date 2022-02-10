#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(-1);
    assert(il.head->data == -1);
    for (int i = 0; i < 3; i++) {
      il.addFront(i);
      assert(il.head->next->data == i - 1);
      assert(il.head->data == i);
    }
    assert(il.tail->data == -1);
    assert(il.tail->prev->data == 0);
  }
  // many more tester methods
  void testAddBack() {
    IntList il;
    il.addBack(-1);
    assert(il.head->data == -1 && il.tail->data == -1);
    for (int i = 0; i < 3; i++) {
      il.addBack(i);
      assert(il.tail->data == i);
      assert(il.tail->prev->data == i - 1);
    }
    assert(il.head->data == -1);
    assert(il.head->next->data == 0);
  }

  void testCopy() {
    IntList il1;
    IntList il2;
    for (int i = 0; i < 3; i++) {
      il2.addFront(2 * i);
    }
    il1 = il2;
    IntList il3 = IntList(il1);
    assert(il1.getSize() == 3);
    assert(il2.getSize() == 3);
    assert(il3.getSize() == 3);
    IntList::Node * curr1 = il1.head;
    IntList::Node * curr2 = il2.head;
    IntList::Node * curr3 = il3.head;
    while (curr1 != NULL) {
      assert(curr1->data == curr2->data && curr2->data == curr3->data &&
             curr1->data == curr3->data);
      curr1 = curr1->next;
      curr2 = curr2->next;
      curr3 = curr3->next;
    }
    assert(curr2 == NULL);
    assert(curr3 == NULL);
    assert(il1.head->prev == NULL);
    assert(il2.head->prev == NULL);
    assert(il3.head->prev == NULL);
    assert(il1.head->next->next == il1.tail);
    assert(il2.head->next->next == il2.tail);
    assert(il3.head->next->next == il3.tail);

    IntList::Node * curr4 = il1.tail;
    IntList::Node * curr5 = il2.tail;
    IntList::Node * curr6 = il3.tail;
    while (curr4 != NULL) {
      assert(curr4->data == curr5->data && curr5->data == curr6->data &&
             curr4->data == curr6->data);
      curr4 = curr4->prev;
      curr5 = curr5->prev;
      curr6 = curr6->prev;
    }
    assert(curr5 == NULL);
    assert(curr6 == NULL);
    assert(il1.tail->next == NULL);
    assert(il2.tail->next == NULL);
    assert(il3.tail->next == NULL);
    assert(il1.tail->prev->prev == il1.head);
    assert(il2.tail->prev->prev == il2.head);
    assert(il3.tail->prev->prev == il3.head);

    assert(il1.getSize() == il2.getSize() && il2.getSize() == il3.getSize() &&
           il1.getSize() == il3.getSize());

    IntList il4;
    il3 = il4;
    assert(il3.getSize() == 0);
  }

  void testRemove() {
    IntList il;
    il.addBack(-1);
    for (int i = 0; i < 3; i++) {
      il.addBack(i);
    }
    IntList il2 = IntList(il);
    il.remove(-1);  //rm head
    assert(il.remove(-1) == false);
    assert(il.head->data == 0);
    assert(il.head->prev == NULL);
    il.addBack(0);
    il.remove(0);  //rm head
    assert(il.find(0) > -1);
    assert(il.head->data == 1);
    assert(il.tail->data == 0);
    il.remove(0);  //rm back
    assert(il.remove(0) == false);
    assert(il.tail->next == NULL);
    il.addBack(3);  //123
    il.remove(2);   //rm mid
    assert(il.head->data == 1);
    assert(il.head->next->data == 3);
    assert(il.head->next->next == NULL);
    assert(il.tail->data == 3);
    assert(il.tail->prev->data == 1);
    assert(il.tail->prev->prev == NULL);
    assert(il.getSize() == 2);
    assert(il[il.find(1)] == 1);
    assert(il[il.find(3)] == 3);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
    assert(il.head->next->prev == il.head);
    assert(il.tail->prev->next == il.tail);
    assert(il.remove(2) == false);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);

    il2.remove(0);
    assert(il2.getSize() == 3);
    assert(il2.head->prev == NULL);
    assert(il2.head->data == -1);
    assert(il2.head->next->data == 1);
    assert(il2.head->next->prev->data == -1);
    assert(il2.head->next->next->data == 2);
    assert(il2.head->next->next == il2.tail);
    assert(il2.head->next->next->next == NULL);
    assert(il2.tail->next == NULL);
    assert(il2.tail->data == 2);
    assert(il2.tail->prev->data == 1);
    assert(il2.tail->prev->prev->data == -1);
    assert(il2.tail->prev->prev->next->data == 1);
    assert(il2.tail->prev->prev == il2.head);
    assert(il2.tail->prev->prev->prev == NULL);

    IntList il4 = il2;

    assert(il4.getSize() == 3);
    assert(il4.head->prev == NULL);
    assert(il4.head->data == -1);
    assert(il4.head->next->data == 1);
    assert(il4.head->next->prev->data == -1);
    assert(il4.head->next->next->data == 2);
    assert(il4.head->next->next == il4.tail);
    assert(il4.head->next->next->next == NULL);
    assert(il4.tail->next == NULL);
    assert(il4.tail->data == 2);
    assert(il4.tail->prev->data == 1);
    assert(il4.tail->prev->prev->data == -1);
    assert(il4.tail->prev->prev->next->data == 1);
    assert(il4.tail->prev->prev == il4.head);
    assert(il4.tail->prev->prev->prev == NULL);

    IntList il3;
    for (int i = 0; i < 4; i++) {
      il3.addBack(3);
    }
    il3.remove(3);
    assert(il3.getSize() == 3);
    assert(il3.head->prev == NULL);
    assert(il3.head->data == 3);
    assert(il3.head->next->data == 3);
    assert(il3.head->next->next->data == 3);
    assert(il3.head->next->next == il3.tail);
    assert(il3.tail->next == NULL);
    assert(il3.tail->data == 3);
    assert(il3.tail->prev->data == 3);
    assert(il3.tail->prev->prev->data == 3);
    assert(il3.tail->prev->prev == il3.head);

    IntList il5;
    il5.addFront(7);
    il5.remove(7);
    assert(il5.getSize() == 0);
    assert(il5.head == NULL);
    assert(il5.tail == NULL);
  }

  void testIndexOp() {
    IntList il;
    il.addBack(-1);
    for (int i = 0; i < 3; i++) {
      il.addBack(i);
    }
    int idx = il.find(1);
    assert(il[idx] == 1);
    assert(il[il.find(-1)] == -1);
    assert(il[il.find(0)] == 0);
    assert(il[il.find(1)] == 1);
    assert(il[il.find(2)] == 2);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  t.testAddBack();
  t.testCopy();
  t.testRemove();
  t.testIndexOp();
  return EXIT_SUCCESS;
}
