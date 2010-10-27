#include"rbt.h"


struct root_pointer *tree_init()
{
	struct root_pointer *rootptr = malloc(sizeof(struct root_pointer));
	struct tree_node *nill = malloc(sizeof(struct tree_node));
	nill->right_child = NULL;
	nill->left_child = NULL;
	nill->color = BLACK;
	nill->parent_node = NULL;
	nill->vruntime = 0;
	rootptr->root = NULL;
	rootptr->nill_node = nill; 
	return rootptr;
}

void insert_node(struct root_pointer *rootptr, int vruntime) 
{	
	struct tree_node *current_node = rootptr->root;

	if (rootptr->root == NULL) {
		struct tree_node *tnode = node_init(rootptr, NULL, vruntime);
		tnode->color = BLACK;
		rootptr->root = tnode;
		return;
	} else {
		current_node = insert_node_aux(rootptr, vruntime, rootptr->root);
		fix(rootptr, current_node);
	}
}

struct tree_node *insert_node_aux(struct root_pointer *rootptr, int vruntime, struct tree_node *current_node)
{
	if (current_node->right_child == rootptr->nill_node && vruntime > current_node->vruntime) {
		struct tree_node *tnode = node_init(rootptr, current_node, vruntime);
		current_node->right_child = tnode;
		return tnode;
	} else if (current_node->left_child == rootptr->nill_node && vruntime < current_node->vruntime) {
		struct tree_node *tnode = node_init(rootptr, current_node, vruntime);
		current_node->left_child = tnode;
		return tnode;
	} else if (current_node->right_child != rootptr->nill_node && vruntime > current_node->vruntime) {
		insert_node_aux(rootptr, vruntime, current_node->right_child);
	} else if (current_node->left_child != rootptr->nill_node && vruntime < current_node->vruntime) {
		insert_node_aux(rootptr, vruntime, current_node->left_child);
	}
}

void fix(struct root_pointer *rootptr, struct tree_node *tnode)
{	
	struct tree_node *parent = tnode->parent_node;

	if (parent == NULL || parent->parent_node == NULL) {
		return;
	} else if (parent->color != RED) {
		return;
	} else if (sibling_color(rootptr, parent) != RED) {
		rotate(rootptr, tnode);
	}
	else {
		parent->color = BLACK;
		sibling(rootptr, parent)->color = BLACK;
		if (parent->parent_node == rootptr->root)
			return;
		parent->parent_node->color = RED;
		fix(rootptr, parent->parent_node);
	}
}

struct tree_node *sibling(struct root_pointer *rootptr, struct tree_node *tnode)
{
	struct tree_node *parent = tnode->parent_node;

	if (parent == NULL)
		return rootptr->nill_node;
	if (parent->left_child == tnode)
		return parent->right_child;
	else 
		return parent->left_child;
}

int sibling_color(struct root_pointer *rootptr, struct tree_node *tnode)
{
	if (tnode == rootptr->nill_node)
		return BLACK;

	else if (sibling(rootptr,tnode) == rootptr->nill_node)
		return BLACK;
	else
		return sibling(rootptr,tnode)->color;
}

void rotate(struct root_pointer *root_pointer, struct tree_node *tnode)
{
	int node_left, node_right;
	int parent_left, parent_right;

	node_right = node_left = parent_left = parent_right = FALSE;

	struct tree_node *parent = tnode->parent_node;

	if (parent->left_child == tnode) {
		node_left = TRUE;
	} else {
		node_right = TRUE;
	}
	if (parent->parent_node->left_child == parent) {
		parent_left = TRUE;
	} else {
		parent_right = TRUE;
	}

	if (parent_left && node_left)
		left_left_rotate(root_pointer, tnode);
	else if (parent_right && node_right)
		right_right_rotate(root_pointer, tnode);
	else if (parent_left && node_right)
		left_right_rotate(root_pointer, tnode);
	else if (parent_right && node_left)
		right_left_rotate(root_pointer, tnode);
	else 
		printf("ERROR IN ROTATE");
}

void left_right_rotate(struct root_pointer *rootptr, struct tree_node *tnode)
{
	struct tree_node *grandparent = tnode->parent_node->parent_node;
	struct tree_node *parent = tnode->parent_node;
	
	tnode->parent_node = grandparent->parent_node;

	if (grandparent == rootptr->root) {
		rootptr->root = tnode;
		grandparent->parent_node = tnode;
	} else {
		if (grandparent->parent_node->right_child == grandparent)
			grandparent->parent_node->right_child = tnode;
		else 
			grandparent->parent_node->left_child = tnode;

		grandparent->parent_node = tnode;
	}
	parent->parent_node = tnode;
	parent->right_child = tnode->left_child;
	tnode->left_child = parent;
	grandparent->left_child = tnode->right_child;
	tnode->right_child = grandparent;

	if (grandparent->left_child != rootptr->nill_node)
		grandparent->left_child->parent_node = grandparent;
	if (parent->right_child != rootptr->nill_node)
		parent->right_child->parent_node = parent;
	tnode->color = BLACK;
	tnode->left_child->color = RED;
	tnode->right_child->color = RED;	
}

void right_left_rotate(struct root_pointer *rootptr, struct tree_node *tnode)
{
	struct tree_node *grandparent = tnode->parent_node->parent_node;
	struct tree_node *parent = tnode->parent_node;

	tnode->parent_node = grandparent->parent_node;

	if (grandparent==rootptr->root) {
		rootptr->root = tnode;
		grandparent->parent_node = tnode;
	} else {
		if (grandparent->parent_node->left_child == grandparent)
			grandparent->parent_node->left_child = tnode;
		else
			grandparent->parent_node->right_child = tnode;

		grandparent->parent_node = tnode;
	}
	

	parent->parent_node = tnode;
	parent->left_child = tnode->right_child;
	tnode->right_child = parent;
	grandparent->right_child = tnode->left_child;
	tnode->left_child = grandparent;

	if (grandparent->right_child != rootptr->nill_node)
		grandparent->right_child->parent_node = grandparent;
	if (parent->left_child != rootptr->nill_node)
		parent->left_child->parent_node = parent;

	tnode->color = BLACK;
	tnode->right_child->color = RED;
	tnode->left_child->color = RED;
}

void left_left_rotate(struct root_pointer *rootptr, struct tree_node *tnode)
{
	struct tree_node *grandparent = tnode->parent_node->parent_node;
	
	if (grandparent == rootptr->root) {
		rootptr->root = grandparent->left_child;
		grandparent->left_child->parent_node = NULL;
	} else { 
		if (grandparent->parent_node->right_child == grandparent)
			grandparent->parent_node->right_child = tnode->parent_node;
		else 
			grandparent->parent_node->left_child = tnode->parent_node;
		
	}
	tnode->parent_node->parent_node = grandparent->parent_node;
	grandparent->parent_node = grandparent->left_child;
	grandparent->left_child = tnode->parent_node->right_child;
	grandparent->left_child->right_child = grandparent;
	tnode->parent_node->right_child = grandparent;
	grandparent->parent_node = tnode->parent_node;


	tnode->parent_node->color = BLACK;
	tnode->parent_node->left_child->color = RED;
	tnode->parent_node->right_child->color = RED;
}


void right_right_rotate(struct root_pointer *rootptr, struct tree_node *tnode)
{
	struct tree_node *grandparent = tnode->parent_node->parent_node;

	if (grandparent  == rootptr->root) {
		rootptr->root = grandparent->right_child;
		grandparent->right_child->parent_node = NULL;
	}
	else {
		if (grandparent->parent_node->left_child == grandparent)
			grandparent->parent_node->left_child = tnode->parent_node;
		else
			grandparent->parent_node->right_child = tnode->parent_node;
	}
	tnode->parent_node->parent_node = grandparent->parent_node;
	grandparent->parent_node = grandparent->right_child;
	grandparent->right_child = tnode->parent_node->left_child;
	grandparent->right_child->left_child = grandparent;
	tnode->parent_node->left_child = grandparent;


	tnode->parent_node->color = BLACK;
	tnode->parent_node->left_child->color = RED;
	tnode->parent_node->right_child->color = RED;

}

struct tree_node *node_init(struct root_pointer *rootptr, struct tree_node *parent_node, int vruntime)
{
	struct tree_node *node = malloc(sizeof(struct tree_node));
	node->color = RED;
	node->vruntime = vruntime;
	node->left_child = rootptr->nill_node;
	node->right_child = rootptr->nill_node;
	node->parent_node = parent_node;
	return node;
}


void print_tree(struct root_pointer *rootptr, struct tree_node *node)
{
	if (node == rootptr->nill_node)
		return;
	printf("color->%d vruntime->%d", node->color, node->vruntime);
	if (node->parent_node != NULL)
		printf(" parent->%d ", node->parent_node->vruntime);
	printf("\n ---------------- \n");
	print_tree(rootptr, node->left_child);
	print_tree(rootptr, node->right_child);

}

int main() 
{	
	struct root_pointer *new = tree_init();
	insert_node(new,15);
	insert_node(new,3);
	insert_node(new,5);
	insert_node(new,20);
	insert_node(new,8);
	insert_node(new,7);
	insert_node(new,6);
	insert_node(new,17);
	insert_node(new,10);
	insert_node(new,11);
	insert_node(new,18);
	insert_node(new,13);
	insert_node(new, 2);
	insert_node(new, 12);
	insert_node(new, 40);
	insert_node(new, 41);
	insert_node(new, 60);
/*
	insert_node(new, 3);
	insert_node(new, 2);
	insert_node(new, 1);
*/	print_tree(new, new->root);

	return 0;
}
