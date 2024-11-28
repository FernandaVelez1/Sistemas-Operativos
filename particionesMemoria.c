#include <stdio.h>
#include <stdbool.h>

#define tMem 10

typedef struct {
    int PID;
    int tamaño;
} Particion;

Particion memoria[tMem];
int numParticiones = 0;

void inicializarMemoria() {
    int sump = 0, tamaño;
    printf("Ingrese el número de particiones: ");
    scanf("%d", &numParticiones);

    for (int i = 0; i < numParticiones; i++) {
        printf("Tamaño de la partición %d (MB): ", i + 1);
        scanf("%d", &tamaño);

        if (sump + tamaño > tMem) {
            printf("Error: La partición excede el tamaño total de memoria.\n");
            numParticiones = i;
            break;
        }
        memoria[i].PID = -1;
        memoria[i].tamaño = tamaño;
        sump += tamaño;
    }
    printf("Memoria configurada con %d particiones.\n\n", numParticiones);
}

bool memoriaLlena() {
    for (int i = 0; i < numParticiones; i++) {
        if (memoria[i].PID == -1) return false;
    }
    return true;
}

int buscarParticion(int pid) {
    for (int i = 0; i < numParticiones; i++) {
        if (memoria[i].PID == pid) return i;
    }
    return -1;
}

void asignarProceso() {
    if (memoriaLlena()) {
        printf("Memoria llena, no se pueden asignar más procesos.\n\n");
        return;
    }

    int pid, tamaño;
    printf("Ingrese ID del proceso: ");
    scanf("%d", &pid);
    if (buscarParticion(pid) != -1) {
        printf("Error: El PID ya existe.\n\n");
        return;
    }

    printf("Ingrese tamaño del proceso (MB): ");
    scanf("%d", &tamaño);

    for (int i = 0; i < numParticiones; i++) {
        if (memoria[i].PID == -1 && memoria[i].tamaño >= tamaño) {
            memoria[i].PID = pid;
            printf("Proceso %d asignado a la partición %d. Memoria desperdiciada: %d MB.\n\n",
                   pid, i + 1, memoria[i].tamaño - tamaño);
            return;
        }
    }
    printf("Error: No hay particiones adecuadas para este proceso.\n\n");
}

void liberarProceso() {
    int pid;
    printf("Ingrese ID del proceso a liberar: ");
    scanf("%d", &pid);

    int indice = buscarParticion(pid);
    if (indice != -1) {
        memoria[indice].PID = -1;
        printf("Proceso %d liberado de la partición %d.\n\n", pid, indice + 1);
    } else {
        printf("Error: No se encontró un proceso con ese PID.\n\n");
    }
}

void mostrarMemoria() {
    printf("\nEstado de la memoria:\n");
    for (int i = 0; i < numParticiones; i++) {
        if (memoria[i].PID == -1) {
            printf("Partición %d: Libre (%d MB)\n", i + 1, memoria[i].tamaño);
        } else {
            printf("Partición %d: Ocupada - PID %d (%d MB)\n", i + 1, memoria[i].PID, memoria[i].tamaño);
        }
    }
    printf("\n");
}

int main() {
    int opcion;

    do {
        printf("------------- Menú -------------\n");
        printf("1. Configurar particiones\n");
        printf("2. Asignar proceso\n");
        printf("3. Liberar proceso\n");
        printf("4. Mostrar memoria\n");
        printf("5. Salir\n");
        printf("--------------------------------\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                inicializarMemoria();
                break;
            case 2:
                asignarProceso();
                break;
            case 3:
                liberarProceso();
                break;
            case 4:
                mostrarMemoria();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opción inválida, intente de nuevo.\n\n");
        }
    } while (true);
}