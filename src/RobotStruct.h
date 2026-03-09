//
// Created by Andreas Ramlov on 25/11/2025.
//

#ifndef P1_PRODUCT_ROBOTSTRUCT_H
#define P1_PRODUCT_ROBOTSTRUCT_H

// AI models available for robot pathfinding
typedef enum {
    MODEL_GREEDY,  // greedy Manhattan distance heuristic (original)
    MODEL_BFS,     // breadth-first search (guaranteed shortest path)
    MODEL_ASTAR    // A* search (optimal with heuristic)
} AIModel;

typedef struct Robot {
    int id;         // unikt ID
    int row;        // nuværende række (y)
    int col;        // nuværende kolonne (x)
    int targetRow;  // mål-række (y)
    int targetCol;  // mål-kolonne (x)
    int active;     // aktiv =1, robot i mål =0
    int** visited;
    AIModel model;  // which pathfinding algorithm the robot uses
} Robot;


// oprettelse af robot
Robot CreateRobot(int id, int startRow, int startCol, int targetRow, int targetCol, int x, int y, AIModel model);

#endif //P1_PRODUCT_ROBOTSTRUCT_H