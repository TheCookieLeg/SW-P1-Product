//
// Created by lucas on 24-11-2025.
//

#include "ReadMapFromFile.h"

#include <stdio.h>
#include <stdlib.h>

#define MINIMUM_WAREHOUSE_SIZE 3

int** CreateGridMap() {
    int x = 0;
    int y = 0;
    FILE* gridFile = fopen("TextFiles/GridMap.txt", "r");
    if (gridFile == NULL) { // Checks if the compiler can find the file
        perror("File could not be found. Try again");
        exit(EXIT_FAILURE);
    }

    GetWarehouseSize(gridFile, &x, &y);
    printf("x: %d\ny: %d", x, y);


    fclose(gridFile);
    return 0;
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