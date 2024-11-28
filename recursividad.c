#include <stdio.h>

// Prototipos de funciones
int realizarDivision();
int realizarPotencia();
int division(int dividendo, int divisor);
int exponente(int base, int exponente);

int main() {
    int opcion;

    do {
        // Menú principal
        printf("Seleccione una operación:\n");
        printf("1. División\n");
        printf("2. Potencias\n");
        printf("0. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                realizarDivision();
                break;
            case 2:
                realizarPotencia();
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    return 0;
}

// Función para manejar la división
int realizarDivision() {
    int dividendo, divisor;

    printf("Introduce el dividendo: ");
    scanf("%d", &dividendo);
    printf("Introduce el divisor: ");
    scanf("%d", &divisor);

    int resultadoDivision = division(dividendo, divisor);
    printf("Resultado de la división: %d\n\n", resultadoDivision);

    return resultadoDivision;
}

// Función para manejar la potencia
int realizarPotencia() {
    int base, potencia;

    printf("Introduce la base: ");
    scanf("%d", &base);
    printf("Introduce el exponente: ");
    scanf("%d", &potencia);

    int resultadoExponente = exponente(base, potencia);
    printf("Resultado del exponente: %d\n\n", resultadoExponente);

    return resultadoExponente;
}

// Función para realizar la división usando restas
int division(int dividendo, int divisor) {
    if (divisor == 0) {
        printf("Error: División por cero.\n");
        return 0;
    }

    int cociente = 0;
    int esNegativo = 0;

    // Manejo de números negativos
    if (dividendo < 0) {
        dividendo = -dividendo;
        esNegativo = !esNegativo;
    }
    if (divisor < 0) {
        divisor = -divisor;
        esNegativo = !esNegativo;
    }

    while (dividendo >= divisor) {
        dividendo -= divisor;
        cociente++;
    }

    return esNegativo ? -cociente : cociente;
}

// Función para calcular la potencia usando sumas
int exponente(int base, int exponente) {
    if (exponente < 0) {
        printf("Error: Exponente negativo no soportado.\n");
        return 0;
    }

    if (exponente == 0) {
        return 1;
    }

    int resultado = 1;
    for (int i = 0; i < exponente; i++) {
        int temp = 0;
        for (int j = 0; j < resultado; j++) {
            temp += base;
        }
        resultado = temp;
    }

    return resultado;
}