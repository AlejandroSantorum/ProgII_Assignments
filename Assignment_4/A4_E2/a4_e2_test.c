/**
*  Project: Assignment 4 - ProgII subject
*  File: a4_e2_test.c
*  Version: 2.0
*  Date: May 2, 2017
*  Revision date: Jun 2, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "node.h"
#include "functions.h"

#define MAX 256

Tree* read_data_from_file(char *filename){
	FILE *in=NULL;
	Tree *t=NULL;
	destroy_elementtree_function_type f1 = destroy_node_function;
	copy_elementtree_function_type f2 = copy_node_function;
	print_elementtree_function_type f3 = print_node_function;
	cmp_elementtree_function_type f4 = cmp_node_function;
	int nNodes, i, id;
	char buffer[MAX], name[MAX];
	Node *node=NULL;

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

	fgets(buffer, MAX, in);
	sscanf(buffer, "%d", &nNodes); /* Reading number of nodes in the file */
	for(i=0; i<nNodes; i++){
		fgets(buffer, MAX, in);
		sscanf(buffer, "%d %s", &id, name);
		if(!(node = node_ini())){ /* Initializing node */
			printf("ERROR: unable to initialize a node (ID = %d) in read_data_from_file function\n", id);
			tree_destroy(t);
			fclose(in);
			return NULL;
		}
		if(!node_setId(node, id)){ /* Setting ID */
			printf("ERROR: unable to set node ID in read_data_from_file function\n");
			node_destroy(node);
			tree_destroy(t);
			fclose(in);
			return NULL;
		}
		if(!node_setName(node, name)){ /* Setting name */
			printf("ERROR: unable to set node name in read_data_from_file function\n");
			node_destroy(node);
			tree_destroy(t);
			fclose(in);
			return NULL;
		}
		if(!tree_insert(t, node)){ /* Inserting into the BS Tree */
			printf("ERROR: unable to insert node into the Binary Search Tree in read_data_from_file function\n");
			node_destroy(node);
			tree_destroy(t);
			fclose(in);
			return NULL;
		}
		node_destroy(node); /* Freeing node memory */
	}
	fclose(in);
	return t;
}


int main(int argc, char **argv){
	Tree *t=NULL;
	int nNodes, depth, id;
	char buff[MAX], name[MAX];
	Node *node=NULL;

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

	printf("Please, introduce a node with the following format: <id> <name>\n");
	fgets(buff, MAX, stdin);
	sscanf(buff, "%d %s", &id, name);
	printf("Introduced number = %d\n", id);
	printf("Introduced name = %s\n", name);

	if(!(node = node_ini())){
		printf("ERROR: unable to initialize a node [main]\n");
		tree_destroy(t);
		exit(EXIT_FAILURE);
	}
	if(!node_setId(node, id)){
		printf("ERROR: unable to set node ID [main]\n");
		tree_destroy(t);
		exit(EXIT_FAILURE);
	}
	if(!node_setName(node, name)){
		printf("ERROR: unable to set node name [main]\n");
		tree_destroy(t);
		exit(EXIT_FAILURE);
	}

	if(tree_find(t, node) == TRUE){
		printf("The given node is in the Binary Search Tree\n");
	}
	else{
		printf("The given node is NOT in the Binary Search Tree\n");
	}
	tree_destroy(t);
	exit(EXIT_SUCCESS);
}