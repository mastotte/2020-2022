// Client Program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Game.h"
#include "Scoreboard.h"
//#include "Sol.html"
#define SEED 2022
int scores_input(int players, int round, bool isTest, FILE* p){
	int in = 0;
	if((!isTest)&&(round>1)){
		printf("1: Save and Exit\n2: Continue\n");
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
	char buf[60];
	int x;
	int y;
	for(int i = 1; i <= players; i++){
		fgets(buf, 60, f);
		strtok(buf, "\n");
		if(!isTest){
			printf("\n%d's score:",i);
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
		scores_input(players,round,isTest,p);
	}
    }
	fclose(f);
	fclose(f2);
	return (in == 1);
}
void print(void){
	FILE *f = fopen("GameFiles/best", "r");
	FILE *f2 = fopen("GameFiles/scOut","r");
	char buf[200];
	char *temp = "";
	char buf2[200];
	bool buf_end = false;
	while(fgets(buf2,200,f2)!=NULL){
		if(!buf_end)
			strtok(buf2,"\n");
		if(buf2[0] != '\n'){
			printf("%s",buf2);
		}
		fgets(buf,200,f);
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
	while(fgets(buf,200,f)!=NULL){
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
        char buf[60];
        while(fgets(buf,60,f) != NULL){
                fprintf(f2,"%s",buf);
        }
        fclose(f);
        fclose(f2);
	fclose(f3);
}/*
int main(void){ // TESTING VERSION
	int x = 10; // Amount of player counts to test
	int y = 20; // Amount of round counts to test
	FILE* p = fopen("GameFiles/trash","w");
	for(int players = 4; players <= x; players++){
		printf("\n%d Players: ", players);
		makeTemplate(players);
		reset();
		for(int rounds = 1; rounds <= y; rounds++){
			doub(players, rounds, 10000, true, p);
			scores_input(players,rounds,true, p);
                	scoreBoard(rounds);
			printf("Double: PASS\n");
		}
	}
	for(int players = 4; players <= x; players++){
		printf("\n%d Players: ", players);
		makeTemplate(players);
		reset();
		for(int rounds = 1; rounds <= y; rounds++){
			trip(players, rounds, 10000, true, p);
                        scores_input(players,rounds,true, p);
                        scoreBoard(rounds);
			printf("Triple: PASS\n");
			
		}
	}
	for(int players = 4; players <= x; players++){
		printf("\n%d Players: ", players);
		makeTemplate(players);
		reset();
		for(int rounds = 1; rounds <= y; rounds++){
			quad(players, rounds, 10000, true, p);
                        scores_input(players,rounds,true, p);
                        scoreBoard(rounds);		
			printf("Quadruple: PASS\n");
			
		}
	}
	printf("-------------------\n");
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
void loadGame(int* players, int* rounds, int* ppg, int* rounds_played){
	int saveslot = 0;
	FILE *save,*f2,*s1,*s2;
	f2 = fopen("GameFiles/f2","w");
	s1 = fopen("GameFiles/scoreboard","w");
	s2 = fopen("GameFiles/scoreboard2","w");
	char buf[300];
	char buf_small[3];
	
	displaySaveList();
	printf("\nEnter a save slot: ");
	scanf("%d",&saveslot);
	
	if(saveslot == 1) save = fopen("GameFiles/save1", "r");
        else if(saveslot == 2) save = fopen("GameFiles/save2","r");
        else if(saveslot == 3) save = fopen("GameFiles/save3","r");
        else if(saveslot == 4) save = fopen("GameFiles/save4","r");
        else save = fopen("GameFiles/save5","r");

	fgets(buf,300,save); // first line
	fgets(buf_small, 3, save); // players
	*players = atoi(buf_small);
	fprintf(f2,"%d\n",*players);
	printf("%d Players buf:(%s)\n",*players,buf_small);

	fgets(buf,300,save); // next line
	fgets(buf_small, 3, save); // rounds
	*rounds = atoi(buf_small);
	fprintf(f2,"%d\n",*rounds);
	printf("%d rounds buf:(%s)\n",*rounds,buf_small);
	
	fgets(buf,300,save); // next line
        fgets(buf_small, 3, save); // rounds
        *ppg = atoi(buf_small);
	fprintf(f2,"%d\n",*ppg);
	printf("%d ppg buf:(%s)\n",*ppg,buf_small);

	fgets(buf,300,save); // next line
	fgets(buf_small,3, save); // rounds played
	*rounds_played = atoi(buf_small);
	printf("%d rounds played buf:(%s)\n",*rounds_played,buf_small);
	fgets(buf,300,save);

	printf("------------SCHEDULE----------\n");
	for(int i = 0; i < *rounds; i++){
		fgets(buf,300,save);
		fprintf(f2,"%s",buf);
		printf("%s",buf);
	}
	printf("\n------------SCOREBOARD----------\n");
	for(int i = 0; i < *players; i++){
		fgets(buf,300,save);
		fprintf(s1,"%s",buf);
		fprintf(s2,"%s",buf);
		printf("%s",buf);
	}
	
	fclose(save);
	fclose(f2);
	fclose(s1);
	fclose(s2);	
}
void saveGame(int players, int rounds, int ppg, int rounds_played){
	int saveslot;
	char buf[300] = ""; // increase if scoreboard lines exceed 300. would require about 100 games.
	FILE *f,*f2,*f3,*saveList;
	printf("Enter a save slot: ");
	scanf("%d",&saveslot);
	saveList = fopen("GameFiles/saveList","r+");
	fseek(saveList, 3+(34*(saveslot-1)), SEEK_SET );
	fprintf(saveList,"______________________________");
	fseek(saveList,-30,SEEK_CUR);
	while((strlen(buf)<1)||(strlen(buf)>30)){
		printf("\n(No spaces)\nName of save: \n");
		scanf("%s", buf);
		if(strlen(buf)>30){
			printf("\nError: Save name too long. Must be under 30 characters.");
		}else{
			//printf("Length: %ld   ",strlen(buf));
			fprintf(saveList,"%s",buf);
		}
	}

	if(saveslot == 1) f = fopen("GameFiles/save1", "w");
	else if(saveslot == 2) f = fopen("GameFiles/save2","w");
	else if(saveslot == 3) f = fopen("GameFiles/save3","w");
	else if(saveslot == 4) f = fopen("GameFiles/save4","w");
	else f = fopen("GameFiles/save5","w");

	f2 = fopen("GameFiles/f2","r");
	if(rounds_played%2 == 1){
                f3 = fopen("GameFiles/scoreboard","r");
        }else if(rounds_played%2 == 2){
                f3 = fopen("GameFiles/scoreboard2","r");
        }
	fprintf(f,"----- Save Slot %d -----\n", saveslot);
	fprintf(f,"%d Players\n%d Rounds\n%d Players Per Game\n%d Rounds Played\n",players,rounds,ppg,rounds_played);
	// printing schedule
	for(int i = 0; i < 3; i++){ // ignore first 3 lines of "f2"
                fgets(buf,300,f2);
        }
        while(fgets(buf,300,f2)){
                fprintf(f,"%s",buf);
        }

	// printing scoreboard
	for(int i = 0; i < players; i++){
		printf("Saved player %d\n",i+1);
		fgets(buf, 300, f3);
		fprintf(f,"%s",buf);
	}
	
	
	fclose(f3);
	fclose(f2);
	fclose(saveList);
	fclose(f);
}

int main(void){
	FILE* p = stdout;
        int players, rounds, ppg, rounds_played;
	ppg = rounds_played = 0;
	int exit;
	
	ppg = getInput(&players, &rounds);
	if(ppg > 1){
		game(players, rounds, 2000, false, p, ppg);
		makeTemplate(players);
		reset();
	}else{
		loadGame(&players,&rounds,&ppg,&rounds_played);
		scoreBoard(rounds_played);
		print();
	}
	
	for(int i = rounds_played+1; i <= rounds; i++){
 	       	exit = scores_input(players,i, false, p);
		if((exit == 0)||(i == 1)){
			scoreBoard(i);
			print();
		}else{
			displaySaveList();
			saveGame(players, rounds, ppg, i-1);
			printf("Game Saved.\n");
			break;
		}
	}
}

