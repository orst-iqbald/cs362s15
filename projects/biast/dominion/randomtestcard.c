// Random test for card Smithy


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NUM_TRIALS 1000

int main() {
	int errors = 0;
    int i, j, m, n;
    int seed = 50;
    int maxBonus = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int currentTurn;
	int cardsInHand;
	int handPosition;
	
	int preCount;
	int postCount;
	int expectedCount;
	
	int success = 0;
	int failures = 0;
	
	srand(time(NULL));
	
	printf("\n\nRandom Tester: SMITHY\n");
	for(n = 0; n < NUM_TRIALS; n++)
	{
		int numPlayer = 2;
		errors = 0;
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &G);
		
		currentTurn = rand()%2;
		G.whoseTurn = currentTurn;
		assert(whoseTurn(&G) == currentTurn);
		
		cardsInHand = (rand() % 100) + 1;
		G.handCount[currentTurn] = cardsInHand;
		
		assert(numHandCards(&G) == cardsInHand);
		
		for(i = 0; i < cardsInHand; i++)
		{
			G.hand[currentTurn][i] = 4;
		}
		
		handPosition = rand() % cardsInHand;
		G.hand[currentTurn][handPosition] = smithy;
				
		preCount = cardsInHand;
		
		playSmithy(&G, currentTurn, handPosition);
		assert(whoseTurn(&G) == currentTurn);
		postCount = G.handCount[currentTurn];
				
		expectedCount = preCount + 2;
				
		if(expectedCount == postCount)
			success++;
		else
			failures++;
	}
	
	printf("SUCCESSES: %d\n", success);
	printf("FAILURES: %d\n", failures);
	
	
	return 0;
}