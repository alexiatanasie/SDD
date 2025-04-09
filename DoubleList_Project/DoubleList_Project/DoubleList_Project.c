//1067 2023
#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>
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
	struct Node* next, *prev;
}Node;

typedef struct DoubleList {
	struct Node* head, * tail;
}DoubleList;

void insertTail(DoubleList* list, Project project) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = project;
	newNode->next = NULL;
	newNode->prev = list->tail;
	if (list->tail)list->tail->next = newNode;
	else list->head = newNode;
	list->tail = newNode;
}

void printForward(DoubleList* list) {
	Node* temp = list->head;
	while (temp) {
		printf("%u, %s, %s, %u, %.2f\n", temp->data.id, temp->data.title, temp->data.customer, temp->data.nrExecutants, temp->data.budget);
		temp = temp->next;
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
//2		
float investmentsCustomer(DoubleList* list, const char* customer) {
	Node* current= list->head;
	float total = 0;
	while (current) {
		if (strcmp(current->data.customer, customer) == 0) {
			total = total + current->data.budget;
		}
		current = current->next;
	}
	return total;


}
//3
void increasesNrExecutants(DoubleList* list, float threshold, float percent) {
	Node* current = list->head;
	while (current) {
		if (current->data.budget > threshold) {
			current->data.nrExecutants += (unsigned char)((percent / 100.0f) * current->data.nrExecutants);
		}
		current = current->next;
	}
}
int main() {

	DoubleList doubleList;
	doubleList.head = NULL;
	doubleList.tail = NULL;
	FILE* f = fopen("projects.txt", "r");
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
		project.nrExecutants= (unsigned char)atoi(buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		project.budget = (float)atof(buffer);

		insertTail(&doubleList,project);

	}
	printForward(&doubleList);

	printf("%.2f\n",investmentsCustomer(&doubleList, "Amazon"));

	increasesNrExecutants(&doubleList, 10000.0f, 50.0f);
	printForward(&doubleList);

	deallocate(&doubleList);
	fclose(f);
	return 0;
}