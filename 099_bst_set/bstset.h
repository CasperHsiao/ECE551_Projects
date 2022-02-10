#ifndef _BST_SET_H_
#define _BST_SET_H_

#include <cstdlib>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
  class TreeNode {
   public:
    T key;
    TreeNode * left;
    TreeNode * right;

    TreeNode(const T & k) : key(k), left(NULL), right(NULL) {}
  };

  TreeNode * root;
  void bstSetDtorHelp(TreeNode * node);
  TreeNode * bstSetAddHelp(TreeNode * node, const T & key);
  TreeNode * bstSetRemoveHelp(TreeNode * node, const T & key);
  void replaceWithJustLarger(TreeNode * node);
  TreeNode * bstSetCopyHelp(TreeNode * node);

 public:
  virtual void add(const T & key);
  virtual bool contains(const T & key) const;
  virtual void remove(const T & key);
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs);
  BstSet & operator=(const BstSet & rhs);
  virtual ~BstSet();
};

template<typename T>
BstSet<T> & BstSet<T>::operator=(const BstSet<T> & rhs) {
  if (this != &rhs) {
    TreeNode * temp = bstSetCopyHelp(rhs.root);
    bstSetDtorHelp(root);
    root = temp;
  }
  return *this;
}

template<typename T>
typename BstSet<T>::TreeNode * BstSet<T>::bstSetCopyHelp(TreeNode * node) {
  if (node == NULL) {
    return NULL;
  }
  TreeNode * temp = new TreeNode(node->key);
  temp->left = bstSetCopyHelp(node->left);
  temp->right = bstSetCopyHelp(node->right);
  return temp;
}

template<typename T>
BstSet<T>::BstSet(const BstSet & rhs) {
  root = bstSetCopyHelp(rhs.root);
}

template<typename T>
void BstSet<T>::replaceWithJustLarger(TreeNode * node) {
  TreeNode * parent = node;
  TreeNode * larger = parent->right;
  while (larger->left != NULL) {
    parent = larger;
    larger = larger->left;
  }
  node->key = larger->key;
  if (parent == node) {
    parent->right = larger->right;
  }
  else {
    parent->left = larger->right;
  }
  delete larger;
}

template<typename T>
typename BstSet<T>::TreeNode * BstSet<T>::bstSetRemoveHelp(TreeNode * node,
                                                           const T & key) {
  if (node == NULL) {
    return NULL;
  }
  node->left = bstSetRemoveHelp(node->left, key);
  node->right = bstSetRemoveHelp(node->right, key);
  if (node->key == key) {
    if (node->left == NULL) {
      TreeNode * temp = node->right;
      delete node;
      return temp;
    }
    else if (node->right == NULL) {
      TreeNode * temp = node->left;
      delete node;
      return temp;
    }
    else {
      replaceWithJustLarger(node);
    }
  }
  return node;
}

template<typename T>
void BstSet<T>::remove(const T & key) {
  root = bstSetRemoveHelp(root, key);
}

template<typename T>
bool BstSet<T>::contains(const T & key) const {
  TreeNode * curr = root;
  while (curr != NULL) {
    if (curr->key == key) {
      return true;
    }
    else if (key > curr->key) {
      curr = curr->right;
    }
    else {
      curr = curr->left;
    }
  }
  return false;
}

template<typename T>
typename BstSet<T>::TreeNode * BstSet<T>::bstSetAddHelp(TreeNode * node, const T & key) {
  if (node == NULL) {
    return new TreeNode(key);
  }
  if (key > node->key) {
    node->right = bstSetAddHelp(node->right, key);
  }
  else if (key < node->key) {
    node->left = bstSetAddHelp(node->left, key);
  }
  return node;
}

template<typename T>
void BstSet<T>::add(const T & key) {
  root = bstSetAddHelp(root, key);
}

template<typename T>
void BstSet<T>::bstSetDtorHelp(TreeNode * node) {
  if (node != NULL) {
    TreeNode * lft = node->left;
    TreeNode * rgt = node->right;
    delete node;
    bstSetDtorHelp(lft);
    bstSetDtorHelp(rgt);
  }
}
template<typename T>
BstSet<T>::~BstSet() {
  bstSetDtorHelp(root);
}

#endif
