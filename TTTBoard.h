#ifndef TTT_BOARD_H
#define TTT_BOARD_H

#include <vector>
#include <iostream>

class TTTBoard {

public:

    TTTBoard(int rows, int cols);

    ~TTTBoard();

    bool move(int row, int col);

    int check(int cond);

    void draw(std::ostream& stream) const;

private:
    
    std::vector< std::vector<int> > board;

    int turn;

};

std::ostream& operator<<(std::ostream& stream, const TTTBoard& board);

#endif
