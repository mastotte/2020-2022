#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SEED 2022
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "Copy.h"
//********************************************************************
//*								     *
//*	Figuring out the Solitaire matches, once and for all.        *
//*     							     *
//*     mastotte, ucsc 2024					     *
//*								     *
//********************************************************************
float calculateSD_copy(float data[], float p, int matches_call) {
    /*printf("\nCalculateSD for: ");
    for(int m=0;m<5;m++){
	printf("[%0.1f]",data[m]);
    }
    printf("\n");*/
    float sum = 0.0, mean, SD = 0.0;
    int i;
    int z = 0;
    for (i = 0; i < p; ++i) {
	//printf("[%f]",data[i]);
        sum += data[i];
	if(data[i] == 0.0){
		z++;
	}	
    }
    //printf("\n");
    if(matches_call == 0) z = 0;
    mean = sum / (p-z);
    //printf("\nMean: %f, Sum: %f, (p,z): (%f,%d)\n",mean,sum,p,z);
    for (i = 0; i < p; ++i) {
	if((data[i] != 0.0)||(matches_call==1)){
        	SD += pow(data[i] - mean, 2);
	}
    }
    if(p-z==0){
	return 0;
    }else{
    	return sqrt(SD / (p-z));
    }
}
void output_copy(int best_round, int n, int best[n][n], int rounds, bool isTest, FILE* p, int ppg){
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
bool isSitting(int val, int mod,float sitters[]){
	for(int i = 0; i < mod; i++){
		if(val == sitters[i]){
			return true;
		}
	}
	return false;
}
	
int findMax(int players, float x[players], bool* C,int ppg, float sitters[]){
	float highest = 0;
	int index = 0;
	for(int i = 0; i < players; i++){
		//printf("stdevs[%d] = %f\n",i,x[i]);
		if((x[i]>highest)&&(C[i]==true)&&(!isSitting(i,players%ppg,sitters))){
			highest = x[i];
			index = i;
		}
	}
	return index;
}
int findMin(int players, int ppg, float sitters[], float x[players], bool* C){
	int lowest = 9999;
	int index = 0;
	for(int i = 0; i < players; i++){
		printf("[%f]",x[i]);
		if((x[i]<lowest)&&(C[i] == true)&&(!isSitting(i,players%ppg,sitters))){
			lowest = x[i];
			index = i;	
		}
	}
	return index;
}
void copy(int players, int rounds, int TESTSIZE, bool isTest, FILE* p, int ppg){
	srandom(SEED);
	int seed_input = 0;
	seed_input = random();
	seed_input = seed_input%100;
	srandom(seed_input);
	int w_count = 0;
	
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	float stdevs[players];
	float matches[players][players];
	int best[players][players];
	float data[players*players];
	for(int i = 0; i < players; i++){
		stdevs[i] = 0;
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
	float dummy[7] = {999,999,999,999,999,999,999};
	float sit_out[players];
	float sitters[players%ppg];
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
		printf("\n");
		// Running Simulation
		for(int j = 0; j < rounds; j++){
			printf("\n");
			for(int i = 0; i < players; i++){
				printf("[%f]",sit_out[i]);
				C[i] = true;
			}
			printf("\n");
			if(sitting){
				printf("\n----------------------Sit Find Min----------------------------\n");
				for(int x=0;x<players%ppg;x++){
                                	sitters[x] =  findMin(players,ppg,dummy,sit_out,C);
					C[(int)(sitters[x])] = false;
				}
				printf("\n--------------------------------------------------------------\n");
				//printf("%d\n",sit);
                        }else{
                                sit = 9999;
                        }
			for(int x=0;x<players%ppg;x++){
				sit_out[(int)sitters[x]]++;
			}
			fprintf(outFile,"\n");
			//fprintf(outFile,"\nRound %d\n",j+1);
			w_count = players;
			//printf("\n");
			for(int z = 0; z < players; z++){
        	        	stdevs[z] = calculateSD_copy(matches[z],(float)players,1);
				//printf("[ %f ] ",stdevs[z]);
			}
			      
			int in=0;                                                              
			while((w_count >= ppg)&&(in<100)){
				//in++;
				// r1 = j, others are j's least played. make a max and min finder.
				sit_pass = true;
				no_equals = true;
				if(j>0){
					/*printf("\n");
					for(int k = 0; k<players;k++)printf("{%d}",C[k]);
					printf("\nJ: %d\n",j);*/
					if((sitting)&&(w_count==players)){
						r1 = (j+1)%(players);
					}else{
						r1 = findMax(players,stdevs,C,ppg,sitters);
					}
					//printf("Max: %d\n",r1);
					C[r1] = false;
					r2 = findMin(players,ppg,sitters,matches[r1],C);
					C[r2] = false;
					if(ppg>2){
						r3 = findMin(players,ppg,sitters,matches[r1],C);
						C[r3] = false;
					}
					if(ppg>3){
						r4 = findMin(players,ppg,sitters,matches[r1],C);
						C[r4] = false;
					}
					if(ppg>4){
						r5 = findMin(players,ppg,sitters,matches[r1],C);
						C[r5] = false;
					}
					if(ppg>5){
						r6 = findMin(players,ppg,sitters,matches[r1],C);
						C[r6] = false;
					}
					if(ppg>6){
						r7 = findMin(players,ppg,sitters,matches[r1],C);
						C[r7] = false;
					}
				}else{
					r1 = 0+(players-w_count);
					if(sitting)r1++;
					C[r1] = false;
					r2 = 1+(players-w_count);
					if(sitting)r2++;
					C[r2] = false;
					if(ppg>2){
						r3 = 2+(players-w_count);
						if(sitting)r3++;
						C[r3] = false;
					}
					if(ppg>3){
						r4 = 3+(players-w_count);
						if(sitting)r4++;
						C[r4] = false;
					}
					if(ppg>4){
                                                r5 = 4+(players-w_count);
						if(sitting)r5++;
						C[r5] = false;
                                        }
					if(ppg>5){
                                                r6 = 5+(players-w_count);
						if(sitting)r6++;
						C[r6] = false;
                                        }
					if(ppg>6){
                                                r7 = 6+(players-w_count);
						if(sitting)r7++;
						C[r7] = false;
                                        }
					//printf("\nELSE--------------\n");
				}
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
					//C[r1]= false,C[r2]= false;
					w_count -= 2;
					// -- double --
					if(ppg>2){
						matches[r3][r1] += 1;
						matches[r3][r2] += 1;
						matches[r2][r3] += 1;
                                        	matches[r1][r3] += 1;
						//C[r3]= false;
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
						//C[r4]= false;	
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
						//C[r5]= false;
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
                                        	//C[r6]= false;
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
                                        	//C[r7]= false;
                                        	w_count--;
					}
				

			}
			/*for(int x=0;x<players;x++){
				if(C[x]) sit_out[x]++;
			}*/
			
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
			stdev_new = calculateSD_copy(data, (float) pow(players,2),0);
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
	output_copy(best_round,players,best,rounds,isTest,p,ppg);
	fprintf(p,"\n");
	
	end = clock();
        
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	fprintf(p,"Time: %0.3f \n",cpu_time_used);
	free(C);
}

