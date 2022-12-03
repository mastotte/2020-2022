#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include "linkedlist.h"
#include <string>
#include <vector>
#include <algorithm>

#include <time.h>

using namespace std;
// -------------------------------------------------------------------------------------------------
// SOURCE FOR THE FOLLOWING SECTION - https://slaystudy.com/c-vector-quicksort/
// -------------------------------------------------------------------------------------------------
// last element is taken as pivot
int Partition(vector<string> &v, int start, int end){
	
	int pivot = end;
	int j = start;
	for(int i=start;i<end;++i){
		if(v[i]<v[pivot]){
			swap(v[i],v[j]);
			++j;
		}
	}
	swap(v[j],v[pivot]);
	return j;
	
}
void PrintVector(vector<string> v){
  cout<<" ";
	for(unsigned int i=0;i<v.size();++i)
		cout<<i<<": "<<v[i]<<endl;
}
void Quicksort(vector<string> &v, int start, int end ){

	if(start<end){
		int p = Partition(v,start,end);
		Quicksort(v,start,p-1);
		Quicksort(v,p+1,end);
	}
}
// -------------------------------------------------------------------------------------------------
// END OF CITED SECTION - https://slaystudy.com/c-vector-quicksort/
// -------------------------------------------------------------------------------------------------

string find_path(List actors, string a1, string a2, string seen){
  cout<<"0"<<endl;
  Node* cur = actors.find(a1);
  cout<<"1"<<endl;
  Node* temp = cur->down;
  cout<<"2"<<endl;
  while(temp != NULL && temp->name != "DUMMY_NODE"){
    seen += temp->name;
    cout<<seen<<endl;
    temp = temp->down;
  }
  return "";
}
//void vector_find(vector<vector<string>> v, string s, int low, int high, int *r){
void vector_find(vector<string> v, string s, int low, int high, int *r){
    int mid = (high+low) / 2;
    int q1 = 0;
    int q3 = 0;
    string s1, s_mid, s3;
    //s_mid = v[mid][0];
    s_mid = v[mid];
    while(s_mid != s){
      mid = (high+low) / 2;
      //s_mid = v[mid][0];
      s_mid = v[mid];
      if(s_mid == s){
        //cout<<v[mid][0]<< " equals "<<s<<endl;
        *r = mid;
      }
      q1 = (mid+low) / 2;
      q3 = (mid+high) / 2;
      //s1 = v[q1][0];
      s1 = v[q1];
      //s3 = v[q3][0];
      s3 = v[q3];


      if(s_mid > s){
        //cout<<v[mid][0]<< " greater than "<<s<<endl;
        if(s1 > s){
          high = q1;
        }else{
          low = q1;
          high = mid;
        }
      }
      else if(s_mid < s){
        //cout<<v[mid][0]<< " less than "<<s<<endl;
        if(s3 > s){
          low = mid;
          high = q3;
        }else{
          low = q3;
        }
      }   
    }
}
void load_actor_adjacency(vector<vector<string>> v1, vector<string> v, List movies){
    clock_t start,s2,e2,end;
    double t_find_total;
    Node* cur_x = movies.getHead();
    Node* cur_y;
    Node* temp;
    vector<string>::iterator v2,v3,low,up,low2,up2;

    double cpu_time_used;
    int i = 0;

    start = clock();
    string mid = v[(v.size()-1) / 2];
    string s1 = v[(v.size()-1) / 4];
    string s3 = v[((v.size()-1)*3) / 4];
    while(cur_x != NULL && cur_x->name != "DUMMY_NODE"){
        cur_y = cur_x->down;
        i++;
        if(i%1000 == 0)
          cout<<"i: "<<i<<endl;
        while(cur_y != NULL && cur_y->name != "DUMMY_NODE"){ // the name
            temp = cur_x->down;
            s2 = clock();

            low= lower_bound (v.begin(), v.end(), cur_y->name); //          ^
            up= upper_bound (v.begin(), v.end(), cur_y->name);
            
            v2 = find (low, up, cur_y->name); // index of name's vector
            e2 = clock();
            t_find_total += e2-s2;

            while(temp != NULL && temp->name != "DUMMY_NODE"){ // adding other names to name's adj list
                if(temp != cur_y){
                  // if name is not already present, add it
  
                  v3 = find (v1[v2 - v.begin()].begin(),v1[v2 - v.begin()].end(), temp->name); // index of name's vector
                  if(v3 == v1[v2 - v.begin()].end()){
                    v1[v2 - v.begin()].push_back(temp->name);
                  }
                }
                temp = temp->down;
            }
            cur_y = cur_y->down;
        }
        cur_x = cur_x->next;
    }
    cout<<"End While"<<endl;
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<"Total Time: "<<cpu_time_used<<endl;
    cpu_time_used = ((double) t_find_total) / CLOCKS_PER_SEC;
    cout<<"Search Time: "<<cpu_time_used<<endl;

    cout<<"40174: "<<v1[40174][0]<<endl;
    cout<<"228064: "<<v1[228064][0]<<endl;
    cout<<"77200: "<<v1[77200][0]<<endl;
    cout<<"105476: "<<v1[105476][0]<<endl;
    //for(int i = 0; i < 50; i++){
    PrintVector(v1[105476]);
    cout<<endl;
    //}

}
int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file
    
    string in;
    string out;
    string token = "";
    vector<string> v;
    vector<vector<string>> v1;

    
    //List actors; // format: head = actor, rest of list = actors that are adjacent in map
    List movies; // format: head = movie title, next = actor1, actor2,...
    Node* cur;
    //Node* tmp;
    int lines = 0;
    
    while(getline(input,in)){
      //cout<<in<<endl;
      // set up lists
      lines++;
      cout<<lines<<endl;
      token = in.substr(0,in.find_first_of(" "));
      in = in.substr(in.find_first_of(" ")+1,in.length());
      //cout<<"Token: "<<token<<endl;
      movies.push(token);
      cur = movies.getHead();
      while(in.find_first_of(" ") < in.length()){
          token = in.substr(0,in.find_first_of(" "));
          //cout<<"Token: "<<token<<endl;
          in = in.substr(in.find_first_of(" ")+1,in.length());
          movies.push_down(cur,token);
          v.push_back(token);
      }
    }
    cout<<"sorting"<<endl;
    cout<<"Size: "<<v.size()<<endl;
    Quicksort(v,0,v.size()-1);
    cout<<"sorted"<<endl;
    //PrintVector(v);
    vector<string>::iterator v2;
    v2 = std::unique(v.begin(), v.end());
    //PrintVector(v);
    v.resize(std::distance(v.begin(),v2));
    cout<<"Size: "<<v.size()<<endl;
    for(unsigned int i = 0; i < v.size(); i++){
      v1.push_back(vector<string>());
      v1[i].push_back(v[i]);
    }
    cout<<"Test 1: "<<v1[105476][0]<<endl;
    cout<<"Test 2: "<<v1[115350][0]<<endl;
    int c;
    double cpu_time_used;
    clock_t start, end;
    start = clock(); 
    vector_find(v, "Frank_Marshall", 0, v.size(), &c);
    end = clock();
    cout<<"C : "<< c<<endl;
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<"Time 1: "<<cpu_time_used<<endl;
    start = clock(); 
    v2 = find (v.begin(), v.end(), "Frank_Marshall");
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout<<"Time 2: "<<cpu_time_used<<endl;
    c = v2 - v.begin();
    cout<<"V2 : "<< c<<endl;

    load_actor_adjacency(v1, v, movies);
    string s1 = "Seshadhri";
    string s2 = "John_Wayne";
    string s3 = "";

    
    cout<<"check"<<endl;
    //out = find_path(actors, s1, s2, s3);
    input.close(); //close input stream
    output.close(); // close output stream
    
}
