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
public:
        // Class Constructors and Destructors 
        List();
        void deleteList();

        // Access Functions
        int length();
        Node* getHead();

        // Manipulation Procedures
        void prepend(int rank, int freq, string word); // insert int into list 
        void append(int rank, int freq, string word);
        void sort();
        Node* find(string word);
        Node* deleteNode(string);
        void deleteAndFreeNode(string);
        string print();

        // My New Access Functions

        // Swaps values of A and B.     
        List swapNodes(Node A, Node B);

        // Appends 
        List append(Node A);

        // Finds a word in the list, and eithe
        //List updateList(string word);
};
