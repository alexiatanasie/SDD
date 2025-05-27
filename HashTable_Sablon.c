#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

#define HASH_TABLE_SIZE 50

typedef struct Evaluare {
	char* nume;
	char* examen;
	int semestru;
	float nota;
	char* profesor;
	char* dataExamen;
}Evaluare;

typedef struct Node {
	Evaluare* evaluare;
	struct Node* next;
}Node;

//hash function
unsigned int hash_function(char* key, unsigned int size) {
	unsigned int sum = 0;
	for (int i = 0; i < strlen(key); i++) {
		sum += key[i];
	}		
	return sum % size;

}

Node* insertNode(Node* list, Evaluare* e) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->evaluare = e;
	newNode->next = list;
	return newNode;
}

void insertInHashTable(Node** table, unsigned int size, Evaluare* e) {
	unsigned int index = hash_function(e->examen, size);
	table[index] = insertNode(table[index], e);
}
void parse(Node* list) {
	Node* temp = list;
	while (temp != NULL) {
		printf("%s %s %d %.2f %s %s\n", temp->evaluare->nume, temp->evaluare->examen, temp->evaluare->semestru, temp->evaluare->nota, temp->evaluare->profesor, temp->evaluare->dataExamen);
		temp = temp->next;
	}
}
Evaluare* searchByExam(Node** table, unsigned int size, char* examen) {
	unsigned int index = hash_function(examen, size);
	Node* temp = table[index];

	while (temp) {
		if (strcmp(temp->evaluare->examen, examen) == 0) {
			return temp->evaluare;
		}
		temp = temp->next;
	}
	return NULL;
}
void deallocateHTable(Node** table, unsigned int size) {
	for (int i = 0; i < size; i++) {
		Node* temp = table[i];
		while (temp) {
			Node* aux = temp;
			temp = temp->next;

			free(aux->evaluare->nume);
			free(aux->evaluare->examen);
			free(aux->evaluare->profesor);
			free(aux->evaluare->dataExamen);
			free(aux->evaluare);
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
	FILE* f = fopen("evaluare.txt", "r");

	while (fgets(buffer, sizeof(buffer), f)) {

		Evaluare ev;

		// nume
		buffer[strlen(buffer)-1] = '\0';
		ev.nume = (char*)malloc(strlen(buffer) + 1);
		strcpy(ev.nume, buffer);

		// examen
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer)-1] = '\0';
		ev.examen = (char*)malloc(strlen(buffer) + 1);
		strcpy(ev.examen, buffer);

		// semestru
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		ev.semestru = atoi(buffer);

		// nota
		fgets(buffer, sizeof(buffer), f);	
		buffer[strlen(buffer) - 1] = '\0';
		ev.nota =(float)atof(buffer);

		// profesor
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer)-1] = '\0';
		ev.profesor = (char*)malloc(strlen(buffer) + 1);
		strcpy(ev.profesor, buffer);

		// data examen
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer)-1] = '\0';
		ev.dataExamen = (char*)malloc(strlen(buffer) + 1);
		strcpy(ev.dataExamen, buffer);


		Evaluare* evaluare = (Evaluare*)malloc(sizeof(Evaluare));
		*evaluare = ev; // deep copy a structurii
		insertInHashTable(htable, HASH_TABLE_SIZE, evaluare);
	}

	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		parse(htable[i]);
	}


	char examenCautat[] = "Programare ";
	Evaluare* rezultat = searchByExam(htable, HASH_TABLE_SIZE, examenCautat);
	if (rezultat) {
		printf("\n Rezultat gasit: %s %s %d %.2f %s %s\n",
			rezultat->nume, rezultat->examen, rezultat->semestru, rezultat->nota, rezultat->profesor, rezultat->dataExamen);
	}
	else {
		printf("nu s-a gasit examenul %s",examenCautat);
	}
	deallocateHTable(htable, HASH_TABLE_SIZE);
	fclose(f);
	return 0;
}
