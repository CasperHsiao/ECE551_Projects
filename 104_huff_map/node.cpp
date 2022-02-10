#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (this->sym != NO_SYM) {
    assert(this->left == NULL && this->right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(this->sym, b));
  }
  else {
    assert(this->left != NULL && this->right != NULL);
    BitString bLft = b.plusZero();
    this->left->buildMap(bLft, theMap);
    BitString bRgt = b.plusOne();
    this->right->buildMap(bRgt, theMap);
  }
}
