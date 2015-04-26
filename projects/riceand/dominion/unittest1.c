/* -------------------------------------------
 * Unit Tests to cover initializeGame() function
---------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set to 0 to turn OFF extra print statements
#define EXTRA_INFO 1

void testInitGameState(int players) {
	
  		printf("----------\n----------\n");
  		int p = players;
  		int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
  		srand(time(0));
  		int randSeed = (rand() % 10000) + 1;
  		if (EXTRA_INFO == 1)
  			printf("randSeed = %d\n", randSeed);
  		struct gameState s;

  		int r = initializeGame(p, k, randSeed, &s);
  		if (EXTRA_INFO == 1)
  			printf("r after init call = %d\n", r);

  		if (EXTRA_INFO == 1)
  			printf("Beginning tests with players = %d\n",p);

  		//make sure no errors returned from initializeGame call, or errors were returned if
  		//player size exceeded bounds
  		if (p > 0 && p <= MAX_PLAYERS)
  			assert(r == 0);
  		else
  			assert(r == -1);

  		if (EXTRA_INFO == 1)
  			printf("init game call returned 0 or -1 if players were out of bounds: PASSED\n");
  	
  	if (r == 0) {	
  		//check number of players was correctly set
  		assert(s.numPlayers == p);
  		if (EXTRA_INFO == 1)
  			printf("Number of players correct: PASSED\n");

  		//check curse cards were properly created
  		if (s.numPlayers == 2)
  			assert(s.supplyCount[curse] == 10);
  		if (s.numPlayers == 3)
  			assert(s.supplyCount[curse] == 20);
  		if (s.numPlayers > 3)
  			assert(s.supplyCount[curse] == 30);

  		if (EXTRA_INFO == 1)
  			printf("Curse cards properly created: PASSED\n");

  		//check estate,duchy,province cards set correctly
  		//if p=2:8 else 12
  		if (s.numPlayers == 2)
  			assert(s.supplyCount[estate] == 8 && s.supplyCount[duchy] == 8 && s.supplyCount[province] == 8);
  		else
  			assert(s.supplyCount[estate] == 12 && s.supplyCount[duchy] == 12 && s.supplyCount[province] == 12);

  		if (EXTRA_INFO == 1)
  			printf("Estate, duchy, and province cards set correctly: PASSED\n");

  		//check state->supplyCount[copper,silver,gold]
		assert(s.supplyCount[copper] == 60 - (7*s.numPlayers));
		assert(s.supplyCount[silver] == 40);
		assert(s.supplyCount[gold] == 30);

		if (EXTRA_INFO == 1)
			printf("Copper, silver, and gold set correctly: PASSED\n");

		//check supply count for adventurer through treasure_map
		int i;
		int j;
		int unused_cards[20];
		int unused_count = 0;
		int found;
		for (i = 0; i < 20; i++)
			unused_cards[i] = -9999; //random value for while loop later
		for (i = adventurer; i <= treasure_map; i++) {
			found = 0;
			for (j = 0; j < 10; j++){
				if (k[j] == i) {
					found = 1;
					if (k[j] == great_hall || k[j] == gardens) {
						if (s.numPlayers == 2)
							assert(s.supplyCount[i] == 8);
						else
							assert(s.supplyCount[i] == 12);
					}
					else
						assert(s.supplyCount[i] == 10);
				}
			}
			if (found == 0)
				unused_cards[unused_count++] = i;
		}

		if (EXTRA_INFO == 1){
			printf("unused_cards array:\n");
			int z;
			for (z = 0; z < 20; z++){
				if (unused_cards[z] != -9999)	
					printf("unused_cards[%d] = %d\n", z, unused_cards[z]);
			}
		}
		unused_count = 0;
		while(unused_cards[unused_count] != -9999)
			assert(s.supplyCount[unused_cards[unused_count++]] == -1);

		if (EXTRA_INFO == 1)
			printf("Supply count for kingdomCards correct: PASSED\n");

		//check state->deckCount[playerNum] != 0 for all players
		for (i = 0; i < s.numPlayers; i++){
			assert(s.deckCount[i] > 0);
		}

		if (EXTRA_INFO == 1)
			printf("deckCount greater than 0: PASSED\n");


		//check state->deck[playerNum][card] has 3 estates and 7 coppers for all players
		int estate_count, copper_count;
		for (i = 0; i < s.numPlayers; i++){
			estate_count = 0;
			copper_count = 0;
			for (j = 0; j < 10; j++) {
				if (s.deck[i][j] == estate)
					estate_count++;
				else if (s.deck[i][j] == copper)
					copper_count++;
			}
			assert(estate_count == 3);
			assert(copper_count == 7);
		}

		if (EXTRA_INFO == 1)
			printf("players start with 3 estates and 7 coppers: PASSED\n");

		//state->discardCount[player] == 0 and handCount is 0 for all other players except 1
		for (i = 0; i < s.numPlayers; i++){
			if (i > 0)
				assert(s.handCount[i] == 0);
			assert(s.discardCount[i] == 0);
		}

		if (EXTRA_INFO == 1)
			printf("discardCount and handCount correct: PASSED\n");

		//state->embargoTokens[0 through treasure_map] == 0
		for (i = 0; i <= treasure_map; i++)
			assert(s.embargoTokens[i] == 0);

		if (EXTRA_INFO == 1)
			printf("embargoTokens set correctly: PASSED\n");

		//other state checks

  		assert(s.outpostPlayed == 0);
  		assert(s.phase == 0);
  		assert(s.numActions == 1);
  		assert(s.numBuys == 1);
  		assert(s.playedCardCount == 0);
  		assert(s.whoseTurn == 0);
  		
  		if (EXTRA_INFO == 1)
  			printf("Checks on other state variables: PASSED\n");

  		//state->handCount[state->whoseTurn] should be 5 after drawing cards
  		assert(s.handCount[s.whoseTurn] == 5);

  		if (EXTRA_INFO == 1)
  			printf("Player 1 draws 5 cards to start: PASSED\n");

  		//state->coins should be > 0
  		assert(s.coins > 0);
  		if (EXTRA_INFO == 1)
  			printf("Update coins for player 1: PASSED\n");

  		printf("----------\n----------\n");
  	}
  	else {// r == -1
  		printf("r == -1 so rest of the tests were skipped for this input\n");
  		printf("----------\n----------\n");
  	}
}	

int main(int argc, char* argv[]) {

	//test with two players
	testInitGameState(2);
	//test with three players
	testInitGameState(3);
	//test with MAX_PLAYERS players
	testInitGameState(MAX_PLAYERS);
	//test with 0 players (expect to fail)
	testInitGameState(0);
	//test with max + 1 players (expect to fail)
	testInitGameState(MAX_PLAYERS+1);
	//test with negative players (definitely expect to fail)
	testInitGameState(-1);

	return 0;
}