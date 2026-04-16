#include <stdlib.h>
#include "algos.h"
#include "hand.h"
#include "evaluate.h"
#include "game.h"
#include "UI.h"
#include "log.h"

double botAnalysis(GAME *g, int botIndex, int phase, FILE *logfp){//phase - 0Preflop, 1FLop, 2Turn, 3River
    int botId = botIndex + 1;
    int Astatus = g->bots[botIndex].active;
    int Fstatus = g->bots[botIndex].folded;
    const char* phase_names[] = {"PreFlop", "Flop", "Turn", "River"};
    int chipsLOG; int betLOG;
    chipsLOG = g->bots[botIndex].chips; betLOG = g->bots[botIndex].bet;
    fprintf(logfp, ">phase %s|active=%d|folded=%d|chips:%d|bet:%d\n", phase_names[phase], Astatus, Fstatus, chipsLOG, betLOG);
    if (Astatus != 1 || Fstatus == 1) {
        fprintf(logfp, ">BOT%d: skipped, returning -1\n", botIndex+1);
        return -1.0;
    }
    fflush(logfp);
    int chen = ChensFormula(&g->botHands[botIndex]);
    int sklMal = SklanskyMalmuth(&g->botHands[botIndex]);
    int gap = gapScoreLen(&g->botHands[botIndex], g->botHands[botIndex].count);
    // Normalize to [0,1]
    double chen_norm = (chen > 0 && chen <= 22) ? (chen - 1) / 21.0 : 0.0;      // Chen: 1–22
    double sklMal_norm = (sklMal > 0 && sklMal <= 9) ? (sklMal - 1) / 8.0 : 0.0; // Group 1–9
    double gap_norm = (gap >= 0 && gap <= 3) ? gap / 3.0 : 1.0;                  // Gap 0–3
    
    fprintf(logfp, ">CHEN: %d -> norm=%.3f|", chen, chen_norm);
    fprintf(logfp, "SKL&MAL: %d -> norm=%.3f|", sklMal, sklMal_norm);
    fprintf(logfp, "GAP: %d -> norm=%.3f\n", gap, gap_norm);
    fflush(logfp);

    double scorePreFlop = 0.3 * chen_norm + 0.4 * sklMal_norm + 0.3 * gap_norm;
    if(phase == 0){
        fprintf(logfp, ">scorePreFlop: %.3f\n", scorePreFlop);
        fflush(logfp);
        return scorePreFlop;}
    double scoreFlop;
    if(g->boardHand.count != 0){
        int texture = BoardTexture(&g->boardHand, g->board.communityCount);
        double texture_norm = (texture >= 0 && texture <= 12) ? texture / 12.0 : 0.5;
        scoreFlop = 0.7 * scorePreFlop + 0.3 * (1.0 - texture_norm);
    } else {
        scoreFlop = 0.7 * scorePreFlop + 0.3;
    }

    int otherChips = g->player.chips;
    for(int i = 0; i < 5; i++){
        if(i != botIndex){
            otherChips += g->bots[i].chips;
        }
    }
    int effectiveActive = g->numberofActive > 0 ? g->numberofActive : 1;
    double chipAvg = otherChips / effectiveActive;

    double chipBoost = 0.0;
    if(g->bots[botIndex].chips > chipAvg){
        chipBoost = 0.1;
    }    
    

    double finalScore = scoreFlop + chipBoost;
    if(finalScore > 1.0) finalScore = 1.0;
    if(finalScore < 0.0) finalScore = 0.0;

    fprintf(logfp, ">BOT%d ANALYSIS - finalScore: %.3f\n",botIndex+1, finalScore);
    fflush(logfp);
    return finalScore;
}
int calculateRaise(GAME *g, int botIndex, int phase){
    int chips = g->bots[botIndex].chips;
    int currBet = g->bots[botIndex].bet;
    int availableChips = chips - currBet;
    int minBet = g->board.minBet;
    int pot = g->board.pot;
    int raise;
    int maxRaise;

    // 1. Pick a baseline raise‑size (as a fraction of pot)

    double raiseMult = 0.5;
    if(phase == 0) raiseMult = 0.5;   // Smaller raises to prevent exponential growth
    if(phase == 1) raiseMult = 0.3;
    if(phase == 2) raiseMult = 0.3;
    if(phase == 3) raiseMult = 0.2;

    raise = minBet + (int)(pot * raiseMult);

    // 2. Clamp to sane stack limits

    if(raise > availableChips){
        raise = availableChips;
    }
    if(raise < minBet + 1 && (minBet + 1 <= availableChips)){
        raise = minBet + 1;
    }

    // 3. Your existing maxRaise caps per phase

    if(phase == 0 && availableChips > 50){
        maxRaise = 50;
    }
    else if(phase == 1 && availableChips > 100){
        maxRaise = 100;
    }
    else if(phase == 2 && availableChips > 150){
        maxRaise = 150;
    }
    else if(phase == 3 && availableChips > 200){
        maxRaise = 200;
    }
    else{
        maxRaise = availableChips;
    }

    if(raise > maxRaise){
        raise = maxRaise;
    }

    return raise;
}
int chipAdvantage(GAME *g, int botIndex){
    int myChips = g->bots[botIndex].chips;
    int otherChips = g->player.chips;
    for(int i = 0; i < 5; i++){
        if(i != botIndex){
            otherChips += g->bots[i].chips;
        }
    }
    int effectiveActive = g->numberofActive > 0 ? g->numberofActive : 1;
    double chipAvg = otherChips / effectiveActive;
    if(chipAvg > myChips){return 0;}
    else{return 1;}
}
void decisionTree(GAME *g, int botIndex,int phase, double finalScore,double foldThreshold, double callThreshold, double raiseThreshold, double ALLIN_threshold, FILE *logfp){
    int botChips = g->bots[botIndex].chips;
    int min = g->board.minBet;
    int maxR = 300 + (g->board.pot/10) + (g->board.minBet);

    if (phase == 3 && finalScore < callThreshold) {
        // On the river, do not fold; call if possible, otherwise go all-in.
        if (min <= botChips) {
            g->bots[botIndex].bet = min;
            fprintf(logfp, ">BOT CALL - river fallback (no fold on river)\n\n");
        } else {
            g->bots[botIndex].bet = botChips;
            fprintf(logfp, ">BOT ALL-IN - river fallback (no fold on river)\n\n");
        }
        fflush(logfp);
        return;
    }

    if(finalScore < foldThreshold){
        //FOLD
        g->bots[botIndex].folded = 1;
        fprintf(logfp,">BOT FOLD - finalScore < foldThreshold\n\n");
        fflush(logfp);
        return;
    }else if(finalScore < callThreshold){
        if(g->board.minBet > 12 && g->numberofActive > 2){
            //FOLD only if more than 2 players active
            g->bots[botIndex].folded = 1;
            fprintf(logfp,">BOT FOLD - finalScore < callThreshold && g->board.minbet > 12 && active > 2\n\n");
            fflush(logfp);
            return;
        }else{
            //CALL
            g->bots[botIndex].bet = min;
            fprintf(logfp,">BOT CALL - finalScore < callThreshold && !(g->board.minbet > 12)\n\n");
            fflush(logfp);
            return;
        }
    }else if(finalScore < raiseThreshold){
        if(g->bots[botIndex].chips - g->board.minBet < 100){
            //CALL
            g->bots[botIndex].bet = min;
            fprintf(logfp, ">BOT CALL - finalScore < raiseThreshold && chips-bet < 100\n\n");
            fflush(logfp);
            return;
        }else if(g->bots[botIndex].raiseCount <= 3){
            //RAISE
            int raise = calculateRaise(g, botIndex, phase);
            g->bots[botIndex].bet = raise;
            g->board.minBet = raise;
            g->bots[botIndex].raiseCount++;
            fprintf(logfp, ">BOT RAISE - chips-bet > 100\n\n");
            fflush(logfp);
            return;
        }else{
            //CALL
            g->bots[botIndex].bet = min;
            fprintf(logfp, ">BOT CALL - Hit raise limit\n\n");
            fflush(logfp);
            return;
        }
    }else{
        //CALL -until allin works
        g->bots[botIndex].folded = 1;
        fprintf(logfp, ">BOT CALLS - lack of ALLIN HANDLING\n\n");
        fflush(logfp);
        return;
        //ALL-IN  WIP
        
    }
}
//Inclusion of evaluate.c
void permutateFLOP(Hand* hand1, Hand* boardhand,  Hand5 out[1]) {
    out[0].cards[0] = hand1->cards[0];
    out[0].cards[1] = hand1->cards[1];
    out[0].cards[2] = boardhand->cards[0];
    out[0].cards[3] = boardhand->cards[1];
    out[0].cards[4] = boardhand->cards[2];
}
void permutateTurn(Hand* hand1, Hand* boardhand, Hand5 out[6]) {
    Card six[6];

    six[0] = hand1->cards[0];
    six[1] = hand1->cards[1];
    six[2] = boardhand->cards[0];
    six[3] = boardhand->cards[1];
    six[4] = boardhand->cards[2];
    six[5] = boardhand->cards[3];

    int combo = 0;
    for(int a = 0; a < 6; a++)
    for(int b = a+1; b < 6; b++)
    for(int c = b+1; c < 6; c++)
    for(int d = c+1; d < 6; d++)
    for(int e = d+1; e < 6; e++) {
        out[combo].cards[0] = six[a];
        out[combo].cards[1] = six[b];
        out[combo].cards[2] = six[c];
        out[combo].cards[3] = six[d];
        out[combo].cards[4] = six[e];
        combo++;
    }
}
double botCardEval(GAME *g, int botIndex, Hand5 out[], int outNum) {
    double biggestScore = 0;
    for(int i = 0; i < outNum; i++){
        int ComboScore = evaluateHand5(&out[i]);
        double ComboNorm = ComboScore / 10.0;
        if(biggestScore < ComboNorm){
            biggestScore = ComboNorm;
        }
    }
    return biggestScore;
}
void botLogic3(GAME *g, int botIndex, int phase, FILE *logfp){
    if (g->bots[botIndex].folded == 1) {
        return;
    }
    if (g->bots[botIndex].bet >= g->bots[botIndex].chips) {
        return;//Already allin
    }
    double foldT, callT, raiseT, allinT;
    switch(phase){
        case 1: // Flop
            foldT   = 0.0051;      // ≈ preflop level
            callT   = 0.35;
            raiseT  = 0.60;
            break;
        case 2: // Turn
            foldT   = 0.00175;
            callT   = 0.45;
            raiseT  = 0.75;
            break;
        case 3: // River
            foldT   = 0.0001;
            callT   = 0.45;
            raiseT  = 0.75;
            break;
        default: // Preflop
            foldT   = 0.005;      // same as flop
            callT   = 0.2;      // unchanged
            raiseT  = 0.45;      // unchanged
            break;
    }
    double analysisScore = botAnalysis(g, botIndex, phase, logfp);
    double cardScore = 0;
    if(g->boardHand.count == 3){
        Hand5 in1[1];
        permutateFLOP(&g->botHands[botIndex], &g->boardHand, in1);//Permutations created
        cardScore = botCardEval(g, botIndex, in1, 1);
    }else if(g->boardHand.count == 4){
        Hand5 in2[6];
        permutateTurn(&g->botHands[botIndex], &g->boardHand, in2);
        cardScore = botCardEval(g, botIndex, in2, 6);
    }else if(g->boardHand.count == 5){
        Hand5 in3[21];
        permutateCards(&g->botHands[botIndex],&g->boardHand, in3);
        cardScore = botCardEval(g, botIndex, in3, 21);
    }
    if(phase == 3){
        analysisScore = 0.2*analysisScore + 0.8 *cardScore;
    }else{
        analysisScore = 0.5 * analysisScore + 0.5 * cardScore;
    }
    
    // Add situational factors
    // Tightness factor: fewer active players = tighter play
    int activePlayers = g->numberofActive;
    double tightnessFactor = (6 - activePlayers) / 5.0;  // 0 when 6 players, 1 when 1 player
    analysisScore -= 0.05 * tightnessFactor;
    // Add small randomness to avoid predictability
    analysisScore += ((double)rand() / RAND_MAX - 0.5) * 0.1;  // +/- 0.05
    // Clamp to [0,1]
    if(analysisScore > 1.0) analysisScore = 1.0;
    if(analysisScore < 0.0) analysisScore = 0.0;
    
    fprintf(logfp, ">Total Analysis Score:%f\n",analysisScore);
    fflush(logfp);
    
    int chipAdv = chipAdvantage(g, botIndex);
    decisionTree(g, botIndex, phase, analysisScore, foldT,callT,raiseT,allinT, logfp);  
}