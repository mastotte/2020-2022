#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "hw7.h"


#define NUM_BUCKETS 10

unsigned long hash(char *str){

	unsigned long hash = 5381;
	int c;

	while (*str != '\0'){
		c = *str;
		hash = ((hash << 5) + hash) + (unsigned char) c;
		str++;
	}
	return hash;
}

void add_person(char *email, char *display_name, int shoe_size, char *fav_food, 
		Customer **buckets, int num_buckets){
	
	size_t which_bucket = hash(email) % num_buckets;
	buckets[which_bucket] = add(email,display_name,shoe_size,fav_food,buckets[which_bucket]);
	//printf("%s goes in bucket %zu\n",email,which_bucket);

}

Customer *add(char *email, char *display_name, int shoe_size, char *fav_food, Customer *bucket){

	Customer *new_customer;
	new_customer = malloc(sizeof(Customer));
	
	new_customer->email = strdup(email);
	new_customer->display_name = strdup(display_name);
	new_customer->fav_food = strdup(fav_food);
	new_customer->shoe_size = shoe_size;
	new_customer->next = bucket;
	
	return new_customer;
}

Customer *lookup_email(int num_buckets, Customer **buckets, char *e, int *index){
	bool found = false;
	Customer *current;
	
	for (int i = 0; i < num_buckets; i++){
		current = buckets[i];
		if (buckets[i] != NULL){
			while (current){ 
				if (strcmp(current->email,e) == 0){
					found = true;
					printf("\nEmail : %s",current->email);
					printf("\nName  : %s",current->display_name);
					printf("\nShoe Size : %d",current->shoe_size);
					printf("\nFavorite Food : %s\n",current->fav_food);
					*index = i;
					return current;
				}
				current = current->next;
			}
		}
	}
	if (!found){
		printf("\nCustomer '%s' not found\n",e);

	}
	return 0;
}

void delete_person(Customer **buckets, int num_buckets ,char *email){
	Customer *current;
	Customer *temp;
	int index = 0;

	printf("\n-----Deleting-----");
	Customer *delete_bucket = lookup_email(num_buckets, buckets, email, &index);

	if (delete_bucket == 0){
		printf("------------------\n");
		return;
	}
	Customer *previous = buckets[index];
	
	if (buckets[index] == delete_bucket){
		temp = buckets[index];
		buckets[index] = buckets[index]->next;
		free(temp);
	}else{
	
		while(previous->next != delete_bucket){
			previous = previous->next;
		}
		current = previous->next;
		if (current->next){
			previous->next = current->next;
			free(current);
		}else{
			previous->next = NULL;
			free(current);
		}
	}
	printf("------------------\n");
}

void list(int num_buckets, Customer **buckets){
	
	Customer *current;
	for (int i = 0; i < num_buckets; i++){
	
		if (buckets[i] != NULL){
			current = buckets[i];
			printf("%s %s",buckets[i]->email,buckets[i]->display_name);
			printf(" %d %s\n",buckets[i]->shoe_size,buckets[i]->fav_food);
			while (current->next){
				current = current->next;
				printf("%s %s",current->email,current->display_name);
				printf(" %d %s\n",current->shoe_size,current->fav_food);
						
			}
		}
	}

}

void save(char *filename, Customer **buckets, int num_buckets){
	Customer *current;
	FILE *file;
	file = fopen(filename, "w+");

	for (int i = 0; i < num_buckets; i++){
		current = buckets[i];
		while (current != NULL){
			fprintf(file,"%s	%s	",current->email,current->display_name);
			fprintf(file,"%d	%s\n",current->shoe_size,current->fav_food);
			current = current->next;
		}
	}

	fclose(file);
}

void quit(int num_buckets, Customer **buckets){
	Customer *current;
	Customer *temp;
	
	for (int i = 0; i < num_buckets; i++){
		current = buckets[i];
		while(current){		
			temp = current->next;
			free(current->email);
			free(current->display_name);
			free(current->fav_food);
			free(current);
			current = temp;
		}
	}
}
	
void import_customers(char *filename, Customer **buckets, int num_buckets){
	
	FILE *file;
	int count = 0;
	file = fopen(filename, "r");
	const int BUFSIZE = 512;
	char buf[512];

	int j = 0;
	int row = 0;
	int x = 0;
	char string[60] = {0};
	char display_name[30] = {0};
	char email[30] = {0};
	int shoe_size = 0;
	char fav_food[30] = {0};
	char shoe_size_string[30] = {0};
	int i = 0;
	int y = 0;
	
	while (fgets(buf,BUFSIZE,file) != NULL){
		
		j = 0;
		x = 0;
		i = 0;
		memset(email,'\0',30);
		memset(fav_food,'\0',30);
		memset(display_name, '\0', 30);
		memset(shoe_size_string,'\0',30);
		memset(string, '\0', 60);
		while(buf[i] != '\n'){
			
			string[i] = buf[i];
			if ((string[i] == '	')&&(j == 0)){
				y=0;
				while (string[y] != '	'){
					email[y] = string[y];
					y++;
				}
				count++;		
			}
			if ((string[i] == '	')&&(j == 1)){
				x=0;
				while (y < i-1){
					display_name[x] = string[y+1];
					x++;
					y++;
				}
				y++;
				count++;
			}
			if ((string[i] == '	')&&(j == 2)){
				x=0;
				while (y < i){
					shoe_size_string[x] = string[y+1];
					x++;
					y++;
				}
				shoe_size = atoi(shoe_size_string);
				count++;
				
			}
			if (buf[i+1] == '\n'){
				x=0;
				while (y <= i){
					fav_food[x] = string[y+1];
					x++;
					y++;
				}
				count++;
			}	
			i++;
			x++;
			if (count > 0){
				j++;
				count = 0;
			}
		}
		add_person(email, display_name, shoe_size, fav_food, buckets, num_buckets);
		row++;
	}
	fclose(file);		
}

int main(void){
	
	char input[] = "";
	Customer *buckets[NUM_BUCKETS] = {NULL};
	bool sensible_result = false;
	int option = 0;
	char *inputs_array[6] = {"add", "lookup", "delete", "list", "save", "quit"};
	char email[50] = {0};
	char display_name[50] = {0};
	char shoe_size_string[50] = {0};
	int shoe_size = 0;
	int temp = 0;
	char fav_food[50] = {0};
	//email, display name, shoe size, favorite food
	
	import_customers("customers.tsv", buckets, NUM_BUCKETS);

    do{
	
        while (!sensible_result){
		
		printf("\nPlease enter one of the options shown below:"
			"\n'add' to Add a new person to the list"
			"\n'lookup' to Look up a person by their email"
			"\n'delete' to Delete a person by their email"
			"\n'list' to Display every user in the list"
			"\n'save' to Save the list to customers.tmv"
			"\n'quit' to Clean up memory and exit the program\n");
		
		fgets(input,8,stdin);
		strtok(input, "\n");
		
		
		for (int i = 0; i < 6; i++){
			
			if (strcmp(input,inputs_array[i]) == 0){
				option = i;
				sensible_result = true;
			}

		}
		
	}
	if (option == 0){
		//add
		printf("\nEnter an email address: ");
		fgets(email,50,stdin);
		strtok(email, "\n");
		printf("\nEnter a display name: ");
		fgets(display_name,50, stdin);
		strtok(display_name, "\n");
		printf("\nEnter a favorite food: ");
		fgets(fav_food,50,stdin);
		strtok(fav_food,"\n");
		printf("\nEnter a shoe size: ");
		fgets(shoe_size_string,50,stdin);
		shoe_size = atoi(shoe_size_string);
		add_person(email,display_name,shoe_size,fav_food,buckets,NUM_BUCKETS);
	}else if (option == 1){
		//lookup
		printf("\nEnter an email address: ");
		fgets(email,50,stdin);
		strtok(email, "\n");
		lookup_email(NUM_BUCKETS, buckets, email, &temp);

	}else if (option == 2){
		//delete
		printf("\nEnter an email address: ");
		fgets(email,50,stdin);
		strtok(email, "\n");
		delete_person(buckets, NUM_BUCKETS, email);
	}else if (option == 3){
		//list
		list(NUM_BUCKETS, buckets);
	}else if (option == 4){
		//save
		save("customers.tsv", buckets, NUM_BUCKETS);
	}else if (option == 5){
		//quit
	}	
	
	sensible_result = false;
	
    }while(option != 5);
  
    quit(NUM_BUCKETS, buckets);	    
}	
