#include <iostream>
#include <cstdint>
#include <bitset>
#include <utility>
#include <string>
#include <cmath>
 
using namespace std;
 
// Square index = rank * 8 + file, with a1 = 0, h1 = 7, a8 = 56, h8 = 63
// so the a-file is the lowest bit of each byte and the h-file the highest.
constexpr uint64_t FILE_A  = 0x0101010101010101ULL;
constexpr uint64_t FILE_B  = FILE_A << 1;
constexpr uint64_t FILE_G  = FILE_A << 6;
constexpr uint64_t FILE_H  = FILE_A << 7;            // 0x8080808080808080
constexpr uint64_t FILE_AB = FILE_A | FILE_B;        // 0x0303030303030303
constexpr uint64_t FILE_GH = FILE_G | FILE_H;        // 0xC0C0C0C0C0C0C0C0
 
constexpr uint64_t NOT_FILE_A  = ~FILE_A;            // 0xFEFEFEFEFEFEFEFE
constexpr uint64_t NOT_FILE_H  = ~FILE_H;            // 0x7F7F7F7F7F7F7F7F
constexpr uint64_t NOT_FILE_AB = ~FILE_AB;           // 0xFCFCFCFCFCFCFCFC
constexpr uint64_t NOT_FILE_GH = ~FILE_GH;           // 0x3F3F3F3F3F3F3F3F
 
// Rule of thumb: moving east (toward h) -> mask with NOT_FILE_H / NOT_FILE_GH
//                moving west (toward a) -> mask with NOT_FILE_A / NOT_FILE_AB
 
 
void displayBitboard(uint64_t bb) {
    for (int r = 7; r >= 0; r--) { // On commence par la ligne du haut (8)
        for (int c = 0; c < 8; c++) {
            int index = r * 8 + c;
            
            // On vérifie si le bit à cet index est à 1
            if ((bb >> index) & 1) {
                cout << "1 ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}
 
short convertCoordToInt(pair<short, short> pieceCoord) {
    return pieceCoord.second * 8 + pieceCoord.first;
}
 
pair<short, short> convertIntToCoord(short index) {
    return { (short)(index % 8), (short)(index / 8) };
}
 
pair<short, short> getCoord (string chessCoord){
    return {(chessCoord[0] - 'a'), (chessCoord[1] - '0') - 1};
}
 
uint64_t getPiecePosBitboard (pair<short, short> position) {
    short piecePos = position.second*8 + position.first;
 
    uint64_t pieceBitboard = 1ULL;
    pieceBitboard = pieceBitboard << piecePos;
 
    return pieceBitboard;
}
 
uint64_t getRookBitboard(pair<short, short> position) {
    short columnMagicNumber = 1ULL << position.first;
 
    uint64_t rookBitboard = 0x0000000000000000;
    uint64_t column = columnMagicNumber * 0x0101010101010101;
    uint64_t line = 0xFFULL << (position.second * 8);
    uint64_t rookPosBitboard = getPiecePosBitboard(position);
 
    //adding columns and lines attacks
    rookBitboard = ((rookBitboard | column) | line) ^ rookPosBitboard;
 
    return rookBitboard;
}
 
uint64_t getBishopBitboard (pair<short, short> position) {
    uint64_t bishopPosBitboard = getPiecePosBitboard(position);
    uint64_t bishopBitboard = 0x0000000000000000;
    uint64_t mask = bishopPosBitboard;
    pair<short, short> tempPos = position;
 
    while (tempPos.first > 0 && tempPos.second > 0) {
        tempPos.first--;
        tempPos.second--;
 
        mask = mask >> 9;
        bishopBitboard = bishopBitboard | mask;
    }
 
    tempPos = position;
    mask = bishopPosBitboard;
    while (tempPos.first > 0 && tempPos.second < 7) {
        tempPos.first--;
        tempPos.second++;
 
        mask = mask << 7;
        bishopBitboard = bishopBitboard | mask;
    }
 
    tempPos = position;
    mask = bishopPosBitboard;
    while (tempPos.first < 7 && tempPos.second > 0) {
        tempPos.first++;
        tempPos.second--;
 
        mask = mask >> 7;
        bishopBitboard = bishopBitboard | mask;
    }
 
    tempPos = position;
    mask = bishopPosBitboard;
    while (tempPos.first < 7 && tempPos.second < 7) {
        tempPos.first++;
        tempPos.second++;
 
        mask = mask << 9;
        bishopBitboard = bishopBitboard | (mask);
    }
 
    return bishopBitboard;
}
 
uint64_t getQueenBitboard(pair<short, short> position) {
    return getRookBitboard(position) | getBishopBitboard(position);
}
 
uint64_t getKingBitboard(pair<short, short> position) {
    uint64_t kingPosBitboard = getPiecePosBitboard(position);
    uint64_t kingbitboard = 0x0000000000000000;
    uint64_t mask;
 
    kingbitboard = kingbitboard | (kingPosBitboard << 8);
    kingbitboard = kingbitboard | (kingPosBitboard >> 8);
 
    // east: E, NE, SE
    mask = kingPosBitboard & NOT_FILE_H;
    kingbitboard = kingbitboard | (mask << 1);
    kingbitboard = kingbitboard | (mask << 9);
    kingbitboard = kingbitboard | (mask >> 7);
 
    // west: W, SW, NW
    mask = kingPosBitboard & NOT_FILE_A;
    kingbitboard = kingbitboard | (mask >> 1);
    kingbitboard = kingbitboard | (mask >> 9);
    kingbitboard = kingbitboard | (mask << 7);
 
    return kingbitboard;
}
 
uint64_t getKnightbBitboard(pair<short, short> position) {
    uint64_t knightPosBitboard = getPiecePosBitboard(position);
    uint64_t knightbitboard = 0x0000000000000000;
    uint64_t mask;
 
    // one file east
    mask = knightPosBitboard & NOT_FILE_H;
    knightbitboard = knightbitboard | (mask << 17);
    knightbitboard = knightbitboard | (mask >> 15);
 
    // one file west
    mask = knightPosBitboard & NOT_FILE_A;
    knightbitboard = knightbitboard | (mask >> 17);
    knightbitboard = knightbitboard | (mask << 15);
 
    // two files east
    mask = knightPosBitboard & NOT_FILE_GH;
    knightbitboard = knightbitboard | (mask << 10);
    knightbitboard = knightbitboard | (mask >> 6);
 
    // two files west
    mask = knightPosBitboard & NOT_FILE_AB;
    knightbitboard = knightbitboard | (mask >> 10);
    knightbitboard = knightbitboard | (mask << 6);
 
    return knightbitboard;
}
 
uint64_t getWhitePawnBitboard(pair<short, short> position) {
    uint64_t pawnPosBitboard = getPiecePosBitboard(position);
    uint64_t pawnbitboard = 0x0000000000000000;
    uint64_t mask;
 
    // capture north-east
    mask = pawnPosBitboard & NOT_FILE_H;
    pawnbitboard = pawnbitboard | (mask << 9);
 
    // capture north-west
    mask = pawnPosBitboard & NOT_FILE_A;
    pawnbitboard = pawnbitboard | (mask << 7);
 
    return pawnbitboard;
}
 
uint64_t getBlackPawnBitboard(pair<short, short> position) {
    uint64_t pawnPosBitboard = getPiecePosBitboard(position);
    uint64_t pawnbitboard = 0x0000000000000000;
    uint64_t mask;
 
    // capture south-east
    mask = pawnPosBitboard & NOT_FILE_H;
    pawnbitboard = pawnbitboard | (mask >> 7);
 
    // capture south-west
    mask = pawnPosBitboard & NOT_FILE_A;
    pawnbitboard = pawnbitboard | (mask >> 9);
 
    return pawnbitboard;
}
