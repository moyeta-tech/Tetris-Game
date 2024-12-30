#pragma once
#include "vector"
#include "raylib.h"

class Grid
{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    bool isCellOutside(int row, int column);
    bool isCellEmpty(int row, int column);
    int clearFullRows();
    int grid[20][10];
private:
    bool isRowFull(int row);
    void clearRow(int row);
    void moverRowDown(int row, int numRows);
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};