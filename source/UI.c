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
void safeguard(){
    gotoxy(1,23);
    for(int i = 0; i < 74; i ++){
        printf(" ");
    }
    gotoxy(1,23);
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

void testClearScreen(){
    printf("\033[2J\033[1;1H");
    fflush(stdout);
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
    system("cls");
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
    if(rank == 99 && suit == 99){
        gotoxy(xCord,yCord);
        printf(GRAY"┌─────┐");
        gotoxy(xCord,yCord+1);
        printf("|     |");
        gotoxy(xCord,yCord+2);
        printf("|     |");
        gotoxy(xCord,yCord+3);;
        printf("|     |");
        gotoxy(xCord,yCord+4);
        printf("└─────┘"RESET);
        return;
    }
    if(suit >= 2){
        gotoxy(xCord,yCord);
        printf("┌─────┐");
        gotoxy(xCord,yCord+1);
        printf("|"RED"%-2s  %s"RESET"|",rankIcon[rank],suitIcon[suit]);
        gotoxy(xCord,yCord+2);
        printf("|  "RED"%s"RESET"  |",suitIcon[suit]);
        gotoxy(xCord,yCord+3);;
        printf("|"RED"%s  %2s"RESET"|",suitIcon[suit],rankIcon[rank]);
        gotoxy(xCord,yCord+4);
        printf("└─────┘");
    }else{
        gotoxy(xCord,yCord);
        printf("┌─────┐");
        gotoxy(xCord,yCord+1);
        printf("|"DARKBLUE"%-2s  %s"RESET"|",rankIcon[rank],suitIcon[suit]);
        gotoxy(xCord,yCord+2);
        printf("|  "DARKBLUE"%s"RESET"  |",suitIcon[suit]);
        gotoxy(xCord,yCord+3);;
        printf("|"DARKBLUE"%s  %2s"RESET"|",suitIcon[suit],rankIcon[rank]);
        gotoxy(xCord,yCord+4);
        printf("└─────┘");
    }
}
int inputpl(GAME *g){
    gotoxy(55,21);
    printf(" Enter choice:");
    gotoxy(69,21);
    int x;//user choice
    scanf("%d",&x);
    if(x == 0 || x == 1 || x == 2 || x == 3){
        g->playerChoice = x;
    }else{
        gotoxy(55,23);
        printf("invalid input      ");
        _sleep(750);
        inputpl(g);
    }
    return x;
}
void communityWindow(GAME *g){
    gotoxy(1,7);
    printf("Community Cards");
    gotoxy(1,8);
    int potsize = g->board.pot;
    printf(" > Pot:   "YELLOW"%-4d"RESET, potsize);
    gotoxy(1,9);
    int minbet = g->board.minBet;
    printf(" > MinBet:"YELLOW"%-4d"RESET,minbet);
    gotoxy(65,7);
    int round = g->round;
    printf("Round: %-3d", round);
    
    int card1Rank = g->boardHand.cards[0].rank; int card1Suit = g->boardHand.cards[0].suit;
    int card2Rank = g->boardHand.cards[1].rank; int card2Suit = g->boardHand.cards[1].suit;
    int card3Rank = g->boardHand.cards[2].rank; int card3Suit = g->boardHand.cards[2].suit;
    int card4Rank = g->boardHand.cards[3].rank; int card4Suit = g->boardHand.cards[3].suit;
    int card5Rank = g->boardHand.cards[4].rank; int card5Suit = g->boardHand.cards[4].suit;
    int comCardCount = g->boardHand.count;
    if(comCardCount >= 1){cardPrint(18, 8, card1Rank,card1Suit);}
    if(comCardCount >= 2){cardPrint(18+8, 8, card2Rank,card2Suit);}
    if(comCardCount >= 3){cardPrint(18+16, 8, card3Rank,card3Suit);}
    if(comCardCount >= 4){cardPrint(18+24, 8, card4Rank,card4Suit);}
    if(comCardCount == 5){cardPrint(18+32, 8, card5Rank,card5Suit);}
    safeguard();
}
void playerWindow(GAME *g){
    gotoxy(1,14);
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
        cardPrint(29,16, player1Rank,player1Suit);
    }
    if(g->playerHand.count == 2){
        cardPrint(39,16, player2Rank,player2Suit);
    }
    gotoxy(54,15);
    printf("| Available actions:");
    gotoxy(54,16);
    printf("|  ["CYAN"0"RESET"] Call / Check");
    gotoxy(54,17);
    printf("|  ["CYAN"1"RESET"] Raise");
    gotoxy(54,18);
    printf("|  ["CYAN"2"RESET"] All-In");
    gotoxy(54,19);
    printf("|  ["CYAN"3"RESET"] Fold");
    gotoxy(54,20);
    printf("├────────────────────");
    gotoxy(54,21);
    printf("| Enter choice:  ");
    gotoxy(54,22);
    printf("┴────────────────────");
    safeguard();
}

void drawFrame(GAME *g){
    system("chcp 65001");
    system("cls");
    testClearScreen();
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
    communityWindow(g);
    //Player area
    playerWindow(g);
    //line segment
    gotoxy(1,22);
    for(int i = 0; i < 74; i ++){
        if(i != 53){printf("─");}
        else{printf("┴");}
    }
    safeguard();
}

void updateBotWindow(GAME *g, int botIndex){
    int foldedStatus = g->bots[botIndex].folded;
    int activeStatus = g->bots[botIndex].active;
    int chips = g->bots[botIndex].chips;
    int bet = g->bots[botIndex].bet;
    switch(botIndex){
        case 0:
            botWindow(1,1,"Bot 1",chips,bet,0,foldedStatus,activeStatus);
            break;
        case 1:
            botWindow(16,1,"Bot 2",chips,bet,1,foldedStatus,activeStatus);
            break;
        case 2:
            botWindow(31,1,"Bot 3",chips,bet,2,foldedStatus,activeStatus);
            break;
        case 3:
            botWindow(46,1,"Bot 4",chips,bet,3,foldedStatus,activeStatus);
            break;
        case 4:
            botWindow(61,1,"Bot 5",chips,bet,4,foldedStatus,activeStatus);
            break;
        default:break;
    }
    gotoxy(1,23);
}

void showdownScreenResult(GAME *game, int indexWinner, int comboIndex) {
    system("cls");
    int count = 0;
    for(int i = 0; i < 5; i++) {
        int botCol = 1 + count * 12;
        int botRow = 9;
        if(game->bots[i].active == 0) {
            gotoxy(botCol, botRow);
            printf(RED "Bot%d" RESET, i+1);
            int botRow2 = botRow+1;
            for(int i = 0; i < 3; i++){
                gotoxy(botCol+2, botRow2+1);
                printf(RED"BUSTED"RESET);
                botRow2++;
            }
            count++;
            continue;
        }
        gotoxy(botCol, botRow);
        printf("Bot%d", i+1, game->bots[i].chips);
        if(game->bots[i].folded) {
            cardPrint(botCol, botRow+1, 99, 99);
            cardPrint(botCol + 4, botRow+1, 99, 99);
        } else {
            cardPrint(botCol, botRow+1, game->botHands[i].cards[0].rank, game->botHands[i].cards[0].suit);
            cardPrint(botCol + 4, botRow+1, game->botHands[i].cards[1].rank, game->botHands[i].cards[1].suit);
        }
        count++;
    }
    // Community
    gotoxy(1,3); printf("COMMUNITY CARDS");
    for(int i=0; i<5 && i<game->board.communityCount; i++) {
        cardPrint(1 + i*7, 4, game->boardHand.cards[i].rank, game->boardHand.cards[i].suit);
    }
    gotoxy(55,3);
    printf("Pot: "YELLOW"%d"RESET, game->board.pot);
    gotoxy(55,4);
    const char* winnerName[6] = {"Bot1","Bot2","Bot3","Bot4","Bot5","Player"};
    printf("Winner: %s",winnerName[indexWinner]);
    gotoxy(55,5);
    const char* handtypes[10] = {
            "High card","Pair","Two Pair","Three of a Kind","Straight","Flush","Full House","Four of a Kind","Straight Flush","Royal Flush"
    };
    printf("Hand: %s", handtypes[comboIndex]);
    gotoxy(1,15);
    for(int i = 0; i < 75; i++){
        printf("-");
    }
    // Player
    gotoxy(1,17); printf("PLAYER Chips:%4d", game->player.chips);
    cardPrint(1, 18, game->playerHand.cards[0].rank, game->playerHand.cards[0].suit);
    cardPrint(9, 18, game->playerHand.cards[1].rank, game->playerHand.cards[1].suit);
    

    fflush(stdout);
    gotoxy(1,23);
}

//  TO-DO
//  - Add input
//  - Add Linux and MAC support
//  - Add a showdown screen, show all cards of active players
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