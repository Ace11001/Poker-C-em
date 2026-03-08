#ifndef PLAYER_H
#define PLAYER_H

typedef struct{
    int chips;
    int bet;
    int folded; //0-active, 1-folded
    int score; //used for scoring
}Player;
void initPlayer(Player *p, int startingChips);

#endif