#include <iostream>
#include <vector>

#include "Pieces.h"
using namespace std;


void Board::movePiece(int x1, int y1, int x2, int y2) {
    //cout << lastPawnMove.x << lastPawnMove.y << boardMatrix[x1][y1]->getColor()<<endl;
    if((lastPawnMove.x == x2 && lastPawnMove.y == y2 - 1) || (lastPawnMove.x == x2 && lastPawnMove.y == y2 + 1)){
        if(boardMatrix[x1][y1]->give_id() == PieceId::pawn){
            boardMatrix[x2][y2] = boardMatrix[x1][y1];
            if (boardMatrix[x1][y1]->getColor() == PieceColor::white){
                delete boardMatrix[x2][y2-1];
                boardMatrix[x2][y2-1] = nullptr;
            }else{
                delete boardMatrix[x2][y2+1];
                boardMatrix[x2][y2+1] = nullptr;
            }
            boardMatrix[x1][y1] = nullptr;
        }
    }
    else if(boardMatrix[x1][y1] != nullptr) { // sprawdzenie czy na polu (x1,y1) jest jakakolwiek figura
        delete boardMatrix[x2][y2];
        boardMatrix[x2][y2] = boardMatrix[x1][y1]; // przeniesienie figury na pole (x2, y2)
        boardMatrix[x1][y1] = nullptr; // usunięcie figury z pola (x1, y1)
    } 
    else{
        cout << "Wrong" << endl;
    }
}

void Board::promote(int x, int y, int promo, PieceColor color){
    switch(promo){
        case 0:
            // kon
            delete boardMatrix[x][y];
            boardMatrix[x][y] = new Knight(color);
            break;
        case 1:
            // bishop
            delete boardMatrix[x][y];
            boardMatrix[x][y] = new Bishop(color);
            break;

        case 2:
            // rook
            delete boardMatrix[x][y];
            boardMatrix[x][y] = new Rook(color);
            break;
        
        case 3:
            // queen
            delete boardMatrix[x][y];
            boardMatrix[x][y] = new Queen(color);
            break;
    }
}

// Sprawdzanie wszystkich ruchow dla danego koloru
vector<vector<pair<int,int>>> Board::checkMoves(PieceColor color, Board board){
    vector<vector<pair<int,int>>> moves;
    
    for(int x = 0; x <=7; x++){
        for(int y = 0; y <= 7; y++){
            if(boardMatrix[x][y] != nullptr && boardMatrix[x][y]->getColor() == color){
                vector<pair<int,int>> movesForPiece;
                movesForPiece = boardMatrix[x][y]->possibleMoves(x, y, board);
                moves.push_back(movesForPiece);
                //for (const pair<int, int> &p : movesForPiece) {
                //    cout << "(" << p.first << ", " << p.second << ") ";
                //}
                //cout<<endl;
            }
        }
    }
    return moves;
}

void Board::updateCurrentPlayer(PieceColor player) {
        currentPlayer = player;
}

bool Board::isCheck(PieceColor color) {
    int king_x, king_y;
    // szukanie krola
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardMatrix[i][j] != nullptr && boardMatrix[i][j]->getColor() == color && boardMatrix[i][j]->give_id() == PieceId::king) {
                king_x = i;
                king_y = j;
                //cout<<"xd"<<endl;
                break;
            }
        }
    }
    // sprawdzanie czy ktorys z figur przeciwnika moze pojsc na pole krola
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardMatrix[i][j] != nullptr && boardMatrix[i][j]->getColor() != color) {
                auto moves = boardMatrix[i][j]->possibleMoves(i, j, *this);
                for (auto move : moves) {
                    if (move.first == king_x && move.second == king_y) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isCheckCastle(int x, int y, PieceColor color){
    //cout<<color;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardMatrix[i][j] != nullptr && boardMatrix[i][j]->getColor() != color && boardMatrix[i][j]->give_id() != PieceId::king) {
                auto moves = boardMatrix[i][j]->possibleMoves(i, j, *this);
                for (auto move : moves) {
                    if (move.first == x && move.second == y) {
                        return true;
                    }
                }
            }
        }
    }
    return false;    
}


bool Board::isCheckmate(PieceColor color) {
    if (!isCheck(color))
        return false;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardMatrix[i][j] != nullptr && boardMatrix[i][j]->getColor() == color) {
                vector<pair<int, int>> possible_moves = boardMatrix[i][j]->possibleMoves(i, j, *this);
                for (auto move : possible_moves) {
                    if (!willBeCheckAfterMove(i, j, move.first, move.second, color))
                        return false;
                }
            }
        }
    }
    return true;
}


bool Board::isStalemate(PieceColor color){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (boardMatrix[i][j] != nullptr && boardMatrix[i][j]->getColor() == color) {
                vector<pair<int, int>> possible_moves = boardMatrix[i][j]->possibleMoves(i, j, *this);
                for (auto move : possible_moves) {
                    if (!willBeCheckAfterMove(i, j, move.first, move.second, color))
                        return false;
                }
            }
        }
    }
    return true;
}

bool Board::willBeCheckAfterMove(int x1, int y1, int x2, int y2, PieceColor color) {
    Piece* piece = boardMatrix[x1][y1];
    Piece* capturedPiece = boardMatrix[x2][y2];
    boardMatrix[x1][y1] = nullptr;
    boardMatrix[x2][y2] = piece;
    bool check = isCheck(color);
    boardMatrix[x2][y2] = capturedPiece;
    boardMatrix[x1][y1] = piece;
    //cout<<"willbe"<<endl;
    return check;
}

void Board::updateLastPawnMove(int x, int y, PieceColor color) {
    
    lastPawnMove.x = x;
    lastPawnMove.y = y;
    lastPawnMove.color = color;
}

LastPawnMove Board::getLastPawnMove(){
    return lastPawnMove;
}

void Board::printBoard(){
    cout<<endl;
    cout<<"    a   b   c   d   e   f   g   h"<<endl;
    for(int row = 7; row >= 0; row--){
        cout<< row + 1 << " |";
        for(int col = 0; col < 8; col++){
            if (boardMatrix[col][row] == nullptr){
                cout << "   |";
                continue;
            }
            //cout << boardMatrix[col][row]->getColor();
            if(boardMatrix[col][row]->getColor() == PieceColor::black){
                cout<<" ";
                //cout << "\033[1;30m" << boardMatrix[col][row]->give_id() <<"\033[0m" << " |"; // czarne
                cout << "\033[1;34m" << boardMatrix[col][row]->give_id() <<"\033[0m" << " |"; // niebieskie
            }
            else{
                cout<<" ";
                cout << "\033[1;37m" << boardMatrix[col][row]->give_id() <<"\033[0m" << " |";
            }
        }
        cout<<" "<< row + 1<<endl;
        if(row != 0)cout<<"  |---|---|---|---|---|---|---|---|"<<endl;
    }
    cout<<"    a   b   c   d   e   f   g   h"<<endl;
    
    cout<<endl;

    
}
