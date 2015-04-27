//*************************************
//Testing for Smithy Card
//*************************************

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


	printf ("Testing Smithy card.\n");  
    // Assign the hand to village and give variables
    G->hand[0][0] = smithy;
    int hand = 0;
    int actions = 0;

    // When playing a smithy card, discard 1, add 3 card
    //start by storing original hand

    hand = G->handCount[0];

  	actionSmithy(0,0, G);

  	// compare two hands after being played
}	//verify number of cards in hand
	// gained 3 but discarded one, should = 2 
	if(G->handCount[0] == hand + 2)
	{
        printf("Smithy(): passed for hand count\n");
    }
    else
    {
        printf("Smithy(): failed for hand count\n");

	}
	return 0; 