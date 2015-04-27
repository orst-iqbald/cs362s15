#include "testings.h"

//test fullDeckCount
int test_FullDeckCount(){
	srand(time(NULL));

	int passes = 0,
		fails = 0,
		tests = 0;

	int p = 2,
		i = 0,
		j = 0;

	int thek = adventurer,
		k1 = council_room,
		k2 = feast;

	int k[10] = {sea_hag, council_room, feast, gardens, mine, remodel,
		smithy, village, baron, great_hall};

	int deckSize = 0,
		handSize = 0,
		discardSize = 0;

	printf("TESTING fullDeckCount():\n");

	for(deckSize = 0; deckSize < MAX_DECK; deckSize += rand()%50+1){
		for(discardSize = 0; discardSize < MAX_DECK; discardSize += rand()%50+1){
			for(handSize = 0; handSize < MAX_HAND; handSize += rand()%50+1){
				for(j = 0; j < 100; j++){
					int deckHits = deckSize == 0 ? 0 : rand() % deckSize,
						discardHits = discardSize == 0 ? 0 : rand() % discardSize,
						handHits = handSize == 0 ? 0 : rand() % handSize;

					printf("Test deck # = %d, discard # = %d, hand # = %d\n",
							deckHits,discardHits,handHits);

					int expectedHits = deckHits + discardHits + handHits;

					struct gameState *state = newGame();
					initializeGame(p,k,1,state);

					state->handCount[p] = 0;
					for(i = 0; i < handSize && i < handHits; i++){
							state->hand[p][i] = thek;
							state->handCount[p]++;
					}

					state->deckCount[p] = 0;
					for(i = 0; i < deckSize && i < deckHits; i++){
							state->deck[p][i] = thek;
							state->deckCount[p]++;
					}

					state->discardCount[p] = 0;
					for(i = 0; i < discardSize && i < discardHits; i++){
							state->discard[p][i] = thek;
							state->discardCount[p]++;
					}

					int hits = fullDeckCount(p,thek,state);

					printf("FullDeckCount counted = %d, expected = %d\n",hits,expectedHits);

					if(expectedHits == hits)
						passes++;
					else
						fails++;
					tests++;

					printf("%s\n",(expectedHits == hits ? STR_PASS : STR_FAIL));

					free(state);
				}
			}
		}
	}
	printf(SUMMARY,passes,fails,tests);

	return 0;
}
