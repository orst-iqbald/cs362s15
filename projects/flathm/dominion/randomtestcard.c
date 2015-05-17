/**************************************************
Michael Flath
CS362
Assignment 4
This file will randomly test smithy()

test2: dominion.o randomtestcard.c
	gcc -o randomtest2 randomtestcard.c -g dominion.o rngs.o $(CFLAGS)
**************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

//Smithy allows the player to add 3 cards to his hand
void checkSmithy(struct gameState *post, int handpos);
int smithyCard(struct gameState *state, int handPos);


int main()
{	
	int i, r, j, end = 0;
	int num;
	int players = 4;
    int seed = rand() % 1000;
    struct gameState G;
	
	 int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; 
   
	while(end < 5000) {
		printf("**************************Smithy Test %d***********************************\n\n", end+1);
		
		//Initialize game 
		memset(&G, 0, sizeof(struct gameState)); // zero game state
		r = initializeGame(players, k, seed, &G); // initializeGame returns 0 on success
		assert(r == 0);
		
		printf("Testing: smithy() in process...!\n");	
		
		//Initialize all player decks and hands
		for(i = 0; i < players; i++) {
			 
			//initialize and set hand
			G.handCount[i] = 5;
			//initialize and set deck
			G.deckCount[i] = 5;
			
			//Psuedo-Random hand and deck
			G.hand[i][0] = smithy;
			G.deck[i][0] = gold;
			for(j = 1; j < 5; j++) {
				num = rand() % 5;
				if(num == 1) {
					G.hand[i][j] = estate;
					G.deck[i][j] = estate;
				}
				else if(num == 2) {
					G.hand[i][j] = duchy;
					G.deck[i][j] = copper;
				}
				else if(num == 3) {
					G.hand[i][j] = province;
					G.deck[i][j] = province;
				}
				else {
					G.hand[i][j] = silver;
					G.deck[i][j] = silver;
				}
			}			
						
		}
		checkSmithy(&G, 0);
		
		end++;
	}
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