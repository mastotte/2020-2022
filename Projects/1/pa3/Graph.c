/****************************************************************************************
 * *  Maxwell Totten
 * *  mastotte
 * *  pa3
 * *****************************************************************************************/
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
typedef struct GraphObj{
	List *Neighbors;
	char *Color;
	int *Discover;
	int *Finish;
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
	G->Color = malloc(n+1);
	G->Discover = malloc(n*sizeof(int));
	G->Finish = malloc(n*sizeof(int));
	
	for(int i = 1; i <= n; i++){
		G->Neighbors[i] = newList();
		//printf("new graph cursor: %p\n",G->Neighbors[i]->cursor);
		G->Neighbors[i]->parent = NIL;		
		G->Neighbors[i]->length = 0;
		G->Color[i] = 'w';
	}		
	G->Order = n;
	return G;	
}
List getList(Graph G, int i){
        return G->Neighbors[i];
}
void freeGraph(Graph* pG){
	
	if(pG!=NULL && *pG!=NULL){
		for(int i = 1; i <= getOrder(*pG); i++){
			//printf("graph cursor: %p\n",(*pG)->Neighbors[i]->cursor);
			freeList(&(*pG)->Neighbors[i]);
		}
		free((*pG)->Discover);
		free((*pG)->Finish);
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
int getDiscover(Graph G, int u){
	return G->Discover[u];
}
int getFinish(Graph G, int u){
	return G->Finish[u];
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
char getColor(Graph G, int i){
	return G->Color[i];
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
			
			if(current->next){
                	if(current->data > current->next->data){
                        	temp = current->next->data;
                        	current->next->data = current->data;
                        	current->data = temp;
                        	sortCount++;
                	}else{
				current = current->next;
			}
			}
		}
		current = G->Neighbors[u]->front;
        }

        G->Size += 1;	
}

void DFS(Graph G, List S){
	
	int time = 0;		
	
	/*for(int i = 1; i <= getOrder(G); i++){
                G->Color[i] = 'w';
                G->Neighbors[i]->parent = NIL;
        }*/
	moveFront(S);
	for(int i = 1; i <= length(S); i++){
		
		
		if(G->Color[get(S)] == 'w'){
			
			//Visit(G, S, get(S), &time, 0);
			Visit(G, S, get(S), &time, 0);
			//append(S, 0);
		}
		moveNext(S);
	}
	moveFront(S);
	/*
	while(get(S) != -1){
		printf(" %d", get(S));
		moveNext(S);
	}
	printf("\n--------------\n");
	
	moveFront(S);
	Node current;
	int temp;
	while(S->cursor->node){
		current = S->cursor->node;
		if(current->next){
			if((get(S) < current->next->data)&&(current->data != 0)){
				temp = current->next->data;
				current->next->data = current->data;
				current->data = temp;
				moveFront(S);
			}
		}		
		moveNext(S);
	}
	
	printf(" discover and finish: \n");
	for(int i = 1; i < getOrder(G); i++){
		for(int j = 1; j <= getOrder(G); j++){
			if(G->Discover[j] == i){
				printf(" %d",j);
			}
		}
	}
	printf("\n\n");

	*/

	for(int i = 1; i <= getOrder(G); i++){
		//printf("\n[%d] : %d  %d, parent = %d",i, G->Discover[i],G->Finish[i],G->Neighbors[i]->parent);
		Delist(S);
	}/*
	printf("checj\n");
	moveFront(S);
	while(S->cursor->node){
		printf(" %d",get(S));
		moveNext(S);
	}*/
}
Graph transpose(Graph G){

	Node current;
	Graph g = newGraph;
	for(int i = 1; i <= getOrder(G); i++){
		current = G->Neighbors[i]->front;
		while(current){
			addArc(g,current->data,i);
			current = current->next;
		}
	}
	return g;
}
void Visit(Graph G, List L, int x, int *time, int head){
	//printf("time = %d",*time);
	(*time) += 1;
	//printf("->%d\n",*time);
	G->Discover[x] = *time;
	//append(L,x);
	G->Color[x] = 'g';
	int y = 0;
	//printf("check current\n");
	Node current = G->Neighbors[x]->back;
	//printf("end current\n");
	/*if(current){
		y = current->data;
		if(y == 9){
			append(L,0);
		}
	}*/
	//printf("current ->data\n");
	y = current->data;
	moveBack(G->Neighbors[x]);
	y = get(G->Neighbors[x]);
	//printf(" %d-----",y);
	for(int i = 1; i <= length(G->Neighbors[x]); i++){
		//printf("\nX Discover = %d, Current time = %d\n",G->Discover[x],*time);
		//printf("\nx = %d(%c), y = %d(%c)", x,G->Color[x],y,G->Color[y]);
		if(G->Color[y] == 'w'){
			G->Neighbors[y]->parent = x;	
			//printf("\n visiting %d  \n", y);
			//i = length(G->Neighbors[x])+1;
                	//append(L,0);
                	
			Visit(G, L, y, time, 0);
			
		}
		movePrev(G->Neighbors[x]);	
		//current = current->next;
		y = get(G->Neighbors[x]);	
		//G->Discover[x] = *time;
		
	}
	//printf("\n-----------------------\n");
	//append(L,x);
	//printf("\n %d is black\n",x);
	G->Color[x] = 'b';
	(*time) += 1;
	G->Finish[x] = *time;
	if(G->Discover[x] < *time-1){
		//printf("\n________________ %d _______________ \n",x);
	}
	if((G->Finish[x] - G->Discover[x] == 1)&&(G->Discover[x] > 2)){
		//printf("\n=== X : %d ===\n",x);
		//printf("Discover = %d\nFinish = %d\n",G->Discover[x],G->Finish[x]);
		append(L,0);
		append(L,x);	
	}else{
		append(L,x);
	}
	//printf("-----------------------\n");
}
Graph copyGraph(Graph G){
	Graph g = newGraph(getOrder(G));
	int n = getOrder(G);
	Node current;
	for(int i = 1; i <= n; i++){
		g->Neighbors[i] = copyList(G->Neighbors[i]);	
		//printf("new graph cursor: %p\n",G->Neighbors[i]->cursor);
		g->Neighbors[i]->parent = G->Neighbors[i]->parent;
	}
	return g;

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
	for(int i = 1; i <= G->Order; i++){
		fprintf(out,"\n%d:",i);
		current = G->Neighbors[i]->front;
		while(current != NULL){
			fprintf(out," %d",current->data);
			current = current->next;
		}
	}
	fprintf(out,"\n");
}
