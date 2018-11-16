/**
*  Project: Assignment 4 - ProgII subject
*  File: a4_e1_test.c
*  Version: 2.0
*  Date: May 1, 2017
*  Revision date: Jun 1, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "functions.h"

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

	t = tree_ini(f1,f2,f3,f4);
	if(!t){
		printf("ERROR: unable to initialize the Binary Search Tree in read_data_from_file function\n");
		return NULL;
	}

	in = (FILE*) fopen(filename, "r");
	if(!in){
		printf("ERROR: unable to open the given file in read_data_from_file function\n");
		tree_destroy(t);
		return NULL;
	}

	while(!feof(in)){
		fscanf(in, "%d", &aux);
		if(tree_insert(t, &aux) == ERROR){
			printf("ERROR: unable to insert the integer %d in the BS Tree in read_data_from_file function\n", aux);
			tree_destroy(t);
			fclose(in);
			return NULL;
		}
	}
	fclose(in);
	return t;
}


int main(int argc, char **argv){
	Tree *t=NULL;
	int nNodes, depth, num;

	if(argc < 2){
		printf("ERROR: insufficient parameters --> %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	t = read_data_from_file(argv[1]);
	if(!t){
		printf("ERROR: unable to create the Binary Search Tree [main]\n");
		exit(EXIT_FAILURE);
	}

	nNodes = tree_numNodes(t);
	if(nNodes == -1){
		printf("ERROR: unable to get the number of nodes [main]\n");
		tree_destroy(t);
		exit(EXIT_FAILURE);
	}
	printf("Number of nodes = %d\n", nNodes);

	if(tree_isEmpty(t) == TRUE){
		printf("Depth: the tree is empty\n");
	}
	else{
		depth = tree_depth(t);
		if(depth == -2){
			printf("ERROR: unable to get the BST depth [main]\n");
			tree_destroy(t);
			exit(EXIT_FAILURE);
		}
		printf("Depth = %d\n", depth);
	}

	printf("Please, introduce a number: ");
	scanf("%d", &num);
	printf("Introduced number = %d\n", num);

	if(tree_find(t, &num) == TRUE){
		printf("The given number %d is in the Binary Search Tree\n", num);
	}
	else{
		printf("The given number %d is NOT in the Binary Search Tree\n", num);
	}
	tree_destroy(t);
	exit(EXIT_SUCCESS);
}