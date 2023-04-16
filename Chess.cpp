#include <iostream>
#include <vector>

#include "Pieces.h"



using namespace std;

// Sprawdzanie ruchow dla jednej figury (do testow)
vector<pair<int,int>> checkMove(int x, int y, Board chessBoard){
    vector<pair<int,int>> moves;
    moves = chessBoard.boardMatrix[x][y]->possibleMoves(x, y, chessBoard);

    for (const pair<int, int> &p : moves) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }

    return moves;
}

// Sprawdzanie ruchow dla wszystkich figur jednego koloru (do testow)
vector<vector<pair<int,int>>> checkAllMoves(PieceColor color, Board chessBoard){
    vector<vector<pair<int,int>>> moves;
    moves = chessBoard.checkMoves(color, chessBoard);

    // Print possible moves
    for (int i = 0; i < moves.size(); i++) {
        for (int j = 0; j < moves[i].size(); j++) {
            cout << moves[i][j].first << " " << moves[i][j].second << endl;
        }
    }

    return moves;
}

// Gra
void gameLoop(){
    Game game;
    game.start();
    
    
    int x1, y1, x2, y2;
    char c;
    int n;
    string input;
    while(true){
        game.printCurrentBoard();
        game.checkGameOver();
        if(game.isGameOver()){
            if(game.isCheckmate()){
                if (game.getCurrentPlayer() == PieceColor::white){
                    cout<<"Checkmate! Black won!"<<endl;
                }
                else{
                    cout<<"Checkmate! White won!"<<endl;
                }
            }else if(game.isStalemate()){
                cout<<"Stalemate! Draw!"<<endl;
            }
            break;
        }
        if (game.getCurrentPlayer() == PieceColor::white){
            cout << "Enter move for White:" << endl ;
        }else{
            cout << "Enter move for Black(Blue):" << endl ;
        }
        cout << "From: "; 
        cin>>input;
        sscanf(input.c_str(), "%c%d", &c, &n);
        switch(c){
            case 'a':
                x1 = 0;
                break;
            case 'b':
                x1 = 1;
                break;
            case 'c':
                x1 = 2;
                break;
            case 'd':
                x1 = 3;
                break;
            case 'e':
                x1 = 4;
                break;
            case 'f':
                x1 = 5;
                break;
            case 'g':
                x1 = 6;
                break;
            case 'h':
                x1 = 7;
                break;
        }
        y1 = n - 1;
        cout << "To: ";
        cin>>input;
        sscanf(input.c_str(), "%c%d", &c, &n);
        switch(c){
            case 'a':
                x2 = 0;
                break;
            case 'b':
                x2 = 1;
                break;
            case 'c':
                x2 = 2;
                break;
            case 'd':
                x2 = 3;
                break;
            case 'e':
                x2 = 4;
                break;
            case 'f':
                x2 = 5;
                break;
            case 'g':
                x2 = 6;
                break;
            case 'h':
                x2 = 7;
                break;
        }
        y2 = n - 1;
        game.makeMove(x1,y1,x2,y2);
    }
}

int main(){

    gameLoop();

    return 0;
}