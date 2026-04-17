#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "deck.h"
#include "board.h"
#include "hand.h"

typedef struct GAME{
    int round;
    int startingChips;

    Player player;
    Hand playerHand;
    Player bots[5];
    Hand botHands[5];
    Board board;
    Hand boardHand;

    int numberOfPlayers;
    int numberofActive;
    int playerChoice;
    int deckTop;

    char* statusMSG;
    int noMoreRaises;
}GAME;
void initGame(GAME *g);
void testFindWinner(int playerScore, int botScores[], int numBots, GAME *g);
void testRound(GAME *g);
void dealToActivePlayers(GAME *g);
int allBetOrFolded(GAME *game);
void autoPot(GAME *g);
void resetForNextRound(GAME *game);
#endif