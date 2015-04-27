#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

#define NUM_PLAYERS 2
#define TOFLAGMAX 3
#define MYDEBUG

int testGainCard(int m_supplyPos, struct gameState *m_state, int toFlag, int player)
{
    return gainCard(m_supplyPos, m_state, toFlag, player);
}

int main(int argc, char* argv[])
{
    printf("\n\n****Start Unit Test 2: GainCard****\n");
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    int i;
    int players[NUM_PLAYERS];
	int playerCardCount[NUM_PLAYERS];
    int flag = 0;
	enum CARD m_supplyPos;
	
    printf ("Start initalization.....");
    initializeGame(NUM_PLAYERS, k, 5, m_state);
    printf("Pass\n");
	

    SelectStream(2);
  PutSeed(3);
	for(i=0; i < NUM_PLAYERS; i++)
    {
        players[i] = i;
		playerCardCount[i] = m_state->handCount[i];
    }
    for(m_supplyPos=0; m_supplyPos <= treasure_map; m_supplyPos++)
    {
        for(i=0; i < NUM_PLAYERS; i++)
        {
            for(flag=0; flag < TOFLAGMAX; flag++)
            {
                int Pass = 0;
                printf("Player%d testGainCard flag:%d card:%d.....", i+1, flag, m_supplyPos);
                int supply = supplyCount(m_supplyPos, m_state);
                switch(flag)
                {
                case 1:;
                    int deckCount = m_state->deckCount[players[i]];
                    if(testGainCard(m_supplyPos, m_state, flag, players[i]) == 0)
                    {
                        if(supplyCount(m_supplyPos, m_state) != supply - 1)
                        {
                            printf("FAIL - supplyCount; ");
                            Pass = 1;
                        }   
                        if(m_state->deckCount[players[i]] != deckCount + 1)
                        {
                            printf("FAIL - deckCount; ");
                            Pass = 1;
                        }
                        if(m_state->deck[players[i]][m_state->deckCount[players[i]] - 1] != m_supplyPos)
                        {
                            printf("FAIL - gain card mismatch; ");
                            Pass = 1;
                        }
                        if(Pass == 0)
                        {
                            printf("Pass\n");
                        }
                        else
                        {
                            printf("\n");
                        }
                        break;
                    }
                    else
                    {
                        printf("No Card\n");
                    }
                    break;
                case 2:;
                    int handCount = m_state->handCount[players[i]];
                    if(testGainCard(m_supplyPos, m_state, flag, players[i]) == 0)
                    {
                        if(supplyCount(m_supplyPos, m_state) != supply - 1)
                        {
                            printf("FAIL - supplyCount; ");
                            Pass = 1;
                        }   
                        if(m_state->handCount[players[i]] != handCount + 1)
                        {
                            printf("FAIL - handCount; ");
                            Pass = 1;
                        }
                        if(m_state->hand[players[i]][m_state->handCount[players[i]] - 1] != m_supplyPos)
                        {
                            printf("FAIL - gain card mismatch; ");
                            Pass = 1;
                        }
                        if(Pass == 0)
                        {
                            printf("Pass\n");
                        }
                        else
                        {
                            printf("\n");
                        }
                        break;
                    }
                    else
                    {
                        printf("No Card\n");
                    }
                    break;
                default:;
                    int discardCount = m_state->discardCount[players[i]];
                    if(testGainCard(m_supplyPos, m_state, flag, players[i]) == 0)
                    {
                        if(supplyCount(m_supplyPos, m_state) != supply - 1)
                        {
                            printf("FAIL - supplyCount; ");
                            Pass = 1;
                        }   
                        if(m_state->discardCount[players[i]] != discardCount + 1)
                        {
                            printf("FAIL - dicardCount; ");
                            Pass = 1;
                        }
                        if(m_state->discard[players[i]][m_state->discardCount[players[i]] - 1] != m_supplyPos)
                        {
                            printf("FAIL - gain card mismatch; ");
                            Pass = 1;
                        }
                        if(Pass == 0)
                        {
                            printf("Pass\n");
                        }
                        else
                        {
                            printf("\n");
                        }
                        break;
                    }
                    else
                    {
                        printf("No Card\n");
                    }
                    break;
                }
            }
        }
    }
    printf("****End of Unit Test 2****\n");
    return 0;
}