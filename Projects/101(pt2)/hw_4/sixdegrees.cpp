#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include "linkedlist.h"
#include <string>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <bits/stdc++.h>



using namespace std;

// -------------------------------------------------------------------------------------------------
// SOURCE FOR THE FOLLOWING SECTION - https://www.geeksforgeeks.org/shortest-path-unweighted-graph/?ref=lbp
// -------------------------------------------------------------------------------------------------
// a modified version of BFS that stores predecessor
// of each vertex in array p
// and its distance from source in array d
bool BFS(vector<vector<int>> adj, int src, int dest, int v,
         int pred[], int dist[])
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    list<int> queue;
 
    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];
 
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (unsigned int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // We stop BFS when we find
                // destination.
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
 
// utility function to print the shortest distance
// between source vertex and destination vertex
vector<int> printShortestDistance(vector<vector<int>> adj, int s,
                           int dest, int v)
{
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];
    vector<int> path;
    if (BFS(adj, s, dest, v, pred, dist) == false) {
 
        path.insert(path.begin(),-1);
        return path;
    }
 
    // vector path stores the shortest path
    
    int crawl = dest;
    path.insert(path.begin(),crawl);
    while (pred[crawl] != -1) {
        path.insert(path.begin(),pred[crawl]);
        crawl = pred[crawl];
    }
 
    /*// distance from source is in distance array
    cout << "Shortest path length is : "
         << dist[dest];
 
     //printing path from source to destination
    cout << "\nPath is::\n";
    //for (int i = path.size() - 1; i >= 0; i--)
        //cout << path[i] << " ";*/

    return path;
}
// -------------------------------------------------------------------------------------------------
// END OF CITED SECTION - https://www.geeksforgeeks.org/shortest-path-unweighted-graph/?ref=lbp
// -------------------------------------------------------------------------------------------------
vector<vector<int>> load_actor_adjacency(vector<vector<string>> v1, vector<string> v, vector<vector<int>> t, List movies){
    
    Node* cur_x = movies.getHead();
    Node* cur_y;
    Node* temp;
    vector<string>::iterator v2,v3,v4,low,up,low2,up2;


    int i = 0;


    while(cur_x != NULL && cur_x->name != "DUMMY_NODE"){
        cur_y = cur_x->down;
        i++;
        //if(i%10000 == 0)
          //cout<<"i: "<<i<<endl;
        while(cur_y != NULL && cur_y->name != "DUMMY_NODE"){ // the name
            temp = cur_x->down;


            low= lower_bound (v.begin(), v.end(), cur_y->name); //          ^
            up= upper_bound (v.begin(), v.end(), cur_y->name);
            
            v2 = find (low, up, cur_y->name); // index of name's vector

            while(temp != NULL && temp->name != "DUMMY_NODE"){ // adding other names to name's adj list
                if(temp != cur_y){
                  // if name is not already present, add it
                  
                  v3 = find (v1[v2 - v.begin()].begin(),v1[v2 - v.begin()].end(), temp->name); // index of name's vector
                  if(v3 == v1[v2 - v.begin()].end()){

                    v1[v2 - v.begin()].push_back(temp->name);
                    low2= lower_bound (v.begin(), v.end(), temp->name); // find int value for conversion
                    up2= upper_bound (v.begin(), v.end(), temp->name);
                    v4 = find(low2, up2, temp->name);
                    t[v2 - v.begin()].push_back(v4 - v.begin());
                  }
                }
                temp = temp->down;
            }
            cur_y = cur_y->down;
        }
        cur_x = cur_x->next;
    }
    return t;
    
}
string find_movies(vector<int> path, List movies, vector<string> v){
    string out;
    vector<string>::iterator v2,low,up;
    Node* cur;
    Node* dwn;
    Node* low_movie;
    bool n1 = false;
    bool n2 = false;
    string name1 = "";
    string name2 = "";
    for(unsigned int i = 0; i < path.size()-1; i++){
      cur = movies.getHead();

      n1 = false;
      n2 = false;
      name1 = v[path[i]];
      name2 = v[path[i+1]];
      while(cur != NULL && cur->name != "DUMMY_NODE"){
        dwn = cur->down;
        n1 = false;
        n2 = false;
        while((dwn != NULL && dwn->name != "DUMMY_NODE")&&(!(n1&&n2))){
          if(dwn->name == name1) n1 = true;
          if(dwn->name == name2) n2 = true;
          dwn = dwn->down;
        }
        if(n1 && n2)
          low_movie = cur;

        cur = cur->next;
      }
      out += name1 + " -(" + low_movie->name + ")- ";
      
    }
    
    out += name2;
    return out;
}
int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./sixdegrees <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open("cleaned_movielist.txt");// open input file
    output.open(argv[2]); // open output file
    
    string in;
    string out;
    string token = "";
    vector<string> v;
    vector<int> path;
    vector<vector<int>> t;
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
      //cout<<lines<<endl;
      token = in.substr(0,in.find_first_of(" "));
      in = in.substr(in.find_first_of(" ")+1,in.length());
      //cout<<"Token: "<<token<<endl;
      movies.push(token);
      cur = movies.getHead();
      while(in.find_first_of(" ") < in.length()){
          token = in.substr(0,in.find_first_of(" "));
          //cout<<"Token: "<<token<<endl;
          in = in.substr(in.find_first_of(" ")+1,in.length());
          //if(token.length() < 2){
            //cout<<"T: "<<token<<endl;
          //}
          movies.push_down(cur,token);
          v.push_back(token);
      }
    }

    //Quicksort(v,0,v.size()-1);
    sort(v.begin(),v.end());
    sort(v.begin(),v.end());
 
    //PrintVector(v);
    vector<string>::iterator v2, low, up;
    v2 = std::unique(v.begin(), v.end());
    //PrintVector(v);
    v.resize(std::distance(v.begin(),v2));
    for(unsigned int i = 0; i < v.size(); i++){
      v1.push_back(vector<string>());
      v1[i].push_back(v[i]);
      t.push_back(vector<int>());
      t[i].push_back((int)i);
    }

    

    t = load_actor_adjacency(v1, v, t, movies);

 

    input.close();
    input.open(argv[1]);
    int index1 = 0;
    int index2 = 0;
    bool abort = false;
    while(getline(input,in)){
      abort = false;
      token = in.substr(0,in.find_first_of(" "));
      in = in.substr(in.find_first_of(" ")+1,in.length());

      low= lower_bound (v.begin(), v.end(), token); //
      up= upper_bound (v.begin(), v.end(), token);
      v2 = find (low, up, token); // 
      index1 = (v2 - v.begin());
      if(v[index1] != token) abort = true; // if name 1 isn't found
      
      low= lower_bound (v.begin(), v.end(), in); //
      up= upper_bound (v.begin(), v.end(), in);
      v2 = find (low, up, in); //
      index2 = (v2 - v.begin());
      if(v[index2] != in) abort = true; // if name 2 isn't found

      if(index1 == index2) abort = true; // if name 1 and name 2 are the same

      if(!abort){
        path = printShortestDistance(t, index1, index2, v.size());
        if(path[0] == -1){
          out = "Not present";
        }else{
          out = find_movies(path, movies, v);
        }
      }else{
        if(index1 == index2){
          out = v[index1];
        }else{
          out = "Not present";
        }
      }
      //cout<<out<<endl;
      output<<out<<endl;
    }
    //out = find_path(actors, s1, s2, s3);
    input.close(); //close input stream
    output.close(); // close output stream    
}
