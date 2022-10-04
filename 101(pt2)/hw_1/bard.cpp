#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <cstring>
#include "linkedlist.h"
#include <string>
// ---------------------------!!! USED hello.cpp AS TEMPLATE !!!-----------------------------
using namespace std;
// using namespace utils; // for the function defined in utils
//
// notes for myself:
// .length() function is really slow, create len reference in list if speed is needed
int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./bard <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file
    string word;
    Node* cursor;
    int len = 0;
    List Table[35]; // (len of word -5) 
    
    input.open("shakespeare-cleaned5.txt"); // open input file
    output.open(argv[2]); // open output file

    //int line_counter = 1;
    while(std::getline (input,word)){
	//cout<<line_counter<<endl;
        //line_counter++;
    	len = word.length()-5;  
	if(Table[len].getLength() == 0){
	    Table[len].prepend(1,1,word);
	}else{
	    cursor = Table[len].find(word);
	    if(cursor!=NULL){
		cursor->freq += 1;
	    }else{
		Table[len].append(Table[len].getLength(),1,word);
	    }
	}
	//cout<<word<<" "<<len<<endl;
    }
    for(int i = 0; i < 35; i++){
	Table[i].sort();
	//cout<<"table "<<i<<" sorted"<<endl;
    }

    input.close(); //close input stream
    input.open(argv[1]); // open new input stream
    int space_index;
    string num1, num2;
    int w_length,w_rank;
    while(std::getline (input, word)){
	space_index = word.find_first_of(" ");
	num1 = word.substr(0,space_index);
	num2 = word.substr(space_index+1,word.length());
	w_length = stoi(num1);
	w_rank = stoi(num2);
        cursor = Table[w_length-5].getHead();
	
	for(int i = 0; i < w_rank; i++){
	    if(cursor!=NULL){
		cursor = cursor->next;
	    }	
        }
	if(cursor!=NULL){
	    output<<cursor->word<<endl;
	}else{
	    output<<"-"<<endl;
	}
    }
    
    for(int i = 8; i < 9; i++){
	    cursor = Table[i].getHead();
	    cout<<"---------------------------- List "<<i<<" ------------------------------"<<endl;
	    for(int j = 0; j < 20; j++){
	    	cout<<cursor->word<<"	Rank: "<<cursor->rank<<"	Freq: "<<cursor->freq<<endl;
	        cursor = cursor->next;
	    }
    }
    for(int i = 0; i < 35; i++){
	Table[i].deleteList();
    }
    input.close();
    output.close(); // close output stream
}

