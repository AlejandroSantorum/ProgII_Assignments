/**
*  Project: Assignment 4 - ProgII subject
*  File: a4_e3_test.c
*  Version: 2.0
*  Date: May 1, 2017
*  Revision date: Jun 2, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "functions.h"
#include "list.h"

Tree* read_data_from_file(char *filename){
    FILE *in=NULL;
    Tree *t=NULL;
    destroy_elementtree_function_type f1 = destroy_intp_function;
    copy_elementtree_function_type f2 = copy_intp_function;
    print_elementtree_function_type f3 = print_intp_function;
    cmp_elementtree_function_type f4 = cmp_intp_function;
    int aux;

    if(!filename){
    	printf("ERROR: filename NULL pointer in read_data_from_file function\n");
    	return NULL;
    }
    
    if(!(t = tree_ini(f1, f2, f3, f4))){
    	printf("ERROR: unable to initialize the tree in read_data_from_file function\n");
    	return NULL;
    }
    
    if(!(in = (FILE*) fopen(filename, "r"))){
    	printf("ERROR: unable to open the file in read_data_from_file function\n");
    	tree_destroy(t);
    	return NULL;
    }
    
    while(!feof(in)){
        fscanf(in,"%d",&aux);
        if(tree_insert(t, &aux)==ERROR){
        	printf("ERROR: unable to insert an element into the tree in read_data_from_file function\n");
    		tree_destroy(t);
        	fclose(in);
        	return NULL;
        }
    }
    fclose(in);
    return t;
}


int main(int argc, char** argv){
    Tree *t=NULL;
    List *l1=NULL, *l2=NULL, *l3=NULL;
    destroy_elementtree_function_type f1 = destroy_intp_function;
    copy_elementtree_function_type f2 = copy_intp_function;
    print_elementtree_function_type f3 = print_intp_function;
    cmp_elementtree_function_type f4 = cmp_intp_function;
    int num, nNodes, depth;
        
    if (argc < 2){
    	printf("ERROR: Insufficient input parameters: %d\n", argc);
    	printf("Please, introduce filename with numbers\n");
		exit(EXIT_FAILURE);
    }
    
    if(!(t = read_data_from_file(argv[1]))){
    	printf("ERROR: unable to initialize and fill up the tree [main]\n");
    	exit(EXIT_FAILURE);
    }
    
    if(!(l1 = list_ini(f1, f2, f3, f4))){
    	printf("ERROR: unable to initialize preOrder list [main]\n");
    	tree_destroy(t);
    	exit(EXIT_FAILURE);
    }
    
    if(!(l2= list_ini(f1, f2, f3, f4))){
    	printf("ERROR: unable to initialize midOrder list [main]\n");
    	tree_destroy(t);
    	list_destroy(l1);
    	exit(EXIT_FAILURE);
    }
    
    if(!(l3= list_ini(f1, f2, f3, f4))){
    	printf("ERROR: unable to initialize postOrder list [main]\n");
    	tree_destroy(t);
    	list_destroy(l1);
    	list_destroy(l2);
    	exit(EXIT_FAILURE);
    }
    
    nNodes = tree_numNodes(t);
	if(nNodes == -1){
		printf("ERROR: unable to get the number of nodes [main]\n");
		tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
		exit(EXIT_FAILURE);
	}
	printf("Number of nodes inserted = %d\n", nNodes);
    
    if(tree_isEmpty(t) == TRUE){
		printf("Depth: the tree is empty\n");
	}
	else{
		depth = tree_depth(t);
		if(depth == -2){
			printf("ERROR: unable to get the BST depth [main]\n");
			tree_destroy(t);
			list_destroy(l1);
    		list_destroy(l2);
    		list_destroy(l3);
			exit(EXIT_FAILURE);
		}
		printf("Depth = %d\n", depth);
	}
    
    printf("\tOutput with tree_XOrder functions\n");
    printf("Previous Order: ");
    if(tree_preOrder(stdout, t) == ERROR){
    	printf("ERROR: unable to print the Binary Search Tree in previous order [main]\n");
    	tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
    	exit(EXIT_FAILURE);
    }
    printf("\nMid Order: ");
    if(tree_midOrder(stdout, t) == ERROR){
    	printf("ERROR: unable to print the Binary Search Tree in mid order [main]\n");
    	tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
    	exit(EXIT_FAILURE);
    }
    printf("\nPosterior Order: ");
    if(tree_postOrder(stdout, t) == ERROR){
    	printf("ERROR: unable to print the Binary Search Tree in posterior order [main]\n");
    	tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
    	exit(EXIT_FAILURE);
    }

    printf("\n\tOutput with tree_XOrderToList functions\n");
    if(tree_preOrderToList(l1, t) == ERROR){
    	printf("ERROR: unable to get the list in previous order [main]\n");
    	tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
    	exit(EXIT_FAILURE);
    }
    printf("Previous Order: ");
    if(list_print(stdout, l1) == -1){
    	printf("ERROR: unable to print the list in previous order [main]\n");
    	tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
    	exit(EXIT_FAILURE);
    }
    if(tree_midOrderToList(l2, t) == ERROR){
    	printf("ERROR: unable to get the list in mid order [main]\n");
    	tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
    	exit(EXIT_FAILURE);
    }
    printf("\nMid Order: ");
    if(list_print(stdout, l2) == -1){
    	printf("ERROR: unable to print the list in mid order [main]\n");
    	tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
    	exit(EXIT_FAILURE);
    }
    if(tree_postOrderToList(l3, t) == ERROR){
    	printf("ERROR: unable to get the list in posterior order [main]\n");
    	tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
    	exit(EXIT_FAILURE);
    }
    printf("\nPosterior Order: ");
    if(list_print(stdout, l3) == -1){
    	printf("ERROR: unable to print the list in posterior order [main]\n");
    	tree_destroy(t);
		list_destroy(l1);
    	list_destroy(l2);
    	list_destroy(l3);
    	exit(EXIT_FAILURE);
    }
    printf("\n");
    
    printf("-> Please, introduce a number: ");
    scanf("%d", &num);
    printf("You have introduced: %d\n", num);
    
    if(tree_find(t, &num) == TRUE){
        printf("The number %d is in the tree.\n", num);
    }
    else if(tree_find(t, &num) == FALSE){
        printf("The number %d is NOT in the tree\n", num);
    }
    
    tree_destroy(t);
    list_destroy(l1);
    list_destroy(l2);
    list_destroy(l3);
    exit(EXIT_SUCCESS);
}