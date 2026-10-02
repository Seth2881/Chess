#include <iostream>
#include <bitset>
#include <utility>
#include <string>
#include <cmath>
#include "bitboards.cpp"

using namespace std;

short pawn = 0b001;
short knight = 0b010;
short bishop = 0b011;
short rook = 0b100;
short queen = 0b101;
short king = 0b110;

short white = 0b01000;
short black = 0b10000;

// piece type OR color to get full piece Ex : white pawn = 0b001 | 0b01000 = 0b01001

extern short pawn;
extern short knight;
extern short bishop;
extern short rook;
extern short queen;
extern short king;

extern short white;
extern short black;

class Piece {
protected :
    short piece;
    short indexPiece;
    pair<short, short> piecePos;
    uint64_t attacks = 0x0000000000000000;
public :
    Piece (short piece, short color, short pieceIndex) {
        this->piece = piece | color; //take the first three bits to get the piece type
        piecePos = convertIntToCoord(pieceIndex);
        indexPiece = pieceIndex;
    }

    void SetPiecePos (pair<short, short> coordinates) {
        piecePos = coordinates;
        Updatebitboard();
    }

    virtual void Updatebitboard() = 0;

    pair<short, short> GetPiecePos () {
        return piecePos;
    }

    uint64_t GetBitboard () {
        return attacks;
    }
};



class King: public Piece {
private :
    bool isCastlePossible;
    bool isLongCastlePossible;
public :
    void Updatebitboard() override {
        attacks = getKingBitboard(piecePos);
    }

    King(short color, short pieceIndex, bool canCastle, bool canLongCastle): Piece (king, color, pieceIndex) {
        isCastlePossible = canCastle;
        isLongCastlePossible = canLongCastle;
        Updatebitboard();
    }

    void SetIsCastlePossible (bool canCastle) {
        isCastlePossible = canCastle;
    }
};



class Queen: public Piece {
public :
    void Updatebitboard() override {
        attacks = getQueenBitboard(piecePos);
    }

    Queen(short color, short pieceIndex): Piece (queen, color, pieceIndex) {
        Updatebitboard();
    }
};



class Rook: public Piece {
public :
    void Updatebitboard() override {
        attacks = getRookBitboard(piecePos);
    }

    Rook(short color, short pieceIndex): Piece (rook, color, pieceIndex) {
        Updatebitboard();
    }
};



class Bishop: public Piece {
public :
    void Updatebitboard() override {
        attacks = getBishopBitboard(piecePos);
    }

    Bishop(short color, short pieceIndex): Piece (bishop, color, pieceIndex) {
        Updatebitboard();
    }
};



class Knight: public Piece {
public :
    void Updatebitboard() override {
        attacks = getKnightbBitboard(piecePos);
    }

    Knight(short color, short pieceIndex): Piece (knight, color, pieceIndex) {
        Updatebitboard();
    }
};



class Pawn: public Piece {
private :
    bool canPromote;
    short enPassant;
    bool isFirstMove;
public :
    void Updatebitboard() override {
        if ((piece | 0b00000) > 16){
            attacks = getBlackPawnBitboard(piecePos);
        } else {
            attacks = getWhitePawnBitboard(piecePos);
        }
    }

    Pawn(short color, short pieceIndex, bool isPromotion, short enPassant = -1): Piece (knight, color, pieceIndex) {
        canPromote = isPromotion;
        this->enPassant = enPassant;

        if (!isPromotion){
            Updatebitboard();
        }
    }

    void SetIsFirstMove() {
        if ((piece | 0b00000) > 16) {
            if (indexPiece > 47 && indexPiece < 56) {
                isFirstMove = true;
            } else {
                isFirstMove = false;
            }
        } else {
            if (indexPiece > 7 && indexPiece < 15) {
                isFirstMove = true;
            } else {
                isFirstMove = false;
            }
        }
    }

    void SetEnPassant(string enPassant) {
        this->enPassant = convertCoordToInt(getCoord(enPassant));
    }

    void SetCanPromote(bool isPromotion) {
        canPromote = isPromotion;
    }

    bool GetEnPassant() {
        return enPassant;
    }

    bool GetCanPromote() {
        return canPromote;
    }
};