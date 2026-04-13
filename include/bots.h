#ifndef BOTS_H
#define BOTS_H
#include <string.h>
#include "deck.h"
#include "hand.h"
#include "game.h"
#include "game.h"

double botAnalysis(GAME *g, int botIndex, int phase);
int calculateRaise(GAME *g, int botIndex, int phase);
int chipAdvantage(GAME *g, int botIndex);
void decisionTree(GAME *g, int botIndex, int phase, double finalScore,double foldThreshold, double callThreshold, double raiseThreshold, double ALLIN_threshold);
//BOTLOGIC2
void botLogic2(GAME*g, int botIndex, int phase);
#endif