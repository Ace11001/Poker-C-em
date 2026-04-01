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
#include "game.h"
#include "UI.h"

int main(void){
    //Init
    printf(BLUE"SETUP START"RESET"\n");
    srand(time(NULL));
    createDeck(deck);
    shuffleDeck(deck);
    resetDeck(deck);
    GAME game;
    initGame(&game);
    printf(BLUE"SETUP END"RESET"\n\n");
    sizeDemo();
    showdownScreen();
    initPlayer(&game.player, game.startingChips, "Player");
    dealToHand(&game.boardHand, deck, &game.deckTop);
    dealToHand(&game.boardHand, deck, &game.deckTop);
    dealToHand(&game.boardHand, deck, &game.deckTop);
    dealToHand(&game.boardHand, deck, &game.deckTop);
    dealToHand(&game.boardHand, deck, &game.deckTop);

    dealToHand(&game.playerHand, deck, &game.deckTop);
    dealToHand(&game.playerHand, deck, &game.deckTop);

    drawFrame(&game);
    
    return 0;
}