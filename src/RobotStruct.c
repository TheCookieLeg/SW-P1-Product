//
// Created by Andreas Ramlov on 25/11/2025.
//
#include "RobotStruct.h"
// Opretelse af robot samt giver start og mål position

Robot CreateRobot(int id, int startRow, int startCol, int targetRow, int targetCol) {
    Robot r = {0}; // Sets everything to zero, including all elements in the visited array
    r.id = id;

    r.row = startRow,
    r.col = startCol;

    r.targetRow = targetRow;
    r.targetCol = targetCol;

    r.active = 1 ; // robotten er aktiv indtil den rammer ind i målet

    return r;
}