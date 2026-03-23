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
    Player bot1, bot2, bot3, bot4, bot5;
    Hand bot1Hand, bot2Hand, bot3Hand, bot4Hand, bot5Hand;
    Board board;
    Hand boardHand[5];

    int numberOfPlayers;
    int numberofActive;
    int playerChoice;
    int deckTop;
}GAME;
void initGame(GAME *g);
#endif