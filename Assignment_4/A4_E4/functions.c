/**
*  Project: Assignment 4 - ProgII subject
*  File: functions.c
*  Version: 2.0
*  Date: May 2, 2017
*  Revision date: Jun 2, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include "functions.h"

/**
*	Function that frees all the memory allocated for an element of type string
*/
void destroy_str_function(void *elem){
	if(elem){
		free((int*)elem);
	}
}

/**
*	Function that copies the string of a given element.
*	It returns the copied string (allocating memory for the copy)
*	or NULL in error case
*/
void* copy_str_function(void *elem){
	char *dst=NULL;

	if(!elem){
		printf("Functions Error: element NULL pointer in copy_str_function\n");
		return NULL;
	}

	dst = (char*) malloc((strlen((char*)elem)+1) * sizeof(char));
	if(!dst){
		printf("Functions Error: unable to allocate memory for the string copy in copy_str_function\n");
		return NULL;
	}

	strcpy(dst, (char*)elem);
	return dst;
}

/**
*	Function that prints the value of a given element of type string.
*	It returns the number of printed characters, or -1 in error case
*/
int print_str_function(FILE *f, void *elem){
	if(!elem){
		printf("Functions Error: element NULL pointer in print_str_function\n");
		return -1;
	}
	if(!f){
		printf("Functions Error: file NULL pointer in print_str_function\n");
		return -1;
	}

	return fprintf(f, " %s", (char*)elem);
}

/**
*	Function that compares two elements of type string.
*	It returns a negative number in case elem2 > elem1,
*	a positive number if elem1 > elem2, or 0 if they are equal.
*	In error case it returns -1 (printing an error message).
*	Keep in mind it can return -1 and it is not an error case,
*	just check if it has printed the error message
*/
int cmp_str_function(void *elem1, void *elem2){
	if(!elem1){
		printf("Functions Error: element 1 NULL pointer in cmp_str_function\n");
		return -1;
	}
	if(!elem2){
		printf("Functions Error: element 2 NULL pointer in cmp_str_function\n");
		return -1;
	}

	return strcmp((char*)elem1, (char*)elem2);
}
