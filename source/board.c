#include "C:\Users\galje\Desktop\PM_Poker_C\include\board.h"
#include <stdio.h>
void initBoard(Board *b){
    b->pot = 0;
    b->phase = 0;
}
void payOutPot(Board *b, Player *p){
    int transfer = b->pot;
    b->pot = 0;
    p->chips += transfer;
}
void placeInPot(Player *p, Board *b){
    int amount = p->bet;
    p->chips -=amount;
    b->pot += amount;
}