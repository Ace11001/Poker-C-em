#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int rank;//0-12
    int suit;//0-3
}Card;

const char* rank_names[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King","Ace"};
const char* suit_names[4] = {"Clubs","Spades","Hearts","Diamonds"};
//examples for cards:
//deck[0].rank = 0; deck[0].suit = 0; -> 2 of Clubs
//deck[22].rank = 9; deck[22].suit = 1; ->Jack of Spades
//printf( "%s of %s\n", rank_names[deck[index].rank, suit_names[[index].suit] )

Card deck[52];//deck init

void createDeck(Card* deck) {
    srand(time(NULL));
    int index = 0;
    for(int suit = 0; suit < 4; suit++){
        for(int rank = 0; rank < 13; rank++){
            deck[index].suit = suit;
            deck[index].rank = rank;
            index++;
        }
    }
}
void printCardName(const Card* card){
    printf( ">%s of %s\n", rank_names[card->rank], suit_names[card->suit]);
}
void DEBUG_printDeck(const Card* deck){
    for(int i=0; i < 52; i++){
        printCardName(&deck[i]);
    }
}
void shuffleDeck(Card* deck){
    for(int i=51; i > 0; i--){
        int j = rand()%(i+1);
        Card temp = deck[i];
        deck[i]=deck[j];
        deck[j]=temp;
    }
}