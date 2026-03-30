#ifndef ALGOS_H
#define ALGOS_H
#include <math.h>
#include "deck.h"
#include "hand.h"
#include "game.h"

int ChensFormula(Hand* h);
int SklanskyMalmuth(Hand *h);
int BoardTexture(Hand* board, int communityCount);
int gapScoreLen(Hand* board, int numOfCards);
void bot_PreFlop(GAME *g, int botIndex);
void bot_Flop(GAME *g, int botIndex);
#endif