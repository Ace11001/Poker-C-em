#include "player.h"
#include "deck.h"
#include "board.h"
#include "hand.h"
#include "game.h"

void initGame(GAME *g){
    g->startingChips = 1000;
    initPlayer(&(g->player), (g->startingChips),"Player");
    initPlayer(&(g->bot1),(g->startingChips),"Bot 1");
    initPlayer(&(g->bot2),(g->startingChips),"Bot 2");
    initPlayer(&(g->bot3),(g->startingChips),"Bot 3");
    initPlayer(&(g->bot4),(g->startingChips),"Bot 4");
    initPlayer(&(g->bot5),(g->startingChips),"Bot 5");   
    initBoard(&(g->board));
    g->deckTop = 0;
    g->round = 1;
}