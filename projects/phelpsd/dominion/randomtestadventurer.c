/************************************************************
 *File: randomtestadventurer.c
 *Author: Dustin Phelps
 *Date: 5/10/2015
 *Desc: File containing code for random testing of 
 *adventurer dominion card.
 *
 *randomtestadventurer.out: dominion.o randomtestadventurer.c
 *	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
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
int advRand();

/************************************************************
main function
params: none
return: returns 0 on success
pre-cond: none
*************************************************************/
int main() {
	return advRand();	
}

/************************************************************
Function that performs random testing of adventurer card.
params: None
return: returns 0 on successful completion
pre-cond: None
*************************************************************/
int advRand() {
	srand(time(NULL));
	int seed = 1000;
	int i, j, p, initCoins, newCoins, numPlayer, handCount, deckCoins, deckCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *G = newGame();

    printf ("RANDOM TESTING playAdventurer():\n");
    for (i = 0; i < NUM_TESTS; ++i) {
		numPlayer = rand() % 3 + 2; //randomly sets num of players to 2-4
		initializeGame(numPlayer, k, seed, G); //initialize a new game
		p = rand() % numPlayer;//randomly pick current player based on number of players
		initCoins = 0; //initializes starting treasure cards for each hand
        newCoins = 0; //initializes finishing treasure cards for each hand
		deckCoins = 0; //initializes variable to store num of treasure cards in deck
		G->handCount[p] = 0; //initialize value
		G->deckCount[p] = rand() % 10 + 10; //stores a random number of cards in the players deck
		//randomly generate the deck
		for (j = 0; j < G->deckCount[p]; ++j) {
			G->deck[p][j] = rand() % 26 + 1;
		}
		for (j = 0; j < 5; j++) {
			drawCard(p, G);
		}
		handCount = G->handCount[p]; //stores initial num of cards in hand
		deckCount = G->deckCount[p]; //stores initial num of cards in deck
		
#if (NOISY_TEST == 1)
        printf("Testing %d player game when player %d has %d cards in hand with adventurer card.\n"
			, numPlayer, p + 1, G->handCount[p]);
#endif 
        G->hand[p][0] = adventurer; //places the adventurer card in the players hand
        
		//count the treasure cards in current hand
		for (j = 0; j < G->handCount[p]; ++j) {
            if ( G->hand[p][j] == gold || G->hand[p][j] == silver || G->hand[p][j] == copper ) {
                initCoins++;
            }
        }
		//count the number of treasure cards in current players deck
		for (j = 0; j < G->deckCount[p]; ++j) {
			if ( G->deck[p][j] == gold || G->deck[p][j] == silver || G->deck[p][j] == copper ) {
                deckCoins++;
            }
		}
        playAdventurer(p, G); //plays the adventurer card for testing
		
        //count the number of treasure cards in the hand after adventurer card is played
		for (j = 0; j < G->handCount[p]; ++j) {
            if ( G->hand[p][j] == gold || G->hand[p][j] == silver || G->hand[p][j] == copper ) {
                newCoins++;
            }
        }
#if (NOISY_TEST == 1)
        printf("With %d treasure cards in hand, %d total cards in deck, and %d treasure in deck...\n"
			, initCoins, deckCount, deckCoins);
		//tests for correct number of treasure cards
		if (deckCoins >= 2) {
			if (newCoins == initCoins + 2) {
				printf("	Test PASSED! Treasure cards: New total = %d, expected = %d\n", newCoins, initCoins + 2);
			}
			else {
				printf("	Test FAILED! Treasure cards: New total = %d, expected = %d\n", newCoins, initCoins + 2);
			}
			//tests for correct number of cards in hand
			if (G->handCount[p] == handCount + 2) {
				printf("	Test PASSED! Hand Count: New total = %d, expected = %d\n", G->handCount[p], handCount + 2);
			}
			else {
				printf("	Test FAILED! Hand Count: New total = %d, expected = %d\n", G->handCount[p], handCount + 2);
			}
		}
		else if (deckCoins == 1) {
			if (newCoins == initCoins + 1) {
				printf("	Test PASSED! Treasure cards: New total = %d, expected = %d\n", newCoins, initCoins + 1);
			}
			else {
				printf("	Test FAILED! Treasure cards: New total = %d, expected = %d\n", newCoins, initCoins + 1);
			}
			//tests for correct number of cards in hand
			if (G->handCount[p] == handCount + 1) {
				printf("	Test PASSED! Hand Count: New total = %d, expected = %d\n", G->handCount[p], handCount + 1);
			}
			else {
				printf("	Test FAILED! Hand Count: New total = %d, expected = %d\n", G->handCount[p], handCount + 1);
			}
		}
		else {
			if (newCoins == initCoins) {
				printf("	Test PASSED! Treasure cards: New total = %d, expected = %d\n", newCoins, initCoins);
			}
			else {
				printf("	Test FAILED! Treasure cards: New total = %d, expected = %d\n", newCoins, initCoins);
			}
			//tests for correct number of cards in hand
			if (G->handCount[p] == handCount) {
				printf("	Test PASSED! Hand Count: New total = %d, expected = %d\n", G->handCount[p], handCount);
			}
			else {
				printf("	Test FAILED! Hand Count: New total = %d, expected = %d\n", G->handCount[p], handCount);
			}
		}
#endif
    }

    printf("Testing Complete!\n");

    return 0;
}