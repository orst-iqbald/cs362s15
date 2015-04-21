/* -----------------------------------------------------------------------
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// return the total for the hand
int getTotal(int hand[MAX_HAND], int size){
	int total = 0;
	int i;

	for (i = 0; i < size; i++){

		if (hand[i] == copper){
	  		total += 1;
		}else if (hand[i] == silver){
	  		total += 2;
		}else if (hand[i] == gold){
	  		total += 3;
		}
  	}
  return total;
}

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    struct gameState G;
    int maxHandCount = 5;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int rand_hand[MAX_HAND];
    int treasures[3] = {copper, silver, gold};

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING updateCoins():\n");
    for (p = 0; p < numPlayer; p++){
        for (handCount = 1; handCount <= maxHandCount; handCount++){
            for (bonus = 0; bonus <= maxBonus; bonus++){
            	int total;
            	// generate a random hand to check
            	for(i = 0; i < MAX_HAND; i++){
            		int n = rand() % 3;
            		rand_hand[i] = treasures[n];
            	}

                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
                memset(&G, '-', sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand

                // get the total that we should see.  This is kind pointless since it just
                // re-creates the updateCoins function but whatev
                total = getTotal(rand_hand, handCount);

                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                r = updateCoins(p, &G, bonus);
                assert(r == 0);

                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
                assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                r = updateCoins(p, &G, bonus);
                assert(r == 0);

                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
                assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold
                r = updateCoins(p, &G, bonus);
                assert(r == 0);

                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
                assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], rand_hand, sizeof(int) * handCount); // test a random hand
                r = updateCoins(p, &G, bonus);
                assert(r == 0);

                printf("G.coins = %d, expected = %d\n", G.coins, total+bonus);
       	        assert(G.coins == total + bonus); // check if the number of coins is correct
            }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
