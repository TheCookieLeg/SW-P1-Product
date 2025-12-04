//
// Created by Andreas Ramlov on 25/11/2025.
//
#include "RobotStruct.h"

#include <stdlib.h>
#include <stdio.h>
// Opretelse af robot samt giver start og mål position

Robot CreateRobot(int id, int startRow, int startCol, int targetRow, int targetCol, int x, int y) {
    Robot r;
    r.id = id;

    r.row = startRow,
    r.col = startCol;

    r.targetRow = targetRow;
    r.targetCol = targetCol;

    r.active = 1 ; // robotten er aktiv indtil den rammer ind i målet

    r.visited = calloc(y, sizeof(int*));
    if (!r.visited) {
        perror("Calloc for robot");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < y; i++) {
        r.visited[i] = calloc(x, sizeof(int));
        if (!r.visited[i]) {
            perror("Calloc for robot");
            exit(EXIT_FAILURE);
        }
    }

    return r;
}