#include "C:\Users\galje\Desktop\PM_Poker_C\include\board.h"
#include <stdio.h>
#include "board.h"
#include "player.h"

void initBoard(Board *b){
    b->pot = 0;
    b->minBet = 5;
    b->phase = 0;
    b->AllInStatus = 0;
    b->AllInSize = 0;
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
void bustDetection(Player *p){
    //should Only check after end of round evaluation to discard the player/bot
    if(p->chips==0){
        //player Has no Chips
        p->active = 0;
    }
}
//showdown
//inputs an array of structs(Hands)
int getShowdown(int scores[],int playerCount){//needs to be passed an array of scores, and an integer of number of hands
    int bestIndex = 0;
    for(int i = 1; i<playerCount;i++){
        if(scores[i] >scores[bestIndex]){
            bestIndex = i;
        }
    }
    return bestIndex;//doesn't handle ties!
}