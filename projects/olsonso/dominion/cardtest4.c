//*************************************
//Testing for GreatHall Card
//************************************

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {

    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    // start building game state
    struct gameState *G = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, G);

    //start Testing
    printf("Testing GreatHall card\n");
    G->hand[0][0] =great_hall;
    int hand = 0;
    int actions =0;

    hand = G->handCount[0];
    actions = G->numActions;

    actionGreat_hall();

    // check to see how many cards are in hand
    if (G->handCount[0] == hand){
    	printf("GreatHall passed tests with hand count\n");
    }
    else{
    	printf("GreatHall Failed test with hand count\n");
    }

    //check to see how many actions 
    if(G->numActions == actions +1 ){
    	printf("GreatHall passed test with actions\n");
    }
    else {
    	printf("GreatHall failed tests with actions \n");
    }

    return 0;
}