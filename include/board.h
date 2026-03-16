#ifndef BOARD_H
#define BOARD_H
typedef struct Player Player;

typedef struct Board{
    int pot;
    int phase;//0-preflop|1-flop|2-turn|3-river
    int AllInStatus; //0-not active 1-active
    int AllInSize; //sizeof All-In bet
}Board;
void initBoard(Board *b);
void payOutPot(Board *b, Player *p);
void placeInPot(Player *p, Board *b);
void bustDetection(Player *p);

#endif