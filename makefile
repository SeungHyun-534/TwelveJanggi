#Makefile

CC = g++

Piece.o : Piece.cpp
	g++ -c Piece.cpp

Pawn.o : Pawn.cpp
	g++ -c  Pawn.cpp

Rook.o : Rook.cpp
	g++ -c Rook.cpp

Bishop.o : Bishop.cpp
	g++ -c Bishop.cpp

King.o : King.cpp
	g++ -c King.cpp

Square.o : Square.cpp
	g++ -c Square.cpp

PieceArray.o : PieceArray.cpp
	g++ -c PieceArray.cpp

Board.o : Board.cpp
	g++ -c Board.cpp

janggi_main.o : janggi_main.cpp
	g++ -c janggi_main.cpp

janggi : Piece.o Pawn.o Rook.o Bishop.o King.o Square.o PieceArray.o Board.o janggi_main.o
	g++ Piece.o Pawn.o Rook.o Bishop.o King.o Square.o PieceArray.o Board.o janggi_main.o -o janggi
