#include <iostream>
#include "colors.h"
#include "board.h"
using namespace std;

Board::Board()
{
    for (int row = 0; row < NB_ROW; row++)
        for (int col = 0; col < NB_COL; col++)
            grid[row][col] = EMPTY;
}

bool Board::IsMovePossible(int col)
{
    if (col < 0 || col >= NB_COL)
        return false;

    return grid[NB_ROW - 1][col] == EMPTY;
}

bool Board::MakeMove(int col, Color color)
{
    if (!IsMovePossible(col))
        return false;

    for (int row = 0; row < NB_ROW; row++)
    {
        if (grid[row][col] == EMPTY)
        {
            grid[row][col] = color;
            return true;
        }
    }

    return false;
}

void Board::Print()
{
    for (int row = NB_ROW - 1; row >= 0; row--)
    {
        cout << '|';
        for (int col = 0; col < NB_COL; col++)
        {
            switch (grid[row][col])
            {
            case EMPTY:
                cout << ' ';
                break;
            case YELLOW:
                cout << "\033[33m█\033[0m";
                break;
            case RED:
                cout << "\033[31m█\033[0m";
                break;
            default:
                break;
            }
            cout << "|";
        }
        cout << '\n' << "---------------" << '\n';
    }
    
    cout << " 0 1 2 3 4 5 6\n\n";
}

Color Board::IsFinished()
{
    for (int row = 0; row < NB_ROW; row++)
    {
        for (int col = 0; col < NB_COL; col++)
        {
            Color c = grid[row][col];
            if (c == EMPTY)
                continue;

            // Horizontal
            if (col <= 3 &&
                c == grid[row][col + 1] &&
                c == grid[row][col + 2] &&
                c == grid[row][col + 3])
                return c;

            // Vertical
            if (row <= 2 &&
                c == grid[row + 1][col] &&
                c == grid[row + 2][col] &&
                c == grid[row + 3][col])
                return c;

            // Diagonale
            if (row <= 2 && col <= 3 &&
                c == grid[row + 1][col + 1] &&
                c == grid[row + 2][col + 2] &&
                c == grid[row + 3][col + 3])
                return c;


            if (row >= 3 && col <= 3 &&
                c == grid[row - 1][col + 1] &&
                c == grid[row - 2][col + 2] &&
                c == grid[row - 3][col + 3])
                return c;
        }
    }

    return EMPTY; 
}

bool Board::IsFull()
{
    for (int col = 0; col < NB_COL; col++)
        if (grid[NB_ROW - 1][col] == EMPTY)
            return false;
    return true;
}

Color Board::getSquare(int row, int col)
{
    return grid[row][col];
}
