/*
	Testing the newGame() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DRAWCOUNT 30
int main ()
{
    printf ("TESTING newGame() function:\n");
    
	struct gameState* g = newGame();
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	//	if it can be initialized then it works
	int init = initializeGame(numPlayer, k, seed, g);
	assert(init == 0);
	printf("\tnewGame() function passed.\n");
    printf ("FINISHED newGame() function:\n\n");
    return 0;
}