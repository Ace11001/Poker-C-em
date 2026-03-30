#include "algos.h"
#include "hand.h"
#include "evaluate.h"
#include "game.h"

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
    // Group 1: AA, AKs, KK, QQ, JJ
    if ((isPair && card1rank >= 9) ||
        (isSuited && card1rank == 12 && card2rank == 11)) {
        return 9;
    }
    // Group 2: AK, AQs, AJs, KQs, TT
    if ((card1rank == 12 && card2rank == 11 && !isSuited) ||
        (isSuited && card1rank == 12 && card2rank == 10) ||
        (isSuited && card1rank == 12 && card2rank == 9)  ||
        (isSuited && card1rank == 11 && card2rank == 10) ||
        (isPair && card1rank == 8)) {
        return 8;
    }
    // Group 3: AQ, ATs, KJs, QJs, JTs, 99
    if ((card1rank == 12 && card2rank == 10 && !isSuited) ||
        (isSuited && card1rank == 12 && card2rank == 8)   ||
        (isSuited && card1rank == 11 && card2rank == 9)   ||
        (isSuited && card1rank == 10 && card2rank == 9)   ||
        (isSuited && card1rank == 9  && card2rank == 8)   ||
        (isPair && card1rank == 7)) {
        return 7;
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
        return 6;
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
        return 4;
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
        return 3;
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
        return 2;
    }
    // Very weak but still “better than total trash”: A2s–A9s, K2s–K9s, Q2s–Q9s, etc.
    if ((card1rank == 12 && card2rank >= 0 && card2rank <= 7 && isSuited) ||
        (card1rank == 11 && card2rank >= 0 && card2rank <= 7 && isSuited) ||
        (card1rank == 10 && card2rank >= 0 && card2rank <= 7 && isSuited)) {
        return 3;
    }
    // Group 9: everything else
    return 1;
}
int BoardTexture(Hand* board, int communityCount){
    int rankCount[13] = {0};
    int boardCount = communityCount;
    for(int i = 0; i < boardCount; i++) {
        int rank = board->cards[i].rank;
        rankCount[rank]++;
    }
    int suitCount[4] = {0};
    for(int i = 0; i < boardCount; i++) {
        int suit = board->cards[i].suit;
        suitCount[suit]++;
    }   
    /*debug print freq
    printf("Suit occurences:\n|C|S|H|D|\n");
    for(int i = 0; i<4;i++){
        printf("|%d",suitCount[i]);
    }
    printf("|\n");
    printf("Rank occurences:\n");
    printf("| 0  1  2  3  4  5  6  7  8  9 10 11 12|\n");
    printf("| 2| 3| 4| 5| 6| 7| 8| 9|10| J| Q| K| A|\n");
    for(int i = 0; i < 13; i++){
        printf("|%-2d",rankCount[i]);
    }
    printf("|\n");
    end of debug1*/

    int maxSuitFreq = 1;
    int maxSuitIndex = 0;
    for(int i = 0; i < 4; i++){
        if(suitCount[i]>maxSuitFreq){
            maxSuitFreq=suitCount[i];
            maxSuitIndex = i;
        }
    }//if there are 4 cards with 2 pairs of the same suit we neglect the correct index
    int pairs=0,threes=0,fours=0,highrank=0;
    for(int i=0; i < 13; i++){
        if(rankCount[i]==2)pairs++;
        if(rankCount[i]==3)threes++;
        if(rankCount[i]==4)fours++;
        if(rankCount[i]>0 && i>highrank)highrank=i;
    }
    int gapScore=0;
    int gapRanks[5];
    for(int i = 0; i < 5; i++){
        gapRanks[i] = board->cards[i].rank;
    }
    for(int i = 0; i < 4; i++){//sort
        for(int j = 0; j < 4-i; j++){
            if(gapRanks[j]>gapRanks[j+1]){
                int gapTemp = gapRanks[j];
                gapRanks[j]=gapRanks[j+1];
                gapRanks[j+1]=gapTemp; 
            }
        }
    }
    int uniqueRanks[5],uniqueCount=0;
    uniqueRanks[0]=gapRanks[0];
    for(int i = 1; i < 5; i++){
        if(gapRanks[i]!=uniqueRanks[i]){
            uniqueRanks[++uniqueCount]=gapRanks[i];
        }
    }
    float avgGap;
    if(uniqueCount>=2){
        int totalGap = 0;
        for(int i = 0; i < uniqueCount-1; i++){
            totalGap += uniqueRanks[i+1] - uniqueRanks[i];
        }
        avgGap = (float)totalGap/(uniqueCount-1);
        if(avgGap <=1.0f)gapScore=3;
        else if(avgGap<=1.5f)gapScore=2;
        else if(avgGap<=2.0f)gapScore=2;
        else gapScore=0;
    }
    //printf("|maxSuitFreq:%d|maxSuitIndex:%d|\n",maxSuitFreq,maxSuitIndex);
    //printf("\n\n");
    //printf("4Kind Count:%d|3Kind Count:%d|pair Count:%d|highcard Index:%d|\n",fours,threes,pairs,highrank);
    int FlushScore;//Higher - More chance other players complete a Flush
    switch(maxSuitFreq){
            case 5:
                FlushScore = 3;//auto flush
                break;
            case 4:
                FlushScore = 2;//high likelyhood of flush
                break;
            case 3:
                FlushScore = 1;//small chance of flush
                break;
            default:
                FlushScore = 0;//No chance for flush
                break;
        }
    //printf("FlushScore:%d\n",FlushScore);
    //printf("Gap Score:%d| Avg Gap Score:%.1f\n",gapScore, avgGap);
    int textureScore = FlushScore + gapScore + pairs + (threes*2);
    return textureScore;
    /*
    Texture 0-2:   "DRY"    
    Texture 3-5:   "MEDIUM"   
    Texture 6-8:   "WET"      
    Texture 9-12:  "WETTEST"   
    */
}
int gapScoreLen(Hand* board, int numOfCards) {
    if (numOfCards < 2) return 0;
    int gapScore = 0;
    int gapRanks[5];
    for(int i = 0; i < numOfCards; i++) {
        gapRanks[i] = board->cards[i].rank;
    }
    for(int i = 0; i < numOfCards-1; i++) {
        for(int j = 0; j < numOfCards-1-i; j++) {
            if(gapRanks[j] > gapRanks[j+1]) {
                int temp = gapRanks[j];
                gapRanks[j] = gapRanks[j+1];
                gapRanks[j+1] = temp;
            }
        }
    }
    int uniqueCount = 1;
    int uniqueRanks[5];
    uniqueRanks[0] = gapRanks[0];
    for(int i = 1; i < numOfCards; i++) {
        if(gapRanks[i] != uniqueRanks[uniqueCount-1]) {
            uniqueRanks[uniqueCount] = gapRanks[i];
            uniqueCount++;
        }
    }
    if(uniqueCount >= 2) {
        int totalGap = 0;
        for(int i = 0; i < uniqueCount-1; i++) {
            totalGap += uniqueRanks[i+1] - uniqueRanks[i];
        }
        float avgGap = (float)totalGap / (uniqueCount-1);
        if(avgGap <= 1.0f) gapScore = 3;
        else if(avgGap <= 1.5f) gapScore = 2;
        else if(avgGap <= 2.0f) gapScore = 1;
        else gapScore = 0;
    }
    return gapScore;
}
void bot_PreFlop(GAME *g, int botIndex){
    int Astatus = g->bots[botIndex].active;
    int Fstatus = g->bots[botIndex].folded;
    if( Astatus == 1 && Fstatus == 0){
        int chen = ChensFormula(&g->botHands[botIndex]); //higher is better
        int SklMal = SklanskyMalmuth(&g->botHands[botIndex]); //higher is better
        int gap = gapScoreLen(&g->botHands[botIndex], 2); //Lower is better
        //Normalise scores
        double chen_norm = (chen-1) / 21.0;
        double SklMal_norm = (SklMal-1) / 8.0;
        double gap_norm = gap / 3.0;
        //weights for scoring
        double weight1 = 0.4;
        double weight2 = 0.4;
        double weight3 = 0.2;
        double score = weight1 * chen_norm + weight2 * SklMal_norm + weight3 * gap_norm;
        /*DebugPrints
        printf("bot%d: chen=%d, SklMal=%d, gap=%d\n", botIndex+1, chen, SklMal, gap);
        printf("chen_norm=%.3f, SklMal_norm=%.3f, gap_norm=%.3f\n",chen_norm, SklMal_norm, gap_norm);
        printf("bot%d PreFlop Score: %lf\n",botIndex+1,score);
        */
        if(score < 0.04){
            //fold
            g->bots[botIndex].folded = 1;
            printf("Bot%d folds\n",1+botIndex);
            return;
        } else if(score < 0.10){
            if(g->board.minBet > 2){//fold if someone raised before; also magic number, fix later
                g->bots[botIndex].folded=1;
                printf("Bot%d folds\n",1+botIndex);
                return;
            }else{
                g->bots[botIndex].bet = g->board.minBet;
                printf("Bot%d calls\n",1+botIndex);
                placeInPot(&g->bots[botIndex], &g->board);
                return;
            }
        } else if(score < 0.30){
            //call
            g->bots[botIndex].bet = g->board.minBet;
            printf("Bot%d calls\n",botIndex+1);
            placeInPot(&g->bots[botIndex], &g->board);
            return;
        } else if(score < 0.55){
            //raise 3 bet
            g->bots[botIndex].bet = 6; //magic number, fix later
            g->board.minBet = g->bots[botIndex].bet;
            printf("Bot%d raises %d\n",botIndex+1,g->bots[botIndex].bet);
            placeInPot(&g->bots[botIndex], &g->board);
            return;
        } else{
            //raise 4 bet
            g->bots[botIndex].bet = 12; //magic number, fix later
            g->board.minBet = g->bots[botIndex].bet;
            printf("Bot%d raises %d\n",botIndex+1,g->bots[botIndex].bet);
            placeInPot(&g->bots[botIndex], &g->board);
            return;
        }
    }else{return;}
}
void bot_Flop(GAME *g, int botIndex) {
    int botId = botIndex + 1;
    int Astatus = g->bots[botIndex].active;
    int Fstatus = g->bots[botIndex].folded;
    if (Astatus != 1 || Fstatus == 1) {
        return;
    }
    if (g->board.communityCount < 3) {
        printf("Bot%d: No flop\n", botId);
        return;
    }

    int chen = ChensFormula(&g->botHands[botIndex]);
    int SklMal = SklanskyMalmuth(&g->botHands[botIndex]);
    int gap = gapScoreLen(&g->botHands[botIndex], 2);

    // Normalize 
    double chen_norm = (chen > 0 && chen <= 22) ? (chen - 1) / 21.0 : 0.0;
    double SklMal_norm = (SklMal > 0 && SklMal <= 9) ? (SklMal - 1) / 8.0 : 0.0;
    double gap_norm = (gap >= 0 && gap <= 3) ? gap / 3.0 : 1.0;

    double scorePreFlop = 0.4 * chen_norm + 0.4 * SklMal_norm + 0.2 * gap_norm;
    int texture = BoardTexture(&g->boardHand, g->board.communityCount);
    double texture_norm = (texture >= 0 && texture <= 12) ? texture / 12.0 : 0.5;
    double scoreFlop = 0.7 * scorePreFlop + 0.3 * (1.0 - texture_norm);

    printf("Bot%d Flop score: %.6f (chen=%.2f skl=%.2f tex=%.2f)\n",
           botId, scoreFlop, chen_norm, SklMal_norm, texture_norm);
    fflush(stdout);

    // Chips status (fixed init)
    int otherChips = g->player.chips;
    for (int i = 0; i < 5; i++) {
        otherChips += g->bots[i].chips;
    }
    otherChips -= g->bots[botIndex].chips;
    double chipAvg = (g->numberOfPlayers > 0) ? otherChips / (double)g->numberOfPlayers : 0;
    int chipsStatus = (g->bots[botIndex].chips > chipAvg) ? 1 : 0;

    int minBet = g->board.minBet;
    int stack = g->bots[botIndex].chips;
    int maxRaise = stack / 3;          // never raise more than ~1/3 of stack
    if (maxRaise < 6) maxRaise = 6;

    int raise3x = minBet * 3;
    int raiseSize = raise3x;
    if (raise3x > maxRaise) {
        raiseSize = maxRaise;
    }

    if (scoreFlop < 0.25) {
        g->bots[botIndex].folded = 1;
        printf("Bot%d folds\n", botId);
    } else if (scoreFlop < 0.35) {
        if (minBet > 2) {
            g->bots[botIndex].folded = 1;
            printf("Bot%d folds\n", botId);
        } else {
            g->bots[botIndex].bet = minBet;
            printf("Bot%d checks\n", botId);
            placeInPot(&g->bots[botIndex], &g->board);
        }
    } else if (scoreFlop < 0.45) {
        g->bots[botIndex].bet = minBet;
        printf("Bot%d calls %d\n", botId, minBet);
        placeInPot(&g->bots[botIndex], &g->board);
    } else if (scoreFlop < 0.55 || chipsStatus == 1) {
        g->bots[botIndex].bet = raiseSize;
        g->board.minBet = raiseSize;
        printf("Bot%d raises %d\n", botId, raiseSize);
        placeInPot(&g->bots[botIndex], &g->board);
    } else {
        g->bots[botIndex].bet = stack;  // All‑in only on very strong hands
        printf("Bot%d raises %d\n", botId, stack);
        placeInPot(&g->bots[botIndex], &g->board);
    }
    fflush(stdout);
}
void bot_Turn(GAME *g, int botIndex) {
    int botId = botIndex + 1;
    int Astatus = g->bots[botIndex].active;
    int Fstatus = g->bots[botIndex].folded;
    if (Astatus != 1 || Fstatus == 1) {
        return;
    }

    if (g->board.communityCount < 4) {
        printf("Bot%d: No turn\n", botId);
        return;
    }

    int chen = ChensFormula(&g->botHands[botIndex]);
    int SklMal = SklanskyMalmuth(&g->botHands[botIndex]);
    int gap = gapScoreLen(&g->botHands[botIndex], 2);

    double chen_norm = (chen > 0 && chen <= 22) ? (chen - 1) / 21.0 : 0.0;
    double SklMal_norm = (SklMal > 0 && SklMal <= 9) ? (SklMal - 1) / 8.0 : 0.0;
    double gap_norm = (gap >= 0 && gap <= 3) ? gap / 3.0 : 1.0;

    double scorePreFlop = 0.4 * chen_norm + 0.4 * SklMal_norm + 0.2 * gap_norm;
    int texture = BoardTexture(&g->boardHand, g->board.communityCount);
    double texture_norm = (texture >= 0 && texture <= 12) ? texture / 12.0 : 0.5;

    double scoreTurn = 0.6 * scorePreFlop + 0.4 * (1.0 - texture_norm);

    printf("Bot%d Turn score: %.6f (chen=%.2f skl=%.2f tex=%.2f)\n",
           botId, scoreTurn, chen_norm, SklMal_norm, texture_norm);
    fflush(stdout);

    int otherChips = g->player.chips;
    for (int i = 0; i < 5; i++) {
        otherChips += g->bots[i].chips;
    }
    otherChips -= g->bots[botIndex].chips;
    double chipAvg = (g->numberOfPlayers > 0) ? otherChips / (double)g->numberOfPlayers : 0;
    int chipsStatus = (g->bots[botIndex].chips > chipAvg) ? 1 : 0;

    int minBet = g->board.minBet;
    int stack = g->bots[botIndex].chips;
    int maxRaise = stack / 3;
    if (maxRaise < 6) maxRaise = 6;

    int raise3x = minBet * 3;
    int raiseSize = raise3x;
    if (raise3x > maxRaise) {
        raiseSize = maxRaise;
    }
    printf("Bot%d: minBet=%d, stack=%d, maxRaise=%d, raise3x=%d, raiseSize=%d\n",
       botId, minBet, stack, maxRaise, raise3x, raiseSize);

    if (scoreTurn < 0.25) {
        g->bots[botIndex].folded = 1;
        printf("Bot%d folds\n", botId);
    } else if (scoreTurn < 0.35) {
        if (minBet > 2) {
            g->bots[botIndex].folded = 1;
            printf("Bot%d folds\n", botId);
        } else {
            g->bots[botIndex].bet = minBet;
            printf("Bot%d checks\n", botId);
            placeInPot(&g->bots[botIndex], &g->board);
        }
    } else if (scoreTurn < 0.45) {
        g->bots[botIndex].bet = minBet;
        printf("Bot%d calls %d\n", botId, minBet);
        placeInPot(&g->bots[botIndex], &g->board);
    } else if (scoreTurn < 0.55 || chipsStatus == 1) {
        g->bots[botIndex].bet = raiseSize;
        g->board.minBet = raiseSize;
        printf("Bot%d raises %d\n", botId, raiseSize);
        placeInPot(&g->bots[botIndex], &g->board);
    } else {
        g->bots[botIndex].bet = stack;
        printf("Bot%d raises %d\n", botId, stack);
        placeInPot(&g->bots[botIndex], &g->board);
    }
    fflush(stdout);
}
void bot_River(GAME *g, int botIndex) {
    int botId = botIndex + 1;
    int Astatus = g->bots[botIndex].active;
    int Fstatus = g->bots[botIndex].folded;
    if (Astatus != 1 || Fstatus == 1) {
        return;
    }

    if (g->board.communityCount < 5) {
        printf("Bot%d: No river\n", botId);
        return;
    }

    int chen = ChensFormula(&g->botHands[botIndex]);
    int SklMal = SklanskyMalmuth(&g->botHands[botIndex]);
    int gap = gapScoreLen(&g->botHands[botIndex], 2);

    double chen_norm = (chen > 0 && chen <= 22) ? (chen - 1) / 21.0 : 0.0;
    double SklMal_norm = (SklMal > 0 && SklMal <= 9) ? (SklMal - 1) / 8.0 : 0.0;
    double gap_norm = (gap >= 0 && gap <= 3) ? gap / 3.0 : 1.0;

    double scorePreFlop = 0.4 * chen_norm + 0.4 * SklMal_norm + 0.2 * gap_norm;
    int texture = BoardTexture(&g->boardHand, g->board.communityCount);
    double texture_norm = (texture >= 0 && texture <= 12) ? texture / 12.0 : 0.5;

    double scoreRiver = 0.5 * scorePreFlop + 0.5 * (1.0 - texture_norm);

    printf("Bot%d River score: %.6f (chen=%.2f skl=%.2f tex=%.2f)\n",
           botId, scoreRiver, chen_norm, SklMal_norm, texture_norm);
    fflush(stdout);

    int otherChips = g->player.chips;
    for (int i = 0; i < 5; i++) {
        otherChips += g->bots[i].chips;
    }
    otherChips -= g->bots[botIndex].chips;
    double chipAvg = (g->numberOfPlayers > 0) ? otherChips / (double)g->numberOfPlayers : 0;
    int chipsStatus = (g->bots[botIndex].chips > chipAvg) ? 1 : 0;

    int minBet = g->board.minBet;
    int stack = g->bots[botIndex].chips;
    int maxRaise = stack / 3;          // cap raises to ~1/3 of stack
    if (maxRaise < 6) maxRaise = 6;

    int raise3x = minBet * 3;
    int raiseSize = raise3x;
    if (raise3x > maxRaise) {
        raiseSize = maxRaise;
    }

    if (scoreRiver < 0.25) {
        g->bots[botIndex].folded = 1;
        printf("Bot%d folds\n", botId);
    } else if (scoreRiver < 0.35) {
        if (minBet > 2) {
            g->bots[botIndex].folded = 1;
            printf("Bot%d folds\n", botId);
        } else {
            g->bots[botIndex].bet = minBet;
            printf("Bot%d checks\n", botId);
            placeInPot(&g->bots[botIndex], &g->board);
        }
    } else if (scoreRiver < 0.45) {
        g->bots[botIndex].bet = minBet;
        printf("Bot%d calls %d\n", botId, minBet);
        placeInPot(&g->bots[botIndex], &g->board);
    } else if (scoreRiver < 0.55 || chipsStatus == 1) {
        g->bots[botIndex].bet = raiseSize;
        g->board.minBet = raiseSize;
        printf("Bot%d raises %d\n", botId, raiseSize);
        placeInPot(&g->bots[botIndex], &g->board);
    } else {
        g->bots[botIndex].bet = stack;  // All‑in on very strong hands
        printf("Bot%d raises %d\n", botId, stack);
        placeInPot(&g->bots[botIndex], &g->board);
    }
    fflush(stdout);
}