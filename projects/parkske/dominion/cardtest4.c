#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define NUMRUNS 4
//#define MYDEBUG

int testDoSteward(struct gameState *state, int player, int handPos, int* choices)
{
    return doSteward(state, player, handPos, choices);
}

int main(int argc, char* argv[])
{
    int color = 0;
    if(argc == 2 && strcmp(argv[1], "-c") == 0)
        color = 1;
    int failedTests = 0;
    printf("\n\n****BEGIN CARDTEST4: doSteward****\n");
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
	int player = 0;
    int choices[3];
    int i;

    for(i = 1; i < NUMRUNS; i++)
    {
        printf ("State initalization.....");
        initializeGame(NUM_PLAYERS, k, 5, m_state);
        printf("PASS\n");
        
        //iterate through each option for choices[0]
        //choices[0] == +2 cards
        //choices[1] == +2 coins
        //choices[<0 || >=3] == trash 2 cards in hand
        choices[0] = i;
        
        //pre-test variables
        int preHandCount = m_state->handCount[player];
        int preCoinCount = m_state->coins;
        int preDeckCount = m_state->deckCount[player];
        int prePlayedCount = m_state->playedCardCount;
        int handPos = m_state->hand[player][preHandCount - 1];
        int choice1 = m_state->hand[player][preHandCount - 2];
        int choice2 = m_state->hand[player][preHandCount - 3];
        int discardCard = handCard(handPos, m_state);

        if(i > 2)
        {
            choices[1] = choice1;
            choices[2] = choice2;
        }
        
        //test return succeeds without error
        printf("Steward returns 0.....");
        if(testDoSteward(m_state, player, handPos, choices) != 0)
        {
            printf("FAIL\n");
            failedTests++;
        }
        else
            printf("PASS\n");

        //test discard card after action
        printf("Discard count.....");
        if(prePlayedCount + 1 != m_state->playedCardCount)
        {
            printf("FAIL\n");
            failedTests++;
        }
        else
            printf("PASS\n"); 

        //check that the card we discarded is the one we expected
        printf("Discard card.....");
        if(discardCard != m_state->playedCards[m_state->playedCardCount - 1])
        {
            printf("FAIL\n");
            failedTests++;
        }
        else
            printf("PASS\n");         
        
        switch(i)
        {
        case 1:
                //test hand +2
                printf("Draw 2 cards.....");
                if(preHandCount + 1 != m_state->handCount[player])
                {
                    printf("FAIL\n");
                    failedTests++;
                }
                else
                    printf("PASS\n");  
                
                //test deck -2
                printf("Deck -2 cards.....");
                if(preDeckCount - 2 != m_state->deckCount[player])
                {
                    printf("FAIL\n");
                    failedTests++;
                }
                else
                    printf("PASS\n");  
                break;
        case 2:
                printf("Coins +2.....");
                if(preCoinCount + 2 != m_state->coins)
                {
                    printf("FAIL\n");
                    failedTests++;
                }
                else
                    printf("PASS\n");  
                break;
        default:
                //cards are trashed, not added to playedCardCount
                printf("Trashed, not played.....");
                if(prePlayedCount + 1 != m_state->playedCardCount)
                {
                    printf("FAIL\n");
                    failedTests++;
                }
                else
                    printf("PASS\n");  
                
                break;
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
    printf("****END CARDTEST4****\n");
    return 0;
}