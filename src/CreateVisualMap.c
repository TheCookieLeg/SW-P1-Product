//
// Created by lucas on 25-11-2025.
//
#include "raylib.h"

#include "CreateVisualMap.h"
#include "RobotStruct.h"
#include "Move.h"


/**
 * Creates a GUI window to visualize the grid map
 * @param x The size of the grid on the x-axis
 * @param y The size of the grid on the y-axis
 * @param grid A 2D array of integers
 */
void CreateWindow(int x, int y, int** grid) {
    InitWindow(GRID_SIZE * x, GRID_SIZE * y, "Robot Simulation");

    Robot robots[] = {
        CreateRobot(2, 0, 0, 6, 6),
    };

    for (int i = 0; i < sizeof(robots) / sizeof(Robot); i++) {
        grid[robots[i].row][robots[i].col] = robots[i].id;
        grid[robots[i].targetRow][robots[i].targetCol] = 8;
    }


    while (!WindowShouldClose())
    {
        int row = 0, col = 0;
        BeginDrawing();
        ClearBackground(WHITE);
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                DrawRectangle(col, row, GRID_SIZE, GRID_SIZE, NumberToColor(grid[i][j]));
                DrawRectangleLines(col, row, GRID_SIZE, GRID_SIZE, BLACK);
                col += GRID_SIZE;
            }
            col = 0;
            row += GRID_SIZE;
        }


        for (int i = 0; i < sizeof(robots) / sizeof(Robot); i++) {
            MoveRobot(grid, y, x, &robots[i]);
        }

        Sleep(750);
        EndDrawing();
    }

    CloseWindow();
}

/**
 * The function takes a number and converts it into a color struct, which is then returned
 * @param x A number from the gridmap
 * @return Returns a color struct
 */
struct Color NumberToColor(int x) {

    switch (x) {
        case 0: return WHITE;
        case 1: return DARKGRAY;
        case 2: return RED;
        case 3: return GREEN;
        case 4: return BLUE;
        case 5: return YELLOW;
        case 6: return PINK;
        case 7: return ORANGE;
        case 8: return LIGHTGRAY;

        default: return BLACK;
    }
}