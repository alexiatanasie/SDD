//DOUBLE LIST SABLON OFFFF VTM MEAAA
//COACE DOAMNE PRUNELEEEEE
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct Project {
	unsigned int id;
	char* title;
	char* customer;
	unsigned char nrExecutants;
	float budget;
}Project;

typedef struct Node {
	Project data;
	struct Node* next, * prev;
}Node;

typedef struct DoubleList {
	struct Node* head, * tail;
}DoubleList;
void insertTail(DoubleList* list, Project project) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) {
		printf("Eroare.\n");
		return; 
	}
	newNode->data = project;
	newNode->next = NULL;
	newNode->prev = list->tail;

	if (list->tail)
		list->tail->next = newNode;
	else list->head = newNode;

	list->tail = newNode;
}

void printForward(DoubleList* list) {
	Node* current = list->head;
	while (current) {
		printf("%u, %s, %s, %u, %.2f\n", current->data.id, current->data.title, current->data.customer, current->data.nrExecutants, current->data.budget);
		current = current->next;
	}
}

void deallocate(DoubleList* list) {
	Node* current = list->head;
	while (current) {
		free(current->data.title);
		free(current->data.customer);

		Node* temp = current;
		current = current->next;
		free(temp);
	}
	list->head = NULL;
	list->tail = NULL;
}
int main() {
	DoubleList doubleList;
	doubleList.head = NULL;
	doubleList.tail = NULL;

	FILE* f = fopen("project.txt", "r");
	char buffer[256];

	while (fgets(buffer, sizeof(buffer), f)) {
		Project project;

		buffer[strlen(buffer) - 1] = '\0';
		project.id = (unsigned int)atoi(buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		project.title = (char*)malloc(strlen(buffer) + 1);
		strcpy(project.title, buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		project.customer = (char*)malloc(strlen(buffer) + 1);
		strcpy(project.customer, buffer);
		
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		project.nrExecutants = (unsigned char)atoi(buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		project.budget = (float)atof(buffer);

		insertTail(&doubleList, project);

	}
	printForward(&doubleList);
	deallocate(&doubleList);
	printForward(&doubleList);

	fclose(f);
	return 0;
}