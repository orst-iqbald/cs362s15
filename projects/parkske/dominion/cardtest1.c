#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define MYDEBUG
#define NUMRUNS 10
#define MAX_TEST_DECK 20

int testDoAdventurer(struct gameState *state, int player, int* temphand, int drawntreasure, int cardDrawn, int z)
{
	return doAdventurer(state, player, temphand, drawntreasure, cardDrawn, z);
}

int getTreasureCount(struct gameState *state, int player)
{
	int treasures = 0;
	int handCount = numHandCards(state);
	int i;
	for(i = 0; i < handCount - 1; i++)
	{
		int card = handCard(i, state);
		switch(card)
		{
			case gold:
			case silver:
			case copper:
				treasures++;
				break;
			default:
				break;
		}
	}
	return treasures;
}

int main(int argc, char* argv[])
{
    printf("\n\n****BEGIN CARDTEST1: doAdventurer****\n");
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
	int player = 0;
	int tempHand[MAX_HAND];
	int drawntreasure = 0;
	int cardDrawn;
	int z = 0;
	int i = 0;
	
	srand(time(NULL));
	
	printf ("State initalization.....");
	initializeGame(NUM_PLAYERS, k, 5, m_state);
	printf("PASS\n");
	
	//pre-test variables
	int m_handCount = numHandCards(m_state);
	int m_preTreasure = getTreasureCount(m_state, player);
	int m_deckCount = m_state->deckCount[player];
	
	//fill the player's deck so we can run our tests
	
	int d;
	for(d = m_deckCount; d < m_deckCount + 10; d++)
	{
		m_state->deck[player][d] = copper;
		m_state->deckCount[player]++;
	}
	m_deckCount += 10;
	
	for(d = m_deckCount; d < m_deckCount + 10; d++)
	{
		m_state->deck[player][d] = curse;
		m_state->deckCount[player]++;
	}
	m_deckCount += 10;
	printf("m_deck: %d\n", m_deckCount);
	for(i = 0; i < NUMRUNS; i++)
	{
		//odd test case 1: deckCount is 0
		if(i == NUMRUNS - 1)
		{
			printf("***Testing empty deck draw card case***\n");
			while(m_state->deckCount[player] > 1)
			{
				if(drawCard(player, m_state) >= 0)
					m_handCount++;
				m_state->discard[player][m_state->discardCount[player] ] = m_state->hand[player][m_handCount - 1];
				m_state->discardCount[player]++;
				m_handCount--;
			}
		}
		
		//normal use case, gain 2 treasure cards, return without error
		printf("Returns non-error.....");
		if(testDoAdventurer(m_state, player, tempHand, drawntreasure, cardDrawn, z) < 0)
		{
			printf("FAIL - Adventurer returns negative\n");
			printf("deCount %d; hCount: %d; tCount: %d; diCount: %d\n", m_state->deckCount[player], m_handCount, 
														  getTreasureCount(m_state, player), m_state->discardCount[player]);
			if(i == NUMRUNS - 1)
			{
				printf("***END empty deck draw card case***\n");
			}
			continue;
		}
		else
			printf("PASS\n");
		
		printf("State is not null.....");
		if(m_state == NULL)
		{
			printf("FAIL - stateNull -- ABORTING TEST\n");
			return -1;
		}
		else
		{
			printf("PASS\n");
			printf("Hand Count +2.....");
			m_handCount += 2;
			if(numHandCards(m_state) != m_handCount)
			{
				printf("FAIL - handCount\n");
			}
			else
				printf("PASS\n");
			printf("Treasure +2.....");
			m_preTreasure += 2;
			if(m_preTreasure != getTreasureCount(m_state, player))
			{
				printf("FAIL - treasureCount\n");
			}
			else
				printf("PASS\n");
		}
		if(i == NUMRUNS - 1)
		{
			printf("***END empty deck draw card case***\n");
		}
	}
	
	
	printf("****END CARDTEST1****\n");
    return 0;
}