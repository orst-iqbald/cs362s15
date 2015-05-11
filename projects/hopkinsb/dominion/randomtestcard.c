//brittany hopkins
//assignment 4
//randomtestcard.c
//due may 10, 2014

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

//random testing for the smithy card

int main() {
	//setting variables needed to create game/ run tests
	int cards[10] = {adventurer, council_room, feast, gardens, mine
              , remodel, smithy, village, baron, great_hall};
	struct gameState state;
	int seed = 1000;
	int numPlayers = 2;
	int i, j;
	int testing = 25;
	int beforeHand = 0;
	int afterHand = 0;
	int totalCardsBefore, totalCardsAfter;
	int errors = 0;
	srand(time(NULL));
	
	printf("Random testing of smithy card beginning...\n");
	
	//Begin loop by setting seed and initializing a game with previous variables
	for(i = 0; i < testing; i++) {
		memset(&state, 23, sizeof(struct gameState));
		initializeGame(numPlayers, cards, seed, &state);
		
		//Randomly generate and fill the deck, hand, and discard pile for a random player
		state.whoseTurn = floor(rand() % MAX_PLAYERS + 1);
		state.handCount[whoseTurn(&state)] = floor(rand() % MAX_HAND + 1);
			for(j = 0; j < state.handCount[whoseTurn(&state)]; j++) {
				state.hand[whoseTurn(&state)][j] = rand() % 17 + 1;
			}
		state.deckCount[whoseTurn(&state)] = floor(rand() % MAX_DECK + 1);
			for(j = 0; j < state.deckCount[whoseTurn(&state)]; j++) {
				state.deck[whoseTurn(&state)][j] = rand() % 17 + 1;
			}
		state.discardCount[whoseTurn(&state)] = MAX_DECK - (state.handCount[whoseTurn(&state)] + state.deckCount[whoseTurn(&state)]);
			for(j = 0; j < state.discardCount[whoseTurn(&state)]; j++) {
				state.discard[whoseTurn(&state)][j] = rand() % 17 + 1;
			}
		
		//get total number of cards generated
		totalCardsBefore = state.discardCount[whoseTurn(&state)] + state.deckCount[whoseTurn(&state)];
		
		//place smithy card at random in the hand
		j = rand() % state.handCount[whoseTurn(&state)] + 1;
		state.hand[whoseTurn(&state)][j] = smithy;
		
		//figure out total number of cards in hand before call to smithy
		beforeHand = state.handCount[whoseTurn(&state)];
		
		//call the smithy function
		smithyCard(&state, whoseTurn(&state), j);
		//figure out the total number of cards in hand after smithy call
		afterHand = state.handCount[whoseTurn(&state)];
		
		//figure out if total cards in discard/deck after smithy call
		totalCardsAfter = state.discardCount[whoseTurn(&state)] + state.deckCount[whoseTurn(&state)];
		
		//start making comparisons between before and after variables
		if(beforeHand + 3 != afterHand) {
			printf("FAILED: number of cards in hand should have been %d but was %d\n", beforeHand + 3, afterHand);
			errors++;
		}
		
		if(totalCardsAfter != totalCardsBefore - 3) { 
			printf("FAILED: total cards should have been %d but was %d\n", totalCardsBefore - 3, totalCardsAfter);
			errors++;
		}
		
		//if errors were found, print that the test failed, otherwise put passed
		if(errors > 0) {
			printf("FAILED\n");
		}
		else { 
			printf("PASSED\n");
		}
		
	}
	
	return 0 ;
}
