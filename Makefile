all:
	rm Justin.lai
	touch Justin.lai
	g++ -g -Wall -o TicTacToe main.cpp TTTBoard.cpp TTTAI.cpp
clean:
	rm TicTacToe *.o
dump:
	hexdump -C Justin.lai
