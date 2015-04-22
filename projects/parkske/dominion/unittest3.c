#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_PLAYERS 2
#define TOFLAGMAX 1
#define MYDEBUG

int main(int argc, char* argv[])
{
    printf("\n\n****BEGIN UNITTEST3: DiscardCard****\n");
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
                if(flag == 0)
                {
                    if(testDiscardCard(m_handPos, players[i], m_state, flag) == 0)
                }
                printf("Player%d testDiscardCard flag:%d card:%d.....", i+1, flag, m_supplyPos);
                
            }
        }
    }
    printf("****END UNITTEST 2****\n");
    return 0;
}    
