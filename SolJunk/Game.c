#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SEED 2022
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "Game.h"
//********************************************************************
//*								     *
//*	Figuring out the Solitaire matches, once and for all.        *
//*     							     *
//*     mastotte, ucsc 2024					     *
//*								     *
//********************************************************************
float calculateSD_1(float data[], float p) {
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
void output_1(int best_round, int n, int best[n][n], int rounds, bool isTest, FILE* p, int ppg){
  	char buf[50];
 	FILE *infile = fopen("out", "r");
	FILE *bestOutput = fopen("best","w");
	FILE *test = fopen("f2","w");
	fprintf(p,"\nBest round = %d\n",best_round);
	fprintf(test,"%d\n%d\n%d\n",n,rounds,ppg);
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
			break;
		}
  	}
	fclose(test);
	fclose(bestOutput);
  	fclose(infile);
}

void game(int players, int rounds, int TESTSIZE, bool isTest, FILE* p, int ppg){
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
	int r4 = 0;
	int r5 = 0;
	int r6 = 0;
	int r7 = 0;
	int priority_row = 0;
	float highest = -1.0;
	float stdev1 = -1.0;
	float stdev = -1.0;
	float stdev_new = 0.0;
	int index = 0;
	bool no_equals;
	int best_round = 0;
	int sit_out[players];
	int sit = 0;
	bool sitting = (players%ppg != 0);
	if(sitting){
		fprintf(p,"People have to sit out.\n");
	}else{
		fprintf(p,"Nobody is sitting out.\n");
	}
	bool sit_pass;
	if(players == ppg)
		TESTSIZE = players+1;
	for(int test_count = players+1; test_count <= TESTSIZE; test_count++){
		fprintf(outFile,"%d",test_count);
		bool con;
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
			fprintf(outFile,"\n");
			//fprintf(outFile,"\nRound %d\n",j+1);
			w_count = players;
			while(w_count >= ppg){
				//inf_blocker++;
				//printf("infinite check\n");
				/*highest = 0;
				priority_row = 0;
				for(int j = 1; j <= players; j++){
					stdev1 = calculateSD_1(matches[j],(float)pow(players,2));
					if(stdev1>highest){
						highest = stdev1;
						priority_row = j;
					}
				}*/
				// r1 = j, others are j's least played. make a max and min finder.	
				sit_pass = true;
				no_equals = true;
				r1 = random();
				r1 = r1%(players);
				r2 = random();	
				r2 = r2%(players);
				// -- double --
				if(ppg>2){
					r3 = random();
                                	r3 = r3%(players);
				}
				if(players<3){
					r3 = 3;
					C[3] = true;
				}
				// -- triple --
				if(ppg>3){
                                	r4 = random();
                                	r4 = r4%(players);
				}
				if(players<4){
					r4 = 4;
					C[4] = true;
				}
				// -- quadruple --
				if(ppg>4){
					r5 = random();
					r5 = r5%(players);
				}
				if(players<5){
					r5 = 5;
					C[5] = true;
				}
				// -- penta --
				if(ppg>5){
					r6 = random();
					r6 = r6%(players);
				}
				if(players<6){
					r6 = 6;
					C[6] = true;
				}
				// -- hex --
				if(ppg>6){
					r7 = random();
					r7 = r7%(players);
				}
				if(players<7){
					r7 = 7;
					C[7] = true;
				}
				int check[7] = {r1,r2,r3,r4,r5,r6,r7};
				
				for(int c = 0; c < ppg; c++){
					if((check[c] == sit)&&(sitting)){
						sit_pass = false;
					}
					for(int d = 0; d < ppg; d++){
						if((c!=d)&&(check[c] == check[d])){
							no_equals = false;
						}
					}
				}
				//printf("ppg: %d\n",ppg);
				//printf("(C1:%d)(C2:%d)(C3:%d)(C4:%d)(C5:%d)(C6:%d)",C[r1],C[r2],C[r3],C[r4],C[r5],C[r6]);
				//printf("(C7:%d)(NE:%d)(SP:%d)\n",C[r7],no_equals,sit_pass);
				if(ppg==2){ 
					con = (C[r1]&&C[r2]);
				}else if(ppg==3){
					con = (C[r1]&&C[r2]&&C[r3]);
				}else if(ppg==4){
					con = (C[r1]&&C[r2]&&C[r3]&&C[r4]);
				}else if(ppg==5){
					con = (C[r1]&&C[r2]&&C[r3]&&C[r4]&&C[r5]);
				}else if(ppg==6){
					con = (C[r1]&&C[r2]&&C[r3]&&C[r4]&&C[r5]&&C[r6]);
				}else if(ppg==7){
					con = (C[r1]&&C[r2]&&C[r3]&&C[r4]&&C[r5]&&C[r6]&&C[r7]);
				}




				if(con&&no_equals&&sit_pass){
					//printf(" | %d vs %d vs %d vs %d |",r1,r2,r3,r4);a
					//printf("inner pass\n");
					fprintf(outFile," %d vs %d",r1+1,r2+1);
					if(ppg>2) fprintf(outFile," vs %d",r3+1);
					if(ppg>3) fprintf(outFile," vs %d",r4+1);
					if(ppg>4) fprintf(outFile," vs %d",r5+1);
					if(ppg>5) fprintf(outFile," vs %d",r6+1);
					if(ppg>6) fprintf(outFile," vs %d",r7+1);
					fprintf(outFile," -");
										
					matches[r2][r1] += 1;
					matches[r1][r2] += 1;
					C[r1]= false,C[r2]= false;
					w_count -= 2;
					// -- double --
					if(ppg>2){
						matches[r3][r1] += 1;
						matches[r3][r2] += 1;
						matches[r2][r3] += 1;
                                        	matches[r1][r3] += 1;
						C[r3]= false;
						w_count--;
					}
					// -- triple --
					if(ppg>3){
						matches[r4][r1] += 1;
                                        	matches[r4][r2] += 1;
                                        	matches[r4][r3] += 1;
                                        	matches[r1][r4] += 1;
						matches[r2][r4] += 1;
                                        	matches[r3][r4] += 1;
						C[r4]= false;	
						w_count--;
					}
					// -- quadruple --
					if(ppg>4){
						matches[r5][r1] += 1;
						matches[r5][r2] += 1;
						matches[r5][r3] += 1;
                                        	matches[r5][r4] += 1;
						matches[r1][r5] += 1;
                                        	matches[r2][r5] += 1;
						matches[r3][r5] += 1;
                                        	matches[r4][r5] += 1;
						C[r5]= false;
						w_count--;
					}
					// -- penta --
					if(ppg>5){
						matches[r6][r1] += 1;
                                        	matches[r6][r2] += 1;
                                        	matches[r6][r3] += 1;
                                        	matches[r6][r4] += 1;
                                        	matches[r6][r5] += 1;
                                        	matches[r1][r6] += 1;
                                        	matches[r2][r6] += 1;
                                        	matches[r3][r6] += 1;
						matches[r4][r6] += 1;
                                        	matches[r5][r6] += 1;
                                        	C[r6]= false;
                                        	w_count--;
					}
					// -- sept --
					if(ppg>6){
						matches[r7][r1] += 1;
                                        	matches[r7][r2] += 1;
                                        	matches[r7][r3] += 1;
                                        	matches[r7][r4] += 1;
                                        	matches[r7][r5] += 1;
						matches[r7][r6] += 1;
                                        	matches[r1][r7] += 1;
                                        	matches[r2][r7] += 1;
                                        	matches[r3][r7] += 1;
                                        	matches[r4][r7] += 1;
                                        	matches[r5][r7] += 1;
						matches[r6][r7] += 1;
                                        	C[r7]= false;
                                        	w_count--;
					}
				}

			}
		}
		bool sits_fair = true;
		for(int k = 0; k < players; k++){
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
			stdev_new = calculateSD_1(data, (float) pow(players,2));
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
	output_1(best_round,players,best,rounds,isTest,p,ppg);
	fprintf(p,"\n");
	
	end = clock();
        
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	fprintf(p,"Time: %0.3f \n",cpu_time_used);
	free(C);
}

