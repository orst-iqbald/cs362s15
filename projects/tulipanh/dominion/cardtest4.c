/* 
	Unit test for the the card 'remodel' implemented in the function
	cardEffect() found in dominion.c.

	Include the following lines in your makefile:

	cardtest4: cardtest4.c dominion.o rngs.o
      	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int main(){
	int r, i, numSupply;
	int numPlayers = 2;
	int seed = 5555;
	int kingCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int bonus = 0;

	printf("\n\n\nTesting the Remodel card.\n\n\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*Discard an Estate to get a Feast*/
	G.handCount[0] = 5;
	for(i = 0; i < 5; i++){
		G.hand[0][i] = copper;
	}
	G.hand[0][0] = remodel;
	G.hand[0][1] = estate;
	G.playedCardCount = 0;
	numSupply = G.supplyCount[9];


	r = cardEffect(remodel, 1, 9, -1, &G, 0, &bonus);
	if(G.discardCount[0] == 1 && G.discard[0][0] == feast) printf("SUCCESS: Feast added to discard pile.\n");
	else printf("FAILURE: Feast not added to discard pile.\n");
	if(G.playedCardCount == 1 && G.playedCards[0] == remodel) printf("SUCCESS: Remodel added to played pile.\n");
	else printf("FAILURE: Remodel not added to played pile.\n");
	if(G.handCount[0] == 3) printf("SUCCESS: Hand-size decreased by 2.\n");
	else printf("FAILURE: Hand-size did not decrease by 2.\n");
	if(G.hand[0][1] != estate) printf("SUCCESS: Estate no longer in hand.\n");
	else printf("FAILURE: Estate still in hand.\n");
	if(numSupply - G.supplyCount[9] == 1) printf("SUCCESS: Feast supply dropped by 1.\n");
	else printf("FAILURE: Feast supply did not drop by 1.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*Discard an Estate to get a Gold (invalid)*/
	G.handCount[0] = 5;
	for(i = 0; i < 5; i++){
		G.hand[0][i] = copper;
	}
	G.hand[0][0] = remodel;
	G.hand[0][1] = estate;
	G.playedCardCount = 0;
	numSupply = G.supplyCount[6];


	r = cardEffect(remodel, 1, 6, -1, &G, 0, &bonus);
	if(r == -1) printf("SUCCESS: Detected that Gold costs more than 2 more than Estate.\n");
	else printf("FAILURE: Did not detect that Gold costs more than 2 more than Estate.\n");
	if(G.discardCount[0] == 1 && G.discard[0][0] == gold) printf("FAILURE: Gold incorrectly added to discard pile.\n");
	else printf("SUCCESS: Gold correctly not added to discard pile.\n");
	if(G.playedCardCount == 1 && G.playedCards[0] == remodel) printf("FAILURE: Remodel incorrectly added to played pile.\n");
	else printf("SUCCESS: Remodel correctly not added to played pile.\n");
	if(G.handCount[0] == 3) printf("FAILURE: Hand-size incorrectly decreased by 2.\n");
	else printf("SUCCESS: Hand-size correctly did not decrease by 2.\n");
	if(G.hand[0][1] != estate) printf("FAILURE: Estate incorrectly no longer in hand.\n");
	else printf("SUCCESS: Estate correctly still in hand.\n");
	if(numSupply - G.supplyCount[6] == 1) printf("FAILURE: Gold supply incorrectly dropped by 1.\n");
	else printf("SUCCESS: Feast supply correctly did not drop by 1.\n");

	memset(&G, 23, sizeof(struct gameState));
	r = initializeGame(numPlayers, kingCards, seed, &G);

	/*Discard an Estate to get a Feast, but no supply left.*/
	G.handCount[0] = 5;
	for(i = 0; i < 5; i++){
		G.hand[0][i] = copper;
	}
	G.hand[0][0] = remodel;
	G.hand[0][1] = estate;
	G.playedCardCount = 0;
	G.supplyCount[9] = 0;

	r = cardEffect(remodel, 1, 9, -1, &G, 0, &bonus);
	if(r == -1) printf("SUCCESS: Detected that Feast is out of supply.\n");
	else printf("FAILURE: Did not detect that Feast is out of supply.\n");
	if(G.discardCount[0] == 1 && G.discard[0][0] == feast) printf("FAILURE: Feast incorrectly added to discard pile.\n");
	else printf("SUCCESS: Feast correctly not added to discard pile.\n");
	if(G.playedCardCount == 1 && G.playedCards[0] == remodel) printf("FAILURE: Remodel incorrectly added to played pile.\n");
	else printf("SUCCESS: Remodel correctly not added to played pile.\n");
	if(G.handCount[0] == 3) printf("FAILURE: Hand-size incorrectly decreased by 2.\n");
	else printf("SUCCESS: Hand-size correctly did not decrease by 2.\n");
	if(G.hand[0][1] != estate) printf("FAILURE: Estate incorrectly no longer in hand.\n");
	else printf("SUCCESS: Estate correctly still in hand.\n");
	if(G.supplyCount[9] == -1) printf("FAILURE: Feast supply incorrectly dropped by 1.\n");
	else printf("SUCCESS: Feast supply correctly did not drop by 1.\n");

	return 0;
}