//
// Created by Andreas Ramlov on 25/11/2025.
//
#include "RobotStruct.h"
// Opretelse af robot samt giver start og mål position

Robot CreateRobot(int id, int startRow, int startCol, int targetRow, int targetCol) {
    return (Robot){
        .id = id,
        .row = startRow,
        .col = startCol,
        .targetRow = targetRow,
        .targetCol = targetCol,
        .active = 1
    };
}
