#include <stdio.h>
#include <stdlib.h>

#include "RBT.h"

int main(){

	struct rbt *tree;

	tree = init_tree();

	insert_node(tree, 15);
	insert_node(tree, 17);
	insert_node(tree, 16);
	insert_node(tree, 20);
	insert_node(tree, 13);
	insert_node(tree, 10);
	insert_node(tree, 12);
	insert_node(tree, 6);
	insert_node(tree, 3);
	insert_node(tree, 4);
	insert_node(tree, 2);

	remove_node(tree, 13);

	printTree(tree);

	return 0;

}
