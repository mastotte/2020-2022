/****************************************************************************************
 * *  Maxwell Totten
 * *  mastotte
 * *  pa1
 * *****************************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

int main(int argc, char** argv){
	FILE* file;
	FILE* fileOut;
	const int BUFSIZE = 512;
	char line[512];
	int count = 0;
	int sortCount = 1;
	char* temp= "";
	if(argc == 3){
		file = fopen(argv[1],"r");
		fileOut = fopen(argv[2],"w");
	}else{
		fprintf(stderr, "Input did not have the correct amount of arguments\n");
		return 0;
	}
	
	while (fgets(line, BUFSIZE, file)!=NULL){
		count++;
	}
	char** string_array;
	string_array = (char**)calloc(count,sizeof(char*));
	fclose(file);
	file = fopen(argv[1],"r");
	for (int i = 0; i < count; i++){
		fgets(line, BUFSIZE, file);
		//printf("line = [%s]\n",line);
		string_array[i] = malloc(strlen(line)+1);
		strtok(line, "\n");
		strcpy(string_array[i],line);
	}
	while(sortCount > 0){
		sortCount = 0;
		for(int i = 0; i < count-1; i++){
			if(strcmp(string_array[i],string_array[i+1]) > 0){
				temp = malloc(strlen(string_array[i])+1);
				strcpy(temp, string_array[i]);
				strcpy(string_array[i],string_array[i+1]);
				strcpy(string_array[i+1],temp);
				free(temp);
				sortCount++;
			}
		}
	}
	for(int i = 0; i < count; i++){
		//printf("%s",string_array[i]);
		fprintf(fileOut,"%s\n",string_array[i]);
		free(string_array[i]);
	}
	free(string_array);
}

