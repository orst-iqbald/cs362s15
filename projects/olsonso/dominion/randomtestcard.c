/* -----------------------------------------------------------------------
 * Random Test for the Smithy card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "rngs.h"

#define MAX_TESTS 1000

int checkSmithyCard(int i, int p, int handPos, struct gameState *post) {
  int initialHandCount;
  int afterPlayCount;
  initialHandCount = post->handCount[p];
  zzzsmithycardplay (i, p, handPos, post);
  afterPlayCount = post->handCount[p];
  if ((initialHandCount + 3) != afterPlayCount)
  {
        printf("Number of cards drawn test FAILED\n");
        printf("Initial count: %d\n", initialHandCount);
        printf("After test count: %d\n", afterPlayCount);
  }

}

int main () {
	srand(time(NULL)); 

	int i, n, r, p, deckCount, discardCount, handCount;
	int num_tests; 
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	struct gameState G;
	printf ("Testing smithyCard.\n");
  
	for (num_tests = 0; num_tests <= MAX_TESTS; num_tests++)
	{	
		p = (rand()%2) + 1;
		deckCount = (rand()%5) + 1;
		handCount = (rand()%5) + 1;

		memset(&G, 23, sizeof(struct gameState));
		r = initializeGame(2, k, 1, &G);
		G.deckCount[p] = deckCount;
		memset(G.deck[p], 0, sizeof(int) * deckCount);
		G.discardCount[p] = discardCount;
		memset(G.discard[p], 0, sizeof(int) * discardCount);
		G.handCount[p] = handCount;
		memset(G.hand[p], 0, sizeof(int) * handCount);
		checkSmithyCard(i, p, 0, &G);	
	}

  return 0;
}