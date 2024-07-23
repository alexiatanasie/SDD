#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//transmitere prin valoare
//orice modificare a parametrilor nu va afecta valorile originale

void interschimbare(int n1, int n2) {
	int aux;
	aux = n1;
	n1 = n2;
	n2 = aux;
}

//transmitere prin adresa
//parametrii sunt pointeri catre variabilele originale, modificarile lor vor afecta variabilele originale
void intPointer(int* n1, int* n2) {
	int aux;
	aux = *n1;
	*n1 = *n2;
	*n2 = aux;
}

//citirea unui vector de la tastatura
//aloca dinamic memorie pt vector in fct de dim introdusa
void citireTast(int** vect, int* dim) {
	printf("\n dimensiune:");
	scanf_s("\%d ", dim);

	*vect = (int*)malloc((*dim) * sizeof(int));
	for (int i = 0; i < (*dim); i++) {
		printf("vect[%i]=", i);
		scanf("%d", &(*vect)[i]);
	}
	printf("\n");
}

void afisare(int* vect, int dim) {
	for (int i = 0; i < dim; i++) {
		printf("\n vect[%d]=%d", i, vect[i]);
	}
}
int main() {
	int nr=13;
	char caracter='T';
	float nrR=22.13f;
	printf("%d", nr);
	printf( "\n");
	printf("%c", caracter);
	printf("\n");
	printf("%.2f", nrR);
	printf("\n");

	char sirCaracter[10];
	for (int i = 0; i < 10; i++) {
		sirCaracter[i] = 100 + i;
	}
	sirCaracter[9] = '\0';
	printf("%s \n", sirCaracter); 

	char* sirDinamic = (char*)malloc(2 * sizeof(char));
	for (int i = 0; i < 5; i++) {
		sirDinamic[i] = 69 + i;
	}
	sirDinamic[4] = '\0';
	printf("%s \n", sirDinamic);

	int n1 = 20, n2 = 25;
	interschimbare(n1, n2);
	printf("%d %d", n1, n2);
	printf("\n");
	intPointer(&n1, &n2);
	printf("%d %d", n1, n2);

	int* vect;
	int dim;
	citireTast(&vect, &dim);
	afisare(vect, dim);
}