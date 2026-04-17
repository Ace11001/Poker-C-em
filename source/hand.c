#include "hand.h"
#include "player.h"
#include <stdlib.h>

void initHand(Hand* hand, Player* player){
    hand->count = 0;
    hand->name = player->name;
}
void dealToHand(Hand* hand, Card* deck, int* deck_top) {
    hand->cards[hand->count] = deck[*deck_top];
    (hand->count)++;
    (*deck_top)++;
}

void printHand(Hand* hand){
    int cardCount = hand->count;
    printf("%s's Cards:\n",hand->name);
    if(cardCount == 0){
        printf(">empty");
    }
    for(int i = 0; i < cardCount; i++){
        printCardName(&hand->cards[i]);
    }
    printf("\n");
}

void clearHand(Hand* hand){
    for(int i = 0; i < hand->count; i++){
        hand->cards[i].rank = -1;
        hand->cards[i].suit = -1;
    }
    hand->count = 0;
}