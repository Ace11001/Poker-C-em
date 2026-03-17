#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\galje\Desktop\PM_Poker_C\include\evaluate.h"

/*
Hand combinations:    |Score:
    1. Royal Flush    |10
    2. Straight Flush |9
    3. Four of a Kind |8
    4. Full House     |7
    5. Flush          |6
    6. Straight       |5
    7. Three of a Kind|4
    8. Two Pair       |3
    9. Pair           |2
    10. High card     |1
Iščemo kombinacije 5 kart iz 7 kart ki so na voljo - igralčeve in community karte
=>21 kombinacij/permutacij
*/
//21 permutacij 
void permutateCards(Hand* hand1, Hand* boardhand, Hand5 out[MAX_COMBINATIONS]) {
    Card seven[7];
    seven[0] = hand1->cards[0];
    seven[1] = hand1->cards[1];
    seven[2] = boardhand->cards[0];
    seven[3] = boardhand->cards[1];
    seven[4] = boardhand->cards[2];
    seven[5] = boardhand->cards[3];
    seven[6] = boardhand->cards[4];

    int combo = 0;
    for(int a = 0; a < 3; a++)
    for(int b = a+1; b < 4; b++)
    for(int c = b+1; c < 5; c++)
    for(int d = c+1; d < 6; d++)
    for(int e = d+1; e < 7; e++){
        out[combo].cards[0] = seven[a];
        out[combo].cards[1] = seven[b];
        out[combo].cards[2] = seven[c];
        out[combo].cards[3] = seven[d];
        out[combo].cards[4] = seven[e];
        combo++;
    }
}
void buildFreqMap(Hand5* hand, int freq[13]){
    for(int i = 0; i < 13; i++) freq[i] = 0;
    for(int i = 0; i < COMBO_SIZE; i++) freq[hand->cards[i].rank]++;
}
int isFlush(Hand5* hand){
    int suit = hand->cards[0].suit;
    for(int i = 1; i < COMBO_SIZE; i++){
        if(hand->cards[i].suit != suit)return 0;//False
    }
    return 1;//True
}
int isStraight(Hand5* hand){
    int ranks[COMBO_SIZE];
    for(int i = 0; i < COMBO_SIZE; i++)
        ranks[i] = hand->cards[i].rank;
    //Bubble sort
    for(int i = 0; i < COMBO_SIZE - 1; i++)
        for(int j = i+1; j < COMBO_SIZE; j++)
            if(ranks[j] < ranks[i]){
                int t = ranks[i];
                ranks[i] = ranks[j];
                ranks[j] = t;
            }
    //check: also catches special T,J,Q,K,A = {8,9,10,11,12}
    int normal = 1;
    for(int i = 0; i < COMBO_SIZE - 1; i++)
        if(ranks[i+1] - ranks[i] != 1){ normal = 0; break; }
    if(normal) return 1;
    //Special case: Ace-low A,2,3,4,5 = {0,1,2,3,12}
    if(ranks[0]==0 && ranks[1]==1 && ranks[2]==2 &&
       ranks[3]==3 && ranks[4]==12) return 1;
    return 0;
}

int evaluateHand5(Hand5* hand){
    int freq[13];
    buildFreqMap(hand, freq);
    int flush = isFlush(hand);
    int straight = isStraight(hand);
    int pairs=0, threes=0, fours=0,highrank=0;
    for(int i=0; i < 13; i++){
        if(freq[i]==2)pairs++;
        if(freq[i]==3)threes++;
        if(freq[i]==4)fours++;
        if(freq[i]>0 && i>highrank)highrank=i;
    }
    //Royal Flush:
    if(flush&&straight&&highrank==12){
        //confirm it's not Ace-low
        int hasTwo=0;
        for(int i=0; i < COMBO_SIZE; i++){
            if(hand->cards[i].rank==0)hasTwo=1;
        }
        if(!hasTwo)return 10;               //Royal Flush
        return 9;                           //Steel wheel - rare
    }
    if(flush&&straight)return 9;            //Straight Flush
    if(fours==1)return 8;                   //Four of a Kind
    if(threes==1&&pairs==1)return 7;        //Full House
    if(flush)return 6;                      //Flush
    if(straight)return 5;                   //straight
    if(threes==1)return 4;                  //Three of a Kind
    if(pairs==2)return 3;                   //Two Pair
    if(pairs==1)return 2;                   //Pair
    return 1;                               //High Card
}
int evaluateMain(Hand* hand1,Hand* boardHand){
    Hand5 permutations[MAX_COMBINATIONS];
    permutateCards(hand1, boardHand, permutations);
    int bestScore = 0;
    for(int i = 0; i < MAX_COMBINATIONS; i++){
        int score = evaluateHand5(&permutations[i]);
        if(score>bestScore)bestScore=score;
    }
    return bestScore;
}