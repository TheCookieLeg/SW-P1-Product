//
// Created by lucas on 24-11-2025.
//

#include "ReadMapFromFile.h"

#include <stdio.h>
#include <stdlib.h>

#define MINIMUM_WAREHOUSE_SIZE 3

int** CreateGridMap(int* px, int* py) {

    int x = *px;
    int y = *py;

    FILE* gridFile = fopen("TextFiles/GridMap.txt", "r"); // Reads our input file

    if (gridFile == NULL) { // Checks if the compiler can find the file
        perror("File could not be found. Try again");
        exit(EXIT_FAILURE);
    }

    GetWarehouseSize(gridFile, &x, &y);
    printf("x: %d\ny: %d\n", x, y);

    int** grid = calloc(y, sizeof(int*)); // This creates all the rows (vertical)
    if (!grid) { perror("malloc"); exit(EXIT_FAILURE); }

    for (int i = 0; i < y; i++) {
        grid[i] = calloc(x, sizeof(int)); // Then for each row, x columns are created, giving us a 2D array
        if (!grid[i]) { perror("malloc"); exit(EXIT_FAILURE); }
    }


    PrintGrid(y, x, grid);


    fclose(gridFile);

    return grid;
}

void GetWarehouseSize(FILE* file, int* x, int* y) {
    char cX[4], cY[4]; // This makes it possible for a warehouse size of 9999 x 9999
    fscanf(file, "%s %s", cX, cY); // Scans the first two integers as strings

    // Converts the strings into integers
    *x = strtol(cX, NULL, 10);
    *y = strtol(cY, NULL, 10);

    if (*x == 0 || *y == 0) {
        fprintf(stderr, "Invalid input: Could not convert string to int\n");
        exit(EXIT_FAILURE);
    } else if (*x < MINIMUM_WAREHOUSE_SIZE || *y < MINIMUM_WAREHOUSE_SIZE) {
        fprintf(stderr, "Warehouse too small: Size of warehouse must be at least 3 x 3\n");
        exit(EXIT_FAILURE);
    }
}

void PrintGrid(int y, int x ,int **grid) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void DeleteGrid(int y, int x, int **grid) {
    for (int i = 0; i < x; i++) {
        free(grid[i]);
    }
    free(grid);
}
