#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SEED 2022
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include "Game.h"
//********************************************************************
//*                                                                  *
//*	Figuring out the Solitaire matches, once and for all.        *
//*                                                                  *
//* mastotte, ucsc 2024                                              *
//*                                                                  *
//********************************************************************
float calculateSD(float data[], float p, int matches_call) {
    float sum = 0.0, mean, SD = 0.0;
    int i;
    int z = 0;
    for (i = 0; i < p; ++i) {
        sum += data[i];
	if(data[i] == 0.0){
		z++;
	}	
    }
    if(matches_call == 0) z = 0;
    mean = sum / (p-z);
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
void output(int best_round, int n, int rounds, FILE* p, int ppg, int players, char names[players][2]){
	int BUFSIZE = 10*players;
  	char buf[BUFSIZE];
 	FILE *infile = fopen("GameFiles/out", "r");
	FILE *bestOutput = fopen("GameFiles/best","w");
	FILE *f2Output = fopen("GameFiles/f2","w");
	fprintf(p,"\nBest round = %d\n",best_round);
	fprintf(f2Output,"%d\n%d\n%d\n",n,rounds,ppg);
	int c = 1;
  	while (fgets(buf, BUFSIZE, infile) != NULL){
		if(atoi(buf) == best_round){
			for(int i = 0; i < rounds; i++){
				fgets(buf, BUFSIZE, infile);
				fprintf(bestOutput,"Round %d\n",c);
				for(unsigned long i=0;i<strlen(buf);i++){
                                	if(isdigit(buf[i])){
                                       		for(unsigned long i2=0;i2<2;i2++){
                                                	fprintf(bestOutput,"%c",names[atoi(&buf[i])-1][i2]);
                                        	}
                                	}else{
                                        	fprintf(bestOutput,"%c",buf[i]);
                                	}
                        	}
				//fprintf(bestOutput,"\nbuf:%s(len:%ld)",buf,strlen(buf));
				fprintf(f2Output,"%s",buf);
    			fprintf(p,"%s",buf);
				c++;
			}
			break;
		}
  	}
	fclose(f2Output);
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
		if((x[i]<lowest)&&(C[i] == true)&&(!isSitting(i,players%ppg,sitters))){
			lowest = x[i];
			index = i;	
		}
	}
	return index;
}
void game(int players, int rounds, int TESTSIZE, FILE* p, int ppg, char names[players][2]){
	srandom(SEED);
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	
	FILE *outFile = fopen("GameFiles/out","w");
	bool *C,sitting,HIT_MAX;
	int r1,r2,r3,r4,r5,r6,r7,index,best_round,sit,w_count;
	int best[players][players];
	float highest,stdev1,stdev,stdev_new,SIT_MAX;
	float stdevs[players];
	float matches[players][players];
	float data[players*players];
	float dummy[7] = {999,999,999,999,999,999,999};
	float sit_out_count[players];
	float sitters[players%ppg];
	r1=r2=r3=r4=r5=r6=r7=index=best_round=stdev_new=sit=w_count=0;
	highest=stdev1=stdev=-1.0;
	sitting = (players%ppg != 0);
	C = malloc(players*(sizeof(bool))+1);
	SIT_MAX = ceil((float)((players%ppg)*rounds)/players);
	for(int i = 0; i < players; i++){
		stdevs[i] = 0;
		for(int j = 0; j < players; j++){
			matches[i][j] = 0;
			best[i][j] = 0;
		}
	}
	if(sitting){
		fprintf(p,"People have to sit out.\n");
	}else{
		fprintf(p,"Nobody is sitting out.\n");
	}
	if(players == ppg)
		TESTSIZE = players+1;
	for(int test_count = players+1; test_count <= TESTSIZE; test_count++){
		fprintf(outFile,"%d",test_count);
		HIT_MAX = false;
		// Clearing The Array
		for(int i = 0; i < players; i++){
			sit_out_count[i] = 0;
                	for(int j = 0; j < players; j++){
                        	matches[i][j] = 0;
                	}
        	}
		//printf("\n");
		// Running Simulation
		for(int j = 0; j < rounds; j++){
			//printf("\n");
			for(int i = 0; i < players; i++){
				//printf("%d: [%f]\n",i+1,sit_out_count[i]);
				C[i] = true;
			}
			//printf("\n");
			if(sitting){
				int count = 0;
				int sit_random = 0;
				while(count<players%ppg){
					if(HIT_MAX){
						sit_random = findMin(players,ppg,dummy,sit_out_count,C);
						sitters[count] = sit_random;
						C[sit_random] = false;
						sit_out_count[sit_random]++;
						count++;
					}else{
						sit_random = random();
						sit_random = sit_random%players;
						if((sit_out_count[sit_random] < SIT_MAX)&&(C[sit_random]==true)){
							//printf("\n%d is sitting",sit_random);
							sitters[count] = sit_random;
							C[sit_random] = false;
							sit_out_count[sit_random]++;
							if(sit_out_count[sit_random] == SIT_MAX) 
								HIT_MAX = true;
							count++;
						}
					}
				}
                        }else{
                                sit = 9999;
                        }
			fprintf(outFile,"\n");
			//fprintf(outFile,"\nRound %d\n",j+1);
			w_count = players;
			for(int z = 0; z < players; z++){
				stdevs[z] = calculateSD(matches[z],(float)players,1);
			}                                                             
			while(w_count >= ppg){
				// r1 = j, others are j's least played. make a max and min finder.
				if(j>0){
					if((sitting)&&(w_count==players)){
						r1 = (j+1)%(players);
					}else{
						r1 = findMax(players,stdevs,C,ppg,sitters);
					}
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
				}					
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
			
			
		}
		bool sits_fair = true;
		for(int k = 0; k < players; k++){
			if((sit_out_count[0] != sit_out_count[k])&&(sitting)){
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
			stdev_new = calculateSD(data, (float) pow(players,2),0);
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
	output(best_round,players,rounds,p,ppg,players,names);
	fprintf(p,"\n");
	
	end = clock();
        
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	fprintf(p,"Time: %0.3f \n",cpu_time_used);
	free(C);
}

