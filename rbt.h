#include<stdio.h>
#include<stdlib.h>


#define RED 0
#define BLACK 1

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
};

struct tree_node *node_init(struct tree_node *parent_node, int vruntime);

struct root_pointer *tree_init();

void insert_node(int vruntime, struct root_pointer *rootptr);

void insert_node_aux(int vruntime, struct tree_node *current_node);

void fix_color(struct root_pointer *root, struct tree_node *tnode);

int parents_sibling_color(struct tree_node *tnode);


