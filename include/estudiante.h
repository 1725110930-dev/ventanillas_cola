#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

/* Estudiante que espera ser atendido en una ventanilla. */
typedef struct {
    int matricula;
    char nombre[100];
    char carrera[100];
    char tramite[100];
} Estudiante;

/* Imprime todos los campos de un estudiante. */
void mostrarEstudiante(const Estudiante *estudiante);

#endif /* ESTUDIANTE_H */