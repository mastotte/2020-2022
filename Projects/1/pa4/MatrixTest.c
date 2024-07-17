//-----------------------------------------------------------------------------
//  MatrixTest.c 
//  Maxwell Totten, mastotte, pa4
//  A test for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "Matrix.h"
     
int main(){
   int n=10;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;
   printf("Changing entries...\n");
   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
   printf("Changed entries.\n");
   printf("A:%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("B:%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\nTesting ScalarMult\n");

   C = scalarMult(1.5, A);
   printf("A*1.5:%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\nTesting Sum\n");
   D = sum(A, B);
   printf("A+B:%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\nTesting Diff\n");

   E = diff(A, A);
   printf("A-A:%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\nTesting Transpose\n");

   F = transpose(B);
   printf("Transpose B:%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\nTesting Product\n");
   printf("B = \n");
   printMatrix(stdout, B);
   G = product(B, B);
   printf("B*B:%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\nTesting Copy\n");

   H = copy(A);
   printf("Copy(A)%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\nTesting Equals\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}

/*
Output of this program:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/
