// * Maxwell Totten, mastotte, 1799187
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstring>
#include <time.h>
#include "Dictionary.h"
using namespace std;

int main(int argc, char **argv){
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	Dictionary D;
	clock_t start0,end0,start1,end1,start2,end2;
	int line = 1;
	std::string buf = "";
	start0 = clock();
	while(getline(in,buf)){
		D.setValue(buf, line);
		line++;
	}
	//D.remove("a"); 
	end0 = clock();
	//cout<<D;
	start1 = clock();
	std::string s = D.to_string();
	out<<s;
	end1 = clock();
	start2 = clock();
	std::string s2 = D.pre_string();
	out<<s2;
	end2 = clock();
	double t0,t1,t2;
	t0 = ((double) (end0 - start0)) / CLOCKS_PER_SEC;
	t1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
	t2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
	printf("Setting up RBT : %0.5f\nTo string      : %0.5f\nPreOrder String: %0.5f\n",t0,t1,t2);

}
