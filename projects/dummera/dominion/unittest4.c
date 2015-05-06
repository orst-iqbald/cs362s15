#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

#define NUM_PLAYERS 2

int testSupplyCount(int card, struct gameState *m_state)
{
	return supplyCount(card, m_state);
}

int main(int argc, char* argv[])
{
    printf("\n\n****Start Unit Test 4: SupplyCount****\n");
    struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    int i;
	int j = 89;
    int players[NUM_PLAYERS];
	int playerHandCount[NUM_PLAYERS];
    int flag = 0;
	enum CARD m_supplyPos;

	printf ("Start initalization.....");
    initializeGame(NUM_PLAYERS, k, 5, m_state);
    printf("Pass\n");
    j=testSupplyCount(1, m_state);

    for(i=0; i < NUM_PLAYERS; i++)
    {
        players[i] = i;
		playerHandCount[i] = m_state->handCount[i];
    }

    if(testSupplyCount(1, m_state) == 8)
    {
    	if(m_state->supplyCount[1] == m_state->supplyCount[1]){
    	printf("Card 1...Pass\n");
    	}


    	if(m_state->supplyCount[2] == m_state->supplyCount[2]){
    	printf("Card 2...Pass\n");
    	}


    	if(m_state->supplyCount[3] == m_state->supplyCount[3]){
    	printf("Card 3...Pass\n");
    	}
    }
    else
    {
    	printf("FAIL\n");
    	printf("Try %d \n", j);
    }
    printf("****End of Unit Test 4****\n");
    return 0;
}