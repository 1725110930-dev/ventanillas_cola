#include <stdio.h>
#include "sistema.h"
#include "io.h"

int main(void) {
    Cola ventanillas[NUM_VENTANILLAS];
    int opcion;

    inicializarVentanillas(ventanillas);

    do {
        printf("\n========================================\n");
        printf("       SERVICIOS ESCOLARES\n");
        printf("========================================\n\n");
        printf("1. Agregar estudiante\n");
        printf("2. Atender estudiante\n");
        printf("3. Consultar proximo estudiante\n");
        printf("4. Mostrar estudiantes en espera\n");
        printf("5. Mostrar cantidad de estudiantes\n");
        printf("6. Consultar si la fila esta vacia\n");
        printf("7. Mostrar estado de las 6 ventanillas\n");
        printf("8. Salir\n\n");

        if (!leerEnteroRango("Seleccione una opcion: ", 1, 8, &opcion)) {
            break;
        }

        switch (opcion) {
            case 1:
                agregarEstudiante(ventanillas);
                break;
            case 2:
                atenderEstudiante(ventanillas);
                break;
            case 3:
                consultarProximoEstudiante(ventanillas);
                break;
            case 4:
                mostrarEstudiantesEnEspera(ventanillas);
                break;
            case 5:
                mostrarCantidadEstudiantes(ventanillas);
                break;
            case 6:
                consultarFilaVacia(ventanillas);
                break;
            case 7:
                mostrarEstadoVentanillas(ventanillas);
                break;
            case 8:
                printf("Gracias por usar el sistema.\n");
                break;
            default:
                break;
        }
    } while (opcion != 8);

    return 0;
}