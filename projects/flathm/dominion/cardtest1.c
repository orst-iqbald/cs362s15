/*
Michael Flath
CS362
cardtest1.c
This file will test smithy()

test2: dominion.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

void checkSmithy(struct gameState *post, int handpos);
int smithyCard(struct gameState *state, int handPos);


int main()
{	
	int i, r;
	int players = 4;
    int seed = rand() % 1000;
    struct gameState G;
	
	 int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; 
   
    //Initialize game 
    memset(&G, 0, sizeof(struct gameState)); // zero game state
	r = initializeGame(players, k, seed, &G); // initializeGame returns 0 on success
	assert(r == 0);
	
	printf("Testing: smithy() in process...!\n");	
	
    //Initialize all player decks and hands
	for(i = 0; i < players; i++) {
		 
		//initialize and set hand
		G.handCount[i] = 5;
		
		G.hand[i][0] = smithy;
		G.hand[i][1] = estate;
		G.hand[i][2] = duchy;
		G.hand[i][3] = province;
		G.hand[i][4] = gold;
		 
		//initialize and set deck
        G.deckCount[i] = 5;
		
        G.deck[i][0] = gold;
        G.deck[i][1] = silver;
        G.deck[i][2] = copper;
        G.deck[i][3] = province;
		G.deck[i][3] = estate;
		
	}
	checkSmithy(&G, 0);
	
    printf("Testing: smithy() Complete!\n");
		
	return 0;
}

void checkSmithy(struct gameState *post, int handpos) {
	int i, check;
	struct gameState pre;
	
	memcpy(&pre, post, sizeof(struct gameState));
	
	for(i = 0; i < post->numPlayers; i++) {
		
		//Set player turn
		post->whoseTurn = i;
	
		//Manually set pre game condition
		pre.handCount[i] += 3;
		pre.discardCount[i] += 1;
		                  
		//Check for 3 drawn cards and 1 discard card.
        check = smithyCard(post, 0);
		
		if(check != 0)
			printf("smithycard function returned unsuccessful!\n");
		
		//Test for the same handCount: smithy draws 3 cards into the players hand
		if(post->handCount[i] != pre.handCount[i]) {
			
			printf("Fail: pre.handCount = %d post.handCount = %d\n", pre.handCount[i], post->handCount[i]);
			printf("Player %d\n", i+1);
		}
		
		//Test for the same discard: smithy discards 1 card 
		if(post->discardCount[i] != pre.discardCount[i]) {
			printf("Fail: pre.discardCount = %d post->discardhandCount = %d\n", pre.discardCount[i], post->discardCount[i]);
			printf("Player %d\n", i+1);
		}
	}
}



