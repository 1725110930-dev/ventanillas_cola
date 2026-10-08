# Servicios Escolares — Sistema de Ventanillas con Colas (FIFO)

Sistema academico en C que administra la atencion de estudiantes en **6 ventanillas
de Servicios Escolares**. Cada ventanilla mantiene su propia cola de estudiantes y
los atiende en el **mismo orden en que llegaron** (principio **FIFO**).

La estructura principal es una **cola implementada con un arreglo circular**, que
aprovecha los espacios libres al inicio del arreglo sin desplazar elementos.

---

## 1. Descripcion del problema

Una institucion educativa tiene 6 ventanillas de Servicios Escolares. Los estudiantes
llegan, forman fila y deben ser atendidos en orden de llegada. El sistema permite:

- **Agregar** un estudiante al final de una fila.
- **Atender** al estudiante que esta al frente (se elimina de la cola).
- **Consultar** el proximo estudiante sin eliminarlo.
- **Mostrar** todos los estudiantes en espera (respetando FIFO).
- **Contar** cuantos estudiantes esperan en una ventanilla.
- **Indicar** si una fila esta vacia.
- **Ver** el estado de las 6 ventanillas.

Cada estudiante tiene:

| Campo     | Tipo  | Descripcion                          |
|-----------|-------|--------------------------------------|
| matricula | int   | Numero de matricula (entero positivo)|
| nombre    | char[100] | Nombre completo del estudiante   |
| carrera   | char[100] | Carrera que cursa                 |
| tramite   | char[100] | Tramite que va a realizar         |

---

## 2. Estructura de datos: cola con arreglo circular

La cola es un arreglo fijo de estudiantes con tres variables de control:

```c
typedef struct {
    Estudiante estudiantes[MAX_ESTUDIANTES]; /* arreglo estatico          */
    int frente;                               /* indice del primer en salir */
    int final;                                /* indice del ultimo en llegar */
    int cantidad;                             /* cuantos hay en la cola      */
} Cola;
```

### Logica de `frente`, `final` y `cantidad`

- **`frente`**: apunta al estudiante mas antiguo (el siguiente en ser atendido).
- **`final`**: apunta al estudiante mas reciente (donde se agregan los nuevos).
- **`cantidad`**: numero de elementos actuales. Evita la ambiguedad entre una cola
  vacia y una llena que tendria un implementacion solo con `frente` y `final`.

### Movimiento circular

Cuando `final` (o `frente`) llega al ultimo indice, vuelve a **0** usando el modulo:

```c
final  = (final  + 1) % MAX_ESTUDIANTES;   /* al encolar  */
frente = (frente + 1) % MAX_ESTUDIANTES;   /* al desencolar */
```

### Condiciones

- Cola **vacia**: `cantidad == 0`
- Cola **llena**: `cantidad == MAX_ESTUDIANTES` (valor por defecto **100**)

### Ejemplo de giro circular (con `MAX_ESTUDIANTES = 5`)

```
Estado: frente = 2, final = 1, cantidad = 5
[ F | G | C | D | E ]
  0   1   2   3   4
       ↑final  ↑frente
```

Se agrego a F y G cuando la cola todavia tenia espacio al principio, por lo que
`final (1) < frente (2)`. El orden de atencion es C, D, E, F, G: se demuestra que
el arreglo dio la vuelta sin desplazar ningun elemento.

### Las 6 ventanillas

El sistema declara un arreglo de 6 colas, una por ventanilla:

```c
#define NUM_VENTANILLAS 6
Cola ventanillas[NUM_VENTANILLAS];   /* indices 0 a 5 */
```

El usuario elige ventanilla del 1 al 6 y el programa accede al indice `ventanilla - 1`.
Cada cola es independiente.

---

## 3. Arquitectura del proyecto

```
structData/
├── include/
│   ├── estudiante.h   # Definicion de Estudiante y mostrarEstudiante
│   ├── cola.h         # Definicion de Cola y operaciones de la cola
│   ├── io.h           # Entrada segura (fgets): texto no vacio y enteros por rango
│   └── sistema.h      # Operaciones de las 6 ventanillas (menu de consola)
├── src/
│   ├── estudiante.c   # Implementacion de mostrarEstudiante
│   ├── cola.c         # Implementacion de la cola circular
│   ├── io.c           # Implementacion de la entrada segura
│   ├── sistema.c      # Operaciones de ventanillas
│   └── main.c         # Menu principal
├── tests/
│   └── test_cola.c    # Pruebas unitarias del modulo Cola
├── Makefile
└── README.md
```

### Funciones de la cola (`cola.h`)

| Funcion                                     | Retorna | Descripcion                            |
|---------------------------------------------|---------|----------------------------------------|
| `void inicializarCola(Cola *cola)`          | —       | Deja la cola vacia                     |
| `int colaVacia(const Cola *cola)`           | 1/0     | 1 si no hay estudiantes                |
| `int colaLlena(const Cola *cola)`           | 1/0     | 1 si no cabe otro estudiante           |
| `int encolar(Cola *cola, Estudiante e)`     | 1/0     | Agrega al final; 0 si esta llena       |
| `int desencolar(Cola *cola, Estudiante *e)` | 1/0     | Retira el frente; 0 si esta vacia      |
| `int consultarProximo(const Cola*, Estudiante*)` | 1/0 | Consulta sin retirar |             |
| `void mostrarCola(const Cola *cola)`        | —       | Imprime en orden FIFO                  |
| `int cantidadEstudiantes(const Cola *cola)` | int     | Cuantos esperan                        |

Los valores de retorno `1/0` permiten detectar **operacion exitosa**, **cola vacia**
o **cola llena** sin comportamiento indefinido.

---

## 4. Compilacion y ejecucion

Requisitos: `gcc` (GCC 4.9 o superior es suficiente; usa solo C estandar).

```bash
make          # compila el programa en build/servicios_escolares
make run      # compila y ejecuta el menu de consola
make test     # compila y ejecuta las pruebas del modulo Cola
make clean    # elimina la carpeta build
```

La compilacion usa advertencias estrictas:

```bash
-Wall -Wextra -Wpedantic
```

### Menu principal

```
========================================
       SERVICIOS ESCOLARES
========================================

1. Agregar estudiante
2. Atender estudiante
3. Consultar proximo estudiante
4. Mostrar estudiantes en espera
5. Mostrar cantidad de estudiantes
6. Consultar si la fila esta vacia
7. Mostrar estado de las 6 ventanillas
8. Salir

Seleccione una opcion:
```

Toda operacion sobre una ventanilla muestra primero el submenu de seleccion:

```
Seleccione ventanilla:

1. Ventanilla 1
2. Ventanilla 2
3. Ventanilla 3
4. Ventanilla 4
5. Ventanilla 5
6. Ventanilla 6

Ventanilla (1-6):
```

### Validaciones

- Ventanilla obligatoriamente entre **1 y 6**.
- Matricula: entero positivo (se valida el rango).
- Nombre, carrera y tramite: no pueden estar vacios.
- No se inserta si la cola esta llena (mensaje claro).
- No se atiende ni se consulta si la cola esta vacia (mensaje claro).
- Toda la entrada se lee con `fgets`, evitando los problemas de `scanf` al mezclar
  numeros y cadenas.

---

## 5. Pruebas

### Pruebas unitarias del modulo Cola (`make test`)

Automatizan el comportamiento de la estructura de datos. Son **28 verificaciones**
que comprueban, entre otras:

1. Inicializacion de una cola.
2. Cola vacia.
3. Insertar un estudiante.
4. Insertar varios estudiantes.
5. Consultar el primero sin eliminarlo.
6. Atender el primero.
7. Respeto del orden FIFO.
8. Llenar la cola.
9. Intentar insertar cuando esta llena.
10. Vaciar la cola.
11. Intentar atender cuando esta vacia.
12. **Comportamiento circular** del arreglo: se llega al estado
    `frente = 2, final = 1` y se verifica que al vaciar salen las matricula
    3, 4, 5, 6, 7 (los ultimos dos vienen de los indices 0 y 1, que ya habian
    quedado libres).

Para hacer estas pruebas practicas, la cola de prueba se compila con
`-DMAX_ESTUDIANTES=5`; el programa real usa el valor por defecto `100`.

### Guia de prueba manual (para presentar al profesor)

Secuencia de menor a mayor complejidad:

1. **Inicio**: opcion 7 → las 6 ventanillas aparecen vacias (0 estudiantes).
2. **Error con cola vacia**: opciones 2, 3 y 6 sobre cualquier ventanilla
   → mensaje indicando que no hay estudiantes.
3. **Ventanilla invalida**: al pedir ventanilla, escribir `0`, `7` o letras
   → el sistema rechaza y vuelve a pedir hasta que el valor sea 1–6.
4. **Agregar**: opcion 1, ventanilla 1. Capturar matricula, nombre, carrera y
   tramite. Probar matricula no numerica (debe rechazarse) y campos vacios
   (deben rechazarse).
5. **FIFO**: agregar 3 estudiantes (A, B, C) en la ventanilla 1. Opcion 3
   → muestra a A. Opcion 4 → muestra A, B, C en ese orden. Opcion 5 → 3.
6. **Atender**: opcion 2 → atiende a A y lo muestra. Consultar nuevamente
   (opcion 3) → ahora es B. Opcion 5 → 2.
7. **Cola vacia tras atender**: atender hasta agotar; la opcion 2 debe
   informar que la ventanilla no tiene estudiantes.
8. **Varias ventanillas**: agregar estudiantes en las ventanillas 1, 3 y 6;
   opcion 7 → cada ventanilla muestra su cantidad y las demas siguen vacias.
9. **Cola llena** (opcional, requiere 100 estudiantes o recompilar con
   `-DMAX_ESTUDIANTES=5` en el programa): al intentar agregar cuando esta llena,
   el sistema informa que no se pudo.
10. **Salir**: opcion 8 termina el programa.

---

## 6. Objetivo academico

El proyecto practica:

- Estructuras `struct`.
- Colas y principio **FIFO**.
- Arreglos y **arreglos circulares**.
- Funciones, punteros y paso de arreglos por referencia.
- Modularizacion (`include/` + `src/`).
- Validacion de entrada con `fgets`.
- Compilacion con GCC y advertencias estrictas.
- Manejo de errores mediante valores de retorno.