#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "board.h"
#include "evaluate.h"
//colors
#define BLUE "\033[34m"
#define RED "\e[0;31m"
#define RESET "\033[0m"
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
    printf(BLUE"SETUP END"RESET"\n\n");
    //
    
    printf(RED">>Dealing cards"RESET"\n");
    dealToHand(&playerHand,deck,&deckTop);dealToHand(&playerHand,deck,&deckTop);
    printf("player");
    printHand(&playerHand);
    _sleep(1500);
    dealToHand(&Bot1Hand,deck,&deckTop);dealToHand(&Bot1Hand,deck,&deckTop);
    printf("Bot1");
    printHand(&Bot1Hand);
    _sleep(1500);
    for(int r=0;r<5;r++)dealToHand(&CommunityBoard,deck,&deckTop);
    printf("Community");
    printHand(&CommunityBoard);
    printf(RED">>Finished dealing, evaluation next"RESET"\n");
    _sleep(1000);//limit speed to not make the CLI too jumpy/fast
    
    int testPlayerHand = evaluateMain(&playerHand, &CommunityBoard);
    int testBot1Hand   = evaluateMain(&Bot1Hand,   &CommunityBoard); 
    //results
    printf("Test results:\n    player:%d\n    Bot1:%d",testPlayerHand,testBot1Hand);
    printf("\nTest over\n");
    return 0;
}