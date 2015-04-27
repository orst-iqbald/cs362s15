//*************************************
//Testing to check isgameover function in game
//*************************************


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main(){

	struct gameState *G = malloc(sizeof(struct gameState));
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
printf ("Testing isgameover function.\n");   
	 initializeGame(numPlayer, k, seed, G);

// Initalizing game should pass this is correctly started game. 

    if (isGameOver(G) != 0)
    {
        printf("isGameOver() fails immediately after game initializing new game \n");
    }
    else
    {
        printf("isGameOver() passed after initializing \n");
    }
//check supply piles, three empty piles should enforece game over. 

    G->supplyCount[0] = 0;
    G->supplyCount[1] = 0;
    G->supplyCount[2] = 0;
    
    if (isGameOver(G) != 1)
    {
        printf("isGameOver() doesn't fail when supply of three piles are empty\n");
    }
    else
    {
        printf("isGameOver() passed when three supply piles = 0 \n");
    }


// check province count

 G->supplyCount[province] = 0;
    if (isGameOver(G) != 1)
    {
        printf("isGameOver() doesn't fail when supply of provinces is 0\n");
    }
    else
    {
        printf("isGameOver() passed supply of provinces is 0\n");
    }
    G->supplyCount[province] = 1;

    return 0;
}