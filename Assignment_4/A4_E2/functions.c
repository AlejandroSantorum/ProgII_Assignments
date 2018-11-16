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
#include "node.h"

/**
*	Function that frees all the memory allocated for an element of type node
*/
void destroy_node_function(void* elem){
    node_destroy((Node *)elem);
}

/**
*	Function that copies the node information of a given node into a new one.
*	It returns the copied node (allocating memory for the copy)
*	or NULL in error case
*/
void* copy_node_function(void *elem){
    return node_copy((Node *)elem);
}

/**
*	Function that prints the value of a given element of type node.
*	It returns the number of printed characters, or -1 in error case
*/
int  print_node_function(FILE *f, void *elem){
    return node_print(f, (Node *)elem);
} 

/**
*	Function that compares two elements of type node.
*	It returns a negative number in case info(elem2) > info(elem1),
*	a positive number if info(elem1) > info(elem2), or 0 if they are equal.
*	In error case it returns -1 (printing an error message).
*	Keep in mind it can return -1 and it is not an error case,
*	just check if it has printed the error message
*/
int cmp_node_function(void *elem1, void *elem2){
    return node_cmp((Node *)elem1,(Node *)elem2);
}
