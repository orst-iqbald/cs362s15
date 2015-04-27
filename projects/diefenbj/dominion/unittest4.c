#include "testings.h"

int test_whoseTurn(){
	srand(time(NULL));

	int ps = 0,
		p = 0,
		i = 0,
		tests = 0,
		passes = 0,
		fails = 0;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};


	printf("TESTING whoseTurn():\n");
	for(ps = 0; ps < MAX_PLAYERS; ps++){
		for(p = 0; p < ps; p++){
			struct gameState *state = newGame();
			initializeGame(ps,k,1,state);

			printf("Init whoseTurn = %d, expected = 0\n",whoseTurn(state));

			int r = rand() % ps;
			state->whoseTurn = r;
			int res = whoseTurn(state);

			printf("whoseTurn = %d, expected = %d\n",res, r);

			if(r == res)
				passes++;
			else
				fails++;
			tests++;
			
			printf("%s\n",(r == res ? STR_PASS : STR_FAIL));

			free(state);
		}
	}
	printf(SUMMARY,passes,fails,tests);

	return 0;
}


