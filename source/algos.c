#include "C:\Users\galje\Desktop\PM_Poker_C\include\algos.h"
#include "C:\Users\galje\Desktop\PM_Poker_C\include\hand.h"
#include "C:\Users\galje\Desktop\PM_Poker_C\include\evaluate.h"

int ChensFormula(Hand* h) {
    const double firstStepScores[13] = {1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,6.0,7.0,8.0,10.0};
    double score = 0.0;
    int val1 = h->cards[0].rank;
    int val2 = h->cards[1].rank;
    int biggerVal;
    if (val1 == val2) {
        if (val1 <= 3) {
            score = 5.0;
        } else {
            score = 2.0 * firstStepScores[val1];
        }
        biggerVal = val1;
    } else {
        if (val1 > val2) {
            biggerVal = val1;
        } else {
            biggerVal = val2;
        }
        score = firstStepScores[biggerVal];
    }
    if (h->cards[0].suit == h->cards[1].suit) {
        score += 2.0;
    }
    int razpon;
    if (val1 == val2) {
        razpon = 0;
    } else if (val1 == 12 || val2 == 12) {
        int other = (val1 == 12) ? val2 : val1;
        razpon = 12 - other - 1;
        if (razpon > 3) razpon = 4;
    } else {
        razpon = val1 - val2;
        if (razpon < 0) razpon *= -1;
        razpon -= 1;
    }
    if (razpon < 0) razpon = 0;
    if (val1 != val2) {
        if (razpon == 1) {
            score -= 1.0;
        } else if (razpon == 2) {
            score -= 2.0;
        } else if (razpon == 3) {
            score -= 4.0;
        } else if (razpon >= 4) {
            score -= 5.0;
        }
        if (razpon <= 1 && biggerVal <= 8) {
            score += 1.0;
        }
    }
    int result = (int)ceil(score);
    if (result < 1) result = 1;  // never returns 0
    return result;
}
int SklanskyMalmuth(Hand *h) {  
/*Sklansky & Malmuth table
    1. AA, AKs, KK, QQ, JJ
    2. AK, AQs, AJs, KQs, TT
    3. AQ, ATs, KJs, QJs, JTs, 99
    4. AJ, KQ, KTs, QTs, J9s, T9s, 98s, 88
    5. (from A9s to A2s), KJ, QJ, JT, Q9s, T8s, 97s, 87s, 77, 76s, 66
    6. AT, KT, QT, J8s, 86s, 75s, 65s, 55, 54s
    7. (from K9s to K2s), J9, T9, 98, 64s, 53s, 44, 43s, 33, 22
    8. A9, K9, Q9, J8, J7s, T8, 96s, 87, 85s, 76, 74s, 65, 54, 42s, 32s
    9. All other hands not required above.*/
    int card1rank, card1suit, card2rank, card2suit;
    if ((h->cards[0].rank - h->cards[1].rank) >= 0) {
        card1rank = h->cards[0].rank; card1suit = h->cards[0].suit;
        card2rank = h->cards[1].rank; card2suit = h->cards[1].suit;
    } else {
        card1rank = h->cards[1].rank; card1suit = h->cards[1].suit;
        card2rank = h->cards[0].rank; card2suit = h->cards[0].suit;
    }
    // card1 >= card2 guaranteed
    //index: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
    // rank: 2, 3, 4, 5, 6, 7, 8, 9,10, J,  Q,  K,  A
 
    int isPair   = (card1rank == card2rank);
    int isSuited = (card1suit == card2suit);
    int gap      = card1rank - card2rank; // always >= 0
    // Group 1: AA, AKs, KK, QQ, JJ
    if ((isPair && card1rank >= 9) ||
        (isSuited && card1rank == 12 && card2rank == 11)) {
        return 1;
    }
    // Group 2: AK, AQs, AJs, KQs, TT
    if ((card1rank == 12 && card2rank == 11 && !isSuited) ||
        (isSuited && card1rank == 12 && card2rank == 10) ||
        (isSuited && card1rank == 12 && card2rank == 9)  ||
        (isSuited && card1rank == 11 && card2rank == 10) ||
        (isPair && card1rank == 8)) {
        return 2;
    }
    // Group 3: AQ, ATs, KJs, QJs, JTs, 99
    if ((card1rank == 12 && card2rank == 10 && !isSuited) ||
        (isSuited && card1rank == 12 && card2rank == 8)   ||
        (isSuited && card1rank == 11 && card2rank == 9)   ||
        (isSuited && card1rank == 10 && card2rank == 9)   ||
        (isSuited && card1rank == 9  && card2rank == 8)   ||
        (isPair && card1rank == 7)) {
        return 3;
    }
    // Group 4: AJ, KQ, KTs, QTs, J9s, T9s, 98s, 88
    if ((card1rank == 12 && card2rank == 9  && !isSuited) ||
        (card1rank == 11 && card2rank == 10 && !isSuited) ||
        (isSuited && card1rank == 11 && card2rank == 8)   ||
        (isSuited && card1rank == 10 && card2rank == 8)   ||
        (isSuited && card1rank == 9  && card2rank == 7)   ||
        (isSuited && card1rank == 8  && card2rank == 7)   ||
        (isSuited && card1rank == 7  && card2rank == 6)   ||
        (isPair && card1rank == 6)) {
        return 4;
    }
    // Group 5: A9s-A2s, KJ, QJ, JT, Q9s, T8s, 97s, 87s, 77, 76s, 66
    if ((isSuited && card1rank == 12 && card2rank >= 0 && card2rank <= 7) ||
        (card1rank == 11 && card2rank == 9  && !isSuited) ||
        (card1rank == 10 && card2rank == 9  && !isSuited) ||
        (card1rank == 9  && card2rank == 8  && !isSuited) ||
        (isSuited && card1rank == 10 && card2rank == 7)   ||
        (isSuited && card1rank == 8  && card2rank == 5)   ||
        (isSuited && card1rank == 7  && card2rank == 5)   ||
        (isSuited && card1rank == 6  && card2rank == 5)   ||
        (isPair && card1rank == 5)                        ||
        (isPair && card1rank == 4)) {
        return 5;
    }
    // Group 6: AT, KT, QT, J8s, 86s, 75s, 65s, 55, 54s
    if ((card1rank == 12 && card2rank == 8  && !isSuited) ||
        (card1rank == 11 && card2rank == 8  && !isSuited) ||
        (card1rank == 10 && card2rank == 8  && !isSuited) ||
        (isSuited && card1rank == 9  && card2rank == 6)   ||
        (isSuited && card1rank == 6  && card2rank == 4)   ||
        (isSuited && card1rank == 5  && card2rank == 3)   ||
        (isSuited && card1rank == 4  && card2rank == 3)   ||
        (isPair && card1rank == 3)                        ||
        (isSuited && card1rank == 3  && card2rank == 2)) {
        return 6;
    }
    // Group 7: K9s-K2s, J9, T9, 98, 64s, 53s, 44, 43s, 33, 22
    if ((isSuited && card1rank == 11 && card2rank >= 0 && card2rank <= 7) ||
        (card1rank == 9  && card2rank == 7  && !isSuited) ||
        (card1rank == 8  && card2rank == 7  && !isSuited) ||
        (card1rank == 7  && card2rank == 6  && !isSuited) ||
        (isSuited && card1rank == 4  && card2rank == 2)   ||
        (isSuited && card1rank == 3  && card2rank == 1)   ||
        (isPair && card1rank == 2)                        ||
        (isSuited && card1rank == 2  && card2rank == 1)   ||
        (isPair && card1rank == 1)                        ||
        (isPair && card1rank == 0)) {
        return 7;
    }
    // Group 8: A9, K9, Q9, J8, J7s, T8, 96s, 87, 85s, 76, 74s, 65, 54, 42s, 32s
    if ((card1rank == 12 && card2rank == 7  && !isSuited) ||
        (card1rank == 11 && card2rank == 7  && !isSuited) ||
        (card1rank == 10 && card2rank == 7  && !isSuited) ||
        (card1rank == 9  && card2rank == 6  && !isSuited) ||
        (isSuited && card1rank == 9  && card2rank == 5)   ||
        (card1rank == 8  && card2rank == 6  && !isSuited) ||
        (isSuited && card1rank == 7  && card2rank == 4)   ||
        (card1rank == 6  && card2rank == 5  && !isSuited) ||
        (card1rank == 5  && card2rank == 4  && !isSuited) ||
        (isSuited && card1rank == 2  && card2rank == 0)   ||
        (isSuited && card1rank == 1  && card2rank == 0)) {
        return 8;
    }
    // Group 9: everything else
    return 9;
}

