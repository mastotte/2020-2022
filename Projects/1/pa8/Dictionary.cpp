//-----------------------------------------------------------------------------
// Maxwell Totten, mastotte, pa8
// Dictionary.cpp
// Dictionary ADT
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdexcept>
#include <math.h>
#include "Dictionary.h"
// Class Constructors & Destructors ----------------------------------------
// Node()
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    color = 'r';
}
// Dictionary()
// Constructor that creates a new Dictionary
Dictionary::Dictionary(){
	nil = new Node("NIL NODE",-1);
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
	nil->color = 'b';
	root = nil;
	current = nil;
	num_pairs = 0;
}
// Dictionary()
// Constructor that creates a copy of N.
Dictionary::Dictionary(const Dictionary& N){
   nil = N.nil;
   root = N.root;
   //current = N.current;
   num_pairs = N.num_pairs;
   preOrderCopy(N.root, N.nil);
}
Dictionary::~Dictionary(){
    if(num_pairs == 0){
	delete(nil);
    }else if(num_pairs == 1){
	delete(root);
	delete(nil);
    }else{
    	postOrderDelete(root);
	delete(nil);
    }
}
// Helper Functions (Optional) ---------------------------------------------
// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R!=nil){
        if(R->left != nil){
	    inOrderString(s,R->left);
        }
        s += R->key + " : " + std::to_string(R->val)+"\n";
        if(R->right != nil){
            inOrderString(s,R->right);
        }
    }
}
// isLeaf(Node*)
// Returns if the current is a leaf or not
int Dictionary::Node::children(){
	int count = 0;
	if(right->key != "NIL NODE"){
		count++;
	}
	if(left->key != "NIL NODE"){
		count++;
	}
	return count;
}
// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
	s += R->key+"\n";
	if(R->left != nil){
		preOrderString(s, R->left);
	}
	if(R->right != nil){
		preOrderString(s, R->right);
	}
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
	if(R->key != "NIL NODE"){
		setValue(R->key, R->val);
		preOrderCopy(R->left, nil);
		preOrderCopy(R->right, nil);   
	}
}
	
// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
	if(R != nil){
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		if(R == R->parent->right) R->parent->right = nil;
		else R->parent->left = nil;
		delete(R);
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if(R->key == k) return R;
    if(R == nil) return nil;
    Node* n = R;
    while((n->key != "NIL NODE")&&(n->key != k)){
	if(k <= n->key){
	    n = n->left;
	}else{
	    n = n->right;
	}
    }
    return n;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
	if(num_pairs == 0) return nil;
	Node* n = R;
	while(n->left->key != "NIL NODE"){
		n = n->left;
	}
	return n;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
	if(num_pairs == 0) return nil;
	Node* n = R;
	while(n->right->key != "NIL NODE"){
		n = n->right;
	}
	return n;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk. If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	if(num_pairs == 0) return nil;
	Node* n;
	Node* rightMost = findMax(root);
	if(N->key == rightMost->key) return nil;
	if(N->children() == 0){
		n = N;
		if(N->key == N->parent->right->key){
			while((n->key == n->parent->right->key)&&(n->key != root->key)){
				n = n->parent;
			}
			return n->parent;
		}else{
			return N->parent;
		}
	}else if(N->children() == 1){
		n = N;
		if(N->right->key != "NIL NODE"){
			return N->right;
		}else{
			if(n->key == n->parent->right->key){
				while(n->left->key != "NIL NODE"){
					n = n->left;
				}
				return n;
			}else{
				return n->parent;
			}
		}
	}else if(N->children() == 2){ // children == 2
		n = N->right;
		while(n->left->key != "NIL NODE"){
			n = n->left;
		}
		return n;
	}
	return nil;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
	if(num_pairs == 0) return nil;
	Node* n;
	Node* leftMost = findMin(root);
	if(N->key == leftMost->key) return nil;
	if(N->children() == 0){
                n = N;
                if(N->key == N->parent->left->key){
                        while((n->key == n->parent->left->key)&&(n->key != root->key)){
                                n = n->parent;
                        }
                        return n->parent;
                }else{
                        return N->parent;
                }
        }else if(N->children() == 1){
                n = N;
                if(N->left->key != "NIL NODE"){
                        return N->left;
                }else{
                        if(n->key == n->parent->left->key){
                                while(n->right->key != "NIL NODE"){
                                        n = n->right;
                                }
                                return n;
                        }else{
                                return n->parent;
                        }
                }
        }else if(N->children() == 2){ // children == 2
                n = N->left;
                while(n->right->key != "NIL NODE"){
                        n = n->right;
                }
                return n;
        }
        return nil;
}
// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    Node *n = search(root, k);
    bool result = true;
    if(n->key == "NIL NODE") result = false;
    return result;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    Node *n = search(root, k);
    return (n->val);
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if(current == nil){
	return false;	
    }else{
    	return true;
    }
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(hasCurrent()){
	return current->key;
    }else{
	throw std::logic_error("current key is nil");
    }	
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(hasCurrent()){
    	return current->val;
    }else{
	throw std::logic_error("current val is nil");
    }
}


// Manipulation procedures -------------------------------------------------
 // LeftRotate()
void Dictionary::LeftRotate(Node* x){
    // set y
    Node* y = x->right;

    // turn y's left subtree into x's right subtree
    x->right = y->left;
    
    if(y->left != nil){
	y->left->parent = x;
    }
    // link y's parent to x
    y->parent = x->parent;
    if(x->parent == nil){
	root = y;
	//y->parent = nil;
    }else if(x == x->parent->left){
	x->parent->left = y;
    }else{
	x->parent->right = y;
    }
    // put x on y's left
    y->left = x;
    x->parent = y;	
}

// RightRotate()
void Dictionary::RightRotate(Node* x){
    // set y
    Node* y = x->left;
    
    // turn y's right subtree into x's left subtree
    x->left = y->right;
    
    if(y->right != nil){
	y->right->parent = x;
    }
    // link y's parent to x
    y->parent = x->parent;
    if(x->parent == nil){
	root = y;
	//y->parent = nil;
    }else if(x == x->parent->right){
	x->parent->right = y;
    }else{
	x->parent->left = y;
    }
  
    // put x on y's right
    y->right = x;
    x->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* z){
    Node* y;
    while(z->parent->color == 'r'){
	if(z->parent == z->parent->parent->left){
	    y = z->parent->parent->right;
	    if(y->color == 'r'){
		z->parent->color = 'b';
		y->color = 'b';
		z->parent->parent->color = 'r';
		z = z->parent->parent;
	    }else{
		if(z == z->parent->right){
		    z = z->parent;
		    LeftRotate(z);
		}
		z->parent->color = 'b';
		z->parent->parent->color = 'r';
		RightRotate(z->parent->parent);
	    }
	}else{
	    y = z->parent->parent->left;
	    if(y->color == 'r'){
		z->parent->color = 'b';
		y->color = 'b';
		z->parent->parent->color = 'r';
		z = z->parent->parent;
	    }else{
		if(z == z->parent->left){
		    z = z->parent;
		    RightRotate(z);
		}
		z->parent->color = 'b';
		z->parent->parent->color = 'r';
		LeftRotate(z->parent->parent);
	    }
	}
    }
    root->color = 'b';
}
// RB_Insert()
void Dictionary::RB_Insert(keyType k, valType v, char call){
    Node* y = nil;
    Node* x = root;
    while((x != nil)&&(x->key!=k)){
	y = x;
	if(k < x->key){
	    x = x->left;
	}else{
	    x = x->right;
	}
    }

    if(x->key == k){
	if(call == 's'){
	    x->val = v;
	}else{
	    x->val += 1;
	}
    }else{
	Node* z = new Node(k,v);
    	z->parent = y;
    	if(y == nil){
	    root = z;
    	}else if(z->key < y->key){
	    y->left = z;
    	}else{
	    y->right = z;
	}
        z->left = nil;
        z->right = nil;
        z->color = 'r';
        num_pairs++;
        RB_InsertFixUp(z);
    }
}
// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil){
	root = v;
    }else if(u == u->parent->left){
	u->parent->left = v;
    }else{
	u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* x){
    Node* w;
    while((x != root)&&(x->color == 'b')){
	if(x == x->parent->left){
	    w = x->parent->right;
	    if(w->color == 'r'){
	 	w->color = 'b';
		x->parent->color = 'r';
		LeftRotate(x->parent);
	   	w = x->parent->right;
	    }
	    if((w->left->color == 'b')&&(w->right->color == 'b')){
		w->color = 'r';
		x = x->parent;
	    }else{
	    	if(w->right->color == 'b'){
		    w->left->color = 'b';
	  	    w->color = 'r';
		    RightRotate(w);
		    w = x->parent->right;
	        }
	        w->color = x->parent->color;
	        x->parent->color = 'b';
	        w->right->color = 'b';
	        LeftRotate(x->parent);
	        x = root;
	    }
	}else{
	    w = x->parent->left;
	    if(w->color == 'r'){
		w->color = 'b';
		x->parent->color = 'r';
		RightRotate(x->parent);
		w = x->parent->left;
	    }
	    if((w->right->color == 'b')&&(w->left->color == 'b')){
		w->color = 'r';
		x = x->parent;
	    }else{
		if(w->left->color == 'b'){
		    w->right->color = 'b';
		    w->color = 'r';
		    LeftRotate(w);
		    w = x->parent->left;
		}
		w->color = x->parent->color;
		x->parent->color = 'b';
		w->left->color = 'b';
		RightRotate(x->parent);
		x = root;
	    }
	}
    }
    x->color = 'b';    
}

// RB_Delete()
void Dictionary::RB_Delete(Node* z){
    Node* y = z;
    Node* x;
    int y_original_color = y->color;
    if(z->left == nil){
	x = z->right;
	RB_Transplant(z, z->left);
    }else{
	y = findMin(z->right);
	y_original_color = y->color;
	x = y->right;
	if(y->parent == z){
	    x->parent = y;
	}else{
	    RB_Transplant(y, y->right);
	    y->right = z->right;
	    y->right->parent = y;
	}
	RB_Transplant(z, y);
	y->left = z->left;
	y->left->parent = y;
	y->color = z->color;
    }
    if(y_original_color == 'b'){
	RB_DeleteFixUp(x);
    }
    num_pairs--;
}

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
     postOrderDelete(root);
     num_pairs = 0;
     current = nil;
     root = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
	RB_Insert(k, v, 's');
}
// remove()
void Dictionary::remove(keyType k){
	Node* x = search(root, k);
	if(current == x)
		current = nil;
	RB_Delete(x);
	delete(x);
}


// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
  if(root->key != "NIL NODE"){
    current = root;
    while(current->left->key != "NIL NODE"){
	current = current->left;
    }
  }else{
     current = nil;
  }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
  if(root->key != "NIL NODE"){
    current = root;
    while(current->right->key != "NIL NODE"){
        current = current->right;
    }
  }else{
     current = nil;
  }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
	if(hasCurrent()){
		current = findNext(current);
	}
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
	if(hasCurrent()){
		current = findPrev(current);
	}
}
// incrementValue(k)
// Increments key K's value by 1.
void Dictionary::incrementValue(keyType k){
    RB_Insert(k, 1, 'i');
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s;
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s;
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    std::string s1 = to_string();
    std::string s2 = D.to_string();
    return (s1 == s2);
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    std::string s = D.to_string();
    return stream<<s;
}


// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    this->preOrderCopy(D.root, D.nil);
    return *this;
}
