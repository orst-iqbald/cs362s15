#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define TOFLAGMAX 1
//#define MYDEBUG

int testDiscardCard(int m_handPos, int player, struct gameState *state, int flag)
{
	return discardCard(m_handPos, player, state, flag);
}

int main(int argc, char* argv[])
{
    int color = 0;
    if(argc == 2 && strcmp(argv[1], "-c") == 0)
        color = 1;
    int failedTests = 0;
    printf("\n\n************** BEGIN UNITTEST 3: DiscardCard **************\n");
	struct gameState *m_state = newGame();
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    int runs;
	int i;
	int j;
    int players[NUM_PLAYERS];
	int playerHandCount[NUM_PLAYERS];
    int flag = 0;
	
	srand(time(NULL));
	for(runs = 10; runs > 0; runs--)
	{
		printf ("DiscardCard State initalization.....");
		initializeGame(NUM_PLAYERS, k, 5, m_state);
		printf("PASS\n");
		
		//create num of players and record their hand count
		for(i=0; i < NUM_PLAYERS; i++)
		{
			players[i] = i;
			playerHandCount[i] = m_state->handCount[i];
		}
		
		for(i=0; i < NUM_PLAYERS; i++)
		{
			for(j=playerHandCount[i] - 1; j >= 0; j--)
			{
				int m_handCount = m_state->handCount[i]; //# of cards in hand
				int m_handPos = rand() % m_handCount + 1; //index of card to discard, 1 or 0
				// int m_handPos = m_handCount % 2; //index of card to discard, 1 or 0
				int m_playedCount = m_state->playedCardCount; //count of played cards
				int m_handCard = m_state->hand[i][m_handPos]; //card type to discard
				int m_lastHandCard = m_state->hand[i][m_handCount - 1]; //last card in hand
				int pass = 0;
				if(m_handCount % 2 == 0)
				{
					flag = 0;
				}
				else
					flag = 1;
				printf("DiscardCard P%d ", i+1);
				printf("flag:%d ", flag);
				printf("discard %d.....", m_handCount);
				if(testDiscardCard(m_handPos, i, m_state, flag) == 0)
				{
					if(flag == 0)
					{
						//check that playedCardCount increased
						if(m_state->playedCardCount != m_playedCount + 1)
						{
							printf("FAIL - playedCardCount; ");
							pass = 1;
                            failedTests++;
						}
						//check that the card in question in last card there
						if(m_state->playedCards[m_playedCount] != m_handCard)
						{
							printf("FAIL - playedCards; ");
							pass = 1;
                            failedTests++;
						}
					}
					//check that m_handPos is -1 then since it's last card
					if((m_handPos == m_handCount - 1) || (m_handCount == 1))
					{
						if(m_state->hand[i][m_handPos] != -1)
						{
							printf("FAIL - lastCardEnd;");
							pass = 1;
                            failedTests++;
						}					
					}
					//if index isn't last in hand or only card, make sure gap is filled
					else
					{
						//last card should be moved to discard index
						if(m_state->hand[i][m_handPos] != m_lastHandCard)
						{
							printf("FAIL - fillHandPos;");
							pass = 1;
                            failedTests++;
						}
						//make sure last card swapped to gap is -1
						if(m_state->hand[i][m_handCount - 1] != -1)
						{
							printf("FAIL - lastCard;");
							pass = 1;
                            failedTests++;
						}
					}
					//make sure handCount decremented
					if(m_handCount - 1 != m_state->handCount[i])
					{
						printf("FAIL - handCount; ");
						pass = 1;
                        failedTests++;
					}
					if(pass != 0)
					{
						printf("\n");
					}
					else
					{
						printf("PASS\n");
					}
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
    printf("************** END UNITTEST 3: DiscardCard **************\n");
    return 0;
}    
