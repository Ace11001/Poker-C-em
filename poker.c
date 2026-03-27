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
    resetDeck(deck);
    GAME game;
    initGame(&game);
    printf(BLUE"SETUP END"RESET"\n\n");
    //Init end//testRound(&gameSpace);
    dealToActivePlayers(&game);
    for(int i = 0; i < 5; i++){
        printHand(&game.botHands[i]);
        bot_PreFlop(&game, i);
        printf("\n");
    }
    printf("Player's ");
    printHand(&game.playerHand);
    return 0;
}