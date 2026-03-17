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
    int numAllPlayers = 2;
    int numActivePlayers = 2;
    int plChoice;
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
    //Dealing to Player
    for(int i = 0; i<3; i++){
        dealToHand(&CommunityBoard,deck,&deckTop);
    }
    printHand(&CommunityBoard);
    int bTexture = BoardTexture(&CommunityBoard);
    printf("Board Texture: %d\n",bTexture);
    return 0;
}