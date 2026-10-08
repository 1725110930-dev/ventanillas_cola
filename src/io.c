#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "io.h"

/* Descarta lo que quede de la linea cuando es mas larga que el buffer. */
static void descartarLineaRestante(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* se descarta */
    }
}

int leerTexto(char *destino, int tamano) {
    if (fgets(destino, tamano, stdin) == NULL) {
        return 0;
    }
    char *salto = strchr(destino, '\n');
    if (salto != NULL) {
        *salto = '\0';
    } else {
        descartarLineaRestante();
    }
    return 1;
}

/* Convierte una cadena a entero validando que solo contenga el numero. */
static int convertirEntero(const char *cadena, int *valor) {
    char *fin = NULL;
    long numero;

    errno = 0;
    numero = strtol(cadena, &fin, 10);
    if (cadena == fin || errno == ERANGE) {
        return 0;
    }
    /* Debe consumir toda la cadena (sin texto sobrante). */
    while (*fin != '\0') {
        if (*fin != ' ' && *fin != '\t' && *fin != '\n' && *fin != '\r') {
            return 0;
        }
        fin++;
    }
    if (numero < INT_MIN || numero > INT_MAX) {
        return 0;
    }
    *valor = (int)numero;
    return 1;
}

int leerEnteroRango(const char *mensaje, int minimo, int maximo, int *resultado) {
    char linea[32];
    int valor;

    while (1) {
        printf("%s", mensaje);
        if (!leerTexto(linea, sizeof(linea))) {
            return 0;
        }
        if (convertirEntero(linea, &valor) && valor >= minimo && valor <= maximo) {
            *resultado = valor;
            return 1;
        }
        printf("  Entrada no valida. Debe ser un entero entre %d y %d.\n",
               minimo, maximo);
    }
}

int leerTextoNoVacio(const char *mensaje, char *destino, int tamano) {
    while (1) {
        printf("%s", mensaje);
        if (!leerTexto(destino, tamano)) {
            return 0;
        }
        if (destino[0] != '\0') {
            return 1;
        }
        printf("  El campo no puede estar vacio.\n");
    }
}