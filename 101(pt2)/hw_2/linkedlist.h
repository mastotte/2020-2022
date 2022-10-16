//  Max Totten
//
//  linkedlist.h
//
//
//
#include <string>
using namespace std;
typedef int DataType;
struct Node{
    int **board;
    DataType col; // col coordinate of last queen placed
		DataType row; // row coordinate of last queen placed
    Node *next;
};
class List
{
private:
	// List Fields
	Node* head;
	int length;
public:
	// Class Constructors and Destructors 
	List();
	void deleteList();
	Node* makeNode(int);
	void popDelete();
  void deleteAndFreeNode(string);

	// Access Functions
	int getLength();
	Node* getHead();
	Node* find(string word);

	// Manipulation Procedures
	Node* pop();
	void push(Node* N);
	void append(Node* N);
	void sort();

  // Printing
	string print();
};

