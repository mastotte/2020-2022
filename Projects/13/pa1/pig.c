
#include <stdio.h>
#include <stdlib.h>
#define SEED 2022
#include "names.h"
#include <limits.h>

typedef enum { SIDE , RAZORBACK , TROTTER , SNOUTER , JOWLER } Position;
const Position pig[7] = {
	SIDE,
	SIDE,
	RAZORBACK,
	TROTTER,
	SNOUTER,
	JOWLER,
	JOWLER
};


int main(void){
	srandom(SEED);
	int seed_input = 0;
	printf("Enter a valid seed (int between 1-10 digits): \n");
	scanf("%d",&seed_input);
	if ((seed_input < 1) || (seed_input > UINT_MAX)){
		fprintf(stderr,"Invalid random seed. Using 2022 instead.\n");
	}else{
		srandom(seed_input);
	}
	
	int condition = 1;
	int amountOfNames = 0;
	int count = 0;
	int roll = 0;
	printf("Enter the amount of players (2-10)\n");
	scanf("%d",&amountOfNames);
	if ((amountOfNames < 2) || (amountOfNames > 10)){
		amountOfNames = 2;
		fprintf(stderr,"Invalid number of players. Using 2 instead.\n");
	}
	int scores[11] = {0,0,0,0,0,0,0,0,0,0,0};
	
	while (condition == 1){
		
		for (int count = 0; count < amountOfNames; count+=1){
			
			roll = random();
			roll = roll %7;
			roll = pig[roll];

			if (roll == SIDE){
				printf("%s rolled SIDE.\n", names[count]);
				scores[count] += 0;
			}else if (roll == RAZORBACK){
				printf("%s rolled RAZORBACK.", names[count]);
				scores[count] += 10;
			}else if (roll == TROTTER){
				printf("%s rolled TROTTER.", names[count]);
				scores[count] += 10;
			}else if (roll == SNOUTER){
				printf("%s rolled SNOUTER.", names[count]);
				scores[count] += 15;
			}else if (roll == JOWLER){
				printf("%s rolled JOWLER.", names[count]);
				scores[count] += 5;
			}
				
			
			if (scores[count]>=100){
				printf("\n%s won with %d points\n",names[count],scores[count]);
				condition = 0;
				break;
			}
			if (roll != SIDE){
				count--;
			}else{
				printf("\n\n");
			}

		}
	}

	return (0);
}
