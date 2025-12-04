//
// Created by Andreas Ramlov on 25/11/2025.
//

#ifndef P1_PRODUCT_ROBOTSTRUCT_H
#define P1_PRODUCT_ROBOTSTRUCT_H
typedef struct Robot {
    int id;         // unikt ID
    int row;        // nuværende række (y)
    int col;        // nuværende kolonne (x)
    int targetRow;  // mål-række (y)
    int targetCol;  // mål-kolonne (x)
    int active;     // aktiv =1, robot i mål =0
    int** visited;
} Robot;


// oprettelse af robot
Robot CreateRobot(int id, int startRow, int startCol, int targetRow, int targetCol, int x, int y);

#endif //P1_PRODUCT_ROBOTSTRUCT_H