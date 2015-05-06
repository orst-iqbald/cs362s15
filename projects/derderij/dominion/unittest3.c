/***********************
* Author: Jon Derderian
* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 3
* Filename: unittest3.c
* Description: A unit test of the kingdomCards() function in dominion.c.
* Compile instruction:
* unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
*************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {
	int pass = 0;
	//loop counter
	int i;
	//setting up card variable holders
	int *deckCards;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};
	
	printf ("TESTING kingdomCards():\n");
	
	deckCards = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall);
	
	for(i = 0; i < 10; i++) {
		printf("kingdomCards = %d, expected = %d\n", deckCards[i], k[i]);
		if(deckCards[i] != k[i]){
			printf("Test %d has FAILED.\n", i+1);
			pass++;
		}
		else {
			printf("Test %d has PASSED.\n", i+1);
		}
	}
	
	if(pass == 0) {
		printf("All Tests PASSED!\n");
	}
	
	return 0;
}