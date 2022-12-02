#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
}Node;

Node* Tree = NULL;

Node* AddTree(Node* Tree, int data) {

	if (Tree == NULL) {
		Tree = (Node*)malloc(sizeof(Node));
		Tree->left = NULL;
		Tree->right = NULL;
		Tree->data = data;
		return Tree;
	}
	else {
		if (Tree->data > data) {
			Tree->left = AddTree(Tree->left, data);
		}
		else {
			Tree->right = AddTree(Tree->right, data);
		}
	}
	return Tree;
}

void PrintTree(Node* node) {
	printf("T %d ", node->data);

	if (node->left != NULL) {
		printf("%d ", node->left->data);
		
	}
	if (node->right != NULL) {
		printf("%d ", node->right->data);
	}
	if (node->left != NULL) {
		if (node->left->left != NULL) {
			PrintTree(node->left->left);
		}
		if (node->left->right != NULL) {
			PrintTree(node -> left->right);
		}
	}
	if (node->right != NULL) {
		if (node->right->left != NULL) {
			PrintTree(node->right->left);
		}
		if (node->right->right != NULL) {
			PrintTree(node->right->right);
		}
	}
}


int main(void) {
	int arr[10];

	printf("Input 10 different numbers: ");
	for (int i = 0; i < 10; i++) {
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < 10; i++) {
		Tree=AddTree(Tree, arr[i]);
	}

	PrintTree(Tree);

	return 0;
}