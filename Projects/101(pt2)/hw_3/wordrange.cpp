#include <iostream>
#include <fstream>
#include "tree.h"
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;
int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    //int *input_array = new int[2];

    Tree tree;
    int range = 0;
    int r = 0;
    clock_t start, end;
    start = clock();
    Node* root = NULL;
    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string in;
    string key1;
    string key2;
    char prev;
    char command;
    string out;
    int lines = 0;
    while(getline(input,in)){
      lines++;
      command = in[0];
      
      in = in.substr(2,in.length());
      if(command == 'i'){
        root = tree.insert(root,in);
        tree.setRoot(root);
      }
      if(command == 'r' && prev == 'i'){
        tree.assignRanks(root, &r);
        //tree.print(root);
      }
      if(command == 'r'){
        //cout<<lines<<endl;
        key1 = in.substr(0,in.find_first_of(' '));
        key2 = in.substr(in.find_first_of(' ')+1, in.length());
        if(key2 < key1) swap(key2,key1);
        range = tree.findRange(key1,key2);
        //cout<<"Answer: "<<range<<endl;
        output<<range<<endl;
      }
      prev = command;
    }
    cout<<setprecision(2)<<fixed;
    input.close(); //close input stream
    output.close(); // close output stream
    end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<"Time: "<<cpu_time_used<<"s"<<endl;
}
