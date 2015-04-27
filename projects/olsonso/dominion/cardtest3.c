//*************************************
//Testing for Adventurer Card
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


	printf ("Testing Adventurer card.\n");  
    //copy values
    G->hand[0][0] = adventurer;
    int hand = 0;
    int treasures = 0;
    int i = 0;
    int test = 0;
    int actions = 0;

    //start by storing original hand count, actions, and treasures

    hand = G->handCount[0];
    actions = G->numActions;
    for (i = 0; i < G->handCount[0]; i++){
        if (G->hand[0][i] == gold || G->hand[0][i] == silver || G->hand[0][i] == copper){
            treasures++;
        }
    }

    //start testing card functions
  	actionAdventurer(0,0, G);

  	// compare two hands after being played
  	// verify number of treasures by first storing in test variable 
     for (i = 0; i < G->handCount[0]; i++){
        if (G->hand[0][i] == gold || G->hand[0][i] == silver || G->hand[0][i] == copper){
            test++;
        }
    }

    // check treasures!
   if (test == treasures + 2)
   {
        printf("Adventurer(): passed for treasure count\n");
    }
    else
    {
        printf("Adventurer(): failed for treausure count\n");

   }

	//verify number of cards in hand
	// should be +1 
	if(G->handCount[0] == hand +1 )
	{
        printf("Adventurer(): passed for hand count\n");
    }
    else
    {
        printf("Adventurer(): failed for hand count\n");

	}
	return 0; 
}