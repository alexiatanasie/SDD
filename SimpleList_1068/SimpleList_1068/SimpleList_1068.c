//1068 SIMPLE LIST
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
typedef struct Booking {
	unsigned int bookingNr;
	char* hotel;
	unsigned char nrBookedRooms;
	char* guestName;
	float price;
	char paid;
}Booking;
typedef struct Node {
	Booking data;
	struct Node* next;
}Node;
Node* insert(Node* list, Booking booking) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = booking;
	newNode->next = list;
	list = newNode;
	return list;

}
void printList(Node* head) {
	Node* temp = head;
	while (temp) {
		printf("%u, %s, %u, %s, %.2f, %c\n", temp->data.bookingNr, temp->data.hotel, temp->data.nrBookedRooms,
			temp->data.guestName, temp->data.price, temp->data.paid);

		temp = temp->next;

	}
	
}
Node* deallocate(Node* list) {

	while (list) {
		free(list->data.hotel);
		free(list->data.guestName);

		Node* temp = list;
		list = list->next;
		free(temp);
	}
	return list;
}
//2 
unsigned int nrRoomsBooked(Node* list, const char* guestName) {

	unsigned int total = 0;
	Node* current = list;
	while (current) {
		if (strcmp(current->data.guestName, guestName) == 0) {
			total += current->data.nrBookedRooms;
		}
		current = current->next;

	}return total;
	
}
//3
Node* deletePaidBookings(Node* list) {
	Node* current = list;
	Node* prev = NULL;

	while (current) {
		if (current->data.paid == 'Y') {
			Node* todelete = current;
			if (prev == NULL) {
				list = current->next;
			}
			else {
				prev->next = current->next;
			}
			current = current->next;

			free(todelete->data.hotel);
			free(todelete->data.guestName);
			free(todelete);

		}
		else {
			prev = current;
			current = current->next;

		}
	}return list;
}
int main() {

	FILE* f = fopen("booking.txt", "r");
	Node* head = NULL;
	char buffer[256];
	while (fgets(buffer, sizeof(buffer), f)) {
		Booking booking;
		buffer[strlen(buffer) - 1] = '\0';
		booking.bookingNr = (unsigned int)atoi(buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.hotel = (char*)malloc(strlen(buffer) + 1);
		strcpy(booking.hotel, buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.nrBookedRooms = atoi(buffer);

		//guest name
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.guestName = (char*)malloc(strlen(buffer) + 1);
		strcpy(booking.guestName, buffer);
		//price
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.price = (float)atof(buffer);

		//paid(char)
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.paid = buffer[0];


		head = insert(head, booking);
	}

	printList(head);

	printf("%u \n", nrRoomsBooked(head, "KIM"));
	head = deletePaidBookings(head);
	printList(head);

	head = deallocate(head);
	printList(head);

	fclose(f);
	return 0;

}