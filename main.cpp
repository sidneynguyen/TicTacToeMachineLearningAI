/*
 * Author: Sidney Nguyen
 * Date Created: Oct 6, 2016
 */
#include <iostream>
#include "TTTBoard.h"

int main() {
    int numRows = 3;
    int numCols = 3;
    int winCond = 3;

    int row = 0;
    int col = 0;
    char cont = 'y';

    TTTBoard board(numRows, numCols);

    std::cout << board << std::endl;
    
    while (cont == 'y') {
        std::cout << "Row: ";
        std::cin >> row;
        std::cout << "Column: ";
        std::cin >> col;
        board.move(row, col);
        std::cout << board << std::endl;
        int win = board.check(winCond);
        if (win != 0) {
            std::cout << "Player " << win << " wins!" << std::endl;
            break;
        }
        std::cout << "Continue? [y/n]: ";
        std::cin >> cont;
    }

    return 0;
}
