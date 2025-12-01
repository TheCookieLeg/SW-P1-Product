//
// Created by lucas on 24-11-2025.
//

#include "ReadMapFromFile.h"

#include <stdio.h>
#include <stdlib.h>

#define MINIMUM_WAREHOUSE_SIZE 3

/**
 * Creates a grid map given the size of the grid map
 * @param px A pointer to the x-variable
 * @param py A pointer to the y-variable
 * @return A 2D array of integers
 */
int** CreateGridMap(int* px, int* py) {

    FILE* gridFile = fopen("../TextFiles/GridMap.txt", "r"); // Reads our input file

    if (gridFile == NULL) { // Checks if the compiler can find the file
        perror("File could not be found. Try again");
        exit(EXIT_FAILURE);
    }

    GetWarehouseSize(gridFile, px, py);
    printf("x: %d\ny: %d\n", *px, *py); //TBD

    int** grid = calloc(*py, sizeof(int*)); // This creates all the rows (vertical)
    if (!grid) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *py; i++) {
        grid[i] = calloc(*px, sizeof(int)); // Then for each row, x columns are created, giving us a 2D array
        if (!grid[i]) {
            perror("calloc");
            exit(EXIT_FAILURE);
        }
    }

    FillGridFromFile(gridFile, *py, *px, grid);
    PrintGrid(*py, *px, grid);


    fclose(gridFile);

    return grid;
}

/**
 * Sets the x and y to the size of the warehouse
 * @param file File to read a gridmap from
 * @param x How many elements are on the x-axis. Must be greater than 2
 * @param y How many elements are on the y-axis. Must be greater than 2
 */
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

/**
 * Prints the 2D array to the console
 * @param y The size of the grid on the y-axis
 * @param x The size of the grid on the x-axis
 * @param grid A 2D array of integers
 */
void PrintGrid(int y, int x ,int **grid) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

/**
 * Frees the grid from memory
 * @param y The size of the grid on the y-axis
 * @param x The size of the grid on the x-axis
 * @param grid A 2D array of integers
 */
void DeleteGrid(int y, int x, int **grid) {
    for (int i = 0; i < y; i++) {
        free(grid[i]);
    }
    free(grid);
}

/**
 * Reads the given file and writes it into the 2D array
 * @param file File with the gridmap
 * @param y The size of the grid on the y-axis
 * @param x The size of the grid on the x-axis
 * @param grid A 2D array of integers
 */
void FillGridFromFile(FILE* file, int y, int x, int **grid) {
    int row = 0, col = 0; // Used to keep track of where we are in the array
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n' || c == '\r') { // In windows, line breaks can be both \n and \r. But on mac, it only uses \r. So this is just to make sure that it works for any operating system
            if (col > 0) {  // Sometimes the first character on a new line is \n. We do this to make sure that we only go to the next row, if we've actually read the line
                row++;
                col = 0;
            }
        } else {
            if (row < y && col < x) { // Makes sure we dont go out of bounds
                grid[row][col] = c - '0';  // Converts a character into an int using ASCII code. Only works for digits, so 0-9
                if (grid[row][col] > 9) {
                    perror("An invalid character has been used in the textfile. Make sure only numbers 0-9 are used.");
                    exit(EXIT_FAILURE);
                }
                col++;

            } else {
                perror("Program went out of bounds while trying to read text file. Check if text file is correct");
                exit(EXIT_FAILURE);
            }
        }
    }
}