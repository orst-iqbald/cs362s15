/* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 4
* Filename: randomtestadventurer.c
* Description: A random unit test of the Adventurer card in dominion.c.
* Compile instruction:
* randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
*      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
	int numTests = 100;
	int pos;
	//loop count
	int i, j;
    //setting up gamestate
	int hCount;
	int card;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};
	
	//setting up the random number generator
	int seed = 1000;
	SelectStream(1);
    PutSeed((long)seed);
	
	printf ("RANDOM TESTING Adventurer Card:\n");
	for(j = 0; j < numTests; j++){
		int treasureHand = 0;
		int treasureHand2 = 0;
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
		
		//filling player's deck with random cards
		for(i = 0; i < G->deckCount[whoseTurn(G)]; i++){
			G->deck[whoseTurn(G)][i] = floor(Random() * 17);
		}
		//putting random cards in the player's hand
		for(i = 0; i < G->handCount[whoseTurn(G)]; i++){
			G->hand[whoseTurn(G)][i] = floor(Random() * 17);
		}
		//filling discard pile with random cards
		for(i = 0; i < G->discardCount[whoseTurn(G)]; i++){
			G->discard[whoseTurn(G)][i] = floor(Random() * 17);
		}
		
		//select random spot in player's hand and put adventurer there
		pos = floor(Random() * G->handCount[whoseTurn(G)]);
		G->hand[whoseTurn(G)][pos] = adventurer;
		//storing amount of card in hCount
		hCount = G->handCount[whoseTurn(G)];
		
		//counting the treasure cards
		for(i = 0; i < G->handCount[whoseTurn(G)]; i++) {
			card = G->hand[whoseTurn(G)][i];
			if(card == copper || card == silver || card == gold) {
				treasureHand++;
			}
		}
		
		cardAdventurer(G, whoseTurn(G));
		
		//counting treasure cards after the draw
		for(i = 0; i < G->handCount[whoseTurn(G)]; i++) {
			card = G->hand[whoseTurn(G)][i];
			if(card == copper || card == silver || card == gold) {
				treasureHand2++;
			}
		}
		//check for correct number of treasure cards
		if(hCount != (treasureHand2 + 2)){
			printf("Incorrect number of treasure cards added to hand, test %d FAILED.\n", j+1);
			pass++;
		}
		
		if(G->handCount[whoseTurn(G)] != (hCount + 1)){
			printf("Incorrect number of cards added to hand, test %d FAILED.\n", j+1);
			pass++;
		}
		
		if(pass == 0){
			printf("Test %d PASSED.\n", j+1);
		}
	}
	
	return 0;
}