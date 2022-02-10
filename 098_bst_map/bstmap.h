#ifndef _BST_MAP_H_
#define _BST_MAP_H_

#include <cstdlib>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class TreeNode {
   public:
    K key;
    V val;
    TreeNode * left;
    TreeNode * right;

    TreeNode(const K & k, const V & v) : key(k), val(v), left(NULL), right(NULL) {}
  };

  TreeNode * root;
  void bstMapDtorHelp(TreeNode * node);
  TreeNode * bstMapAddHelp(TreeNode * node, const K & key, const V & value);
  TreeNode * bstMapRemoveHelp(TreeNode * node, const K & key);
  void replaceWithJustLarger(TreeNode * node);
  TreeNode * bstMapCopyHelp(TreeNode * node);

 public:
  virtual void add(const K & key, const V & value);
  virtual const V & lookup(const K & key) const throw(std::invalid_argument);
  virtual void remove(const K & key);
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs);
  BstMap & operator=(const BstMap & rhs);
  virtual ~BstMap();
};

template<typename K, typename V>
BstMap<K, V> & BstMap<K, V>::operator=(const BstMap<K, V> & rhs) {
  if (this != &rhs) {
    TreeNode * temp = bstMapCopyHelp(rhs.root);
    bstMapDtorHelp(root);
    root = temp;
  }
  return *this;
}

template<typename K, typename V>
typename BstMap<K, V>::TreeNode * BstMap<K, V>::bstMapCopyHelp(TreeNode * node) {
  if (node == NULL) {
    return NULL;
  }
  TreeNode * temp = new TreeNode(node->key, node->val);
  temp->left = bstMapCopyHelp(node->left);
  temp->right = bstMapCopyHelp(node->right);
  return temp;
}

template<typename K, typename V>
BstMap<K, V>::BstMap(const BstMap & rhs) {
  root = bstMapCopyHelp(rhs.root);
}

template<typename K, typename V>
void BstMap<K, V>::replaceWithJustLarger(TreeNode * node) {
  TreeNode * parent = node;
  TreeNode * larger = parent->right;
  while (larger->left != NULL) {
    parent = larger;
    larger = larger->left;
  }
  node->key = larger->key;
  node->val = larger->val;
  if (parent == node) {
    parent->right = larger->right;
  }
  else {
    parent->left = larger->right;
  }
  delete larger;
}

template<typename K, typename V>
typename BstMap<K, V>::TreeNode * BstMap<K, V>::bstMapRemoveHelp(TreeNode * node,
                                                                 const K & key) {
  if (node == NULL) {
    return NULL;
  }
  node->left = bstMapRemoveHelp(node->left, key);
  node->right = bstMapRemoveHelp(node->right, key);
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

template<typename K, typename V>
void BstMap<K, V>::remove(const K & key) {
  root = bstMapRemoveHelp(root, key);
}

template<typename K, typename V>
const V & BstMap<K, V>::lookup(const K & key) const throw(std::invalid_argument) {
  TreeNode * curr = root;
  while (curr != NULL) {
    if (curr->key == key) {
      return curr->val;
    }
    else if (key > curr->key) {
      curr = curr->right;
    }
    else {
      curr = curr->left;
    }
  }
  throw std::invalid_argument("Key is not found");
}

template<typename K, typename V>
typename BstMap<K, V>::TreeNode * BstMap<K, V>::bstMapAddHelp(TreeNode * node,
                                                              const K & key,
                                                              const V & value) {
  if (node == NULL) {
    return new TreeNode(key, value);
  }
  if (key > node->key) {
    node->right = bstMapAddHelp(node->right, key, value);
  }
  else if (key < node->key) {
    node->left = bstMapAddHelp(node->left, key, value);
  }
  else {
    node->val = value;
  }
  return node;
}

template<typename K, typename V>
void BstMap<K, V>::add(const K & key, const V & value) {
  root = bstMapAddHelp(root, key, value);
}

template<typename K, typename V>
void BstMap<K, V>::bstMapDtorHelp(TreeNode * node) {
  if (node != NULL) {
    TreeNode * lft = node->left;
    TreeNode * rgt = node->right;
    delete node;
    bstMapDtorHelp(lft);
    bstMapDtorHelp(rgt);
  }
}
template<typename K, typename V>
BstMap<K, V>::~BstMap() {
  bstMapDtorHelp(root);
}

#endif
