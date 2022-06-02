//-----------------------------------------------------------------------------
// Maxwell Totten, mastotte, pa5
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
// Private Constructor --------------------------------------------------------
// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}
// Class Constructors & Destructors -------------------------------------------
// Creates a new List in the empty state
List::List(){
   frontDummy = new Node(-9999);
   backDummy = new Node(9999);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   afterCursor = nullptr;
   beforeCursor = nullptr;
   num_elements = 0;
   pos_cursor = 0;
}
// Copy Constructor
List::List(const List& Q){
   frontDummy = new Node(-9999);
   backDummy = new Node(9999);
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   afterCursor = nullptr;
   beforeCursor = nullptr;
   num_elements = 0;
   pos_cursor = 0;
   Node* N = Q.frontDummy->next;
    
   for(int i = 0; i < Q.num_elements; i++){
      this->insertBefore(N->data);
      N = N->next;
   }
}
// Destructor
List::~List(){  
   moveFront();
   int num = num_elements;
   for(int i = 0; i < num; i++){
      eraseAfter();
   }
   delete(frontDummy);
   delete(backDummy);
   
}
// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
// OutFile,"\n");
ListElement List::peekPrev() const{
    return beforeCursor->data;
}
// Manipulation procedures ---------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
        //printf("clear\n");
	moveFront();
	int num = num_elements;
	for(int i = 0; i < num; i++){
		eraseAfter();
	}
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if(pos_cursor == num_elements){
        throw std::range_error("List: moveNext(): At end");
    }
    Node* temp;
    temp = afterCursor->next;
    beforeCursor = afterCursor;
    afterCursor = temp;
    pos_cursor += 1;
    return peekPrev();
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(pos_cursor == 0){
        throw std::range_error("List: movePrev(): At front");
    }
    Node* temp;
    temp = beforeCursor->prev;
    afterCursor = beforeCursor;
    beforeCursor = temp;
    pos_cursor -= 1;
    return peekNext();
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* NewNode = new Node(x);
    if (num_elements == 0){
	NewNode->prev = frontDummy;
	NewNode->next = backDummy;
        afterCursor = NewNode;
        beforeCursor = frontDummy;
        frontDummy->next = NewNode;
        backDummy->prev = NewNode;
    }else{
        NewNode->prev = beforeCursor;
        NewNode->next = afterCursor;
	afterCursor->prev = NewNode;
        beforeCursor->next = NewNode;
        afterCursor = NewNode;
    }
    //printf("Prev: %d   Next: %d\n",NewNode->prev->data,NewNode->next->data);
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* NewNode = new Node(x);
    if (num_elements == 0){
        backDummy->prev = NewNode;
        frontDummy->next = NewNode;
	afterCursor = backDummy;
        beforeCursor = NewNode;
	NewNode->next = backDummy;
	NewNode->prev = frontDummy;
    }else{
        afterCursor->prev = NewNode;
        beforeCursor->next = NewNode;
        NewNode->prev = beforeCursor;
        NewNode->next = afterCursor;
	beforeCursor = NewNode;
    }
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if(pos_cursor > num_elements){
        throw std::range_error("List: setAfter(): Cursor past back");
    }
    if(pos_cursor == num_elements){
        throw std::range_error("List: setAfter(): Cursor at back");
    }
    afterCursor->data = x;  
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(pos_cursor <= 0){
        throw std::range_error("List: setBefore(): Cursor is <= 0");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){ 
    if(pos_cursor == num_elements){
        throw std::range_error("List: eraseAfter(): Cursor at back");
    }
    Node* After = afterCursor->next;
    delete(afterCursor);
    After->prev = beforeCursor;
    beforeCursor->next = After;
    afterCursor = After;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(pos_cursor == 0){
        throw std::range_error("List: eraseBefore(): Cursor at front");
    }
    Node* Before = beforeCursor->prev;
    delete(beforeCursor);
    Before->next = afterCursor;
    afterCursor->prev = Before;
    beforeCursor = Before;
    pos_cursor--;
    num_elements--;
}
// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    if(pos_cursor == num_elements)return -1;
    
    while((pos_cursor < num_elements)&&(peekNext() != x)){
        moveNext();
    }
    if(peekNext() != x){
        return -1;
    }else if(pos_cursor < num_elements){
	moveNext();
    }
    return pos_cursor;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    if(pos_cursor == 0)return -1;
    while((pos_cursor > 0)&&(peekPrev() != x)){
        movePrev();
    }
    if(peekPrev() != x){
        return -1;
    }else if(pos_cursor > 0){
	movePrev();
    }
    return pos_cursor;   
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    int Position = pos_cursor;
    moveFront();
    for(int i = 0; i < num_elements; i++){
	moveFront();
	for(int j = 0; j <= i; j++){
		moveNext();
	}
	
	if(findNext(peekPrev()) != -1){
		if(pos_cursor <= Position)Position--;
		eraseBefore();
		i--;
	}
    }
    moveFront();
    for(int k=0;k<num_elements;k++){
        moveNext();
    }
    moveFront();
    while(pos_cursor != Position){
	moveNext();
    }
    
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List NewList;
    Node* N = frontDummy->next;
    Node* M = L.frontDummy->next;
    for(int i=0;i<num_elements;i++){
        NewList.insertBefore(N->data);
	N = N->next;
    }
    for(int i=0;i<L.num_elements;i++){
        NewList.insertBefore(M->data);
	M = M->next;   
    }
    NewList.moveFront();
    return NewList;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N;
    if(num_elements == 0){
	throw std::range_error("List: to_string(): empty List");
    }
    std::string s = "(";

    for(N=frontDummy->next; N!=backDummy; N=N->next){
        s += std::to_string(N->data)+",";
    }
    s.pop_back();
    s += ")";
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    List t, r;
    r = R;
    t = *this;
    r.moveFront();
    t.moveFront();
    if(num_elements != r.num_elements){
	return false;
    }
    for(int i = 0; i < r.num_elements; i++){
            if(r.peekNext() != t.peekNext()){
                return false;
            }
            r.moveNext();
	    t.moveNext();
    }
    return true;
}
// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if( this != &L ){ // not self assignment
      // make a copy of L
      List temp = L;
      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(beforeCursor, temp.beforeCursor);
     }
   // return this with the new data installed
   return *this;
   // the copy, if there is one, is deleted upon return
}









