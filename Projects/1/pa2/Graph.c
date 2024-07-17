/****************************************************************************************
 * *  Maxwell Totten
 * *  mastotte
 * *  pa2
 * *****************************************************************************************/
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
typedef struct GraphObj{
	List *Neighbors;
	char *Color;
	int Order;
	int Size;
	int Source;
}GraphObj;
typedef struct NodeObj* Node;
typedef struct CursorObj* Cursor;

typedef struct NodeObj{
	int data;
	Node next;
}NodeObj;

typedef struct CursorObj{
	Node node;
	int index;
}CursorObj;

typedef struct ListObj{
	Node front;
	Node back;
	int Distance;
	int length;
	int parent;
	Cursor cursor;
}ListObj;
/*** Constructors-Destructors ***/
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->Neighbors = calloc(n,sizeof(ListObj));
	G->Color = calloc(n,sizeof(char)+1);
	
	for(int i = 0; i <= n; i++){
		G->Neighbors[i] = newList();
		G->Neighbors[i]->parent = NIL;		
		G->Neighbors[i]->length = 0;
	}		
	G->Order = n;
	return G;	
}
List getList(Graph G, int i){
        return G->Neighbors[i];
}
void freeGraph(Graph* pG){
	
	if(pG!=NULL && *pG!=NULL){
		for(int i = 0; i < getOrder(*pG); i++){
			freeList(&(*pG)->Neighbors[i]);
			
		}
		free((*pG)->Color);
		free((*pG)->Neighbors);
	}
	free(*pG);
	*pG = NULL;
}
/*** Access functions ***/
int getOrder(Graph G){
	return G->Order;
}

int getSize(Graph G){
	return G->Size;
}

int getSource(Graph G){
	return G->Source;
}

int getParent(Graph G, int u){
	return G->Neighbors[u]->parent;
}

int getDist(Graph G, int u){
	return G->Neighbors[u]->Distance;
}

void getPath(List L, Graph G, int u){
	if(((length(L) > getOrder(G))||(G->Neighbors[u]->parent == NIL))&&(u != getSource(G))){
		L->length = INF;
		return;
	}
	if(getSource(G) != u){
		prepend(L, u);
		getPath(L, G, G->Neighbors[u]->parent);
	}	
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
	for(int i = 1; i <= G->Order; i++){
		freeList(&G->Neighbors[i]);
	}	
}

void addEdge(Graph G, int u, int v){
	addArc(G,u,v);
	addArc(G,v,u);
	G->Size -= 1;
}

void addArc(Graph G, int u, int v){
	int sortCount = 1;
        int temp = 0;
        Node current;
        prepend(G->Neighbors[u],v);
        current = G->Neighbors[u]->front;
	G->Color[u] = 'w';
	G->Color[v] = 'w';
        while(sortCount > 0){
		sortCount = 0;
		for(int i = 0; i < G->Neighbors[u]->length; i++){
                	if(current->data > current->next->data){
                        	temp = current->next->data;
                        	current->next->data = current->data;
                        	current->data = temp;
                        	sortCount++;
                	}else{
				current = current->next;
			}
		}
		current = G->Neighbors[u]->front;
        }
	G->Neighbors[u]->length++;
        G->Size += 1;	
}

void BFS(Graph G, int s){
	G->Source = s;
	List L = newList();
	for(int i = 0; i < getOrder(G); i++){
		G->Color[i] = 'w';
		G->Neighbors[i]->parent = NIL;
	}
	Node current;
	prepend(L, s);
	current = L->front;
	int di = 0;
	for(int j = 0; j < length(L); j++){
                BFS_Helper(G, current->data, L, di);
		di++;
		current = current->next;
        }
	freeList(&L);
}
void BFS_Helper(Graph G, int s, List L, int di){
	Node current;
	current = G->Neighbors[s]->front;
	for(int i = 0; i < G->Neighbors[s]->length; i++){
		if(G->Color[current->data] == 'w'){
			append(L,current->data);
			G->Neighbors[current->data]->parent = s;
			setDistance(G, current->data);
			G->Color[current->data] = 'g';
		}else if(G->Color[current->data] == 'g'){
			append(L,current->data);
		}
		current = current->next;
	}
	G->Color[s] = 'b';
}
void setDistance(Graph G, int s){
	int d = 0;
	int temp = s;
	while((getParent(G,temp) != NIL)&&(d < getOrder(G))){
		d++;
		temp = getParent(G, temp);
	}
	G->Neighbors[s]->Distance = d;
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	Node current;
	for(int i = 1; i < G->Order; i++){
		fprintf(out,"\n%d:",i);
		current = G->Neighbors[i]->front;
		while(current != NULL){
			fprintf(out," %d",current->data);
			current = current->next;
		}
	}
	fprintf(out,"\n");
}
