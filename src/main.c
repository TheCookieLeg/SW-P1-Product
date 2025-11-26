#include <stdio.h>

#include "ReadMapFromFile.h"
#include "CreateVisualMap.h"
#include "RobotStruct.h"
int x = 0, y = 0;

int main(void) {

    int** grid = CreateGridMap(&x, &y);

    CreateWindow();

    // EKSMPEL PÅ ROBOT
    Robot robot = CreateRobot(1, 0, 0, 6, 6);



    DeleteGrid(y, x, grid);
    return 0;
}