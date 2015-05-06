/*
Michael Flath
CS362
cardtest4.c
This file will test village()

test2: dominion.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

//+1 card +2 Actions
//void TestVillage(struct gameState *post, int handpos);
int villageCard(struct gameState *state, int handPos);

int main()
{	
	int i, r, j;
	int players = 4;
    int seed = rand() % 1000;
	int check;
	struct gameState G;
	struct gameState pre; 
	
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; 
   
    //Initialize game 
    memset(&G, 0, sizeof(struct gameState)); // zero game state
	r = initializeGame(players, k, seed, &G); // initializeGame returns 0 on success
	assert(r == 0);
	
	printf("Testing: village() in process...!\n");	
	
	//Initialize all player decks and hands
	for(i = 0; i < players; i++) {
		 
		//initialize and set hand
		G.handCount[i] = 5;
		
		G.hand[i][0] = village;
		G.hand[i][1] = feast;
		G.hand[i][2] = mine;
		G.hand[i][3] = smithy;
		G.hand[i][4] = baron;
		 
		//initialize and set deck
        G.deckCount[i] = 5;
		
        G.deck[i][0] = adventurer;
        G.deck[i][1] = council_room;
        G.deck[i][2] = copper;
        G.deck[i][3] = silver;
		G.deck[i][3] = gold;
		
	}
	
	memcpy(&pre, &G, sizeof(struct gameState));
	
	for(j = 0; j < G.numPlayers; j++) {
		
		//Set player turn
		G.whoseTurn = j;
	
		//Manually set pre game condition
		//Increase handCount since village adds +1 cards to hand
		//Increase numActions since village adds +2 actions to a player's turn
		pre.numActions = 1;	//Always starts at 1 for each turn
		pre.handCount[j] += 1;
		pre.numActions += 2; //village adds +2 actions
		                  
		//Test for +1 card, +2 action 
        check = villageCard(&G, 0);
		
		if(check != 0)
			printf("great_hall card function returned unsuccessful!\n");
		
		//Test for the same handCount: great_hall adds +1 cards into the players hand
		if(G.handCount[j] != pre.handCount[j]) {
			
			printf("Fail: pre.handCount = %d post.handCount = %d\n", pre.handCount[j], G.handCount[j]);
			printf("Player %d\n", j+1);
		}
		
		//Test for the same numActions: great_hall = +1 actions  
		if(G.numActions != pre.numActions) {
			printf("Fail: pre.numActions = %d post.numActions = %d\n", pre.numActions, G.numActions);
			printf("Player %d\n", j+1);
		}
		
	}
	
	printf("Testing: village() complete!\n");	

	return 0;
}
