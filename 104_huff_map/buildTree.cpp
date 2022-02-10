#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t q;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      q.push(new Node(i, counts[i]));
    }
  }
  while (q.size() > 1) {
    Node * mynodeone = q.top();
    q.pop();
    Node * mynodetwo = q.top();
    q.pop();
    Node * combinenode = new Node(mynodeone, mynodetwo);
    q.push(combinenode);
  }
  Node * root = q.top();
  q.pop();
  return root;
}
