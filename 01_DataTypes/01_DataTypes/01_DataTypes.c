#include <stdio.h>
#include <malloc.h>

#define BYTEARRAY_SIZE 10
#define LINE_SIZE 6
#define COLUMN_SIZE 9

int main() {
	char x = 65; //echivalent cu char x='A'
	unsigned char y = -2;
	float z = (float)65.64;

	char* p = NULL;
	printf("memory address of location p=%p \n", &p);
	printf("content of location p=%p \n", p);
	//printf("content of pointed location p=%d \n", *p);

	p = &x; //pointerul p primeste adresa lui x //write p with the stack memory address of x
	printf("memory address of location p=%p \n", &p);
	printf("content of location p=%p \n", p);
	printf("content of pointed location p=%d \n", *p);

	p = (char*)malloc(1 * sizeof(char)); //heap memory for one single char location
	printf("memory address of location p=%p \n", &p);
	printf("content of location p=%p \n", p);
	printf("content of pointed location p=%d \n", *p);
	//malloc aloca un octet pe heap si returneaza pointer catre aceasta locatie
	//p este actualizat pentru a indica aceasta locatie
	//nu initializeaza memoria, deci *p poate contine o valoare aleatorie

	*p = x; //write content of x(65) over the memory pointed of p
	printf("Memory Address of location p = %p \n", &p);
	printf("Content of location p = %p \n", p);
	printf("Content of pointed location p = %d \n", *p);

	free(p);//deallocation of heap memory pointer by p

	p = (char*)malloc((BYTEARRAY_SIZE + 1) * sizeof(char)); //allocate a byte array
	//se aloca un array de 10 caractere +1 pt '\0'
	//se populeaza array ul cu caractere A,B,C...J
	for (unsigned char i = 0; i < BYTEARRAY_SIZE; i++) {
		p[i] = x + i;
		// p[i] points to heap mem for the item having the offset i(same like compile-time allocated array)

	}
	p[BYTEARRAY_SIZE] = 0; //adaugam terminatorul '\0' //// save the null byte right after the last item in the bytearray
	for (unsigned char i = 0; i < BYTEARRAY_SIZE; i++) {
		printf("%d -->%c\n", p[i], p[i]);
	}

	printf("%s\n", p);
	free(p);

	char v[BYTEARRAY_SIZE + 1];
	p = v; //p containts the starting point(mem address) of the array v
	for (unsigned char i = 0; i < BYTEARRAY_SIZE; i++) {
		v[i] = x + i;
	}
	v[BYTEARRAY_SIZE] = 0; //null byte terminator is put on the last item in array v
	printf("%s\n", p);

	char** pM = NULL; //este un pointer la pointeri
	//matrix allocation
	pM = (char**)malloc(LINE_SIZE * sizeof(char*)); //allocation of the 1st level of the matrix in heap
	for (unsigned char i = 0; i < LINE_SIZE; i++) {
		pM[i] = (char*)malloc(COLUMN_SIZE * sizeof(char)); //allocation of the line i;heap memory address stored on intermediary level(pM[i])

	}
	//by me
	//populate matrix
	for (unsigned char i = 0; i < LINE_SIZE; i++) {
		for (unsigned char j = 0; j < COLUMN_SIZE - 1; j++) 
			{
				pM[i][j] = 'A' + (i + j) % 26;
		}
			pM[i][COLUMN_SIZE - 1] = '\0'; //null terminator
	}
	//print matrix
	printf("mat:\n");
	for (unsigned char i = 0; i < LINE_SIZE; i++) {
		printf("%s\n", pM[i]);
	}
	//matrix deallocation
	///deallocate the farest heap location(the lines with the actual values)
	for (unsigned char i = 0; i < LINE_SIZE; i++) {
		free(pM[i]); //deallocate line i
	}
	//deallocate the nearest line i'
	free(pM); //deallocate the intermediary array of address to the lines
	return 0;
}