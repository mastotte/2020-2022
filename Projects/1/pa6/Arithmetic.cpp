// * Maxwell Totten, mastotte, 1799187
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstring>
#include "BigInteger.h"
using namespace std;

int main(int argc, char **argv){
    string s1 = "";
    string s2 = "";
    char c;
    FILE* inFile = fopen(argv[1], "r");
    ofstream f;
    f.open(argv[2]);
    BigInteger C, D, E, F, G, H, I, J;
    c = fgetc(inFile);
    while(c!='\n'){
	s1 = s1 + c;
        c = fgetc(inFile);
    }
    while(c == '\n')
	c = fgetc(inFile);
    while(c!=EOF){
	s2 = s2 + c;
	c = fgetc(inFile);
    }
    BigInteger A = BigInteger(s1);
    BigInteger B = BigInteger(s2);
    BigInteger Two = BigInteger("2");
    BigInteger Three = BigInteger("3");
    BigInteger Nine = BigInteger("9");
    BigInteger Sixteen = BigInteger("16");
    //cout<<"S1: "<<s1<<endl;
    //cout<<"S2: "<<s2<<endl;
    // A, B, A+B, A-B, A-A, 3A - 2B, AB, A^2, B^2, 9A^4 + 16B^5
    
    // A --------------------------------------
    //cout<<"A: "<<A<<endl;
    f<<A<<endl<<endl;
    // B --------------------------------------
    //cout<<"B: "<<B<<endl;
    f<<B<<endl<<endl;
    // A+B ------------------------------------
    C = A+B;
    //cout<<"A+B: "<<C<<endl;
    f<<C<<endl<<endl;
    // A-B ------------------------------------
    D = A-B;
    //cout<<"A-B: "<<D<<endl;
    f<<D<<endl<<endl;
    // A-A ------------------------------------
    E = A-A;
    //cout<<"A-A: "<<E<<endl;
    f<<E<<endl<<endl;
    // 3A-2B ----------------------------------
    F = Three*A-Two*B;
    //cout<<"3A-2B: "<<F<<endl;
    f<<F<<endl<<endl;
    // A*B ------------------------------------
    G = A*B;
    //cout<<"A*B: "<<G<<endl;
    f<<G<<endl<<endl;
    // A^2 ------------------------------------
    H = A*A;
    //cout<<"A^2: "<<H<<endl;
    f<<H<<endl<<endl;
    // B^2 ------------------------------------
    I = B*B;
    //cout<<"B^2: "<<I<<endl;
    f<<I<<endl<<endl;
    // 9A^4 + 16B^5 ---------------------------
    J = Nine*A*A*A*A + Sixteen*B*B*B*B*B;
    //cout<<"9A^4 + 16B^5: "<<J<<endl;
    f<<J<<endl<<endl;
    // ----------------------------------------
    
}
