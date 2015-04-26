#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define NUMRUNS 10

int main(int argc, char* argv[])
{
    printf("\n\n****BEGIN CARDTEST2: doSmithy****\n");
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
	int player = 0;
	
	printf ("State initalization.....");
	initializeGame(NUM_PLAYERS, k, 5, m_state);
	printf("PASS\n");
    
    printf("****END CARDTEST2****\n");
    return 0;
}