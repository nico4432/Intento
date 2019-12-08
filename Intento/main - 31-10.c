#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int leerDatos(char* version, char* lista) {
	FILE* archivo;
	char dato[250], nombre[20] = "EntradaParte1_", formato[20] = ".in";
	strcat(nombre, version);
	strcat(nombre, formato);
	archivo = fopen(nombre, "r");
	while (feof(archivo) == 0) {
		fscanf(archivo, "%s", dato);
		strcat(lista, dato);
	}
	fclose(archivo);
}

void generarMatriz(char pmatriz[50][50], char* lista) {
	int posicion = 1;
	int largo = 0;
	if (lista[0]=='5') {
		largo = 11;
	}
	if (lista[0] == '1' && lista[1] == '0') {
		largo = 21;
		posicion++;
	}
	if (lista[0] == '1' && lista[1] == '5') {
		largo = 31;
		posicion++;
	}
	for (int j = 0; j < largo; j++) {
		for (int i = 0; i < largo; i++) {
			if (j % 2 == 0) {
				pmatriz[j][i] = ' ';
			}
			else {
				if (i % 2 == 0) {
					pmatriz[j][i] = ' ';
				}
				else {
					pmatriz[j][i] = lista[posicion];
					posicion++;
				}
			}
		}
	}
	// Este print es para revisar la matriz que entra, se puede borrar mas tarde.
	for (int j = 0; j < largo; j++) {
		for (int i = 0; i < largo; ++i) {
			printf("%c", pmatriz[j][i]);
		}
		printf("\n");
	}
}


int main() {
	char* version, lista[250] = "\0";
	int largo;
	char matriz[50][50];

	 printf("Ingrese la vercion del archivo que desea cargar:");
	 scanf("%s", version);

	 largo = strlen(version);
	 if (largo != 2) {
	 	printf("Escriba una version correcta.\n");
	 } else {
	 	leerDatos(version, lista);
		printf("%s\n", lista);
		generarMatriz(matriz, lista);
	 }

	return 0;
}