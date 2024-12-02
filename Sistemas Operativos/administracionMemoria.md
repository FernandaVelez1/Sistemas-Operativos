# SISTEMAS OPERATIVOS
    Alumna: FERNANDA ELIZABETH VÉLEZ ALEJANDRE (22121321)

## ADMINISTRACIÓN DE MEMORIA

### 3.1 Política y Filosofía

#### **Diferencia entre fragmentación interna y externa**

- **Fragmentación interna:**  Ocurre cuando se asigna más memoria de la necesaria a un proceso debido al tamaño fijo de las particiones o bloques de memoria. Esto genera espacios inutilizados dentro de las particiones asignadas.  
    - **Ejemplo:** Si un bloque tiene 4 KB pero el proceso solo necesita 3.5 KB, los 0.5 KB restantes están desperdiciados.  
    - **Impacto:** Disminuye el rendimiento al reducir la memoria disponible, aunque técnicamente haya espacio libre.

- **Fragmentación externa:**  Ocurre cuando hay espacios libres en memoria que son insuficientes para satisfacer la solicitud de un nuevo proceso, aunque la memoria total libre podría ser suficiente.  
    - **Ejemplo:** Tres bloques libres de 2 KB, 1 KB y 3 KB, pero no pueden acomodar un proceso que necesita 5 KB.  
    - **Impacto:** Genera espacios inutilizables y obliga al sistema a realizar compactación o reemplazos costosos.
---
---
#### **Políticas de reemplazo de páginas**

Las políticas de reemplazo de páginas son estrategias utilizadas para decidir qué página de la memoria será reemplazada cuando no hay espacio disponible para cargar una nueva página. Estas políticas son esenciales para la gestión de memoria virtual, donde las páginas se transfieren entre la memoria principal y el almacenamiento secundario (generalmente el disco) para garantizar el correcto funcionamiento de los programas.

1. **FIFO (First-In-First-Out):**  Se reemplaza la página más antigua en memoria.  
   - **Ventaja:** Fácil de implementar.  
   - **Desventaja:** Puede generar problemas como "anomalías de Belady".

2. **LRU (Least Recently Used):**  Se reemplaza la página que no ha sido usada durante más tiempo.  
   - **Ventaja:** Mejor rendimiento en la mayoría de los casos.  
   - **Desventaja:** Requiere mayor complejidad y uso de estructuras como pilas o conteos de tiempo.

3. **Optimal (OPT):**  Se reemplaza la página que no será utilizada por el mayor tiempo en el futuro.  
   - **Ventaja:** Es el más eficiente.  
   - **Desventaja:** No es realizable en tiempo real porque requiere conocimiento previo de los accesos.

4. **Clock (Second Chance):**  Variación de FIFO que da una segunda oportunidad a las páginas antes de reemplazarlas.  
   - **Ventaja:** Balance entre eficiencia y simplicidad.
   - **Desventaja:** Puede ser menos eficiente que LRU en ciertas cargas de trabajo.

5. **NRU (Not Recently Used):**  Clasifica las páginas en grupos según dos bits: el de uso y el de modificación. Reemplaza primero las páginas no usadas ni modificadas.  
   - **Ventaja:** Menor costo computacional que LRU.
   - **Desventaja:** Menos precisa que LRU.

**Política más eficiente según mi criterio:**  
Para mi, **LRU** es generalmente la más eficiente, porque se acerca al óptimo en la mayoría de los casos, especialmente cuando los patrones de acceso tienen alta localidad temporal (patrones dinámicos de acceso a memoria).

---
---
---
### 3.2 Memoria Real

#### **Administración de memoria mediante particiones fijas.**
*Ejemplo del programa en C:*
```c
#include <stdio.h>
#include <stdbool.h>

#define NUM_PARTICIONES 5
#define TAM_PARTICION 100 // Tamaño de cada partición en KB

typedef struct {
    int id_proceso;
    int tam_proceso;
    bool ocupado;
} Particion;

Particion memoria[NUM_PARTICIONES];

void inicializar_memoria() {
    for (int i = 0; i < NUM_PARTICIONES; i++) {
        memoria[i].id_proceso = -1;  // Sin proceso asignado
        memoria[i].tam_proceso = 0;
        memoria[i].ocupado = false;
    }
}

void cargar_proceso(int id, int tam) {
    for (int i = 0; i < NUM_PARTICIONES; i++) {
        if (!memoria[i].ocupado && tam <= TAM_PARTICION) {
            memoria[i].id_proceso = id;
            memoria[i].tam_proceso = tam;
            memoria[i].ocupado = true;
            printf("Proceso %d cargado en la partición %d.\n", id, i);
            return;
        }
    }
    printf("No hay particiones disponibles para el proceso %d.\n", id);
}

void liberar_memoria(int particion) {
    if (particion < 0 || particion >= NUM_PARTICIONES) {
        printf("Número de partición inválido.\n");
        return;
    }
    if (memoria[particion].ocupado) {
        printf("Liberando partición %d asignada al proceso %d.\n", particion, memoria[particion].id_proceso);
        memoria[particion].id_proceso = -1;
        memoria[particion].tam_proceso = 0;
        memoria[particion].ocupado = false;
    } else {
        printf("La partición %d ya está libre.\n", particion);
    }
}

void mostrar_estado_memoria() {
    printf("\nEstado actual de la memoria:\n");
    for (int i = 0; i < NUM_PARTICIONES; i++) {
        printf("Partición %d: ", i);
        if (memoria[i].ocupado) {
            printf("Ocupada por proceso %d (%d KB).\n", memoria[i].id_proceso, memoria[i].tam_proceso);
        } else {
            printf("Libre.\n");
        }
    }
}

int main() {
    inicializar_memoria();
    int opcion, id, tam, particion;

    do {
        printf("\n--- Administración de Memoria: Particiones Fijas ---\n");
        printf("1. Cargar proceso\n");
        printf("2. Liberar partición\n");
        printf("3. Mostrar estado de la memoria\n");
        printf("4. Salir\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Introduce el ID del proceso: ");
                scanf("%d", &id);
                printf("Introduce el tamaño del proceso (en KB): ");
                scanf("%d", &tam);
                cargar_proceso(id, tam);
                break;
            case 2:
                printf("Introduce el número de partición a liberar: ");
                scanf("%d", &particion);
                liberar_memoria(particion);
                break;
            case 3:
                mostrar_estado_memoria();
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 4);

    return 0;
}
```
El programa simula la administración de memoria utilizando particiones fijas, una técnica de asignación de memoria en la que la memoria principal se divide en bloques o particiones de tamaño fijo antes de que se carguen los procesos. Cada proceso debe ajustarse completamente en una de estas particiones. Si un proceso es más pequeño que una partición, se desperdicia el espacio restante (fragmentación interna).

```c
Diseño del programa
```
- *Inicialización:*
Se define el tamaño de la memoria y el número de particiones.Cada partición tiene un tamaño fijo.

- *Cargar procesos:*
Se introduce un sistema para agregar procesos con un tamaño especificado. Cada proceso es asignado a la primera partición disponible que pueda alojarlo.
- *Liberar memoria:*
Se puede liberar una partición específica, marcándola como disponible.
- *Reporte de estado:*
Se muestra el estado actual de las particiones (ocupadas/libres).
---
---
#### **Algoritmo de "Primera Cabida"**
*Ejemplo del algoritmo en C:*
```c
#include <stdio.h>

#define MEMORY_SIZE 500

void first_fit(int process_sizes[], int num_processes) {
    int memory[MEMORY_SIZE] = {0};
    for (int i = 0; i < num_processes; i++) {
        int allocated = 0;
        for (int j = 0; j < MEMORY_SIZE; j++) {
            if (memory[j] == 0 && j + process_sizes[i] <= MEMORY_SIZE) {
                for (int k = j; k < j + process_sizes[i]; k++) {
                    memory[k] = 1;
                }
                printf("Proceso %d asignado desde %d a %d.\n", i + 1, j, j + process_sizes[i] - 1);
                allocated = 1;
                break;
            }
        }
        if (!allocated) {
            printf("Proceso %d no pudo ser asignado.\n", i + 1);
        }
    }
}

int main() {
    int process_sizes[] = {120, 200, 50, 100};
    int num_processes = sizeof(process_sizes) / sizeof(process_sizes[0]);
    first_fit(process_sizes, num_processes);
    return 0;
}
```

Este código se utiliza para asignar memoria a procesos en un sistema simulado. Se basa en asignar cada proceso al primer espacio continuo disponible en memoria que sea lo suficientemente grande.

```c
Diseño del programa
```
- *Constante y estructura de datos principales:*
    - MEMORY_SIZE define el tamaño total de la memoria disponible (500 unidades).
    - *memory* es un arreglo que simula la memoria. Cada posición representa una unidad de memoria, inicializada a 0, lo que indica que está libre.

- *Parámetros del algoritmo:*
La función first_fit recibe:
    - process_sizes[]: un arreglo con los tamaños de los procesos que necesitan memoria.
    - num_processes: la cantidad de procesos.
- *Lógica de asignación:*
    1. Recorrer procesos: Para cada proceso, intenta asignarlo a un bloque libre en memoria.

    2. Recorrer memoria: Dentro de la memoria, busca el primer bloque contiguo de tamaño suficiente:

        - Comprueba que todas las posiciones del bloque estén libres (memory[j] == 0).
        - Se asegura de que el bloque no exceda el tamaño de la memoria (j + process_sizes[i] <= MEMORY_SIZE).
    3. Asignar memoria:
        - Si encuentra un bloque adecuado, marca las posiciones del bloque como ocupadas (memory[k] = 1) dentro del rango [j, j + process_sizes[i]).
        - Imprime un mensaje indicando la asignación exitosa con los índices de inicio y fin del bloque.
---
---
---
### 3.3 Organización de Memoria Virtual

#### **Paginación y Segmentación**

- **Paginación:** Divide la memoria física en bloques de tamaño fijo llamados frames y la memoria lógica en bloques de igual tamaño llamados páginas. Asigna páginas a frames.
    - **Ventajas:** Elimina la fragmentación externa; eficiente en uso de memoria.
    - **Desventajas:** Introduce fragmentación interna y sobrecarga en las tablas de páginas.

- **Segmentación:** Divide la memoria en segmentos lógicos de tamaños variables que corresponden a partes de un programa.
    - **Ventajas:** Compatible con estructuras lógicas como funciones y arreglos.
    - **Desventajas:** Puede generar fragmentación externa.

---
---
#### **Simulación de Tabla de Páginas**
*Ejemplo de la simualción en C:*
```c
#include <stdio.h>
#include <stdlib.h>

#define NUM_PAGES 5
#define FRAME_SIZE 1024

void simulate_page_table(int page_accesses[], int num_accesses) {
    int page_table[NUM_PAGES];
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i] = -1;
    }

    for (int i = 0; i < num_accesses; i++) {
        int page = page_accesses[i];
        if (page_table[page] == -1) {
            page_table[page] = rand() % 100; // Simulación de marco asignado
        }
        printf("Acceso a página %d, marco físico: %d.\n", page, page_table[page]);
    }
}

int main() {
    int page_accesses[] = {0, 2, 4, 1, 3, 0};
    int num_accesses = sizeof(page_accesses) / sizeof(page_accesses[0]);
    simulate_page_table(page_accesses, num_accesses);
    return 0;
}
```
El código simula un comportamiento básico de una tabla de páginas en el contexto de la gestión de memoria virtual. 

```c
Diseño del programa
```
- *Constante y estructura de datos principales:*
    - MEMORY_SIZE define el tamaño total de la memoria disponible (500 unidades).

- *Definiciones y constantes:*
    - NUM_PAGES: Es el número máximo de páginas que la tabla puede manejar (5 en este caso).
    - FRAME_SIZE: Simula el tamaño de un marco de memoria física. No se usa explícitamente en la lógica, pero podría integrarse en una simulación más compleja.
- *Estructura principal:*
    - La tabla de páginas está representada por el arreglo page_table de tamaño NUM_PAGES. Cada índice del arreglo corresponde a una página virtual, y su valor indica el marco físico asignado.
- *Función simulate_page_table:*
    - Recibe como parámetros un arreglo page_accesses con los accesos a las páginas y la cantidad total de accesos num_accesses.
    - Inicializa la tabla de páginas con valores de -1, indicando que las páginas aún no tienen marcos asignados.
- *Función main:*
    - Define un arreglo page_accesses con los accesos simulados a las páginas: {0, 2, 4, 1, 3, 0}.
    - Calcula el número total de accesos (num_accesses) dividiendo el tamaño del arreglo entre el tamaño de un elemento.
    - Llama a simulate_page_table para simular el proceso.
---
---
---
### 3.4 Administración de Memoria Virtual

#### **Algoritmo de Reemplazo de Página "Least Recently Used" (LRU)**
*Ejemplo del algoritmo en C:*
```c
#include <stdio.h>
#include <limits.h>

#define NUM_FRAMES 3

void lru(int pages[], int num_pages) {
    int frames[NUM_FRAMES], counter[NUM_FRAMES];
    int time = 0, page_faults = 0;

    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i], found = 0;
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                counter[j] = ++time;
                break;
            }
        }
        if (!found) {
            int lru_index = 0, min_time = INT_MAX;
            for (int j = 0; j < NUM_FRAMES; j++) {
                if (counter[j] < min_time) {
                    min_time = counter[j];
                    lru_index = j;
                }
            }
            frames[lru_index] = page;
            counter[lru_index] = ++time;
            page_faults++;
        }
        printf("Estado de los marcos: ");
        for (int j = 0; j < NUM_FRAMES; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Fallos de página: %d\n", page_faults);
}

int main() {
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int num_pages = sizeof(pages) / sizeof(pages[0]);
    lru(pages, num_pages);
    return 0;
}
```
El código implementa el algoritmo LRU (Least Recently Used), que se utiliza para gestionar el reemplazo de páginas en un sistema de memoria virtual. 

```c
**Diseño del programa**
```
- *Definiciones:*
    - #define NUM_FRAMES 3: 
    Define el número de marcos de página disponibles en la memoria (3 en este caso).

- *Variables:*

    int frames[NUM_FRAMES], counter[NUM_FRAMES]; 
    int time = 0, page_faults = 0;

    - frames[ ]: Almacena las páginas actualmente en los marcos.
    - counter[ ]: Almacena el "tiempo de uso" de cada página para identificar la página menos recientemente usada.
    - time: Un contador global para simular el paso del tiempo.
    - page_faults: Lleva el conteo de los fallos de página.
- *Inicialización:*

    for (int i = 0; i < NUM_FRAMES; i++) {
    frames[i] = -1;
    counter[i] = 0;
    }

    - Los marcos (frames) se inicializan en -1 para indicar que están vacíos.
    - Los contadores (counter) se inicializan en 0.
---
---
#### **Diagrama del proceso de traducción de direcciones virtuales a físicas**

- *Conceptos básicos:*

    - Dirección virtual: Es una dirección generada por el programa, que forma parte de su espacio de direcciones lógico. No corresponde directamente a una ubicación física en la memoria RAM.

    - Dirección física: Es una dirección real dentro de la memoria principal (RAM) donde se almacenan los datos.
    - Memoria virtual: Es una técnica que utiliza una combinación de RAM y espacio en disco para simular una mayor cantidad de memoria.
    - Paginación: Es el método más común para implementar memoria virtual, dividiendo la memoria en bloques llamados páginas (en la memoria virtual) y marcos (en la memoria física).
    - Unidad de Gestión de Memoria (MMU): Hardware responsable de traducir las direcciones virtuales en direcciones físicas.
    - Tabla de páginas: Estructura de datos que mantiene el sistema operativo para registrar cómo se mapean las páginas virtuales a los marcos físicos.
    - Swapping: Proceso de mover páginas entre la memoria RAM y el almacenamiento secundario (como un disco duro o SSD) cuando la RAM está llena.
- *DIAGRAMA:*

![Diagrama](3.4.2%20Diagrama.png)

---
---
---
### INTEGRACIÓN en la Administración de Memoria

#### **Análisis del Sistema Operativo Windows y su Administración de Memoria Virtual**
- *Conceptos Claves:*
    - Memoria Virtual: Técnica que utiliza espacio en disco duro para simular memoria RAM adicional. Ayuda a ejecutar procesos más grandes que la memoria física.

    - Paginación: División de la memoria en bloques de tamaño fijo llamados páginas (en memoria virtual) y marcos de página (en RAM).
    - Swapping: Mecanismo donde procesos inactivos son movidos entre RAM y disco para liberar espacio.
    - Archivo de Paginación: En Windows, es un archivo en el disco duro (generalmente pagefile.sys) que actúa como memoria virtual.

- *Características de la Administración de Memoria en Windows:*
    - Arquitectura Basada en Paginación:
Usa un modelo jerárquico de tablas de páginas para traducir direcciones virtuales a físicas.

    - Política de Swapping:
Usa algoritmos de reemplazo como Least Recently Used (LRU) para seleccionar qué páginas mover al archivo de paginación.
Monitorea constantemente el uso de memoria para optimizar rendimiento.
    - Gestión del Archivo de Paginación:
Configurable por el usuario o manejado automáticamente por el sistema.
Puede abarcar varios discos para mejorar la eficiencia.
    - Supervisión de Recursos:
Herramientas como el Administrador de Tareas muestran métricas de uso de memoria física y virtual.

- *Comparaciones:*

| Aspecto           | Windows                              | Otros SO (Linux)                                |
|--------------------|--------------------------------------|----------------------------------------|
| Modelo de memoria | Paginación y archivo de paginación | Paginación con swap en partición |
| Archivo de swap  | pagefile.sys | Archivo o partición de swap |
| Gestión de prioridades | Dinámica  | Configurable |
---
---
#### **Simulación de Swapping**
*Ejemplo de la simulación en C:*
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAM_SIZE 1024  // Tamaño de la RAM en KB
#define DISK_SIZE 4096 // Tamaño del disco en KB
#define PROCESS_COUNT 5

typedef struct {
    int id;
    int size;      // Tamaño en KB
    int in_memory; // 1 si está en RAM, 0 si está en disco
} Process;

void swap_to_disk(Process *process, int *ram_used, int *disk_used) {
    printf("Swapping process %d to disk (size: %d KB).\n", process->id, process->size);
    process->in_memory = 0;
    *ram_used -= process->size;
    *disk_used += process->size;
}

void load_to_ram(Process *process, int *ram_used, int *disk_used) {
    printf("Loading process %d to RAM (size: %d KB).\n", process->id, process->size);
    process->in_memory = 1;
    *ram_used += process->size;
    *disk_used -= process->size;
}

int main() {
    Process processes[PROCESS_COUNT] = {
        {1, 300, 1},
        {2, 400, 1},
        {3, 500, 0},
        {4, 200, 0},
        {5, 700, 1},
    };

    int ram_used = 1400; // RAM inicial utilizada
    int disk_used = 700; // Disco inicial utilizado

    printf("Initial RAM used: %d KB\n", ram_used);
    printf("Initial Disk used: %d KB\n", disk_used);

    // Intentamos cargar un proceso grande en RAM
    if (ram_used + processes[3].size > RAM_SIZE) {
        printf("Not enough RAM for process %d. Swapping required.\n", processes[3].id);

        // Swapping de procesos para liberar espacio
        for (int i = 0; i < PROCESS_COUNT; i++) {
            if (processes[i].in_memory) {
                swap_to_disk(&processes[i], &ram_used, &disk_used);
                if (ram_used + processes[3].size <= RAM_SIZE) {
                    break;
                }
            }
        }
    }

    // Cargamos el proceso a RAM
    if (ram_used + processes[3].size <= RAM_SIZE) {
        load_to_ram(&processes[3], &ram_used, &disk_used);
    }

    printf("Final RAM used: %d KB\n", ram_used);
    printf("Final Disk used: %d KB\n", disk_used);

    return 0;
}

```
El código emula un sistema de memoria virtual simplificado con swapping. Simula un conjunto de procesos cargados en memoria y cómo algunos se mueven a disco cuando no hay suficiente espacio.
```c
**Diseño del programa**
```
- Se define una estructura Process que representa cada proceso con un identificador, tamaño, y su estado (RAM o disco).

- Se simula un sistema con RAM de 1 MB y disco de 4 MB.
- Cuando un proceso no cabe en RAM, se realiza swapping de procesos existentes a disco.
- Se cargan procesos a RAM según disponibilidad.
---
---
---