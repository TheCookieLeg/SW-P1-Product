//
// Created by lucas on 25-11-2025.
//

#ifndef P1_PRODUCT_CREATEVISUALMAP_H
#define P1_PRODUCT_CREATEVISUALMAP_H
#include "RobotStruct.h"
#include "raylib.h"

#define GRID_SIZE 50

void CreateWindow(int x, int y, int** grid, Robot* robot);
Color NumberToColor(int x);

#endif //P1_PRODUCT_CREATEVISUALMAP_H

