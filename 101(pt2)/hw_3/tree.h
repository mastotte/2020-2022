//  Max Totten
//
//  tree.h
//
//
//
#include <string>
using namespace std;
struct Node{
    string key;
    Node* left;
    Node* right;
		int height;
    int rank;
};
class Tree
{
private:
	// Tree Fields
	Node* root;
	Node* dummy;
	int size;
public:
	// Class Constructors and Destructors 
	Tree();
	void deleteTree();
	Node* newNode(string);

	// Access Functions
	Node* getRoot();
  void setRoot(Node *N);
	Node* find(string word);
	int getSize();
	int getHeight(Node* N);

	// Other
  void assignRanks(Node* N, int *r);

// -------------------------------------------------------------------------------------------------
// SOURCE FOR THE FOLLOWING SECTION - https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// -------------------------------------------------------------------------------------------------
  int max(int a, int b);
  Node* rightRotate(Node* y);
	Node* leftRotate(Node* x);
	int getBalance(Node* N);
  Node* insert(Node* node, string key);
// -------------------------------------------------------------------------------------------------
// END OF CITED SECTION - https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
// -------------------------------------------------------------------------------------------------
  int findRange(string key1, string key2);
  // Printing
	void print(Node* N);
};
