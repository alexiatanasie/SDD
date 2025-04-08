//SIMPLE LIST SABLON EX SUB 1068 :))) sdd  e vtm ibrm mea
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct Booking {
	unsigned int bookingNumber;
	char* hotel;
	unsigned char nrBookedRooms;
	char* guestName;
	float price;
	char paid; //Y OR N

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
		printf("%u, %s, %u, %s, %.2f, %c\n", temp->data.bookingNumber, temp->data.hotel, temp->data.nrBookedRooms, temp->data.guestName, temp->data.price, temp->data.paid);
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

int main() {


	FILE* f = fopen("booking.txt", "r");
	Node* head = NULL;
	char buffer[256];
	while (fgets(buffer, sizeof(buffer), f)) {
		Booking booking;

		//booking nr
		buffer[strlen(buffer) - 1] = '\0';
		booking.bookingNumber = atoi(buffer);

		//hotel
		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = '\0';
		booking.hotel = (char*)malloc(strlen(buffer) + 1);
		strcpy(booking.hotel, buffer);

		//nr booked rooms
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
	head = deallocate(head);
	printList(head);



	fclose(f);
	return 0;
}