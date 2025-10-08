#pragma once

#include <iostream>
#include "colors.h"

#define NB_ROW 6
#define NB_COL 7


class Board
{
    private:
        Color grid[NB_ROW][NB_COL];

    public:
        Board();
        bool IsMovePossible(int col);
        bool MakeMove(int col, Color color);
        void Print();
        Color IsFinished();
        bool IsFull();
        Color getSquare(int row, int col);
};
