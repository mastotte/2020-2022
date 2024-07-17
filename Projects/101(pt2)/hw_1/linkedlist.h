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
    DataType rank;
    DataType freq;
    string word;
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
	Node* deleteNode(string);
  void deleteAndFreeNode(string);
	// Access Functions
	int getLength();
	Node* getHead();
	Node* find(string word);

	// Manipulation Procedures
	Node* pop();
	void push(Node* N);
  void prepend(DataType rank, DataType freq, string word); // insert int into list 
	void append(DataType rank, DataType freq, string word);
	void sort();

  // Printing
	string print();
};
