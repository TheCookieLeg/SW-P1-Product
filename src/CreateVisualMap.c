//
// Created by lucas on 25-11-2025.
//
#include "raylib.h"

#include "CreateVisualMap.h"

#define GRID_SIZE 75

void CreateWindow(int x, int y, int** grid) {
    InitWindow(GRID_SIZE * x, GRID_SIZE * y, "Robot Simulation");

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

        EndDrawing();
    }

    CloseWindow();
}

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

        default: return BLACK;
    }
}