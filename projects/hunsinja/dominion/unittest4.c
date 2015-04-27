//normal includes
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//dominion includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.c"
#include "rngs.h"

void endTurnTest(int players, struct gameState *state)
{
	int i, temp;
	for(i = 0; i < players; i++) 
	{
		temp = i + 1;

		printf("Ending player %d's turn\n", state->whoseTurn + 1);
		endTurn(state);
		
		if (temp % players == 0)
			temp = 1;
		else
			temp++;

		printf("It is player %d's turn now\n", state->whoseTurn + 1, temp);
		assert(state->whoseTurn + 1 == temp);
		printf("All is well so far\n");
	}
}

int main(int argc, char **argv)
{
	struct gameState game;
	int seed = 8675309;	
	int i;
	int k[10] = {baron, adventurer, council_room, gardens, feast, mine, great_hall, village, remodel, smithy};

	printf("Begin testing\n\n");    
	for(i = 2; i <= MAX_PLAYERS; i++)
	{
		initializeGame(i, k, seed, &game);
		endTurnTest(i, &game);
	}
   	printf("\nEnd testing\n");          

	return 0;
}