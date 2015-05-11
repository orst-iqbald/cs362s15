/* -----------------------------------------------------------------------
	Unit test for the function: 
	int isGameOver(struct gameState *state);
	
	Include the following lines in your makefile:
	
	Compile instruction: add the lines below to the makefile
	unittest3: unittest3.c dominion.o
		gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------- 
 */

#include <stdio.h>
#include "dominion.h"

/* To suppress noise set this to 0 */
#define NOISY_TEST 1

/** test the function isGameOver */
void unittest3() {
	struct gameState* g = NULL;
	int i;
	
	g = newGame();
	g->supplyCount[province] = 0;
	if (isGameOver(g) != 1) {
		printf("The function isGameOver failed for 0 province cards.\n");
	} else {
		printf("The function isGameOver successfully Completed 0 province cards. \n");
	}	
	
	for (i = 0; i < 25; i ++) {
		g->supplyCount[i] = 1;
	}
	g->supplyCount[curse] = 0;
	g->supplyCount[estate] = 0;
	g->supplyCount[duchy] = 0;
	if (isGameOver(g) != 1) {
		printf("The function isGameOver failed for at least three supply piles are at 0. \n");
	} else {
		printf("The function isGameOver successfully Completed for at least three supply piles are at 0. \n");
	}
	free(g);
	return;
}

int main() {
	if (NOISY_TEST) printf("*** %s Start \n", __FILE__);
	printf("=== Testing %s ===\n", __FILE__);
	unittest3();
	if (NOISY_TEST) printf("*** %s Complete \n", __FILE__);
	
	return 0;
}