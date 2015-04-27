#include "testings.h"

int test_Smithy(){
	printf("TESTING Smithy\n");

	struct gameState *state = newGame();

	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	initializeGame(2,k,1,state);

	state->deck[0][0] = adventurer;

	int res = h_adventurer(0,state);

	if(res == 0)
		printf(STR_PASS);
	else
		printf(STR_FAIL);

	return 0;
}
