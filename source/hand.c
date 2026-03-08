#include "C:\Users\galje\Desktop\PM_Poker_C\include\hand.h"
#include <stdlib.h>

void initHand(Hand* hand){
    hand->count = 0;
}
void dealToHand(Hand* hand, Card* deck, int* deck_top) {
    if (*deck_top < 52 && hand->count < MAX_HAND) {
        hand->cards[hand->count] = deck[*deck_top];
        hand->count++;
        (*deck_top)++;
    }
}
void printHand(const Hand* hand){
    printf(" Hand:\n");
    if(hand->count == 0){
        printf(">empty");
    }
    for(int i = 0; i < hand->count; i++){
        printCardName(&hand->cards[i]);
    }
    printf("\n");
}