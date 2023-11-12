#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMEROS_LOTERIA 3
#define MAX_NUMERO 99
#define MAX_HISTORIAL 10

struct Registro {
    int numerosGanadores[NUMEROS_LOTERIA];
    struct tm tiempo;
};

void imprimirHistorial(struct Registro historial[], int cantidad) {
    printf("\nHistorial de números:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%d. %d, %d, %d - %02d-%02d-%04d %02d:%02d:%02d\n", i + 1,
               historial[i].numerosGanadores[0], historial[i].numerosGanadores[1], historial[i].numerosGanadores[2],
               historial[i].tiempo.tm_mday, historial[i].tiempo.tm_mon + 1, historial[i].tiempo.tm_year + 1900,
               historial[i].tiempo.tm_hour, historial[i].tiempo.tm_min, historial[i].tiempo.tm_sec);
    }
    printf("\n");
}

int main() {
    int opcion;
    struct Registro historial[MAX_HISTORIAL];
    int contadorHistorial = 0;
    int montoApostado;
    int numeroApostado;
    int resultadoJuego;
    double probabilidadGanar = 0.4; // 40% de probabilidad de ganar

    // Inicializar el generador de números aleatorios con el tiempo actual
    srand(time(NULL));

    do {
        // Menú
        printf("Bienvenido a Loteria La Chocha\n");
        printf("1. Tirar\n");
        printf("2. Imprimir historial\n");
        printf("3. Jugar\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Tirar números aleatorios
                printf("\nNúmeros ganadores (Loteria La Chocha): ");
                for (int i = 0; i < NUMEROS_LOTERIA; i++) {
                    historial[contadorHistorial].numerosGanadores[i] = 1 + rand() % MAX_NUMERO;
                    printf("%d ", historial[contadorHistorial].numerosGanadores[i]);
                }
                printf("- ");

                // Obtener la fecha y hora actual
                time_t t = time(NULL);
                historial[contadorHistorial].tiempo = *localtime(&t);

                printf("%02d-%02d-%04d %02d:%02d:%02d\n",
                       historial[contadorHistorial].tiempo.tm_mday, historial[contadorHistorial].tiempo.tm_mon + 1,
                       historial[contadorHistorial].tiempo.tm_year + 1900, historial[contadorHistorial].tiempo.tm_hour,
                       historial[contadorHistorial].tiempo.tm_min, historial[contadorHistorial].tiempo.tm_sec);

                // Incrementar el contador del historial
                contadorHistorial = (contadorHistorial + 1) % MAX_HISTORIAL;
                break;

            case 2:
                // Imprimir historial
                imprimirHistorial(historial, contadorHistorial);
                break;

            case 3:
                // Opciones de juego
                printf("Seleccione una opción de juego:\n");
                printf("1. Jugar un número\n");
                printf("2. Pale\n");
                printf("3. Tripleta\n");
                printf("0. Volver al menú principal\n");
                printf("Seleccione una opción: ");
                scanf("%d", &opcion);

                switch (opcion) {
                    case 1:
                    case 2:
                    case 3:
                        // Apostar un monto
                        printf("Ingrese el monto a apostar: $");
                        scanf("%d", &montoApostado);

                        // Apostar un número
                        if (opcion == 1) {
                            printf("Ingrese el número a apostar (1-%d): ", MAX_NUMERO);
                            scanf("%d", &numeroApostado);
                        } else {
                            // Apostar dos o tres números (pale o tripleta)
                            printf("Ingrese el primer número a apostar (1-%d): ", MAX_NUMERO);
                            scanf("%d", &numeroApostado);
                        }

                        // Simular el juego
                        if ((rand() % 100) < probabilidadGanar * 100) {
                            printf("¡Felicidades! Has ganado $%d\n", montoApostado * 50);
                        } else {
                            printf("Lo siento, has perdido $%d\n", montoApostado);
                        }
                        break;

                    case 0:
                        // Volver al menú principal
                        break;

                    default:
                        printf("Opción no válida. Por favor, ingrese 0, 1, 2 o 3.\n");
                        break;
                }
                break;

            case 0:
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;

            default:
                printf("Opción no válida. Por favor, ingrese 0, 1, 2 o 3.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
