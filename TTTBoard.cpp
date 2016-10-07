#include "TTTBoard.h"

TTTBoard::TTTBoard(int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        std::vector<int> row;
        for (int j = 0; j < cols; j++) {
            row.push_back(0);
        }
        board.push_back(row);
    }
    turn = 1;
}

TTTBoard::~TTTBoard() {

}

bool TTTBoard::move(int row, int col) {
    if (board[row][col] == 0) {
        board[row][col] = turn;
        turn == 1 ? turn = 2 : turn = 1;
        return true;
    }
    return false;
}

int TTTBoard::check(int cond) {
    for (unsigned int i = 0; i <= board.size() - cond; i++) {
        for (unsigned int j = 0; j < board[i].size(); j++) {
            int player = board[i][j];
            if (player != 0) {
                for (int k = 1; k < cond; k++) {
                    if (board[i + k][j] != player) {
                        break;
                    } else if (k == cond - 1) {
                        return player;
                    }
                }
            }
        }
    }
    for (unsigned int i = 0; i <= board[0].size() - cond; i++) {
        for (unsigned int j = 0; j < board.size(); j++) {
            int player = board[j][i];
            if (player != 0) {
                for (int k = 1; k < cond; k++) {
                    if (board[j][i + k] != player) {
                        break;
                    } else if (k == cond - 1) {
                        return player;
                    }
                }
            }
        }
    }
    for (unsigned int i = 0; i <= board.size() - cond; i++) {
        for (unsigned int j = 0; j <= board[i].size() - cond; j++) {
            int player = board[j][i];
            if (player != 0) {
                for (int k = 1; k < cond; k++) {
                    if (board[i + k][j + k] != player) {
                        break;
                    } else if (k == cond - 1) {
                        return player;
                    }
                }
            }
        }
    }
    return 0;
}

void TTTBoard::draw(std::ostream& stream) const {
    for (unsigned int i = 0; i < board.size(); i++) {
        for (unsigned int j = 0; j < board[i].size(); j++) {
            stream << " " << board[i][j] << " ";
            if (j < board[i].size() - 1) {
                stream << "|";
            }
        }
        if (i < board.size() - 1) {
            std::cout << std::endl;
            for (unsigned int k = 0; k < 4 * board[i].size() - 1; k++) {
                stream << "-";
            }
            stream << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& stream, const TTTBoard& board) {
    board.draw(stream);
    return stream;
}
