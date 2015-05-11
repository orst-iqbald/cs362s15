/* 
	Unit test for the function int isGameOver(struct gameState *state)
	found in dominion.c.

	Include the following lines in your makefile:

	unittest4: unittest4.c dominion.o rngs.o
      	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
	int i, j, k, r, index;
	int failCount = 0;
	int totalCount = 0;
	int numPlayers = 2;
	int seed = 5555;
	int kingCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	FILE* outfile;
	FILE* reportfile;

	outfile = fopen("unittest4.result", "w");
	reportfile = fopen("unittestresult.out", "a");

	fprintf(reportfile, "Testing isGameOver, with all combinations of number of provinces left (0-12), and number of other piles at zer0 (0-17).\n");

	for(i = 0; i < 13; i++)/*Number of Provinces*/{
		for(j = 0; j < 18; j++)/*Number of Piles at zero*/{
			memset(&G, 23, sizeof(struct gameState));
			r = initializeGame(numPlayers, kingCards, seed, &G);

			G.supplyCount[3] = i;

			for(k = 0; k < j; k++){
				index = floor(Random() * treasure_map);
				if(index == 3) k--;
				else if(G.supplyCount[index] == 0) k--;
				else G.supplyCount[index] = 0;
			}

			r = isGameOver(&G);
			totalCount++;

			if(i <= 0){
				if(r == 1) fprintf(outfile, "SUCCESS: Correctly found that Province pile is empty. (%d, %d)\n", i, j);
				else{
					fprintf(outfile, "FAILURE: Did not find that Province pile is empty. (%d, %d)\n", i, j);
					failCount++;
				}
			}
			else if(r == 1){
				fprintf(outfile, "FAILURE: Incorrectly found that Province pile is empty. (%d, %d)\n", i, j);
				failCount++;
			}
			else fprintf(outfile, "SUCCESS: Did not incorrectly find the Province pile is empty. (%d, %d)\n", i, j);

			if(j >= 3 && r > 1){
				if(r == 2) fprintf(outfile, "SUCCESS: Correctly found that 3 or more piles are empty. (%d, %d)\n", i, j);
				else{
					fprintf(outfile, "FAILURE: Did not find that 3 or more piles were empty. (%d, %d)\n", i, j);
					failCount++;
				}
			}
			else if(r == 2){
				fprintf(outfile, "FAILURE: Incorrectly found that 3 or more piles were empty. (%d, %d)\n", i, j);
				failCount++;
			}
			else fprintf(outfile, "SUCCESS: Did not incorrectly find that 3 or more piles were empty. (%d, %d)\n", i, j);

		}
	}

	fprintf(reportfile, "NUMBER OF COMBINATIONS TESTED: %d\n", totalCount);
	fprintf(reportfile, "NUMBER OF FAILED TESTS (2 possible per unique set of inputs): %d\n", failCount);

	fclose(outfile);
	fclose(reportfile);

	return 0;
}