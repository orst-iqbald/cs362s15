/* -----------------------------------------------------------------------
 * Michael Flath
 * CS362
 * unittest1.c
 * Include the following lines in your makefile:
 *
 * test1: dominion.o unittest1.c
 *      gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


void CheckUpdateCoins(int player, struct gameState *post, int bonus) {
	int j, check, r_num;
	struct gameState pre;
	
	memcpy (&pre, post, sizeof(struct gameState));
	printf("PRE: handCount: %d\n", pre.handCount[player]);
	
	// Hand status based on game initialization.
	pre.coins = 0; 
   
   //Add random coin cards to the deck and check if updateCoins() updated amount in each case: copper, silver, gold, or none. 
   //Test bonus coins.
   //Test no coins
 	for(j = 1; j < 100; j++) {
			r_num = rand() % 4; 	//produce a random number between 0 -> 3, indicating either no coin, copper, silver, or gold.
			printf("Random num: %d\n", r_num);
			
			//Place new coin cards in players hand
			if(r_num == 1) {
				post->hand[player][post->handCount[player]+j] = copper;
				
				pre.hand[player][pre.handCount[player]+j] = copper;
				pre.handCount[player]++;
				pre.coins += 1;
			}
			else if (r_num == 2) {
				post->hand[player][post->handCount[player]+j] = silver;
				
				pre.hand[player][pre.handCount[player]+j] = silver;
				pre.handCount[player]++;
				pre.coins += 2;
			}
			else if (r_num == 3) {
				post->hand[player][post->handCount[player]+j] = gold;
				
				pre.hand[player][pre.handCount[player]+j] = gold;
				pre.handCount[player]++;
				pre.coins += 3;
			} 
			pre.coins += bonus;
			
			check = updateCoins(player, post, bonus);
			
			assert(check == 0); //Confirm the function call returns successfully
			if(assert(pre.coins != post->coins)) {
				printf("Fail: COINS error at: %d\n", j);	//Check for matching coin count
				printf("pre.coins: %d post.coins %d\n", pre.coins, post->coins);
			}
			//Test for the same hand count through each iteration
			if(assert(pre.handCount[player] != post->handCount[player])) {
				printf("Fail: handCount error at: %d\n", j);
				printf("pre.handCount: %d post.handCount %d\n", pre.handCount[player], post->handCount[player]);
			}
	}	
}

int main() {
	
    int j, r;
	int random_num;
	int players = 2;
	int seed = rand() % 1000; //Random seed to initialize game
    int bonus;
	
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
	struct gameState G;	
		
    printf ("TESTING updateCoins():\n");
	
	bonus = rand() % 10;
	memset(&G, 0, sizeof(struct gameState));	//reset game
	r = initializeGame(players, k, seed, &G);
	G.handCount[1] = rand() % 100;
	printf("HandCount %d\n", G.handCount[1]);
	
	//Set initialized hand for the player.
	for(j = 0; j < G.handCount[1]; j++) {
		random_num = rand() % 4;
		
		if(random_num == 1) {
			G.hand[1][j] = copper;
			G.coins += 1;
		}
		else if (random_num == 2) {
			G.hand[1][j] = silver;
			G.coins += 2;
		}
		else if (random_num == 3) {
			G.hand[1][j] = gold;
			G.coins += 3;
		} 
	}
	CheckUpdateCoins(1, &G, bonus);
		
	assert(r == 0);
    printf("Tests have been executed!\n");
	
	return 0;
}