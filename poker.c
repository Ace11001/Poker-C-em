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
        printf("Bot %d's",i+1);
        printHand(&game.botHands[i]);
        bot_PreFlop(&game, i);
        printf("\n");
    }
    printf("Player's ");
    printHand(&game.playerHand);
    game.playerChoice = playerAction();
    printf("minBet %d\n",game.board.minBet );
    printf("playerChips%d\n",game.player.chips);
    PlayerActionExec(game.playerChoice, &game.player, &game.board);
    printf("playerChips%d\n",game.player.chips);
    //end of preflop
    dealToHand(&game.boardHand, deck, &game.deckTop);
    dealToHand(&game.boardHand, deck, &game.deckTop);
    dealToHand(&game.boardHand, deck, &game.deckTop);
    game.board.communityCount = 3;
    printf("\nFlop\n");
    for(int i = 0; i < 5; i++){
        if(game.bots[i].folded == 0 && game.bots[i].active == 1){
            printf("Bot %d's",i+1);
            printHand(&game.botHands[i]);
            bot_Flop(&game, i);
        }
    }
    return 0;
}