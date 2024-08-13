#include "tateti.h"

int main(void) {

  tateti tablero[3][3];
    coordenada valor;

    // Inicializar el tablero
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j].dominio = 0;
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    tablero[i][j].arr[k][l] = 0;
                }
            }
        }
    }

    //archivoEntrada es el archivo que contiene los nombres de los jugadores
    //archivoSalida es el archivo que contiene los resultados de la partida(nombre del ganador y tablero)
    
    FILE *archivoEntrada = fopen("nombres.txt", "r+");
      if (archivoEntrada == NULL) {
        printf("No se pudo abrir el archivo");
        return 1;
      }
    
    char **nombres = separarNombres(archivoEntrada);

    FILE *archivoSalida = fopen("resultado.txt", "w+");
    if(archivoSalida == NULL){
        printf("No se pudo abrir el archivo de salida");
        return 1;
    }
    //usar fprintf para escribir en el archivo, necesitaria utilizar la funcion de imprimir tablero

    int jugador = rand() % 2 ? 1 : 2; //El jugador que empieza es aleatorio
    printf("\nEs el turno de %s", jugador == 1 ? nombres[0] : nombres[1]);
    printf("Ingrese tablero a jugar, ponga coordenada X Y: ");
    scanf("%d %d", &valor.x, &valor.y);

    int ganador = 0;
    int bandera = 1;
    while (bandera){
        if (tablero[valor.x][valor.y].dominio == 0){
            valor = (ponerFicha (tablero, jugador, valor));
            ganador = validarGanador(tablero,jugador);
            if (ganador)
              bandera = 0;
            jugador = (jugador == 1) ? 2 : 1; //Va cambiando de jugador
            imprimirTableroConsola(tablero);
            printf("\nEs el turno de %s", jugador == 1 ? nombres[0] : nombres[1]);
        }
        else{
            printf("Coordenada ocupada o invalida, ingrese otra: ");
            scanf("%d %d", &valor.x, &valor.y);
        }
    }

    if (ganador == 3) {
        fprintf(archivoSalida, "Hubo empate\n");
        printf("Hubo empate\n");
    } else {
        fprintf(archivoSalida, "El ganador es el jugador %s\n", ganador == 1 ? nombres[0] : nombres[1]);
        printf("El ganador es el jugador %s\n", ganador == 1 ? nombres[0] : nombres[1]);
    }

    fprintf(archivoSalida, "\nTablero final:\n");
    imprimirTableroArchivo(archivoSalida, tablero);

    fclose(archivoSalida);

    //Libero Memoria
    free(nombres[0]);
    free(nombres[1]);
    free(nombres);


  return 0;
}

coordenada ponerFicha (tateti t[3][3], int jugador, coordenada xy){
    coordenada casilla;
    printf("Ingrese casilla a jugar (Coordenadas X Y): ");
    scanf("%d %d", &casilla.x, &casilla.y);

    int bandera = 1;
    while (bandera){
        if (t[xy.x][xy.y].arr[casilla.x][casilla.y] == 0){
            t[xy.x][xy.y].arr[casilla.x][casilla.y] = jugador;
            t[xy.x][xy.y].dominio = validarDominio(t[xy.x][xy.y].arr);
            bandera = 0;
        }
        else{
            printf("Casilla Ocupada, ingrese otra: ");
            scanf("%d %d", &casilla.x, &casilla.y);
        }
    }
    return casilla;
}

int validarDominio (int arr[3][3]){
    for (int i = 0; i < 3; i++){
        //laterales
        if (arr[i][0] != 0 && arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2])
            return arr[i][0];

        //verticales
        if (arr[0][i] != 0 && arr[0][i] == arr[1][i] && arr[1][i] ==arr[2][i])
                return arr[0][i];
    }

    //diagonales
    if (arr[0][0] != 0 && arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2])
        return arr[1][1];

    if (arr[0][2] != 0 && arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0])
        return arr[1][1];

    //caso empate
    //No cambiar si no hay ninguna de las anteriores

    int contadorCero = 0; //cuenta la cantidad de ceros
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(arr[i][j] == 0){
                contadorCero++;
            }
        }
    }

    if(contadorCero == 0)
        return 3;

    //Ninguna de las anteriores
    return 0;
}


void imprimirTableroConsola(tateti tablero[3][3]) {
    for (int bigRow = 0; bigRow < 3; bigRow++) {
        for (int smallRow = 0; smallRow < 3; smallRow++) {
            for (int bigCol = 0; bigCol < 3; bigCol++) {
                for (int smallCol = 0; smallCol < 3; smallCol++) {
                    int value = tablero[bigRow][bigCol].arr[smallRow][smallCol];
                    if (value == 0) {
                        printf(".");
                    } else if (value == 1) {
                        printf("X");
                    } else if (value == 2) {
                        printf("O");
                    } else {
                        printf("?");
                    }
                }
                if (bigCol < 2) {
                    printf(" | ");
                }
            }
            printf("\n");
        }
        if (bigRow < 2) {
            printf("----------------\n");
        }
    }
}

void imprimirTableroArchivo(FILE *archivo, tateti tablero[3][3]) {
    for (int bigRow = 0; bigRow < 3; bigRow++) {
        for (int smallRow = 0; smallRow < 3; smallRow++) {
            for (int bigCol = 0; bigCol < 3; bigCol++) {
                for (int smallCol = 0; smallCol < 3; smallCol++) {
                    int value = tablero[bigRow][bigCol].arr[smallRow][smallCol];
                    if (value == 0) {
                        fprintf(archivo, ".");
                    } else if (value == 1) {
                        fprintf(archivo, "X");
                    } else if (value == 2) {
                        fprintf(archivo, "O");
                    } else {
                        fprintf(archivo, "?");
                    }
                }
                if (bigCol < 2) {
                    fprintf(archivo, " | ");
                }
            }
            fprintf(archivo, "\n");
        }
        if (bigRow < 2) {
            fprintf(archivo, "----------------\n");
        }
    }
}

void copiarDominios(tateti origen[3][3], int destino[3][3]) {
    for (int i = 0; i < 3; i++){
      for (int j = 0; j < 3; j++){
        destino[i][j] = origen[i][j].dominio;
      }
    }

}


void convertirComodines(int arr[3][3], int jugador) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == 3) {
                arr[i][j] = jugador;
            }
        }
    }
}

int validarGanador (tateti t[3][3], int jugador){
  int aux[3][3];
  copiarDominios(t, aux);
  convertirComodines(aux, jugador);
  return validarDominio(aux);
}

char **separarNombres(FILE *archivoEntrada){
    char nombres[100];
    fread(nombres, sizeof(char), 100, archivoEntrada);
    fclose(archivoEntrada);

    char **palabras = (char **)malloc(2 * sizeof(char *));
    int i = 0, j = 0;
    char buffer[30];

    for (; nombres[i] != '\n' && nombres[i] != '\0'; i++) {
        buffer[i] = nombres[i];
    }
    buffer[i] = '\n';
    buffer[i+1] = '\0';
    palabras[0] = malloc (sizeof(char) * strlen(buffer) + 1);
    strcpy (palabras[0], buffer);

    if (nombres[i] == '\n') {
        i++;
    }

    for (; nombres[i] != '\0'; i++, j++) {
        buffer[j] = nombres[i];
    }
    buffer[j] = '\0';
    palabras[1] = malloc (sizeof(char) * strlen(buffer) + 1);
    strcpy (palabras[1], buffer);

    return palabras;
}