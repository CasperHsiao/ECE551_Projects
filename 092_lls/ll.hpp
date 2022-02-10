#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class Index_Excep : public std::exception {
 public:
  virtual const char * what() const throw() { return "Invalid index!\n"; }
};

class Tester;

template<typename T>
class LinkedList {
  class Node {
   public:
    T data;
    Node * prev;
    Node * next;
    Node() : data(T()), prev(NULL), next(NULL) {}
    Node(const T & d, Node * p, Node * n) : data(d), prev(p), next(n) {}
  };

  Node * head;
  Node * tail;
  int size;

  Node * removeElem(Node * node, const T & item);

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs);
  ~LinkedList();
  LinkedList & operator=(const LinkedList & rhs);

  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item) const;
  int getSize() const { return this->size; }
  friend class Tester;
};

template<typename T>
typename LinkedList<T>::Node * LinkedList<T>::removeElem(Node * node, const T & item) {
  if (node == NULL) {
    return NULL;
  }
  if (node->data == item) {
    Node * temp = node->next;
    if (this->tail == node) {
      this->tail = node->prev;
      if (this->tail != NULL) {
        this->tail->next = NULL;
      }
    }
    delete node;
    this->size--;
    return temp;
  }
  node->next = removeElem(node->next, item);
  if (node->next != NULL) {
    node->next->prev = node;
  }
  return node;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
  Node * curr = rhs.head;
  while (curr != NULL) {
    this->addBack(curr->data);
    curr = curr->next;
  }
  this->size = rhs.size;
}

template<typename T>
LinkedList<T>::~LinkedList() {
  while (this->head != NULL) {
    Node * temp = head->next;
    delete this->head;
    this->head = temp;
  }
}

template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs) {
  if (this != &rhs) {
    LinkedList temp(rhs);
    Node * tHead = this->head;
    Node * tTail = this->tail;
    size_t tSize = this->size;
    this->head = temp.head;
    this->tail = temp.tail;
    this->size = temp.size;
    temp.head = tHead;
    temp.tail = tTail;
    temp.size = tSize;
  }
  return *this;
}

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  Node * node = new Node(item, NULL, this->head);
  if (this->size == 0) {
    this->head = node;
    this->tail = node;
  }
  else {
    this->head->prev = node;
    this->head = node;
  }
  this->size++;
}

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  Node * node = new Node(item, this->tail, NULL);
  if (this->size == 0) {
    this->head = node;
    this->tail = node;
  }
  else {
    this->tail->next = node;
    this->tail = node;
  }
  this->size++;
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  if (this->size == 0) {
    return false;
  }
  int oldSz = this->size;
  head = removeElem(head, item);
  if (head != NULL) {
    head->prev = NULL;
  }
  return this->size < oldSz;
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  int currIdx = 0;
  Node * curr = this->head;
  while (currIdx < index && curr != NULL) {
    curr = curr->next;
    currIdx++;
  }
  if (curr == NULL) {
    throw Index_Excep();
  }
  return curr->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  int currIdx = 0;
  Node * curr = this->head;
  while (currIdx < index) {
    curr = curr->next;
    currIdx++;
  }
  if (curr == NULL) {
    throw Index_Excep();
  }
  return curr->data;
}

template<typename T>
int LinkedList<T>::find(const T & item) const {
  Node * curr = this->head;
  int idx = 0;
  while (curr != NULL and curr->data != item) {
    curr = curr->next;
    idx++;
  }
  if (curr != NULL) {
    return idx;
  }
  return -1;
}

#endif
