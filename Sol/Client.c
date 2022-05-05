// Client Program
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Quad.h"
#include "Triple.h"
#include "Double.h"
#include "Scoreboard.h"
void scores_input(int players, int round){
	FILE* f;
	FILE* f2;
	if(round%2 == 1){
		f = fopen("scoreboard2","r");
		f2 = fopen("scoreboard","w");
	}else if(round%2 == 0){
		f = fopen("scoreboard","r");
                f2 = fopen("scoreboard2","w");
	}
	char buf[60];
	char* m[players];
	int x;
	int y;
	for(int i = 1; i <= players; i++){
		fgets(buf, 60, f);
		strtok(buf, "\n");
		printf("\n%d's score:",i);
		scanf("%d",&y);
		fprintf(f2,"%s	%d\n",buf,y);
	}
	printf("\n0: Yes\n1: No\nFinalize Scores?");
	scanf("%d",&x);
	printf("\n\n\n\n");
	if(x == 1){
		scores_input(players,round);
	}
	fclose(f);
	fclose(f2);
}
void print(void){
	FILE *f = fopen("best", "r");
	FILE *f2 = fopen("scOut","r");
	char buf[200];
	char *temp = "";
	char buf2[200];
	bool buf_end = false;
	while(fgets(buf2,200,f2)!=NULL){
		if(!buf_end)strtok(buf2,"\n");
		printf("%s",buf2);
		fgets(buf,200,f);
		if(!buf_end){
			for(int i = 0; i < 50-strlen(buf2); i++)printf(" ");
		}
		if(strcmp(temp,buf)!=0){
			printf("%s",buf);
			temp = strdup(buf);
		}else if(!buf_end){
			printf("\n");	
			buf_end = true;
		}
	}
	printf("\n");
	fclose(f);
	fclose(f2);
}
void copyTemplate(void){
	FILE* f = fopen("scoreboardT","r");
        FILE* f2 = fopen("scoreboard2","w");
        char buf[60];
        while(fgets(buf,60,f) != NULL){
                fprintf(f2,"%s",buf);
        }
        fclose(f);
        fclose(f2);
}
int main(void){
        int players, rounds,ppg;
        printf("How many players?\n");
        scanf("%d",&players);

        printf("How many rounds?\n");
        scanf("%d",&rounds);
        while(((ppg > 4)||(ppg < 2))&&(ppg != 0)){
                printf("\n-- Main Menu --\n");
                printf("2: Double\n3: Triple\n4: Quadruple\n0: Exit\n");
                scanf("%d",&ppg);
        }
        if(ppg == 2)doub(players, rounds);
        if(ppg == 3)trip(players, rounds);
        if(ppg == 4)quad(players, rounds);

	copyTemplate();
	for(int i = 1; i <= rounds; i++){
 	        scores_input(players,i);
		scoreBoard(i);
		print();
	}
}


