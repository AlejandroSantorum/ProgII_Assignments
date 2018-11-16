/**
*  Project: Assignment 4 - ProgII subject
*  File: functions.c
*  Version: 2.0
*  Date: May 1, 2017
*  Revision date: Jun 1, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include "functions.h"

/**
*	Function that frees all the memory allocated for an element of type integer
*/
void destroy_intp_function(void *elem){
	if(elem){
		free((int*)elem);
	}
}

/**
*	Function that copies the integer value of a given element.
*	It returns the copied integer (allocating memory for the copy)
*	or NULL in error case
*/
void* copy_intp_function(void *elem){
	int *dst=NULL;

	if(!elem){
		printf("Functions Error: element NULL pointer in copy_intp_function\n");
		return NULL;
	}

	dst = (int*) malloc(sizeof(int));
	if(!dst){
		printf("Functions Error: unable to allocate memory for the integer copy in copy_intp_function\n");
		return NULL;
	}

	*dst = *((int*)elem);
	return dst;
}

/**
*	Function that prints the value of a given element of type integer.
*	It returns the number of printed characters, or -1 in error case
*/
int print_intp_function(FILE *f, void *elem){
	if(!elem){
		printf("Functions Error: element NULL pointer in print_intp_function\n");
		return -1;
	}
	if(!f){
		printf("Functions Error: file NULL pointer in print_intp_function\n");
		return -1;
	}

	return fprintf(f, "[%d]\n", *((int*)elem));
}

/**
*	Function that compares two elements of type integer.
*	It returns a negative number in case elem2 > elem1,
*	a positive number if elem1 > elem2, or 0 if they are equal.
*	In error case it returns -1 (printing an error message).
*	Keep in mind it can return -1 and it is not an error case,
*	just check if it has printed the error message
*/
int cmp_intp_function(void *elem1, void *elem2){
	int a, b;

	if(!elem1){
		printf("Functions Error: element 1 NULL pointer in cmp_intp_function\n");
		return -1;
	}
	if(!elem2){
		printf("Functions Error: element 2 NULL pointer in cmp_intp_function\n");
		return -1;
	}

	a = *((int*)elem1);
	b = *((int*)elem2);
	return a-b;
}
