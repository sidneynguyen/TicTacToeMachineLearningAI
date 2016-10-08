#ifndef TTT_AI_H
#define TTT_AI_H

#include <fstream>
#include <vector>

using namespace std;

typedef long offset;

class TTTAI {

public:

    TTTAI(const char* dataFile, int r, int c, int cd);

    ~TTTAI();

    pair<int, int> move(int turn);

    void addMove(int row, int col, int trn);
    void win();
    void lose();
    void tie();

private:
    fstream* fio;

    streampos root;
    streampos currentMove;
    vector< vector<int> > pastMoves;
    int player;
    int rows;
    int cols;
    int cond;
    vector<int> madeMoves;

};

struct TTTStat {
    int wins;
    int losses;
    int ties;
};

class TTTNode {

public:
    streampos position;

    TTTNode(int rows, int cols, int trn);

    ~TTTNode();

    void read(fstream* fio, streampos pos);
    void write(fstream* fio);

    pair<int, int> findMove(fstream* fio, vector< vector<int> >& pMoves);
    void setMovePos(int row, int col, streampos pos);
    bool moveExists(int row, int col);
    int getMove(int row, int col);
    int getScore();
    void win();
    void lose();
    void tie();

private:

    TTTStat stats;
    int turn;
    std::vector< std::vector<int> > moves;
};

#endif
