/* -----------------------------------------------------------------------
	Unit test for the function: 
	int updateCoins(int player, struct gameState *state, int bonus);
	
	Include the following lines in your makefile:
	
	Compile instruction: add the lines below to the makefile
	unittest4: unittest4.c dominion.o
		gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------- 
 */

#include <stdio.h>
#include "dominion.h"

/* To suppress noise set this to 0 */
#define NOISY_TEST 1

/** test the function updateCoins */
void unittest4() {
	struct gameState* g = NULL;
	int i, player, bonus;
	
	g = newGame();
	player = 1;  /* this should be less than MAX_PLAYERS = 4 */
	g->handCount[player] = 5;
	g->hand[player][0] = copper;  /* 1 Coin */
	g->hand[player][1] = silver;  /* 2 Coins */
	g->hand[player][2] = gold;    /* 3 Coins */
	g->hand[player][3] = copper;  /* 1 Coin */
	g->hand[player][4] = silver;  /* 2 Coins */
	bonus = 5;
	
	updateCoins(player, g, bonus);

	if (g->coins != 14) {
		printf("The function updateCoins failed.\n");
	} else {
		printf("The function updateCoins successfully Completed. \n");
	}	
	
	free(g);
	return;
}

int main() {
	if (NOISY_TEST) printf("*** %s Start \n", __FILE__);
	printf("=== Testing %s ===\n", __FILE__);
	unittest4();
	if (NOISY_TEST) printf("*** %s Complete \n", __FILE__);
	
	return 0;
}