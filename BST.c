#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


typedef struct Farmacie {
	unsigned short int cod;
	char* denumire;
	float m2;
	unsigned char nrAngajati;


}Farmacie;

typedef struct BST {
	Farmacie data;
	struct BST* left, * right;
}BST;

BST* insert_node(BST* root, Farmacie farmacie) {
	if (root == NULL) {
		BST* node = (BST*)malloc(sizeof(BST));
		node->data = farmacie;
		node->left = node->right = NULL;
		return node;
	}

	if (farmacie.cod < root->data.cod) {
		root->left = insert_node(root->left, farmacie);
	}
	else if (farmacie.cod > root->data.cod) {
		root->right= insert_node(root->right, farmacie);
	}
	return root;

}
void parse_inOrder(BST* node) {
	if (node != NULL) {
		parse_inOrder(node->left);
		printf("%d ", node->data.cod);
		parse_inOrder(node->right);
	}
}
void postOrder(BST* node) {
	if (node) {
		postOrder(node->left);
		postOrder(node->right);
		printf("%d %s %.2f %d\n", node->data.cod, node->data.denumire, node->data.m2, node->data.nrAngajati);
	}
}

BST* deallocate(BST* node) {
	if (node != NULL) {
		deallocate(node->left);
		deallocate(node->right);
		free(node->data.denumire);
		free(node);
		node = NULL;
	}
	return node;

}
int main() {

	BST* bst = NULL;
	unsigned char buffer[200];

	FILE* f = fopen("farmacii.txt", "r");
	while (fgets(buffer, sizeof(buffer), f)) {

		Farmacie farma;

		buffer[strlen(buffer) - 1] = '\0';
		farma.cod= (unsigned short int)atoi(buffer);


		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		farma.denumire = (char*)malloc(strlen(buffer) + 1);
		strcpy(farma.denumire, buffer);


		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		farma.m2 = (float)atof(buffer);
		
		
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		farma.nrAngajati = (unsigned char)atoi(buffer);



		bst = insert_node(bst, farma);

	}
	postOrder(bst);
	bst=deallocate(bst);

	fclose(f);
	return 0;

}
