#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define NUMRUNS 10
//#define MYDEBUG

int testDoSmithy(struct gameState *state, int player, int handPos)
{
    return doSmithy(state, player, handPos);
}

int main(int argc, char* argv[])
{
    int color = 0;
    if(argc == 2 && strcmp(argv[1], "-c") == 0)
        color = 1;
    int failedTests = 0;
    printf("\n\n****BEGIN CARDTEST2: doSmithy****\n");
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
	int player = 0;
	
	printf ("State initalization.....");
	initializeGame(NUM_PLAYERS, k, 5, m_state);
	printf("PASS\n");
    
    //pre-test variables
    int preHandCount = m_state->handCount[player];
    int preDeckCount = m_state->deckCount[player];
    int prePlayedCount = m_state->playedCardCount;
    int handPos = m_state->hand[player][preHandCount - 1];
    int discardCard = handCard(handPos, m_state);
    
#ifdef MYDEBUG
    printf("preHandCount: %d\n", preHandCount);
    printf("preDeckCount: %d\n", preDeckCount);
    printf("prePlayedCount: %d\n", prePlayedCount);
    printf("prePlayedCard: %d\n", prePlayedCard);
    printf("handPos: %d\n", handPos);
    printf("discardCard: %d\n", discardCard);
#endif
    
    printf("Smithy returns 0.....");
    if(testDoSmithy(m_state, player, handPos) != 0)
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");
    
    printf("State not null.....");
    if(m_state != NULL)
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");

    printf("Test hand count.....");
    if(preHandCount + 2 != m_state->handCount[player])
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");
    
    printf("Test discardCard count.....");
    if(prePlayedCount + 1 != m_state->playedCardCount)
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");
    
    printf("Test discardCard card.....");
    if(discardCard != m_state->playedCards[m_state->playedCardCount - 1])
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");
    
    printf("Test deckCount.....");
    if(preDeckCount - 3 != m_state->deckCount[player])
    {
        printf("FAIL\n");
        failedTests++;
    }
    else
        printf("PASS\n");

#ifdef MYDEBUG
    printf("postHandCount: %d\n", m_state->handCount[player]);
    printf("postDeckCount: %d\n", m_state->deckCount[player]);
    printf("postPlayedCount: %d\n", m_state->playedCardCount);
    printf("postPlayedCard: %d\n", m_state->playedCards[m_state->playedCardCount - 1]);
    printf("postHandPos: %d\n", handPos);
    printf("postDiscardCard: %d\n", handCard(handPos, m_state));
#endif

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
    printf("****END CARDTEST2****\n");
    return 0;
}