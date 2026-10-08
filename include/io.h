#ifndef IO_H
#define IO_H

/* Lee una linea de texto (fgets) y le quita el salto de linea.
 * Retorna 1 si se pudo leer, 0 ante fin de entrada. */
int leerTexto(char *destino, int tamano);

/* Pide un entero dentro de [minimo, maximo] con validacion.
 * Retorna 1 si se capturo un valor valido, 0 ante fin de entrada. */
int leerEnteroRango(const char *mensaje, int minimo, int maximo, int *resultado);

/* Pide una cadena que no este vacia.
 * Retorna 1 si se capturo, 0 ante fin de entrada. */
int leerTextoNoVacio(const char *mensaje, char *destino, int tamano);

#endif /* IO_H */