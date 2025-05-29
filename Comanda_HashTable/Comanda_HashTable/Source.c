#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define HASH_TABLE_SIZE 50

typedef struct Comanda {
	unsigned int id;
	char* lansare;
	char* livrare;
	char* nume;
	float suma;

}Comanda;

typedef struct Node {
	Comanda* comanda;
	struct Node* next;
}Node;

unsigned int hash_function(char* key, unsigned int size) {
	unsigned int sum=0;
	for (int i = 0; i < strlen(key); i++) {
		sum += key[i];
	}
	return sum % size;
}

Node* insertNode(Node* list, Comanda* c) {
	Node* newNode = (Node*)mallloc(sizeof(Node));
	newNode->comanda = c;
	newNode->next = list;
	return newNode;

}

void insertInHashTable(Node** table, unsigned int size, Comanda* c) {
	unsigned int index = hash_function(c->nume, HASH_TABLE_SIZE);
	table[index] = insertNode(table[index], c);

}

void parse(Node* list) {
	Node* temp = list;
	while (temp != NULL) {
		printf("%d %s %s %s %.2f\n", temp->comanda->id, temp->comanda->lansare, temp->comanda->livrare, temp->comanda->nume, temp->comanda->suma);
		temp = temp->next;
	}
}

Comanda* searchByName(Node** table, unsigned int size, char* nume) {
	unsigned int index = hash_function(nume, size);
	Node* temp = table[index];
	while (temp) {
		if (strcmp(temp->comanda->nume, nume) == 0) {
			return temp->comanda;
		}
		temp = temp->next;
	}
	return NULL;

}
void deallocate(Node** table, unsigned int size) {
	for (int i = 0; i < size; i++) {
		Node* temp = table[i];
		while (temp) {
			Node* aux = temp;
			temp = temp->next;
			free(aux->comanda->lansare);
			free(aux->comanda->livrare);
			free(aux->comanda->nume);
			free(aux->comanda);
			free(aux);
		}
	}
	free(table);
}

int main() {

	Node** htable = NULL;
	htable = malloc(sizeof(Node*) * HASH_TABLE_SIZE);
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++) {
		htable[i] = NULL;

	}
	unsigned char buffer[200];
	FILE* f = fopen("comanda.txt", "r");

	while (fgets(buffer, sizeof(buffer), f)) {

		Comanda com;
		buffer[strlen(buffer) - 1] = '\0';
		com.id = (unsigned int)atoi(buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		com.lansare = (char*)malloc(strlen(buffer) + 1);
		strcpy(com.lansare, buffer);


		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		com.livrare = (char*)malloc(strlen(buffer) + 1);
		strcpy(com.livrare, buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		com.nume = (char*)malloc(strlen(buffer) + 1);
		strcpy(com.nume, buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		com.suma = (float)atof(buffer);

		Comanda* comanda = (Comanda*)malloc(sizeof(Comanda));
		*comanda = com;
		insertInHashTable(htable, HASH_TABLE_SIZE, comanda);
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		parse(htable[i]);
	}

	char numeClient[] = "Alice Popescu";
	Comanda* result = searchByName(htable, HASH_TABLE_SIZE, numeClient);
	if (result) {
		printf("NUME: %s", result->nume);
	}
	else {
		printf("NO: ", numeClient);
	}
	deallocate(htable, HASH_TABLE_SIZE);
	fclose(f);
	return 0;
}