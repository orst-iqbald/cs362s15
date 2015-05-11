/*
    Testing whoseTurn() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {
    int seed = 1000;
    int numPlayer = 4;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    struct gameState g;
    initializeGame(numPlayer, k, seed, &g);
    
    printf ("TESTING whoseTurn() function:\n");
    int p, turn;
    for(p = 0; p < numPlayer; p++){
    	
	    turn = whoseTurn(&g);
	    assert(turn==p);
    	printf("\tPassed - whoseTurn() returned correct value. Expected %d, Returned %d.\n",p,turn);
	    
	    g.whoseTurn++;
	}
    printf ("FINISHED whoseTurn() function:\n\n");
  return 0;
}