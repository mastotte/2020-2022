//-----------------------------------------------------------------------------
// Maxwell Totten, mastotte, pa6
// BigInteger.cpp
// Math for BIIIIIIIIIIG integers
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
}
// Dictionary()
// Constructor that creates a new Dictionary
Dictionary::Dictionary(){
	nil = new Node("NIL NODE",-1);
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
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
    postOrderDelete(root);
    
    //printf("DESTRUCTOR END\n");
}
// Helper Functions (Optional) ---------------------------------------------
// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R->key != "NIL NODE"){
	inOrderString(s,R->left);
	s = s+R->key + " : " + std::to_string(R->val)+"\n";
	//s = R->key + " : " + std::to_string(R->val)+" (p: "+R->parent->key+")"+"(l,r):("+R->left->key+","+R->right->key+")\n"+s;
	inOrderString(s,R->right);
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
    if(R->key != "NIL NODE"){
	s = s+"\n"+R->key;
	preOrderString(s, R->left);
	preOrderString(s, R->right);
    } 
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
Dictionary::Node* Dictionary::preOrderCopy(Node* R, Node* N){
	if(R->key != "NIL NODE"){
		setValue(R->key, R->val);
		preOrderCopy(R->left, nil);
		//setValue(R->key, R->val);
		preOrderCopy(R->right, nil);
	}	



	/*
    	if((R->key != "NIL NODE")&&(R->key != N->key)){
                Node* left = preOrderCopy(R->left,N);
                Node* right = preOrderCopy(R->right,N);
                Node* newNode = new Node(R->key, R->val);
		num_pairs++;
                newNode->left = left;
                newNode->right = right;
		return newNode;
        }
	return nil;      */    
}
//Node* copy_tree(Node* n){
//base case n = null
//left = copy n.left_child- recursive
//right = copy n.right_child-recursive
//new_node = new node
//new_node.children = left, right
//copy 'data' of n into new node
//return new_node
	
// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
	/*if(num_pairs == 1){
		std::string s = this->to_string();
		std::cout<<s<<std::endl;
		R = nil;
	}*/
	//std::cout<<num_pairs<<std::endl;
	if(R->key != "NIL NODE"){
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		if(R->key != root->key)
			remove(R->key);
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    //if(num_pairs == 0) return nil;
    Node* n = R;
    //std::cout<<"NUM PAIRS: "<<num_pairs<<std::endl;
    if(root->key == "NIL NODE"){
	//std::cout<<"ROOT IS NIL\n";
    }
    if((R->key == "NIL NODE")||(k == R->key)){
	return R;
    }
    while((n->key != "NIL NODE")&&(n->key != k)){
	if(k < n->key){
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
	//current = N;
	//printf("ranNext ");
	//std::cout<<"\n"<<N->key<<"'s children: "<<N->children()<<std::endl;
	Node* rightMost = findMax(root);
	//std::cout<<"RightMost: "<<rightMost->key;
	if(N->key == rightMost->key){
		//printf("Next:NIL\n");
		return N;
	}
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
	if(N->key == leftMost->key){
                //printf("Next:NIL\n");
        	return N;
        }
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
    if(n->key == "") result = false;
    if(n->key == " ") result = false;
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
    if(current->key == "NIL NODE"){
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
	return "NIL CURRENT";
    }	
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(hasCurrent()){	
        return current->val;
    }else{
	return current->val;
    }
}


// Manipulation procedures -------------------------------------------------
// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
     postOrderDelete(root);   
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
     //printf("set call\n");
     //std::cout << "Root->key: " << root->key << std::endl;
     Node* prev;
     Node* newNode = new Node(k,v);
     newNode->left = nil;
     newNode->right = nil;
     newNode->parent = nil;
     char side = ' ';
     if(root->key == "NIL NODE"){
	root = newNode;
	num_pairs++;
     }else{
	current = search(root, k);
	if(current->key != "NIL NODE"){
     		current->val = v;
	}else{
		current = root;
		prev = current;
		while(current->key != "NIL NODE"){
			//printf("while\n");
			prev = current;
			if((k < current->key)&&(current->key != "NIL NODE")){
				current = current->left;
				side = 'l';
			}else if((k > current->key)&&(current->key != "NIL NODE")){
				current = current->right;
				side = 'r';
			}
		}
		if(side == 'r'){
			prev->right = newNode;
		}else if(side == 'l'){
			prev->left = newNode;
		}else{
			printf("side not r or l?\n");
		}
		newNode->parent = prev;
		num_pairs++;
     	}
   }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
	std::cout<<"Removing "<<k<<std::endl;
	if(contains(k)){
	    std::cout<<"contains...";
	    current = search(root, k);
	    Node* temp;
	// Case 1: K is a leaf
	    if(current->children() == 0){
		if(current->key == current->parent->right->key){
			current->parent->right = nil;
		}else{
			current->parent->left = nil;
		}
		temp = current;
		//std::cout<<"Deleting "<<temp->key<<std::endl;
		delete(temp);
		current = nil;
	    }
	// Case 2: K has 1 child
	    else if(current->children() == 1){
		char side = ' ';
		// Linking parent to current's child
		if(current->key == current->parent->right->key){
                        side = 'r';
                }else{
                        side = 'l';
                }
		if(current->left->key != "NIL NODE"){
			temp = current;
			current = current->left;
			if(side == 'r'){ 
			    temp->parent->right = current;
			}else if(side == 'l'){
			     temp->parent->left = current;
			}
		}else if(current->right->key != "NIL NODE"){
                        temp = current;
			current = current->right;
			if(side == 'r'){
                            temp->parent->right = current;
                        }else if(side == 'l'){
                             temp->parent->left = current;
                        }
                }
		current->parent = temp->parent;
		//std::cout<<"Deleting "<<temp->key<<std::endl;
		delete(temp);
	    
			
	// Case 3: K has 2 children  
	    }else if(current->children() == 2){
		while(current->children() != 0){
			if(current->right->key != "NIL NODE"){
				std::cout<<"R: Replacing "<<current->key<<" with "<<current->right->key<<std::endl;
				current->key = current->right->key;
				current->val = current->right->val;
				current = current->right;
			}else if(current->left->key != "NIL NODE"){
				std::cout<<"L: Replacing "<<current->key<<" with "<<current->left->key<<std::endl;
				current->key = current->left->key;
				current->val = current->left->val;
				current = current->left;
			}
		}
		current->parent->right = nil;
		current->parent->left = nil;
		//temp = current;
		//std::cout<<"Deleting "<<current->key<<std::endl;
		delete(current);
		current = nil;
	   }
	   num_pairs--;		
	}
	
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
    std::string s1;
    std::string s2;
    Dictionary A,B;
    A = *this;
    B = D;
    s1 = to_string();
    s2 = D.to_string();
    //std::cout<<std::endl<<"A string: "<<s1;
    //std::cout<<std::endl<<"B string: "<<s2;
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
