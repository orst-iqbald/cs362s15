/* 
	Unit test for the function int buyCard(int supplyPos, struct gameState *state)
	found in dominion.c.

	Include the following lines in your makefile:

	unittest2: unittest2.c dominion.o rngs.o
      	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
	int i, j, k, l, r;
	int failCount = 0;
	int totalCount = 0;
	int numPlayers = 2;
	int seed = 5555;
	int kingCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	FILE* outfile;
	FILE* reportfile;

	outfile = fopen("unittest2.result", "w");
	reportfile = fopen("unittestresult.out", "a");

	fprintf(reportfile, "Testing buyCard() with all combinations of card buying (0-16), money on hand (0-7), supply left (-1-10), and buys left (0-1).\n");

	for(i = 0; i < 17; i++)/*What Buying*/{
		for(j = 0; j < 8; j++)/*How Much Money*/{
			for(k = -1; k < 11; k++)/*How Many Supply Left*/{
				for(l = 0; l < 2; l++)/*How Many Buys Left*/{
					memset(&G, 23, sizeof(struct gameState));
					r = initializeGame(numPlayers, kingCards, seed, &G);
					G.coins = j;
					G.supplyCount[i] = k;
					G.numBuys = l;

					fprintf(outfile, "\nTesting buyCard() buying %d, with %d coins, with %d of the chosen item left, and %d buys left.\n", i, j, k, l);

					r = buyCard(i, &G);
					totalCount++;

					if(l <= 0){
						if(r == -1) fprintf(outfile, "SUCCESS: Correctly detected not enough buys. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Did not detect not enough buys. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}
					}
					else if(r == -1){
						fprintf(outfile, "FAILURE: Incorrectly detected not enough buys. (%d, %d, %d, %d)\n", i, j, k, l);
						failCount++;
					}
					else fprintf(outfile, "SUCCESS: Did not incorrectly detect not enough buys. (%d, %d, %d, %d)\n", i, j, k, l);

					if(k < 1 && r < -1){
						if(r == -2) fprintf(outfile, "SUCCESS: Correctly detected not enough supply. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Did not detect not enough supply. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}
					}
					else if(r == -2){
						fprintf(outfile, "FAILURE: Incorrectly detected not enough supply. (%d, %d, %d, %d)\n", i, j, k, l);
						failCount++;
					}
					else fprintf(outfile, "SUCCESS: Did not incorrectly detect not enough supply. (%d, %d, %d, %d)\n", i, j, k, l);

					if(j < getCost(i) && r < -2){
						if(r == -3) fprintf(outfile, "SUCCESS: Correctly detected not enough money. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Did not detect not enough money. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}
					}
					else if(r == -3){
						fprintf(outfile, "FAILURE: Incorrectly detected not enough money. (%d, %d, %d, %d)\n", i, j, k, l);
						failCount++;
					}
					else fprintf(outfile, "SUCCESS: Did not incorrectly detect not enough money. (%d, %d, %d, %d)\n", i, j, k, l);

					if(r >= 0){
						if(G.discard[0][G.discardCount[0] - 1] == i) fprintf(outfile, "SUCCESS: Correct card on top of the discard pile. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Incorrect card on top of the discard pile. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}

						if(G.coins == (j - getCost(i))) fprintf(outfile, "SUCCESS: Correct reduction in coins available. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Incorrect reduction in coins available. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}

						if(G.numBuys == (l - 1)) fprintf(outfile, "SUCCESS: Correct reduction in number of buys available. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Incorrect reduction in coins available. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}
					}
				}
			}
		}
	}

	fprintf(reportfile, "NUMBER OF COMBINATIONS TESTED: %d\n", totalCount);
	fprintf(reportfile, "NUMBER OF FAILED TESTS (1 - 3 possible per unique set of inputs): %d\n", failCount);

	fclose(outfile);
	fclose(reportfile);

	return 0;
}