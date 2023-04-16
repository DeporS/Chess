#include <iostream>
#include <vector>

#include "Pieces.h"
using namespace std;

//Piece::Piece(PieceColor color) : color(color) {}

PieceColor Piece::getColor() {
    return color;
}

bool Piece::moved(){
    return moved_already;
}
void Piece::addMove(){
    moved_already = true;
}


// Pion
PieceId Pawn::give_id() const{
    return PieceId::pawn;
}
// Goniec
PieceId Bishop::give_id() const{
    return PieceId::bishop;
}
// Kon
PieceId Knight::give_id() const{
    return PieceId::knight;
}
// Wieza
PieceId Rook::give_id() const{
    return PieceId::rook;
}
// Krolowa
PieceId Queen::give_id() const{
    return PieceId::queen;
}
// Krol
PieceId King::give_id() const{
    return PieceId::king;
}




// Sprawdzanie mozliwych ruchow dla piona
vector<pair<int,int>> Pawn::possibleMoves(int x, int y, Board board) const{
    vector<pair<int,int>> moves;
    

    // Ruch o dwa pola do przodu białego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white && y == 1){
        if(board.boardMatrix[x][y+2] == nullptr && board.boardMatrix[x][y+1] == nullptr){
            moves.push_back(make_pair(x,y+2));
        } 
    }

    // Ruch o dwa pola do przodu czarnego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::black && y == 6){
        if(board.boardMatrix[x][y-2] == nullptr && board.boardMatrix[x][y-1] == nullptr){
            moves.push_back(make_pair(x,y-2));
        } 
    }

    // Rucho o jedno pole do przodu białego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white && board.boardMatrix[x][y+1] == nullptr){
        moves.push_back(make_pair(x,y+1));
        
    }

    // Rucho o jedno pole do przodu czarnego
    else if(board.boardMatrix[x][y]->getColor() == PieceColor::black && board.boardMatrix[x][y-1] == nullptr){
        moves.push_back(make_pair(x,y-1));
    }
    
    auto lastPawnMove = board.getLastPawnMove();
    // Bicie Białego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white){
        if(x-1 >= 0){
            if(board.boardMatrix[x-1][y+1] != nullptr){
                if(board.boardMatrix[x-1][y+1]->getColor() == PieceColor::black){
                    moves.push_back(make_pair(x-1,y+1));
                }
            }
            if(lastPawnMove.x != -1){
                if(x-1 == lastPawnMove.x && y == lastPawnMove.y && lastPawnMove.color == PieceColor::black){
                    moves.push_back(make_pair(x-1,y+1));
                }
            }
        }
        if(x+1 <= 7){
            if(board.boardMatrix[x+1][y+1] != nullptr){
                if(board.boardMatrix[x+1][y+1]->getColor() == PieceColor::black){
                    moves.push_back(make_pair(x+1,y+1));
                }
            }
            if(lastPawnMove.x != -1){
                if(x+1 == lastPawnMove.x && y == lastPawnMove.y && lastPawnMove.color == PieceColor::black){
                    moves.push_back(make_pair(x+1,y+1));
                }
            }
        }
    }
    //Bicie czarnego 
    else if(board.boardMatrix[x][y]->getColor() == PieceColor::black) {
        if(x-1 >= 0){
            if(board.boardMatrix[x-1][y-1] != nullptr){
                if(board.boardMatrix[x-1][y-1]->getColor() == PieceColor::white){
                    moves.push_back(make_pair(x-1,y-1));
                }
            }
            if(lastPawnMove.x != -1){
                if(x-1 == lastPawnMove.x && y == lastPawnMove.y && lastPawnMove.color == PieceColor::white){
                    moves.push_back(make_pair(x-1,y-1));
                }
            }
        }
        if(x+1 <= 7){
            if(board.boardMatrix[x+1][y-1] != nullptr){
                if(board.boardMatrix[x+1][y-1]->getColor() == PieceColor::white){
                    moves.push_back(make_pair(x+1,y-1));
                }
            }
            if(lastPawnMove.x != -1){
                if(x+1 == lastPawnMove.x && y == lastPawnMove.y && lastPawnMove.color == PieceColor::white){
                    moves.push_back(make_pair(x+1,y-1));
                }
            }
        }
    }
    
    //cout<<lastPawnMove.x<< " , " << lastPawnMove.y << lastPawnMove.color << endl;
    

    return moves;
}


// Sprawdzanie ruchow dla wiezy
vector<pair<int,int>> Rook::possibleMoves(int x, int y, Board board) const{
    vector<pair<int,int>> moves;
    
    
    // Ruch pionowy białego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white){
        for(int i = 1; i < 8; i++){
            if(y-i >= 0){
                if(board.boardMatrix[x][y-i] == nullptr){
                    moves.push_back(make_pair(x,y-i));
                }
                else if(board.boardMatrix[x][y-i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x,y-i));
                    break;
                    
                }
            }
            else{
                break;
            }
            
        }
        for(int i = 1; i < 8; i++){
            if(y+i <= 7){
                if(board.boardMatrix[x][y+i] == nullptr){
                    moves.push_back(make_pair(x,y+i));
                }
                else if(board.boardMatrix[x][y+i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x,y+i));
                    break;

                }
            }
            else{
                break;
            }
        }
    }
    
    // Ruch pionowy czarnego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::black){
        for(int i = 1; i < 8; i++){
            if(y-i >= 0){
                if(board.boardMatrix[x][y-i] == nullptr){
                    moves.push_back(make_pair(x,y-i));
                }
                else if(board.boardMatrix[x][y-i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x,y-i));
                    break;

                }
            }
            else{
                break;
            }
        }
        for(int i = 1; i < 8; i++){
            if(y+i <= 7){
                if(board.boardMatrix[x][y+i] == nullptr){
                    moves.push_back(make_pair(x,y+i));
                }
                else if(board.boardMatrix[x][y+i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x,y+i));
                    break;

                }
            }
            else{
                break;
            }
        }
    }
    
    // Ruch poziomy białego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white){
        for(int i = 1; i < 8; i++){
            if(x-i >= 0){
                if(board.boardMatrix[x-i][y] == nullptr){
                    moves.push_back(make_pair(x-i,y));
                }
                else if(board.boardMatrix[x-i][y]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y));
                    break;

                }
            }
            else{
                break;
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7){
                if(board.boardMatrix[x+i][y] == nullptr){
                    moves.push_back(make_pair(x+i,y));
                }
                else if(board.boardMatrix[x+i][y]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y));
                    break;
                }
            }
            else{
                break;
            }
        }
    }
    
    // Ruch poziomy czarnego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::black){
        for(int i = 1; i < 8; i++){
            if(x-i >= 0){
                if(board.boardMatrix[x-i][y] == nullptr){
                    moves.push_back(make_pair(x-i,y));
                }
                else if(board.boardMatrix[x-i][y]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y));
                    break;

                }
            }
            else{
                break;
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7){
                if(board.boardMatrix[x+i][y] == nullptr){
                    moves.push_back(make_pair(x+i,y));
                }
                else if(board.boardMatrix[x+i][y]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y));
                    break;
                }
            }
            else{
                break;
            }
        }
    }
    
    return moves;
}

// Sprawdzanie ruchow dla gonca
vector<pair<int,int>> Bishop::possibleMoves(int x, int y, Board board) const{
    vector<pair<int,int>> moves;

    //Sprawdzanie ruchow bialego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white){
        // ruchy ukosne: /
        for(int i = 1; i < 8; i++){
            if(x-i >= 0 && y+i <= 7){
                if(board.boardMatrix[x-i][y+i] == nullptr){
                    moves.push_back(make_pair(x-i,y+i));
                }
                else if(board.boardMatrix[x-i][y+i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y+i));
                    break;
                    
                }
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7 && y-i >= 0){
                if(board.boardMatrix[x+i][y-i] == nullptr){
                    moves.push_back(make_pair(x+i,y-i));
                }
                else if(board.boardMatrix[x+i][y-i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y-i));
                    break;
                    
                }
            }
        }
        // Ruchy ukosne: te drugie
        for(int i = 1; i < 8; i++){
            if(x-i >= 0 && y-i >= 0){
                if(board.boardMatrix[x-i][y-i] == nullptr){
                    moves.push_back(make_pair(x-i,y-i));
                }
                else if(board.boardMatrix[x-i][y-i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y-i));
                    break;
                    
                }
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7 && y+i <= 7){
                if(board.boardMatrix[x+i][y+i] == nullptr){
                    moves.push_back(make_pair(x+i,y+i));
                }
                else if(board.boardMatrix[x+i][y+i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y+i));
                    break;
                    
                }
            }
        }
    }
    //Sprawdzanie ruchow czarnego
    else{
        // ruchy ukosne: /
        for(int i = 1; i < 8; i++){
            if(x-i >= 0 && y+i <= 7){
                if(board.boardMatrix[x-i][y+i] == nullptr){
                    moves.push_back(make_pair(x-i,y+i));
                }
                else if(board.boardMatrix[x-i][y+i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y+i));
                    break;
                    
                }
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7 && y-i >= 0){
                if(board.boardMatrix[x+i][y-i] == nullptr){
                    moves.push_back(make_pair(x+i,y-i));
                }
                else if(board.boardMatrix[x+i][y-i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y-i));
                    break;
                    
                }
            }
        }
        // Ruchy ukosne: te drugie
        for(int i = 1; i < 8; i++){
            if(x-i >= 0 && y-i >= 0){
                if(board.boardMatrix[x-i][y-i] == nullptr){
                    moves.push_back(make_pair(x-i,y-i));
                }
                else if(board.boardMatrix[x-i][y-i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y-i));
                    break;
                    
                }
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7 && y+i <= 7){
                if(board.boardMatrix[x+i][y+i] == nullptr){
                    moves.push_back(make_pair(x+i,y+i));
                }
                else if(board.boardMatrix[x+i][y+i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y+i));
                    break;
                    
                }
            }
        }
    }

    return moves;
}

// Sprawdzanie ruchow dla konia
vector<pair<int,int>> Knight::possibleMoves(int x, int y, Board board) const{
    vector<pair<int,int>> moves;

    // Ruchy białego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white){
        if(x-2 >= 0 && y-1 >= 0){
            if(board.boardMatrix[x-2][y-1] == nullptr || board.boardMatrix[x-2][y-1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x-2,y-1));
            }
        }
        if(x-2 >= 0 && y+1 <= 7){
            if(board.boardMatrix[x-2][y+1] == nullptr || board.boardMatrix[x-2][y+1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x-2,y+1));
            }
        }
        if(x-1 >= 0 && y-2 >= 0){
            if(board.boardMatrix[x-1][y-2] == nullptr || board.boardMatrix[x-1][y-2]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x-1,y-2));
            }
        }
        if(x-1 >= 0 && y+2 <= 7){
            if(board.boardMatrix[x-1][y+2] == nullptr || board.boardMatrix[x-1][y+2]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x-1,y+2));
            }
        }
        if(x+1 <= 7 && y-2 >= 0){
            if(board.boardMatrix[x+1][y-2] == nullptr || board.boardMatrix[x+1][y-2]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x+1,y-2));
            }
        }
        if(x+1 <= 7 && y+2 <= 7){
            if(board.boardMatrix[x+1][y+2] == nullptr || board.boardMatrix[x+1][y+2]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x+1,y+2));
            }
        }
        if(x+2 <= 7 && y-1 >= 0){
            if(board.boardMatrix[x+2][y-1] == nullptr || board.boardMatrix[x+2][y-1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x+2,y-1));
            }
        }
        if(x+2 <= 7 && y+1 <= 7){
            if(board.boardMatrix[x+2][y+1] == nullptr || board.boardMatrix[x+2][y+1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x+2,y+1));
            }
        }
    }
    // Ruchy czarnego
    else{
        if(x-2 >= 0 && y-1 >= 0){
            if(board.boardMatrix[x-2][y-1] == nullptr || board.boardMatrix[x-2][y-1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x-2,y-1));
            }
        }
        if(x-2 >= 0 && y+1 <= 7){
            if(board.boardMatrix[x-2][y+1] == nullptr || board.boardMatrix[x-2][y+1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x-2,y+1));
            }
        }
        if(x-1 >= 0 && y-2 >= 0){
            if(board.boardMatrix[x-1][y-2] == nullptr || board.boardMatrix[x-1][y-2]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x-1,y-2));
            }
        }
        if(x-1 >= 0 && y+2 <= 7){
            if(board.boardMatrix[x-1][y+2] == nullptr || board.boardMatrix[x-1][y+2]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x-1,y+2));
            }
        }
        if(x+1 <= 7 && y-2 >= 0){
            if(board.boardMatrix[x+1][y-2] == nullptr || board.boardMatrix[x+1][y-2]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x+1,y-2));
            }
        }
        if(x+1 <= 7 && y+2 <= 7){
            if(board.boardMatrix[x+1][y+2] == nullptr || board.boardMatrix[x+1][y+2]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x+1,y+2));
            }
        }
        if(x+2 <= 7 && y-1 >= 0){
            if(board.boardMatrix[x+2][y-1] == nullptr || board.boardMatrix[x+2][y-1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x+2,y-1));
            }
        }
        if(x+2 <= 7 && y+1 <= 7){
            if(board.boardMatrix[x+2][y+1] == nullptr || board.boardMatrix[x+2][y+1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x+2,y+1));
            }
        }
    }

    return moves;
}

// Sprawdzanie ruchow dla krolowej
vector<pair<int,int>> Queen::possibleMoves(int x, int y, Board board) const{
    vector<pair<int,int>> moves;

    // Ruch pionowy białego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white){
        for(int i = 1; i < 8; i++){
            if(y-i >= 0){
                if(board.boardMatrix[x][y-i] == nullptr){
                    moves.push_back(make_pair(x,y-i));
                }
                else if(board.boardMatrix[x][y-i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x,y-i));
                    break;
                    
                }
            }
            else{
                break;
            }
            
        }
        for(int i = 1; i < 8; i++){
            if(y+i <= 7){
                if(board.boardMatrix[x][y+i] == nullptr){
                    moves.push_back(make_pair(x,y+i));
                }
                else if(board.boardMatrix[x][y+i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x,y+i));
                    break;

                }
            }
            else{
                break;
            }
        }
    }
    
    // Ruch pionowy czarnego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::black){
        for(int i = 1; i < 8; i++){
            if(y-i >= 0){
                if(board.boardMatrix[x][y-i] == nullptr){
                    moves.push_back(make_pair(x,y-i));
                }
                else if(board.boardMatrix[x][y-i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x,y-i));
                    break;

                }
            }
            else{
                break;
            }
        }
        for(int i = 1; i < 8; i++){
            if(y+i <= 7){
                if(board.boardMatrix[x][y+i] == nullptr){
                    moves.push_back(make_pair(x,y+i));
                }
                else if(board.boardMatrix[x][y+i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x,y+i));
                    break;

                }
            }
            else{
                break;
            }
        }
    }
    
    // Ruch poziomy białego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white){
        for(int i = 1; i < 8; i++){
            if(x-i >= 0){
                if(board.boardMatrix[x-i][y] == nullptr){
                    moves.push_back(make_pair(x-i,y));
                }
                else if(board.boardMatrix[x-i][y]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y));
                    break;

                }
            }
            else{
                break;
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7){
                if(board.boardMatrix[x+i][y] == nullptr){
                    moves.push_back(make_pair(x+i,y));
                }
                else if(board.boardMatrix[x+i][y]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y));
                    break;
                }
            }
            else{
                break;
            }
        }
    }
    
    // Ruch poziomy czarnego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::black){
        for(int i = 1; i < 8; i++){
            if(x-i >= 0){
                if(board.boardMatrix[x-i][y] == nullptr){
                    moves.push_back(make_pair(x-i,y));
                }
                else if(board.boardMatrix[x-i][y]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y));
                    break;

                }
            }
            else{
                break;
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7){
                if(board.boardMatrix[x+i][y] == nullptr){
                    moves.push_back(make_pair(x+i,y));
                }
                else if(board.boardMatrix[x+i][y]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y));
                    break;
                }
            }
            else{
                break;
            }
        }
    }

    //Sprawdzanie ruchow bialego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white){
        // ruchy ukosne: /
        for(int i = 1; i < 8; i++){
            if(x-i >= 0 && y+i <= 7){
                if(board.boardMatrix[x-i][y+i] == nullptr){
                    moves.push_back(make_pair(x-i,y+i));
                }
                else if(board.boardMatrix[x-i][y+i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y+i));
                    break;
                    
                }
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7 && y-i >= 0){
                if(board.boardMatrix[x+i][y-i] == nullptr){
                    moves.push_back(make_pair(x+i,y-i));
                }
                else if(board.boardMatrix[x+i][y-i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y-i));
                    break;
                    
                }
            }
        }
        // Ruchy ukosne: te drugie
        for(int i = 1; i < 8; i++){
            if(x-i >= 0 && y-i >= 0){
                if(board.boardMatrix[x-i][y-i] == nullptr){
                    moves.push_back(make_pair(x-i,y-i));
                }
                else if(board.boardMatrix[x-i][y-i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y-i));
                    break;
                    
                }
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7 && y+i <= 7){
                if(board.boardMatrix[x+i][y+i] == nullptr){
                    moves.push_back(make_pair(x+i,y+i));
                }
                else if(board.boardMatrix[x+i][y+i]->getColor() == PieceColor::white){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y+i));
                    break;
                    
                }
            }
        }
    }
    //Sprawdzanie ruchow czarnego
    else{
        // ruchy ukosne: /
        for(int i = 1; i < 8; i++){
            if(x-i >= 0 && y+i <= 7){
                if(board.boardMatrix[x-i][y+i] == nullptr){
                    moves.push_back(make_pair(x-i,y+i));
                }
                else if(board.boardMatrix[x-i][y+i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y+i));
                    break;
                    
                }
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7 && y-i >= 0){
                if(board.boardMatrix[x+i][y-i] == nullptr){
                    moves.push_back(make_pair(x+i,y-i));
                }
                else if(board.boardMatrix[x+i][y-i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y-i));
                    break;
                    
                }
            }
        }
        // Ruchy ukosne: te drugie
        for(int i = 1; i < 8; i++){
            if(x-i >= 0 && y-i >= 0){
                if(board.boardMatrix[x-i][y-i] == nullptr){
                    moves.push_back(make_pair(x-i,y-i));
                }
                else if(board.boardMatrix[x-i][y-i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x-i,y-i));
                    break;
                    
                }
            }
        }
        for(int i = 1; i < 8; i++){
            if(x+i <= 7 && y+i <= 7){
                if(board.boardMatrix[x+i][y+i] == nullptr){
                    moves.push_back(make_pair(x+i,y+i));
                }
                else if(board.boardMatrix[x+i][y+i]->getColor() == PieceColor::black){
                    break;
                }
                else{
                    moves.push_back(make_pair(x+i,y+i));
                    break;
                    
                }
            }
        }
    }
    
    return moves;
}

// Sprawdzanie ruchow dla krola
vector<pair<int,int>> King::possibleMoves(int x, int y, Board board) const{
    vector<pair<int,int>> moves;

    // Ruchy bialego
    if(board.boardMatrix[x][y]->getColor() == PieceColor::white){
        if(x-1 >= 0 && y-1 >= 0){
            if(board.boardMatrix[x-1][y-1] == nullptr || board.boardMatrix[x-1][y-1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x-1,y-1));
            }
        }
        if(x-1 >= 0){
            if(board.boardMatrix[x-1][y] == nullptr || board.boardMatrix[x-1][y]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x-1,y));
            }
        }
        if(x-1 >= 0 && y+1 <= 7){
            if(board.boardMatrix[x-1][y+1] == nullptr || board.boardMatrix[x-1][y+1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x-1,y+1));
            }
        }
        if(y-1 >= 0){
            if(board.boardMatrix[x][y-1] == nullptr || board.boardMatrix[x][y-1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x,y-1));
            }
        }
        if(y+1 <= 7){
            if(board.boardMatrix[x][y+1] == nullptr || board.boardMatrix[x][y+1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x,y+1));
            }
        }
        if(x+1 <= 7 && y-1 >= 0){
            if(board.boardMatrix[x+1][y-1] == nullptr || board.boardMatrix[x+1][y-1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x+1,y-1));
            }
        }
        if(x+1 <= 7){
            if(board.boardMatrix[x+1][y] == nullptr || board.boardMatrix[x+1][y]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x+1,y));
            }
        }
        if(x+1 <= 7 && y+1 <= 7){
            if(board.boardMatrix[x+1][y+1] == nullptr || board.boardMatrix[x+1][y+1]->getColor() == PieceColor::black){
                moves.push_back(make_pair(x+1,y+1));
            }
        }
        // roszada prawa
        if(!board.boardMatrix[x][y]->moved() && !board.isCheckCastle(x,y,PieceColor::white)){
            if(board.boardMatrix[x+1][y] == nullptr && !board.isCheckCastle(x+1,y,PieceColor::white)){
                if(board.boardMatrix[x+2][y] == nullptr && !board.isCheckCastle(x+2,y,PieceColor::white)){
                    if(board.boardMatrix[x+3][y] != nullptr){
                        if(board.boardMatrix[x+3][y]->give_id() == PieceId::rook && !board.boardMatrix[x+3][y]->moved()){
                            moves.push_back(make_pair(x+2,y));
                        }
                    }
                }
            }
        }
        // roszada lewa
        if(!board.boardMatrix[x][y]->moved() && !board.isCheckCastle(x,y,PieceColor::white)){
            if(board.boardMatrix[x-1][y] == nullptr && !board.isCheckCastle(x-1,y,PieceColor::white)){
                if(board.boardMatrix[x-2][y] == nullptr && !board.isCheckCastle(x-2,y,PieceColor::white)){
                    if(board.boardMatrix[x-3][y] == nullptr){
                        if(board.boardMatrix[x-4][y] != nullptr){
                            if(board.boardMatrix[x-4][y]->give_id() == PieceId::rook && !board.boardMatrix[x-4][y]->moved()){
                                moves.push_back(make_pair(x-2,y));
                            }
                        }
                    }
                }
            }
        }

    }   
    // Ruchy czarnego
    else{
        if(x-1 >= 0 && y-1 >= 0){
            if(board.boardMatrix[x-1][y-1] == nullptr || board.boardMatrix[x-1][y-1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x-1,y-1));
            }
        }
        if(x-1 >= 0){
            if(board.boardMatrix[x-1][y] == nullptr || board.boardMatrix[x-1][y]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x-1,y));
            }
        }
        if(x-1 >= 0 && y+1 <= 7){
            if(board.boardMatrix[x-1][y+1] == nullptr || board.boardMatrix[x-1][y+1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x-1,y+1));
            }
        }
        if(y-1 >= 0){
            if(board.boardMatrix[x][y-1] == nullptr || board.boardMatrix[x][y-1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x,y-1));
            }
        }
        if(y+1 <= 7){
            if(board.boardMatrix[x][y+1] == nullptr || board.boardMatrix[x][y+1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x,y+1));
            }
        }
        if(x+1 <= 7 && y-1 >= 0){
            if(board.boardMatrix[x+1][y-1] == nullptr || board.boardMatrix[x+1][y-1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x+1,y-1));
            }
        }
        if(x+1 <= 7){
            if(board.boardMatrix[x+1][y] == nullptr || board.boardMatrix[x+1][y]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x+1,y));
            }
        }
        if(x+1 <= 7 && y+1 <= 7){
            if(board.boardMatrix[x+1][y+1] == nullptr || board.boardMatrix[x+1][y+1]->getColor() == PieceColor::white){
                moves.push_back(make_pair(x+1,y+1));
            }
        }
        // roszada prawa
        if(!board.boardMatrix[x][y]->moved() && !board.isCheckCastle(x,y,PieceColor::black)){
            if(board.boardMatrix[x+1][y] == nullptr && !board.isCheckCastle(x+1,y,PieceColor::black)){
                if(board.boardMatrix[x+2][y] == nullptr && !board.isCheckCastle(x+2,y,PieceColor::black)){
                    if(board.boardMatrix[x+3][y] != nullptr){
                        if(board.boardMatrix[x+3][y]->give_id() == PieceId::rook && !board.boardMatrix[x+3][y]->moved()){
                            moves.push_back(make_pair(x+2,y));
                        }
                    }
                }
            }
        }
        // roszada lewa
        if(!board.boardMatrix[x][y]->moved() && !board.isCheckCastle(x,y,PieceColor::black)){
            if(board.boardMatrix[x-1][y] == nullptr && !board.isCheckCastle(x-1,y,PieceColor::black)){
                if(board.boardMatrix[x-2][y] == nullptr && !board.isCheckCastle(x-2,y,PieceColor::black)){
                    if(board.boardMatrix[x-3][y] == nullptr){
                        if(board.boardMatrix[x-4][y] != nullptr){
                            if(board.boardMatrix[x-4][y]->give_id() == PieceId::rook && !board.boardMatrix[x-4][y]->moved()){
                                moves.push_back(make_pair(x-2,y));
                            }
                        }
                    }
                }
            }
        }

    }
    return moves;
}

