/* 
	Unit test for the the card 'smithy' implemented in the function
	cardEffect() found in dominion.c.

	Include the following lines in your makefile:

	cardtest2: cardtest2.c dominion.o rngs.o
      	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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

	printf("\n\n\nTesting the Smithy card.\n\n\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*3 cards in the deck*/
	G.handCount[0] = 5;
	G.hand[0][0] = smithy;
	G.playedCardCount = 0;
	G.deckCount[0] = 10;
	G.discardCount[0] = 0;
	for(i = 0; i < 10; i++){
		G.deck[0][i] = estate;
	}
	
	cardEffect(smithy, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 7){
		if(G.hand[0][0] == estate && G.hand[0][5] == estate && G.hand[0][6] == estate) printf("SUCCESS: Drew three estates.\n");
		else printf("FAILURE: Three cards not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw three cards.\n");
	if(G.deckCount[0] + G.discardCount[0] == 7) printf("SUCCESS: Removed three from deck or discard.\n");
	else printf("FAILURE: Did not remove three from deck or discard.\n");
	if(G.playedCardCount == 1) printf("SUCCESS: One added to played pile.\n");
	else printf("FAILURE: One not added to played pile.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*3 cards in discard, none in deck*/
	G.handCount[0] = 5;
	G.hand[0][0] = smithy;
	G.playedCardCount = 0;
	G.discardCount[0] = 10;
	G.deckCount[0] = 0;
	for(i = 0; i < 10; i++){
		G.discard[0][i] = estate;
	}
	
	cardEffect(smithy, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 7){
		if(G.hand[0][0] == estate && G.hand[0][5] == estate && G.hand[0][6] == estate) printf("SUCCESS: Drew three estates.\n");
		else printf("FAILURE: Three cards not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw three cards.\n");
	if(G.deckCount[0] + G.discardCount[0] == 7) printf("SUCCESS: Removed three from deck or discard.\n");
	else printf("FAILURE: Did not remove three from deck or discard.\n");
	if(G.playedCardCount == 1) printf("SUCCESS: One added to played pile.\n");
	else printf("FAILURE: One not added to played pile.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*Less than 3 in deck, some in discard*/
	G.handCount[0] = 5;
	G.hand[0][0] = smithy;
	G.playedCardCount = 0;
	G.discardCount[0] = 8;
	G.deckCount[0] = 2;
	for(i = 0; i < 8; i++){
		G.discard[0][i] = estate;
	}
	for(i = 0; i < 2; i++){
		G.deck[0][i] = estate;
	}
	
	cardEffect(smithy, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 7){
		if(G.hand[0][0] == estate && G.hand[0][5] == estate && G.hand[0][6] == estate) printf("SUCCESS: Drew three estates.\n");
		else printf("FAILURE: Three cards not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw three cards.\n");
	if(G.deckCount[0] + G.discardCount[0] == 7) printf("SUCCESS: Removed three from deck or discard.\n");
	else printf("FAILURE: Did not remove three from deck or discard.\n");
	if(G.playedCardCount == 1) printf("SUCCESS: One added to played pile.\n");
	else printf("FAILURE: One not added to played pile.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*Less than 3 total*/
	G.handCount[0] = 5;
	G.hand[0][0] = smithy;
	G.playedCardCount = 0;
	G.discardCount[0] = 1;
	G.deckCount[0] = 1;
	G.deck[0][0] = estate;
	G.discard[0][0] = estate;
	
	cardEffect(smithy, -1, -1, -1, &G, 0, &bonus);
	if(G.handCount[0] == 6){
		if(G.hand[0][0] == estate && G.hand[0][5] == estate) printf("SUCCESS: Only drew two estates.\n");
		else printf("FAILURE: Two cards not added to end of hand.\n");
	}
	else printf("FAILURE: Did not draw two cards.\n");
	if(G.deckCount[0] + G.discardCount[0] == 0) printf("SUCCESS: Removed two from deck or discard.\n");
	else printf("FAILURE: Did not remove two from deck or discard.\n");
	if(G.playedCardCount == 1) printf("SUCCESS: One added to played pile.\n");
	else printf("FAILURE: One not added to played pile.\n");

	return 0;
}
