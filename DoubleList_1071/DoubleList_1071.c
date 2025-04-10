//1071 2024
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>


typedef struct Project {
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

void insertTail(DoubleList* list,Project project) {
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
		printf("%s, %s, %u, %.2f\n", temp->data.title, temp->data.customer, temp->data.nrExecutants, temp->data.budget);
		temp = temp->next;
	}
}
void printBackward(DoubleList* list) {
	Node* temp = list->tail;
	while (temp) {
		printf("%s, %s, %u, %.2f\n", temp->data.title, temp->data.customer, temp->data.nrExecutants, temp->data.budget);
		temp = temp->prev;
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
unsigned int countExecutants(DoubleList* list, const char* customer) {
	Node* temp = list->head;
	unsigned int count=0;
	while (temp) {
		if (strcmp(temp->data.customer, customer) == 0) {
			count = count + temp->data.nrExecutants;
		}
		temp = temp->next;
	}
	return count;
}
//3 
void increaseBudget(DoubleList* list, float threshold, float percent) {
	Node* temp = list->head;
	while (temp) {
		if (temp->data.budget > threshold) {
			temp->data.budget += (percent / 100.0f) * temp->data.budget;

		}
		temp = temp->next;
	}
}
int main() {
	DoubleList doubleList;
	doubleList.head = NULL;
	doubleList.tail = NULL;
	FILE*f = fopen("project.txt", "r");
	char buffer[256];
	while (fgets(buffer, sizeof(buffer), f)) {
		Project project;

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
		project.budget = ( float)atof(buffer);

		insertTail(&doubleList, project);
	}
	printBackward(&doubleList);

	//2
	printf("%u \n", countExecutants(&doubleList, "Google"));
	//3
	increaseBudget(&doubleList, 10000, 60.0f);
	printBackward(&doubleList);
	printForward(&doubleList);
	deallocate(&doubleList);
	fclose(f);
	return 0;
}