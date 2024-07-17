/****************************************************************************************
 *  * *  Maxwell Totten
 *   * *  mastotte
 *    * *  pa2
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
	int count = 0;
	int line = 0;
	int fileSize = 0;
	List L = newList();
	Graph G = NULL;
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
	order = atoi(buf)+1;
	int num1[fileSize];
	int num2[fileSize];
	G = newGraph(order);

	//helper call
	importNums(inputFile, num1, num2);	
	for(int i = 0; i < fileSize; i++){
		if((num1[i] != 0)&&(num2[i] != 0)){
			addEdge(G, num1[i], num2[i]);
			line++;
		}else{
			break;
		}
	}
	line++;
	//printGraph
	printGraph(outputFile, G);

	//findPath with output		
	while((num1[line+count] != 0)&&(num2[line+count] != 0)){
		clear(L);
		BFS(G,num1[line+count]);
		getPath(L, G, num2[line+count]);
		pathOutput(L, G, num2[line+count],outputFile);
		count++;
	}
}
void pathOutput(List L, Graph G, int u, FILE* f){
	if(length(L) == INF){
                fprintf(f,"\nThe distance from %d to %d is infinity",getSource(G),u);
                fprintf(f,"\nNo %d-%d path exists\n",getSource(G),u);
        }else{
                if(length(L) > 0){
                        moveFront(L);
                        fprintf(f,"\nThe distance from %d to %d", getSource(G),back(L));
                        fprintf(f," is %d",getDist(G, back(L)));
                        fprintf(f,"\nA shortest %d-%d path is: %d",getSource(G),back(L),getSource(G));
                        while((get(L) != back(L))&&(get(L) != -1)){
                                fprintf(f," %d",get(L));
                                moveNext(L);
                        }
                        fprintf(f," %d\n",back(L));
                }else{
                        fprintf(f,"\nThe distance from %d to %d is 0",u,u);
			fprintf(f,"\nA shortest %d-%d path is: %d\n",u,u,u);
                }
        }
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















