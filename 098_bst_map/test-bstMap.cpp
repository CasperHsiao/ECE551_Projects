#include <assert.h>

#include <iostream>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> * m = new BstMap<int, int>();
  m->add(0, 1);
  m->add(-5, 2);
  m->add(5, 3);
  m->add(-10, 4);
  m->add(-3, 5);
  m->add(3, 6);
  m->add(10, 7);
  m->add(-15, 8);
  m->add(-4, 9);
  m->add(4, 10);
  m->add(15, 11);
  assert(m->lookup(0) == 1);
  assert(m->lookup(-5) == 2);
  assert(m->lookup(5) == 3);
  assert(m->lookup(-10) == 4);
  assert(m->lookup(-3) == 5);
  assert(m->lookup(3) == 6);
  assert(m->lookup(10) == 7);
  assert(m->lookup(-15) == 8);
  assert(m->lookup(-4) == 9);
  assert(m->lookup(4) == 10);
  assert(m->lookup(15) == 11);
  m->add(0, 0);
  assert(m->lookup(0) == 0);

  BstMap<int, int> mm = *m;
  mm.add(0, 1);
  mm.add(-5, 2);
  mm.add(5, 3);
  mm.add(-10, 4);
  mm.add(-3, 5);
  mm.add(3, 6);
  mm.add(10, 7);
  mm.add(-15, 8);
  mm.add(-4, 9);
  mm.add(4, 10);
  mm.add(15, 11);
  assert(mm.lookup(0) == 1);
  assert(mm.lookup(-5) == 2);
  assert(mm.lookup(5) == 3);
  assert(mm.lookup(-10) == 4);
  assert(mm.lookup(-3) == 5);
  assert(mm.lookup(3) == 6);
  assert(mm.lookup(10) == 7);
  assert(mm.lookup(-15) == 8);
  assert(mm.lookup(-4) == 9);
  assert(mm.lookup(4) == 10);
  assert(mm.lookup(15) == 11);
  mm.add(0, 0);
  assert(mm.lookup(0) == 0);

  /*
  Map<int, int> * mm = new BstMap<int, int>(*m);
  mm->add(0, 1);
  mm->add(-5, 2);
  mm->add(5, 3);
  mm->add(-10, 4);
  mm->add(-3, 5);
  mm->add(3, 6);
  mm->add(10, 7);
  mm->add(-15, 8);
  mm->add(-4, 9);
  mm->add(4, 10);
  mm->add(15, 11);
  assert(mm->lookup(0) == 1);
  assert(mm->lookup(-5) == 2);
  assert(mm->lookup(5) == 3);
  assert(mm->lookup(-10) == 4);
  assert(mm->lookup(-3) == 5);
  assert(mm->lookup(3) == 6);
  assert(mm->lookup(10) == 7);
  assert(mm->lookup(-15) == 8);
  assert(mm->lookup(-4) == 9);
  assert(mm->lookup(4) == 10);
  assert(mm->lookup(15) == 11);
  mm->add(0, 0);
  assert(mm->lookup(0) == 0);
  delete mm;
  */

  //test remove
  //remove subtree roots
  std::cout << "Removing subtree roots" << std::endl;
  m->remove(-5);
  m->remove(5);
  try {
    m->lookup(-5);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }
  try {
    m->lookup(5);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }

  //remove nodes with one child
  std::cout << "Removing nodes with one child" << std::endl;
  m->remove(-10);
  m->remove(-3);
  m->remove(3);
  m->remove(10);
  try {
    m->lookup(-10);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }
  try {
    m->lookup(-3);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }
  try {
    m->lookup(3);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }
  try {
    m->lookup(10);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }

  //remove invalid node
  m->remove(10);

  //remove nodes with two children
  /*
  std::cout << "Removing nodes with two children" << std::endl;
  m->remove(-5);
  m->remove(5);
  try {
    m->lookup(-5);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }
  try {
    m->lookup(5);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }
  */

  //remove nodes with no children
  std::cout << "Removing nodes with no children" << std::endl;
  m->remove(-15);
  m->remove(4);
  try {
    m->lookup(-15);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }
  try {
    m->lookup(4);
  }
  catch (std::invalid_argument & e) {
    std::cout << "Successfully removed node" << std::endl;
  }

  delete m;
}
