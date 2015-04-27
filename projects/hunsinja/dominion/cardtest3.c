//normal includes
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

//dominion includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testCouncil_Room(int handPos, int player, struct gameState *after) 
{
	struct gameState before;
	int currPlayer = player;
	int card = council_room;
	int effect;
	int i;

	memcpy(&before, after, sizeof(struct gameState));
	effect = cardEffect(card, 0, 0, 0, &before, handPos, 0);

	for (i = 0; i < 4; i++) 
		drawCard(currPlayer, after);	

	after->numBuys++;

	for (i = 0; i < after->numPlayers; i++) {
		if (i != currPlayer) 
			drawCard(i, after);		
	}

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

	for (i = 0; i < state.numPlayers; i++) {
		state.deckCount[i] = floor(Random() * (MAX_DECK));
		state.handCount[i] = floor(Random() * (MAX_DECK - 4));
		state.discardCount[i] = floor(Random() * (MAX_DECK));
	}

	state.playedCardCount = floor(Random() * MAX_DECK);
	state.numBuys = 1;
	position = floor(Random() * (state.handCount[player]));

	testCouncil_Room(position, player, &state);
	return 0;
}