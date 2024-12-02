# SISTEMAS OPERATIVOS
    Alumna: FERNANDA ELIZABETH VÉLEZ ALEJANDRE (22121321)

## ADMINISTRACIÓN DE ENTRADA/SALIDA

### 4.1 Dispositivos y manejadores de dispositivos

#### **Diferencia entre dispositivos de bloque y dispositivos de carácter**

- **Dispositivos de bloque:**
Son dispositivos que manejan los datos en bloques de tamaño fijo, generalmente de 512 bytes o múltiplos. Los datos se almacenan y acceden en unidades completas llamadas bloques.

- **Dispositivos de carácter:**
Son dispositivos que manejan los datos como un flujo continuo de caracteres, procesándolos uno por uno.

|Dispositivos de bloque: | Dispositivos de carácter: |
|-----------|-----------|
| Manejan bloques de datos de tamaño fijo.|Manejan datos como flujos de caracteres, uno por uno.|
| Permiten acceso aleatorio (se puede acceder a cualquier parte de los datos directamente).|Sólo permiten acceso secuencial (los datos deben ser leídos o escritos en orden).|
| *Ejemplo:* discos duros, discos SSD.|*Ejemplo:* teclado, impresora.|
---
---
#### **Manejador de dispositivos para un dispositivo virtual de entrada**
*Ejemplo del programa en C:*
```c
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

// Estructura para representar el dispositivo virtual
typedef struct {
    char buffer[BUFFER_SIZE]; // Búfer de almacenamiento
} VirtualDevice;

// Función para escribir datos al dispositivo virtual
void writeToDevice(VirtualDevice *device, const char *data) {
    strncpy(device->buffer, data, BUFFER_SIZE - 1); // Copia datos al búfer
    device->buffer[BUFFER_SIZE - 1] = '\0'; // Asegura que el búfer termine en '\0'
}

// Función para leer datos del dispositivo virtual
void readFromDevice(VirtualDevice *device) {
    printf("Contenido del dispositivo: %s\n", device->buffer); // Muestra el contenido
}

int main() {
    VirtualDevice device; // Declarar el dispositivo virtual
    memset(device.buffer, 0, BUFFER_SIZE); // Inicializar el búfer a ceros

    // Simular una escritura en el dispositivo
    writeToDevice(&device, "Hola, este es un mensaje de prueba.");
    printf("Escribiendo en el dispositivo...\n");

    // Simular una lectura desde el dispositivo
    printf("Leyendo desde el dispositivo...\n");
    readFromDevice(&device);

    return 0;
}
```
El programa implementa un manejador de un dispositivo virtual de entrada. Este dispositivo tiene un búfer en el que almacena datos ingresados y permite operaciones básicas de lectura y escritura.

```c
Diseño del programa
```

- *Estructura del dispositivo virtual:*
    - Utilizamos una estructura (struct) para modelar el dispositivo.
    - Contiene un búfer (buffer) que almacena los datos.
    - Tiene funciones asociadas para operar sobre el búfer.

- *Funciones del manejador:*
    - Escribir en el dispositivo:
Recibe una cadena y la almacena en el búfer, simulando una operación de escritura en el dispositivo.
    - Leer del dispositivo:
Recupera los datos almacenados en el búfer, simulando una operación de lectura.

- *Lógica del programa principal:*
    - Se inicializa el dispositivo virtual.
    - Se simulan operaciones de escritura (almacenar datos en el dispositivo) y lectura (recuperar datos desde el dispositivo).
    - Se imprimen los resultados para mostrar cómo funciona el manejo del dispositivo.

---
---
---
### 4.2 Mecanismos y funciones de los manejadores de dispositivos

#### **Interrupción por E/S y su administración por el sistema operativo**

- ¿Qué es una interrupción por E/S?

Una interrupción por E/S es un mecanismo utilizado por los dispositivos de entrada/salida para notificar al sistema operativo que han completado una operación o que requieren atención. Este método permite al procesador continuar ejecutando otras tareas mientras el dispositivo realiza la operación de E/S, mejorando la eficiencia del sistema.

- Características:
    - No bloqueante:
El procesador no espera activamente a que termine la operación de E/S.
    - Asincrónico:
La interrupción puede ocurrir en cualquier momento, independientemente de la ejecución actual.
    - Manejador de interrupciones:
El sistema operativo implementa manejadores específicos para procesar las interrupciones.

- Flujo básico de manejo de una interrupción por E/S:
    1. El dispositivo genera una señal de interrupción.
    2. El procesador detiene la tarea actual y salta al manejador de interrupción.
    3. El manejador procesa la solicitud del dispositivo.
    4. El control regresa a la tarea interrumpida.

---
#### **Pseudocódigo para simular el proceso de interrupción por E/S**
*Ejemplo del pseudocódigo*
```c
iniciar_sistema() {
    inicializar_dispositivos();
    habilitar_interrupciones();
    ejecutar_tareas_principales();
}

manejar_interrupcion() {
    identificar_dispositivo();
    procesar_solicitud_dispositivo();
    actualizar_estado_sistema();
    regresar_a_tarea_anterior();
}

proceso_principal() {
    while (true) {
        realizar_operaciones_normales();
        // El manejador de interrupción se ejecutará cuando el dispositivo lo requiera.
    }
}
```
---
---
#### **Programa en C para manejar interrupciones**
*Ejemplo del programa en C:*
```c
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // Para la función sleep()

// Simulación de un dispositivo con interrupciones
bool dispositivoListo = false;

// Función simulada para manejar la interrupción
void manejarInterrupcion() {
    printf("Interrupción recibida: Procesando solicitud del dispositivo...\n");
    dispositivoListo = false; // Restablecer estado del dispositivo
    printf("Dispositivo atendido. Continuando con las tareas principales.\n");
}

// Función para simular una tarea del dispositivo
void tareaDispositivo() {
    printf("Dispositivo: Iniciando tarea...\n");
    sleep(2); // Simula un tiempo de procesamiento
    dispositivoListo = true; // Simula que el dispositivo completó la tarea
    printf("Dispositivo: Generando interrupción.\n");
}

// Proceso principal
int main() {
    printf("Iniciando el sistema...\n");

    while (1) {
        // Simular el trabajo principal del procesador
        printf("Procesador: Ejecutando tareas principales...\n");
        sleep(1);

        // Simular la tarea del dispositivo en paralelo
        if (!dispositivoListo) {
            tareaDispositivo();
        }

        // Verificar si el dispositivo genera una interrupción
        if (dispositivoListo) {
            manejarInterrupcion();
        }
    }

    return 0;
}
```
Este programa simula un sistema donde un dispositivo genera una interrupción para notificar al procesador que una tarea está completa.
```c
Diseño del programa
```
- *Variable dispositivoListo:*
Indica si el dispositivo ha completado su tarea y necesita atención.

- *Función manejarInterrupcion:*
Simula el manejo de la interrupción generada por el dispositivo.
Procesa la solicitud y reinicia el estado del dispositivo.

- *Función tareaDispositivo:*
Simula el trabajo del dispositivo y genera una interrupción después de completar la tarea.

- *Bucle* principal (main):*
Ejecuta tareas principales del sistema (procesador).
En paralelo, monitorea el estado del dispositivo.
Atiende las interrupciones cuando el dispositivo está listo.
---
---
---
### 4.3 Estructuras de datos para manejo de dispositivos

#### **Interrupción por E/S y su administración por el sistema operativo**

- ¿Qué es una cola de E/S?

Una cola de E/S es una estructura de datos utilizada por los sistemas operativos para gestionar solicitudes de entrada/salida. Cuando múltiples procesos realizan peticiones simultáneas a un dispositivo, el sistema operativo organiza estas solicitudes en una cola y las procesa en el orden adecuado.

- Características de una cola de E/S:
    - FIFO (First-In, First-Out):
En colas simples, las solicitudes se procesan en el orden en que llegan.
    - Colas con prioridad:
Las solicitudes más importantes (según ciertos criterios) se procesan antes que otras.
    - Optimización:
Las políticas como elevador (Elevator Scheduling) optimizan el acceso a dispositivos como discos.
---
#### **Simulación de una cola de E/S con prioridad**
*Ejemplo de la simulación en C:*
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_REQUESTS 10

// Estructura para representar una solicitud de E/S
typedef struct {
    int id;           // ID de la solicitud
    int prioridad;    // Prioridad de la solicitud (menor valor = mayor prioridad)
    char descripcion[50]; // Descripción de la solicitud
} Solicitud;

// Estructura de la cola de E/S
typedef struct {
    Solicitud solicitudes[MAX_REQUESTS];
    int tamano; // Número actual de solicitudes en la cola
} Cola;

// Función para inicializar la cola
void inicializarCola(Cola *cola) {
    cola->tamano = 0;
}

// Función para agregar una solicitud a la cola
bool agregarSolicitud(Cola *cola, int id, int prioridad, const char *descripcion) {
    if (cola->tamano >= MAX_REQUESTS) {
        printf("La cola de E/S está llena.\n");
        return false;
    }
    Solicitud nueva = {id, prioridad, ""};
    strncpy(nueva.descripcion, descripcion, sizeof(nueva.descripcion) - 1);
    cola->solicitudes[cola->tamano++] = nueva;
    return true;
}

// Función para procesar la solicitud con mayor prioridad
void procesarSolicitud(Cola *cola) {
    if (cola->tamano == 0) {
        printf("La cola de E/S está vacía.\n");
        return;
    }

    // Buscar la solicitud con mayor prioridad (menor valor de prioridad)
    int indicePrioridad = 0;
    for (int i = 1; i < cola->tamano; i++) {
        if (cola->solicitudes[i].prioridad < cola->solicitudes[indicePrioridad].prioridad) {
            indicePrioridad = i;
        }
    }

    // Procesar la solicitud
    printf("Procesando solicitud ID: %d, Prioridad: %d, Descripción: %s\n",
           cola->solicitudes[indicePrioridad].id,
           cola->solicitudes[indicePrioridad].prioridad,
           cola->solicitudes[indicePrioridad].descripcion);

    // Eliminar la solicitud procesada
    for (int i = indicePrioridad; i < cola->tamano - 1; i++) {
        cola->solicitudes[i] = cola->solicitudes[i + 1];
    }
    cola->tamano--;
}

// Función principal para probar la cola de E/S
int main() {
    Cola cola;
    inicializarCola(&cola);

    agregarSolicitud(&cola, 1, 2, "Lectura de archivo");
    agregarSolicitud(&cola, 2, 1, "Escritura en disco");
    agregarSolicitud(&cola, 3, 3, "Transferencia de datos a red");

    printf("Cola inicial:\n");
    for (int i = 0; i < cola.tamano; i++) {
        printf("ID: %d, Prioridad: %d, Descripción: %s\n",
               cola.solicitudes[i].id, cola.solicitudes[i].prioridad,
               cola.solicitudes[i].descripcion);
    }

    printf("\nProcesando solicitudes:\n");
    while (cola.tamano > 0) {
        procesarSolicitud(&cola);
    }

    return 0;
}
```
Este programa utiliza una estructura de datos para simular una cola con prioridad. Las solicitudes con menor número de prioridad (valor más bajo) se procesan primero.
```c
Diseño de la simulación
```
- La estructura Solicitud tiene un identificador, prioridad y una descripción.
- La estructura Cola almacena un arreglo de solicitudes y el tamaño actual.
- Se agregan solicitudes con distintas prioridades.
- Se procesan en orden de prioridad hasta que la cola está vacía.
---
---
#### **Manejador de dispositivos utilizando una tabla de estructuras**
*Ejemplo del programa en C:*
```c
#include <stdio.h>
#include <string.h>

#define MAX_DISPOSITIVOS 5

// Estructura para representar un dispositivo
typedef struct {
    int id;                   // ID del dispositivo
    char nombre[30];          // Nombre del dispositivo
    char estado[10];          // Estado del dispositivo ("Activo" o "Inactivo")
} Dispositivo;

// Tabla de dispositivos
Dispositivo tablaDispositivos[MAX_DISPOSITIVOS];
int numDispositivos = 0;

// Función para agregar un dispositivo
void agregarDispositivo(int id, const char *nombre, const char *estado) {
    if (numDispositivos >= MAX_DISPOSITIVOS) {
        printf("No se pueden agregar más dispositivos.\n");
        return;
    }
    tablaDispositivos[numDispositivos].id = id;
    strncpy(tablaDispositivos[numDispositivos].nombre, nombre, sizeof(tablaDispositivos[numDispositivos].nombre) - 1);
    strncpy(tablaDispositivos[numDispositivos].estado, estado, sizeof(tablaDispositivos[numDispositivos].estado) - 1);
    numDispositivos++;
}

// Función para mostrar la tabla de dispositivos
void mostrarTabla() {
    printf("ID\tNombre\t\tEstado\n");
    printf("--------------------------------\n");
    for (int i = 0; i < numDispositivos; i++) {
        printf("%d\t%s\t\t%s\n", tablaDispositivos[i].id, tablaDispositivos[i].nombre, tablaDispositivos[i].estado);
    }
}

// Función para actualizar el estado de un dispositivo
void actualizarEstado(int id, const char *nuevoEstado) {
    for (int i = 0; i < numDispositivos; i++) {
        if (tablaDispositivos[i].id == id) {
            strncpy(tablaDispositivos[i].estado, nuevoEstado, sizeof(tablaDispositivos[i].estado) - 1);
            printf("Estado del dispositivo %d actualizado a '%s'.\n", id, nuevoEstado);
            return;
        }
    }
    printf("Dispositivo con ID %d no encontrado.\n", id);
}

// Programa principal
int main() {
    agregarDispositivo(1, "Teclado", "Activo");
    agregarDispositivo(2, "Mouse", "Activo");
    agregarDispositivo(3, "Impresora", "Inactivo");

    printf("Tabla inicial de dispositivos:\n");
    mostrarTabla();

    printf("\nActualizando el estado del dispositivo 3...\n");
    actualizarEstado(3, "Activo");

    printf("\nTabla actualizada de dispositivos:\n");
    mostrarTabla();

    return 0;
}
```
En este programa, simulamos un manejador de dispositivos que usa una tabla de estructuras para gestionar diferentes dispositivos.
```c
Diseño del programa
```
- *Funciones principales:*
    - agregarDispositivo: Registra un nuevo dispositivo en la tabla.
    - mostrarTabla: Imprime la lista actual de dispositivos.
    - actualizarEstado: Cambia el estado de un dispositivo dado su ID.

- *Flujo del programa:*
    - Se agregan dispositivos a la tabla.
    - Se muestra la tabla inicial.
    - Se actualiza el estado de un dispositivo y se muestra la tabla actualizada.
---
---
---
### 4.4 Operaciones de Entrada/Salida

#### **Flujo para describir el proceso de lectura de un archivo desde un disco magnético**
El proceso de lectura de un archivo desde un disco magnético generalmente implica los siguientes pasos:
1. *Solicitud de lectura:* El programa o proceso solicita acceso al archivo.

2. *Acceso al sistema de archivos:* El sistema operativo verifica la existencia del archivo y su ubicación en el disco.
3. *Localización del archivo:* El sistema busca la dirección física del archivo en el disco, utilizando la tabla de asignación (FAT, NTFS, etc.).
4. *Movimiento del cabezal:* El cabezal del disco magnético se posiciona sobre la pista y sector donde está almacenado el archivo.
5. *Lectura de datos:* Los datos se leen del disco y se transfieren al buffer del sistema operativo.
6. *Transferencia al programa:* El sistema operativo transfiere los datos al programa que realizó la solicitud.

#### **Simulación del proceso de lectura de un archivo**
*Ejemplo del programa en C:*
```c
#include <stdio.h>
#include <stdlib.h>

// Simulación de una función para localizar el archivo en el disco
void localizarArchivo(const char *nombreArchivo) {
    printf("Localizando archivo '%s' en el sistema de archivos...\n", nombreArchivo);
    printf("Archivo encontrado en la pista 12, sector 34.\n");
}

// Simulación de lectura de datos desde el disco
void leerDatosDesdeDisco() {
    printf("Moviendo cabezal al sector correspondiente...\n");
    printf("Leyendo datos del disco...\n");
    printf("Datos transferidos al buffer del sistema operativo.\n");
}
 
// Función para procesar la lectura de un archivo
void procesarLectura(const char *nombreArchivo) {
    printf("Iniciando proceso de lectura para '%s'...\n", nombreArchivo);
    localizarArchivo(nombreArchivo);
    leerDatosDesdeDisco();
    printf("Transferencia completada al programa.\n");
}

int main() {
    const char *nombreArchivo = "archivo_ejemplo.txt";
    procesarLectura(nombreArchivo);
    return 0;
}
```
Este programa simula el flujo de lectura de un archivo desde un disco. Aunque no interactúa directamente con hardware, representa el proceso lógico.

---
---
#### **Operaciones de entrada/salida asíncronas**
- ¿Qué son las operaciones de entrada/salida asíncronas?

Las operaciones de E/S asíncronas permiten que un programa continúe ejecutándose mientras se realiza una operación de entrada/salida, en lugar de esperar a que esta termine.

#### **Programa que realiza operaciones de E/S asíncronas**
*Ejemplo del programa en C:*
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Para la función sleep()

// Función que simula una operación de lectura asíncrona
void *leerArchivo(void *nombreArchivo) {
    const char *archivo = (const char *)nombreArchivo;
    printf("Inicio de lectura del archivo '%s'...\n", archivo);
    sleep(3); // Simula el tiempo necesario para la lectura
    printf("Lectura del archivo '%s' completada.\n", archivo);
    pthread_exit(NULL);
}

// Función principal
int main() {
    pthread_t hiloLectura; // Hilo para la operación asíncrona
    const char *nombreArchivo = "archivo_asincrono.txt";

    printf("Creando hilo para leer el archivo de forma asíncrona...\n");
    if (pthread_create(&hiloLectura, NULL, leerArchivo, (void *)nombreArchivo) != 0) {
        perror("Error al crear el hilo");
        return 1;
    }

    printf("El programa puede continuar con otras tareas mientras se lee el archivo...\n");
    for (int i = 1; i <= 5; i++) {
        printf("Tarea principal en progreso... Paso %d\n", i);
        sleep(1); // Simula trabajo en el programa principal
    }

    // Esperar a que el hilo termine
    pthread_join(hiloLectura, NULL);
    printf("El programa principal finalizó.\n");

    return 0;
}
```
El programa utiliza hilos para simular operaciones de entrada/salida asíncronas.
```c
Diseño del programa
```
- *Uso de hilos (pthread):*
La operación de lectura del archivo se realiza en un hilo separado, simulando E/S asíncrona.

- *Función leerArchivo:*
Representa la tarea de leer un archivo. Incluye un retardo con sleep para simular el tiempo necesario para completar la operación.

- *Ejecución paralela:*
Mientras se ejecuta la función de lectura, el programa principal continúa ejecutando otras tareas.

- *Sincronización:*
Se utiliza pthread_join para esperar a que el hilo finalice antes de terminar el programa principal.
---
---
---
### INTEGRACIÓN en la Administración de Entrada/Salida

#### **Implementación del algoritmo de planificación de discos "Elevator (SCAN)"**
- Concepto:

El algoritmo Elevator (SCAN) mueve el cabezal del disco en una dirección (ascendente o descendente) atendiendo las solicitudes en orden según las pistas, hasta que llega al extremo del disco. Luego invierte su dirección para atender las solicitudes restantes.

- Características del algoritmo SCAN:
    - Evita el hambre al atender todas las solicitudes en cada dirección.
    - Es más eficiente que First-Come-First-Serve (FCFS) en entornos con alta carga de solicitudes.

#### **Programa que realiza el algoritmo Elevator (SCAN)**
*Ejemplo del programa en C:*
```c
#include <stdio.h>
#include <stdlib.h>

// Función para ordenar las solicitudes de pistas
void ordenarSolicitudes(int solicitudes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (solicitudes[j] > solicitudes[j + 1]) {
                int temp = solicitudes[j];
                solicitudes[j] = solicitudes[j + 1];
                solicitudes[j + 1] = temp;
            }
        }
    }
}

// Implementación del algoritmo SCAN
void algoritmoSCAN(int solicitudes[], int n, int pistaInicial, int direccion, int limite) {
    ordenarSolicitudes(solicitudes, n);

    int i, recorrido = 0;
    printf("Orden de acceso a las pistas:\n");

    if (direccion == 1) { // Dirección ascendente
        for (i = 0; i < n && solicitudes[i] < pistaInicial; i++);
        for (; i < n; i++) {
            printf("Pista %d\n", solicitudes[i]);
            recorrido += abs(solicitudes[i] - pistaInicial);
            pistaInicial = solicitudes[i];
        }
        if (pistaInicial < limite) {
            printf("Pista %d (extremo superior)\n", limite);
            recorrido += abs(limite - pistaInicial);
            pistaInicial = limite;
        }
        for (i = n - 1; i >= 0 && solicitudes[i] < pistaInicial; i--) {
            printf("Pista %d\n", solicitudes[i]);
            recorrido += abs(solicitudes[i] - pistaInicial);
            pistaInicial = solicitudes[i];
        }
    } else { // Dirección descendente
        for (i = n - 1; i >= 0 && solicitudes[i] > pistaInicial; i--);
        for (; i >= 0; i--) {
            printf("Pista %d\n", solicitudes[i]);
            recorrido += abs(solicitudes[i] - pistaInicial);
            pistaInicial = solicitudes[i];
        }
        if (pistaInicial > 0) {
            printf("Pista 0 (extremo inferior)\n");
            recorrido += pistaInicial;
            pistaInicial = 0;
        }
        for (i = 0; i < n && solicitudes[i] > pistaInicial; i++) {
            printf("Pista %d\n", solicitudes[i]);
            recorrido += abs(solicitudes[i] - pistaInicial);
            pistaInicial = solicitudes[i];
        }
    }

    printf("Recorrido total del cabezal: %d pistas\n", recorrido);
}

int main() {
    int solicitudes[] = {95, 180, 34, 119, 11, 123, 62, 64};
    int n = sizeof(solicitudes) / sizeof(solicitudes[0]);
    int pistaInicial = 50, direccion = 1, limite = 199;

    printf("Pista inicial: %d\n", pistaInicial);
    printf("Dirección: %s\n", direccion == 1 ? "Ascendente" : "Descendente");

    algoritmoSCAN(solicitudes, n, pistaInicial, direccion, limite);
    return 0;
}
```

```c
Diseño del programa
```
- *Ordenación:*
Las solicitudes de pistas se ordenan para facilitar el acceso secuencial.

- *Dirección:*
El cabezal se mueve en la dirección especificada (ascendente o descendente).
- *Extremos:*
Al alcanzar un extremo, el cabezal invierte su dirección.
- *Cálculo de recorrido:*
Se suma la distancia total recorrida por el cabezal.
---
---
#### **Sistema que maneja múltiples dispositivos simulados**
*Ejemplo del sistema en C:*
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Estructura para solicitudes de dispositivos
typedef struct {
    int idSolicitud;
    char dispositivo[20];
} Solicitud;

// Función que simula el manejo de un dispositivo
void *manejadorDispositivo(void *args) {
    Solicitud *solicitud = (Solicitud *)args;
    printf("Procesando solicitud %d en %s...\n", solicitud->idSolicitud, solicitud->dispositivo);
    sleep(2); // Simula tiempo de procesamiento
    printf("Solicitud %d en %s completada.\n", solicitud->idSolicitud, solicitud->dispositivo);
    free(solicitud);
    pthread_exit(NULL);
}

int main() {
    const char *dispositivos[] = {"Disco Duro", "Impresora", "Teclado"};
    const int totalSolicitudes = 5;

    pthread_t hilos[totalSolicitudes];

    for (int i = 0; i < totalSolicitudes; i++) {
        Solicitud *solicitud = (Solicitud *)malloc(sizeof(Solicitud));
        solicitud->idSolicitud = i + 1;
        snprintf(solicitud->dispositivo, sizeof(solicitud->dispositivo), "%s", dispositivos[i % 3]);

        printf("Creando hilo para solicitud %d en %s...\n", solicitud->idSolicitud, solicitud->dispositivo);
        if (pthread_create(&hilos[i], NULL, manejadorDispositivo, solicitud) != 0) {
            perror("Error al crear hilo");
            return 1;
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < totalSolicitudes; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Todas las solicitudes fueron procesadas.\n");
    return 0;
}

```
Sistema operativo que coordina la comunicación entre dispositivos mediante controladores y colas de espera. Se simulan dispositivos como disco, impresora y teclado. Cada dispositivo tendrá una cola de solicitudes y un manejador que procesa las tareas.
```c
Diseño del sistema
```
- *Simulación de solicitudes:*
Se generan solicitudes para diferentes dispositivos.

- *Manejador de dispositivos:*
Cada solicitud es procesada por un hilo independiente.
- *Comunicación asíncrona:*
Los dispositivos funcionan de manera simultánea, simulando paralelismo.
---
---
---
### AVANZADOS

#### **Optimización de Operaciones de Entrada/Salida con el Uso de Memoria Caché**
- Conceptos Clave
    - Memoria Caché:
Es una memoria intermedia de alta velocidad utilizada para almacenar datos frecuentemente accedidos.
Se encuentra entre la CPU y los dispositivos de almacenamiento (como el disco duro o SSD).

    - Entrada/Salida en Sistemas Operativos:
Las operaciones de entrada/salida (E/S) suelen ser más lentas que las operaciones en memoria debido a la latencia de los dispositivos físicos.
Los sistemas operativos optimizan estas operaciones usando la caché para reducir el acceso directo a los dispositivos.

- Optimización de E/S con Caché:
    - Lectura anticipada (read-ahead):
El sistema operativo predice qué datos serán necesarios y los carga en la caché antes de que sean solicitados.
    - Escritura diferida (write-back):
Los datos se escriben primero en la caché y, de manera diferida, se sincronizan con el disco, lo que mejora el rendimiento.
    - Eliminación de accesos repetidos:
Si los datos solicitados ya están en la caché, se evita el acceso físico al dispositivo.
Políticas de reemplazo en caché:
Para administrar el espacio limitado de la caché, los sistemas usan políticas como:
LRU (Least Recently Used): Se reemplazan los datos menos usados recientemente.
FIFO (First In, First Out): Se reemplazan los datos más antiguos.

| Aspecto           | Ventaja                              | Desafío                                |
|--------------------|--------------------------------------|----------------------------------------|
| Velocidad         | Reduce significativamente la latencia. | La coherencia de datos es crítica.    |
| Espacio limitado  | Optimiza operaciones comunes.        | Requiere políticas eficientes.         |
| Escritura diferida | Reduce operaciones en disco.        | Puede haber pérdida de datos en caso de fallos. |
---
---
---