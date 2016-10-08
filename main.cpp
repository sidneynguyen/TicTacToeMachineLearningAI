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

    char play;
    cout << "Play against AI? [y/n]: ";
    cin >> play;
    if (play == 'y') {
        TTTAI Justin("Justin.lai", numRows, numCols, winCond);

        TTTBoard board(numRows, numCols);

        std::cout << board << std::endl;

        int player = 1;

        while (true) {
            int col;
            int row;
            std::cout << "Row: ";
            std::cin >> row;
            std::cout << "Column: ";
            std::cin >> col;
            board.move(row, col);
            Justin.addMove(row, col, player);
            player == 1 ? player = 2 : player = 1;
            cout << board << endl;
            int win = board.check(winCond);
            if (win != 0) {
                if (win == 3) {
                    std::cout << "TIE!!!" << endl;
                    Justin.tie();
                    break;
                }
                std::cout << "Player " << win << " wins!" << std::endl;
                if (win == 1) {
                    Justin.lose();
                } else {
                    Justin.win();
                }
                break;
            }
            pair<int, int> AIMove = Justin.move(player);
            board.move(AIMove.first, AIMove.second);
            player == 1 ? player = 2 : player = 1;
            cout << board << endl;
            win = board.check(winCond);
            if (win != 0) {
                if (win == 3) {
                    std::cout << "TIE!!!" << endl;
                    Justin.tie();
                    break;
                }
                std::cout << "Player " << win << " wins!" << std::endl;
                if (win == 2) {
                    Justin.win();
                } else {
                    Justin.lose();
                }
                break;
            }
        }
    } else {

        TTTAI Justin("Justin.lai", numRows, numCols, winCond);

        TTTAI Jack("Jack.cho", numRows, numCols, winCond);

        TTTBoard board(numRows, numCols);

        std::cout << board << std::endl;

        int player = 1;

        for (int i = 1; i <= 500; i++) {
            cout << "Game " << i << endl;
            while (true) {
                pair<int, int> AI1Move = Jack.move(player);
                board.move(AI1Move.first, AI1Move.second);
                Justin.addMove(AI1Move.first, AI1Move.second, player);
                player == 1 ? player = 2 : player = 1;
                cout << board << endl;
                int win = board.check(winCond);
                if (win != 0) {
                    if (win == 3) {
                        std::cout << "TIE!!!" << endl;
                        Justin.tie();
                        Jack.tie();
                        break;
                    }
                    std::cout << "Player " << win << " wins!" << std::endl;
                    if (win == 1) {
                        Justin.lose();
                        Jack.win();
                    } else {
                        Jack.lose();
                        Justin.win();
                    }
                    break;
                }
                pair<int, int> AIMove = Justin.move(player);
                board.move(AIMove.first, AIMove.second);
                Jack.addMove(AIMove.first, AIMove.second, player);
                player == 1 ? player = 2 : player = 1;
                cout << board << endl;
                win = board.check(winCond);
                if (win != 0) {
                    if (win == 3) {
                        std::cout << "TIE!!!" << endl;
                        Justin.tie();
                        Jack.tie();
                        break;
                    }
                    std::cout << "Player " << win << " wins!" << std::endl;
                    if (win == 2) {
                        Justin.win();
                        Jack.lose();
                    } else {
                        Justin.lose();
                        Jack.win();
                    }
                    break;
                }
            }
        }
    }

    return 0;
}
