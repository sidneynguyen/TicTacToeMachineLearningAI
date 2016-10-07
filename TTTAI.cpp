#include "TTTAI.h"

#include <iostream>

TTTAI::TTTAI(const char* dataFile, int r, int c, int cd):
        rows(r), cols(c), cond(cd) {
    // Open file for reading/writing
    fio = new fstream(dataFile, ios::out | ios::in);
    fio->seekg(0, ios::beg);
    std::streampos fileStart = fio->tellg();
    fio->seekg(0, ios::end);
    std::streampos fileEnd = fio->tellg();

    // Check if file is empty or not
    if (fileStart == fileEnd) {
        // Reserve space for root and write other properties
        fio->write((const char*) &root, sizeof(streampos));
        fio->write((const char*) &rows, sizeof(int));
        fio->write((const char*) &cols, sizeof(int));
        fio->write((const char*) &cond, sizeof(int));

        // Get location of root and write a new root
        root = fio->tellp();
        TTTNode rt(rows, cols, 1);
        rt.position = root;
        rt.write(fio);

        // Write location of root
        fio->seekp(0, ios::beg);
        fio->write((char*) &root, sizeof(streampos));
    } else {
        // Read location of root
        fio->seekg(0, ios::beg);
        fio->read((char*) &root, sizeof(streampos));
        fio->read((char*) &rows, sizeof(int));
        fio->read((char*) &cols, sizeof(int));
        fio->read((char*) &cond, sizeof(int));
        cerr << "File already contains some data" << endl;
    }

    cerr << "Root located at: " << root << endl;
    currentMove = root;

    fio->flush();

    for (int i = 0; i < rows; i++) {
        vector<int> row;
        for (int j = 0; j < cols; j++) {
            row.push_back(0);
        }
        pastMoves.push_back(row);
    }
}

TTTAI::~TTTAI() {
    delete fio;
}

pair<int, int> TTTAI::move(int turn) {
    cerr << "[Making a move]" << endl;
    // Read current move
    TTTNode curr(rows, cols, 0);
    curr.read(fio, currentMove);
    cerr << "Read current move at: " << currentMove << endl;
    // Get a move
    pair<int, int> coord = curr.findMove(pastMoves);
    cerr << "Found move: (" << coord.first << ", " << coord.second << ")"
            << endl;
    pastMoves[coord.first][coord.second] = 1;
    // Write new node to end of file
    TTTNode nextMove(rows, cols, turn);
    fio->seekp(0, ios::end);
    streampos newPos = fio->tellp();
    nextMove.position = newPos;
    nextMove.write(fio);
    // Update current move
    curr.setMovePos(coord.first, coord.second, newPos);
    curr.write(fio);
    // Next move
    currentMove = newPos;
    cerr << "Set current move to: " << currentMove << endl;
    return coord;
}

void TTTAI::addMove(int row, int col, int trn) {
    cerr << "[Adding a move]" << endl;
    // Read the current move
    TTTNode curr(rows, cols, 0);
    curr.read(fio, currentMove);
    cerr << "Read current move at: " << currentMove << endl;
    // Check if the move made already exists
    if (curr.moveExists(row, col)) {
        // Set current move to move just made
        currentMove = curr.getMove(row, col);
        cerr << "Move already exists" << endl;
    } else {
        // Create new move
        TTTNode newMove(rows, cols, trn);
        // Write new move to end of file
        fio->seekp(0, ios::end);
        streampos newPos = fio->tellp();
        newMove.position = newPos;
        newMove.write(fio);
        // Update current move
        curr.setMovePos(row, col, newPos);
        curr.write(fio);
        // Next move
        currentMove = newPos;
    }
    cerr << "Set current move to: " << currentMove << endl;
    pastMoves[row][col] = 1;
}

TTTNode::TTTNode(int rows, int cols, int trn) {
    position = 0;
    p1.wins = 0;
    p1.losses = 0;
    p1.ties = 0;
    p2.wins = 0;
    p2.losses = 0;
    p2.ties = 0;
    for (int i = 0; i < rows; i++) {
        vector<int> row;
        for (int j = 0; j < cols; j++) {
            row.push_back(0);
        }
        moves.push_back(row);
    }
    turn = trn;
}

TTTNode::~TTTNode() {

}

void TTTNode::read(fstream* fio, streampos pos) {
    fio->seekg(pos);
    fio->read((char*) &position, sizeof(streampos));
    fio->read((char*) &p1, sizeof(TTTStat));
    fio->read((char*) &p2, sizeof(TTTStat));
    fio->read((char*) &turn, sizeof(int));
    for (unsigned int i = 0; i < moves.size(); i++) {
        for (unsigned int j = 0; j < moves[j].size(); j++) {
            fio->read((char*) &moves[i][j], sizeof(int));
        }
    }
}

void TTTNode::write(fstream* fio) {
    fio->seekp(position);
    fio->write((char*) &position, sizeof(streampos));
    fio->write((char*) &p1, sizeof(TTTStat));
    fio->write((char*) &p2, sizeof(TTTStat));
    fio->write((char*) &turn, sizeof(int));
    for (unsigned int i = 0; i < moves.size(); i++) {
        for (unsigned int j = 0; j < moves[i].size(); j++) {
            fio->write((char*) &moves[i][j], sizeof(int));
        }
    }
}

pair<int, int> TTTNode::findMove(vector< vector<int> >& pMoves) {
    for (unsigned int i = 0; i < moves.size(); i++) {
        for (unsigned int j = 0; j < moves[i].size(); j++) {
            if (!moves[i][j] && pMoves[i][j] == 0) {
                return pair<int, int>(i, j);
            }
        }
    }
    return pair<int, int>(0, 0);
}

void TTTNode::setMovePos(int row, int col, streampos pos) {
    moves[row][col] = pos;
}

bool TTTNode::moveExists(int row, int col) {
    return moves[row][col] != 0;
}

int TTTNode::getMove(int row, int col) {
    return moves[row][col];
}
