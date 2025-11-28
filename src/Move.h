#ifndef P1_PRODUCT_MOVE_H
#define P1_PRODUCT_MOVE_H

#include "RobotStruct.h"

int AtGoal(Robot *r);
int InBounds(int row, int col, int height, int width);
void MoveRobot(int **grid, int height, int width, Robot *robot);

#endif //P1_PRODUCT_MOVE_H
