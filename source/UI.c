#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "evaluate.h"

#define BLUE "\033[34m" 
#define GRAY "\033[90m" 
#define YELLOW "\e[0;33m" //Chips
#define DARKBLUE "\033[0;36m"
//bot names
#define CYAN "\e[0;36m"    //0
#define MAGENTA "\e[0;35m" //1
#define GREEN "\e[0;32m"   //2
#define RED "\e[0;31m"     //3
#define BYELLOW "\e[0;93m" //4
//format
#define RESET "\033[0m"
#define ITALIC "\033[1;34;3m" 
void gotoxy(int x,int y){
    printf("%c[%d;%df",0x1B,y,x);
}
void sizeDemo(){
    system("cls");
    gotoxy(1,1);
    for(int i = 0; i<75; i++){
        printf("#");
    }
    for(int i = 0; i < 22; i++){
        gotoxy(1,2+i);
        printf("#");
        gotoxy(75, 2+i);
        printf("#");
    }
    gotoxy(1,24);
    for(int i = 0; i<74; i++){
        printf("#");
    }
    //instructions
    gotoxy(4,3);
    printf("Poker - Texas hold'em");
    gotoxy(4,4);
    printf("The # border is the size of the game user interface");
    gotoxy(4,5);
    printf("Resize the terminal window to see the # signs");
    gotoxy(4,7);
    printf("Enjoy!");
    gotoxy(4,9);
    system("pause");
}

void showdownScreen(){
    //74x25
    /**
    *       ______                 __                  __  __  __
    *      / __/ /  ___ _    _____/ /__ _    _____    / / / / / /
    *     _\ \/ _ \/ _ \ |/|/ / _  / _ \ |/|/ / _ \  /_/ /_/ /_/ 
    *    /___/_//_/\___/__,__/\_,_/\___/__,__/_//_/ (_) (_) (_)  
    *                                                            
 */
    gotoxy(5,6);
    printf(YELLOW"        ______                 __                  __  __  __");
    gotoxy(5,7);
    printf("       / __/ /  ___ _    _____/ /__ _    _____    / / / / / /");
    gotoxy(5,8);
    printf("      _\\ \\/ _ \\/ _ \\ |/|/ / _  / _ \\ |/|/ / _ \\  /_/ /_/ /_/ ");
    gotoxy(5,9);
    printf("     /___/_//_/\\___/__,__/\\_,_/\\___/__,__/_//_/ (_) (_) (_)  ");
    gotoxy(5,10);
    printf("                                                              "RESET);
    gotoxy(5,12);
    system("pause");
}

void botWindow(int xCord, int yCord, char* botName, int chips, int bet, int colIndex, int foldedStatus, int activeStatus){
if(activeStatus == 1){
    gotoxy(xCord, yCord);
    printf("+------------+");
    gotoxy(xCord, yCord+1);
    switch(colIndex){
        case 0:
            printf("|"CYAN "%8s"RESET"    |",botName);
            break;
        case 1: 
            printf("|"MAGENTA "%8s"RESET"    |",botName);
            break;
        case 2:
            printf("|"GREEN "%8s"RESET"    |",botName);
            break;
        case 3:
            printf("|"RED "%8s"RESET"    |",botName);
            break;
        case 4:
            printf("|"BYELLOW "%8s"RESET"    |",botName);
            break;
        default:
            printf("|%8s    |",botName);
            break;
    }
    gotoxy(xCord, yCord+2);
    printf("|Chips:" YELLOW "%5d" RESET " |", chips);
    gotoxy(xCord, yCord+3);
    if(foldedStatus == 0){
        printf("|Bet:" YELLOW "%7d"RESET" |" , bet);
    }else{
        printf("|"YELLOW "---FOLDED---" RESET "|" , bet);
    }
    gotoxy(xCord, yCord+4);
    printf("+------------+");
    }else{
        gotoxy(xCord, yCord);
        printf(GRAY"+------------+"RESET);
        gotoxy(xCord, yCord+1);
        printf(GRAY"|            |"RESET);
        gotoxy(xCord, yCord+2);
        printf(GRAY"|   "RED"BUSTED"GRAY"   |"RESET);
        gotoxy(xCord, yCord+3);
        printf(GRAY"|            |"RESET);
        gotoxy(xCord, yCord+4);
        printf(GRAY"+------------+"RESET);
    }
}
void cardPrint(int xCord,int yCord, int rank, int suit){
    const char* rankIcon[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K","A"};
    const char* suitIcon[4] = {"♣","♠","♥","♦"};
    if(suit >= 2){
        gotoxy(xCord,yCord);
        printf("┌─────┐");
        gotoxy(xCord,yCord+1);
        printf("|"RED"%-2s"RESET"   |",rankIcon[rank]);
        gotoxy(xCord,yCord+2);
        printf("|  "RED"%s"RESET"  |",suitIcon[suit]);
        gotoxy(xCord,yCord+3);;
        printf("|   "RED"%2s"RESET"|",rankIcon[rank]);
        gotoxy(xCord,yCord+4);
        printf("└─────┘");
    }else{
        gotoxy(xCord,yCord);
        printf("┌─────┐");
        gotoxy(xCord,yCord+1);
        printf("|"DARKBLUE"%-2s"RESET"   |",rankIcon[rank]);
        gotoxy(xCord,yCord+2);
        printf("|  "DARKBLUE"%s"RESET"  |",suitIcon[suit]);
        gotoxy(xCord,yCord+3);;
        printf("|   "DARKBLUE"%2s"RESET"|",rankIcon[rank]);
        gotoxy(xCord,yCord+4);
        printf("└─────┘");
    }
}
void drawFrame(GAME *g){
    system("chcp 65001");
    system("cls");
    //bot boxes
    int b1C = g->bots[0].chips;int b2C = g->bots[1].chips;int b3C = g->bots[2].chips;int b4C = g->bots[3].chips;int b5C = g->bots[4].chips;
    int b1B = g->bots[0].bet;int b2B = g->bots[1].bet;int b3B = g->bots[2].bet;int b4B = g->bots[3].bet;int b5B = g->bots[4].bet;
    int b1F = g->bots[0].folded;int b2F = g->bots[1].folded;int b3F = g->bots[2].folded;int b4F = g->bots[3].folded;int b5F = g->bots[4].folded;
    int b1A = g->bots[0].active;int b2A = g->bots[1].active;int b3A = g->bots[2].active;int b4A = g->bots[3].active;int b5A = g->bots[4].active;
    botWindow(1     , 1, "Bot 1", b1C, b1B, 0, b1F, b1A);
    botWindow(1 + 15, 1, "Bot 2", b2C, b2B, 1, b2F, b2A);
    botWindow(1 + 30, 1, "Bot 3", b3C, b3B, 2, b3F, b3A);
    botWindow(1 + 45, 1, "Bot 4", b4C, b4B, 3, b4F, b4A);
    botWindow(1 + 60, 1, "Bot 5", b5C, b5B, 4, b5F, b5A);
    //line segment
    gotoxy(1,6);
    for(int i = 0; i < 74; i ++){
        printf("─");
    }
    gotoxy(1,8);
    for(int i = 0; i < 74; i ++){
        printf("─");
    }
    gotoxy(1,7);
    printf("Status: "YELLOW"%s"RESET, "Hello world"); //<==Add status messages
    //Community Area
    gotoxy(1,9);
    printf("Community Cards");
    gotoxy(1,10);
    int potsize = g->board.pot;
    printf(" > Pot:   "YELLOW"%-4d"RESET, potsize);
    gotoxy(1,11);
    int minbet = g->board.minBet;
    printf(" > MinBet:"YELLOW"%-4d"RESET,minbet);
    gotoxy(65,9);
    int round = g->round;
    printf("Round: %-3d", round);
    
    int card1Rank = g->boardHand.cards[0].rank; int card1Suit = g->boardHand.cards[0].suit;
    int card2Rank = g->boardHand.cards[1].rank; int card2Suit = g->boardHand.cards[1].suit;
    int card3Rank = g->boardHand.cards[2].rank; int card3Suit = g->boardHand.cards[2].suit;
    int card4Rank = g->boardHand.cards[3].rank; int card4Suit = g->boardHand.cards[3].suit;
    int card5Rank = g->boardHand.cards[4].rank; int card5Suit = g->boardHand.cards[4].suit;
    int comCardCount = g->boardHand.count;
    if(comCardCount >= 3){
        cardPrint(18, 10, card1Rank,card1Suit);
        cardPrint(18+8, 10, card2Rank,card2Suit);
        cardPrint(18+16, 10, card3Rank,card3Suit);
    }
    if(comCardCount >= 4){
        cardPrint(18+24, 10, card4Rank,card4Suit);
    }
    if(comCardCount == 5){
        cardPrint(18+32, 10, card5Rank,card5Suit);
    }
    //Player area
    gotoxy(1,16);
    for(int i = 0; i < 74; i ++){
        if(i != 53){printf("─");}
        else{printf("┬");}
    }
    printf("\n");
    printf("Player:\n");
    int playerChips = g->player.chips;int playerBet = g->player.bet;
    printf(" > Chips: "YELLOW"%-4d"RESET"\n", playerChips);
    printf(" > Bet:   "YELLOW"%-4d"RESET"\n", playerBet);
    //adress that cards might not exist yet
    int player1Rank = g->playerHand.cards[0].rank; int player1Suit = g->playerHand.cards[0].suit; 
    int player2Rank = g->playerHand.cards[1].rank; int player2Suit = g->playerHand.cards[1].suit;
    if(g->playerHand.count >= 1){
        cardPrint(29,18, player1Rank,player1Suit);
    }
    if(g->playerHand.count == 2){
        cardPrint(39,18, player2Rank,player2Suit);//Magic Numbers, adress
    }
    gotoxy(54,17);
    printf("| Available actions:");
    gotoxy(54,18);
    printf("|  ["CYAN"0"RESET"] Call / Check");
    gotoxy(54,19);
    printf("|  ["CYAN"1"RESET"] Raise");
    gotoxy(54,20);
    printf("|  ["CYAN"2"RESET"] All-In");
    gotoxy(54,21);
    printf("|  ["CYAN"3"RESET"] Fold");
    gotoxy(54,22);
    printf("├────────────────────");
    gotoxy(54,23);
    printf("| Enter choice:");
    gotoxy(54,24);
    printf("┴────────────────────");
    //line segment
    gotoxy(1,24);
    for(int i = 0; i < 74; i ++){
        if(i != 53){printf("─");}
        else{printf("┴");}
    }
}
//  TO-DO
//  - Add input
//  - Add Linux and MAC support
//  - Add a showdown screen, show all cards of active players
//  - Add a size-reffrence screen before game begins so the player can resize the terminal window
/*
LINUX version
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> <==
...
int main(void){
    setlocale(LC_ALL, "en_US.UTF-8"); <==
    system("clear"); <==
*/