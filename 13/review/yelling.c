#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int main(int argc, char **argv) {
  // You're going to have to use argc to decide whether to open up a file, or to
  // read from stdin.
  // If you haven't seen them before, you will likely want to use the functions
  // `fgetc()` and `fputc()`.
  
	int letter;
	char file_letter = 'a';
	char temp;
	char input[50] = {0};
	FILE *file;

	if (argc > 1){

		for (int word = 1; word < argc; word++){
			letter = 0;
			while(argv[word][letter]){
				if ((96 < argv[word][letter]) && (123 > argv[word][letter])){
					temp = argv[word][letter] - 32;
					printf("%c",temp);	
				}else{
					printf("%c",argv[word][letter]);
				}
				letter++;
			}
			printf(" ");
			
		}
		
	}else{
		
		printf("\nEnter the name of the file: ");
		fgets(input,50,stdin);
		strtok(input,"\n");
		file = fopen(input,"r");
		file_letter = fgetc(file);
		do{
		
			if ((96 < file_letter) && (123 > file_letter)){
				temp = file_letter - 32;
				printf("%c",temp);
			}else{
				printf("%c",file_letter);
			}	

			file_letter = fgetc(file);

		}while (file_letter != -1);
		fclose(file);
	}

	printf("\n");


  return 0;
}
