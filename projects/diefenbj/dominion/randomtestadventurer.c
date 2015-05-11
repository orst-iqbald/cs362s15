#ifndef H_RTADV_
#define H_RTADV_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "dominion.h"

int adv_test(){
    srand(time(NULL));
    printf("Testing Adventurer (h_adventurer())\n");

    int i, n, r, p, deckCount, discardCount, handCount;
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

    //the code handling the adventurer card is assuming a VALID gameState -
    //that's why i won't be randomizing bits.
    //also, it assumes at least 2 treasures are in deck/discard/hand
 
    //randomize based on deck,discard,hand(s) size&composition
    //min size is 0, max size is 500, min card is curse, max card is t_map
    for(i = 0; i < 2000; i++){
        printf("TEST #%i",runs);
        runs++;
        
        //deck + discard 2 <= r <= 500
        r = rand() % 499 + 2;
        //1 <= deckcount <= r - 1
        deckCount = (rand() % (r - 1)) + 1;
        //1 <= discardcount <= r - deckcount
        //check r to make sure we dont mod by 0 -> core dump
        discardCount = (rand() % (r - deckCount - (r - deckCount == 1 ? 0 : 1))) + 1;

        handCount = rand() % 499;
        printf("\tDECK #: %i\tDISCARD #: %i\tHAND #: %i\n",
                deckCount,discardCount,handCount);

        state->deckCount[p] = deckCount;
        state->discardCount[p] = discardCount;
        state->handCount[p] = handCount;

        int t_pos[2] = {-1,-1};
        int t_count = 0;

        for(n = 0; n < deckCount; n++){
            r = rand() % treasure_map + 1;
            state->deck[p][n] = r;
            if(r == copper || r == silver || r == gold){
                t_count++;
                if(t_pos[0] == -1){
                    t_pos[0] = n;
                } else if(t_pos[1] == -1){
                    t_pos[1] = n;
                }
            }
        }
            
        for(n = 0; n < discardCount; n++){
            r = rand() % treasure_map + 1;
            state->discard[p][n] = r;
            if(r == copper || r == silver || r == gold){
                t_count++;
                if(t_pos[0] == -1){
                    t_pos[0] = n + deckCount;
                } else if(t_pos[1] == -1){
                    t_pos[1] = n + deckCount;
                }
            }
        }

        //in the unlikely case we have <2 treasures, just put two in.
        if(t_count < 2){
            state->deck[p][rand() % deckCount] = copper;
            t_count++;
            state->discard[p][rand() % discardCount] = silver;
            t_count++;
        }

        int res = h_adventurer(p, state);
        int new_1 = state->hand[p][state->handCount[p] - 1];
        int new_2 = state->hand[p][state->handCount[p] - 2];
        
        if(res != 0){
            printf("FAILED : return status != 0\n");
            fails++;
        } else if(state->handCount[p] != handCount + 2){
            printf("FAILED : did not draw two cards\n");
            fails++;
        } else if(new_2 < copper || new_2 > gold){
            printf("FAILED : the second-to-last card drawn was not a treasure.\n");
            fails++;
        } else if(new_1 < copper || new_1 > gold){
            printf("FAILED : the last card drawn was not a treasure.\n");
            fails++;
        } else {
            passes++;
        }
    }

    printf("RANDOM TESTS: %i\tPASSES: %i\tFAILS: %i\n",runs,passes,fails);
    return 0;
}

int main(){
    return adv_test();
}

#endif
