#include <iostream>
#include <cstdlib>

using namespace std;

// Our tree node with an integer key.  The tree is composed
// of these individual nodes, each pointing to a left and right
// child.  The left/right pointers are 0 if there is no left/right child.
struct node {
    struct node *left;
    struct node *right;
    int val;
};

void inOrderTraversal(node *);
void preOrderTraversal(node *);
void postOrderTraversal(node *);
void dumpTreeSideways(node *, int, int);

int main() {
  node n4 = { 0, 0, 10 };       // left child of value 25
  node n3 = { 0, 0, 30 };       // right child of value 25
  node n2 = { 0, 0, 60 };       // right child of root, value 60
  node n1 = { &n4, &n3, 25 };    // left child of root, value 25
  node root = { &n1, &n2, 55 }; // root node, value 55

  postOrderTraversal(&root);
  return (0);
}

// In-order traversal of a BST with root 'nodep'.
// This function should print all the tree values in order.
void inOrderTraversal(node *nodep) {                            // go left, print value, go right
	if (!nodep)
	return;

	inOrderTraversal(nodep ->left);
    cout << nodep -> val << endl;
    inOrderTraversal(nodep -> right);
  // hint:  To traverse the left side, use: inOrderTraversal(nodep->left))

}


// Pre-order traversal of a BST with root 'nodep'.
void preOrderTraversal(node *nodep) {                           // print value, go left, go right
    if(!nodep){
        return;
    }
    cout << nodep -> val << endl;
    preOrderTraversal(nodep -> left);
    preOrderTraversal(nodep -> right);
}

// Post-order traversal of a BST with root 'nodep'.
void postOrderTraversal(node *nodep) {                  // go left, go right, print value
    if(!nodep){
        return;
    }

    postOrderTraversal(nodep -> left);
    postOrderTraversal(nodep -> right);
    cout << nodep -> val << endl;
}

// Prints the tree sideways, starting with the rightmost node,
// with the root at the left margin.
void dumpTreeSideways(node *nodep, int inc, int space) {
  while (nodep) {
    dumpTreeSideways(nodep->right, inc, space + inc);
    for (int i = 0; i < space; i++)
      cout <<  ' ';
    cout << nodep->val << endl;
    nodep = nodep->left;
    space += inc;
  }
}
