#include <stdio.h>
#include "cola.h"

void inicializarCola(Cola *cola) {
    cola->frente = 0;
    cola->final = -1;
    cola->cantidad = 0;
}

int colaVacia(const Cola *cola) {
    return cola->cantidad == 0;
}

int colaLlena(const Cola *cola) {
    return cola->cantidad == MAX_ESTUDIANTES;
}

int encolar(Cola *cola, Estudiante estudiante) {
    if (colaLlena(cola)) {
        return 0;
    }
    /* Avanza de forma circular: si final era el último índice, vuelve a 0. */
    cola->final = (cola->final + 1) % MAX_ESTUDIANTES;
    cola->estudiantes[cola->final] = estudiante;
    cola->cantidad++;
    return 1;
}

int desencolar(Cola *cola, Estudiante *estudiante) {
    if (colaVacia(cola)) {
        return 0;
    }
    *estudiante = cola->estudiantes[cola->frente];
    /* Avanza de forma circular: si frente era el último índice, vuelve a 0. */
    cola->frente = (cola->frente + 1) % MAX_ESTUDIANTES;
    cola->cantidad--;
    return 1;
}

int consultarProximo(const Cola *cola, Estudiante *estudiante) {
    if (colaVacia(cola)) {
        return 0;
    }
    *estudiante = cola->estudiantes[cola->frente];
    return 1;
}

void mostrarCola(const Cola *cola) {
    if (colaVacia(cola)) {
        printf("La cola esta vacia.\n");
        return;
    }
    /* Recorre desde frente hasta cubrir la cantidad de elementos. */
    for (int i = 0; i < cola->cantidad; i++) {
        int indice = (cola->frente + i) % MAX_ESTUDIANTES;
        printf("%d. ", i + 1);
        mostrarEstudiante(&cola->estudiantes[indice]);
    }
}

int cantidadEstudiantes(const Cola *cola) {
    return cola->cantidad;
}