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
    printf("Community's\n");
    printHand(&game.boardHand);
    printf("\nFlop\n");
    for(int i = 0; i < 5; i++){
        if(game.bots[i].folded == 0 && game.bots[i].active == 1){
            printf("Bot %d's",i+1);
            printHand(&game.botHands[i]);
            bot_Flop(&game, i);
        }
    }
    printf("Player's ");
    printHand(&game.playerHand);
    game.playerChoice = playerAction();
    printf("minBet %d\n",game.board.minBet );
    printf("playerChips%d\n",game.player.chips);
    PlayerActionExec(game.playerChoice, &game.player, &game.board);
    printf("playerChips%d\n",game.player.chips);
    //end of flop
    printf("\nturn\n");
    dealToHand(&game.boardHand, deck, &game.deckTop);
    game.board.communityCount = 4;
    printf("Community's\n");
    printHand(&game.boardHand);
    for(int i = 0; i < 5; i++){
        if(game.bots[i].folded == 0 && game.bots[i].active == 1){
            printf("Bot %d's",i+1);
            printHand(&game.botHands[i]);
            bot_Turn(&game, i);
        }
    }
    printf("Player's ");
    printHand(&game.playerHand);
    game.playerChoice = playerAction();
    printf("minBet %d\n",game.board.minBet );
    printf("playerChips%d\n",game.player.chips);
    PlayerActionExec(game.playerChoice, &game.player, &game.board);
    printf("playerChips%d\n",game.player.chips);
    //end of turn
    printf("\nRiver\n");
    dealToHand(&game.boardHand, deck, &game.deckTop);
    game.board.communityCount = 5;
    printf("Community's\n");
    printHand(&game.boardHand);
    for(int i = 0; i < 5; i++){
        if(game.bots[i].folded == 0 && game.bots[i].active == 1){
            printf("Bot %d's",i+1);
            printHand(&game.botHands[i]);
            printf("Calling bot_River\n");
            bot_River(&game, i);
        }
    }
    printf("Player's ");
    printHand(&game.playerHand);
    game.playerChoice = playerAction();
    printf("minBet %d\n",game.board.minBet );
    printf("playerChips%d\n",game.player.chips);
    PlayerActionExec(game.playerChoice, &game.player, &game.board);
    printf("playerChips%d\n",game.player.chips);
    //showdown!
    int playerEval, bot1Eval, bot2Eval, bot3Eval, bot4Eval, bot5Eval;
    if(game.player.active == 1 && game.player.folded == 0){playerEval = evaluateMain(&game.playerHand, &game.boardHand);}
    if(game.bots[0].active == 1 && game.bots[0].folded == 0){bot1Eval = evaluateMain(&game.botHands[0], &game.boardHand);}
    if(game.bots[1].active == 1 && game.bots[0].folded == 0){bot2Eval = evaluateMain(&game.botHands[1], &game.boardHand);}
    if(game.bots[2].active == 1 && game.bots[0].folded == 0){bot3Eval = evaluateMain(&game.botHands[2], &game.boardHand);}
    if(game.bots[3].active == 1 && game.bots[0].folded == 0){bot4Eval = evaluateMain(&game.botHands[3], &game.boardHand);}
    if(game.bots[4].active == 1 && game.bots[0].folded == 0){bot5Eval = evaluateMain(&game.botHands[4], &game.boardHand);}
    
    int bestEval = -1;
    int bestPlayerId = -1;  // 0=player, 1–5 bots

    if (game.player.active == 1 && game.player.folded == 0) {
        int playerEval = evaluateMain(&game.playerHand, &game.boardHand);
        if (playerEval > bestEval) {
            bestEval = playerEval;
            bestPlayerId = 0;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (game.bots[i].active == 1 && game.bots[i].folded == 0) {
            int botEval = evaluateMain(&game.botHands[i], &game.boardHand);
            if (botEval > bestEval) {
                bestEval = botEval;
                bestPlayerId = i + 1;  // 1–5 for bots
            }
        }
    }
    if(bestPlayerId == 0){
        printf("Player Wins!!!\n");
        printf("  Debug player chips%d\n",game.player.chips);
        payOutPot(&game.board, &game.player);
        printf("  Debug player chips%d\n",game.player.chips);
    }
    else{
        printf("Bot%d Wins!!!\n",bestPlayerId);
        printf("  Debug bot%d chips%d\n",bestPlayerId,game.bots[bestPlayerId-1].chips);
        payOutPot(&game.board, &game.bots[bestPlayerId-1]);
        printf("  Debug bot%d chips%d\n",bestPlayerId,game.bots[bestPlayerId-1].chips);
    }
    int chip_counter_max = 0;
    printf("sanity check\n");
    printf("Player Chips%d|",game.player.chips);
    chip_counter_max += game.player.chips;
    for(int i = 0; i<5; i++){
        printf("Bot%d Chips%d|",i+1, game.bots[i].chips);
        chip_counter_max += game.bots[i].chips;
    }
    printf("ChipCounter:%d\n",chip_counter_max);
    return 0;
}