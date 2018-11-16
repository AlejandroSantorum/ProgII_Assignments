/**
*  Project: Assignment 4 - ProgII subject
*  File: tree.c
*  Version: 2.0
*  Date: May 1, 2017
*  Revision date: Jun 1, 2018
*
*  (C) Alejandro Santorum Varela
*  alejandro.santorum@gmail.com
*
*/
#include "tree.h"

/**
*	Private struct that defines the node of our Binary Search Tree
*/
typedef struct _NodeBST{
	void *info; 					/* Information in the node */
	struct _NodeBST *left;			/* Left subtree */
	struct _NodeBST *right;			/* Right subtree */
} NodeBST;


/**
*	Definition of the Binary Search Tree
*/
struct _Tree{
	/* Root node of the BST */
	NodeBST *root;
	destroy_elementtree_function_type destroy_element_function;
	copy_elementtree_function_type copy_element_function;
    print_elementtree_function_type print_element_function;
    cmp_elementtree_function_type cmp_element_function;
};


/**
*	Private function: It initializes a BST node
*	Returns the initialized node or NULL in error case
*/
NodeBST* nodeBST_ini(){
	NodeBST *node=NULL;

	node = (NodeBST*) malloc(sizeof(NodeBST));
	if(!node){
		return NULL;
	}

	node->info = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}


/**
*	Private function: It frees all the memory allocated for a BST node
*/
void nodeBST_destroy(NodeBST *node, Tree *t){
	if(!node || !t){
		return;
	}

	if(node->info){
		t->destroy_element_function(node->info);
	}
	free(node);
	return;
}

/**
*	It initializes a tree, allocating memory for it and its components,
*	returning the created tree, or NULL otherwise
*/
Tree* tree_ini(destroy_elementtree_function_type f1, copy_elementtree_function_type f2, print_elementtree_function_type f3, cmp_elementtree_function_type f4){
	Tree *t=NULL;

	t = (Tree*) malloc(sizeof(Tree));
	if(!t){
		printf("BSTree Error: unable to allocate memory for a new Binary Search Tree\n");
		return NULL;
	}

	t->destroy_element_function = f1;
	t->copy_element_function = f2;
	t->print_element_function = f3;
	t->cmp_element_function = f4;
	t->root = NULL;
	return t;
}

/**
*	Private function: it frees all the nodes of a given tree recursively
*/
void tree_destroy_rec(NodeBST *node, Tree *t){
	if(!node){ /* Base case */
		return;
	}
	tree_destroy_rec(node->left, t);
	tree_destroy_rec(node->right, t);
	nodeBST_destroy(node, t);
	return;
}
/**
*	It frees all the allocated memory for the given tree
*/
void tree_destroy(Tree *t){
	if(!t){
		printf("BSTree Warning: trying to free a NULL Binary Search Tree\n");
		return;
	}

	if(!(t->root)){ /* The tree is empty */
		free(t);
		return;
	}

	tree_destroy_rec(t->root, t);
	free(t);
	return;
}

/**
*	Private function: it inserts recursively the given element,
*	respecting Binary Search Tree properties
*/
Status tree_insert_rec(NodeBST **node, void *po, Tree *t){
	int cmp;

	if(!node){
		printf("BSTree Error: NULL pointer in tree_insert function\n");
		return ERROR;
	}

	if(!(*node)){
		*node = nodeBST_ini();
		if(!(*node)){
			printf("BSTree Error: unable to allcate memory for a new node in tree_insert function\n");
			return ERROR;
		}
		(*node)->info = t->copy_element_function(po);
		if(!((*node)->info)){
			printf("BSTree Error: unable to copy the information in the new node in tree_insert function\n");
			nodeBST_destroy(*node, t);
			*node = NULL;
			return ERROR;
		}
		return OK;
	}

	cmp = t->cmp_element_function(po, (*node)->info);
	if(cmp<0){
		return tree_insert_rec(&((*node)->left), po, t);
	}
	if(cmp>0){
		return tree_insert_rec(&((*node)->right), po, t);
	}
	if(!cmp){
		printf("The element: ");
		t->print_element_function(stdout, po);
		printf("is already inserted in the Binary Search Tree\n");
		return OK;
	}
	return OK;
}
/**
*	It inserts in the given tree a COPY of the given information (pointer po),
*	returning ERROR if the element was already in the tree. OK is returned on success
*/
Status tree_insert(Tree *t, void *po){
	if(!t){
		printf("BSTree Error: Binary Search Tree NULL pointer in tree_insert function\n");
		return ERROR;
	}
	if(!po){
		printf("BSTree Error: element NULL pointer in tree_insert function\n");
		return ERROR;
	}

	return tree_insert_rec(&(t->root), po, t);
}

/**
*	Private function: it searches recursively for a node with the
*	same information as the element given, returning TRUE if the node
*	has been found or FALSE otherwise
*/
Bool tree_find_rec(NodeBST *node, void *po, Tree *t){
	int cmp;

	if(!node){ /* Base case */
		return FALSE;
	}

	cmp = t->cmp_element_function(po, node->info);
	if(cmp<0){
		return tree_find_rec(node->left, po, t);
	}
	if(cmp>0){
		return tree_find_rec(node->right, po, t);
	}
	return TRUE; /* cmp == 0 */
}
/**
*	It compares the given node with the nodes of the tree, returning TRUE if
*	the node can be found in the tree, or FALSE otherwise
*/
Bool tree_find(Tree *t, void *po){
	if(!t){
		printf("BSTree Error: Binary Search Tree NULL pointer in tree_find function\n");
		return ERROR;
	}
	if(!po){
		printf("BSTree Error: element NULL pointer in tree_find function\n");
		return ERROR;
	}

	return tree_find_rec(t->root, po, t);
}

/**
*	It checks if the given tree is empty, returning TRUE in affirmative case,
*	or FALSE otherwise
*/
Bool tree_isEmpty(Tree *t){
	if(!t){
		printf("BSTree Error: Binary Search Tree NULL pointer in tree_isEmpty function\n");
		return ERROR;
	}

	if(!(t->root)){
		return TRUE;
	}
	return FALSE;
}

/**
*	Private function: it checks recursively the depth of the subtrees of a given tree
*/
int tree_depth_rec(NodeBST *node){
	int i, j;

	if(!node){ /* Base case */
		return 0;
	}

	i = tree_depth_rec(node->left);
	j = tree_depth_rec(node->right);
	if(i>=j){
		return i+1;
	}
	return j+1; /* Working as an else statement */
}
/**
*	It returns the depth of the given tree. If the tree is empty it returns -1,
*	and it returns -2 in error case
*/
int tree_depth(Tree *t){
	if(!t){
		printf("BSTree Error: Binary Search Tree NULL pointer in tree_depth function\n");
		return -2;
	}

	if(!(t->root)){
		return -1;
	}
	return tree_depth_rec(t->root)-1;
}

/**
*	Private function: it counts recursively the number of nodes of the subtrees of a given tree
*/
int tree_numNodes_rec(NodeBST *node){
	int i, j;

	if(!node){ /* Base case */
		return 0;
	}

	i = tree_numNodes_rec(node->left);
	j = tree_numNodes_rec(node->right);
	return i+j+1;
}
/**
*	It returns the number of nodes of the given tree. If the tree is empty it returns 0,
*	and it returns -1 in error case
*/
int tree_numNodes(Tree *t){
	if(!t){
		printf("BSTree Error: Binary Search Tree NULL pointer in tree_numNodes function\n");
		return -1;
	}

	if(!(t->root)){
		return 0;
	}
	return tree_numNodes_rec(t->root);
}

