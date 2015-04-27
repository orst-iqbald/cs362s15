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
	int seed = 1000;
    int numPlayer = 2;
	struct gameState *G = malloc(sizeof(struct gameState));
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    initializeGame(numPlayer, k, seed, G);
printf ("Now testing the isgameover function.\n");   
 
//this should fail if the code is functioning correctly since it was just initiated
    if (isGameOver(G) != 0)
    {
        printf("isGameOver() fails game was just initiated \n");
    }
    else
    {
        printf("isGameOver() works correctly\n");
    }
//now gonna chekc the province stack 
    G->supplyCount[province] = 1;

    if (isGameOver(G) >= 1)
    {
        printf("isGameOver() doesn't fail when supply of provinces is 0\n");
    }
    else
    {
        printf("isGameOver() passed supply of provinces is 0\n");
    }

//since there ware two players we make the supply counts empty
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

    return 0;
}