#include <stdio.h>

#include "ReadMapFromFile.h"
#include "CreateVisualMap.h"

int x = 0, y = 0;

int main(void) {

    int** grid = CreateGridMap(&x, &y);
    printf("x: %d, y: %d", x, y);
    CreateWindow(x, y, grid);


    DeleteGrid(y, x, grid);
    return 0;
}