#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura del nodo
typedef struct _nodo {
    int valor;
    struct _nodo *siguiente;
} nodo;

// Estructura de la cola
typedef struct _cola {
    nodo *cabeza;  // Primer nodo (inicio de la cola)
    nodo *final;   // Último nodo (final de la cola)
} cola;

// Función para inicializar la cola
cola* inicializar_cola() {
    cola *nuevaCola = (cola*)malloc(sizeof(cola));
    if (nuevaCola == NULL) {
        printf("ERROR AL ASIGNAR MEMORIA PARA LA COLA.\n");
        exit(1);
    }
    nuevaCola->cabeza = NULL;
    nuevaCola->final = NULL;
    return nuevaCola;
}

// Función para generar un nuevo proceso
nodo* genera_proceso() {
    static int contador = 1;
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));
    if (nuevo == NULL) {
        printf("ERROR AL ASIGNAR MEMORIA PARA EL NODO.\n");
        exit(1);
    }
    nuevo->valor = contador++;
    nuevo->siguiente = NULL;
    printf("NUEVO PROCESO CREADO %d\n", nuevo->valor);
    return nuevo;
}

// Función para insertar un nodo al final de la cola
void insertar_final(cola *q) {
    nodo *nuevoNodo = genera_proceso();
    if (q->cabeza == NULL) {
        // Si la cola está vacía, cabeza y final apuntan al nuevo nodo
        q->cabeza = nuevoNodo;
        q->final = nuevoNodo;
    } else {
        // Si no, enlazamos el nuevo nodo al final de la cola
        q->final->siguiente = nuevoNodo;
        q->final = nuevoNodo;
    }
}

// Función para imprimir la cola
void imprimir_cola(cola *q) {
    nodo *temp = q->cabeza;
    if (temp == NULL) {
        printf("LA COLA ESTÁ VACÍA.\n");
        return;
    }
    printf("LISTA DE PROCESOS:\n");
    while (temp != NULL) {
        printf("PROCESO %d -> ", temp->valor);
        temp = temp->siguiente;
    }
    printf("NULL\n");
}

// Función para atender (eliminar) el primer nodo de la cola
void atender_proceso(cola *q) {
    if (q->cabeza == NULL) {
        printf("NO HAY PROCESOS PARA ATENDER.\n");
        return;
    }
    nodo *temp = q->cabeza;
    printf("ATENDIENDO PROCESO %d\n", temp->valor);

    // Avanzamos la cabeza al siguiente nodo
    q->cabeza = temp->siguiente;

    // Si la cabeza se vuelve NULL, también actualizamos el final
    if (q->cabeza == NULL) {
        q->final = NULL;
    }

    free(temp);  // Liberamos la memoria del nodo atendido
}

// Función para liberar toda la memoria de la cola
void liberar_cola(cola *q) {
    nodo *temp;
    while (q->cabeza != NULL) {
        temp = q->cabeza;
        q->cabeza = q->cabeza->siguiente;
        free(temp);
    }
    free(q);  // Liberamos la estructura de la cola
}

// Función principal
int main() {
    srand(time(NULL));
    cola *q = inicializar_cola();
    int op = 0;

    do {
        printf("1. GENERAR PROCESO\n");
        printf("2. ATENDER PROCESO\n");
        printf("3. MOSTRAR LISTA DE PROCESOS\n");
        printf("4. SALIR\n");
        printf("SELECCIONE UNA OPCIÓN: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                insertar_final(q);
                break;
            case 2:
                atender_proceso(q);
                break;
            case 3:
                imprimir_cola(q);
                break;
            case 4:
                printf("LIBERANDO MEMORIA Y SALIENDO...\n");
                liberar_cola(q);
                break;
            default:
                printf("OPCIÓN NO VÁLIDA.\n");
        }
    } while (op != 4);

    return 0;
}