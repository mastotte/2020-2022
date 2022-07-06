// Client Program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Game.h"
#include "Scoreboard.h"
//#include "Sol.html"
#define SEED 2022
int scores_input(int players, int round, bool isTest, FILE* p, char names[players][2]){// char* names[]
	int in = 0;
	if((!isTest)&&(round>1)){
		printf("\n1: Exit\n2: Continue\n");
		scanf("%d",&in);
		printf("\n");
	}
	srandom(SEED);
	FILE* f;
	FILE* f2;
	if(round%2 == 1){
		f = fopen("GameFiles/scoreboard2","r");
		f2 = fopen("GameFiles/scoreboard","w");
	}else if(round%2 == 0){
		f = fopen("GameFiles/scoreboard","r");
                f2 = fopen("GameFiles/scoreboard2","w");
	}
    if(in != 1){
	int BUFSIZE = (10*round)+5;
	char buf[BUFSIZE];
	int x;
	int y;
	for(int i = 1; i <= players; i++){
		fgets(buf, BUFSIZE, f);
		strtok(buf, "\n");
		if(!isTest){
			printf("\n");
			for(int j=0;j<2;j++){
				printf("%c",names[i-1][j]);
			}
			printf("'s score: ");
			scanf("%d",&y);
		}
		if(isTest)y = 5;
		fprintf(f2,"%s	%d\n",buf,y);
	}
	if(!isTest){
		printf("\n0: Yes\n1: No\nFinalize Scores?");
		scanf("%d",&x);
		printf("\n\n\n\n");
	}
	if(isTest)x = 0;
	if(x == 1){
		scores_input(players,round,isTest,p,names);
	}
    }
	fclose(f);
	fclose(f2);
	return (in == 1);
}
void print(int BUFSIZE, int BUF2SIZE){
	FILE *f = fopen("GameFiles/best", "r");
	FILE *f2 = fopen("GameFiles/scOut","r");
	char buf[BUFSIZE];
	char *temp = "";
	char buf2[BUF2SIZE];
	bool buf_end = false;
	for(int i=0;i<10;i++) printf("\n\n\n\n");
	while(fgets(buf2,BUF2SIZE,f2)!=NULL){
		if(!buf_end)
			strtok(buf2,"\n");
		if(buf2[0] != '\n'){
			printf("%s",buf2);
		}
		fgets(buf,BUFSIZE,f);
		if(!buf_end){
			for(unsigned long i = 0; i < 50-strlen(buf2); i++)printf(" ");
		}
		if(strcmp(temp,buf)!=0){
			printf("%s",buf);
			temp = strdup(buf);
		}else if(!buf_end){
			printf("\n");	
			buf_end = true;
		}
	}
	while(fgets(buf,BUFSIZE,f)!=NULL){
		for(int i = 0; i < 50; i++)printf(" ");
		printf("%s",buf);
	}
	printf("\n");
	fclose(f);
	fclose(f2);
}
void makeTemplate(int players){
	FILE* f = fopen("GameFiles/scoreboardTemplate","w");
	for(int i = 1; i <= players; i++){
		fprintf(f,"%d:\n",i);
	}
	fclose(f);
}
void reset(void){
	FILE* f = fopen("GameFiles/scoreboardTemplate","r");
        FILE* f2 = fopen("GameFiles/scoreboard2","w");
	FILE* f3 = fopen("GameFiles/scoreboard","w");
	FILE* f4 = fopen("GameFiles/scOut","w");
        char buf[60];
        while(fgets(buf,60,f) != NULL){
                fprintf(f2,"%s",buf);
        }
        fclose(f);
        fclose(f2);
	fclose(f3);
	fclose(f4);
}
void resetSaves(){
	FILE* f = fopen("GameFiles/saveList","w");
	fprintf(f,"1: ______________________________\n2: ______________________________\n3: ______________________________\n");
	fprintf(f,"4: ______________________________\n5: ______________________________\n");
	fclose(f);
}
/*
int main(void){ // TESTING VERSION
	int x = 30; // Amount of player counts to test
	int y = 10; // Amount of round counts to test
	FILE* p = fopen("GameFiles/trash","w");
    for(int ppg = 2; ppg <= 7; ppg++){
	for(int players = 25; players <= x; players++){
		if(ppg<players){
		printf("\n%d Players: \n", players);
		makeTemplate(players);
		reset();
		for(int rounds = 1; rounds <= y; rounds++){
			game(players, rounds, 2000, p, ppg);
			scores_input(players,rounds,true,p);
                	scoreBoard(rounds);
			printf("PPG:%d P:%d R:%d PASS\n",ppg,players,rounds);
		}
		}
	}
	printf("-------------------\n");
    }
	fclose(p);
}
*/
int getInput(int *players, int *rounds){
	int p,r,out;
	printf("\n-- Main Menu --\n");
        printf("0: New Game\n1: Load Saved Game\n");
        scanf("%d",&out);
	if(out == 1){
		return out;
	}

        printf("How many players?\n");
        scanf("%d",&p);
	*players = p;

        printf("How many rounds?\n");
        scanf("%d",&r);
	*rounds = r;

        while((out > 7)||(out < 2)){
                printf("\n-- Game Selection --\n");
                printf("2: Double\n3: Triple\n4: Quadruple\n5: Pentuple\n6: Hextuple\n7: Septuple\n0: Exit\n");
                scanf("%d",&out);
                if(out == 0) break;
        }
	// FOR LOOP ASKING FOR PLAYERS
	return out;	
}
void displaySaveList(){
	FILE* saveList = fopen("GameFiles/saveList","r");
	char buf[60];
	while(fgets(buf, 60, saveList)){
		if(buf[3] != '_'){
			for(unsigned long i=0; i<strlen(buf); i++){
				if(buf[i] == '_'){
					buf[i] = ' ';
				}
			}
		}
                printf("%s",buf);
        }
	fclose(saveList);
}
int loadGame(int* players, int* rounds, int* ppg, int* rounds_played, char names[*players][2]){
	int saveslot = 0;
	FILE *save,*f2,*s1,*s2;
	f2 = fopen("GameFiles/f2","w");
	s1 = fopen("GameFiles/scoreboard","w");
	s2 = fopen("GameFiles/scoreboard2","w");
	char line[30];
	char buf_small[3];
	
	displaySaveList();
	printf("\nEnter a save slot: ");
	scanf("%d",&saveslot);
	
	if(saveslot == 1) save = fopen("GameFiles/save1", "r");
        else if(saveslot == 2) save = fopen("GameFiles/save2","r");
        else if(saveslot == 3) save = fopen("GameFiles/save3","r");
        else if(saveslot == 4) save = fopen("GameFiles/save4","r");
        else save = fopen("GameFiles/save5","r");

	fgets(line,30,save); // first line
	fgets(buf_small, 3, save); // players
	*players = atoi(buf_small);
	fprintf(f2,"%d\n",*players);
	printf("%d Players buf:(%s)\n",*players,buf_small);
	
	fgets(line,30,save); // next line
	fgets(buf_small, 3, save); // rounds
	*rounds = atoi(buf_small);
	fprintf(f2,"%d\n",*rounds);
	printf("%d rounds buf:(%s)\n",*rounds,buf_small);
	
	fgets(line,30,save); // next line
        fgets(buf_small, 3, save); // ppg
        *ppg = atoi(buf_small);
	fprintf(f2,"%d\n",*ppg);
	printf("%d ppg buf:(%s)\n",*ppg,buf_small);

	fgets(line,30,save); // next line
	fgets(buf_small,3, save); // rounds played
	*rounds_played = atoi(buf_small);
	printf("%d rounds played buf:(%s)\n",*rounds_played,buf_small);
	fgets(line,30,save);
	
	int BUFSIZE = (10*(*rounds))+3;
        int BUF2 = (35*(*players));
        if(BUF2>BUFSIZE) BUFSIZE = BUF2;
	char buf[BUFSIZE];

	printf("------------SCHEDULE----------\n");
	for(int i = 0; i < *rounds; i++){
		fgets(buf,BUFSIZE,save);
		fprintf(f2,"%s",buf);
		printf("%s",buf);
	}
	printf("\n------------SCOREBOARD----------\n");
	for(int i = 0; i < *players; i++){
		fgets(buf,BUFSIZE,save);
		fprintf(s1,"%s",buf);
		fprintf(s2,"%s",buf);
		printf("%s",buf);
	}
	printf("\n------------PLAYERS------------\n");
	fgets(buf,BUFSIZE,save);
	for(int i = 0; i < *players; i++){
		for(int j = 0; j < 2; j++){
			names[i][j] = buf[j+(i*2)];
			printf("%c",buf[j+(i*2)]);
		}
		printf("\n");
	}	
	fclose(save);
	fclose(f2);
	fclose(s1);
	fclose(s2);	
	return saveslot;
}
int createGame(){
	int saveslot = 0;
	bool first_input = true;
        int BUFSIZE = 20;
        char buf[BUFSIZE];
        FILE *saveList;
	displaySaveList();
        printf("Enter a save slot: ");
        scanf("%d",&saveslot);
        saveList = fopen("GameFiles/saveList","r+");
        fseek(saveList, 3+(34*(saveslot-1)), SEEK_SET );
        fprintf(saveList,"______________________________");
        fseek(saveList,-30,SEEK_CUR);
        while((first_input)||(strlen(buf)<1)||(strlen(buf)>30)){
                first_input = false;
                printf("\n(No spaces)\nName of save: \n");
                scanf("%s", buf);
                if(strlen(buf)>30){
                        printf("\nError: Save name too long. Must be under 30 characters.");
                }else{
                        printf("Length: %ld   ",strlen(buf));
                        fprintf(saveList,"%s",buf);
                 }
	}
	return saveslot;
 }

void saveGame(int players, int rounds, int ppg, int rounds_played, char names[players][2], int saveslot){
	int BUFSIZE = (10*rounds)+5;
	char buf[BUFSIZE];
	FILE *f,*f2,*f3;

	if(saveslot == 1) f = fopen("GameFiles/save1", "w");
	else if(saveslot == 2) f = fopen("GameFiles/save2","w");
	else if(saveslot == 3) f = fopen("GameFiles/save3","w");
	else if(saveslot == 4) f = fopen("GameFiles/save4","w");
	else f = fopen("GameFiles/save5","w");

	f2 = fopen("GameFiles/f2","r");
	if(rounds_played%2 == 1){
                f3 = fopen("GameFiles/scoreboard","r");
        }else if(rounds_played%2 == 0){
                f3 = fopen("GameFiles/scoreboard2","r");
        }
	fprintf(f,"----- Save Slot %d -----\n", saveslot);
	fprintf(f,"%d Players\n%d Rounds\n%d Players Per Game\n%d Rounds Played\n",players,rounds,ppg,rounds_played);
	// printing schedule
	for(int i = 0; i < 3; i++){ // ignore first 3 lines of "f2"
                fgets(buf,BUFSIZE,f2);
        }
        while(fgets(buf,BUFSIZE,f2)){
                fprintf(f,"%s",buf);
        }
	// printing scoreboard
	for(int i = 0; i < players; i++){
		printf("Saved player %d\n",i+1);
		fgets(buf, BUFSIZE, f3);
		fprintf(f,"%s",buf);
	}
	// printing names
	for(int i = 0; i < players; i++){
                //fprintf(f,"\n");
                for(int j=0;j<2;j++){
                       fprintf(f,"%c",names[i][j]);
                }
        }
	
	fclose(f3);
	fclose(f2);
	fclose(f);
}

int main(void){
	FILE* p = stdout;
        int players, rounds, ppg, rounds_played, saveslot, exit;
	ppg = rounds_played = 0;
	
	ppg = getInput(&players, &rounds);
	char names[players][2];
	//resetSaves();           // un-comment this to reset the save files
	char name[50];
	if(ppg > 1){
		printf("\nEnter Each Player's First and Last Initials");
		for(int i = 0; i < players; i++){
                	printf("\nPlayer %d: ",i+1);
			scanf("%s",name);
			for(unsigned long j=0;j<strlen(name);j++){
				names[i][j] = name[j];
			}
		}
		game(players, rounds, 2000, p, ppg, names);
		saveslot = createGame();
		makeTemplate(players);
		reset();
	}else{
		saveslot = loadGame(&players,&rounds,&ppg,&rounds_played,names);
		scoreBoard(rounds_played,players,ppg,names);
		print(10*players,8*rounds);
	}
	
	for(int i = rounds_played+1; i <= rounds; i++){
		print(10*players,8*rounds);
 	       	exit = scores_input(players,i, false, p,names);
		if((exit == 0)||(i == 1)){
			scoreBoard(i,players,ppg,names);
			print(10*players,8*rounds);			
		}else{
			break;
		}
		saveGame(players, rounds, ppg, i-1,names,saveslot);
		printf("Game Saved.\n");
	}
}

