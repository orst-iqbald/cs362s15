// Random test for card Adventurer


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
    int numPlayer = 2;
    int maxBonus = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int player = 0;
	int preCount;
	int postCount;
	int expectedCount;
	
	int success = 0;
	int failures = 0;
	
	srand(time(NULL));
	
	printf("\n\nRandom Tester: ADVENTURER\n");
	for(n = 0; n < NUM_TRIALS; n++)
	{
		int numPlayer = 2;
		errors = 0;
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &G);
		
		int currentTurn = rand()%2;
		G.whoseTurn = currentTurn;
		assert(whoseTurn(&G) == currentTurn);
		
		int cardsInHand = 5;
		G.handCount[currentTurn] = cardsInHand;
		
		assert(numHandCards(&G) == cardsInHand);
		
		for(i = 0; i < cardsInHand; i++)
		{
			G.hand[currentTurn][i] = estate;
		}
		
		int handPosition = rand() % cardsInHand;
		G.hand[currentTurn][handPosition] = adventurer;
		
		
		// PREPARING DECK
		G.deckCount[currentTurn] = 25;
		int counter = 0;
		for(i = 0; i < 25; i++)
		{
			if(counter < 2)
			{
				int triggerInt = rand()%4;
				if(triggerInt == 0)
				{
					G.deck[currentTurn][i] = copper;
					counter++;
				}
				else if(triggerInt == 1)
				{
					G.deck[currentTurn][i] = silver;
					counter++;
				}
				else if(triggerInt == 2)
				{
					G.deck[currentTurn][i] = gold;
					counter++;
				}
				else
					G.deck[currentTurn][i] = estate;
			}
			else
				G.deck[currentTurn][i] = estate;
		}
		
		// CHECKING STATE OF DECK
		int numEstates = 0;
		int numCoppers = 0;
		int numSilvers = 0;
		int numGolds = 0;
		for(i = 0; i < G.deckCount[currentTurn]; i ++)
		{
			if(G.deck[currentTurn][i] == estate)
				numEstates++;
			else if(G.deck[currentTurn][i] == copper)
				numCoppers++;
			else if(G.deck[currentTurn][i] == silver)
				numSilvers++;
			else if(G.deck[currentTurn][i] == gold)
				numGolds++;
		}
		
		G.deck[currentTurn][23] = copper;
		G.deck[currentTurn][24] = copper;
		
		
		int deckValue;
		int handValue;
		deckValue = ((numCoppers) + (numSilvers * 2) + (numGolds * 3));
		preCount = cardsInHand;
		playAdventurer(&G, currentTurn);
		//assert(whoseTurn(&G) == currentTurn);
		postCount = G.handCount[currentTurn];
				
		expectedCount = preCount + 2;
		
		updateCoins(currentTurn, &G, 0);
		handValue = G.coins;
		
		if(deckValue == handValue)
		{
			success++;
		}
		else
		{
			failures++;;
		}
	}
	
	printf("Matched value: %d\n", success);
	printf("Differing value: %d\n", failures);

	return 0;
}