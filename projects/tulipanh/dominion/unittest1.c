/* 
	Unit test for the function int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
	found in dominion.c.

	Include the following lines in your makefile:

	unittest1: unittest1.c dominion.o rngs.o
      	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rngs.h"

int main(){
	int i, j, k, l, r, effectOut;
	int coinBonus = 0;
	int failCount = 0;
	int totalCount = 0;
	int numPlayers = 2;
	int seed = 5555;
	int kingCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	FILE* outfile;
	FILE* reportfile;

	outfile = fopen("unittest1.result", "w");
	reportfile = fopen("unittestresult.out", "a");

	fprintf(reportfile, "Testing playCard() with all combinations of phase (0-1), number of actions (0-1), hand position (0-5), and card (0-27).\n");

	for(i = 0; i < 2; i++)/*Phase*/{
		for(j = 0; j < 2; j++)/*Num Actions*/{
			for(k = 0; k < 5; k++)/*Hand Pos*/{
				for(l = 0; l < 27; l++)/*Card*/{
					memset(&G, 23, sizeof(struct gameState));
					r = initializeGame(numPlayers, kingCards, seed, &G);
					G.phase = i;
					G.numActions = j;
					G.hand[0][k] = l;
					effectOut = cardEffect(l, -1, -1, -1, &G, k, &coinBonus);

					fprintf(outfile, "\nTesting playCard() with phase %d, number of actions %d, handPos %d, and card %d.\n", i, j, k, l);

					memset(&G, 23, sizeof(struct gameState));
					r = initializeGame(numPlayers, kingCards, seed, &G);
					G.phase = i;
					G.numActions = j;
					G.hand[0][k] = l;
					G.whoseTurn = 0;
					r = playCard(k, -1, -1, -1, &G);
					totalCount++;

					if(i > 0){
						if(r == -1) fprintf(outfile, "SUCCESS: Correctly detected wrong phase. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Did not detect wrong phase. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}
					}
					else if(r == -1){
						fprintf(outfile, "FAILURE: Incorrectly detected wrong phase. (%d, %d, %d, %d)\n", i, j, k, l);
						failCount++;
					}
					else fprintf(outfile, "SUCCESS: Did not incorrectly detect wrong phase. (%d, %d, %d, %d)\n", i, j, k, l);

					if(j == 0 && r < -1){
						if(r == -2) fprintf(outfile, "SUCCESS: Correctly detected no actions left. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Did not detect no actions left. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}
					}
					else if(r == -2){
						fprintf(outfile, "FAILURE: Incorrectly detected no actions left. (%d, %d, %d, %d)\n", i, j, k, l);
						failCount++;
					}
					else fprintf(outfile, "SUCCESS: Did not incorrectly detect no actions left. (%d, %d, %d, %d)\n", i, j, k, l);

					if((l < adventurer || l > treasure_map) && r < -2){
						if(r == -3) fprintf(outfile, "SUCCESS: Correctly detected non-action card. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Did not detect non-action card. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}
					}
					else if(r == -3){
						fprintf(outfile, "FAILURE: Incorrectly detected non-action card. (%d, %d, %d, %d)\n", i, j, k, l);
						failCount++;
					}
					else fprintf(outfile, "SUCCESS: Did not incorrectly detect non-action card. (%d, %d, %d, %d)\n", i, j, k, l);

					if(effectOut < 0 && r < -3){
						if(r == -4) fprintf(outfile, "SUCCESS: Correctly detected bad cardEffect input. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Did not detect bad cardEffect input. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}
					}
					else if(r == -4){
						fprintf(outfile, "FAILURE: In correctly detected bad cardEffect input. (%d, %d, %d, %d)\n", i, j, k, l);
						failCount++;
					}
					else fprintf(outfile, "SUCCESS: Did not incorrectly detect bad cardEffect input. (%d, %d, %d, %d)\n", i, j, k, l);

					if(r >= 0){
						if((j - G.numActions) ==  1) fprintf(outfile, "SUCCESS: Correctly decremented numActions. (%d, %d, %d, %d)\n", i, j, k, l);
						else{
							fprintf(outfile, "FAILURE: Did not decrement numActions. (%d, %d, %d, %d)\n", i, j, k, l);
							failCount++;
						}
					}
				}
			}
		}
	}

	fprintf(reportfile, "NUMBER OF COMBINATIONS TESTED: %d\n", totalCount);
	fprintf(reportfile, "NUMBER OF FAILED TESTS (1 or 2 possible per unique set of inputs): %d\n", failCount);

	fclose(outfile);
	fclose(reportfile);

	return 0;
}