//-----------------------------------------------------------------------------
// Shuffle.cpp
// Max Totten, mastotte, #1799187
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
void shuffle(List &D){
	D.moveFront();
	List A, B;
	std::string S;
	int num = D.length();
	int pos = 0;
	while(pos<num){
		if(pos<num){
			A.insertBefore(D.peekNext());
			D.moveNext();
			pos++;
		}	
		if(pos<num){
			B.insertBefore(D.peekNext());
			D.moveNext();
			pos++;
		}
	}
	//printf("shuffle loop success\n");
	D = B.concat(A);
}
int main(int argc, char **argv){
	int input = 0;
	int digits = 0;
	int base = 10;
	int shuffle_count = 1;
	FILE* f = fopen("out","w");
	List C;
	List D;
	if(argc != 2){
		printf("How many cards?\n");
		scanf("%d",&input);
	}else{
		input = atoi(argv[1]);
	}
	fprintf(f,"deck size       shuffle count\n");
	fprintf(f,"------------------------------\n");
	printf("deck size       shuffle count\n");
        printf("------------------------------\n");
	for(int current_size = 1; current_size <= input; current_size++){
		C.clear();
		D.clear();
		C.moveFront();
		D.moveFront();
		for(int i = 0; i < current_size; i++){
			D.insertBefore(i);
			C.insertBefore(i);
		}
		D.moveFront();
		shuffle(D);
		while((!D.equals(C))&&(shuffle_count<101)){
			shuffle_count++;
			shuffle(D);
		}
		if(current_size == base){
			digits++;
			base = base*10;
		}
		fprintf(f," %d",current_size);
		printf(" %d",current_size);
		for(int j = 0; j < 15-digits; j++)fprintf(f," ");
		for(int j = 0; j < 15-digits; j++)printf(" ");
		fprintf(f,"%d\n",shuffle_count);
		printf("%d\n",shuffle_count);
		shuffle_count = 1;
	}	
	fclose(f);
}
