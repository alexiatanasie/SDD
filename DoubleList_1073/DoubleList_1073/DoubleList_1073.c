//1073 DOUBLE LIST
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<stdio.h>

typedef struct Booking {
	unsigned int bookingNr;
	char* hotel;
	unsigned char nrBookedRooms;
	char* guestName;
	float price;
	char* status;
}Booking;

typedef struct Node {
	Booking data;
	struct Node* next, * prev;
}Node;
typedef struct DoubleList {
	struct Node* head, * tail;
}DoubleList;

void insertTail(DoubleList* list, Booking booking) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = booking;
	newNode->next = NULL;
	newNode->prev = list->tail;
	if (list->tail)list->tail->next = newNode;
	else list->head = newNode;
	list->tail = newNode;
}
void printForward(DoubleList* list) {
	Node* temp = list->head;
	while (temp) {
		printf("%u, %s, %u, %s, %.2f, %s\n", temp->data.bookingNr, temp->data.hotel, temp->data.nrBookedRooms, temp->data.guestName
			, temp->data.price, temp->data.status);
		temp = temp->next;
	}
}
//3
void printBackward(DoubleList* list) {
	Node* temp = list->tail;
	while (temp) {
		printf("%u, %s, %u, %s, %.2f, %s\n", temp->data.bookingNr, temp->data.hotel, temp->data.nrBookedRooms, temp->data.guestName
			, temp->data.price, temp->data.status);
		temp = temp->prev;
	}
}
void deallocate(DoubleList* list) {
	Node* current = list->head;
	while (current) {
		free(current->data.hotel);
		free(current->data.guestName);
		free(current->data.status);

		Node* temp = current;
		current = current->next;
		free(temp);
	}
	list->head = NULL;
	list->tail = NULL;
}
//ex 2 
float calculateAveragePricePerRoom(DoubleList* list) {
	Node* current = list->head;
	float total = 0;
	int totalRooms = 0;
	float average = 0;


	while (current) {
		total = total + current->data.price;
		totalRooms = totalRooms + current->data.nrBookedRooms;
		current = current->next;
		
	}
	if (totalRooms > 0) {
		average = total / totalRooms;
	}
	return average;

}
//3
void replaceStatus(DoubleList* list, const char* guestName){

	Node* current = list->head;
	while (current) {
		if (strcmp(current->data.guestName, guestName) == 0 && strcmp(current->data.status, "Reserved") == 0) {
			free(current->data.status);
			current->data.status = (char*)malloc(strlen("Canceled") + 1);
			strcpy(current->data.status, "Canceled");
		}
		current = current->next;
	}

}
int main(){

	DoubleList doubleList;
	doubleList.head = NULL;
	doubleList.tail = NULL;

	FILE* f = fopen("booking.txt", "r");
	char buffer[256];
	while (fgets(buffer, sizeof(buffer), f)) 
	{

		Booking booking;

		buffer[strlen(buffer) - 1] = '\0';
		booking.bookingNr = atoi(buffer);


		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.hotel = (char*)malloc(strlen(buffer) + 1);
		strcpy(booking.hotel, buffer);


		fgets (buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.nrBookedRooms = (unsigned char)atoi(buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.guestName = (char*)malloc(strlen(buffer) + 1);
		strcpy(booking.guestName, buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.price = (float)atof(buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.status = (char*)malloc(strlen(buffer) + 1);
		strcpy(booking.status, buffer);


		insertTail(&doubleList, booking);
	}
	printForward(&doubleList);

	//2
	printf("%.2f\n",calculateAveragePricePerRoom(&doubleList));

	//3
	replaceStatus(&doubleList, "ALE");
	printForward(&doubleList);
	printBackward(&doubleList);

	
	deallocate(&doubleList);

	fclose(f);
	return 0;
}