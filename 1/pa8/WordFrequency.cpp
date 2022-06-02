//-----------------------------------------------------------------------------
// Maxwell Totten, mastotte, pa8
// WordFrequency.cpp
// Outputs frequency of words found in a file, using a dictionary
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Dictionary.h"
using namespace std;

int main(int argc, char **argv){
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    string s;
    string s2;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    int x,y;
    Dictionary D;
    while(getline(in,s)){
	for (size_t i=0; i<s.length(); ++i){
		if(isupper(s[i])){
    			s[i] = tolower(s[i]);
		}
	}
	s2 = " ";
	y = 0;
	while((s2!="")&&(y != -1)){
	    x = s.find_first_not_of(delim);
	    if(x == -1) break;
	    s = s.substr(x);
	    y = s.find_first_of(delim);
	    s2 = s.substr(0,y);
	    if(y != -1){
	    	s = s.substr(y);
	    }
	    D.incrementValue(s2);
	}
	s = "";
    }
    s2 = D.to_string();
    out<<s2;
    out<<endl;
    return 0;
}
