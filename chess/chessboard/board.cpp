#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <ranges>
#include <memory>
#include <algorithm>
#include "raylib.h"
#include "../pieces/pieces.cpp"
using namespace std;

class Board {
private :
    vector<unique_ptr<Piece>> pieceOnBoard;

    string startingposition;

    string board;
    char whoStart;
    string castling;
    string enPassant;

    short truns;
    short midTurns;

public :
    Board(string fenPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq – 0 1") {
        startingposition = fenPosition;

        auto split_view = startingposition | std::views::split(' ');
        auto parts = split_view | std::ranges::to<vector<string>>();

        board = parts[0];
        whoStart = parts[1][0];
        castling = parts[2];
        enPassant = parts[3];
        midTurns = static_cast<short>(stoi(parts[4])); 
        truns = static_cast<short>(stoi(parts[5]));
    }

    void SetUpGame() {
        short counter = 63;
        bool castle;
        bool longCastle;

        for (int i = 0 ; i < board.size() ; i++) {
            if ((board[i] - '0') < 9) {
                counter -= (board[i] - '0'); 
            } else if (board[i] != '/' && !((board[i] - '0') < 9)){
                if (isupper(board[i]) == 0) {
                    castle = castling.contains('K');
                    longCastle = castling.contains('Q');

                    switch (tolower(board[i])) {
                        // case 'k' : pieceOnBoard.push_back(make_unique<King>(white, counter, castle, longCastle)); break;
                        // case 'q' : pieceOnBoard.push_back(make_unique<Queen>(white, counter)); break;
                        // case 'r' : pieceOnBoard.push_back(make_unique<Rook>(white, counter)); break;
                        // case 'b' : pieceOnBoard.push_back(make_unique<Bishop>(white, counter)); break;
                        // case 'n' : pieceOnBoard.push_back(make_unique<Knight>(white, counter)); break;
                        // case 'p' : pieceOnBoard.push_back(make_unique<Pawn>(white, counter, false)); break;
                    }
                } else {
                    castle = castling.contains('k');
                    longCastle = castling.contains('q');

                    switch (tolower(board[i])) {
                        // case 'k' : pieceOnBoard.push_back(make_unique<King>(black, counter, castle, longCastle)); break;
                        // case 'q' : pieceOnBoard.push_back(make_unique<Queen>(black, counter)); break;
                        // case 'r' : pieceOnBoard.push_back(make_unique<Rook>(black, counter)); break;
                        // case 'b' : pieceOnBoard.push_back(make_unique<Bishop>(black, counter)); break;
                        // case 'n' : pieceOnBoard.push_back(make_unique<Knight>(black, counter)); break;
                        // case 'p' : pieceOnBoard.push_back(make_unique<Pawn>(black, counter, false)); break;
                    }
                }
                counter--;

                if (counter < 0) {
                    cerr << "Error: Board overflow :" << counter << endl;
                }
            }
            
        }
    }

};