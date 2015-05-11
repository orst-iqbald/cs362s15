#ifndef H_RTC_
#define H_RTC_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "dominion.h"

int card_test(){
    srand(time(NULL));
    printf("Testing Embargo (h_embargo())\n");

    int i, n, r, p, 
        discardCount, handCount, coinCount, 
        choice, handPos;
    int runs = 0,
        passes = 0,
        fails = 0;

    //cards go from curse (0) to treasure_map (26?)
    //treasures are copper,silver,gold
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};

    p = 1;

    struct gameState *state = newGame();
    initializeGame(2,k,p,state);
    
    //the code handling the embargo card is assuming a VALID gameState -
    //that's why i won't be randomizing bits.
    //also, it assumes a valid choice1
 
    //randomize based on discard,hand(s) size&composition,
    //coin count, choice, handPos, supplyCount foreach card
    //min size is 0, max size is 500, min card is curse, max card is t_map
    //coin count can be anything
    //pos is in range of hand size
    for(i = 0; i < 2000; i++){
        printf("TEST #%i",runs);
        runs++;
        
        discardCount = rand() % 500;
        handCount = (rand() % 499) + 1;
        handPos = rand() % handCount;
        coinCount = rand() % 500;
        choice = rand() % (treasure_map + 1);
        int choiceEmbargoCount = rand() % 10;

        printf("\tDISCARD #: %i\tHAND #: %i\tPOS #: %i\tCOINS: %i\n",
                discardCount,handCount, handPos,coinCount);

        state->discardCount[p] = discardCount;
        state->handCount[p] = handCount;
        state->coins = coinCount;

        //setup supplycount & embargotokens
        for(n = 0; n < treasure_map + 1; n++){
            state->supplyCount[n] = rand() % 2 - 1;
            state->embargoTokens[n] = rand() % 10;
        }
        state->embargoTokens[choice] = choiceEmbargoCount;

        //setup hand
        for(n = 0; n < handCount; n++){
            r = rand() % treasure_map + 1;
            state->hand[p][n] = r;
        }

        //mark embargo card
        state->hand[p][handPos] = embargo;


        int res = h_embargo(handPos,p,choice,state);
        
        if(res != 0 && state->supplyCount[choice] != -1){
            printf("FAILED : return status != 0 when choice is in supply\n");
            fails++;
        } else if(res == 0 && state->coins != coinCount + 2){
            printf("FAILED : did not add two coins\n");
            fails++;
        } else if(res == 0 && state->embargoTokens[choice] != choiceEmbargoCount + 1){
            printf("FAILED : did not add 1 to choice's embargo count\n");
            fails++;
        } else {
            passes++;
        }
    }

    printf("RANDOM TESTS: %i\tPASSES: %i\tFAILS: %i\n",runs,passes,fails);
    return 0;
}

int main(){
    return card_test();
}

#endif
