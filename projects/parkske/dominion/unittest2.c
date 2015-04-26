#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define TOFLAGMAX 3
#define MYDEBUG

int testGainCard(int m_supplyPos, struct gameState *m_state, int toFlag, int player)
{
    return gainCard(m_supplyPos, m_state, toFlag, player);
}

int main(int argc, char* argv[])
{
    int color = 0;
    if(argc == 2 && strcmp(argv[1], "-c") == 0)
        color = 1;
    printf("\n\n****BEGIN UNITTEST2: GainCard****\n");
    int failedTests = 0;
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    int i;
    int players[NUM_PLAYERS];
	int playerCardCount[NUM_PLAYERS];
    int flag = 0;
	enum CARD m_supplyPos;
	
    printf ("State initalization.....");
    initializeGame(NUM_PLAYERS, k, 5, m_state);
    printf("PASS\n");
	
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
                int pass = 0;
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
                            pass = 1;
                            failedTests++;
                        }   
                        if(m_state->deckCount[players[i]] != deckCount + 1)
                        {
                            printf("FAIL - deckCount; ");
                            pass = 1;
                            failedTests++;
                        }
                        if(m_state->deck[players[i]][m_state->deckCount[players[i]] - 1] != m_supplyPos)
                        {
                            printf("FAIL - gain card mismatch; ");
                            pass = 1;
                            failedTests++;
                        }
                        if(pass == 0)
                        {
                            printf("PASS\n");
                        }
                        else
                        {
                            printf("\n");
                        }
                        break;
                    }
                    else
                    {
                        printf("Card not in game\n");
                    }
                    break;
                case 2:;
                    int handCount = m_state->handCount[players[i]];
                    if(testGainCard(m_supplyPos, m_state, flag, players[i]) == 0)
                    {
                        if(supplyCount(m_supplyPos, m_state) != supply - 1)
                        {
                            printf("FAIL - supplyCount; ");
                            pass = 1;
                            failedTests++;
                        }   
                        if(m_state->handCount[players[i]] != handCount + 1)
                        {
                            printf("FAIL - handCount; ");
                            pass = 1;
                            failedTests++;
                        }
                        if(m_state->hand[players[i]][m_state->handCount[players[i]] - 1] != m_supplyPos)
                        {
                            printf("FAIL - gain card mismatch; ");
                            pass = 1;
                            failedTests++;
                        }
                        if(pass == 0)
                        {
                            printf("PASS\n");
                        }
                        else
                        {
                            printf("\n");
                        }
                        break;
                    }
                    else
                    {
                        printf("Card not in game\n");
                    }
                    break;
                default:;
                    int discardCount = m_state->discardCount[players[i]];
                    if(testGainCard(m_supplyPos, m_state, flag, players[i]) == 0)
                    {
                        if(supplyCount(m_supplyPos, m_state) != supply - 1)
                        {
                            printf("FAIL - supplyCount; ");
                            pass = 1;
                            failedTests++;
                        }   
                        if(m_state->discardCount[players[i]] != discardCount + 1)
                        {
                            printf("FAIL - dicardCount; ");
                            pass = 1;
                            failedTests++;
                        }
                        if(m_state->discard[players[i]][m_state->discardCount[players[i]] - 1] != m_supplyPos)
                        {
                            printf("FAIL - gain card mismatch; ");
                            pass = 1;
                            failedTests++;
                        }
                        if(pass == 0)
                        {
                            printf("PASS\n");
                        }
                        else
                        {
                            printf("\n");
                        }
                        break;
                    }
                    else
                    {
                        printf("Card not in game\n");
                    }
                    break;
                }
            }
        }
    }
    if(failedTests > 0)
        if(color)
            printf("\033[1;31mFailed %d tests\033[0m\n", failedTests);
        else
            printf("Failed %d tests\n", failedTests);
    else
        if(color)
            printf("\033[1;32mFailed %d tests\033[0m\n", failedTests);	
        else
            printf("Failed %d tests\n", failedTests);	
    printf("****END UNITTEST 2****\n");
    return 0;
}    
