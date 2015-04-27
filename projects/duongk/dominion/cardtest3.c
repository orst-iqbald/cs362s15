#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
    int newCards = 3;
    int discardedCard = 1;
    int shuffledCards = 0;
    int cardDrawn = 0;
    int currentPlayer=0;
    int i = 0;
    int handpos = 0;
    int seed = 1000;
    int numPlayers = MAX_PLAYERS;
    int thisPlayer = 0;
    struct gameState* G;
    struct gameState* testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};
    
    // set game state and player cards
    G = newGame();
    initializeGame(numPlayers, k, seed, G);
    
    // copy the game state to a test case
    testG = newGame();
    memcpy(testG, G, sizeof(struct gameState));

    printf("Testing Card: %s \n", TESTCARD);

    village_card(thisPlayer, testG, handPos);

        printf("Testing hand count\n");
    if(testG->handCount[thisPlayer] == G->handCount[thisPlayer] + 1){
        printf("HAND COUNT PASSES\n");
    }else{
        printf("HAND COUNT FAILS\n");
    }

    printf("Current hand count = %d, expected = %d\n", testG->handCount[thisPlayer], G->handCount[thisPlayer] + 1);

    printf("%s card finished with tests.\n", TESTCARD);
    
    return 0;