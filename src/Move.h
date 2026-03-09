#ifndef P1_PRODUCT_MOVE_H
#define P1_PRODUCT_MOVE_H

#include "RobotStruct.h"

int AtGoal(Robot *r);
int InBounds(int row, int col, int height, int width);

// Greedy Manhattan distance heuristic (original algorithm)
void MoveRobotGreedy(int **grid, int height, int width, Robot *robot);

// Breadth-first search – always finds the shortest path
void MoveRobotBFS(int **grid, int height, int width, Robot *robot);

// A* search – optimal pathfinding using Manhattan distance heuristic
void MoveRobotAStar(int **grid, int height, int width, Robot *robot);

// Dispatches to the correct algorithm based on robot->model
void MoveRobot(int **grid, int height, int width, Robot *robot);

#endif //P1_PRODUCT_MOVE_H
