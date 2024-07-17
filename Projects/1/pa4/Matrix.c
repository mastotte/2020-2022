/****************************************************************************************
 * *  Maxwell Totten
 * *  mastotte
 * *  pa4
 * *****************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "Matrix.h"
typedef struct EntryObj{
	int column;
	double data;
}EntryObj;

typedef struct EntryObj* Entry;

typedef struct MatrixObj{
	List* Row;
	int Size;
	int NNZ;
}MatrixObj;

//typedef struct MatrixObj* Matrix;

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix M = malloc(sizeof(MatrixObj));
	M->Row = malloc(n*sizeof(List));
	for(int i = 1; i <= n; i++){
		M->Row[i] = newList();
	}
	M->Size = n;
	M->NNZ = 0;
	return M;

}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	if(pM!=NULL && *pM!=NULL){
		makeZero(*pM);
		free(*pM);
		*pM = NULL;
	}
	//free(*pM);
	//*pM = NULL;
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
	return M->Size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	return M->NNZ;
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	int rows = A->Size;
	if(size(A) != size(B))return false;
	if(NNZ(A) != NNZ(B))return false;
	for(int i = 1; i <= rows; i++){
		if(isEmpty(A->Row[i]) != isEmpty(B->Row[i]))return false;
		if(length(A->Row[i]) != length(B->Row[i]))return false;
		if((!isEmpty(A->Row[i]))&&(!isEmpty(B->Row[i]))){
		moveFront(A->Row[i]);
		moveFront(B->Row[i]);
		while(get(A->Row[i]) || get(B->Row[i])){
			if(((Entry)get(A->Row[i]))->data != ((Entry)get(B->Row[i]))->data){
				return false;
			}
			moveNext(A->Row[i]);
			moveNext(B->Row[i]);
			if(index(A->Row[i]) == -1)break;
		}
		}
	}
	return true;
}
// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	for(int i = 1; i <= size(M); i++){
		if(!isEmpty(M->Row[i])){
			clear(M->Row[i]);
		}
	}
	M->NNZ = 0;
}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	Entry E = malloc(sizeof(EntryObj));
	E->data = x;
	E->column = j;
	moveFront(M->Row[i]);
	if(!isEmpty(M->Row[i])){
		moveBack(M->Row[i]);
		if((((Entry)get(M->Row[i]))->column < j)&&(x != 0)){
			append(M->Row[i], E);
			M->NNZ++;
			return;
		}else if((((Entry)get(M->Row[i]))->column == j)&&(x == 0)){
			delete(M->Row[i]);
			M->NNZ--;
			return;
		}else if((((Entry)get(M->Row[i]))->column < j)&&(x == 0)){
			return;
		}else{
		moveFront(M->Row[i]);
		while(((Entry)get(M->Row[i]))->column < j){
			moveNext(M->Row[i]);
		}	
		if(((Entry)get(M->Row[i]))->column == j){
			if(x != 0){
				set(M->Row[i],E);
			}else if(x == 0){
				delete(M->Row[i]);
				M->NNZ--;
			}
		}else if(((Entry)get(M->Row[i]))->column > j){
			insertBefore(M->Row[i], E);
			M->NNZ++;
		}
		}
	}else if((isEmpty(M->Row[i])&&(x != 0))){
		append(M->Row[i], E);
		M->NNZ++;
	}else{
		return;
	}

}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	Matrix M = newMatrix(A->Size);
	double x = 0;
	int col = 0;
	for(int i = 1; i <= A->Size; i++){
		if(!isEmpty(A->Row[i])){//this might cause a problem, not sure
			moveFront(A->Row[i]);
			while((Entry)get(A->Row[i])){
				x = ((Entry)get(A->Row[i]))->data;
				col = ((Entry)get(A->Row[i]))->column;
				changeEntry(M, i, col, x);
				moveNext(A->Row[i]);
				if(index(A->Row[i]) == -1)break;
			}
		}
	}	
	return M;		
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	Matrix M = newMatrix(A->Size);
	int col = 0;
	double x = 0;
	for(int i = 1; i <= A->Size; i++){
		if(!isEmpty(A->Row[i])){
		moveFront(A->Row[i]);
		while((Entry)get(A->Row[i])){
			col = ((Entry)get(A->Row[i]))->column;
			x = ((Entry)get(A->Row[i]))->data;
			changeEntry(M, col, i, x);
			moveNext(A->Row[i]);
			if(index(A->Row[i]) == -1)break;
		}
		}
	}
	return M;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	double prod = 0;
	Matrix M = newMatrix(size(A));
	for(int i = 1; i <= A->Size; i++){
		moveFront(A->Row[i]);
		if(!isEmpty(A->Row[i])){
			while((Entry)get(A->Row[i])){
				prod = ((Entry)get(A->Row[i]))->data * x;
				changeEntry(M, i, ((Entry)get(A->Row[i]))->column, prod);
				moveNext(A->Row[i]);
				if(index(A->Row[i]) == -1){
					break;
				}
			}
		}
	}
	return M;
}
Matrix sum_diff_helper(Matrix A, Matrix B, int sign){
 	Matrix M = newMatrix(size(A));
        Entry a = NULL;
        Entry b = NULL;
        double x = 0;
	int col = 0;
	bool skip, a_done, b_done;
        for(int i = 1; i <= size(A); i++){
		skip = false;
		a_done = false;
		b_done = false;
		moveFront(A->Row[i]);
		moveFront(B->Row[i]);
                if((isEmpty(A->Row[i]))&&(!isEmpty(B->Row[i]))){
			// If A is empty and B is not empty
                        moveFront(B->Row[i]);
			while(index(B->Row[i]) != -1){
				x = ((Entry)get(B->Row[i]))->data;
                                col = ((Entry)get(B->Row[i]))->column;
				if(sign == -1){
					x -= x*2;
				}
                                changeEntry(M, i, col, x);
				moveNext(B->Row[i]);
			}
            		skip = true;
		}else if((isEmpty(B->Row[i]))&&(!isEmpty(A->Row[i]))){
			// If B is empty and A is not empty
			moveFront(A->Row[i]);
                        while(index(A->Row[i]) != -1){
				x = ((Entry)get(A->Row[i]))->data;
				col = ((Entry)get(A->Row[i]))->column;
                                changeEntry(M, i, col, x);
                                moveNext(A->Row[i]);
                        }
                        skip = true;
		}else if((isEmpty(A->Row[i]))&&(isEmpty(B->Row[i]))){
			// If A and B are both empty
			skip = true;
		}else{
			moveFront(A->Row[i]);
			moveFront(B->Row[i]);
			a = (Entry)get(A->Row[i]);
			b = (Entry)get(B->Row[i]);
                while(!skip){
                        if(a->column == b->column){
				if(sign == -1){
					x = a->data - b->data;
				}else{
                                	x = a->data + b->data;
				}
				col = a->column;
                                changeEntry(M, i, col, x);
                                moveNext(A->Row[i]);
                                moveNext(B->Row[i]);
                        }else if(((a->column < b->column)||(index(B->Row[i]) == -1))&&(!a_done)){
                                col = a->column;
				x = a->data;
                                changeEntry(M, i, col, x);
                                moveNext(A->Row[i]);
                        }else if(((b->column < a->column)||(index(A->Row[i]) == -1))&&(!b_done)){
				col = b->column;
				x = b->data;
				if(sign == -1){
					x -= x*2;
				}
				changeEntry(M, i, col, x);
                                moveNext(B->Row[i]);
                        }
                        if((index(A->Row[i]) == -1)&&(index(B->Row[i]) == -1)){
				skip = true;
                                break;
                        }
			if(index(A->Row[i]) != -1 ){
                        	a = (Entry)get(A->Row[i]);
			}else{
				a_done = true;
			}
			if(index(B->Row[i]) != -1){
                        	b = (Entry)get(B->Row[i]);
			}else{
				b_done = true;
			}
                }
		}

        }
        return M;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	Matrix C = copy(B);
	Matrix M = sum_diff_helper(A,C,1);
	freeMatrix(&C);
	return M;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	Matrix C = copy(B);
	Matrix M = sum_diff_helper(A,C,-1);
	freeMatrix(&C);
	return M;
}
bool listEqual(List A, List B){
	moveFront(A);
	moveFront(B);
	moveNext(A);
	if(index(A) == index(B))return true;

	return false;
}
// dotProduct()
// Computes Dot Product, given 2 lists
// pre: length(A) > 0 && length(B) > 0
double dotProduct(List A, List B){
	double sum = 0;
	moveFront(A);
	moveFront(B);
	while((index(A) != -1)&&(index(B) != -1)){
		
		if(((Entry)get(B))->column < ((Entry)get(A))->column){
			moveNext(B);
		}else if(((Entry)get(B))->column > ((Entry)get(A))->column){
			moveNext(A);
		}else{
			sum += ((Entry)get(B))->data * ((Entry)get(A))->data;
			moveNext(A);
			moveNext(B);
		}
	}
	return sum;
}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	Matrix M = newMatrix(size(A));
	Matrix C = transpose(B);
	for(int i = 1; i <= size(A); i++){
	  if(!isEmpty(A->Row[i])){
	    for(int j = 1; j <= size(C); j++){
	      if(!isEmpty(C->Row[j])){
		changeEntry(M, i, j, dotProduct(A->Row[i],C->Row[j]));
	      }
	    }
	  }
	}
	return M;
}
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	Entry E;
	fprintf(out,"\n");
	for(int i = 1; i <= size(M); i++){
		if(!isEmpty(M->Row[i])){
			fprintf(out,"%d: ",i);
			moveFront(M->Row[i]);
			while(index(M->Row[i]) != -1){
				E = (Entry)get(M->Row[i]);
				fprintf(out,"(%d, %0.1f) ",E->column,E->data);
				moveNext(M->Row[i]);
			}
			fprintf(out,"\n");
		}
	}
	fprintf(out,"\n");

}
