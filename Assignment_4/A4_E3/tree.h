/**
*  Project: Assignment 4 - ProgII subject
*  File: tree.h
*  Version: 2.0
*  Date: May 1, 2017
*  Revision date: Jun 2, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "types.h"

typedef struct _Tree Tree;


/** Function pointer types supported by the tree of integers */
typedef void (*destroy_elementtree_function_type)(void*);
typedef void *(*copy_elementtree_function_type)(void*);
typedef int (*print_elementtree_function_type)(FILE*, void*);
typedef int (*cmp_elementtree_function_type)(void*, void*);


/**
*	It initializes a tree, allocating memory for it and its components,
*	returning the created tree, or NULL otherwise
*/
Tree* tree_ini(destroy_elementtree_function_type f1, copy_elementtree_function_type f2, print_elementtree_function_type f3, cmp_elementtree_function_type f4);

/**
*	It frees all the allocated memory for the given tree
*/
void tree_destroy(Tree *t);

/**
*	It inserts in the given tree a COPY of the given information (pointer po),
*	returning ERROR if the element was already in the tree. OK is returned on success
*/
Status tree_insert(Tree *t, void *po);

/**
*	It compares the given node with the nodes of the tree, returning TRUE if
*	the node can be found in the tree, or FALSE otherwise
*/
Bool tree_find(Tree *t, void *po);

/**
*	It checks if the given tree is empty, returning TRUE in affirmative case,
*	or FALSE otherwise
*/
Bool tree_isEmpty(Tree *t);

/**
*	It returns the depth of the given tree. If the tree is empty it returns -1,
*	and it returns -2 in error case
*/
int tree_depth(Tree *t);

/**
*	It returns the number of nodes of the given tree. If the tree is empty it returns 0,
*	and it returns -1 in error case
*/
int tree_numNodes(Tree *t);

/**
*	It writes in the given file the path followed when walking
*	through the tree as a expression tree in previous order, it
*	means first is printed the current node, then the left node
*	and eventually the right node.
*	It returns OK on success, ERROR otherwise.
*/
Status  tree_preOrder(FILE *f, Tree *t);

/**
*	It writes in the given file the path followed when walking
*	through the tree as a expression tree in mid order, it
*	means first is printed the left node, then the current node
*	and eventually the right node.
*	It returns OK on success, ERROR otherwise.
*/
Status  tree_midOrder(FILE *f, Tree *t);

/**
*	It writes in the given file the path followed when walking
*	through the tree as a expression tree in post order, it
*	means first is printed the left node, then the right node
*	and eventually the current node.
*	It returns OK on success, ERROR otherwise.
*/
Status  tree_postOrder(FILE *f, Tree *t);

/**
*	It inserts in the given list the path followed when walking
*	through the tree as a expression tree in previous order, it
*	means first is printed the current node, then the left node
*	and eventually the right node.
*	It returns OK on success, ERROR otherwise.
*/
Status tree_preOrderToList(List *l, Tree *t);

/**
*	It inserts in the given list the path followed when walking
*	through the tree as a expression tree in mid order, it
*	means first is printed the left node, then the current node
*	and eventually the right node.
*	It returns OK on success, ERROR otherwise.
*/
Status  tree_midOrderToList(List *l, Tree *t);

/**
*	It inserts in the given list the path followed when walking
*	through the tree as a expression tree in post order, it
*	means first is printed the left node, then the right node
*	and eventually the current node.
*	It returns OK on success, ERROR otherwise.
*/
Status  tree_postOrderToList(List *l, Tree *t);

#endif /* TREE_H */