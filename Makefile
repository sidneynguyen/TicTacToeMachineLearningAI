all:
	g++ -g -Wall -o TicTacToe main.cpp TTTBoard.cpp TTTAI.cpp
	touch Justin.lai Jack.cho
clean:
	touch TicTacToe *.o Justin.lai Jack.cho
	rm TicTacToe *.o Justin.lai Jack.cho
new:
	make clean
	make all
dump:
	hexdump -C Justin.lai
