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
    string name;
    Node *next;
    Node *down;
};
class List
{
private:
	// List Fields
	Node* head;
  Node* tail;
	int length;
  Node* dummy;
public:
	// Class Constructors and Destructors 
	List();
	void deleteList();
	Node* makeNode(string);

  void deleteAndFreeNode(string);

	// Access Functions
	int getLength();
	Node* getHead();
  Node* getTail();
	Node* find(string s);

	// Manipulation Procedures
	Node* pop();
	void push(string s);
  void push_down(Node* N, string s);
	void append(string s);
	void sort();

  // Printing
	string print();
};


