#include "C:\Users\galje\Desktop\PM_Poker_C\include\player.h"
#include <stdio.h>

void initPlayer(Player *p, int startingChips){
    p->chips = startingChips;
    p->bet = 0;
    p->folded = 0;
    p->score = 0;
}
