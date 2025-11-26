//
// Created by lucas on 25-11-2025.
//
#include "raylib.h"

#include "CreateVisualMap.h"

void CreateWindow() {
    InitWindow(1280, 720, "Robot Simulation");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("THE WINDOW WORKS", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
}