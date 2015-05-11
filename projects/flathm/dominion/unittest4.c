/*
Michael Flath
CS362
unittest3.c
This file will test isGameOver()

test2: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


int main()
{	

	int i, j, x, r, m, rnum, end;
	int over;
	int players = 2;
    int seed = rand() % 1000;
    struct gameState G;
	
	 int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; 
   
    //Initialize game 
    memset(&G, 0, sizeof(struct gameState)); // zero game state
	r = initializeGame(players, k, seed, &G); // initializeGame returns 0 on success
	assert(r == 0);
	
	printf("Testing: isGameOver() in process...!\n");
	//test when game ends province cards == 0
	for(i = 100; i >= 0; i--) {
		G.supplyCount[province] = i;
		over = isGameOver(&G);
		if(i == 0 && over != 1) {
			printf("Fail: Game did not end with 0 province cards!\n");
		}
	}
	
	//Fill supplyCount with 10 cards each
	for(x = 0; x < 27; x++) {
		G.supplyCount[x] = 10;
	}
	
	//test when 3 piles are empty or == 0
	//Test randomly decremented supplyCount 
	end = 0;
	for(j = 0; j <  1000; j++) {
		rnum = rand() % 27;
		G.supplyCount[rnum] -= 1;
		over = isGameOver(&G);
		for(m = 0; m < 27; m++) {
			if(G.supplyCount[m] == 0) {
				end++;
			}
			if(end >= 3 && over != 1) {
				printf("Fail: 3 supplyCount cards are 0 and the game did not end!\n");
			}
				
		}
	}
	
	printf("Testing Completed\n");
	
	return 0;
}