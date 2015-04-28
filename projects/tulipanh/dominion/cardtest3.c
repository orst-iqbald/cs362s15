/* 
	Unit test for the the card 'village' implemented in the function
	cardEffect() found in dominion.c.

	Include the following lines in your makefile:

	cardtest3: cardtest3.c dominion.o rngs.o
      	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int main(){
	int r, i, numActs;
	int numPlayers = 2;
	int seed = 5555;
	int kingCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int bonus = 0;

	printf("\n\n\nTesting the Village card.\n\n\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*Cards in the deck*/
	G.handCount[0] = 5;
	G.hand[0][0] = village;
	G.playedCardCount = 0;
	G.deckCount[0] = 10;
	G.discardCount[0] = 0;
	numActs = G.numActions;
	for(i = 0; i < 10; i++){
		G.deck[0][i] = estate;
	}
	
	cardEffect(village, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 5){
		if(G.hand[0][0] == estate) printf("SUCCESS: Drew an estate.\n");
		else printf("FAILURE: Card not added to hand\n");
	}
	else printf("FAILURE: Did not draw a card.\n");
	if(G.deckCount[0] + G.discardCount[0] == 9) printf("SUCCESS: Removed one from deck or discard.\n");
	else printf("FAILURE: Did not remove one from deck or discard.\n");
	if(G.playedCardCount == 1) printf("SUCCESS: One added to played pile.\n");
	else printf("FAILURE: One not added to played pile.\n");
	if(G.numActions - numActs == 2) printf("SUCCESS: Two actions added.\n");
	else printf("FAILURE: Two actions not added.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*Cards in the discard but not in deck.*/
	G.handCount[0] = 5;
	G.hand[0][0] = village;
	G.playedCardCount = 0;
	G.discardCount[0] = 10;
	G.deckCount[0] = 0;
	numActs = G.numActions;
	for(i = 0; i < 10; i++){
		G.discard[0][i] = estate;
	}
	
	cardEffect(village, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 5){
		if(G.hand[0][0] == estate) printf("SUCCESS: Drew an estate.\n");
		else printf("FAILURE: Card not added to hand\n");
	}
	else printf("FAILURE: Did not draw a card.\n");
	if(G.deckCount[0] + G.discardCount[0] == 9) printf("SUCCESS: Removed one from deck or discard.\n");
	else printf("FAILURE: Did not remove one from deck or discard.\n");
	if(G.playedCardCount == 1) printf("SUCCESS: One added to played pile.\n");
	else printf("FAILURE: One not added to played pile.\n");
	if(G.numActions - numActs == 2) printf("SUCCESS: Two actions added.\n");
	else printf("FAILURE: Two actions not added.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*No cards in either.*/
	G.handCount[0] = 5;
	G.hand[0][0] = village;
	G.playedCardCount = 0;
	G.deckCount[0] = 0;
	G.discardCount[0] = 0;
	numActs = G.numActions;
	
	cardEffect(village, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 4) printf("SUCCESS: No cards drawn.\n");
	else printf("FAILURE: Incorrect hand size.\n");
	if(G.deckCount[0] + G.discardCount[0] == 0) printf("SUCCESS: Number in deck and discard remained the same.\n");
	else printf("FAILURE: Number in deck and discard changed.\n");
	if(G.playedCardCount == 1) printf("SUCCESS: One added to played pile.\n");
	else printf("FAILURE: One not added to played pile.\n");
	if(G.numActions - numActs == 2) printf("SUCCESS: Two actions added.\n");
	else printf("FAILURE: Two actions not added.\n");

	return 0;
}