/**************************************************
Michael Flath
CS362
Assignment 4

This file is a random test for adventurer()

test2: dominion.o randomtestadventurer.c
	gcc -o randomadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
**************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

//Reveal cards in deck until 2 treasure cards are found, 
//the 2 treasure cards are placed in players hand, and the other revealed
//cards are discarded
int adventurerCard(struct gameState *state);

int main()
{	
	int i, p, r, j, x, count, count2;
	int players = 4;
    int seed = rand() % 1000;
	int check, check1, check2, check3;
	struct gameState G;
	struct gameState pre; 
	
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; 
    
	int end = 0;
    while(end < 5000) {
			printf("***************************************** TEST %d *******************************\n\n", end+1);
		//Initialize game 
		memset(&G, 0, sizeof(struct gameState)); // zero game state
		r = initializeGame(players, k, seed, &G); // initializeGame returns 0 on success
		assert(r == 0);
		
		printf("Testing: adventurer() in process...!\n");	
		
		//Run tests for players 1 and 2 with treasure cards
		//Initialize all player decks and hands
		for(i = 0; i < 2; i++) {
			 
			//initialize and set hand
			G.handCount[i] = 5;
			
			G.hand[i][0] = adventurer;
			G.hand[i][1] = duchy;
			G.hand[i][2] = estate;
			G.hand[i][3] = province;
			G.hand[i][4] = baron;
			 
			//initialize and set deck
			G.deckCount[i] = 5;
			
			G.deck[i][0] = feast;
			G.deck[i][1] = council_room;
			G.deck[i][2] = copper;
			G.deck[i][3] = silver;
			G.deck[i][4] = gold;
			
			
		}
		
		memcpy(&pre, &G, sizeof(struct gameState));
		
		//player 1
		int p1 = 0; 
		int p2 = 1;
		G.whoseTurn = p1;
		//set player 1 and 2 handCount to equal the 2 additional coin cards that should be added by adventurer()	
		pre.handCount[p1] += 2;
		pre.handCount[p2] += 2;
		
		//Test players 1 and 2 for +2 treasure cards in hand. 
		check = adventurerCard(&G);	
		if(check != 0)
			printf("Fail: Adventure card did not return successfully for check1!\n");
		
		G.whoseTurn = p2;
		check1 = adventurerCard(&G);	
		if(check1 != 0)
			printf("Fail: Adventure card did not return successfully for check1!\n");
		
		
		//Check if 2 actual treasure cards were added to the hand.
		count = 0;
		count2 = 0;
		for(p = 0; p < 2; p++) {
			for(x = 0; x < G.handCount[1]; x++) {
				if(G.hand[p][x] == copper || G.hand[p][x] == silver || G.hand[p][x] == gold) {
					if(p == 0) //increment count for player 1
						count++;
					else	//increment count for player 2
						count2++;
				}
			}
		}
		
		//Test for the same handCount 2 treasure cards should have been added to hand
		//Test for player 1
		if(pre.handCount[p1] != G.handCount[p1]) {
			printf("Tesing player 1\n");
			printf("Fail: pre.handCount = %d post.handCount = %d\n", pre.handCount[p1], G.handCount[p1]);
		}
		//Test for player 2
		if(pre.handCount[p2] != G.handCount[p2]) {
			printf("Tesing player 2\n");
			printf("Fail: pre.handCount = %d post.handCount = %d\n", pre.handCount[p2], G.handCount[p2]);
		}
		
		//Check if 2 actual treasure cards were added to the hand.
		//count for player 1
		if(count != 2) {
			printf("Tesing player 1\n");
			printf("Fail: count = %d\n", count);
		}
		//count for player 2
		if(count2 != 2) {
			printf("Tesing player 2\n");
			printf("Fail: count = %d\n", count2);
		}
		
		/*************************************test 2*************************************/
		//Test player 3 for no treasure cards - fill player 3's deck with estate cards.
		//set handCount and hand for player 3
		G.handCount[2] = 5;
		G.hand[2][0] = adventurer;
		G.hand[2][1] = duchy;
		G.hand[2][2] = estate;
		G.hand[2][3] = province;
		G.hand[2][4] = baron;
		
		pre.handCount[2] = 5;
		
		//set deck for player 3
		G.deckCount[2] = MAX_HAND;
		
		//Maximize deck with estate cards and no treasure cards.
		for(j = 0; j < MAX_HAND; j++) {
			G.deck[2][j] = estate;
		}	
		
		int p3 = 2;
		G.whoseTurn = p3;
		
		check2 = adventurerCard(&G);
		
		if(check2 != 0)
			printf("Fail: Adventure card did not return successfully for check2!\n");
		
		//Test for handCount. 0 cards should be added to hand count since there are no treasure cards in the deck.
		if(pre.handCount[p3] != G.handCount[p3]) {
			printf("Testing player 3\n");
			printf("Fail: pre.handCount = %d post.handCount = %d\n", pre.handCount[p3], G.handCount[p3]);
		}
		
		/********************************test 3*********************************************/
		int p4 = 3;
		//Test player 4 with deckCount == 0
		G.deckCount[p4] = 0;
		pre.deckCount[p4] = 0;
		pre.discardCount[p4] += 1;
		
		G.whoseTurn = p4;
		check3 = adventurerCard(&G);
		
		if(check3 != 0)
			printf("Fail: Adventure card did not return successfully for check3!\n");

		//If there are no cards in the deck, the function adventurer will shuffle, discard, and add to the deck.,
		if(pre.handCount[p3] != G.handCount[p3]) {
			printf("Tesing player 4\n");
			printf("Fail: pre.handCount = %d post.handCount = %d\n", pre.handCount[p3], G.handCount[p3]);
		}
		
		//Check if action discard was made
		if(G.discardCount[p3] < 1) {
			printf("Tesing player 4\n");
			printf("Fail: pre.discardCount = %d post.discardCount = %d\n", pre.discardCount[p3], G.discardCount[p3]);
		}
	
		end++;
	}
	printf("Testing adventurer completed!\n");
	
	return 0;
}