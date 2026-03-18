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

int main(void){
    //Init
        printf(BLUE"SETUP START"RESET"\n");
    srand(time(NULL));
    createDeck(deck);
    shuffleDeck(deck);
    
    Hand playerHand = {0};
    Hand player2Hand = {0};
    int numAllPlayers = 2;
    int numActivePlayers = 2;
    int pl1Choice, pl2Choice; 
    
    Hand CommunityBoard = {0};
    
    int startingChips = 1000;
    Player player;
    Player player2;
    Board board;
    
    initPlayer(&player, startingChips, "Player");
    initPlayer(&player2,startingChips, "Bot");
    initBoard(&board);
    
    int deckTop = 0; 
    int roundCount = 1;
        printf(BLUE"SETUP END"RESET"\n\n");
    //Init end
    //Round Demo - Crude Implementation, only 2 players, no bots
    ColPrintfPlus("Round %d\n",roundCount,1);
    printf(" >Starting Bet - %d\n",(&board)->minBet);
    playerInitBet(&player, &board);
    playerInitBet(&player2, &board);
    placeInPot(&player,&board);
    placeInPot(&player2,&board);
        //prereqs done,card dealing
    dealToHand(&playerHand, deck, &deckTop);
    dealToHand(&player2Hand, deck, &deckTop);
    dealToHand(&playerHand, deck, &deckTop);
    dealToHand(&player2Hand, deck, &deckTop);
        //cards dealt,betting
    pl1Choice = playerAction();
    PlayerActionExec(pl1Choice, &player, &board);
    pl2Choice = playerAction();
    PlayerActionExec(pl2Choice, &player2, &board);
        //player Actions done, community dealing
    dealToHand(&CommunityBoard,deck,&deckTop);
    dealToHand(&CommunityBoard,deck,&deckTop);
    dealToHand(&CommunityBoard,deck,&deckTop);
    printHand(&CommunityBoard);
        //second action
    pl1Choice = playerAction();
    PlayerActionExec(pl1Choice, &player, &board);
    pl2Choice = playerAction();
    PlayerActionExec(pl2Choice, &player2, &board);
        //next card
    dealToHand(&CommunityBoard, deck, &deckTop);
    printHand(&CommunityBoard);
        //third action
    pl1Choice = playerAction();
    PlayerActionExec(pl1Choice, &player, &board);
    pl2Choice = playerAction();
    PlayerActionExec(pl2Choice, &player2, &board);
        //final draw
    dealToHand(&CommunityBoard, deck, &deckTop);
    printHand(&CommunityBoard);
        //final action
    pl1Choice = playerAction();
    PlayerActionExec(pl1Choice, &player, &board);
    pl2Choice = playerAction();
    PlayerActionExec(pl2Choice, &player2, &board);
        //card reveal
    printf("\n\n\n\n\n");
    printHand(&CommunityBoard);
    printHand(&playerHand);
    printHand(&player2Hand);
    
    //eval
    int evaluatedPlayer = evaluateMain(&playerHand,&CommunityBoard);
    int evaluatedBot1 = evaluateMain(&player2Hand, &CommunityBoard);

    char DEBUGplayerScore[64];
    snprintf(DEBUGplayerScore, sizeof(DEBUGplayerScore), "Player Hand result: %d\n", evaluatedPlayer);
    char DEBUGbot1Score[64];
    snprintf(DEBUGbot1Score, sizeof(DEBUGbot1Score), "Bot 1 Hand result: %d\n", evaluatedBot1);
    ColPrintf(DEBUGplayerScore,0);
    ColPrintf(DEBUGbot1Score, 0);
    
    //to be changed
    if(evaluatedPlayer > evaluatedBot1){
        printf("Player wins\n");
    }
    else if(evaluatedPlayer < evaluatedBot1){
        printf("Bot 1 wins\n");
    }
    else if(evaluatedPlayer == evaluatedBot1){
        printf("Draw!\n");
        //add way to divide pot evenly between winning players
    }
    
    return 0;
}