-- Ignacio Giovannetti, Mateo Giovannetti

# Compilación

> gcc tateti.c -o tateti

# Ejecución

> ./tateti nombres.txt resultado.txt

El archivo de entrada tendra los dos nombres de los jugadores separados tanto por un *Enter* . El archivo de salida mostrara el ganador y el tablero resultante. 

# ¿Cómo Jugar?

El jugador que empieza al ejecutar el juego es aleatorio. En cada turno, el jugador correspondiente debera de jugar en el tablero que fue mandado o si esta ocupado se le pedira que ingrese las coordenadas del tablero a jugar. Una vez en el tablero debera ingresar la casilla donde quiera ingresar la ficha.

Las coordenadas escritas por el usuario son las mismas que las de un arreglo bidimensional. X (Filas) Y (Columnas)

# Representacion de Datos

- Una **estructura tateti** que representa un tablero menor, en sus miembros se encuentra un arreglo bidimensional 3x3 que imita un tablero de tateti. Ademas, tiene un dominio que indica cual es su estado.
    - 0 -> En progreso
    - 1 -> Ganó Jugador 1
    - 2 -> Ganó Jugador 2
    - 3 -> Hubo Empate

- Una **estructura Coordena** que representa las coordenadas en un plano segun los ejes X e Y.
- El **tablero** es el espacio donde se va a jugar. Este es un arreglo bidimensional 3x3 de estructuras de tateti.

# Lectura del código por primera vez

Se recomienda para una mayor legibilidad primero leer las estructuras, luego leer el main y luego leer las funciones que son llamadas respectivamente.

# Lógica y Explicación del código

Las funciones que son aplicadas en el programa y su funcionamiento es el siguiente:

- **ponerFicha:** Esta funcion va a tomar como parametro el Tablero_Grande, el jugador y la coordena del Tablero_Chico a jugar. Va a pedir en que coordenadas del Tablero_Chico quiere poner su ficha, si es posbible lo hace y devuele las coordenadas pedidas. De lo contrario pide que ingrese nuevamente unas coordenadas

- **separarNombres:** Toma el archivo de los nombres y retorna los nombres en un puntero a puntero.

- **validarDominio:** Esta funcion toma un arreglo bidimensional 3x3 y dice cual es su ganador o si hubo empate.

- **imprimirTableroConsola:** Pone en pantalla el tablero que se esta jugando en la consola

- **imprimirTableroArchivo:** Pone el tablero ya finalizado en un archivo

- **copiarDominios:** Toma los dominios de los distintas estructuras y lo pasa a un  arreglo bidimensional auxiliar

- **convertirComodines:** Toma un arreglo bidimensional y el jugador que esta jugando. Transorma los empates que se usan como comodines para que puedan ser útiles para formar patrones

- **validarGanador:** Según el Tablero_Grande y el jugador, determina cual es el ganador final.

# Main

Para encarar el problema lo tomamos desde el main. En este pediremos para comenzar que se ingrese el Tablero_Chico que se va a jugar. Luego inicia un *while* que va a preguntar si el Tablero_Chico que se quiere jugar esta disponible por medio del dominio, si es verdadero podremos poner la ficha y guardar sus coordenadas. A la vez, se va a validar el ganador, cambiar el jugador e imprimir tablero. En el caso de que sea falso, esto sucedería probablemente porque las coordenadas de la casilla que guardamos ya estan ocupadas, entonces vamos a pedir que las ingrese nuevamente. La unica manera de salir del bucle va a ser cuando haya un ganador.