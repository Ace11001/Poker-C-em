#ifndef BOARD_H
#define BOARD_H
#include "player.h"

typedef struct{
    int pot;
    int phase;//0-preflop|1-flop|2-turn|3-river
}Board;
void initBoard(Board *b);
void payOutPot(Board *b, Player *p);
void placeInPot(Player *p, Board *b);

#endif