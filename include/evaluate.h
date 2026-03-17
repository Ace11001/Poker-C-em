#ifndef EVALUATE_H
#define EVALUATE_H
#include "hand.h"
#include "player.h"
#include "board.h"

#define MAX_COMBINATIONS 21
#define COMBO_SIZE 5

typedef struct {
    Card cards[COMBO_SIZE];
} Hand5;

void permutateCards(Hand* hand1, Hand* boardhand, Hand5 out[MAX_COMBINATIONS]);
void buildFreqMap(Hand5* hand, int freq[13]);
int isFlush(Hand5* hand);
int isStraight(Hand5* hand);
int evaluateHand5(Hand5* hand);
int evaluateMain(Hand* hand1, Hand* boardHand);


#endif