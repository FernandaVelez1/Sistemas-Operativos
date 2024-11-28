#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 8

// Estructura para almacenar la matriz y su estado de visitado.
typedef struct {
    int matrix[ROWS][COLS];
    int visited[ROWS][COLS];
} Grid;

// Prototipos de funciones.
void initVisited(Grid *grid);
void dfs(Grid *grid, int row, int col);
int countAreas(Grid *grid);

int main(void) {
    // Declaración e inicialización de la matriz.
    Grid grid = {
        .matrix = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0, 0, 1, 0},
            {0, 1, 1, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 1, 1},
            {0, 1, 1, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
        }
    };

    // Inicializa la matriz de visitados.
    initVisited(&grid);

    // Cuenta las áreas y muestra el resultado.
    int areaCount = countAreas(&grid);
    printf("Cantidad de areas con 1 en la matriz: %d\n", areaCount);

    return 0;
}

// Inicializa la matriz de visitados en 0.
void initVisited(Grid *grid) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid->visited[i][j] = 0;
        }
    }
}

// Función DFS para explorar áreas conectadas.
void dfs(Grid *grid, int row, int col) {
    // Verifica los límites y condiciones de la celda.
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS ||
        grid->matrix[row][col] == 0 || grid->visited[row][col]) {
        return;
    }

    // Marca la celda como visitada.
    grid->visited[row][col] = 1;

    // Llama recursivamente a las celdas vecinas.
    dfs(grid, row + 1, col); // Abajo.
    dfs(grid, row - 1, col); // Arriba.
    dfs(grid, row, col + 1); // Derecha.
    dfs(grid, row, col - 1); // Izquierda.
}

// Cuenta las áreas conectadas de 1 en la matriz.
int countAreas(Grid *grid) {
    int count = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid->matrix[i][j] == 1 && !grid->visited[i][j]) {
                count++;
                dfs(grid, i, j); // Explora el área conectada.
            }
        }
    }

    return count;
}