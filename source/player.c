#include "player.h"
#include <stdio.h>
#include "board.h"
#include "textColor.h"
#include "UI.h"

void initPlayer(Player *p, int startingChips, char* name){
    p->name = name;
    p->chips = startingChips;
    p->bet = 0;
    p->folded = 0;
    p->score = 0;
    p->active=1;//player is "alive"
}
void DebugPrintPlayer(Player *p){
    printf(RED);
    printf("\nDEBUG %s\n",p->name);
    printf(RESET);
    printf(" >%s.chips:%d\n",p->name,p->chips);
    printf(" >%s.bet:%d\n",p->name, p->bet);
    printf(" >%s.folded:%d\n",p->name,p->folded);
    printf(" >%s.score:%d\n",p->name, p->score);
    printf(" >%s.active:%d\n",p->name, p->active);
}
void playerInitBet(Player *p, Board *b){
    int initBet = b->minBet;
    p->bet=initBet;
}
int playerAction(){
    int choice;
    printf("Available actions: \n");
    printf("  >Call/Check - 0\n");
    printf("  >Raise      - 1\n");
    printf("  >All-In     - 2\n");
    printf("  >Fold       - 3\n");
    printf(">Select: ");
    scanf("%d", &choice);
    printf("\n");
    return choice;
}
void Player_Call_Check(Player *p, Board *b) {
    if(p->bet>b->minBet){
        b->minBet = p->bet;
    }
    int diff = b->minBet - p->bet;
    if (diff > 0) {
        p->bet += diff;
    }
}
void Player_Raise(Player *p, Board *b){
    int currPot = b->pot;
    int playerBet = p->bet;
    int playerRaiseAmount;
    gotoxy(1,23);
    printf(">Enter the amount you want to bet(minimal: %d):", b->minBet+1);
    scanf("%d",&playerRaiseAmount);
    if(playerRaiseAmount <= b->minBet) {
        printf("Invalid raise!\n");
        return;
    }
    int toCall = b->minBet - p->bet;
    p->bet = playerRaiseAmount;
    b->minBet = playerRaiseAmount;
}
void Player_ALLIN(Player *p, Board *b){
    int AllInSize = p->chips;
    p->bet = AllInSize;
    b->minBet = AllInSize;
    b->AllInStatus=1;
    b->AllInSize = AllInSize;
}
void Player_Fold(Player *p,Board *b){
    p->folded = 1;
}
void PlayerActionExec(int choice, Player *p, Board *b){
    switch(choice){
        case 0:
            Player_Call_Check(p, b);
            break;
        case 1:
            Player_Raise(p, b);
            break;
        case 2:
            Player_ALLIN(p, b);
            break;
        case 3:
            Player_Fold(p, b);
            break;
        default:
            ColPrintf(" > Invalid User Input, try again\n",1);
            int errorChoice = playerAction();
            PlayerActionExec(errorChoice,p,b);
            break;
    }
}
void PlayerSetScore(Player *p, int scoreInput){
    p->score = scoreInput;
}