#ifndef _PIECES_H_
#define _PIECES_H_

#include <iostream>
#include <vector>

using namespace std;

enum class PieceId { pawn, rook , knight, bishop, queen, king };
enum class PieceColor{ white, black };

class Piece;
class Pawn;
class Rook;
class Board;


inline ostream& operator << (ostream& stream, PieceColor col){
    switch (col)
    {
        case PieceColor::white:
            stream << "w";
            break;
        case PieceColor::black:
            stream << "b";
            break;
    }
    return stream;
    
}

inline ostream& operator << (ostream& stream, PieceId id){
    switch (id)
    {
        case PieceId::pawn:
            stream << "p";
            break;
        case PieceId::bishop:
            stream << "B";
            break;
        case PieceId::rook:
            stream << "R";
            break;
        case PieceId::knight:
            stream << "N";
            break;
        case PieceId::queen:
            stream << "Q";
            break;
        case PieceId::king:
            stream << "K";
            break;
    }
    return stream;
}

// Figury
class Piece {
private:
    PieceColor color;
    PieceId id;
    bool moved_already;

    
public:
    Piece(PieceColor color) : color(color), moved_already(false) {}
    //Piece(PieceColor color);
    PieceColor getColor();
    bool moved();
    void addMove();

    virtual vector<pair<int,int>> possibleMoves(int, int, Board) const = 0;
    virtual PieceId give_id() const = 0;

    //friend Board;
};

// Pionek
class Pawn : public Piece{

public:
    Pawn(PieceColor color) : Piece(color) {};

    PieceId give_id() const override;
    vector<pair<int,int>> possibleMoves(int, int, Board) const override; 
};

// Goniec
class Bishop : public Piece{

public:
    Bishop(PieceColor color) : Piece(color) {};

    PieceId give_id() const override;
    vector<pair<int,int>> possibleMoves(int, int, Board) const override;
};

// Kon
class Knight : public Piece{

public:
    Knight(PieceColor color) : Piece(color) {};

    PieceId give_id() const override;
    vector<pair<int,int>> possibleMoves(int, int, Board) const override;
};

// Wieza
class Rook : public Piece{

public:
    Rook(PieceColor color) : Piece(color) {};

    PieceId give_id() const override;

    vector<pair<int,int>> possibleMoves(int, int, Board) const override;
};

// Krolowa
class Queen : public Piece{

public:
    Queen(PieceColor color) : Piece(color) {};

    PieceId give_id() const override;
    vector<pair<int,int>> possibleMoves(int, int, Board) const override;
};

// Krol
class King : public Piece{

public:
    King(PieceColor color) : Piece(color) {};

    PieceId give_id() const override;
    vector<pair<int,int>> possibleMoves(int, int, Board) const override;
};

// Struktura zapisujaca ostatnie ruchy piona, w przypadku gdy ten ruszy sie o dwa pola
struct LastPawnMove {
    int x;
    int y;
    PieceColor color;
};

// Szachownica
class Board{
    PieceColor currentPlayer;
    LastPawnMove lastPawnMove;


public:
    vector<vector<Piece*>> boardMatrix;


public:
    Board() {
        boardMatrix = vector<vector<Piece*>>(8, vector<Piece*>(8, nullptr));
        currentPlayer = PieceColor::white;


        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
 
                if (col == 1){
                    boardMatrix[row][col] = new Pawn(PieceColor::white);
                }
                if (col == 6){
                    boardMatrix[row][col] = new Pawn(PieceColor::black);
                }
                if ((row == 0 || row == 7) && (col == 0)){
                    boardMatrix[row][col] = new Rook(PieceColor::white);
                }
                if ((row == 0 || row == 7) && (col == 7)){
                    boardMatrix[row][col] = new Rook(PieceColor::black);
                }
                if ((row == 2 || row == 5) && (col == 0)){
                    boardMatrix[row][col] = new Bishop(PieceColor::white);
                }
                if ((row == 2 || row == 5) && (col == 7)){
                    boardMatrix[row][col] = new Bishop(PieceColor::black);
                }
                if ((row == 1 || row == 6) && (col == 0)){
                    boardMatrix[row][col] = new Knight(PieceColor::white);
                }
                if ((row == 1 || row == 6) && (col == 7)){
                    boardMatrix[row][col] = new Knight(PieceColor::black);
                }
                if ((row == 4) && (col == 0)){
                    boardMatrix[row][col] = new King(PieceColor::white);
                }
                if ((row == 4) && (col == 7)){
                    boardMatrix[row][col] = new King(PieceColor::black);
                }
                if ((row == 3) && (col== 0)){
                    boardMatrix[row][col] = new Queen(PieceColor::white);
                }
                if ((row == 3) && (col == 7)){
                    boardMatrix[row][col] = new Queen(PieceColor::black);
                }

                /*if ((row == 3) && (col == 5)){
                    boardMatrix[row][col] = new Queen(PieceColor::black);
                }
                if ((row == 3) && (col == 4)){
                    boardMatrix[row][col] = new Knight(PieceColor::black);
                }
                if ((row == 7) && (col == 3)){
                    boardMatrix[row][col] = new Pawn(PieceColor::black);
                }
                if ((row == 0) && (col == 4)){
                    boardMatrix[row][col] = new Pawn(PieceColor::white);
                }*/
            }
        }
    }

    vector<vector<pair<int,int>>> checkMoves(PieceColor, Board);
    void movePiece(int, int, int, int);
    bool isCheckmate(PieceColor);
    bool isStalemate(PieceColor);
    bool isCheck(PieceColor);
    bool isCheckCastle(int, int, PieceColor);
    bool willBeCheckAfterMove(int, int, int, int, PieceColor);
    void updateCurrentPlayer(PieceColor);
    void updateLastPawnMove(int, int, PieceColor);
    LastPawnMove getLastPawnMove();
    void promote(int, int, int, PieceColor);
    void printBoard();
};

// Gra
class Game {
private:
    Board board;
    PieceColor currentPlayer;
    bool gameOver;
    bool checkmate;
    bool stalemate;

public:
    Game() : currentPlayer(PieceColor::white), gameOver(false), checkmate(false), stalemate(false) {};

    void start();
    void makeMove(int x1, int y1, int x2, int y2);
    void checkGameOver();
    bool isCheckmate();
    bool isStalemate();
    bool isGameOver();
    PieceColor getCurrentPlayer();
    void switchPlayer();
    void printCurrentBoard();
};



#endif