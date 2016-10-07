/*
 * Author: Sidney Nguyen
 * Date Created: Oct 6, 2016
 */
#include <iostream>
#include "TTTBoard.h"
#include "TTTAI.h"

int main() {
    int numRows = 3;
    int numCols = 3;
    int winCond = 3;

    int row = 0;
    int col = 0;

    TTTAI Justin("Justin.lai", numRows, numCols, winCond);

    TTTBoard board(numRows, numCols);

    std::cout << board << std::endl;

    int player = 1;

    while (true) {
        std::cout << "Row: ";
        std::cin >> row;
        std::cout << "Column: ";
        std::cin >> col;
        board.move(row, col);
        std::cout << board << std::endl;
        Justin.addMove(row, col, player);
        player == 1 ? player = 2 : player = 1;
        int win = board.check(winCond);
        if (win != 0) {
            std::cout << "Player " << win << " wins!" << std::endl;
            break;
        }
        pair<int, int> AIMove = Justin.move(player);
        board.move(AIMove.first, AIMove.second);
        player == 1 ? player = 2 : player = 1;
        cout << board << endl;
        win = board.check(winCond);
        if (win != 0) {
            std::cout << "Player " << win << " wins!" << std::endl;
            break;
        }
    }

    return 0;
}
