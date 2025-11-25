//
// Created by lucas on 24-11-2025.
//
#ifndef P1_PRODUCT_READMAPFROMFILE_H
#define P1_PRODUCT_READMAPFROMFILE_H
#include <stdio.h>


int** CreateGridMap(int* px, int* py);
void GetWarehouseSize(FILE* file, int* x, int* y);
void PrintGrid(int y, int x ,int **grid);
void DeleteGrid(int y, int x, int **grid);
void FillGridFromFile(FILE* file, int y, int x, int **grid);

#endif //P1_PRODUCT_READMAPFROMFILE_H