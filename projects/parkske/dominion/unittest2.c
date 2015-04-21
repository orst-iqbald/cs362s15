#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define TOFLAGMAX 3
#define MYDEBUG

int testGainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
	return gainCard(supplyPos, state, toFlag, player);
}

int main(int argc, char* argv[])
{
    printf("\n\n****BEGIN UNITTEST2: GainCard****\n");
	struct gameState state;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    int i;
    int players[NUM_PLAYERS];
	int playerCardCount[NUM_PLAYERS];
    int flag = 0;
	int m_supplyPos = 1;
	
    printf ("State initalization.....");
    initializeGame(NUM_PLAYERS, k, 5, &state);
    printf("PASS\n");
	
	for(i=0; i < NUM_PLAYERS; i++)
    {
        players[i] = i;
		playerCardCount[i] = state.handCount[i];
    }

	for(i=0; i < NUM_PLAYERS; i++)
	{
		for(flag=0; flag < TOFLAGMAX; flag++)
		{
			printf("Player%d testGainCard flag:%d.....", i+1, flag);
			int supply = supplyCount(m_supplyPos, &state);
			switch(flag)
			{
			case 1:;
				int deckCount = state.deckCount[players[i]];
				if(testGainCard(m_supplyPos, &state, flag, players[i]) == 0)
				{
					if(supplyCount(m_supplyPos, &state) == supply - 1 && \
						state.deckCount[players[i]] == deckCount + 1)
					{
						printf("PASS\n");
						break;
					}
					else
					{
						printf("FAIL\n");
						break;
					}
				}
				else
				{
					break;
				}
			case 2:;
				int handCount = state.handCount[players[i]];
				if(testGainCard(m_supplyPos, &state, flag, players[i]) == 0)
				{
					if(supplyCount(m_supplyPos, &state) == supply - 1 && \
						state.handCount[players[i]] == handCount + 1)
					{
						printf("PASS\n");
						break;
					}
					else
					{
						printf("FAIL\n");
						break;
					}
				}
				else
					break;
			default:;
				int discardCount = state.discardCount[players[i]];
				if(testGainCard(m_supplyPos, &state, flag, players[i]) == 0)
				{
					if(supplyCount(m_supplyPos, &state) == supply - 1 && \
						state.discardCount[players[i]] == discardCount + 1)
					{
						printf("PASS\n");
						break;
					}
					else
					{
						printf("FAIL\n");
						break;
					}
				}
				else
					break;
			}
		}
	}
    printf("****END UNITTEST 2****\n");
    return 0;
}    
