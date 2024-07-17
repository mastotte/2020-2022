/****************************************************************************************
 *  * *  Maxwell Totten
 *   * *  mastotte
 *    * *  pa3
 *     * *****************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "Graph.h"

int main(int argc, char* argv[]){
	FILE *inputFile;
	FILE *outputFile;
	int order;
	char c;
	char buf[10];
	int line = 0;
	int fileSize = 0;
	Graph G = NULL;
	//Graph gT = NULL;
	if(argc != 3){
		fprintf(stderr,"Program was not given 3 arguments.\n");
		return 0;
	}else{
		inputFile = fopen(argv[1],"r");
		outputFile = fopen(argv[2],"w");
	}
	for(c = getc(inputFile); c != EOF; c = getc(inputFile)){
		if(c == '\n'){
			fileSize++;
		}
	}
	fclose(inputFile);
	inputFile = fopen(argv[1],"r");
	fgets(buf, 10, inputFile);
	order = atoi(buf);
	int num1[fileSize];
	int num2[fileSize];
	G = newGraph(order);
	//gT = newGraph(order);
	//helper call
	importNums(inputFile, num1, num2);	
	for(int i = 0; i < fileSize; i++){
		if((num1[i] != 0)&&(num2[i] != 0)){
			addArc(G, num1[i], num2[i]);
			//addArc(gT, num2[i], num1[i]);
			line++;
		}else{
			break;
		}
	}
	line++;
	//findPath with output		
	List S = newList();
	//List sT = newList();
	
	for(int i = 1; i <= getOrder(G); i++){
		append(S, i);
		//prepend(sT, i);
	}
	//printGraph(outputFile, G);
	DFS(G, S);
	
	//DFS(gT, sT);
	//printf("end dfs2\n");
	
	
	DFSOutput(S, G, outputFile);
	//printf("end output 2\n");

	fclose(outputFile);
	freeGraph(&G);
	//freeGraph(&gT);
	//printf("free graph works\n");
	freeList(&S);
	//freeList(&sT);
	//fclose(outputFile);*/
	fclose(inputFile);
}
void DFSOutput(List L, Graph G,  FILE* f){
	int component = 1;
	fprintf(f,"Adjacency List Representation of G: ");
	printGraph(f,G);
	int count = 1;
	moveFront(L);
	while(get(L)!=-1){
		if(get(L) == 0){
			count++;
		}
		moveNext(L);
	}
	fprintf(f,"\nG contains %d strongly connected components:\n",count);
	moveBack(L);
	while(get(L) != -1){
		//printf("check %d\n",get(L));
		fprintf(f,"Component %d: ",component);
		while((get(L)!=0)&&(get(L)!=-1)){
			fprintf(f," %d",get(L));
			movePrev(L);
		}
		fprintf(f,"\n");
		component++;
		movePrev(L);
	}
	freeList(&L);
}
void importNums(FILE* inputFile, int* num1, int *num2){
	char buf[10];
        char temp[10];
        char temp2[10];
	int count = 0;
	int len = 0;
	int t2 = 0;
	while(fgets(buf,10,inputFile) != NULL){
                count = 0;
                for(int i = 0; i < 10; i++){
                        temp[i] = '\0';
                        temp2[i] = '\0';
                }
                while(buf[count] != ' '){
                        temp[count] = buf[count];
                        count++;
                }
                num1[len] = atoi(temp);
		count++;
		t2 = count;
                while(buf[count] != '\n'){
                        temp2[count-t2] = buf[count];
                        count++;
                }	
                num2[len] = atoi(temp2);
		len++;
        }
}















