//************************************
//Testing for Village Card
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


	printf ("Testing Village card.\n");  
    // Assign the hand to village and give variables
    G->hand[0][0] =village;
    int hand = 0;
    int actions = 0;


    // When playing a village, discard 1, add 1 card, and lose 1 action
    //start by storing original hand

    hand = G->handCount[0];
    actions = G->numActions;

  	actionVillage(0,0, G);

  	// compare two hands after being played
  	// verify number of actions
    if (G->numActions == actions + 1)
    {
        printf("Village(): passed for actions count\n");
    }
    else
    {
        printf("Village(): failed for actions count\n");
    }


}
	//verify number of cards in hand
	// should be equal since discard and gained new card both = 0
	if(G->handCount[0] == hand)
	{
        printf("Village(): passed for hand count\n");
    }
    else
    {
        printf("Village(): failed for hand count\n");

	}
	return 0; 