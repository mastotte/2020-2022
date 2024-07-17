#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct Customer{

	char *email;
	char *display_name;
	int shoe_size;
	char *fav_food;
	struct Customer *next;

}Customer;

unsigned long hash(char *str);

void add_person(char *email, char *display_name, int shoe_size, char* fav_food, 
		Customer **buckets, int num_buckets);

Customer *add(char *email, char *display_name, int shoe_size, char *fav_food, Customer *bucket);

Customer *lookup_email(int num_buckets, Customer **buckets, char *email, int *index);

void import_customers(char *filename, Customer **buckets, int num_buckets);

void delete_person(Customer **buckets, int num_buckets, char *email);

void list(int num_buckets, Customer **buckets);

void save(char *filename, Customer **buckets, int num_buckets);

void quit(int num_buckets, Customer **buckets);


