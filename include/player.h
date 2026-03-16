#ifndef PLAYER_H
#define PLAYER_H

typedef struct Board Board;

typedef struct Player{
    int chips;
    int bet;
    int folded; //0-active, 1-folded
    int score;  //used for scoring
    int active;
} Player;

void initPlayer(Player *p, int startingChips);
int playerAction();
void Player_Call_Check(Player *p, Board *b);
void Player_Raise(Player *p, Board *b);
void Player_ALLIN(Player *p, Board *b);
void Player_Fold(Player *p, Board *b);
void PlayerActionExec(int choice, Player *p, Board *b);
void PlayerSetScore(Player *p, int score);
#endif