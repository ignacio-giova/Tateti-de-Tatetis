#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct tatetis{
  int dominio;
  // 0 -> sin dominio
  // 1 -> jugador 1
  // 2 -> jugador 2
  // 3 -> empate
  int arr[3][3];
} tateti;

typedef struct coordenadas{
 int x;
 int y;
} coordenada;

coordenada ponerFicha (tateti t[3][3], int jugador, coordenada xy);
char **separarNombres(FILE *archivoEntrada);
int validarDominio (int arr[3][3]);
void copiarDominios(tateti origen[3][3], int destino[3][3]); 
void convertirComodines(int arr[3][3], int jugador);
void imprimirTableroConsola(tateti tablero[3][3]);
void imprimirTableroArchivo(FILE *archivo, tateti tablero[3][3]);
int validarGanador (tateti t[3][3], int jugador);