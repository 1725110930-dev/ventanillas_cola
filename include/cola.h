#ifndef COLA_H
#define COLA_H

#include "estudiante.h"

/* Tamano del arreglo circular de cada cola.
 * Por defecto 100; en las pruebas se redefine con -DMAX_ESTUDIANTES=5
 * para poder llenarla facilmente. */
#ifndef MAX_ESTUDIANTES
#define MAX_ESTUDIANTES 100
#endif

/* Cola de estudiantes implementada con arreglo circular.
 *
 * frente : índice del elemento más antiguo (primero en salir).
 * final  : índice del elemento más reciente (último en llegar).
 * cantidad: número de elementos actualmente en la cola.
 */
typedef struct {
    Estudiante estudiantes[MAX_ESTUDIANTES];
    int frente;
    int final;
    int cantidad;
} Cola;

/* Deja la cola vacía: frente = 0, final = -1, cantidad = 0. */
void inicializarCola(Cola *cola);

/* Retorna 1 si la cola está vacía, 0 en caso contrario. */
int colaVacia(const Cola *cola);

/* Retorna 1 si la cola está llena, 0 en caso contrario. */
int colaLlena(const Cola *cola);

/* Agrega un estudiante al final de la cola.
 * Retorna 1 si tuvo éxito, 0 si la cola estaba llena. */
int encolar(Cola *cola, Estudiante estudiante);

/* Retira el estudiante del frente y lo devuelve por el puntero.
 * Retorna 1 si tuvo éxito, 0 si la cola estaba vacía. */
int desencolar(Cola *cola, Estudiante *estudiante);

/* Copia el estudiante del frente sin retirarlo.
 * Retorna 1 si tuvo éxito, 0 si la cola estaba vacía. */
int consultarProximo(const Cola *cola, Estudiante *estudiante);

/* Muestra los estudiantes de la cola en orden FIFO. */
void mostrarCola(const Cola *cola);

/* Retorna cuántos estudiantes hay esperando. */
int cantidadEstudiantes(const Cola *cola);

#endif /* COLA_H */