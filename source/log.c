#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void playerLog(FILE *logfp, GAME *game){
    fprintf(logfp,"Players:%d|Active:%d|Round:%d\n", game->numberOfPlayers, game->numberofActive, game->round);
    fprintf(logfp, ">Player|Active:%d|Folded:%d|Chips:%d|Bet:%d\n", game->player.active, game->player.folded, game->player.chips, game->player.bet);
    fprintf(logfp, ">Bot1  |Active:%d|Folded:%d|Chips:%d|Bet:%d\n", game->bots[0].active, game->bots[0].folded, game->bots[0].chips, game->bots[0].bet);
    fprintf(logfp, ">Bot2  |Active:%d|Folded:%d|Chips:%d|Bet:%d\n", game->bots[1].active, game->bots[1].folded, game->bots[1].chips, game->bots[1].bet);
    fprintf(logfp, ">Bot3  |Active:%d|Folded:%d|Chips:%d|Bet:%d\n", game->bots[2].active, game->bots[2].folded, game->bots[2].chips, game->bots[2].bet);
    fprintf(logfp, ">Bot4  |Active:%d|Folded:%d|Chips:%d|Bet:%d\n", game->bots[3].active, game->bots[3].folded, game->bots[3].chips, game->bots[3].bet);
    fprintf(logfp, ">Bot5  |Active:%d|Folded:%d|Chips:%d|Bet:%d\n", game->bots[4].active, game->bots[4].folded, game->bots[4].chips, game->bots[4].bet);
}
void handLog(FILE *logfp, GAME *game){
    int p1S,p1R,p2S,p2R;
    p1S = game->playerHand.cards[0].suit; p1R = game->playerHand.cards[0].rank;
    p2S = game->playerHand.cards[1].suit; p2R = game->playerHand.cards[1].rank;
    int b11S,b11R,b12S,b12R;
    b11S = game->botHands[0].cards[0].suit; b11R = game->botHands[0].cards[0].rank;
    b12S = game->botHands[0].cards[1].suit; b12R = game->botHands[0].cards[1].rank;
    int b21S,b21R,b22S,b22R;
    b21S = game->botHands[1].cards[0].suit; b21R = game->botHands[1].cards[0].rank;
    b22S = game->botHands[1].cards[1].suit; b22R = game->botHands[1].cards[1].rank;
    int b31S,b31R,b32S,b32R;
    b31S = game->botHands[2].cards[0].suit; b31R = game->botHands[2].cards[0].rank;
    b32S = game->botHands[2].cards[1].suit; b32R = game->botHands[2].cards[1].rank;
    int b41S,b41R,b42S,b42R;
    b41S = game->botHands[3].cards[0].suit; b41R = game->botHands[3].cards[0].rank;
    b42S = game->botHands[3].cards[1].suit; b42R = game->botHands[3].cards[1].rank;
    int b51S,b51R,b52S,b52R;
    b51S = game->botHands[4].cards[0].suit; b51R = game->botHands[4].cards[0].rank;
    b52S = game->botHands[4].cards[1].suit; b52R = game->botHands[4].cards[1].rank;
    const char* rank_names[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King","Ace"};
    const char* suit_names[4] = {"Clubs","Spades","Hearts","Diamonds"};
    fprintf(logfp, "Cards:\n", NULL);
    fprintf(logfp, ">Player|%5s of %-8s|%5s of %-8s\n", rank_names[p1R], suit_names[p1S], rank_names[p2R], suit_names[p2S]);
    fprintf(logfp, ">Bot 1 |%5s of %-8s|%5s of %-8s\n", rank_names[b11R], suit_names[b11S], rank_names[b12R], suit_names[b12S]);
    fprintf(logfp, ">Bot 2 |%5s of %-8s|%5s of %-8s\n", rank_names[b21R], suit_names[b21S], rank_names[b22R], suit_names[b22S]);
    fprintf(logfp, ">Bot 3 |%5s of %-8s|%5s of %-8s\n", rank_names[b31R], suit_names[b31S], rank_names[b32R], suit_names[b32S]);
    fprintf(logfp, ">Bot 4 |%5s of %-8s|%5s of %-8s\n", rank_names[b41R], suit_names[b41S], rank_names[b42R], suit_names[b42S]);
    fprintf(logfp, ">Bot 5 |%5s of %-8s|%5s of %-8s\n", rank_names[b51R], suit_names[b51S], rank_names[b52R], suit_names[b52S]);
}
void boardHLog(FILE *logfp, GAME *game){
    int S1,S2,S3,S4,S5, R1,R2,R3,R4,R5;
    int count = game->boardHand.count;
    fprintf(logfp, "Board Cards:\n", NULL);
    if(count == 3){
        S1 = game->boardHand.cards[0].suit;R1 = game->boardHand.cards[0].rank;
        S2 = game->boardHand.cards[1].suit;R2 = game->boardHand.cards[1].rank;
        S3 = game->boardHand.cards[2].suit;R3 = game->boardHand.cards[2].rank;
        fprintf(logfp,"> %s of %s\n", rank_names[R1], suit_names[S1]);
        fprintf(logfp,"> %s of %s\n", rank_names[R2], suit_names[S2]);
        fprintf(logfp,"> %s of %s\n", rank_names[R3], suit_names[S3]);
    }else if(count == 4){
        S1 = game->boardHand.cards[0].suit;R1 = game->boardHand.cards[0].rank;
        S2 = game->boardHand.cards[1].suit;R2 = game->boardHand.cards[1].rank;
        S3 = game->boardHand.cards[2].suit;R3 = game->boardHand.cards[2].rank;
        S4 = game->boardHand.cards[3].suit;R4 = game->boardHand.cards[3].rank;
        fprintf(logfp,"> %s of %s\n", rank_names[R1], suit_names[S1]);
        fprintf(logfp,"> %s of %s\n", rank_names[R2], suit_names[S2]);
        fprintf(logfp,"> %s of %s\n", rank_names[R3], suit_names[S3]);
        fprintf(logfp,"> %s of %s\n", rank_names[R4], suit_names[S4]);
    }else if(count == 5){
        S1 = game->boardHand.cards[0].suit;R1 = game->boardHand.cards[0].rank;
        S2 = game->boardHand.cards[1].suit;R2 = game->boardHand.cards[1].rank;
        S3 = game->boardHand.cards[2].suit;R3 = game->boardHand.cards[2].rank;
        S4 = game->boardHand.cards[3].suit;R4 = game->boardHand.cards[3].rank;
        S5 = game->boardHand.cards[4].suit;R5 = game->boardHand.cards[4].rank;
        fprintf(logfp,"> %s of %s\n", rank_names[R1], suit_names[S1]);
        fprintf(logfp,"> %s of %s\n", rank_names[R2], suit_names[S2]);
        fprintf(logfp,"> %s of %s\n", rank_names[R3], suit_names[S3]);
        fprintf(logfp,"> %s of %s\n", rank_names[R4], suit_names[S4]);
        fprintf(logfp,"> %s of %s\n", rank_names[R5], suit_names[S5]);
    }else{
        fprintf(logfp,">Board Cards don't exist\n", NULL);
        return;
    }
}