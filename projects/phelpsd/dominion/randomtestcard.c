/************************************************************
 *File: randomtestcard.c
 *Author: Dustin Phelps
 *Date: 5/10/2015
 *Desc: File containing code for random testing of 
 *smithy dominion card.
 *
 *randomtestcard.out: dominion.o randomtestcard.c
 *	gcc -o randomtestcard randomtestcard.c -g dominion.o rngs.o $(CFLAGS)
 ************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"

//set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
//sets the number of random test runs
#define NUM_TESTS 1000

//function prototyping
int smithRand();

/************************************************************
main function
params: none
return: returns 0 on success
pre-cond: none
*************************************************************/
int main() {
	return smithRand();	
}

/************************************************************
Function that performs random testing of smithy card.
params: None
return: returns 0 on successful completion
pre-cond: None
*************************************************************/
int smithRand() {
	srand(time(NULL));
	int seed = 1000;
    int i, p, hp, handCount, numPlayer;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *G = newGame();

    printf ("RANDOM TESTING playSmithy():\n");
    for (i = 0; i < NUM_TESTS; ++i) {
		numPlayer = rand() % 3 + 2; //randomly sets num of players to 2-4
		initializeGame(numPlayer, k, seed, G); //initialize a new game
		p = rand() % numPlayer;//randomly pick current player based on number of players
		handCount = rand() % 15 + 1; //randomly decide on num of cards in hand
		hp = rand() % handCount; //randomly set smithy in hand position based on number of cards in hand
#if (NOISY_TEST == 1)
        printf("Testing %d player game when player %d has smithy card in hand pos %d and %d cards in hand.\n"
			, numPlayer, p + 1, hp, handCount);
#endif        
        G->handCount[p] = handCount; //sets handCount to the current number of cards in the players hand
		G->hand[p][hp] = smithy; //places the smithy card in the players hand
        playSmithy(p, G, hp); //plays the smithy card for testing
#if (NOISY_TEST == 1)
		if (G->handCount[p] == handCount + 2) {
			printf("	Test PASSED! Hand count = %d, expected = %d\n", G->handCount[p], handCount + 2);
		}
		else {
			printf("	Test FAILED! Hand count = %d, expected = %d\n", G->handCount[p], handCount + 2);
		}
#endif
	}
    printf("Testing Complete!\n");
	return 0;
}