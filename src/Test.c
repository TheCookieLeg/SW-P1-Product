#include <stdio.h>
#include <stdlib.h>

#include "RobotStruct.h"
#include "move.h"

// Print the grid and robot
void PrintGrid2(int **grid, int rows, int cols, Robot *robot) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {

            if (r == robot->row && c == robot->col)
                printf("R ");
            else if (grid[r][c] == 1)
                printf("# ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

// int main() {
//
//     int rows = 7, cols = 7;
//
//     int staticGrid[7][7] = {
//         {0,0,0,0,0,0,0},
//         {0,1,1,1,0,1,0},
//         {0,0,0,1,0,1,0},
//         {0,1,0,0,0,1,0},
//         {0,1,0,1,0,0,0},
//         {0,0,0,1,1,1,0},
//         {0,0,0,0,0,0,0}
//     };
//
//     int **grid = malloc(rows * sizeof(int*));
//     for (int r = 0; r < rows; r++) {
//         grid[r] = malloc(cols * sizeof(int));
//         for (int c = 0; c < cols; c++)
//             grid[r][c] = staticGrid[r][c];
//     }
//
//     Robot robot = CreateRobot(1, 0, 0, 6, 6);
//
//     printf("Initial:\n");
//     PrintGrid2(grid, rows, cols, &robot);
//
//     while (!AtGoal(&robot)) {
//
//         MoveRobot(grid, rows, cols, &robot);
//
//         PrintGrid2(grid, rows, cols, &robot);
//
//         // optional: delay for readability
//         // _sleep(200);
//     }
//
//     printf("Robot reached goal!\n");
//
//     for (int r = 0; r < rows; r++)
//         free(grid[r]);
//     free(grid);
//
//     return 0;
// }
//
