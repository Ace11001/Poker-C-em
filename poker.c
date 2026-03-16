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
    printf(" Community:\n");
    printHand(&CommunityBoard);
    printf(" Player:\n");
    printHand(&playerHand);
    printf(" Bot1:\n");
    printHand(&Bot1Hand);
    printf("\n");

    int evaluatedPlayer = evaluateMain(&playerHand,&CommunityBoard);
    int evaluatedBot1 = evaluateMain(&Bot1Hand, &CommunityBoard);

    char DEBUGplayerScore[64];
    snprintf(DEBUGplayerScore, sizeof(DEBUGplayerScore), "Player Hand result: %d\n", evaluatedPlayer);
    char DEBUGbot1Score[64];
    snprintf(DEBUGbot1Score, sizeof(DEBUGbot1Score), "Bot 1 Hand result: %d\n", evaluatedBot1);
    ColorfulPrintf(DEBUGplayerScore,0);
    ColorfulPrintf(DEBUGbot1Score, 0);
    
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