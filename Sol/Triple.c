#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SEED 2022
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "Triple.h"
//********************************************************************
//*								     *
//*	Figuring out the Solitaire matches, once and for all.        *
//*     							     *
//*     mastotte, ucsc 2024					     *
//*								     *
//********************************************************************
float calculateSD_3(float data[], float p) {
    float sum = 0.0, mean, SD = 0.0;
    int i;
    int z = 0;
    for (i = 0; i < p; ++i) {
        sum += data[i];
	if(data[i] == 0.0){
		z++;
	}	
    }
    mean = sum / (p-z);
    for (i = 0; i < p; ++i) {
	if(data[i] != 0.0){
        	SD += pow(data[i] - mean, 2);
	}
    }
    return sqrt(SD / (p-z));
}
void output_3(int best_round, int n, int best[n][n], int rounds, bool isTest, FILE* p){
	char buf[50];
	fprintf(p,"\nBest round = %d\n",best_round);
	FILE *infile = fopen("out", "r");
	FILE *bestOutput = fopen("best","w");
	FILE *test = fopen("f2","w");
	fprintf(test,"%d\n%d\n3\n",n,rounds);
	int c = 1;
	while (fgets(buf, 50, infile) != NULL){
			if(atoi(buf) == best_round){
					for(int i = 0; i < rounds; i++){
			fgets(buf, 50, infile);
							fprintf(bestOutput,"Round %d\n",c);
							fprintf(bestOutput,"%s",buf);
							fprintf(test,"%s",buf);
							fprintf(p,"%s",buf);
							c++;
					}
			}
	}
	fclose(test);
	fclose(bestOutput);
	fclose(infile);
}

void trip(int players, int rounds, int TESTSIZE, bool isTest, FILE* p){
	srandom(SEED);
	int seed_input = 0;
	seed_input = random();
	seed_input = seed_input%100;
	srandom(seed_input);
	int w_count = 0;
	
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	int matches[players][players];
	int best[players][players];
	float data[players*players];
	for(int i = 0; i < players; i++){
		for(int j = 0; j < players; j++){
			matches[i][j] = 0;
			best[i][j] = 0;
		}
	}
	FILE *outFile = fopen("out","w");
	FILE *outBest = fopen("best","w");
	bool* C = malloc(players*(sizeof(bool))+1);
	int r1 = 0;
	int r2 = 0;
	int r3 = 0;
	float stdev = -1.0;
	float stdev_new = 0.0;
	int index = 0;
	bool no_equals;
	int best_round = 0;
	int sit_out[players];
	int sit = 0;
	bool sitting = (players%3 != 0);
	if(sitting){
		fprintf(p,"People have to sit out.\n");
	}else{
		fprintf(p,"Nobody is sitting out.\n");
	}
	bool sit_pass;
	if(players == 3)
		TESTSIZE = 1;
	for(int test_count = 1; test_count <= TESTSIZE; test_count++){
		fprintf(outFile,"%d",test_count);
		//printf("\n %f%%",((float)test_count/(float)TESTSIZE)*100.0);
		// Clearing The Array
		for(int i = 0; i < players; i++){
			sit_out[i] = 0;
                	for(int j = 0; j < players; j++){
                        	matches[i][j] = 0;
                	}
        	}
		// Running Simulation
		for(int j = 0; j < rounds; j++){
			if(sitting){
				sit = j;
			}
			for(int i = 0; i <= players; i++){
				if(C[i]){
					sit_out[i]++;
				}
				C[i] = true;
			}
			fprintf(outFile, "\n");
			w_count = players;
			while(w_count >= 3){
				sit_pass = true;
				no_equals = true;
				r1 = random();
				r1 = r1%(players);
				r2 = random();		
				r2 = r2%(players);
				// -- double --
				r3 = random();
                                r3 = r3%(players);
				// -- triple --
				int check[3] = {r1,r2,r3};
				for(int c = 0; c < 3; c++){
					if((check[c] == sit)&&(sitting)){
						sit_pass = false;
					}
					for(int d = 0; d < 3; d++){
						if((c!=d)&&(check[c] == check[d])){
							no_equals = false;
						}
					}
				}
					
				if(C[r1]&&C[r2]&&C[r3]&&no_equals&&sit_pass){
					//printf(" | %d vs %d vs %d vs %d |",r1,r2,r3,r4);
					fprintf(outFile," %d vs %d vs %d -",r1+1,r2+1,r3+1);
					matches[r2][r1] += 1;
					matches[r1][r2] += 1;
					C[r1]= false,C[r2]= false;
					w_count -= 2;
					// -- double --
					matches[r3][r1] += 1;
					matches[r3][r2] += 1;
					matches[r2][r3] += 1;
                                        matches[r1][r3] += 1;
					C[r3]= false;
					w_count--;
					// -- triple --
				}
			}
		}
		bool sits_fair = true;
		//printf("\nSits:\n");
		for(int k = 0; k < players; k++){
			//printf(" %d", sit_out[k]);
			if((sit_out[0] != sit_out[k])&&(sitting)){
				sits_fair = false;
			}
			for(int k2 = 0; k2 < players; k2++){
				data[index] = matches[k][k2];
				index++;
			}
		}
		index = 0;
		int zero_count = 0;
        	for(int i = 0; i < pow(players,2); i++){
			if(data[i] == 0.0){
				zero_count++;
			}
        	}
		if((zero_count <= players)||(players >= rounds)){
			stdev_new = calculateSD_3(data, (float) pow(players,2));
		}
		if((stdev_new < stdev)||(stdev == -1.0)){
			stdev = stdev_new;
			best_round = test_count;
			for(int x = 0; x < players; x++){
				for(int y = 0; y < players; y++){
					best[x][y] = matches[x][y];
				}
			}
		}
		fprintf(outFile,"\n%d\n",test_count);
	}
	fprintf(p,"\n");
	for(int x = 0; x < players; x++){
                fprintf(p,"\n%d:",x+1);
                for(int y = 0; y < players; y++){
                        fprintf(p," %d",best[x][y]);
                }
        }
	fclose(outFile);
	output_3(best_round,players,best,rounds);
	fprintf(p,"\n");
	
	end = clock();
        
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	fprintf(p,"Time: %0.3f \n",cpu_time_used);
	free(C);
}

