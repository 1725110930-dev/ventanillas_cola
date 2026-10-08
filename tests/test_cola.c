#include <stdio.h>
#include <string.h>
#include "cola.h"

static int pruebas_pasadas = 0;
static int pruebas_fallidas = 0;

/* Crea un estudiante con datos de prueba. */
static Estudiante crearEstudiante(int matricula, const char *nombre) {
    Estudiante e;
    e.matricula = matricula;
    strcpy(e.nombre, nombre);
    strcpy(e.carrera, "Carrera");
    strcpy(e.tramite, "Tramite");
    return e;
}

/* Registra el resultado de una prueba. */
static void verificar(const char *nombre, int condicion) {
    if (condicion) {
        printf("[PASA]   %s\n", nombre);
        pruebas_pasadas++;
    } else {
        printf("[FALLA]  %s\n", nombre);
        pruebas_fallidas++;
    }
}

/* Consulta el frente y verifica su matricula. */
static void comprobarMatriculaFrente(Cola *cola, int matriculaEsperada) {
    Estudiante frente;
    if (consultarProximo(cola, &frente)) {
        verificar("Consultar el frente (matricula)", frente.matricula == matriculaEsperada);
    } else {
        verificar("Consultar el frente (matricula)", 0);
    }
}

int main(void) {
    /* 1 y 2. Inicializar y comprobar que esta vacia. */
    Cola cola;
    inicializarCola(&cola);
    verificar("Cola vacia tras inicializar", colaVacia(&cola));
    verificar("Cantidad 0 tras inicializar", cantidadEstudiantes(&cola) == 0);

    /* Consultar con cola vacia debe fallar. */
    {
        Estudiante e;
        verificar("Consultar proximo con cola vacia retorna 0", !consultarProximo(&cola, &e));
    }

    /* 3. Insertar un estudiante. */
    Estudiante a = crearEstudiante(1, "Ana");
    verificar("Encolar primer estudiante", encolar(&cola, a));
    verificar("Cola ya no esta vacia", !colaVacia(&cola));
    verificar("Cantidad es 1", cantidadEstudiantes(&cola) == 1);
    comprobarMatriculaFrente(&cola, 1);

    /* 4. Insertar varios estudiantes. */
    verificar("Encolar segundo", encolar(&cola, crearEstudiante(2, "Bruno")));
    verificar("Encolar tercero", encolar(&cola, crearEstudiante(3, "Carla")));
    verificar("Encolar cuarto", encolar(&cola, crearEstudiante(4, "Diego")));
    verificar("Encolar quinto", encolar(&cola, crearEstudiante(5, "Elena")));

    /* 8. Llenar la cola. */
    verificar("Cola llena", colaLlena(&cola));
    verificar("Cantidad es MAX_ESTUDIANTES", cantidadEstudiantes(&cola) == MAX_ESTUDIANTES);

    /* 9. Intentar insertar cuando esta llena. */
    verificar("Encolar con cola llena retorna 0", !encolar(&cola, crearEstudiante(6, "Fabián")));
    verificar("Cantidad no cambio", cantidadEstudiantes(&cola) == MAX_ESTUDIANTES);

    /* 5 y 6. Consultar no elimina; atender si elimina. */
    comprobarMatriculaFrente(&cola, 1);
    {   Estudiante atendido;
        verificar("Atender al frente", desencolar(&cola, &atendido));
        verificar("Primero en salir (matricula 1)", atendido.matricula == 1);
        comprobarMatriculaFrente(&cola, 2);
        verificar("Desencolar no desplazo elementos (frente=1)", cola.frente == 1);
    }
    {   Estudiante atendido;
        desencolar(&cola, &atendido);
        verificar("Segundo en salir (matricula 2)", atendido.matricula == 2);
    }

    /* 12. Estado circular: frente > 0 y final < frente. */
    verificar("Encolar da la vuelta al arreglo", encolar(&cola, crearEstudiante(6, "Fabián")));
    verificar("Encolar da la vuelta al arreglo", encolar(&cola, crearEstudiante(7, "Gabriela")));
    verificar("Estado circular: frente=2, final=1, cantidad=5",
              cola.frente == 2 && cola.final == 1 && cola.cantidad == 5);
    verificar("Cola llena de nuevo", colaLlena(&cola));

    /* 10 y 11. Vaciar respetando FIFO a traves del giro circular. */
    {
        int ordenCorrecto = 1;
        int esperado[5] = {3, 4, 5, 6, 7};
        for (int i = 0; i < 5 && ordenCorrecto; i++) {
            Estudiante atendido;
            ordenCorrecto = desencolar(&cola, &atendido) && atendido.matricula == esperado[i];
        }
        verificar("FIFO en giro circular (salen 3,4,5,6,7)", ordenCorrecto);
        verificar("Cola vacia tras atender a todos", colaVacia(&cola));
    }

    /* 11. Atender con cola vacia debe fallar. */
    {
        Estudiante atendido;
        verificar("Desencolar con cola vacia retorna 0", !desencolar(&cola, &atendido));
    }

    printf("\nResultado: %d pasadas, %d fallidas\n", pruebas_pasadas, pruebas_fallidas);
    return pruebas_fallidas == 0 ? 0 : 1;
}