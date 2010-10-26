#include <stdio.h>
#include <stdlib.h>

struct node {

	int color;
	int num;
	int nil;
	struct node *parent;
	struct node *left;
	struct node *right;

};

struct rbt {

	struct node *root;
	struct node *first;
	struct node *nil;

};

struct rbt *init_tree();

void insert_node(struct rbt *tree, int num);

struct node *remove_node(struct rbt *tree, int num);

void printTree(struct rbt *tree);
