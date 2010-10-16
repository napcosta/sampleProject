#include<stdio.h>
#include<stdlib.h>

#define RED 1
#define BLUE 0

struct tree_node {
	int node_color;
	struct tree *leftChild;
	struct tree *rightChild;
};


