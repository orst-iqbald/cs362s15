/* 
	Unit test for the the card 'adventurer' implemented in the function
	cardEffect() found in dominion.c.

	Include the following lines in your makefile:

	cardtest1: cardtest1.c dominion.o rngs.o
      	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int main(){
	int r, i;
	int numPlayers = 2;
	int seed = 5555;
	int kingCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int bonus = 0;

	printf("\n\n\nTesting the Adventurer card.\n\n\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*2 Treasures in the deck*/
	G.handCount[0] = 5;
	G.hand[0][0] = adventurer;
	G.deckCount[0] = 10;
	G.discardCount[0] = 0;
	for(i = 0; i < 10; i++){
		G.deck[0][i] = estate;
	}
	G.deck[0][3] = copper;
	G.deck[0][7] = copper;

	cardEffect(adventurer, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 7){
		if(G.hand[0][5] == copper && G.hand[0][6] == copper) printf("SUCCESS: Drew two coppers.\n");
		else printf("FAILURE: Two coppers not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw two cards.");
	if(G.deckCount[0] + G.discardCount[0] == 8) printf("SUCCESS: Removed two from deck or discard.\n");
	else printf("FAILURE: Did not remove two from deck or discard.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*2 Treasures in the discard*/
	G.handCount[0] = 5;
	G.hand[0][0] = adventurer;
	G.deckCount[0] = 0;
	G.discardCount[0] = 10;
	for(i = 0; i < 10; i++){
		G.discard[0][i] = estate;
	}
	G.discard[0][3] = copper;
	G.discard[0][7] = copper;

	cardEffect(adventurer, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 7){
		if(G.hand[0][5] == copper && G.hand[0][6] == copper) printf("SUCCESS: Drew two coppers.\n");
		else printf("FAILURE: Two coppers not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw two cards.\n");
	if(G.deckCount[0] + G.discardCount[0] == 8) printf("SUCCESS: Removed two from deck or discard.\n");
	else printf("FAILURE: Did not remove two from deck or discard.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*1 in Deck, 1 in Discard*/
	G.handCount[0] = 5;
	G.hand[0][0] = adventurer;
	G.deckCount[0] = 5;
	G.discardCount[0] = 5;
	for(i = 0; i < 5; i++){
		G.discard[0][i] = estate;
		G.deck[0][i] = estate;
	}
	G.discard[0][2] = copper;
	G.deck[0][3] = copper;

	cardEffect(adventurer, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 7){
		if(G.hand[0][5] == copper && G.hand[0][6] == copper) printf("SUCCESS: Drew two coppers.\n");
		else printf("FAILURE: Two coppers not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw two cards.\n");
	if(G.deckCount[0] + G.discardCount[0] == 8) printf("SUCCESS: Removed two from deck or discard.\n");
	else printf("FAILURE: Did not remove two from deck or discard.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*1 in Deck, many in Discard*/
	G.handCount[0] = 5;
	G.hand[0][0] = adventurer;
	G.deckCount[0] = 5;
	G.discardCount[0] = 5;
	for(i = 0; i < 5; i++){
		G.discard[0][i] = estate;
		G.deck[0][i] = estate;
	}
	G.discard[0][2] = copper;
	G.discard[0][3] = copper;
	G.discard[0][1] = copper;
	G.discard[0][0] = copper;
	G.deck[0][3] = copper;

	cardEffect(adventurer, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 7){
		if(G.hand[0][5] == copper && G.hand[0][6] == copper) printf("SUCCESS: Drew two coppers.\n");
		else printf("FAILURE: Two coppers not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw two cards.\n");
	if(G.deckCount[0] + G.discardCount[0] == 8) printf("SUCCESS: Removed two from deck or discard.\n");
	else printf("FAILURE: Did not remove two from deck or discard.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*1 in Deck*/
	G.handCount[0] = 5;
	G.hand[0][0] = adventurer;
	G.deckCount[0] = 10;
	G.discardCount[0] = 0;
	for(i = 0; i < 10; i++){
		G.deck[0][i] = estate;
	}
	G.deck[0][3] = copper;

	cardEffect(adventurer, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 6){
		if(G.hand[0][5] == copper) printf("SUCCESS: Drew one coppers.\n");
		else printf("FAILURE: One copper not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw the one copper.\n");
	if(G.deckCount[0] + G.discardCount[0] == 9) printf("SUCCESS: Removed one from deck or discard.\n");
	else printf("FAILURE: Did not remove one from deck or discard.\n");

	/*1 in Discard*/
	G.handCount[0] = 5;
	G.hand[0][0] = adventurer;
	G.deckCount[0] = 0;
	G.discardCount[0] = 10;
	for(i = 0; i < 10; i++){
		G.discard[0][i] = estate;
	}
	G.discard[0][3] = copper;

	cardEffect(adventurer, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 6){
		if(G.hand[0][5] == copper) printf("SUCCESS: Drew one coppers.\n");
		else printf("FAILURE: One copper not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw the one copper.\n");
	if(G.deckCount[0] + G.discardCount[0] == 9) printf("SUCCESS: Removed one from deck or discard.\n");
	else printf("FAILURE: Did not remove one from deck or discard.\n");

	/*None in Deck or Discard*/
	G.handCount[0] = 5;
	G.hand[0][0] = adventurer;
	G.deckCount[0] = 5;
	G.discardCount[0] = 5;
	for(i = 0; i < 5; i++){
		G.discard[0][i] = estate;
		G.deck[0][i] = estate;
	}

	cardEffect(adventurer, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 5) printf("SUCCESS: Did not draw any new cards.\n");
	else printf("FAILURE: Incorrectly drew cards.\n");
	if(G.deckCount[0] + G.discardCount[0] == 10) printf("SUCCESS: Did not remove and cards from deck or discard.\n");
	else printf("FAILURE: Incorrectly removed cards from deck or discard.\n");

	return 0;
}