#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct movPosibles posicion;

struct movPosibles {
	int R; // contendran 0 y 1 los que se pueden usar
	int U;
	int L;
	int D;
	int posx; // coordenada x
	int posy; // coordenada y
};

int movimientos = 0;

posicion nuevaPosicion(char pmatriz[50][50], int posicionActualX, int posiciconActualY);
posicion* agregarPosicion(posicion* lista, int* elementos, posicion estado);
posicion* quitarPosicion(posicion* lista, int* elementos);
int leerDatos(char* version, char* lista);
void generarMatriz(char pmatriz[50][50], char* lista);
int puntosalrededor(char pmatriz[50][50], int poscicionx, int posciciony);
int largoMatriz(char pmatriz[50][50]);
posicion busqueda3(char pmatriz[50][50]);
int condiciones(int posicionActualX, int posiciconActualY, int posiciconFinalX, int posicionFinalY, char pmatriz[50][50]);
int movimientoR(char pmatriz[50][50], int posicionActualX, int posiciconActualY);
int movimientoU(char pmatriz[50][50], int posicionActualX, int posiciconActualY);
int movimientoL(char pmatriz[50][50], int posicionActualX, int posiciconActualY);
int movimientoD(char pmatriz[50][50], int posicionActualX, int posiciconActualY);
void cerco(char pmatriz[50][50]);
void solucion(char pmatriz[50][50], int posicionActualX, int posicionActualY, int posiciconFinalX, int posicionFinalY, posicion* listaPosiciones);

posicion nuevaPosicion(char pmatriz[50][50], int posicionActualX, int posiciconActualY) {
	posicion nuevaPos;
	nuevaPos.R = movimientoR(pmatriz, posicionActualX, posiciconActualY);
	nuevaPos.U = movimientoU(pmatriz, posicionActualX, posiciconActualY);
	nuevaPos.L = movimientoL(pmatriz, posicionActualX, posiciconActualY);
	nuevaPos.D = movimientoD(pmatriz, posicionActualX, posiciconActualY);
	nuevaPos.posx = posicionActualX;
	nuevaPos.posy = posiciconActualY;

	return nuevaPos;
}

posicion* agregarPosicion(posicion* lista, int* elementos, posicion estado) {
	posicion* nuevaLista = (posicion*)malloc(sizeof(posicion) * (*elementos + 1));
	for (int i = 0; i < *elementos; ++i) {
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos + 1;
	free(lista);
	return nuevaLista;
}

posicion* quitarPosicion(posicion* lista, int* elementos) {
	posicion* nuevaLista = (posicion*)malloc(sizeof(posicion) * (*elementos));
	for (int i = 0; i < *elementos; ++i) {
		nuevaLista[i] = lista[i];
	}
	*elementos = *elementos - 1;
	free(lista);
	return nuevaLista;
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

int puntosalrededor(char pmatriz[50][50], int poscicionx, int posciciony) {
	int cantidadDePuntos = 0;
	if (pmatriz[poscicionx][posciciony + 1] == '#') {
		cantidadDePuntos++;
	}
	if (pmatriz[poscicionx - 1][posciciony] == '#') {
		cantidadDePuntos++;
	}
	if (pmatriz[poscicionx][posciciony - 1] == '#') {
		cantidadDePuntos++;
	}
	if (pmatriz[poscicionx + 1][posciciony] == '#') {
		cantidadDePuntos++;
	}
	return cantidadDePuntos;
}

int largoMatriz(char pmatriz[50][50]) {
	int largo = 0;
	while (pmatriz[0][largo] == '_' || pmatriz[0][largo] == '0' || pmatriz[0][largo] == '1' || pmatriz[0][largo] == '2' || pmatriz[0][largo] == '3' || pmatriz[0][largo] == ' ' || pmatriz[0][largo] == '#') {
		largo++;
	}
	return largo;
}

posicion busqueda3(char pmatriz[50][50]) {
	posicion inicio;
	int largo = largoMatriz(pmatriz);
	int cantidad = 0;
 
	for (int j = 0; j < largo; j++) {
		for (int i = 0; i < largo; ++i) {
			if (pmatriz[j][i] == '3') {
				inicio.posx = j;
				inicio.posy = i;
			}
		}
	}
	inicio.R = 1;
	inicio.U = 1;
	inicio.L = 1;
	inicio.D = 1;
	return inicio;
}

int condiciones(int posicionActualX, int posiciconActualY, int posiciconFinalX, int posicionFinalY, char pmatriz[50][50]) {
	int condicionesCumplidas = 1;
	if (posicionActualX == posiciconFinalX && posiciconActualY == posicionFinalY) {
		condicionesCumplidas++;
	}
	int largo = largoMatriz(pmatriz);
	int cantidad = 0;
 
	for (int j = 0; j < largo; j++) {
		for (int i = 0; i < largo; ++i) {
			if (pmatriz[j][i] == '3' && puntosalrededor(pmatriz, j, i) != 3 ) {
				condicionesCumplidas = 0;
			}
		}
	}
	for (int j = 0; j < largo; j++) {
		for (int i = 0; i < largo; ++i) {
			if (pmatriz[j][i] == '2' && puntosalrededor(pmatriz, j, i) != 2) {
				condicionesCumplidas = 0;
			}
		}
	}
	for (int j = 0; j < largo; j++) {
		for (int i = 0; i < largo; ++i) {
			if (pmatriz[j][i] == '1' && puntosalrededor(pmatriz, j, i) != 1) {
				condicionesCumplidas = 0;
			}
		}
	}
	for (int j = 0; j < largo; j++) {
		for (int i = 0; i < largo; ++i) {
			if (pmatriz[j][i] == '0' && puntosalrededor(pmatriz, j, i) != 0) {
				condicionesCumplidas = 0;
			}
		}
	}
	return condicionesCumplidas;
}

int movimientoR(char pmatriz[50][50], int posicionActualX, int posiciconActualY) {
	int movimiento;
	if (pmatriz[posicionActualX][posiciconActualY + 1] == ' ') {
		movimiento = 1;
	} else {
		movimiento = 0;
	}
	return movimiento;
}

int movimientoU(char pmatriz[50][50], int posicionActualX, int posiciconActualY) {
	int movimiento;
	if (pmatriz[posicionActualX - 1][posiciconActualY] == ' ') {
		movimiento = 1;
	}
	else {
		movimiento = 0;
	}
	return movimiento;
}

int movimientoL(char pmatriz[50][50], int posicionActualX, int posiciconActualY) {
	int movimiento;
	if (pmatriz[posicionActualX][posiciconActualY - 1] == ' ') {
		movimiento = 1;
	}
	else {
		movimiento = 0;
	}
	return movimiento;
}

int movimientoD(char pmatriz[50][50], int posicionActualX, int posiciconActualY) {
	int movimiento;
	if (pmatriz[posicionActualX + 1][posiciconActualY] == ' ') {
		movimiento = 1;
	}
	else {
		movimiento = 0;
	}
	return movimiento;
}

void cerco(char pmatriz[50][50]) {
	int largo = largoMatriz(pmatriz);
	int contador = 0;

	for (int fila = 0; fila < largo; fila++) {
		for (int columna = 0; columna < largo; columna++) {
			if (fila % 2 == 0) {
				if (pmatriz[fila][columna] != '#') {
					pmatriz[fila][columna] = ' ';
				}
				else if (pmatriz[fila][columna] == '#') {
					while (pmatriz[fila][columna] == '#') {
						columna++;
					}
				}
			}
			else if (fila % 2 == 1) {
				if (contador % 2 == 0) {
					if (pmatriz[fila][columna] != '#') {
						pmatriz[fila][columna] = ' ';
					}
				} 
				else if (contador % 2 == 1) {
					if (pmatriz[fila][columna] != '#') {
						pmatriz[fila][columna] = '0';
					}
				} 
				if (pmatriz[fila][columna] == '#') {
					contador++;
				}
			}
		}
	}

	for (int fila = 0; fila < largo; fila++) {
		for (int columna = 0; columna < largo; columna++) {
			if (pmatriz[fila][columna] == '0' && pmatriz[fila + 1][columna] == ' ' && pmatriz[fila + 2][columna] == '0') {
				pmatriz[fila + 1][columna] = '0';
			}
		}
	}
}

void solucion(char pmatriz[50][50], int posicionActualX, int posicionActualY, int posiciconFinalX, int posicionFinalY, posicion* listaPosiciones) {

	while (condiciones(posicionActualX, posicionActualY, posiciconFinalX, posicionFinalY, pmatriz) != 2) {
		int* mov = &movimientos;
		posicion coorActual;
		if (movimientos == 1) {
			if (listaPosiciones[0].R == 1) {
				listaPosiciones[0].R = 0;

				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy - 1] = '#';
				pmatriz[listaPosiciones[0].posx][listaPosiciones[0].posy - 1] = '#';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy - 1] = '#';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy] = '#';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy + 1] = '#';

				posiciconFinalX = listaPosiciones[0].posx + 1;
				posicionFinalY = listaPosiciones[0].posy;

				coorActual = nuevaPosicion(pmatriz, listaPosiciones[0].posx - 1, listaPosiciones[0].posy + 1);
				listaPosiciones = agregarPosicion(listaPosiciones, mov, coorActual);

			}
			else if (listaPosiciones[0].U == 1) {
				listaPosiciones[0].U = 0;

				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy - 1] = ' ';
				pmatriz[listaPosiciones[0].posx][listaPosiciones[0].posy - 1] = ' ';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy - 1] = ' ';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy] = ' ';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy + 1] = ' ';

				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy + 1] = '#';
				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy] = '#';
				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy - 1] = '#';
				pmatriz[listaPosiciones[0].posx][listaPosiciones[0].posy - 1] = '#';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy - 1] = '#';

				posiciconFinalX = listaPosiciones[0].posx;
				posicionFinalY = listaPosiciones[0].posy + 1;

				coorActual = nuevaPosicion(pmatriz, listaPosiciones[0].posx - 1, listaPosiciones[0].posy - 1);
				listaPosiciones = agregarPosicion(listaPosiciones, mov, coorActual);


			}
			else if (listaPosiciones[0].L == 1) {
				listaPosiciones[0].L = 0;

				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy + 1] = ' ';
				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy] = ' ';
				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy - 1] = ' ';
				pmatriz[listaPosiciones[0].posx][listaPosiciones[0].posy - 1] = ' ';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy - 1] = ' ';

				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy + 1] = '#';
				pmatriz[listaPosiciones[0].posx][listaPosiciones[0].posy + 1] = '#';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy + 1] = '#';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy] = '#';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy - 1] = '#';

				posiciconFinalX = listaPosiciones[0].posx + 1;
				posicionFinalY = listaPosiciones[0].posy;

				coorActual = nuevaPosicion(pmatriz, listaPosiciones[0].posx - 1, listaPosiciones[0].posy - 1);
				listaPosiciones = agregarPosicion(listaPosiciones, mov, coorActual);


			}
			else if (listaPosiciones[0].D == 1) {
				listaPosiciones[0].D = 0;

				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy + 1] = ' ';
				pmatriz[listaPosiciones[0].posx][listaPosiciones[0].posy + 1] = ' ';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy + 1] = ' ';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy] = ' ';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy - 1] = ' ';

				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy + 1] = '#';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy] = '#';
				pmatriz[listaPosiciones[0].posx - 1][listaPosiciones[0].posy - 1] = '#';
				pmatriz[listaPosiciones[0].posx][listaPosiciones[0].posy - 1] = '#';
				pmatriz[listaPosiciones[0].posx + 1][listaPosiciones[0].posy - 1] = '#';

				posiciconFinalX = listaPosiciones[0].posx;
				posicionFinalY = listaPosiciones[0].posy + 1;

				coorActual = nuevaPosicion(pmatriz, listaPosiciones[0].posx + 1, listaPosiciones[0].posy - 1);
				listaPosiciones = agregarPosicion(listaPosiciones, mov, coorActual);


			}

		}
		else {
			if (listaPosiciones[movimientos - 1].R == 1) {
				listaPosiciones[movimientos - 1].R = 0;
				coorActual = nuevaPosicion(pmatriz, listaPosiciones[movimientos - 1].posx, listaPosiciones[movimientos - 1].posy + 1);
				listaPosiciones = agregarPosicion(listaPosiciones, mov, coorActual);
				pmatriz[listaPosiciones[movimientos - 1].posx][listaPosiciones[movimientos - 1].posy] = '#';

				posicionActualX = listaPosiciones[movimientos - 1].posx;
				posicionActualY = listaPosiciones[movimientos - 1].posy;
			}
			else if (listaPosiciones[movimientos - 1].U == 1) {
				listaPosiciones[movimientos - 1].U = 0;
				coorActual = nuevaPosicion(pmatriz, listaPosiciones[movimientos - 1].posx - 1, listaPosiciones[movimientos - 1].posy);
				listaPosiciones = agregarPosicion(listaPosiciones, mov, coorActual);
				pmatriz[listaPosiciones[movimientos - 1].posx][listaPosiciones[movimientos - 1].posy] = '#';

				posicionActualX = listaPosiciones[movimientos - 1].posx;
				posicionActualY = listaPosiciones[movimientos - 1].posy;

			}
			else if (listaPosiciones[movimientos - 1].L == 1) {
				listaPosiciones[movimientos - 1].L = 0;
				coorActual = nuevaPosicion(pmatriz, listaPosiciones[movimientos - 1].posx, listaPosiciones[movimientos - 1].posy - 1);
				listaPosiciones = agregarPosicion(listaPosiciones, mov, coorActual);
				pmatriz[listaPosiciones[movimientos - 1].posx][listaPosiciones[movimientos - 1].posy] = '#';

				posicionActualX = listaPosiciones[movimientos - 1].posx;
				posicionActualY = listaPosiciones[movimientos - 1].posy;

			}
			else if (listaPosiciones[movimientos - 1].D == 1) {
				listaPosiciones[movimientos - 1].D = 0;
				coorActual = nuevaPosicion(pmatriz, listaPosiciones[movimientos - 1].posx + 1, listaPosiciones[movimientos - 1].posy);
				listaPosiciones = agregarPosicion(listaPosiciones, mov, coorActual);
				pmatriz[listaPosiciones[movimientos - 1].posx][listaPosiciones[movimientos - 1].posy] = '#';

				posicionActualX = listaPosiciones[movimientos - 1].posx;
				posicionActualY = listaPosiciones[movimientos - 1].posy;

			}
			else if (listaPosiciones[movimientos - 1].R == 0 && listaPosiciones[movimientos - 1].U == 0 && listaPosiciones[movimientos - 1].L == 0 && listaPosiciones[movimientos - 1].D == 0) {
				pmatriz[listaPosiciones[movimientos - 1].posx][listaPosiciones[movimientos - 1].posy] = ' ';
				listaPosiciones = quitarPosicion(listaPosiciones, mov);

			}
		}
		//for (int j = 0; j < 11; j++) {
		//	for (int i = 0; i < 11; ++i) {
		//		printf("%c", pmatriz[j][i]);
		//	}
		//	printf("\n");
		//}
		//system("cls");
	}
}

int main() {
	char version[10], lista[250] = "\0";
	int largo = 0;
	char matriz[50][50];

	int coordenadasFinalesX = 0, coordenadasFinalesY = 0;
	int* posfx = &coordenadasFinalesX, * posfy = &coordenadasFinalesY;

	int coorActualX = 0, coorActualY = 0;
	int* posx = &coorActualX, * posy = &coorActualY;

	int* mov = &movimientos;

	 printf("Ingrese la vercion del archivo que desea cargar:");
	 scanf("%s", version);
	 largo = strlen(version);

	 if (largo != 2) {
	 	printf("Escriba una version correcta.\n");
	 } else {
	 	leerDatos(version, lista);
		generarMatriz(matriz, lista);
		posicion* listaPosiciones = (posicion*)malloc(sizeof(posicion) * movimientos);
		posicion inicio;
		inicio = busqueda3(matriz);
		listaPosiciones = agregarPosicion(listaPosiciones, mov, inicio);

		solucion(matriz, coorActualX, coorActualY, coordenadasFinalesX, coordenadasFinalesY, listaPosiciones);

		cerco(matriz);

		for (int j = 0; j < 11; j++) {
			for (int i = 0; i < 11; ++i) {
				printf("%c", matriz[j][i]);
			}
			printf("\n");
		}  

		


	 }


	return 0;
}






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


//for (int j = 0; j < 11; j++) {
//	for (int i = 0; i < 11; ++i) {
//		printf("%c", matriz[j][i]);
//	}
//	printf("\n");
//}

//matriz[10][2] = '#';
//matriz[10][3] = '#';
//matriz[10][4] = '#';
//matriz[10][5] = '#';
//matriz[10][6] = '#';
//matriz[10][7] = '#';
//matriz[10][8] = '#';
//matriz[10][9] = '#';
//matriz[10][10] = '#';
//matriz[9][2] = '#';
//matriz[9][10] = '#';
//matriz[8][10] = '#';
//matriz[8][9] = '#';
//matriz[8][8] = '#';
//matriz[8][7] = '#';
//matriz[8][6] = '#';
//matriz[8][5] = '#';
//matriz[8][4] = '#';
//matriz[8][2] = '#';
//matriz[8][1] = '#';
//matriz[8][0] = '#';
//matriz[7][0] = '#';
//matriz[7][4] = '#';
//matriz[6][0] = '#';
//matriz[6][2] = '#';
//matriz[6][3] = '#';
//matriz[6][4] = '#';
//matriz[6][6] = '#';
//matriz[6][7] = '#';
//matriz[6][8] = '#';
//matriz[5][0] = '#';
//matriz[5][2] = '#';
//matriz[5][6] = '#';
//matriz[5][8] = '#';
//matriz[4][0] = '#';
//matriz[4][2] = '#';
//matriz[4][3] = '#';
//matriz[4][4] = '#';
//matriz[4][5] = '#';
//matriz[4][6] = '#';
//matriz[4][8] = '#';
//matriz[4][9] = '#';
//matriz[4][10] = '#';
//matriz[3][0] = '#';
//matriz[3][10] = '#';
//matriz[2][0] = '#';
//matriz[2][1] = '#';
//matriz[2][2] = '#';
//matriz[2][4] = '#';
//matriz[2][5] = '#';
//matriz[2][6] = '#';
//matriz[2][8] = '#';
//matriz[2][9] = '#';
//matriz[2][10] = '#';
//matriz[1][2] = '#';
//matriz[1][4] = '#';
//matriz[1][6] = '#';
//matriz[1][8] = '#';
//matriz[0][2] = '#';
//matriz[0][3] = '#';
//matriz[0][4] = '#';
//matriz[0][6] = '#';
//matriz[0][7] = '#';
//matriz[0][8] = '#';