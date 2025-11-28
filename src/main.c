#include <stdio.h>

#include "ReadMapFromFile.h"
#include "CreateVisualMap.h"
#include "RobotStruct.h"

int main(void) {
    int x = 0, y = 0;
    int** grid = CreateGridMap(&x, &y);

    Robot r = CreateRobot(1, 0, 0, 6, 6);

    CreateWindow(x, y, grid, &r);   // nu 4 argumenter

    DeleteGrid(y, x, grid);
    return 0;
}
