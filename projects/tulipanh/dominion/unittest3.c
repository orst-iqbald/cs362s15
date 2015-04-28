/* 
	Unit test for the function int fullDeckCount(int player, int card, struct gameState *state)
	found in dominion.c.

	Include the following lines in your makefile:

	unittest3: unittest3.c dominion.o rngs.o
      	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int main(){
	int i, j, k, l, m, n, r, totalCards, index, count, card;
	int failCount = 0;
	int totalCount = 0;
	int numPlayers = 2;
	int seed = 5555;
	int kingCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	FILE* outfile;
	FILE* reportfile;

	outfile = fopen("unittest3.result", "w");
	reportfile = fopen("unittestresult.out", "a");

	fprintf(reportfile, "Testing fullDeckCount() with all combinations of number in deck (0-9), number in hand (0-9), number in discard (0-9), and player (0-1).\n");
	
	for(i = 0; i < 10; i++)/*Number in Deck*/{
		for(j = 0; j < 10; j++)/*Number in Hand*/{
			for(k = 0; k < 10; k++)/*Number in Discard*/{
				for(l = 0; l < 2; l++)/*Which Player*/{
					for(n = 0; n < 27; n++){
					memset(&G, 23, sizeof(struct gameState));
					r = initializeGame(numPlayers, kingCards, seed, &G);
					//int card = floor(Random() * 27);
					card = n;
					G.handCount[l] = 20;
					G.deckCount[l] = 20;
					G.discardCount[l] = 20;

					for(m = 0; m < i; m++){
						index = floor(Random() * G.deckCount[l]);
						if(G.deck[l][index] == card) m--;
						else G.deck[l][index] = card;
					}

					for(m = 0; m < j; m++){
						index = floor(Random() * G.handCount[l]);
						if(G.hand[l][index] == card) m--;
						else G.hand[l][index] = card;
					}

					for(m = 0; m < k; m++){
						index = floor(Random() * G.discardCount[l]);
						if(G.discard[l][index] == card) m--;
						else G.discard[l][index] = card;
					}

					totalCards = i + j + k;

					count = fullDeckCount(l, card, &G);
					totalCount++;

					if(count == totalCards) fprintf(outfile, "SUCCESS: Total number of the card %d correctly counted. (%d, %d, %d, %d)\n", card, i, j, k, l);
					else{
						fprintf(outfile, "FAILURE: Total number of the card %d, incorrectly counted. (%d, %d, %d, %d)\n", card, i, j, k, l);
						failCount++;
					}
				}
				}
			}
		}
	}

	fprintf(reportfile, "NUMBER OF COMBINATIONS TESTED: %d\n", totalCount);
	fprintf(reportfile, "NUMBER OF FAILED TESTS (1 possible per unique set of inputs): %d\n", failCount);

	fclose(outfile);
	fclose(reportfile);

	return 0;
}