#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SEED 2022
#include <string.h>
#include <limits.h>
#include <stdbool.h>
//********************************************************************
//*                                                                  *
//*     Solitaire Scoreboard				                         *
//*                                                                  *
//*     mastotte, ucsc 2024                                          *
//*                                                                  *
//********************************************************************

void scoreBoard(int rounds,int players,int ppg,char names[players][2]){
	FILE* SCORES;

	if(rounds%2 == 1){
                SCORES = fopen("GameFiles/scoreboard","r");
        }else if(rounds%2 == 0){
                SCORES = fopen("GameFiles/scoreboard2","r");
        }
	FILE *infile = fopen("GameFiles/f2", "r");
	char p[50];
	char r[50];
	char ppG[50];
	//int players,ppg,delete,BUFSIZE,BUFSCORES;
	int BUFSIZE,BUFSCORES;
	int p1,p2,p3,p4,p5,p6,p7;
	float s1,s2,s3,s4,s5,s6,s7;
	s1=s2=s3=s4=s5=s6=s7=0.0;
	int s;
	
	fgets(p, 50, infile);
	//players = atoi(p);
	fgets(r, 50, infile);
	//delete = atoi(r);
	fgets(ppG, 50, infile);
	//ppg = atoi(ppG);
	BUFSIZE = 35*players;
	BUFSCORES = (10*rounds)+5;
	char buf[BUFSIZE];
	char buf_scores[BUFSCORES];
	//printf("players, rounds = ( %d , %d )\n",players,rounds);
	float pars[players+1][rounds+1];
	int scores[players+1][rounds+1];
	for(int i = 0; i < (players+1)*(rounds+1); i++){
		pars[1][i] = 0;
	}
	for(int i = 1; i <= players; i++){
		memset(buf_scores, '\0',BUFSCORES);
		fgets(buf_scores, BUFSCORES, SCORES);
		s = atoi(strtok(buf_scores,"	"));
		for(int j = 1; j <= rounds; j++){
			s = atoi(strtok(NULL,"	"));
			scores[i][j] = s;
			//printf("%d\n", scores[i][j]);
		}
		//printf("\n");
	}
	char* buf_copy;
	float avg = 0;
	float sum = 0;
	char* m[players/ppg];
	//get input matches
	
	for(int j = 1; j <= rounds; j++){
		fgets(buf, BUFSIZE, infile);
		buf_copy = strtok(buf, "-");
		for(int k = 0; k < players/ppg; k++){
			m[k] = buf_copy;
			buf_copy = strtok(NULL, "-");
		}
			
	for(int i = 0; i < players/ppg; i++){	
		p1 = p2 = p3 = p4 = p5 = p6 = p7 = 0;
		p1 = atoi(strtok(m[i], "  vs  "));
                //printf("\np1:%d",p1);
		p2 = atoi(strtok(NULL, "  vs  "));
        	//printf("\np2:%d",p2);
		if(ppg>2){
			p3 = atoi(strtok(NULL, "  vs  "));
        		//printf("\np3:%d",p3);
		}
		if(ppg>3){
			p4 = atoi(strtok(NULL, "  vs  "));
        		//printf("\np4:%d\n",p4);
		}
		if(ppg>4){
			p5 = atoi(strtok(NULL, "  vs  "));
		}
		if(ppg>5){
			p6 = atoi(strtok(NULL, "  vs  "));
		}
		if(ppg>6){
			p7 = atoi(strtok(NULL, "  vs  "));
		} 
		//printf("(%s),(%s)\n",buf,buf_copy);
		s1 = scores[p1][j];
		s2 = scores[p2][j];
		if(ppg>2)s3 = scores[p3][j];
		if(ppg>3)s4 = scores[p4][j];
		if(ppg>4)s4 = scores[p5][j];
		if(ppg>5)s5 = scores[p6][j];
		if(ppg>6)s6 = scores[p7][j];
		//printf("%0.0f %0.0f %0.0f %0.0f\n",s1,s2,s3,s4);
		sum = s1+s2;
		if(ppg>2)sum+=s3;
		if(ppg>3)sum+=s4;
		if(ppg>4)sum+=s5;
		if(ppg>5)sum+=s6;
		if(ppg>6)sum+=s7;

		avg = sum/ppg;
		pars[p1][j] = s1-avg;
		pars[p2][j] = s2-avg;
		if(ppg>2)pars[p3][j] = s3-avg;
		if(ppg>3)pars[p4][j] = s4-avg;
		if(ppg>4)pars[p5][j] = s5-avg;
		if(ppg>5)pars[p6][j] = s6-avg;
		if(ppg>6)pars[p7][j] = s7-avg;
		
	}
	}
	//output
	//fprintf(scOut,"\n	1	2	3	4	5\n");
	FILE* sc_out = fopen("GameFiles/scOut","w");
	float standings[players][3];// players, player number & total score
	float sum2;
	int sorted = 1;
	float t1,t2;

	fprintf(sc_out,"Scores");
	for(int i = 1; i <= players; i++){
		fprintf(sc_out,"\n");
                for(int j=0;j<2;j++){
                       fprintf(sc_out,"%c",names[i-1][j]);
                }
                fprintf(sc_out,":");
		for(int j = 1; j <= rounds; j++){
			if(scores[i][j]>0&&scores[i][j]<10)fprintf(sc_out," ");
			fprintf(sc_out," %d",scores[i][j]);
		}
	}
	fprintf(sc_out,"\n      \nPars");
	for(int i = 1; i <= players; i++){
		sum2 = 0.0;
		fprintf(sc_out,"\n");
		for(int j=0;j<2;j++){
                       fprintf(sc_out,"%c",names[i-1][j]);
                }
		fprintf(sc_out,":");
                for(int j = 1; j <= rounds; j++){
			if((pars[i][j]>0)&&(pars[i][j]<10))fprintf(sc_out," ");
			if(pars[i][j]>-10)fprintf(sc_out," ");
			sum2 += pars[i][j];
                        fprintf(sc_out," %0.0f",pars[i][j]);
		}
		standings[i][1] = i;
		standings[i][2] = sum2;
	}
	while(sorted != 0){
		sorted = 0;
		for(int i = 1; i < players; i++){
			if(standings[i][2] > standings[i+1][2]){
				t1 = standings[i+1][1];
				t2 = standings[i+1][2];
				standings[i+1][1] = standings[i][1];
				standings[i+1][2] = standings[i][2];
				standings[i][1] = t1;
				standings[i][2] = t2;
				sorted++;
			}
		}
	} 	
	fprintf(sc_out,"\n      \nStandings:");
	for(int i = 1; i <= players; i++){
		fprintf(sc_out,"\n");
		for(int j=0;j<2;j++){
                	fprintf(sc_out,"%c",names[(int)(standings[i][1])-1][j]);
                }
		fprintf(sc_out,": %0.1f",standings[i][2]);
	}
	fclose(sc_out);	
	
}	
