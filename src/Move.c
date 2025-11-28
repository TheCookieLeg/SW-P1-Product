#include "Move.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 *  AtGoal(Robot*)
 *  This function checks whether the robot has reached its destination.
 *  The robot has a targetRow and targetCol, and if its current position matches
 *  this location, the function returns 1 (true).
 */
int AtGoal(Robot *r) {
    return (r->row == r->targetRow && r->col == r->targetCol);
}

/*
 *  InBounds(int, int, int, int)
 *  This function ensures that the robot does not move outside the warehouse grid.
 *  It checks whether the row and column indices are within the width and height
 *  of the grid. If the robot attempted to move outside, the movement would result
 *  in undefined behavior, so this check prevents that.
 */
int InBounds(int row, int col, int height, int width) {
    return (row >= 0 && row < height && col >= 0 && col < width);
}

/*
 *  MoveRobot(int**, int, int, Robot*)
 *  The robot moves one tile at a time based on a simple heuristic approach.
 *  For each step, the robot evaluates the four neighboring tiles (up, down,
 *  left, right). It only considers valid tiles:
 */

static int visited[20][20]={0};

void MoveRobot(int **grid, int height, int width, Robot *robot) {

    // Prevents movement attempts when the robot has already reached its target
    if (AtGoal(robot)) return;
    visited[robot->row][robot->col] = 1;

    int moves[4][2] = {
        {-1, 0},  // up
        { 1, 0},  // down
        { 0,-1},  // left
        { 0, 1}   // right
    };

    int bestRow = robot->row;
    int bestCol = robot->col;
    int bestDist = 999999; // Large default value to ensure first valid move is chosen

    /*
     *  This for-loop holds  all four possible movement directions.
     *  For each direction, a candidate row/column is calculated.
     *  The loop then checks:
     *      (1) if the tile is inside the grid
     *      (2) if the tile contains no obstacle
     *
     *  If both conditions are satisfied, the Manhattan distance from
     *  the candidate tile to the target is calculated. The tile with
     *  the smallest distance is selected as the next movement step.
     */
    for (int i = 0; i < 4; i++) {

        int newRow = robot->row + moves[i][0];
        int newCol = robot->col + moves[i][1];


        if (InBounds(newRow, newCol, height, width) && grid[newRow][newCol] == 0 &&
!visited[newRow][newCol]) {

            // Manhattan distance used as a simple heuristic
            int dist = abs(robot->targetRow - newRow) + abs(robot->targetCol - newCol);

            // Selects the move that gets the robot closest to its target
            if (dist < bestDist) {
                bestDist = dist;
                bestRow = newRow;
                bestCol = newCol;
            }
        }
    }

    // Updates the robot's position with the best candidate move
    robot->row = bestRow;
    robot->col = bestCol;

    if (AtGoal(robot))
        robot->active = 0;
}

