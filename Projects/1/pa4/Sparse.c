//-----------------------------------------------------------------------------
//  Sparse.c
//  Maxwell Totten, mastotte, pa4
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "Matrix.h"

int main(int argc, char* argv[]){
	Matrix A,B,C, D, E, F, G, H, X,Y;
	FILE* out = fopen(argv[2],"w");
	FILE* inFile = fopen(argv[1],"r");
	int n = 0;
	int a = 0;
	int b = 0;
	int row = 0;
	int col = 0;
	double data;
	char buf[30];
	fgets(buf,30,inFile);
	n = atoi(strtok(buf," "));
	a = atoi(strtok(NULL," "));
	b = atoi(strtok(NULL,"\n"));
	A = newMatrix(n);
        B = newMatrix(n);
	fgets(buf,30,inFile);
	for(int i = 1; i <= a; i++){
		fgets(buf,30,inFile);
		row = atoi(strtok(buf," "));
		col = atoi(strtok(NULL," "));
		data = strtod(strtok(NULL,"\n"),NULL);
		changeEntry(A, row, col, data);
	}
	fprintf(out,"A has %d non-zero entries:",NNZ(A));
	printMatrix(out,A);
	fgets(buf,30,inFile);
	for(int i = 1; i <= b; i++){
                fgets(buf,30,inFile);
                row = atoi(strtok(buf," "));
                col = atoi(strtok(NULL," "));
                data = strtod(strtok(NULL,"\n"),NULL);
                changeEntry(B, row, col, data);
        }
	fprintf(out,"B has %d non-zero entries:",NNZ(B));
	printMatrix(out,B);
	C = scalarMult(1.5, A);
   fprintf(out,"(1.5)*A =");
   printMatrix(out, C);
   D = sum(A, B);
   fprintf(out,"A+B =");
   printMatrix(out, D);
   
   Y = sum(A, A);
   fprintf(out,"A+A =");
   printMatrix(out, Y);

   E = diff(B, A);
   fprintf(out,"B-A =");
   printMatrix(out, E);
	
   X = diff(A, A);
   fprintf(out,"A-A =");
   printMatrix(out, X);

   F = transpose(A);
   fprintf(out,"Transpose(A) =");
   printMatrix(out, F);

   G = product(A, B);
   fprintf(out,"A*B =");
   printMatrix(out, G);

   H = product(B, B);
   fprintf(out,"B*B =");
   printMatrix(out, H);
   /*
   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );
   */
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&X);
   return EXIT_SUCCESS;
}
