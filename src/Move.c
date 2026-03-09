#include "Move.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MOVE_INF 999999  /* sentinel value representing an unreachably large distance */

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
 *  MoveRobotGreedy(int**, int, int, Robot*)
 *  The robot moves one tile at a time based on a simple greedy heuristic.
 *  For each step, the robot evaluates the four neighbouring tiles (up, down,
 *  left, right) and picks the one with the smallest Manhattan distance to the
 *  target.  A visited array prevents the robot from revisiting the same tile
 *  within a single search attempt; it is reset whenever the robot gets stuck.
 */
void MoveRobotGreedy(int **grid, int height, int width, Robot *robot) {

    // Prevents movement attempts when the robot has already reached its target
    if (AtGoal(robot)) return;
    robot->visited[robot->row][robot->col] = 1;

    int moves[4][2] = {
        {-1, 0},  // up
        { 1, 0},  // down
        { 0,-1},  // left
        { 0, 1}   // right
    };

    int bestRow = robot->row;
    int bestCol = robot->col;
    int bestDist = MOVE_INF; // Large default value to ensure first valid move is chosen

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


        if (InBounds(newRow, newCol, height, width) && (grid[newRow][newCol] == 0 || grid[newRow][newCol] == 8) &&
!robot->visited[newRow][newCol]) {

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
    if (bestRow == robot->row && bestCol == robot->col) {
        // if bestRow and bestCol are the robots current position, it means no other moves were valid. So we reset the visited array
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                robot->visited[i][j] = 0;
            }
        }
        return;
    }
    // Updates the robot's position with the best candidate move
    grid[robot->row][robot->col] = 0;

    robot->row = bestRow;
    robot->col = bestCol;

    grid[robot->row][robot->col] = robot->id;

    if (AtGoal(robot))
        robot->active = 0;
}

/*
 *  MoveRobotBFS(int**, int, int, Robot*)
 *  Uses breadth-first search to find the shortest path from the robot's current
 *  position to its target.  The full path is recomputed every step so that the
 *  robot reacts to other robots blocking tiles.  BFS guarantees the shortest
 *  unweighted path; the robot then takes only the first step of that path.
 */
void MoveRobotBFS(int **grid, int height, int width, Robot *robot) {
    if (AtGoal(robot)) return;

    int total = height * width;
    int *parent  = malloc(total * sizeof(int));
    int *queue   = malloc(total * sizeof(int));
    int *visited = calloc(total, sizeof(int));

    if (!parent || !queue || !visited) {
        free(parent); free(queue); free(visited);
        return;
    }

    for (int i = 0; i < total; i++) parent[i] = -1;

    int startIdx = robot->row * width + robot->col;
    int goalIdx  = robot->targetRow * width + robot->targetCol;

    int head = 0, tail = 0;
    queue[tail++] = startIdx;
    visited[startIdx] = 1;

    int moves[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int found = 0;

    while (head < tail && !found) {
        int current = queue[head++];
        if (current == goalIdx) { found = 1; break; }

        int cr = current / width;
        int cc = current % width;

        for (int i = 0; i < 4; i++) {
            int nr = cr + moves[i][0];
            int nc = cc + moves[i][1];
            if (!InBounds(nr, nc, height, width)) continue;
            if (grid[nr][nc] != 0 && grid[nr][nc] != 8) continue;
            int nIdx = nr * width + nc;
            if (visited[nIdx]) continue;
            visited[nIdx] = 1;
            parent[nIdx] = current;
            queue[tail++] = nIdx;
        }
    }

    if (found) {
        // Trace back from goal to find the first step after the start
        int idx = goalIdx;
        while (parent[idx] != startIdx && parent[idx] != -1) {
            idx = parent[idx];
        }
        if (parent[idx] == startIdx) {
            int firstRow = idx / width;
            int firstCol = idx % width;
            grid[robot->row][robot->col] = 0;
            robot->row = firstRow;
            robot->col = firstCol;
            grid[robot->row][robot->col] = robot->id;
            if (AtGoal(robot)) robot->active = 0;
        }
    }

    free(parent); free(queue); free(visited);
}

/*
 *  MoveRobotAStar(int**, int, int, Robot*)
 *  Uses A* search with Manhattan distance as the admissible heuristic.
 *  Like MoveRobotBFS, the full path is recomputed every step so that dynamic
 *  obstacles (other robots) are handled correctly.  A* is typically faster than
 *  BFS because it focuses the search towards the goal.
 */
void MoveRobotAStar(int **grid, int height, int width, Robot *robot) {
    if (AtGoal(robot)) return;

    int total = height * width;
    int *g        = malloc(total * sizeof(int));
    int *f        = malloc(total * sizeof(int));
    int *parent   = malloc(total * sizeof(int));
    int *inOpen   = calloc(total, sizeof(int));
    int *inClosed = calloc(total, sizeof(int));

    if (!g || !f || !parent || !inOpen || !inClosed) {
        free(g); free(f); free(parent); free(inOpen); free(inClosed);
        return;
    }

    for (int i = 0; i < total; i++) {
        g[i] = MOVE_INF;
        f[i] = MOVE_INF;
        parent[i] = -1;
    }

    int startIdx = robot->row * width + robot->col;
    int goalIdx  = robot->targetRow * width + robot->targetCol;

    g[startIdx] = 0;
    f[startIdx]  = abs(robot->targetRow - robot->row) + abs(robot->targetCol - robot->col);
    inOpen[startIdx] = 1;

    int moves[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int found = 0;

    while (1) {
        // Find the open node with the lowest f-score
        int current = -1, minF = MOVE_INF;
        for (int i = 0; i < total; i++) {
            if (inOpen[i] && f[i] < minF) {
                minF = f[i];
                current = i;
            }
        }
        if (current == -1) break; // No path exists

        if (current == goalIdx) { found = 1; break; }

        inOpen[current]   = 0;
        inClosed[current] = 1;

        int cr = current / width;
        int cc = current % width;

        for (int i = 0; i < 4; i++) {
            int nr = cr + moves[i][0];
            int nc = cc + moves[i][1];
            if (!InBounds(nr, nc, height, width)) continue;
            if (grid[nr][nc] != 0 && grid[nr][nc] != 8) continue;
            int nIdx = nr * width + nc;
            if (inClosed[nIdx]) continue;

            int tentativeG = g[current] + 1;
            if (tentativeG < g[nIdx]) {
                parent[nIdx] = current;
                g[nIdx] = tentativeG;
                f[nIdx] = tentativeG + abs(robot->targetRow - nr) + abs(robot->targetCol - nc);
                inOpen[nIdx] = 1;
            }
        }
    }

    if (found) {
        // Trace back from goal to find the first step after the start
        int idx = goalIdx;
        while (parent[idx] != startIdx && parent[idx] != -1) {
            idx = parent[idx];
        }
        if (parent[idx] == startIdx) {
            int firstRow = idx / width;
            int firstCol = idx % width;
            grid[robot->row][robot->col] = 0;
            robot->row = firstRow;
            robot->col = firstCol;
            grid[robot->row][robot->col] = robot->id;
            if (AtGoal(robot)) robot->active = 0;
        }
    }

    free(g); free(f); free(parent); free(inOpen); free(inClosed);
}

/*
 *  MoveRobot(int**, int, int, Robot*)
 *  Dispatcher that calls the correct pathfinding algorithm based on the
 *  robot's assigned AI model (robot->model).
 */
void MoveRobot(int **grid, int height, int width, Robot *robot) {
    switch (robot->model) {
        case MODEL_BFS:
            MoveRobotBFS(grid, height, width, robot);
            break;
        case MODEL_ASTAR:
            MoveRobotAStar(grid, height, width, robot);
            break;
        case MODEL_GREEDY:
        default:
            MoveRobotGreedy(grid, height, width, robot);
            break;
    }
}

