#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "hand.h"
#include "player.h"
#include "board.h"
#include "include\evaluate.h"
//#include "include\algos.h"
//colors
#include "textColor.h"
//usage:
//printf(BLUE "text" RESET "\n")


int main(void){
    //Init
    printf(BLUE"SETUP START"RESET"\n");
    srand(time(NULL));
    createDeck(deck);
    shuffleDeck(deck);
    Hand playerHand = {0};
    Hand Bot1Hand = {0};
    Hand CommunityBoard = {0};
    int startingChips = 1000;
    Player player;
    Player Bot1;
    Board board;
    initPlayer(&player, startingChips);
    initPlayer(&Bot1,startingChips);
    initBoard(&board);
    int numAllPlayer = 2;
    int numActivePlayer = 2;
    int deckTop = 0; 
    int plChoice;
    printf(BLUE"SETUP END"RESET"\n\n");
    //Dealing to Player
    dealToHand(&playerHand,deck,&deckTop);
    dealToHand(&playerHand,deck,&deckTop);
    //Dealing to Bot1
    dealToHand(&Bot1Hand,deck,&deckTop);
    dealToHand(&Bot1Hand,deck,&deckTop);
    //Dealing to board cards
    dealToHand(&CommunityBoard, deck, &deckTop);
    dealToHand(&CommunityBoard, deck, &deckTop);
    dealToHand(&CommunityBoard, deck, &deckTop);
    dealToHand(&CommunityBoard, deck, &deckTop);
    dealToHand(&CommunityBoard, deck, &deckTop);
    //printing hands
    printf(" Community");
    printHand(&CommunityBoard);
    printf(" Player");
    printHand(&playerHand);
    printf(" Bot1");
    printHand(&Bot1Hand);
    printf("\n");

    int evaluatedPlayer = evaluateMain(&playerHand,&CommunityBoard);
    int evaluatedBot1 = evaluateMain(&Bot1Hand, &CommunityBoard);
    PlayerSetScore(&player, evaluatedPlayer);
    PlayerSetScore(&Bot1, evaluatedBot1);
    char DEBUGplayerScore[64];
    snprintf(DEBUGplayerScore, sizeof(DEBUGplayerScore), "Player Hand result: %d\n", evaluatedPlayer);
    ColPrintf(DEBUGplayerScore,0);
    
    ColPrintfPlus("Bot 1 Hand: %d\n",evaluatedBot1,0);
    
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