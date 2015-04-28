/*
Michael Flath
CS362
cardtest3.c
This file will test great_hall()

test2: dominion.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

//+1 card +1 action +1 VP
void TestGreat_Hall(struct gameState *post, int handpos);
int great_hallCard(struct gameState *state, int handPos);
int scoreFor(int player, struct gameState *state);

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
	
	printf("Testing: great_hall() in process...!\n");	
	
	//Initialize all player decks and hands
	for(i = 0; i < players; i++) {
		 
		//initialize and set hand
		G.handCount[i] = 5;
		
		G.hand[i][0] = great_hall;
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
	TestGreat_Hall(&G, 0);
	
	printf("Testing: great_hall() Complete!\n");	

	return 0;
}

void TestGreat_Hall(struct gameState *post, int handpos) {
	int i, check, post_score;
	int pre_score = 1;
	struct gameState pre;
	
	memcpy(&pre, post, sizeof(struct gameState));
	
	for(i = 0; i < post->numPlayers; i++) {
		
		//Set player turn
		post->whoseTurn = i;
	
		//Manually set pre game condition
		//Increase handCount since great_hall adds +1 cards to hand
		//Increase numActions since great_hall adds +1 actions to a player's turn
		pre.numActions = 1;	//Always starts at 1 for each turn
		pre.handCount[i] += 1;
		pre.numActions += 1;
		                  
		//Check for +1 card, +1 action, +1 VP 
        check = great_hallCard(post, 0);
		//Test for +1 VP
		post_score = scoreFor(i, post);
		
		if(check != 0)
			printf("great_hall card function returned unsuccessful!\n");
		
		//Test for the same handCount: great_hall adds +1 cards into the players hand
		if(post->handCount[i] != pre.handCount[i]) {
			
			printf("Fail: pre.handCount = %d post.handCount = %d\n", pre.handCount[i], post->handCount[i]);
			printf("Player %d\n", i+1);
		}
		
		//Test for the same numActions: great_hall = +1 actions  
		if(post->numActions != pre.numActions) {
			printf("Fail: pre.numActions = %d post->numActions = %d\n", pre.numActions, post->numActions);
			printf("Player %d\n", i+1);
		}
		
		//Test for the same score. great_hall = +1 VP
		if(post_score != pre_score) {
			printf("Fail: pre score = %d post score = %d\n", pre_score, post_score);
			printf("Player %d\n", i+1);
		}
	}
}