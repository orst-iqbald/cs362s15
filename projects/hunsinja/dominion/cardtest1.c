//normal includes
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//dominion includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int greatHallTest(int handPos, int player, struct gameState *after) 
{
	int currPlayer = player;
	struct gameState before;
	int card = great_hall;
	int effect = cardEffect(card, 0, 0, 0, &before, handPos, 0);

	memcpy(&before, after, sizeof(struct gameState));
	
	drawCard(currPlayer, after);
	after->numActions++;
	discardCard(handPos, currPlayer, after, 0);
	
	//make sure nothing bad happened
	assert (effect == 0);
	assert (before.numBuys == after->numBuys);
	assert (before.deckCount[currPlayer] == after->deckCount[currPlayer]);
	assert (before.handCount[before.whoseTurn] == after->handCount[before.whoseTurn]);
	assert (before.discardCount[before.whoseTurn] == after->discardCount[before.whoseTurn]);
	printf("Test passed\n");
	return 0;
}

int main()
{
	struct gameState state;
	int position;
	int i;
	int player;

	for (i = 0; i < sizeof(struct gameState); i++) 	
		((char*)&state)[i] = floor(Random() * 255);
	
	state.numPlayers = 2 + floor(Random() * (MAX_PLAYERS - 1));
	player = floor(Random() * state.numPlayers);
	state.whoseTurn = player;

	for (i = 0; i < state.numPlayers; i++) 
	{
		state.deckCount[i] = floor(Random() * (MAX_DECK));
		state.handCount[i] = floor(Random() * (MAX_DECK - 4));
		state.discardCount[i] = floor(Random() * (MAX_DECK));
	}

	state.playedCardCount = floor(Random() * MAX_DECK);
	state.numBuys = 1;    
	position = floor(Random() * (state.handCount[player]));
 
	greatHallTest(position, player, &state);
	return 0;
}