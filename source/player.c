#include "C:\Users\galje\Desktop\PM_Poker_C\include\player.h"
#include <stdio.h>
#include "board.h"
#include "textColor.h"

void initPlayer(Player *p, int startingChips){
    p->chips = startingChips;
    p->bet = 0;
    p->folded = 0;
    p->score = 0;
    p->active=1;//player is "alive"
}
int playerAction(){
    int choice;
    printf("Available actions: \n");
    printf("  >Call/Check - 0\n");
    printf("  >Raise      - 1\n");
    printf("  >All-In     - 2\n");
    printf("  >Fold       - 3\n");
    printf(">Select: ");
    scanf("%d",&choice);
    printf("\n");
    return choice;
}
void Player_Call_Check(Player *p, Board *b){
    placeInPot(p, b);
    printf("Player's move: Call/Check\n");
}
void Player_Raise(Player *p,Board *b){
    int currPot = b->pot;
    int playerBet = p->bet;
    int playerRaiseAmount;
    printf("Current information:\n");
    printf("  >Current Pot:%-4d\n",currPot);
    printf("  >Your current bet:%-4d\n",playerBet);
    printf(">Enter the amount you want to raise:");
    scanf("%d",&playerRaiseAmount);
    p->bet += playerRaiseAmount;
    placeInPot(p,b);
}
void Player_ALLIN(Player *p, Board *b){
    printf("Player goes All-In!!!\n");
    int AllInSize = p->chips;
    p->bet = p->chips;
    p->chips = 0;
    placeInPot(p,b);
    b->AllInStatus=1;
    b->AllInSize = AllInSize;
}
void Player_Fold(Player *p,Board *b){
    printf("Player Folded!!!\n");
    p->folded = 1;
    placeInPot(p,b);
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
            ColorfulPrintf(">Invalid User Input, try again",1);
            int errorChoice = playerAction();
            PlayerActionExec(errorChoice,p,b);
    }
}