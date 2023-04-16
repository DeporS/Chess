CC = g++ -g -Wall

main: Chess.o Pieces.o Game.o Board.o
	$(CC) -o main Chess.o Pieces.o Game.o Board.o
Chess.o: Chess.cpp Pieces.h
	$(CC) -c Chess.cpp
Pieces.o: Pieces.cpp Pieces.h
	$(CC) -c Pieces.cpp
Game.o: Game.cpp Pieces.h
	$(CC) -c Game.cpp
Board.o: Board.cpp Pieces.h
	$(CC) -c Board.cpp

clean: 
	del *.o *.exe