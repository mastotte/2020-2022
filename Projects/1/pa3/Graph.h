#include "List.h"
#define NIL -1
#define INF 0
typedef struct GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

void getPath(List L, Graph G, int u);

char getColor(Graph G, int i);
/*** Manipulation procedures ***/
void makeNull(Graph G);

Graph transpose(Graph G);

Graph copyGraph(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
