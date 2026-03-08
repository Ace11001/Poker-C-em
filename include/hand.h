#ifndef HAND_H
#define HAND_H
#include "deck.h"

#define MAX_HAND 5

typedef struct {
    Card cards[MAX_HAND];
    int count;
} Hand;

void initHand(Hand* hand);
void dealToHand(Hand* hand, Card* deck, int* deckTop);
void printHand(const Hand* hand);

#endif