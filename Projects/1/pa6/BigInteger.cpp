//-----------------------------------------------------------------------------
// Maxwell Totten, mastotte, pa6
// BigInteger.cpp
// Math for BIIIIIIIIIIG integers
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdexcept>
#include <math.h>
#include "BigInteger.h"
const long power = 9;
const long base = 10;
// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
	signum = 0;
	List digits;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){	
	int start = 0;
        int end = 0;
	std::string sign = "";
        std::string sub = "";
        std::string result = "";
	// Remove sign
	sub = s.substr(0,1);
        if(sub == "-"){
	     signum = -1;
	     s = s.substr(1);
	}else if(sub == "+"){
	     signum = 1;
	     s = s.substr(1);
	}else{
	     signum = 1;
	}
	// Remove leading Non-Numbers and Zeroes
	end = s.find_first_of("123456789");
	s = s.substr(end);
	// Parse string
        while(end != -1){
            end = s.find_first_not_of("0123456789");
            sub = s.substr(0,end);
            result = result + "" + sub;
            start = end+1;
            s = s.substr(start);
        }
	// Put string into list, separated by numbers less than base
	while(result.length() > power){
		sub = result.substr(result.length()-power);
		digits.insertAfter(stol(sub));
		result = result.substr(0,result.length()-power);
	}
	if(result.length() > 0)
		digits.insertAfter(stol(result));
	
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
	signum = N.signum;
	digits = N.digits;
}

// Helper Functions --------------------------------------------------------
// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
}
// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
}
// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List &L){
	// Delete Leading Zeroes
	L.moveFront();
	while(L.peekNext() == 0) L.eraseAfter();
	const long b = pow(base, power);
	bool positive;
	std::string s = "";
	if(L.length() > 0)
		s = L.to_string();
	int SIZE = s.length();
	int positive_sum[SIZE] = {0};
	int negative_sum[SIZE] = {0};
	int result[SIZE] = {0};
	long current = 0;
	int shift = 1;
	int sum = 0;
	int sign = 0;
	int p = 1; // places
	L.moveBack();
	for(int index = 1; index <= L.length(); index++){
		current = L.peekPrev();
		positive = (current>=0);
		if(!positive) current = current*-1;
		while(current >= b){
			current = current/b;
			p++;
		}
		current = L.peekPrev();
		if(!positive) current = current*-1;
		for(int i = 0; i < p; i++){
			if(positive){
			    positive_sum[SIZE-i-shift] += current%b;
			    if(positive_sum[SIZE-i-shift] > b){
				positive_sum[SIZE-i-shift] = positive_sum[SIZE-i-shift]%b;
				positive_sum[SIZE-i-shift-1] += 1;
			    }
			    //printf("[%d] = %d\n",SIZE-i-shift,positive_sum[SIZE-i-shift]);
			}else{ 
			    negative_sum[SIZE-i-shift] += current%b;
			    if(negative_sum[SIZE-i-shift] > b){
                                negative_sum[SIZE-i-shift] = negative_sum[SIZE-i-shift]%b;
                                negative_sum[SIZE-i-shift-1] += 1;
                            }
			    //printf("[%d] = %d\n",SIZE-i-shift,negative_sum[SIZE-i-shift]);
			}
			current = current/b;
		}
		p = 1;
		shift++;
		L.movePrev();
	}
	// Find if negative_sum is greater than positive_sum
	for(int i = 0; i < SIZE; i++){
		if(positive_sum[i]>negative_sum[i]){
			sign = 1;
			break;
		}
		if(negative_sum[i]>positive_sum[i]){ 
			sign = -1;
			break;
		}
	}
	// If negative is greater, do -1*(negative-positive), else do positive-negative
	if(sign == -1){
		for(int i = SIZE-1; i > 0; i--){
			sum = negative_sum[i] - positive_sum[i];
			while(sum<0){
				sum += b;
				negative_sum[i-1] = negative_sum[i-1] - 1;	
			}
			result[i] = sum;
		}
	}
	if(sign == 1){
		for(int i = SIZE-1; i > 0; i--){
			sum = positive_sum[i] - negative_sum[i];
			while(sum<0){
				sum += b;
				positive_sum[i-1] = positive_sum[i-1] - 1;
					
			}
			result[i] = sum;
		}			
	}
	// Transfer contents of result into List
	int index = 0;
	L.clear();
	while(result[index] == 0) //move to leading digit
		index++;
	while(index < SIZE){
		L.insertBefore(result[index]);
		index++;
	}
	return sign;
}

// shiftList()
// APPENDS p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
	L.moveBack();
	for(int i = 0; i < p; i++){
		L.insertBefore(0);
	}
}
// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
	L.moveFront();
	long n;
	for(int i = 0; i < L.length(); i++){
		n = L.peekNext();
		L.setAfter(m*n);
		L.moveNext();
	}
}
 // Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
	return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	if(signum > N.signum) return 1;
	if(signum < N.signum) return -1;
	List A, B;
	A = this->digits;
	B = N.digits;
	if(A.length() > B.length()) return 1;
	if(B.length() > A.length()) return -1;
	A.moveFront();
	B.moveFront();
	for(int i = 0; i < A.length(); i++){
                if(B.peekNext()>A.peekNext()){
                        return -1;
                }
                if(A.peekNext()>B.peekNext()){
                        return 1;
                }
		A.moveNext();
		B.moveNext();
        }
	return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	digits.clear();
	signum = 0;	
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
	signum = signum*-1;
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	BigInteger Sum, a, b;
	List A, B;
	a = *this;
	b = N;
	A = a.digits;
	B = b.digits;
	A.moveBack();
	B.moveBack();
	long s = 0;
	while(A.position() > 0 || B.position() > 0){
		
		if(A.position() > 0)
			s += a.signum*A.peekPrev();
		
		if(B.position() > 0)
			s += b.signum*B.peekPrev();
	
		if(A.position() > 0)
	                A.movePrev();
	        if(B.position() > 0)
	                B.movePrev();
		
		Sum.digits.insertAfter(s);
		s = 0;
	}
	Sum.signum = normalizeList(Sum.digits);
	return Sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
        BigInteger Diff, b;
	b = N;
	b.negate();
	Diff =  (*this).add(b);
	return Diff;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
	BigInteger Prod,A,B,Dummy;
	List b;

	A = *this;
        B = N;
        A.signum *= normalizeList(A.digits);
        B.signum *= normalizeList(B.digits);
	Dummy.signum = B.signum;
	A.digits.moveFront();
	B.digits.moveFront();

	for(int m = 0; m < A.digits.length(); m++){
		b = B.digits;
		scalarMultList(b, A.digits.peekNext());
		Dummy.digits = b;
		shiftList(Dummy.digits,A.digits.length()-m-1);
		Prod += Dummy;
		A.digits.moveNext();
	}
	if(A.signum == B.signum){
		Prod.signum = 1;
	}else if((A.signum == 0)||(B.signum == 0)){
		Prod.signum = 0;
	}else{
		Prod.signum = -1;
	}
	return Prod;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
	std::string s = "";
	std::string result = "";
	List L = this->digits;
	L.moveBack();
	for(int i = L.length(); i > 0; i--){
		s = std::to_string(L.peekPrev());
		while((s.length() < power)&&(L.position()!=1)){
			s = "0" + s;
		}
		result = s + result;
		s = "";
		L.movePrev();
	}
	if(signum == -1){
		result = "-" + result;
	}else if(signum == 0){
		result = "0";
	}
	  
	
	return result;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	std::string s = N.to_string();
	return stream<<s;
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	int result = A.compare(B);
	if(result == 0){
		return 1;
	}else{
		return 0;
	}
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	int result = B.compare(A);
	if(result == 1){
		return 1;
	}else{
		return 0;
	}
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	int result = B.compare(A);
	if(result == -1){
		return 0;
	}else{
		return 1;
	}
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	int result = A.compare(B);
	if(result == 1){
		return 1;
	}else{
		return 0;
	}
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	int result = A.compare(B);
	if(result == -1){
		return 0;
	}else{
		return 1;
	}
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	BigInteger Sum = A.add(B);
	return Sum;
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	A = A.add(B);
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	BigInteger Diff = A.sub(B);
	return Diff;
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	A = A.sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	BigInteger Product = A.mult(B);
	return Product;
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	A = A.mult(B);
	return A;
}

