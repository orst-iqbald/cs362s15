/*
Michael Flath
CS362
unittest3.c
This file will test fullDeckCount()

test2: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
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
	int i, j, x, r, rnum;
	int total;
	int players = 4;
	int player1 = 1;
	int player2 = 2;
	int player3 = 3;
    int seed = rand() % 1000;
    struct gameState G;
	int hand[27];
	int deck[27];
	int discard[27];
	
	 int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}; 
   
    //Initialize game 
    memset(&G, 0, sizeof(struct gameState)); // zero game state
	r = initializeGame(players, k, seed, &G); // initializeGame returns 0 on success
	assert(r == 0);
	
	printf("Testing: fullDeckCount() in process...!\n");
	
	G.deckCount[player1] = 500;
	G.discardCount[player1] = 500;
	G.handCount[player1] = 500;
	
	//Test boundary condition by maximizing hand, deck, and discard piles with estate cards.
	for(i = 0; i < MAX_DECK; i++) {
		
		G.hand[player1][i] = estate;	//Fill with 100 estate cards
		G.deck[player1][i] = estate;
		G.discard[player1][i] = estate;
	}
	total = fullDeckCount(player1, 1, &G);
	if(total != 1500) {
		printf("Fail: %d", total);
	}
	printf("Total upper boundary: %d\n", total);
	
	//Test boundary condition by zeroing out player2's hand, deck, and discard piles.
	G.deckCount[player2] = 0;
	G.discardCount[player2] = 0;
	G.handCount[player2] = 0;
	
	total = fullDeckCount(player2, 1, &G);
	if(total != 0) {
		printf("Fail: %d", total);
	}
	printf("Total lower boundary: %d\n", total);
	
	G.handCount[player3] = 500;
	G.deckCount[player3] = 500;
	G.discardCount[player3] = 500;
	//Test for random cards in player3's hand, deck, and discard piles.
	for(j = 0; j < MAX_HAND; j++) {
		rnum = rand() % 27;
		//count each deck
		hand[rnum] += 1;
		deck[rnum] += 1;
		discard[rnum] += 1;
			 
		switch( rnum ) 
		{
			
			case curse:
			  G.hand[player3][j] = curse;
			  G.deck[player3][j] = curse;
			  G.discard[player3][j] = curse;
			case estate:
			  G.hand[player3][j] = estate;
			  G.deck[player3][j] = estate;
			  G.discard[player3][j] = estate;
			case duchy:
			  G.hand[player3][j] = duchy;
			  G.deck[player3][j] = duchy;
			  G.discard[player3][j] = duchy;
			case province:
			  G.hand[player3][j] = province;
			  G.deck[player3][j] = province;
			  G.discard[player3][j] = province;
			case copper:
			  G.hand[player3][j] = copper;
			  G.deck[player3][j] = copper;
			  G.discard[player3][j] = copper;
			case silver:
			  G.hand[player3][j] = silver; 
			  G.deck[player3][j] = silver; 
			  G.discard[player3][j] = silver; 
			case gold:
			  G.hand[player3][j] = gold;
			  G.deck[player3][j] = gold;
			  G.discard[player3][j] = gold;
			case adventurer:
			  G.hand[player3][j] = adventurer;
			  G.deck[player3][j] = adventurer;
			  G.discard[player3][j] = adventurer;
			case council_room:
			  G.hand[player3][j] = council_room;
			  G.deck[player3][j] = council_room;
			  G.discard[player3][j] = council_room;
			case feast:
			  G.hand[player3][j] = feast;
			  G.deck[player3][j] = feast;
			  G.discard[player3][j] = feast;
			case gardens:
			  G.hand[player3][j] = gardens;
			  G.deck[player3][j] = gardens;
			  G.discard[player3][j] = gardens;
			case mine:
			  G.hand[player3][j] = mine;
			  G.deck[player3][j] = mine;
			  G.discard[player3][j] = mine;
			case remodel:
			  G.hand[player3][j] = remodel;
			  G.deck[player3][j] = remodel;
			  G.discard[player3][j] = remodel;
			case smithy:
			  G.hand[player3][j] = smithy;
			  G.deck[player3][j] = smithy;
			  G.discard[player3][j] = smithy;
			case village:
			  G.hand[player3][j] = village;
			  G.deck[player3][j] = village;
			  G.discard[player3][j] = village;
			case baron:
			  G.hand[player3][j] = baron;
			  G.deck[player3][j] = baron;
			  G.discard[player3][j] = baron;
			case great_hall:
			  G.hand[player3][j] = great_hall;
			  G.deck[player3][j] = great_hall;
			  G.discard[player3][j] = great_hall;
			case minion:
			  G.hand[player3][j] = minion;
			  G.deck[player3][j] = minion;
			  G.discard[player3][j] = minion;
			case steward:
			  G.hand[player3][j] = steward;
			  G.deck[player3][j] = steward;
			  G.discard[player3][j] = steward;
			case tribute:
			  G.hand[player3][j] = tribute;
			  G.deck[player3][j] = tribute;
			  G.discard[player3][j] = tribute;
			case ambassador:
			  G.hand[player3][j] = ambassador;
			  G.deck[player3][j] = ambassador;
			  G.discard[player3][j] = ambassador;
			case cutpurse:
			  G.hand[player3][j] = cutpurse;
			  G.deck[player3][j] = cutpurse;
			  G.discard[player3][j] = cutpurse;
			case embargo: 
			  G.hand[player3][j] = embargo;
			  G.deck[player3][j] = embargo;
			  G.discard[player3][j] = embargo;
			case outpost:
			  G.hand[player3][j] = outpost;
			  G.deck[player3][j] = outpost;
			  G.discard[player3][j] = outpost;
			case salvager:
			  G.hand[player3][j] = salvager;
			  G.deck[player3][j] = salvager;
			  G.discard[player3][j] = salvager;
			case sea_hag:
			  G.hand[player3][j] = sea_hag;
			  G.deck[player3][j] = sea_hag;
			  G.discard[player3][j] = sea_hag;
			case treasure_map:
			  G.hand[player3][j] = treasure_map;
			  G.deck[player3][j] = treasure_map;
			  G.discard[player3][j] = treasure_map;
		}
	
		
	}
	for(x = 0; x < 27; x++) {
		total = fullDeckCount(player3, x, &G);
		if(total != (hand[x] + deck[x] + discard[x])) {
			printf("Fail: At cardnumber %d\n", x);
			printf("Total count: %d\n", total);
			printf("Total cards: %d\n", (hand[x] + deck[x] + discard[x]));
		}
	}
	printf("Testing Complete!\n");
	//Test cards in hand and deck 
	
	return 0;
}

/*
//Compares switch statement results to if statements: they receive same results
		if(rnum == 0)
			G.hand[player3][j] = curse;
		else if(rnum == 1)
			G.hand[player3][j] = estate;
		else if(rnum == 2)
			G.hand[player3][j] = duchy;
		else if(rnum == 3)
			G.hand[player3][j] = province;
		else if(rnum == 4)
			G.hand[player3][j] = copper;
		else if(rnum == 5)
			 G.hand[player3][j] = silver;

*/

