#include <stdio.h>
#include <limits.h>
#include "sistema.h"
#include "io.h"

/* Muestra el submenu de seleccion de ventanilla. */
static void mostrarMenuVentanillas(void) {
    printf("\nSeleccione ventanilla:\n\n");
    for (int i = 1; i <= NUM_VENTANILLAS; i++) {
        printf("%d. Ventanilla %d\n", i, i);
    }
    printf("\n");
}

/* Pide y valida la ventanilla (1-6). Retorna 1 si se capturo, 0 si no. */
static int seleccionarVentanilla(int *ventanilla) {
    mostrarMenuVentanillas();
    return leerEnteroRango("Ventanilla (1-6): ", 1, NUM_VENTANILLAS, ventanilla);
}

void inicializarVentanillas(Cola ventanillas[NUM_VENTANILLAS]) {
    for (int i = 0; i < NUM_VENTANILLAS; i++) {
        inicializarCola(&ventanillas[i]);
    }
}

void agregarEstudiante(Cola ventanillas[NUM_VENTANILLAS]) {
    int ventanilla;
    Cola *cola;
    Estudiante estudiante;

    if (!seleccionarVentanilla(&ventanilla)) {
        return;
    }
    cola = &ventanillas[ventanilla - 1];

    if (colaLlena(cola)) {
        printf("La ventanilla %d esta llena; no se pudo agregar al estudiante.\n",
               ventanilla);
        return;
    }

    printf("\nDatos del estudiante:\n");
    if (!leerEnteroRango("  Matricula (entero positivo): ", 1, INT_MAX,
                         &estudiante.matricula)) {
        return;
    }
    if (!leerTextoNoVacio("  Nombre: ", estudiante.nombre,
                          sizeof(estudiante.nombre))) {
        return;
    }
    if (!leerTextoNoVacio("  Carrera: ", estudiante.carrera,
                          sizeof(estudiante.carrera))) {
        return;
    }
    if (!leerTextoNoVacio("  Tramite: ", estudiante.tramite,
                          sizeof(estudiante.tramite))) {
        return;
    }

    if (encolar(cola, estudiante)) {
        printf("\nEstudiante agregado a la ventanilla %d.\n", ventanilla);
    } else {
        printf("\nLa ventanilla %d estaba llena; no se pudo agregar.\n", ventanilla);
    }
}

void atenderEstudiante(Cola ventanillas[NUM_VENTANILLAS]) {
    int ventanilla;
    Cola *cola;
    Estudiante atendido;

    if (!seleccionarVentanilla(&ventanilla)) {
        return;
    }
    cola = &ventanillas[ventanilla - 1];

    if (desencolar(cola, &atendido)) {
        printf("\nEstudiante atendido en la ventanilla %d:\n", ventanilla);
        mostrarEstudiante(&atendido);
    } else {
        printf("La ventanilla %d no tiene estudiantes en espera.\n", ventanilla);
    }
}

void consultarProximoEstudiante(const Cola ventanillas[NUM_VENTANILLAS]) {
    int ventanilla;
    const Cola *cola;
    Estudiante proximo;

    if (!seleccionarVentanilla(&ventanilla)) {
        return;
    }
    cola = &ventanillas[ventanilla - 1];

    if (consultarProximo(cola, &proximo)) {
        printf("\nProximo estudiante en la ventanilla %d:\n", ventanilla);
        mostrarEstudiante(&proximo);
    } else {
        printf("La ventanilla %d no tiene estudiantes en espera.\n", ventanilla);
    }
}

void mostrarEstudiantesEnEspera(const Cola ventanillas[NUM_VENTANILLAS]) {
    int ventanilla;
    const Cola *cola;

    if (!seleccionarVentanilla(&ventanilla)) {
        return;
    }
    cola = &ventanillas[ventanilla - 1];

    printf("\nEstudiantes en espera (ventanilla %d):\n", ventanilla);
    mostrarCola(cola);
}

void mostrarCantidadEstudiantes(const Cola ventanillas[NUM_VENTANILLAS]) {
    int ventanilla;
    const Cola *cola;

    if (!seleccionarVentanilla(&ventanilla)) {
        return;
    }
    cola = &ventanillas[ventanilla - 1];

    printf("La ventanilla %d tiene %d estudiante(s) en espera.\n",
           ventanilla, cantidadEstudiantes(cola));
}

void consultarFilaVacia(const Cola ventanillas[NUM_VENTANILLAS]) {
    int ventanilla;
    const Cola *cola;

    if (!seleccionarVentanilla(&ventanilla)) {
        return;
    }
    cola = &ventanillas[ventanilla - 1];

    if (colaVacia(cola)) {
        printf("La ventanilla %d esta vacia (no hay estudiantes en espera).\n",
               ventanilla);
    } else {
        printf("La ventanilla %d NO esta vacia.\n", ventanilla);
    }
}

void mostrarEstadoVentanillas(const Cola ventanillas[NUM_VENTANILLAS]) {
    printf("\n=== Estado de las 6 ventanillas ===\n");
    for (int i = 0; i < NUM_VENTANILLAS; i++) {
        printf("Ventanilla %d: %d estudiante(s) en espera%s\n",
               i + 1,
               cantidadEstudiantes(&ventanillas[i]),
               colaVacia(&ventanillas[i]) ? " (fila vacia)" : "");
    }
}