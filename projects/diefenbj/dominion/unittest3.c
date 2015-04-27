#include "testings.h"

//scoreFor

int test_scoreFor(){
	srand(time(NULL));

	int i = 0,
		j = 0,
		p = 0,
		ks = 27,
		hs = 0,
		dks = 0,
		dcs = 0,
		passes = 0,
		fails = 0,
		tests = 0;


	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	printf("TESTING scoreFor():\n");

	for(dks = 0; dks < MAX_DECK; dks+=rand()%50+1){
		for(dcs = 0; dcs < MAX_DECK; dcs+=rand()%50+1){
			for(hs = 0; hs < MAX_HAND; hs+=rand()%50+1){
				int kcount[27] = {0};
				int scores[27] = {0};

				struct gameState *state = newGame();
				initializeGame(2,k,1,state);

				for(i = 0; i < state->deckCount[p]; i++){
					state->deck[p][i] = -1;
				}
				for(i = 0; i < state->discardCount[p]; i++){
					state->discard[p][i] = -1;
				}
				for(i = 0; i < state->handCount[p]; i++){
					state->hand[p][i] = -1;
				}

				state->deckCount[p] = 0;
				for(i = 0; i < dks; i++){
					int r = rand() % 27;
					state->deck[p][i] = r;
					state->deckCount[p]++;
					kcount[r]++;
				}

				state->discardCount[p] = 0;
				for(i = 0; i < dcs; i++){
					int r = rand() % 27;
					state->discard[p][i] = r;
					state->discardCount[p]++;
					kcount[r]++;
				}

				state->handCount[p] = 0;
				for(i = 0; i < hs; i++){
					int r = rand() % 27;
					state->hand[p][i] = r;
					state->handCount[p]++;
					kcount[r]++;
				}

				//printf("curse counts:%d\n",kcount[curse]);
				scores[curse] = -1 * kcount[curse];
				//printf("estate counts:%d\n",kcount[estate]);
				scores[estate] = kcount[estate];
				//printf("duchy counts:%d\n",kcount[duchy]);
				scores[duchy] = 3 * kcount[duchy];
				//printf("province counts:%d\n",kcount[province]);
				scores[province] = 6 * kcount[province];
				//printf("great_hall counts:%d\n",kcount[great_hall]);
				scores[great_hall] = kcount[great_hall];
				//printf("gardens counts:%d\n",kcount[gardens]);
				scores[gardens] = (fullDeckCount(p, 0, state) / 10) * kcount[gardens];

				printf("Test deck # = %d, discard # = %d, hand # = %d\n",
						state->deckCount[p],state->discardCount[p],state->handCount[p]);

				int exp = 0;
				for(i = 0; i < ks; i++){
					exp += scores[i];
				}

				int res = scoreFor(p,state);

				printf("Score = %d, expected = %d\n",res,exp);

				if(exp == res)
					passes++;
				else
					fails++;
				tests++;
				
				printf("%s\n",(exp == res ? STR_PASS : STR_FAIL));

				free(state);
			}
		}
	}
	printf(SUMMARY,passes,fails,tests);

	return 0;
}
