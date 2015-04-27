//Brittany Hopkins
//unittest3.c
//scoreFor()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main() {
	//I'm going to set all the variables that I need to start a new Dominion game
    int seed = 1000;
    int numPlayer = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
              , remodel, smithy, village, baron, great_hall};
    struct gameState state;
	int i;

	//printing the message for what is being tested
    printf ("Testing scoreFor()...\n");
	//clearing current game state
    memset(&state, 23, sizeof(struct gameState));   
	//initializing new game
    initializeGame(numPlayer, k, seed, &state); 
	
	//setting up array to hold card names
	const char *cardArray[6] = {"curse", "estate", "duchy", "province", "great_hall", "gardens"};
	//and a variable that holds the correct score for an 18 card deck with 3 of each card
	//equivalent to (-1 * 3) + (1 * 3) + (3 * 3) + (6 * 3) + (3 * 3) + (18/10) = 
	int totalScore = 41;
	
	//now I am going to set the deck so that the hand, discard, and deck each have 6 cards
	state.handCount[0] = 6;
	state.discardCount[0] = 6;
	state.deckCount[0] = 6;
	
	//Now i'll add one of each card to the hand, discard, and deck
	for(i = 0; i < state.handCount[0]; i++) {
		state.hand[0][i] = *cardArray[i];
		state.discard[0][i] = *cardArray[i];
		state.deck[0][i] = *cardArray[i];
		}
	
	//When I call the scoreFor() function with this hand, it should cover all possible if statements and produce
	//the same score as totalScore. If not, something is wrong with the function.
	int score = scoreFor(0, &state);
	
	//if score and totalScore are the same it passed, say so. Else tell them why it failed.
	if(score == totalScore) {
		printf("PASSED: scoreFor() correctly calculated score");
	}
	else {
		printf("FAILED: scoreFor() should have produced total score of %d\n", totalScore);
		printf("Score produced: %d\n", score);
	}
	
return 0;
}
