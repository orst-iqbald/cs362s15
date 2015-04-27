/*
Michael Flath
CS362
unittest2.c
This file will test getCost()

test2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
*******************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


int main()
{	
   
	int i, j, x, r, rnum, badnum;
	int cost;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	char *cards[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast",
			"gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse",
			"embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	
	char *costCard[27][2] = {{"curse", "0"}, {"estate", "2"}, {"duchy", "5"}, {"province", "8"}, {"copper", "0"}, {"silver", "3"}, {"gold", "6"}, {"adventurer", "6"}, {"council_room", "5"}, {"feast", "4"},
			{"gardens", "4"}, {"mine", "5"}, {"remodel", "4"}, {"smithy", "4"}, {"village", "3"}, {"baron", "4"}, {"great_hall", "3"}, {"minion", "5"}, {"steward", "3"}, {"tribute", "5"}, {"ambassador", "3"}, {"cutpurse", "4"},
			{"embargo", "2"}, {"outpost", "5"}, {"salvager", "4"}, {"sea_hag", "4"}, {"treasure_map", "4"}};
	
	int players = 2;
    int seed = rand() % 1000;
    struct gameState G;
   
   
    //Initialize game 
    memset(&G, 0, sizeof(struct gameState)); // zero game state
	r = initializeGame(players, k, seed, &G); // initializeGame returns 0 on success
	assert(r == 0);
	
	printf("Testing: getCost()...In Process\n");
	
	//Test for each card
	for(i = 0; i < 27; i++) {
		cost = getCost(i);
		//printf("Card: %s =  %d\n", cards[i], cost);	
	}
	
	//test for random inputs and check with built in 2d-array
	for(x = 0; x < 1000; x++) {
		rnum = rand() % 27;
		cost = getCost(rnum);
		if(cost != atoi(costCard[rnum][1])) {
			printf("Fail: %s = %d\n", costCard[rnum][0], rnum); 
		}
		
	}
	
	//Test false card numbers inputs
	for(j = 1; j < 100; j++) {
		badnum = j - 100;
		cost = getCost(badnum);
		if(cost != -1) {
			printf("Fail: Error - successful input with %d\n", badnum);
		}
		
	}
	
	printf("Testing Complete!\n");
	
	return 0;
}
 