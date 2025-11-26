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

    FillGridFromFile(gridFile, y, x, grid);
    PrintGrid(y, x, grid);


    fclose(gridFile);

    return grid;
}

/*
 *  GetWareHouseSize(FILE*, int*, int*)
 *  This function reads the first two numbers in the text file
 *  It then saves this into the x and y variables that are passed as pointers to the function
 *  It also looks at the numbers it receives. If strtol() returns 0, it means that the char could not be converted to an int
 *  And if one of the numbers are smaller than 3, it returns an error, as we want the grid to be at least 3x3
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

/*
 *  This just prints out the grid to the console
 *  Mostly used for testing and wont be relevant for the final program
*/
void PrintGrid(int y, int x ,int **grid) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

/*
 *  When using malloc, it is important to free up the memory that has been allocated, so we don't get a memory leak
 *  This function frees the memory
*/
void DeleteGrid(int y, int x, int **grid) {
    for (int i = 0; i < y; i++) {
        free(grid[i]);
    }
    free(grid);
}

/*
 *  This function is pivotal for the program
 *  It reads the file and fills out our 2D array with the info from the text file
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