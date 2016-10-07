all:
	g++ -g -Wall -o TicTacToe main.cpp TTTBoard.cpp
clean:
	rm TicTacToe *.o
