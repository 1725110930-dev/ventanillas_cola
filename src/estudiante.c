#include <stdio.h>
#include "estudiante.h"

void mostrarEstudiante(const Estudiante *estudiante) {
    printf("Matricula: %d\n", estudiante->matricula);
    printf("Nombre:    %s\n", estudiante->nombre);
    printf("Carrera:   %s\n", estudiante->carrera);
    printf("Tramite:   %s\n", estudiante->tramite);
}