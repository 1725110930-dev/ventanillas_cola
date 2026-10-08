#ifndef SISTEMA_H
#define SISTEMA_H

#include "cola.h"
#include "estudiante.h"

#define NUM_VENTANILLAS 6

/* Inicializa las 6 colas (una por ventanilla). */
void inicializarVentanillas(Cola ventanillas[NUM_VENTANILLAS]);

/* Operaciones pedidas por el menu. Cada una pide la ventanilla (1-6). */
void agregarEstudiante(Cola ventanillas[NUM_VENTANILLAS]);
void atenderEstudiante(Cola ventanillas[NUM_VENTANILLAS]);
void consultarProximoEstudiante(const Cola ventanillas[NUM_VENTANILLAS]);
void mostrarEstudiantesEnEspera(const Cola ventanillas[NUM_VENTANILLAS]);
void mostrarCantidadEstudiantes(const Cola ventanillas[NUM_VENTANILLAS]);
void consultarFilaVacia(const Cola ventanillas[NUM_VENTANILLAS]);
void mostrarEstadoVentanillas(const Cola ventanillas[NUM_VENTANILLAS]);

#endif /* SISTEMA_H */