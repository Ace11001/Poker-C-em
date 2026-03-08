#ifndef DECK_H
#define DECK_H
#include <stdio.h>

typedef struct{
    int rank;//0-12
    int suit;//0-3
} Card;

extern Card deck[52];

void createDeck(Card* deck);
void shuffleDeck(Card* deck);
void printCardName(const Card* deck);
void DEBUG_printDeck(const Card* deck);

extern const char* rank_names[13];
extern const char* suit_names[4];

#endif 