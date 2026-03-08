#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "include\hand.h"
#include "include\player.h"
#include "include\board.h"
#include "include\evaluate.h"
#include "include\algos.h"
//colors
#define BLUE "\033[34m"
#define RED "\e[0;31m"
#define RESET "\033[0m"
//usage:
//printf(BLUE "text" RESET "\n")


int main(void){
system("chcp 65001");
    createDeck(deck);
    shuffleDeck(deck);
    Hand Hand_Player1;
    Player Player1;
    Hand Hand_Player2;
    Player Player2;
    int startingChips = 1000;
    initPlayer(&Player1, startingChips);initPlayer(&Player2, startingChips);
    initHand(&Hand_Player1);initHand(&Hand_Player2);
    int deckTop=0;
    dealToHand(&Hand_Player1,deck,&deckTop);
    dealToHand(&Hand_Player1,deck,&deckTop);
    printCardName(&Hand_Player1.cards[0]);
    printCardName(&Hand_Player1.cards[1]);
    printf("\n");
    int a = ChensFormula(&Hand_Player1);//higher score is more favorable
    int b = SklanskyMalmuth(&Hand_Player1);//lower score is more favorable, less risky
    printf("ChenFormula result:%d\n",a);
    printf("Sklansky&Malmuth Table: %d\n", b);
    double kvocient = (1.0+(double)a)/(double)b;
    printf("Arbitrary kvocient for comparing hands %.4lf\n",kvocient);
    printf("\nprecomputing all 2hand combination\n");
    allCombosKvocient();
return 0;
}