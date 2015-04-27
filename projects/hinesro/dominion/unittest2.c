/********************************
*      Test for endTurn().      *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "dominion.h"
#include "interface.h"

int main() {
    srand(time(NULL));
    struct gameState state;
    int i,j, p, idx, coinSum, count, cards[26];

    for(i = 0; i < 1; i++) {
        coinSum = 0;
        count = (rand() % MAX_HAND) + 1;
        state.numPlayers = 4;
        p = 2;
        state.whoseTurn = p;
        state.deckCount[p] = 80;
        state.handCount[p] = 10;
        state.outpostPlayed = 0;
        state.phase = 0;
        state.numActions = 2;
        state.coins = 5;
        state.numBuys = 1;
        state.playedCardCount = 18;

        for(j = 0; j < state.deckCount[p]; j++) {
            idx = 25;
            state.deck[p][j] = idx;
            cards[idx]++;
        }
        for(j = 0; j < state.handCount[p]; j++) {
            idx = 25;
            state.hand[p][j] = idx;
            cards[idx]++;
        }
        endTurn(&state);  
        printf("%d players.\n", state.numPlayers);
        printf("%d cards.\n", state.deckCount[p]);
        printf("%d is current player.\n",p);
        printf("%d is card index.\n", idx);
        printf("%d is the hand count.\n", state.handCount[p]);
    }

    return 0;
}