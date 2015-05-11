/* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 4
* Filename: randomtestcard.c
* Description: A random unit test of the smithy card in dominion.c.
* Compile instruction:
* randomtestcard: randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
*************************/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {
	int r;
	//loop counters
	int i, j;
	int numTests = 100; //number of tests to run
	int cardsPlayed;
	int pos;
    //setting up gamestate
	int hCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};
			
	//setting up the random number generator
	int seed = 1000;
	SelectStream(1);
    PutSeed((long)seed);
	
	printf ("TESTING Smithy Card:\n");
	
	for(i = 0; i < numTests; i++){
		int pass = 0;
		struct gameState *G = malloc(sizeof(struct gameState));
		seed = floor((Random() * 1000) + 1);
		int numPlayer = floor((rand() % 3) + 2); //random number of players, between 2-4
		// initialize game, as seen in example
		memset(G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, G); // initialize a new game
		assert(r == 0);
		
		//choosing a random player
		G->whoseTurn = floor(Random() * numPlayer);
		//Putting random amount of cards in current player's deck
		G->deckCount[whoseTurn(G)] = floor(Random() * (MAX_DECK / 3));
		//Putting random amount of cards in current player's hand
		G->handCount[whoseTurn(G)] = floor(Random() * (MAX_HAND / 3));
		//Setting discarded amount of cards
		G->discardCount[whoseTurn(G)] = MAX_DECK - (G->deckCount[whoseTurn(G)] + G->handCount[whoseTurn(G)]);
		G->playedCardCount = floor(Random() * 5);//number of played cards
		cardsPlayed = G->playedCardCount;
		
		//filling player's deck with random cards
		for(j = 0; j < G->deckCount[whoseTurn(G)]; j++){
			G->deck[whoseTurn(G)][j] = floor(Random() * 17);
		}
		//putting random cards in the player's hand
		for(j = 0; j < G->handCount[whoseTurn(G)]; j++){
			G->hand[whoseTurn(G)][j] = floor(Random() * 17);
		}
		//filling discard pile with random cards
		for(j = 0; j < G->discardCount[whoseTurn(G)]; j++){
			G->discard[whoseTurn(G)][j] = floor(Random() * 17);
		}
		
		//select random spot in player's hand and put smithy there
		pos = floor(Random() * G->handCount[whoseTurn(G)]);
		G->hand[whoseTurn(G)][pos] = smithy;
		//setting the hand count variable
		hCount = G->handCount[whoseTurn(G)];
		
		//running the smithy card
		cardSmithy(G, whoseTurn(G), pos);
		
		//see if smithy returned correct number of cards
		if(G->handCount[whoseTurn(G)] != (hCount+2)){ //add 3 cards, discard smithy card
			printf("Hand has incorrect number of cards, Test %d FAILED.\n", i+1);
			pass++;
		} 
		
		if(G->playedCards[G->playedCardCount - 1] != smithy){
			printf("Discard Test 1: Smithy was not discarded properly, Test %d FAILED.\n", i+1);
			pass++;
		}
		
		if(G->playedCardCount != (cardsPlayed - 1)){
			printf("Discard Test 2: Discard count incorrect, Test %d FAILED.\n", i+1);
			pass++;
		}
		
		if(pass == 0){
			printf("Test %d PASSED.\n", i+1);
		}
	}
	return 0;
}