#include"rbt.h"


struct root_pointer *tree_init()
{
	struct root_pointer *root = malloc(sizeof(struct tree_node));
	root->root = NULL;
	return root;
}

void insert_node(struct root_pointer root, int vruntime, struct  root_pointer *rootptr) 
{	
	struct tree_node *current_node = rootptr->root;

	if (rootptr->root == NULL) {
		struct tree_node *tnode = node_init(NULL, vruntime);
		tnode->color = RED;
		rootptr->root = tnode;
	} else {
		insert_node_aux(root, vruntime, rootptr->root);
	}
}

void insert_node_aux(root, int vruntime, struct tree_node *current_node)
{
	if ((current_node->right_child == NULL) && (vruntime > current_node->vruntime)) {
		struct tree_node *tnode = node_init(current_node, vruntime);
		current_node->right_child = tnode;
		return;
	} else if (current_node->left_child == NULL && vruntime < current_node->vruntime) {
		struct tree_node *tnode = node_init(current_node, vruntime);
		current_node->left_child = tnode;
		return;
	} else if (current_node->right_child != NULL && vruntime > current_node->vruntime) {
		insert_node_aux(vruntime, current_node->right_child);
	} else if (current_node->left_child != NULL && vruntime < current_node->vruntime) {
		insert_node_aux(vruntime, current_node->left_child);
	}
}

void fix_color(root, struct tree_node *tnode)
{	
	struct tree_node *parent = tnode->parent_node;

	if (parent->parent_node == NULL)
		return;
	else if (parent->color != RED)
		return;
	else if (parents_sibling_color(tnode) != RED)
		rotate(root, tnode);
		tnode->color = BLACK;
		parent.left		
}


int parents_sibling_color(struct tree_node *tnode)
{
	struct tree_node *grandparent = tnode->parent_node->parent_node;

	if (grandparent->right_child != tnode->parent_node)
		return grandparent->right_child->color;
	else return grandparent->left_child->color;
}

void rotate(struct root_pointer, struct tree_node *tnode)
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
		left_left_rotate(tnode);
	else if (parent_right && node_right)
		righ_right_rotate(tnode);
	else if (parent_left && node_right)
		left_right_rotate(tnode);
	else if (parent_right && node_left)
		right_left_rotate(tnode);
	else 
		printf("ERROR IN ROTATE");

}

struct tree_node *node_init(struct tree_node *parent_node, int vruntime)
{
	struct tree_node *node = malloc(sizeof(struct tree_node));
	node->color = RED;
	node->vruntime = vruntime;
	node->left_child = NULL;
	node->right_child = NULL;
	node->parent_node = parent_node;
	return node;
}

int main() 
{	
	struct root_pointer *new = tree_init();
	insert_node(1,new);
	insert_node(2,new);
	insert_node(3, new);

	return 0;
}

