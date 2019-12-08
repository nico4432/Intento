#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct posicion posicion;
typedef struct movPosibles desplazamiento;

struct movPosibles {
	int R; // contendran 0 y 1 los que se pueden usar
	int U;
	int L;
	int D;
};

struct posicion {
	int posx; // coordenada x
	int posy; // coordenada y
};

int movimientos = 0;

desplazamiento nuevaPosicion(int a, int b, int c, int d) {
	desplazamiento nuevaPos;
	nuevaPos.R = a;
	nuevaPos.U = b;
	nuevaPos.L = c;	
	nuevaPos.D = d; 
	return nuevaPos;
}

posicion* agregarPosicion(posicion* lista, int* elementos, posicion estado) {
	posicion* nuevaLista = (posicion*)malloc(sizeof(posicion) * (*elementos + 1));
	for (int i = 0; i < *elementos; ++i) {
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	free(lista);
	return nuevaLista;
}

desplazamiento* agregarDesplazamiento(desplazamiento* lista, int *elementos, desplazamiento estado) {
	desplazamiento* nuevaLista = (desplazamiento*)malloc(sizeof(desplazamiento) * (*elementos + 1));
	for (int i = 0; i < *elementos; ++i) {
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	free(lista);
	return nuevaLista;
}



desplazamiento busquedaNumeroAd(char pmatriz[50][50], int posInicialX, int posInicialY) ;//devuelve la cantidad de numeros adyacentes
void busqueda0(int* fila, int* columna, char pmatriz[50][50]);

//desplazamiento busquedaNumeroAd(char pmatriz[50][50], int posInicialX, int posInicialY) {
//	desplazamiento primermovimiento;
//
//	if (pmatriz[posInicialX][posInicialY + 2] == '1' || pmatriz[posInicialX][posInicialY + 2] == '2' || pmatriz[posInicialX][posInicialY + 2] == '3') {
//		primermovimiento.R = 1;
//
//	} else { primermovimiento.R = 0; }
//
//	if (pmatriz[posInicialX - 2][posInicialY] == '1' || pmatriz[posInicialX - 2][posInicialY] == '2' || pmatriz[posInicialX - 2][posInicialY] == '3') {
//		primermovimiento.U = 1;
//	} else { primermovimiento.U = 0; }
//
//	if (pmatriz[posInicialX][posInicialY - 2] == '1' || pmatriz[posInicialX][posInicialY - 2] == '2' || pmatriz[posInicialX][posInicialY - 2] == '3') {
//		primermovimiento.L = 1;
//	} else { primermovimiento.L = 0; }
//
//	if (pmatriz[posInicialX + 2][posInicialY] == '1' || pmatriz[posInicialX + 2][posInicialY] == '2' || pmatriz[posInicialX + 2][posInicialY] == '3') {
//		primermovimiento.D = 1;
//	} else { primermovimiento.D = 0; }
//	return primermovimiento;
//}

desplazamiento busquedaNumeroAd(char pmatriz[50][50], int posInicialX, int posInicialY) {
	desplazamiento primermovimiento;

	if (pmatriz[posInicialX][posInicialY + 2] == '1') {
		primermovimiento.R = 1;
	}
	else if (pmatriz[posInicialX][posInicialY + 2] == '2') {
		primermovimiento.R = 2;
	}
	else if (pmatriz[posInicialX][posInicialY + 2] == '3') {
		primermovimiento.R = 3;
	} else { primermovimiento.R = 0; }

	if (pmatriz[posInicialX - 2][posInicialY] == '1') {
		primermovimiento.U = 1;
	}
	else if (pmatriz[posInicialX - 2][posInicialY] == '2') {
		primermovimiento.U = 2;
	}
	else if (pmatriz[posInicialX - 2][posInicialY] == '3') {
		primermovimiento.U = 3;
	} else { primermovimiento.U = 0; }

	if (pmatriz[posInicialX][posInicialY - 2] == '1') {
		primermovimiento.L = 1;
	}
	else if (pmatriz[posInicialX][posInicialY - 2] == '2') {
		primermovimiento.L = 2;
	}
	else if (pmatriz[posInicialX][posInicialY - 2] == '3') {
		primermovimiento.L = 3;
	} else { primermovimiento.L = 0; }

	if (pmatriz[posInicialX + 2][posInicialY] == '1') {
		primermovimiento.D = 1;
	}
	else if (pmatriz[posInicialX + 2][posInicialY] == '2') {
		primermovimiento.D = 2;
	}
	else if (pmatriz[posInicialX + 2][posInicialY] == '3') {
		primermovimiento.D = 3;
	} else { primermovimiento.D = 0; }

	return primermovimiento;
}


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
	////for (int j = 0; j < largo; j++) {
	////	for (int i = 0; i < largo; ++i) {
	////		printf("%c", pmatriz[j][i]);
	////	}
	////	printf("\n");
	////}
}

void busqueda0(int* fila, int* columna, char pmatriz[50][50]) {
	int largo = 0;
	while (pmatriz[0][largo] == '_' || pmatriz[0][largo] == '0' || pmatriz[0][largo] == '1' || pmatriz[0][largo] == '2' || pmatriz[0][largo] == '3' || pmatriz[0][largo] == ' ') {
		largo++;
	}
	for (int j = 0; j < largo; j++) {
		for (int i = 0; i < largo; ++i) {
			if (pmatriz[j][i] == '3') {
				*fila = j;
				*columna = i;
			}
		}
	}
}






void inicioFinal(int* posicionInicialX, int* posiciconInicialY, int* posiciconFinalX, int* posicionFinalY, char pmatriz[50][50]) {
	int coordenadas0X = 0, coordenadas0Y = 0;
	int* coorx = &coordenadas0X, * coory = &coordenadas0Y;
	desplazamiento numerosAdyacentes;
	busqueda0(coorx, coory, pmatriz);
	numerosAdyacentes = busquedaNumeroAd(pmatriz, coordenadas0X, coordenadas0Y);

	printf("Coordenada de X: %d \nCoordenada de Y: %d \n", coordenadas0X, coordenadas0Y);
	printf("%d %d %d %d \n", numerosAdyacentes.R, numerosAdyacentes.U, numerosAdyacentes.L, numerosAdyacentes.D);

	*posicionInicialX = 5;

}





int main() {
	char version[10], lista[250] = "\0";
	int largo = 0;
	char matriz[50][50];

	int coordenadasInicialesX = 0, coordenadasInicialesY = 0;
	int * posx = &coordenadasInicialesX, * posy = &coordenadasInicialesY;
	int coordenadasFinalesX = 0, coordenadasFinalesY = 0;
	int* posfx = &coordenadasFinalesX, * posfy = &coordenadasFinalesY;

	int coorActualX = 0, coorActualY = 0;
	int* poosx = &coorActualX, * poosy = &coorActualY;

	 printf("Ingrese la vercion del archivo que desea cargar:");
	 scanf("%s", version);
	 largo = strlen(version);

	 if (largo != 2) {
	 	printf("Escriba una version correcta.\n");
	 } else {
	 	leerDatos(version, lista);
		//printf("%s\n", lista);
		generarMatriz(matriz, lista);
		//matriz[6][7] = 'o';
		for (int j = 0; j < 11; j++) {
			for (int i = 0; i < 11; ++i) {
				printf("%c", matriz[j][i]);
			}
			printf("\n");
		}
		
		inicioFinal(posx, posy, posfx, posfy, matriz);

		// Bloque de como debo operar las listas al agregar un elemento nuevo

		////desplazamiento inicio, gato; // inicio es el importante
		////int* mov = &movimientos;
		////posicion* listaPosiciones = (posicion*)malloc(sizeof(posicion) * movimientos);
		////desplazamiento * listaMovimientos = (desplazamiento*)malloc(sizeof(desplazamiento) * movimientos);
		////listaMovimientos = agregarDesplazamiento(listaMovimientos, mov, inicio);
		////mov++;
		////gato = nuevaPosicion(5, 7, 8, 9);
		////listaMovimientos = agregarDesplazamiento(listaMovimientos, mov, gato);
		////printf("%d %d %d %d %d", listaMovimientos[1].R, listaMovimientos[0].U, listaMovimientos[1].L, listaMovimientos[0].D, movimientos);













	 }



	return 0;
}