#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "hand.h"
#include "player.h"
#include "board.h"
#include "evaluate.h"
#include "algos.h"
#include "textColor.h"
#include "game.h"

int main(void){
    //Init
    printf(BLUE"SETUP START"RESET"\n");
    srand(time(NULL));
    createDeck(deck);
    shuffleDeck(deck);
    GAME gameSpace;
    initGame(&gameSpace);
    printf(BLUE"SETUP END"RESET"\n\n");
    //Init end
    dealToHand(&(gameSpace.playerHand), deck, &(gameSpace.deckTop));
    printHand(&(gameSpace.playerHand));
    return 0;
}