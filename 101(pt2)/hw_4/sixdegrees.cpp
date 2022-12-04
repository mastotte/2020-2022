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

#include <time.h>

using namespace std;
// -------------------------------------------------------------------------------------------------
// SOURCE FOR THE FOLLOWING SECTION - https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
// -------------------------------------------------------------------------------------------------
// Structure to represent a min heap node
int NO_PARENT = 0;
struct MinHeapNode
{
    int  v;
    int dist;
};
// Structure to represent a min heap
struct MinHeap
{  
    // Number of heap nodes present currently
    int size;      
    // Capacity of min heap
    int capacity; 
    // This is needed for decreaseKey()
    int *pos;   
    struct MinHeapNode **array;
};
 
// A utility function to create a
// new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*)
      malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*)
      malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(
            capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**)
                 malloc(capacity *
       sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist <
         minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist <
         minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode =
             minHeap->array[smallest];
        MinHeapNode *idxNode =
                 minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest],
                         &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if
// the given minHeap is empty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract
// minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode =
         minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasekey dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete
    // tree is not heapified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist <
           minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =
                                      (i-1)/2;
        minHeap->pos[minHeap->array[
                             (i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], 
                 &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
void printPath(int currentVertex, int parents[])
{
    // Base case : Source node has
    // been processed
    if (currentVertex == 0) {
        return;
    }
    printPath(parents[currentVertex], parents);
    cout << currentVertex << " ";  
}
vector<int> dijkstra(vector<vector<int>> t, int src, int target)
{
     
    // Get the number of vertices in graph
    int V = t.size();
    cout<<"V = "<<V<<endl;
    // dist values used to pick
    // minimum weight edge in cut
    int dist[V];
    int parent[V];
    vector<int> path;
       
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all
    // vertices. dist value of all vertices
    cout<<"2"<<endl;
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        parent[v] = -1;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    
    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] =
          newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the following loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    cout<<"3"<<endl;
    //for(int i = 1; i <= 300001; i+=10000){
     // cout<<i<<": dist: "<<dist[i]<<" parent: "<<parent[i]<<endl;
    //}
    int visited = 0;
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode* minHeapNode =
                     extractMin(minHeap);
       
        // Store the extracted vertex number
        int u = minHeapNode->v;
        /*cout<<"Vertex: "<<t[u][0]<<endl;
        for(int i = 1; i < t[u].size()-1; i++){
          cout<<i<<": "<<t[u][i]<<endl;
        }*/
 
        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        //int pCrawl = t[u][1];
                                     //graph->array[u].head;
        //while (pCrawl != NULL)
        for(int pCrawl = 1; pCrawl < t[u].size()-1; pCrawl++)
        {
            int v = t[u][pCrawl];
            visited++;
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            //if(dist[u] == V) cout<<"possible"<<endl;
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 1 + dist[u] < dist[v])
            {
                dist[v] = dist[u] + 1;
                parent[v] = u;
 
                // update distance
                // value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
        }
    }
    //cout<<"DISTANCE TO TARGET: "<<dist[target]<<endl;
    cout<<"VISITED: "<<visited<<endl;
    //printPath(target, parent);
    if(dist[target] == V){
      path[0] == -1;
      return path;
    }
    int current = target;
    int inf_blocker = 0;
    while(current != parent[src] && inf_blocker < V){
      path.insert(path.begin(),current);
      current = parent[current];
      inf_blocker++;
    }
    if(inf_blocker == V){
      path[0] = -1;
    }
    cout<<"5"<<endl;
    cout<<endl;
    for(int i = 0; i < 15; i++){
      cout<<path[i]<<" , ";
    }
    cout<<endl;
    return path;
    // print the calculated shortest distances
    //printArr(dist, V);
}
// -------------------------------------------------------------------------------------------------
// END OF CITED SECTION - https://slaystudy.com/c-vector-quicksort/
// -------------------------------------------------------------------------------------------------

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
void PrintVector_int(vector<int> v){
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
vector<vector<int>> load_actor_adjacency(vector<vector<string>> v1, vector<string> v, vector<vector<int>> t, List movies){
    clock_t start,s2,e2,end;
    double t_find_total;
    Node* cur_x = movies.getHead();
    Node* cur_y;
    Node* temp;
    vector<string>::iterator v2,v3,v4,low,up,low2,up2;

    double cpu_time_used;
    int i = 0;

    start = clock();
    string mid = v[(v.size()-1) / 2];
    string s1 = v[(v.size()-1) / 4];
    string s3 = v[((v.size()-1)*3) / 4];
    while(cur_x != NULL && cur_x->name != "DUMMY_NODE"){
        cur_y = cur_x->down;
        i++;
        if(i%10000 == 0)
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
    
    cout<<"V1 size: "<<v1.size()<<endl;
    return t;
    //}
}
string find_movies(vector<int> path, List movies, vector<string> v){
    string out;
    vector<string>::iterator v2,low,up;
    Node* cur;
    Node* dwn;
    bool n1 = false;
    bool n2 = false;
    string name1 = "";
    string name2 = "";
    cout<<"finding movies"<<endl;
    for(int i = 0; i < path.size()-1; i++){
      cur = movies.getHead();

      n1 = false;
      n2 = false;
      name1 = v[path[i]];
      name2 = v[path[i+1]];
      while((cur != NULL && cur->name != "DUMMY_NODE")&&(!(n1&&n2))){
        dwn = cur->down;
        while((dwn != NULL && dwn->name != "DUMMY_NODE")&&(!(n1&&n2))){
          if(dwn->name == name1) n1 = true;
          if(dwn->name == name2) n2 = true;
          dwn = dwn->down;
        }
        if(!n1 || !n2)
          cur = cur->next;
      }
      out += name1 + " -(" + cur->name + ")- ";
    }
    out += name2;
    return out;
}
int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
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
    cout<<"sorting"<<endl;
    cout<<"Size: "<<v.size()<<endl;
    //Quicksort(v,0,v.size()-1);
    sort(v.begin(),v.end());
    sort(v.begin(),v.end());
    cout<<"sorted"<<endl;
    //PrintVector(v);
    vector<string>::iterator v2, low, up;
    v2 = std::unique(v.begin(), v.end());
    //PrintVector(v);
    v.resize(std::distance(v.begin(),v2));
    cout<<"Size: "<<v.size()<<endl;
    for(unsigned int i = 0; i < v.size(); i++){
      v1.push_back(vector<string>());
      v1[i].push_back(v[i]);
      t.push_back(vector<int>());
      t[i].push_back((int)i);
    }
    
    //for(int i = 0; i < 300; i++){
     // cout<<i<<": "<<t[i][0]<<endl;
      
    //}
    
    
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

    t = load_actor_adjacency(v1, v, t, movies);
    
    PrintVector(v1[11129]);
    PrintVector_int(t[11129]);
    PrintVector(v1[202494]);
    PrintVector_int(t[202494]);

    input.close();
    input.open(argv[1]);
    int index1 = 0;
    int index2 = 0;
    bool abort = false;
    int block = 0;
    while(getline(input,in)&&block<2){
      abort = false;
      block++;
      token = in.substr(0,in.find_first_of(" "));
      in = in.substr(in.find_first_of(" ")+1,in.length());

      low= lower_bound (v.begin(), v.end(), token); //
      up= upper_bound (v.begin(), v.end(), token);
      v2 = find (low, up, token); // 
      index1 = (v2 - v.begin());
      if(v2 == v.end()) abort = true; // if name 1 isn't found
      
      low= lower_bound (v.begin(), v.end(), in); //
      up= upper_bound (v.begin(), v.end(), in);
      v2 = find (low, up, in); //
      index2 = (v2 - v.begin());
      if(v2 == v.end()) abort = true; // if name 2 isn't found

      if(index1 == index2) abort = true; // if name 1 and name 2 are the same

      if(!abort){
        cout<<"dijkstra-ing: "<<v[index2]<<"("<<index2<<") to ";
        cout<<v[index1]<<"("<<index1<<")"<<endl;
        path = dijkstra(t, index2, index1);
        if(path[0] == -1){
          out = "Not present\n";
        }else{
          out = find_movies(path, movies, v);
        }
      }else{
        out = "Not present\n";
      }
      cout<<out<<endl;
      output<<out<<endl;
    }
    //out = find_path(actors, s1, s2, s3);
    input.close(); //close input stream
    output.close(); // close output stream
    


    /*!! NOTE
    v1, vector of numbers,
    v, vector of strings as a translator for v1.*/
}
