#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define NUMRUNS 10
//#define MYDEBUG

int testDoVillage(struct gameState *state, int player, int handPos)
{
    return doVillage(state, player, handPos);
}

int main(int argc, char* argv[])
{
    int color = 0;
    if(argc == 2 && strcmp(argv[1], "-c") == 0)
        color = 1;
    int failedTests = 0;
    printf("\n\n****BEGIN CARDTEST3: doVillage****\n");
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
	int player = 0;
	
	printf ("State initalization.....");
	initializeGame(NUM_PLAYERS, k, 5, m_state);
	printf("PASS\n");
    
    //pre-test variables
    int preHandCount = m_state->handCount[player];
    int preActionCount = m_state->numActions;
    int preDeckCount = m_state->deckCount[player];
    int prePlayedCount = m_state->playedCardCount;
    int handPos = m_state->hand[player][preHandCount - 1];
    int discardCard = handCard(handPos, m_state);

    //test return succeeds without error
    printf("Village returns 0.....");
    if(testDoVillage(m_state, player, handPos) != 0)
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");
    
    //test state is not null somehow
    printf("State not null.....");
    if(m_state == NULL)
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");
    
    //test that we gained 1 card in hand
    printf("Gain 1 card.....");
    if(preHandCount != m_state->handCount[player])
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");
    
    //test that we decremented deck by 1 from drawCard
    printf("Decrement deck.....");
    if(preDeckCount - 1 != m_state->deckCount[player])
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");
    
    //test that we gained 2 actions
    printf("Gain 2 actions.....");
    if(preActionCount + 2 != m_state->numActions)
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");    
    
    //test that we discarded to playedcards 1 card
    printf("Discard count.....");
    if(prePlayedCount + 1 != m_state->playedCardCount)
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");
    
    //test that the card we discarded is last card on playedCards pile
    printf("Discard card.....");
    if(discardCard != m_state->playedCards[m_state->playedCardCount - 1])
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");

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
    printf("****END CARDTEST3****\n");
    return 0;
}