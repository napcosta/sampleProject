#include<stdio.h>
#include<stdlib.h>


#define RED 1
#define BLACK 0

#define TRUE 1
#define FALSE 0

struct tree_node {
	
	int color;
	struct tree_node *left_child;
	struct tree_node *right_child;
	struct tree_node *parent_node;
	int vruntime;

};

struct root_pointer {
	
	struct tree_node *root;
	struct tree_node *nill_node;

};


struct tree_node *node_init(struct root_pointer *rootptr, struct tree_node *parent_node, int vruntime);

struct root_pointer *tree_init();

void insert_node(struct root_pointer *rootptr, int vruntime);

struct tree_node *insert_node_aux(struct root_pointer *rootptr, int vruntime, struct tree_node *current_node);

void fix(struct root_pointer *root, struct tree_node *tnode);

struct tree_node *sibling(struct root_pointer *rootptr, struct tree_node *tnode);

int sibling_color(struct root_pointer *rootptr, struct tree_node *tnode);

void right_right_rotate(struct root_pointer *rootptr, struct tree_node *tnode);

void left_left_rotate(struct root_pointer *rootptr, struct tree_node *tnode);

void left_right_rotate(struct root_pointer *rootptr, struct tree_node *tnode);

void right_left_rotate(struct root_pointer *rootptr, struct tree_node *tnode);

void rotate(struct root_pointer *rootptr, struct tree_node *tnode);
