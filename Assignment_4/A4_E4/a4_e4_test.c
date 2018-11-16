/**
*  Project: Assignment 4 - ProgII subject
*  File: a4_e3_test.c
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
#include "functions.h"

#define MAX_STRING_SIZE 512

Tree* read_data_from_file(char *filename){
    FILE *in=NULL;
    Tree *t=NULL;
    destroy_elementtree_function_type f1 = destroy_str_function;
    copy_elementtree_function_type f2 = copy_str_function;
    print_elementtree_function_type f3 = print_str_function;
    cmp_elementtree_function_type f4 = cmp_str_function;
    char buffer[MAX_STRING_SIZE], string[MAX_STRING_SIZE];

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
        fgets(buffer, MAX_STRING_SIZE, in);
        sscanf(buffer, "%s", string);
        if(tree_insert(t, string) == ERROR){
            printf("ERROR: unable to insert the string '%s' in the BS Tree in read_data_from_file function\n", string);
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
    int nNodes, depth;
    char string[MAX_STRING_SIZE];

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

    printf("Please, introduce a character string: ");
    scanf("%[^\n]s", string);
    printf("Introduced string = '%s'\n", string);

    if(tree_find(t, string) == TRUE){
        printf("The given string '%s' is in the Binary Search Tree\n", string);
    }
    else{
        printf("The given string '%s' is NOT in the Binary Search Tree\n", string);
    }
    tree_destroy(t);
    exit(EXIT_SUCCESS);
}