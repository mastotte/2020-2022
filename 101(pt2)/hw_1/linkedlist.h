//  Max Totten
//
//  linkedlist.h
//
//
//    See pa5 List
#include <string>
using namespace std;

struct Node{
    int rank;
    int freq;
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
        void prepend(int rank, int freq, string word); // insert int into list 
	void append(int rank, int freq, string word);
	void sort();

	string print();
	
};
