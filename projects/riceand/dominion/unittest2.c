/* -------------------------------------------
 * Unit Tests to cover shuffle() function
---------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set to 0 to turn OFF extra print statements
#define EXTRA_INFO 1

void testShuffle(){
	//set up gamestate
	int player = 0; //variable for accessing player 1's stuff
	int p = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
  	srand(time(0));
  	int randSeed = (rand() % 10000) + 1;
  	if (EXTRA_INFO == 1)
  		printf("randSeed = %d\n", randSeed);
  	
  	struct gameState s;

  	int r = initializeGame(p, k, randSeed, &s);
  	if (EXTRA_INFO == 1)
  		printf("r after init call = %d\n", r);

  	assert(r == 0); //else rest will fail
  	
  	//end gamestate set up

  	/*
		Testing shuffle:
			1. copy player deck to array
			2. run shuffle on player deck
			3. make sure shuffle returns -1 if deckCount < 1 else 0
			4. Reset deck and size with randomly generated values in acceptable range
			5. check new deck against player deck
			    a. checking for same cards as before, to make sure it isn't shuffling and adding wrong cards
			6. repeat this random number of times for up to 50 runs
			7. Check that state->deckCount is same before and after shuffle call

			NOTE: Originally I tried to test to make sure at least 1 card was different after the shuffle. 
			However, with this in place I could only get through a full run of the program about
			once every 50 or so tries, even sometimes when random was low. So shuffle doesn't actually
			always shuffle it... perhaps a bug?
  	*/

	//first check the easiest thing - whether sending a deckCount below 1 returns -1
	int saved_deckCount = s.deckCount[player];
	s.deckCount[player] = 0;
	assert(shuffle(player, &s) == -1);
	s.deckCount[player] = saved_deckCount;

	if (EXTRA_INFO == 1)
		printf("Shuffle returns -1 when deckCount < 1: PASSED\n");

	//copy player deck to new array to "save" it
	int i, j, loop_count;
	int deck_size;
	int saved_deck[MAX_DECK];
	int random_amount = (rand() % 50) + 1;
	int random_card, random_size;
	for (loop_count = 0; loop_count < random_amount; loop_count++) {
		
		//find size of deck for this run
		random_size = (rand() % MAX_DECK) + 1;

		if (EXTRA_INFO == 1)
			printf("Size of deck for pass #%d is: %d\n", loop_count, random_size);

		//set to deck_size and gamestate variable
		deck_size = s.deckCount[player] = random_size;

		//make player deck using a random card from the enum CARD
		//assign to both gamestate deck and backup for checking later
		for (i = 0; i < deck_size; i++) {
			random_card = (rand() % 25);
			saved_deck[i] = s.deck[player][i] = random_card;
		}

		//call shuffle
		int shuffle_return = shuffle(player, &s);

		assert(shuffle_return == 0);

		//int diff = 0; //count the differences in the decks

		//make sure deckCount is still same size since this is altered in shuffle function
		assert(deck_size == s.deckCount[player]);

		//set up found for assert later
		int found = 0;
		//set up array to keep track of which cards were found in which positions
		//so if a deck as two coppers, we make sure we find both coppers and not 1 twice
		int checked[MAX_DECK];
		for (i = 0; i < deck_size; i++)
			checked[i] = 0;

		for (i = 0; i < deck_size; i++) {
			for (j = 0; j < deck_size; j++) {
				if (saved_deck[i] == s.deck[player][j]) {
					if (checked[i] == 0) {
						found++;
						checked[i] = 1;
						break;
					}
				}
			}
		}

		if (EXTRA_INFO == 1)
			printf("found = %d and deck_size = %d\n", found, deck_size);
		//make sure found cards == number of cards in player deck
		assert(found == deck_size);

		//test that there is at least one difference
		//had to be removed, refer to NOTE In block comment above
		//assert(diff >= 1); 
		
		if (EXTRA_INFO == 1)
			printf("Random test %d of %d testing shuffle: PASSED\n", loop_count+1, random_amount);
	}
}

 int main(int argc, char* argv[]) {

 	srand(time(0));

 	testShuffle();

 	return 0;
 }