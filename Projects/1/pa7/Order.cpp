// * Maxwell Totten, mastotte, 1799187
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstring>
#include "Dictionary.h"
using namespace std;

int main(int argc, char **argv){
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	Dictionary D;
	int line = 1;
	std::string buf = "";
	while(getline(in,buf)){
		D.setValue(buf, line);
		line++;
	} 
	std::string s = D.to_string();
	out<<s;
	std::string s2 = D.pre_string();
	out<<s2;
}
