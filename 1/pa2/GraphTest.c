//-----------------------------------------------------------------------------
// Maxwell Totten, mastotte, pa2
// GraphTest.c
// 
// This is a fancy test that calculates the Radius and Diameter of 
// the graph defined on lines 41-49, along with its Central and Peripheral 
// vertices.  The definitions of these terms at:
// 
//    http://en.wikipedia.org/wiki/Distance_(graph_theory)
// 
// It also tests the rest of the functions in Graph.c
// 
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   int test;
   printf("\nMaking Lists...\n");
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   List Path = newList();
   Graph G = NULL;
   
   // Build graph G 
   printf("Building Graph...\n");
   G = newGraph(n);
   
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }
   // Testing getFunctions
   printf("Testing getFunctions...\n");
   test = getOrder(G);
   printf("Order = %d\n",test);
   test = getSize(G);
   printf("Size  = %d\n",test);
   test = getSource(G);
   printf("Source = %d\n",test);
   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<n; i++){
      printf("%d\n",i);
      d = get(E);
      printf("-\n");
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }
   
   // Print results 
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");
   //findPath
   for(int i = 1; i < getOrder(G); i++){
	printf("Parent of %d is %d\n",i,getParent(G,i));
   	getPath(Path, G, i);
	freeList(&Path);
	Path = newList();
   }
   //print graph
   
   printGraph(stdout, G);
   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeList(&Path);
   freeGraph(&G);
   return(0);
}
