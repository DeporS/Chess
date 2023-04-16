#include <iostream>
#include <vector>
#include <cmath>

#include "Pieces.h"
using namespace std;

void Game::start() {
    board = Board();  // tworzy nowa szachownice
    gameOver = false; // ustawia stan gry na false
    checkmate = false;
    stalemate = false;
    cout<<endl<<"=====================";
    cout <<endl<< "The game is starting!" << endl;
    cout<<"====================="<<endl<<endl;
    cout <<"Correct use of coordinates: 'a2', 'b5', 'g8'..."<< endl;
}

void Game::makeMove(int x1, int y1, int x2, int y2){
    vector<pair<int,int>> moves;
    if(board.willBeCheckAfterMove(x1,y1,x2,y2,currentPlayer)){
        cout<<endl<<"-------------------"<<endl;
        cout<<"Invalid move(check)"<<endl;
        cout<<"-------------------"<<endl;
    }
    else if(board.boardMatrix[x1][y1] != nullptr){
        if(board.boardMatrix[x1][y1]->getColor() == currentPlayer){
            auto lpm = board.getLastPawnMove();
            moves = board.boardMatrix[x1][y1]->possibleMoves(x1,y1,board);
            if (lpm.color == currentPlayer){
                if (currentPlayer == PieceColor::black){
                    board.updateLastPawnMove(8, 8, PieceColor::white);
                }else{
                    board.updateLastPawnMove(8, 8, PieceColor::black);
                }
            }
        }
        
        int i = 0;
        for (const pair<int, int> &p : moves) {
            if (p.first == x2 && p.second == y2){
                // En passant
                if(board.boardMatrix[x1][y1]->give_id() == PieceId::pawn) {
                    if(abs(y1 - y2) == 2){
                        board.updateLastPawnMove(x2, y2, board.boardMatrix[x1][y1]->getColor());
                    }
                }

                // Roszada
                if(board.boardMatrix[x1][y1]->give_id() == PieceId::king && !board.boardMatrix[x1][y1]->moved()) {
                    if(x1 == 4 & x2 == 6){
                        board.movePiece(x1+3,y1,x1+1,y1);
                    }
                    else if(x1 == 4 & x2 == 2){
                        board.movePiece(x1-4,y1,x1-1,y1);
                    }
                }

                // Potrzebne do roszady
                if(board.boardMatrix[x1][y1]->give_id() == PieceId::king || board.boardMatrix[x1][y1]->give_id() == PieceId::rook){
                    board.boardMatrix[x1][y1]->addMove();
                }
                

                board.movePiece(x1,y1,x2,y2);
                // Promotion
                if(board.boardMatrix[x2][y2]->give_id() == PieceId::pawn) {
                    if((board.boardMatrix[x2][y2]->getColor() == PieceColor::white && y2 == 7) || (board.boardMatrix[x2][y2]->getColor() == PieceColor::black && y2 == 0)){
                        cout<<"0 - knight\n"<<"1 - bishop\n"<<"2 - rook\n"<<"3 - queen"<<endl;
                        int promo;
                        cin >> promo;
                        board.promote(x2, y2, promo, board.boardMatrix[x2][y2]->getColor());
                    }
                }
                switchPlayer();
                i++;
                break;
            }

        }
        if(i==0){
            cout<<endl<<"---------------"<<endl;
            cout<<"Can't move here"<<endl;
            cout<<"---------------"<<endl;
        }
    }
    else{
        cout<<endl<<"---------------"<<endl;
        cout<<"Move your piece"<<endl;
        cout<<"---------------"<<endl;
    }
    //auto lastPawnMove = board.getLastPawnMove();
    //cout<<lastPawnMove.x<< " , " << lastPawnMove.y << " , " << lastPawnMove.color << endl;
}

void Game::checkGameOver() {
    if(board.isCheckmate(currentPlayer)) {
        gameOver = true;
        checkmate = true;
        
    } else if (board.isStalemate(currentPlayer)) {
        gameOver = true;
        stalemate = true;
        
    }
}

bool Game::isCheckmate() {
    return checkmate;
}

bool Game::isStalemate(){
    return stalemate;
}

bool Game::isGameOver(){
    return gameOver;
}

PieceColor Game::getCurrentPlayer() {
    return currentPlayer;
}

void Game::switchPlayer() {
    if(currentPlayer == PieceColor::white) {
        currentPlayer = PieceColor::black;
    } else {
        currentPlayer = PieceColor::white;
    }
}

void Game::printCurrentBoard(){
    board.printBoard();
}