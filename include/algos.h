#ifndef ALGOS_H
#define ALGOS_H
#include <math.h>
#include "deck.h"
#include "hand.h"

int ChensFormula(Hand* h);
int SklanskyMalmuth(Hand *h);
int BoardTexture(Hand* board);
int gapScoreLen(Hand* board, int numOfCards);
#endif