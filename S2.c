#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Produs {
	float pret;
	int cod;
	char* denumire;
};
//citeste un vector dintr-un fisier
//deschide fisierul specificat prin fisierProdus pt citire
//citeste dim vect din fisier si aloca memorie pt vector
//populeaza vectorul citind val din fisier
//inchide fisierul
void citireVector(const char* fisierProdus, int** vect, int* dim) {
	//dereferentiere
	FILE* f = NULL;
	f = fopen(fisierProdus, "r");
	if (f != NULL) {
		fscanf(f, "%d", dim);
		*vect = (int*)malloc(sizeof(int) * (*dim));//sizeof(int) * (*dim) calculează numărul total de bytes necesari pentru a stoca *dim elemente de tip int
		for (int i = 0; i < *dim; i++) {
			fscanf(f, "%d", *vect + i);
		}

	}
	fclose(f);
}

struct Produs preluareProdusDinFisier(FILE* file) {
	struct Produs produs;
	if (file != NULL) {
		char buffer[20]; //buffer este un array de (20 in ex) caractere unde linia de etxt va fi stocata 


		fgets(buffer, 10, file); //10 specifica nr max de caractere care vor fi citite inclusiv caract nul de terminare
		produs.pret = atof(buffer);

		fgets(buffer, 10, file);
		produs.cod = atoi(buffer);

		fgets(buffer, 15, file);
		char* denumire = strtok(buffer, "\n");
		produs.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
		strcpy(produs.denumire, denumire);
	}
	return produs;
}

void afisareProdus(struct Produs produs);

void main() {
	int val1, val2;
	FILE* f = NULL;
	f = fopen("Fisier.txt", "r");
	if (f != NULL) {
		fscanf(f, "%d", &val1);
		fscanf(f, "%d", &val2);
	}
	fclose(f);

	printf("\n val1= %d, val2= %d", val1, val2);

	int* vector = NULL;
	int dimensiune;
	citireVector("Vector.txt", &vector, &dimensiune);

	for (int i = 0; i < dimensiune; i++) {
		printf("\n vector[%i]= %d", i, vector[i]);
	}
	free(vector);

	FILE* file = NULL;
	file = fopen("Produs.txt", "r");
	struct Produs produs = preluareProdusDinFisier(file);

	afisareProdus(produs);
}

void afisareProdus(struct Produs produs) {
	printf("\nProdusul %s are codul %d si pretul %.2f lei.", produs.denumire, produs.cod, produs.pret);
}
//
//Citirea valorilor din fișier : Deschide fișierul "Fisier.txt", citește două valori întregi și le afișează.
//Citirea vectorului din fișier : Deschide fișierul "Vector.txt", citește un vector de întregi și îl afișează, apoi eliberează memoria alocată.
//Citirea unui produs din fișier : Deschide fișierul "Produs.txt", citește un produs și îl afișează.